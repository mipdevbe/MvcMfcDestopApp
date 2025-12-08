#pragma once
#include <vector>
#include "../Model/IModel.h"
#include "../Model/CompanyModel.h"

class CompaniesModel : public IModel {
public:
	CompaniesModel();
	virtual ~CompaniesModel();

	bool addCompany(const CompanyModel& company);
	bool removeCompany(int id);
	const std::vector<CompanyModel>& getAll() const;

private:
	std::vector<CompanyModel> companies;
};