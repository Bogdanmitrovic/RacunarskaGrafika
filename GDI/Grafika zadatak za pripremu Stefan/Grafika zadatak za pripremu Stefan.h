
// Grafika zadatak za pripremu Stefan.h : main header file for the Grafika zadatak za pripremu Stefan application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CGrafikazadatakzapripremuStefanApp:
// See Grafika zadatak za pripremu Stefan.cpp for the implementation of this class
//

class CGrafikazadatakzapripremuStefanApp : public CWinAppEx
{
public:
	CGrafikazadatakzapripremuStefanApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CGrafikazadatakzapripremuStefanApp theApp;
