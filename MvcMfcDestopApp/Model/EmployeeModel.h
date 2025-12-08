#pragma once

#include <string>
#include "../Model/IModel.h"

class EmployeeModel : public IModel
{
public:

	EmployeeModel(int id, int companyId, const std::string& name) : _id(id), _companyId(companyId), _name(name) {}
	virtual ~EmployeeModel() {}

	int getId() const { return _id; }
	int getCompanyId() const { return _companyId; }
	const std::string& getName() const { return _name; }

private:
	int _id;
	int _companyId;
	std::string _name;

};