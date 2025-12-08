#pragma once

#include <vector>
#include <memory>
#include "..\Model\EmployeeModel.h"

class EmployeesModel {
public:
	EmployeesModel() {}
	virtual ~EmployeesModel() {}

	void Load(int comppanyId = -1) {

		// Simulate loading data
		_models.emplace_back(std::make_shared<EmployeeModel>(1, 1, "TechCorp"));
		_models.emplace_back(std::make_shared<EmployeeModel>(2, 1, "BizSolutions"));
		_models.emplace_back(std::make_shared<EmployeeModel>(3, 1, "InnovateLtd"));

		_models.emplace_back(std::make_shared<EmployeeModel>(1, 2, "TechCorp"));
		_models.emplace_back(std::make_shared<EmployeeModel>(2, 2, "BizSolutions"));

		_models.emplace_back(std::make_shared<EmployeeModel>(1, 3, "TechCorp"));
		_models.emplace_back(std::make_shared<EmployeeModel>(2, 3, "BizSolutions"));
		_models.emplace_back(std::make_shared<EmployeeModel>(3, 3, "InnovateLtd"));
	}

	const std::vector<std::shared_ptr<IModel>>& getData() const {
		return _models;
	}

private:
	std::vector<std::shared_ptr<IModel>> _models;
}; 
