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

	void doWork() override
	{
		while (!stopRequested.load())
		{
			std::tuple<RequestType, int> request;
			if (_requestQueue.pop(request))
			{
				std::tuple<RequestType, std::vector<std::unique_ptr<IModel>>> result;
				switch (std::get<0>(request))
				{
					case RequestType::LoadEmployees:
					{
						int companyId = std::get<1>(request);
						_employeesModel.Load(companyId);
						result = std::make_tuple(RequestType::LoadEmployees, _employeesModel.getData());
						_resultQueue.push(std::move(result));
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
			std::tuple<RequestType, std::vector<std::unique_ptr<IModel>>> result;
			if (_resultQueue.pop(result))
			{
				if (view)
				{
					switch (std::get<0>(result))
					{
						case RequestType::LoadEmployees:
						{
							view->UpdateView(std::move(std::get<1>(result)));
							break;
						}
					}
				}
			}

			// Sleep for interval period
			std::this_thread::sleep_for(std::chrono::milliseconds(20));
		}
	}
private:
	EmployeesModel _employeesModel{};
	MessagingQueue<std::tuple<RequestType, int>> _requestQueue{};
	MessagingQueue<std::tuple<RequestType,std::vector<std::unique_ptr<IModel>>>> _resultQueue{};
};