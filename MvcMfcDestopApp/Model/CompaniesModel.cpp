#include <iostream>
#include <vector>
#include <string>
#include "../Model/CompaniesModel.h"

CompaniesModel::CompaniesModel() 
{
	
/*	companies.emplace_back(1, "Tech Solutions");
	companies.emplace_back(2, "Innovatech");
	companies.emplace_back(3, "Global Corp");
*/
}

CompaniesModel::~CompaniesModel() 
{
}

bool CompaniesModel::addCompany(const CompanyModel& newCompany)
{
	// Check if company with the same ID already exists
	for (const auto& company : companies) {
		if (company.getId() == newCompany.getId()) {
			return false; // Company with this ID already exists
		}
	}
	companies.emplace_back(newCompany);
	return true;
}

bool CompaniesModel::removeCompany(int id)
{
	auto it = std::remove_if(companies.begin(), companies.end(),
		[id](const CompanyModel& company) {
			return company.getId() == id;
		});

	if (it != companies.end()) {
		companies.erase(it, companies.end());
		return true; // Company removed
	}

	return false; // Company not found
}

const std::vector<CompanyModel>& CompaniesModel::getAll() const
{
	return companies;
}
