
// SecondSame.h : main header file for the SecondSame application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CSecondSameApp:
// See SecondSame.cpp for the implementation of this class
//

class CSecondSameApp : public CWinApp
{
public:
	CSecondSameApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP() // macros for window message handling
};

extern CSecondSameApp theApp;
