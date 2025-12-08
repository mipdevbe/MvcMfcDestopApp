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
	virtual bool Load() override
	{
		_companiesModel.Load(); // --> should fire to the ui.

		View<CMvcMfcDestopAppDlg>()->Update();
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