// Again.cpp : implementation file
//

#include "stdafx.h"
#include "bm.h"
#include "Again.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAgain dialog


CAgain::CAgain(CWnd* pParent /*=NULL*/)
	: CDialog(CAgain::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAgain)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CAgain::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAgain)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAgain, CDialog)
	//{{AFX_MSG_MAP(CAgain)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAgain message handlers
