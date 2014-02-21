// Winmethod.cpp: implementation of the CWinmethod class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "bm.h"
#include "Winmethod.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWinmethod::CWinmethod()
{
for(int i = 0;i<5;i++)
	for(int j = 0;j < 2;j++)
		pos[i][j]=0;
}

CWinmethod::~CWinmethod()
{

}
