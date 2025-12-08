#pragma once
#include "../Controller/IControler.h"

class CompanyController : public IController
{
public:

	CompanyController()
	{
	}

	virtual ~CompanyController()
	{
	}

	bool Initialize() override
	{
		// Implementation of Initialize
		return true;
	}

	bool Load() override
	{
		// Implementation of Load
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

};