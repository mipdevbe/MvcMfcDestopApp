#pragma once
#include <iostream>
#include <vector>
#include "../Controller/CompaniesController.h"
#include "../Controller/EmployeeController.h"
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

	const CompaniesController& Companies() const {
		return _companiesController;
	}

	const EmployeeController& Employee() const {
		return _employeeController;
	}

	const LeaveController& Leave() const {
		return _leaveController;
	}

private:
	CompaniesController _companiesController;
    EmployeeController _employeeController;
    LeaveController _leaveController;
};