#pragma once

#include <vector>
#include "..\Model\CompanyModel.h"

class CompaniesModel {
public:

	CompaniesModel() {}
	virtual ~CompaniesModel() {}

	void Load() {
		// Simulate loading data
		_models.emplace_back(1, "TechCorp");
		_models.emplace_back(2, "BizSolutions");
		_models.emplace_back(3, "InnovateLtd");
	}

private:
	std::vector<CompanyModel> _models;
};