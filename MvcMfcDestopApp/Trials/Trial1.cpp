#include "Trial1.h"
#include <iostream>

TrialOne::TrialOne()
{
}

TrialOne::~TrialOne()
{
}

// Returns the dataset by moving it (useful if you want to transfer ownership)
std::vector<std::unique_ptr<EmployeeModel>>&& TrialOne::moveDataSet()
{
    // Create a static dataset to demonstrate move semantics.
    static std::vector<std::unique_ptr<EmployeeModel>> dataset;
    if (dataset.empty()) {
        dataset.emplace_back(std::make_unique<EmployeeModel>(1, 1, "TechCorp"));
        dataset.emplace_back(std::make_unique<EmployeeModel>(2, 1, "BizSolutions"));
        dataset.emplace_back(std::make_unique<EmployeeModel>(3, 1, "InnovateLtd"));
    }
    return std::move(dataset);
}

// Returns a copy of the dataset
std::vector<std::unique_ptr<EmployeeModel>> TrialOne::getDataSet() const
{
	auto dataset = std::vector<std::unique_ptr<EmployeeModel>>{};

	dataset.emplace_back(std::make_unique<EmployeeModel>(1, 1, "TechCorp"));
	dataset.emplace_back(std::make_unique<EmployeeModel>(2, 1, "BizSolutions"));
	dataset.emplace_back(std::make_unique<EmployeeModel>(3, 1, "InnovateLtd"));

	return dataset;
}

void TrialOne::Run()
{
	// auto results = getDataSet();
	auto results = std::move(moveDataSet());
	for (const auto& item : results)
	{
		std::cout << "Employee ID: " << item->getId()
			<< ", Company ID: " << item->getCompanyId()
			<< ", Name: " << item->getName() << std::endl;
	}
}
