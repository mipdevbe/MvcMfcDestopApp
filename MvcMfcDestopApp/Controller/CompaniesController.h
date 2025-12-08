#pragma once
#include "../Controller/IControler.h"
#include "../Model/CompaniesModel.h"

class CompaniesController : public IController
{
public:

	CompaniesController()
	{
	}

	virtual ~CompaniesController()
	{
	}

	bool Initialize() override
	{
		return true;
	}

	bool Load() override
	{
		_companiesModel.Load(); // --> should fire to the ui.
		return true;
	}

	bool Update() override
	{
		// Implementation of Update
		return true;
	}

	bool Close() override
	{
		// Implementation of Close
		return true;
	}

private:
	CompaniesModel _companiesModel;
};