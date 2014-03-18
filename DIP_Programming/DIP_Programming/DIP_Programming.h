
// DIP_Programming.h : main header file for the DIP_Programming application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CDIP_ProgrammingApp:
// See DIP_Programming.cpp for the implementation of this class
//

class CDIP_ProgrammingApp : public CWinAppEx
{
public:
	CDIP_ProgrammingApp();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CDIP_ProgrammingApp theApp;
