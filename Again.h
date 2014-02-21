#if !defined(AFX_AGAIN_H__DE832AA9_324F_4D0A_BA50_F70501FE508B__INCLUDED_)
#define AFX_AGAIN_H__DE832AA9_324F_4D0A_BA50_F70501FE508B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Again.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CAgain dialog

class CAgain : public CDialog
{
// Construction
public:
	CAgain(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CAgain)
	enum { IDD = IDD_DIALOG2 };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAgain)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAgain)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_AGAIN_H__DE832AA9_324F_4D0A_BA50_F70501FE508B__INCLUDED_)
