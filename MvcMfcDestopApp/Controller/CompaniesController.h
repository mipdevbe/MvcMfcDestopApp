#pragma once
#include <functional>
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

	void Initialize() override
	{
	}

	// async ??
	void Load() override
	{
		_companiesModel.Load();
		auto view = View<CMvcMfcDestopAppDlg>(); // existing helper that returns shared_ptr<IView>

	}

	void Update() override
	{
		// Implementation of Update
	}

	void Close() override
	{
		// Implementation of Close
	}

private:
	CompaniesModel _companiesModel;
};