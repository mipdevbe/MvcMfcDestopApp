#pragma once
#include <string>
#include "../Model/IModel.h"

class CompanyModel : public IModel
{
public: 

	CompanyModel::CompanyModel(int id, const std::string& name)
		: id(id), name(name) , IModel() {
	}

	virtual CompanyModel::~CompanyModel() {
	}

	int CompanyModel::getId() const {
		return id;
	}

	const std::string& CompanyModel::getName() const {
		return name;
	}


private:
	int id;
	std::string name;	
};