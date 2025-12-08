#pragma once

#include <vector>
#include "../Model/IModel.h"
#include "../Model/EmployeeModel.h"

class EmployeesModel : public IModel
{
public:
	EmployeesModel();
	virtual ~EmployeesModel();

	bool add(const EmployeeModel& employee);
	bool remove(int id);
	const std::vector<EmployeeModel>& getAll() const;

private:
	std::vector<EmployeeModel> employees;
};