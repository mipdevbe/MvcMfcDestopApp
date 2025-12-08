#include "CompanyModel.h"

CompanyModel::CompanyModel(int id, const std::string& name)
	: id(id), name(name) {
}

CompanyModel::~CompanyModel() {
}

int CompanyModel::getId() const {
	return id;
}

const std::string& CompanyModel::getName() const {
	return name;
}
