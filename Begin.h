#if !defined(AFX_BEGIN_H__5D03A424_C863_4FBD_9691_96C618AF184A__INCLUDED_)
#define AFX_BEGIN_H__5D03A424_C863_4FBD_9691_96C618AF184A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Begin.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBegin dialog

class CBegin : public CDialog
{
// Construction
public:
	bool time_mode;
	bool attack_mode;
	BOOL player_first;
	CBegin(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBegin)
	enum { IDD = IDD_DIALOG1 };
	CButton	m_check1;
	CSliderCtrl	m_slider;
	int		m_hanglie;
	int		m_choice;
	int		m_attack;
	int		m_timer;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBegin)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBegin)
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	afx_msg void OnRadio3();
	afx_msg void OnRadio4();
	virtual BOOL OnInitDialog();
	afx_msg void OnCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCheck1();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BEGIN_H__5D03A424_C863_4FBD_9691_96C618AF184A__INCLUDED_)
