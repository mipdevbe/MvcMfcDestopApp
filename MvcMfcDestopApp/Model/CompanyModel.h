#pragma once
#include <string>
#include "../Model/IModel.h"

class CompanyModel : public IModel
{
public: 
	CompanyModel(int id, const std::string& name);
	virtual ~CompanyModel();
	int getId() const;
	const std::string& getName() const;

private:
	int id;
	std::string name;	
};