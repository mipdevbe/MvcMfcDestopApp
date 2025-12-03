
// MvcMfcDestopApp.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols
#include <memory>
#include "Controller.h"

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
    std::shared_ptr<Controller> GetController()
    {
        if (_controller != nullptr)
            return _controller;

        _controller = make_shared<Controller>();
        return _controller;
    }

// Implementation


	DECLARE_MESSAGE_MAP()

private:
    shared_ptr<Controller> _controller{ nullptr };
};

extern CMvcMfcDestopAppApp theApp;
