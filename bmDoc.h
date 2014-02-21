// bmDoc.h : interface of the CBmDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BMDOC_H__95ECA9CF_AA32_4359_87F8_9F18693223CA__INCLUDED_)
#define AFX_BMDOC_H__95ECA9CF_AA32_4359_87F8_9F18693223CA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CBmDoc : public CDocument
{
protected: // create from serialization only
	CBmDoc();
	DECLARE_DYNCREATE(CBmDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBmDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBmDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBmDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BMDOC_H__95ECA9CF_AA32_4359_87F8_9F18693223CA__INCLUDED_)
