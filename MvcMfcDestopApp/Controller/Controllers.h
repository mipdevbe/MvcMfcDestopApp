#pragma once
#include <iostream>
#include <vector>
#include "../Controller/CompaniesController.h"
#include "../Controller/EmployeesController.h"
#include "../Controller/LeaveController.h"

#include <typeindex>

using namespace std;

class Controllers
{
public:
	Controllers() { cout << "Controllers instance created" << endl; }

	virtual ~Controllers() {
		cout << "Controllers instance destroyed" << endl;
	}

	void Initialize()
	{
	}

	CompaniesController& Companies() {
		return _companiesController;
	}

	EmployeesController& Employees() {
		return _employeesController;
	}

	LeaveController& Leave() {
		return _leaveController;
	}

private:
	CompaniesController _companiesController;
    EmployeesController _employeesController;
    LeaveController _leaveController;
};