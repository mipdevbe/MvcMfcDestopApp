#pragma once
#include "../Controller/IControler.h"
#include "../Model/CompaniesModel.h"
#include "../MvcMfcDestopAppDlg.h"

class CompaniesController : public IController
{
public:

	//------------------------------------------------------------------------------
	// Question: I thought the based contructor was auto invoked but need to check ?
	//------------------------------------------------------------------------------

	CompaniesController()
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
		if (view) view->UpdateView(_companiesModel.getData());

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