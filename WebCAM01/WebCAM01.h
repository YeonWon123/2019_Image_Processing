
// WebCAM01.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CWebCAM01App:
// See WebCAM01.cpp for the implementation of this class
//

class CWebCAM01App : public CWinApp
{
public:
	CWebCAM01App();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CWebCAM01App theApp;