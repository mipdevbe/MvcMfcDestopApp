#pragma once
#include <vector>
#include <memory>
#include "../Model/IModel.h"
#include "../Model/EmployeeModel.h"

class TrialOne 
{
public:
	using EmployeeModelPtr = std::unique_ptr<EmployeeModel>;

	TrialOne();
	virtual ~TrialOne();

	// Returns a copy of the dataset
	std::vector<EmployeeModelPtr> getDataSet() const;

	// Returns the dataset by moving it (useful if you want to transfer ownership)
	std::vector<EmployeeModelPtr>&& moveDataSet();

	void Run();
};