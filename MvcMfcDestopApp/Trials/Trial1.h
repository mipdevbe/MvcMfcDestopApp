#pragma once
#include <vector>
#include <memory>
#include "../Model/IModel.h"
#include "../Model/EmployeeModel.h"

class TrialOne 
{
public:
	TrialOne();
	virtual ~TrialOne();

	// Returns a copy of the dataset
	std::vector<std::unique_ptr<EmployeeModel>> getDataSet() const;

	// Returns the dataset by moving it (useful if you want to transfer ownership)
	std::vector<std::unique_ptr<EmployeeModel>>&& moveDataSet();

	void Run();
};