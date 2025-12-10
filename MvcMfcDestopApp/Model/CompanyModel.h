#pragma once
#include <string>
#include "../Model/IModel.h"

class CompanyModel : public IModel
{
public: 

	CompanyModel(int id, const std::string& name)
		: id(id), name(name) , IModel() {
	}

	virtual ~CompanyModel() {
	}

	int getId() const {
		return id;
	}

	const std::string& getName() const {
		return name;
	}

private:
	int id;
	std::string name;	
};