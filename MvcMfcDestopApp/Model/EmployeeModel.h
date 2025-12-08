#pragma once

#include <string>
#include "../Model/IModel.h"

class EmployeeModel : public IModel
{
public:

	EmployeeModel(int id, const std::string& name);
	virtual ~EmployeeModel();

	int getId() const;
	const std::string& getName() const;

private:
	int id;
	std::string name;

};