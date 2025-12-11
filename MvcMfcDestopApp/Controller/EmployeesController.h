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
#include <Windows.h>

class EmployeesController : public IController, public ThreadingBase
{
private:
	enum class RequestType
	{
		LoadEmployees,
		UpdateEmployee,
		DeleteEmployee
	};

public:

	EmployeesController() 
	{
	}

	virtual ~EmployeesController()
	{
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
		std::tuple<RequestType, int> request = std::make_tuple(RequestType::LoadEmployees, companyId);
		_requestQueue.push(std::move(request));
	}

private:

	void SetActionMessage(LPCSTR message)
	{
		auto view = View<EmployeeView>();
		if (view) {
		}
	}

protected:

	using ResultTuple = std::tuple<RequestType, const std::vector<std::unique_ptr<IModel>>*>;

	void doWork() override
	{
		while (!stopRequested.load())
		{
			std::tuple<RequestType, int> request;
			if (_requestQueue.pop(request))
			{
				ResultTuple result;
				switch (std::get<0>(request))
				{
				case RequestType::LoadEmployees:
				{
					int companyId = std::get<1>(request);
					_employeesModel.Load(companyId);
					result = std::make_tuple(RequestType::LoadEmployees, &_employeesModel.getData());
					_resultQueue.push(result); 
					break;
				}
				}
			}

			this_thread::sleep_for(chrono::milliseconds(20));
		}
	}

private:
	// Responsible to flush all results and propage them....
	std::thread resultsThread;
	atomic<bool> stopResultsRequested{ false };

	void processingProc()
	{
		auto view = View<EmployeeView>(); // existing helper that returns shared_ptr<IView>

		while (!stopResultsRequested.load())
		{
			ResultTuple result;
			if (_resultQueue.pop(result))
			{
				if (view)
				{
					switch (std::get<0>(result))
					{
					case RequestType::LoadEmployees:
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
	MessagingQueue<std::tuple<RequestType, int>> _requestQueue{};
	MessagingQueue<ResultTuple> _resultQueue{};
};