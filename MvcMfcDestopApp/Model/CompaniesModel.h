#pragma once

#include <vector>
#include <memory>
#include "..\Model\CompanyModel.h"

class CompaniesModel {
public:
	CompaniesModel() {}
	virtual ~CompaniesModel() {}

	void Load() {
		// Simulate loading data
		_models.emplace_back(std::make_shared<CompanyModel>(1, "TechCorp"));
		_models.emplace_back(std::make_shared<CompanyModel>(2, "BizSolutions"));
		_models.emplace_back(std::make_shared<CompanyModel>(3, "InnovateLtd"));
	}

	const std::vector<std::shared_ptr<IModel>>& getData() const {
		return _models;
	}

private:
	std::vector<std::shared_ptr<IModel>> _models;
};