#include "Trial1.h"
#include <iostream>

TrialOne::TrialOne()
{
}

TrialOne::~TrialOne()
{
}

void TrialOne::RunTrial()
{
	auto results = getDataSet();
	for (const auto& item : results)
	{
		std::cout << "Employee ID: " << item->getId()
			<< ", Company ID: " << item->getCompanyId()
			<< ", Name: " << item->getName() << std::endl;
	}
}

std::vector<std::unique_ptr<EmployeeModel>> TrialOne::getDataSet()
{
	auto dataset = std::vector<std::unique_ptr<EmployeeModel>>{};

	dataset.emplace_back(std::make_unique<EmployeeModel>(1, 1, "TechCorp"));
	dataset.emplace_back(std::make_unique<EmployeeModel>(2, 1, "BizSolutions"));
	dataset.emplace_back(std::make_unique<EmployeeModel>(3, 1, "InnovateLtd"));

	return dataset;
}