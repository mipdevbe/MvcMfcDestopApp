#pragma once
#include "../Controller/IControler.h"
#include "../Model/EmployeesModel.h"
#include "../View/EmployeeView.h"

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

private:
	EmployeesModel _employeesModel;
};