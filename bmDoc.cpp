// bmDoc.cpp : implementation of the CBmDoc class
//

#include "stdafx.h"
#include "bm.h"

#include "bmDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBmDoc

IMPLEMENT_DYNCREATE(CBmDoc, CDocument)

BEGIN_MESSAGE_MAP(CBmDoc, CDocument)
	//{{AFX_MSG_MAP(CBmDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBmDoc construction/destruction

CBmDoc::CBmDoc()
{
	// TODO: add one-time construction code here

}

CBmDoc::~CBmDoc()
{
}

BOOL CBmDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CBmDoc serialization

void CBmDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CBmDoc diagnostics

#ifdef _DEBUG
void CBmDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBmDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBmDoc commands
