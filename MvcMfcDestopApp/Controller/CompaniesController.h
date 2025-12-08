#pragma once
#include "../Controller/IControler.h"
#include "../Model/CompaniesModel.h"
#include "../MvcMfcDestopAppDlg.h"

class CompaniesController : public IController
{
public:

	CompaniesController() : IController()
	{
	}

	virtual ~CompaniesController()
	{
	}

	bool Initialize() override
	{
		registerModel<CompaniesModel>();

		return true;
	}

	// async ??
	bool Load() override
	{
		_companiesModel.Load();
		View<CMvcMfcDestopAppDlg>()->UpdateView();

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