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

	std::vector<std::unique_ptr<EmployeeModel>> getDataSet();

	void RunTrial();
};