#include <iostream>
#include <vector>
#include <string>
#include "../Model/EmployeesModel.h"

EmployeesModel::EmployeesModel()
{
}

EmployeesModel::~EmployeesModel()
{
}

bool EmployeesModel::add(const EmployeeModel& newCompany)
{
	// Check if company with the same ID already exists
	for (const auto& company : employees) {
		if (company.getId() == newCompany.getId()) {
			return false; // Company with this ID already exists
		}
	}
	employees.emplace_back(newCompany);
	return true;
}

bool EmployeesModel::remove(int id)
{
	auto it = std::remove_if(employees.begin(), employees.end(),
		[id](const EmployeeModel& company) {
			return company.getId() == id;
		});

	if (it != employees.end()) {
		employees.erase(it, employees.end());
		return true; // Company removed
	}

	return false; // Company not found
}

const std::vector<EmployeeModel>& EmployeesModel::getAll() const
{
	return employees;
}
