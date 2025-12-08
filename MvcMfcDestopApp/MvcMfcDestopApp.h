
// MvcMfcDestopApp.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include <memory>
#include ".\Controller\Controllers.h"

// CMvcMfcDestopAppApp:
// See MvcMfcDestopApp.cpp for the implementation of this class
//

using namespace std;

class CMvcMfcDestopAppApp : public CWinApp
{
public:
	CMvcMfcDestopAppApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Features
// 
    template <typename C>
    const Controllers& Controller() const {
		return _controllers.Controller<C>();
    }

// Implementation

	DECLARE_MESSAGE_MAP()

private:
    Controllers _controllers;
};

extern CMvcMfcDestopAppApp theApp;
