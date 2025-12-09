#pragma once
#include "../Controller/IControler.h"
#include "../Model/EmployeesModel.h"
#include "../View/EmployeeView.h"
#include<thread>
#include<mutex>
#include<vector>
#include<memory>

class EmployeesController : public IController
{
public:

	EmployeesController() : IController()
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
	void LoadAsync(int companyId = -1, HWND notifyHwnd = nullptr) {
		auto view = View<EmployeeView>();
		if (view) {
			std::vector<std::shared_ptr<IModel>>placeholder;
			placeholder.emplace_back(std::make_shared<EmployeeModel>(-1, -1, "Loading.."));
			view->UpdateView(placeholder);
		}
		std::thread([this, companyId, notifyHwnd]() {
			EmployeesModel modelCopy;
			modelCopy.Load(companyId);
			{
				std::lock_guard<std::mutex> lk(_mtx);
				_latestData = modelCopy.getData();
			}
			if (notifyHwnd) {
				::PostMessage(notifyHwnd, WM_EMPLOYEES_LOADED, 0, 0);
			}
			}).detach();
	}
	void PublishLatest() {
		auto view = View<EmployeeView>();
		if (!view)return;
		std::vector<std::shared_ptr<IModel>>dataCopy; {
			std::lock_guard<std::mutex> lk(_mtx);
			dataCopy = _latestData;
		}
		view->UpdateView(dataCopy);
	}
private:
	EmployeesModel _employeesModel;
	std::mutex _mtx;
	std::vector<std::shared_ptr<IModel>> _latestData;
};