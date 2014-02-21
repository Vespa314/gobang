// Begin.cpp : implementation file
//

#include "stdafx.h"
#include "bm.h"
#include "Begin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBegin dialog


CBegin::CBegin(CWnd* pParent /*=NULL*/)
	: CDialog(CBegin::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBegin)
	m_hanglie = 19;
	m_choice = -1;
	m_attack = -1;
	m_timer = 0;
	//}}AFX_DATA_INIT
	player_first = false;
	m_choice = 1;
	m_attack = 0;
	attack_mode = true;
	time_mode = false;
	/*if(time_mode)
		MessageBox("yes");
	else
	MessageBox("no");*/
}


void CBegin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBegin)
	DDX_Control(pDX, IDC_CHECK1, m_check1);
	DDX_Control(pDX, IDC_SLIDER1, m_slider);
	DDX_Text(pDX, IDC_EDIT1, m_hanglie);
	DDX_Radio(pDX, IDC_RADIO1, m_choice);
	DDX_Radio(pDX, IDC_RADIO3, m_attack);
	DDX_Text(pDX, IDC_EDIT2, m_timer);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBegin, CDialog)
	//{{AFX_MSG_MAP(CBegin)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, OnCustomdrawSlider1)
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBegin message handlers

void CBegin::OnRadio1() 
{
	// TODO: Add your control notification handler code here
	player_first = true;
}

void CBegin::OnRadio2() 
{
	// TODO: Add your control notification handler code here
	player_first = false;
}

//DEL void CBegin::OnRegrret() 
//DEL {
//DEL 	// TODO: Add your command handler code here
//DEL 	
//DEL }

void CBegin::OnRadio3() 
{
	// TODO: Add your control notification handler code here
	attack_mode = true;
}

void CBegin::OnRadio4() 
{
	// TODO: Add your control notification handler code here
	attack_mode = false;
}

BOOL CBegin::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_slider.SetRangeMin(3,false);
	m_slider.SetRangeMax(120,false);
	m_slider.SetPos(30);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CBegin::OnCustomdrawSlider1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	m_timer = m_slider.GetPos();
	UpdateData(false);
	*pResult = 0;
}

//DEL void CBegin::OnTimemode() 
//DEL {
//DEL 	// TODO: Add your command handler code here
//DEL 	/*time_mode = !time_mode;
//DEL 	if(time_mode)
//DEL 		MessageBox("yes");
//DEL 	else
//DEL 	MessageBox("no");*/
//DEL }

void CBegin::OnCheck1() 
{
	// TODO: Add your control notification handler code here
	time_mode = m_check1.GetCheck();
	/*if(time_mode)
		MessageBox("yes");
	else
	MessageBox("no");*/
}

void CBegin::OnOK() 
{
	// TODO: Add extra validation here
	time_mode = m_check1.GetCheck();
	if(m_hanglie >19) 
	{
	m_hanglie = 19;
	MessageBox("您输入的行列数大于19了!!");
	}
	CDialog::OnOK();
}
