// bm.h : main header file for the BM application
//

#if !defined(AFX_BM_H__825ABA71_54E4_48A6_B93C_DE165FB349C0__INCLUDED_)
#define AFX_BM_H__825ABA71_54E4_48A6_B93C_DE165FB349C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CBmApp:
// See bm.cpp for the implementation of this class
//

class CBmApp : public CWinApp
{
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CBmApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBmApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CBmApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BM_H__825ABA71_54E4_48A6_B93C_DE165FB349C0__INCLUDED_)
