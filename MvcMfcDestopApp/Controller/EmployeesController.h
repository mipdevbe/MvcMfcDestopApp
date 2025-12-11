#pragma once
#include "../Controller/IControler.h"
#include "../Model/EmployeesModel.h"
#include "../View/EmployeeView.h"
#include "../Tools/ThreadingBase.h"
#include "../Tools/MessagingQueue.h"

#include <thread>
#include <string>
#include <mutex>
#include <chrono>
#include <future>
#include <memory>
#include <vector>
#include <array>
#include <any>
#include <Windows.h>
#include <Filter.h>
#include <Filter.h>

class EmployeesController : public IController, public ThreadingBase
{
private:
	enum class RequestType
	{
		LoadEmployees,
		UpdateEmployee,
		DeleteEmployee,
		SearchEmployees
	};

public:

	EmployeesController() 
	{
	}

	virtual ~EmployeesController()
	{
		stop();
	}

	void Initialize() override
	{
	}

	// async ??
	void Load() override
	{
		Load(-1);
	}

	void Load(int comppanyId = -1)
	{
		_employeesModel.Load(comppanyId);
		auto view = View<EmployeeView>(); // existing helper that returns shared_ptr<IView>
		if (view) view->UpdateView(_employeesModel.getData());

	}

	void Update() override
	{
		// Implementation of Update
	}

	void Close() override
	{
		// Implementation of Close
	}

	void LoadAsync(int companyId = -1) {
		start();

		SetActionMessage("Loading employees...");
		RequestTuple request = std::make_tuple(RequestType::LoadEmployees, std::vector<std::any> { companyId });
		_requestQueue.push(request);
	}


	void SearchAsync(const std::string& criteria, int companyId = -1) {
		start();

		SetActionMessage("Searching employees...");
		RequestTuple request = std::make_tuple(RequestType::SearchEmployees, std::vector<std::any> { criteria, companyId });
		_requestQueue.push(request);
	}

private:

	void SetActionMessage(LPCSTR message)
	{
		auto view = View<EmployeeView>();
		if (view)
		{
			auto employee = std::make_unique<EmployeeModel>(
				-1,
				-1,
				message
			);

			_placeholder.clear();
			_placeholder.emplace_back(std::move(employee));
			view->UpdateView(_placeholder);
		}
	}

protected:

	using ResultTuple = std::tuple<RequestType, const std::vector<std::unique_ptr<IModel>>*>;
	using RequestTuple = std::tuple<RequestType, std::vector< std::any >>;

	void doActionsWork() override
	{
		while (!stopRequested.load())
		{
			RequestTuple request;
			if (_requestQueue.pop(request))
			{
				ResultTuple result;
				auto requestType = std::get<0>(request); 
				switch (requestType)
				{
					case RequestType::LoadEmployees:
					{
						auto companyIdAny = std::get<1>(request)[0];
						int companyId = std::any_cast<int>(companyIdAny);

						_employeesModel.Load(companyId);
						result = std::make_tuple(requestType, &_employeesModel.getData());
						_resultQueue.push(result); 
						break;
					}
					case RequestType::SearchEmployees:
					{
						//-----------------------------------------------------------------------
						// ? how to be sure we have the expected amount and expected data types ?
						//-----------------------------------------------------------------------

						auto criteriaAny = std::get<1>(request)[0];
						auto companyIdAny = std::get<1>(request)[1];

						std::string criteria = std::any_cast<std::string>(criteriaAny);
						int companyId = std::any_cast<int>(companyIdAny);

						_employeesModel.Load(companyId);

						_filteredDataSet.clear();
						for (const auto& item : _employeesModel.getData()) {
							auto* employee = dynamic_cast<EmployeeModel*>(item.get());
							if (employee)
							{
								auto firstCheck = employee->getName()._Starts_with(criteria);
								auto secondCheck = employee->getCompanyId() == companyId;
								if ((firstCheck) && (secondCheck))
								{
									_filteredDataSet.emplace_back(std::make_unique<EmployeeModel>(
										employee->getId(),
										employee->getCompanyId(),
										employee->getName()
									));
								}
							}
						}


						result = std::make_tuple(requestType, &_filteredDataSet);
						_resultQueue.push(result);
						break;
					}

				}
			}

			this_thread::sleep_for(chrono::milliseconds(20));
		}
	}

	// Responsible to flush all results and propage them....
	void doResultsWork() override
	{
		auto view = View<EmployeeView>(); // existing helper that returns shared_ptr<IView>

		while (!stopRequested.load())
		{
			ResultTuple result;
			if (_resultQueue.pop(result))
			{
				if (view)
				{
					switch (std::get<0>(result))
					{
					case RequestType::LoadEmployees:
					case RequestType::SearchEmployees:
					{
						const auto* data = std::get<1>(result);
						if (data) {
							view->UpdateView(*data);
						}
						break;
					}
					}
				}
			}

			
			std::this_thread::sleep_for(std::chrono::milliseconds(20));
		}
	}
private:
	EmployeesModel _employeesModel{};
	MessagingQueue<RequestTuple> _requestQueue{};
	MessagingQueue<ResultTuple> _resultQueue{};

	std::vector<std::unique_ptr<IModel>> _filteredDataSet{};
	std::vector<std::unique_ptr<IModel>> _placeholder{};
};