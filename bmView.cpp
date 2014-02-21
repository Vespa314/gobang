// bmView.cpp : implementation of the CBmView class
//

#include "stdafx.h"
#include "bm.h"
#include "MainFrm.h"
#include "bmDoc.h"
#include "bmView.h"
#include "Winmethod.h"
#include "Begin.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBmView

IMPLEMENT_DYNCREATE(CBmView, CView)

BEGIN_MESSAGE_MAP(CBmView, CView)
	//{{AFX_MSG_MAP(CBmView)
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(DC_BEGINGAME, OnBegingame)
	ON_WM_MOUSEMOVE()
	ON_COMMAND(IDC_REGRRET, OnRegrret)
	ON_UPDATE_COMMAND_UI(IDC_REGRRET, OnUpdateRegrret)
	ON_COMMAND(IDC_DAPU, OnDapu)
	ON_UPDATE_COMMAND_UI(IDC_DAPU, OnUpdateDapu)
	ON_COMMAND(IDC_TIMEMODE, OnTimemode)
	ON_UPDATE_COMMAND_UI(IDC_TIMEMODE, OnUpdateTimemode)
	ON_WM_TIMER()
	ON_COMMAND(IDC_zhizhao, Onzhizhao)
	ON_UPDATE_COMMAND_UI(IDC_zhizhao, OnUpdatezhizhao)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBmView construction/destruction

CBmView::CBmView()
{
	// TODO: add construction code here
//	turn = false;
	jiange = 30;
	player_first = false;
	game_begin = false;
	game_finish = 0;
	ChessOrderCounter = 0;
	dapu = false;
	for(int i =0;i < 5;i++)
		win_step[i][0] = win_step[i][1] = 0;
	attackmode = true;
}

CBmView::~CBmView()
{
}

BOOL CBmView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CBmView drawing

void CBmView::OnDraw(CDC* pDC)
{
	CBmDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	CDC mdc1,mdc2;
	mdc1.CreateCompatibleDC(pDC);
	mdc2.CreateCompatibleDC(pDC);
	CBitmap bitmap1,bitmap2;
	bitmap1.LoadBitmap(IDB_BITMAP1);
	mdc1.SelectObject(bitmap1);
	bitmap2.LoadBitmap(IDB_BITMAP2);
	mdc2.SelectObject(bitmap2);
	if(game_begin)
	{
	char c[2];
	CString str;
	CSize size;
	//画棋盘
	for(int i = 0;i<begin_dial.m_hanglie;i++)
		{
		pDC->MoveTo(100,i*jiange+100);
		pDC->LineTo((begin_dial.m_hanglie-1)*jiange+100,i*jiange+100);
		pDC->MoveTo(i*jiange+100,100);
		pDC->LineTo(i*jiange+100,(begin_dial.m_hanglie-1)*jiange+100);
		itoa(i+1,c,10);
		str = c;
		size = pDC->GetTextExtent(str);
		pDC->TextOut(100-size.cx-jiange/2,100+i*jiange-size.cy/2,str);
		str = 'A'+i;
		size = pDC->GetTextExtent(str);
		pDC->TextOut(100+i*jiange-size.cx/2,100+jiange*(begin_dial.m_hanglie)-jiange/2,str);
		}

	//画棋子
	int x1,y1;
	for(i = 0;i <= ChessOrderCounter && ChessOrder[i].x != 0 && ChessOrder[i].y != 0;i++)
		{	
			x1 = (ChessOrder[i].x - 1)*jiange + 100 - jiange/2;
			y1 = (ChessOrder[i].y - 1)*jiange + 100 - jiange/2;
			if(!(i%2))
			pDC->BitBlt(x1,y1,x1+jiange,y1+jiange,&mdc1,0,0,SRCCOPY);
			else
			pDC->BitBlt(x1,y1,x1+jiange,y1+jiange,&mdc2,0,0,SRCCOPY);
		}
	
	//为最后一个走的棋子做标记
	x1 +=jiange/2;
	y1+=jiange/2;
	CPen pen(PS_SOLID,1,RGB(255,0,0));
	CPen *oldpen = pDC->SelectObject(&pen);
	pDC->MoveTo(x1 - jiange/4,y1 - jiange/4);
	pDC->LineTo(x1 - jiange/4,y1 + jiange/4);
	pDC->MoveTo(x1 - jiange/4,y1 + jiange/4);
	pDC->LineTo(x1 + jiange/4,y1 + jiange/4);

	pDC->MoveTo(x1 + jiange/4,y1 + jiange/4);
	pDC->LineTo(x1 + jiange/4,y1 - jiange/4);
	pDC->MoveTo(x1 + jiange/4,y1 - jiange/4);
	pDC->LineTo(x1 - jiange/4,y1 - jiange/4);

	pDC->SelectObject(oldpen);

	
	//若有人胜出，连成5子的棋子标出
	if(game_finish == 1)
		{	
		CDC mdc3;
		mdc3.CreateCompatibleDC(pDC);
		CBitmap bitmap3;
		bitmap3.LoadBitmap(IDB_BITMAP3);
		mdc3.SelectObject(bitmap3);
		for(int i = 0;i < 5;i++)
			{
			int xx = (win_step[i][0]-1)*jiange+100-jiange/2;
			int yy = (win_step[i][1]-1)*jiange+100-jiange/2; 
			pDC->BitBlt(yy,xx,yy+jiange,xx+jiange,&mdc3,0,0,SRCCOPY);
			}
		game_finish = 2;
		}
	}

	//dapu
	if(dapu)
	{
	int x1,y1;
	char num[3];
	CString strnum;
	CSize size;
	for(int i = 0;i <= ChessOrderCounter && ChessOrder[i].x != 0 && ChessOrder[i].y != 0;i++)
		{	
			itoa(i+1,num,10);
			strnum = num;
			size = pDC->GetTextExtent(strnum);
			x1 = (ChessOrder[i].x - 1)*jiange + 100 - size.cx / 2;
			y1 = (ChessOrder[i].y - 1)*jiange + 100 - size.cy / 2;
			pDC->TextOut(x1,y1,strnum);
		}
	}

	if(tip.x != 0)
	{
	int x1 = jiange*(tip.x - 1)+100;
	int y1 = jiange*(tip.y - 1)+100;
	CPen pen(PS_SOLID,1,RGB(0,255,0));
	CPen *oldpen = pDC->SelectObject(&pen);
	pDC->MoveTo(x1 - jiange/4,y1 - jiange/4);
	pDC->LineTo(x1 - jiange/4,y1 + jiange/4);
	pDC->MoveTo(x1 - jiange/4,y1 + jiange/4);
	pDC->LineTo(x1 + jiange/4,y1 + jiange/4);

	pDC->MoveTo(x1 + jiange/4,y1 + jiange/4);
	pDC->LineTo(x1 + jiange/4,y1 - jiange/4);
	pDC->MoveTo(x1 + jiange/4,y1 - jiange/4);
	pDC->LineTo(x1 - jiange/4,y1 - jiange/4);

	pDC->SelectObject(oldpen);
	tip.x = tip.y = 0;
	}
}

/////////////////////////////////////////////////////////////////////////////
// CBmView printing

BOOL CBmView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CBmView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CBmView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CBmView diagnostics

#ifdef _DEBUG
void CBmView::AssertValid() const
{
	CView::AssertValid();
}

void CBmView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBmDoc* CBmView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBmDoc)));
	return (CBmDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBmView message handlers

void CBmView::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
int legel = 0;
	if(point.x >= 75 && point.y >= 75 &&//鼠标位置有效
			point.x <= (begin_dial.m_hanglie-1)*jiange+100 &&
				point.y <= (begin_dial.m_hanglie-1)*jiange+100 
				&& game_begin && game_finish == 0)
	{
//	CClientDC dc(this);
//	CDC mdc;
//	mdc.CreateCompatibleDC(&dc);
//	CBitmap bitmap;
//	bitmap.LoadBitmap(IDB_BITMAP1);
//	mdc.SelectObject(bitmap);
//	dc.SelectStockObject(NULL_BRUSH);
	//CBrush brush(&bitmap);
//	int x1 = int((point.x+jiange/2-100)/jiange) * jiange +100 - jiange/2;
//	int y1 = int((point.y+jiange/2-100)/jiange) * jiange +100 - jiange/2;
//	dc.BitBlt(x1,y1,x1+jiange,y1+jiange,&mdc,0,0,SRCCOPY);
	//若该地方没下过，则下该处	
	int x1 = (point.x+jiange/2-100)/jiange+1;
	int y1 = (point.y+jiange/2-100)/jiange+1;
	if(Chessboard[y1-1][x1-1] == 0)
		{
		if(begin_dial.time_mode)	
		KillTimer(1);
		timer_counter = 0;
		
		legel = 1;
		ChessOrder[ChessOrderCounter].x = x1;
		ChessOrder[ChessOrderCounter].y = y1;
		Chessboard[y1 - 1][x1 - 1] = 1;
		ChessOrderCounter++;
		Invalidate();
	//	CString str = "";
	//	str.Format("%d,%d",y1,x1);
	//	MessageBox(str);
		UpdateLeft(y1,x1,0);
		}
	
	}

	if(game_finish != 2)
	{
	//计算机决策
	if(legel == 1)
	{
		//判断计算机有无连四冲五
	int i_temp = -1,j_temp = -1;
	int i_temp33 = -1,j_temp33 = -1;
	int best_score = 0;
	for(int dd = 0;dd < (4*begin_dial.m_hanglie-8)*(begin_dial.m_hanglie-4);dd++)
	{
	if(computer_left[dd] == 1)
		{
		for(int i = 0;i < 5;i++)
			{
			if(Chessboard[winmethod[dd].pos[i][0]-1][winmethod[dd].pos[i][1]-1] == 0)
				{
				i_temp = winmethod[dd].pos[i][0]-1;
				j_temp = winmethod[dd].pos[i][1]-1;
				}
			}
		}
	}
	//判断玩家有无连四冲五
	if(i_temp == -1)
	for(int dd = 0;dd < (4*begin_dial.m_hanglie-8)*(begin_dial.m_hanglie-4);dd++)
	{
	if(player_left[dd] == 1)
		{
		for(int i = 0;i < 5;i++)
			{
			if(Chessboard[winmethod[dd].pos[i][0]-1][winmethod[dd].pos[i][1]-1] == 0)
				{
				i_temp = winmethod[dd].pos[i][0]-1;
				j_temp = winmethod[dd].pos[i][1]-1;
				}
			}
		}
	}
	//扫描全盘，计算各个方向计算机子的个数
	 if(i_temp == -1)
		{
		 bool have33 = false;
	for(int aa = 0;aa<begin_dial.m_hanglie;aa++)
		for(int bb =0;bb < begin_dial.m_hanglie;bb++)
			if(Chessboard[aa][bb] == 0)
			{
			int sum[8] ={0,0,0,0,0,0,0,0}; 
			int end[8] ={-2,-2,-2,-2,-2,-2,-2,-2};  
			for(int dr = 1;dr+bb < begin_dial.m_hanglie && Chessboard[aa][dr+bb] == -1;dr++)
					sum[0]++;//右
					if(bb+dr < begin_dial.m_hanglie)
					end[0] = Chessboard[aa][dr+bb];
			for(dr = 1;bb-dr >=0 && Chessboard[aa][bb-dr] == -1;dr++)
					sum[1]++;//左
					if(bb-dr >=0)
					end[1] = Chessboard[aa][bb-dr];
			for(dr = 1;dr+aa < begin_dial.m_hanglie && Chessboard[aa+dr][bb] == -1;dr++)
					sum[2]++;//下
					if(aa+dr < begin_dial.m_hanglie)
					end[2] = Chessboard[aa+dr][bb];
			for(dr = 1;aa-dr >=0 && Chessboard[aa-dr][bb] == -1;dr++)
					sum[3]++;//上
					if(aa-dr>=0)
					end[3] = Chessboard[aa-dr][bb];
			for(dr = 1;bb-dr >=0 && aa - dr >=0 && Chessboard[aa-dr][bb-dr] == -1;dr++)
					sum[4]++;//左上
					if(aa-dr>=0&&bb-dr>=0)
					end[4] = Chessboard[aa-dr][bb-dr];
			for(dr = 1;bb+dr < begin_dial.m_hanglie && aa+dr < begin_dial.m_hanglie && Chessboard[aa+dr][bb+dr] == -1;dr++)
					sum[5]++;//右下
					if(aa+dr< begin_dial.m_hanglie && bb+dr< begin_dial.m_hanglie)
					end[5] = Chessboard[aa+dr][bb+dr];
			for(dr = 1;dr+aa < begin_dial.m_hanglie && bb-dr >= 0 && Chessboard[aa+dr][bb-dr] == -1;dr++)
					sum[6]++;//左下
					if(aa+dr< begin_dial.m_hanglie&&bb-dr >=0)
					end[6] = Chessboard[aa+dr][bb-dr] ;
			for(dr = 1;aa-dr >=0 && bb + dr < begin_dial.m_hanglie && Chessboard[aa-dr][bb+dr] == -1;dr++)
					sum[7]++;//右上
					if(aa-dr >=0&& bb+dr <begin_dial.m_hanglie)
					end[7] = Chessboard[aa-dr][bb+dr];			
			int win_33 = 0;
			//判断计算机有误空头三
			for(int cc = 0;cc < 8;cc++)
			{
			if(sum[cc] >=3 && end[cc] == 0 )
				{
				i_temp = aa;
				j_temp = bb;
				}
			//判断计算机有无创造33，34棋型可能
			if(sum[cc] >=2 && end[cc] == 0)
				win_33++;
			}
			if(win_33 >1 && i_temp == -1)
				{
				i_temp33 = aa;
				j_temp33 = bb;
				have33 =true;
				}
			//判断有无两头可以冲
			if(i_temp == -1 && !have33)
			{
			for(int cc = 0;cc < 4;cc++)
			{
				if(sum[cc*2] + sum[cc*2+1] >=3 && (end[cc*2]==0 && end[cc*2+1]==0) && attackmode)
				{
				i_temp = aa;
				j_temp = bb;
				}
				else if(sum[cc*2] + sum[cc*2+1] >=3 && (end[cc*2]==0 || end[cc*2+1]==0) && !attackmode)
				{
				i_temp = aa;
				j_temp = bb;
				}

			}
			}

			}
		}
//扫描全盘，计算各个方向玩家子的个数
 if(i_temp == -1)
		{
	 bool have33 = false;
	for(int aa = 0;aa<begin_dial.m_hanglie;aa++)
		for(int bb =0;bb < begin_dial.m_hanglie;bb++)
			if(Chessboard[aa][bb] == 0)
			{
			int sum[8] ={0,0,0,0,0,0,0,0}; 
			int end[8] ={-2,-2,-2,-2,-2,-2,-2,-2};  
			for(int dr = 1;dr+bb < begin_dial.m_hanglie && Chessboard[aa][dr+bb] == 1;dr++)
					sum[0]++;//右
					if(bb+dr < begin_dial.m_hanglie)
					end[0] = Chessboard[aa][dr+bb];
			for(dr = 1;bb-dr >=0 && Chessboard[aa][bb-dr] == 1;dr++)
					sum[1]++;//左
					if(bb-dr >=0)
					end[1] = Chessboard[aa][bb-dr];
			for(dr = 1;dr+aa < begin_dial.m_hanglie && Chessboard[aa+dr][bb] == 1;dr++)
					sum[2]++;//下
					if(aa+dr < begin_dial.m_hanglie)
					end[2] = Chessboard[aa+dr][bb];
			for(dr = 1;aa-dr >=0 && Chessboard[aa-dr][bb] == 1;dr++)
					sum[3]++;//上
					if(aa-dr>=0)
					end[3] = Chessboard[aa-dr][bb];
			for(dr = 1;bb-dr >=0 && aa - dr >=0 && Chessboard[aa-dr][bb-dr] == 1;dr++)
					sum[4]++;//左上
					if(aa-dr>=0&&bb-dr>=0)
					end[4] = Chessboard[aa-dr][bb-dr];
			for(dr = 1;bb+dr < begin_dial.m_hanglie && aa+dr < begin_dial.m_hanglie && Chessboard[aa+dr][bb+dr] == 1;dr++)
					sum[5]++;//右下
					if(aa+dr< begin_dial.m_hanglie && bb+dr< begin_dial.m_hanglie)
					end[5] = Chessboard[aa+dr][bb+dr];
			for(dr = 1;dr+aa < begin_dial.m_hanglie && bb-dr >= 0 && Chessboard[aa+dr][bb-dr] == 1;dr++)
					sum[6]++;//左下
					if(aa+dr< begin_dial.m_hanglie&&bb-dr >=0)
					end[6] = Chessboard[aa+dr][bb-dr] ;
			for(dr = 1;aa-dr >=0 && bb + dr < begin_dial.m_hanglie && Chessboard[aa-dr][bb+dr] == 1;dr++)
					sum[7]++;//右上
					if(aa-dr >=0&& bb+dr <begin_dial.m_hanglie)
					end[7] = Chessboard[aa-dr][bb+dr];	
					int win33 = 0;
			for(int cc = 0;cc < 8;cc++)
			{
			if(sum[cc] >=3 && end[cc] == 0)
				{
				i_temp = aa;
				j_temp = bb;
				}
			if(sum[cc] >=2 && end[cc] == 0)
				win33++;
			}
			if(i_temp == -1 && i_temp33 != -1)
				{
				i_temp = i_temp33;
				j_temp = j_temp33;
				}
			if(win33 > 1 && i_temp == -1)
			{
			i_temp = aa;
			j_temp = bb;
			have33 = true;
			}
			if(i_temp == -1 && !have33)
			{
			for(int cc = 0;cc < 4;cc++)
			{
			if(sum[cc*2] + sum[cc*2+1] >=3 && (end[cc*2]==0 && end[cc*2+1]==0) && attackmode)
				{
				i_temp = aa;
				j_temp = bb;
				}
				else if(sum[cc*2] + sum[cc*2+1] >=3 && (end[cc*2]==0 || end[cc*2+1]==0) && !attackmode)
				{
				i_temp = aa;
				j_temp = bb;
				}
			}
			}

			}
		}
		//研究绝对防御。。。这一段可以注释掉
	/*if(i_temp == -1)
	{
	for(int aa = 3;aa<begin_dial.m_hanglie-3;aa++)
		for(int bb =3;bb < begin_dial.m_hanglie-3;bb++)
		{
			if(Chessboard[aa][bb] == 0)
		if((Chessboard[aa-1][bb-2] == 1 && Chessboard[aa-3][bb-1] == 1 && Chessboard[aa-2][bb+1] == 1)||
			(Chessboard[aa-2][bb+1] == 1 && Chessboard[aa-1][bb+3] == 1 && Chessboard[aa+1][bb+2] == 1)||
			(Chessboard[aa-1][bb-2] == 1 && Chessboard[aa+1][bb-3] == 1 && Chessboard[aa+2][bb-1] == 1)||
			(Chessboard[aa+1][bb+2] == 1 && Chessboard[aa+3][bb+1] == 1 && Chessboard[aa+2][bb-1] == 1)||
			(Chessboard[aa+1][bb-2] == 1 && Chessboard[aa-1][bb-3] == 1 && Chessboard[aa-2][bb-1] == 1)||
			(Chessboard[aa-1][bb+2] == 1 && Chessboard[aa-3][bb+1] == 1 && Chessboard[aa-2][bb-1] == 1)||
			(Chessboard[aa+2][bb+1] == 1 && Chessboard[aa-1][bb+2] == 1 && Chessboard[aa+1][bb+3] == 1)||
			(Chessboard[aa-1][bb-2] == 1 && Chessboard[aa+1][bb-2] == 1 && Chessboard[aa+3][bb+1] == 1))
			{
			i_temp = aa;
			j_temp = bb;
			}			
		}
	}
*/
	//若无以上情形，计算计算机各点分数
	
	if(i_temp == -1)
	{
		//MessageBox("这有可能是无理手。。。。");
	for(int i = 0;i < begin_dial.m_hanglie;i++)
		for(int j = 0;j < begin_dial.m_hanglie;j++)
		{
		if(Chessboard[i][j] == 0)
		{
			score[i][j] = 0;
		for(int k = 0;k < (4*begin_dial.m_hanglie-8)*(begin_dial.m_hanglie-4);k++)
			{
			for(int l = 0;l < 5;l++)
				{
				if(i + 1 == winmethod[k].pos[l][0] && j + 1 == winmethod[k].pos[l][1] && computer_left[k] <5)
					score[i][j] += (5-computer_left[k]);//有权相加，若为无权，改为score[i][j] ++;
				}
			}
		if(score[i][j] > best_score)
			{
			best_score = score[i][j];
			i_temp = i;
			j_temp = j;
			}
		}
		}

	


	//计算玩家各点分数
	for(i = 0;i < begin_dial.m_hanglie;i++)
		for(int j = 0;j < begin_dial.m_hanglie;j++)
		{
		if(Chessboard[i][j] == 0)
		{
			score[i][j] = 0;
		for(int k = 0;k < (4*begin_dial.m_hanglie-8)*(begin_dial.m_hanglie-4);k++)
			{
			for(int l = 0;l < 5;l++)
				{
				if(i + 1 == winmethod[k].pos[l][0] && j + 1 == winmethod[k].pos[l][1] && player_left[k] < 5)
					score[i][j] += (5 - player_left[k]);//有权相加，若为无权，改为score[i][j] ++;
				}
			}
		if(score[i][j] > best_score)
			{
			best_score = score[i][j];
			i_temp = i;
			j_temp = j;
			}
		}
		}
	}
	ChessOrder[ChessOrderCounter].x = j_temp+1;
	ChessOrder[ChessOrderCounter].y = i_temp+1;
	Chessboard[i_temp][j_temp] = -1;
	Invalidate();

	if(begin_dial.time_mode)
		{
		SetTimer(1,1000,NULL);
		}
//	CString str = "";
//	str.Format("%d,%d---%d",i_temp+1,j_temp+1,computer_left[339]);
//	MessageBox(str);
	ChessOrderCounter++;
	UpdateLeft(i_temp+1,j_temp+1,1);
	
	}
	}
	//dc.FillRect(CRect(point,p),&brush);
	CView::OnLButtonDown(nFlags, point);
}



//DEL void CBmView::OnPaint() 
//DEL {
//DEL 	CPaintDC dc(this); // device context for painting
//DEL 	// TODO: Add your message handler code here
//DEL 	
//DEL 	// Do not call CView::OnPaint() for painting messages
//DEL }

void CBmView::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	//下方状态框显示鼠标棋盘上的坐标
	CString str;
	str.Format("x = %d,y = %d ",//   %d",
		(point.x+jiange/2-100)/jiange+1,
		(point.y+jiange/2-100)/jiange+1);//,
	//	ChessOrderCounter);
	((CMainFrame*)GetParent())->m_wndStatusBar.SetWindowText(str);
	CView::OnMouseMove(nFlags, point);
}


void CBmView::OnBegingame() 
{
	// TODO: Add your command handler code here
	//CBegin begin;
	//if(Chessboard) delete []Chessboard;
	
	
	
	if(IDOK ==begin_dial.DoModal())
	{
	if(game_begin && game_finish == 0)
		{
		if( IDOK != again_dial.DoModal())
		return;
		}
	//信息初始化
	//jiange = 30;
	//player_first = false;
	game_begin = false;
	game_finish = 0;
	attackmode = begin_dial.attack_mode;
	time_limit = begin_dial.m_timer;
	timer_counter = 0;
	KillTimer(1);
	tip.x = tip.y = 0;
	//	dapu = false;
	ChessOrderCounter = 0;
	for(int iii =0;iii < 5;iii++)
		win_step[iii][0] = win_step[iii][1] = 0;

	Chessboard=new int*[begin_dial.m_hanglie];
	score=new int*[begin_dial.m_hanglie];
	//棋盘信息清空
	for(int l=0;l<begin_dial.m_hanglie;l++)
		{		
		Chessboard[l]=new int[begin_dial.m_hanglie];
		score[l]=new int[begin_dial.m_hanglie];
		for(int k=0;k<begin_dial.m_hanglie;k++)
			{
			Chessboard[l][k]=0;//0 没下  1玩家 -1 电脑
			score[l][k]=0;
			}
		}
	//Invalidate();
	//玩家，电脑胜法信息清空
	player_left = new int[(4*begin_dial.m_hanglie-8)*(begin_dial.m_hanglie-4)];
	computer_left = new int[(4*begin_dial.m_hanglie-8)*(begin_dial.m_hanglie-4)];
	for(int c = 0;c < (4*begin_dial.m_hanglie-8)*(begin_dial.m_hanglie-4);c++)
	{
	player_left[c] = 5;
	computer_left[c] = 5;
	}

	//对所有胜利方法进行排序
	winmethod = new CWinmethod[(4*begin_dial.m_hanglie-8)*(begin_dial.m_hanglie-4)];
	int counter = 0;
	//“/”方向，上到下，左到右（上半部）
	for(int i = 5;i <= begin_dial.m_hanglie;i++)
	{
	int j = 0;
	while((i - j) - 5 >= 0)
		{
		//	CString str = "";
		for(int k = 0;k < 5;k++)
			{
			winmethod[counter].pos[k][0] = i - j - k;//纵坐标
			winmethod[counter].pos[k][1] = j + k + 1;//横坐标
		//	str.Format(str + "(%d,%d)",winmethod[counter].pos[k][0],winmethod[counter].pos[k][1]);
			}
	//	MessageBox(str);
		counter++;
		j++;
		}
	}
	//“/”方向，上到下，左到右（下半部）
	for(i = 2;i <=begin_dial.m_hanglie - 4;i++)
	{
	int j = 0;
	while(i + j + 5 <= begin_dial.m_hanglie + 1)
		{
		//	CString str = "";
		for(int k = 0;k < 5;k++)
			{
			winmethod[counter].pos[k][0] = begin_dial.m_hanglie - j - k;
			winmethod[counter].pos[k][1] = i + j + k;
		//	str.Format(str + "(%d,%d)",winmethod[counter].pos[k][0],winmethod[counter].pos[k][1]);
			}
		//MessageBox(str);
		counter++;
		j++;
		}
	}
	//“\”方向，下到上，左到右（下半部）
	for(i = begin_dial.m_hanglie -4;i >= 1;i--)
	{
	int j = 0;
	while(i + j + 5 <= begin_dial.m_hanglie + 1)
		{
		//	CString str = "";
		for(int k = 0;k < 5;k++)
			{
			winmethod[counter].pos[k][0] = i + j + k;
			winmethod[counter].pos[k][1] = k + j + 1;
		//	str.Format(str + "(%d,%d)",winmethod[counter].pos[k][0],winmethod[counter].pos[k][1]);
			}
		//MessageBox(str);
		counter++;
		j++;
		}
	}
	//“\”方向，下到上，上到下（上半部）
	for(i = 2;i <= begin_dial.m_hanglie - 4;i++)
	{
	int j = 0;
	while(i + j + 5 <= begin_dial.m_hanglie + 1)
		{
		//	CString str = "";
		for(int k = 0;k < 5;k++)
			{
			winmethod[counter].pos[k][0] = j + k + 1;
			winmethod[counter].pos[k][1] = k + j + i;
	//		str.Format(str + "(%d,%d)",winmethod[counter].pos[k][0],winmethod[counter].pos[k][1]);
			}
	//	MessageBox(str);
		counter++;
		j++;
		}
	}
	//"-"方向 上到下，左到右
	for(i = 1;i <= begin_dial.m_hanglie;i++)
	{
	int j = 0;
	while(j + 5 <= begin_dial.m_hanglie)
		{
		//	CString str = "";
		for(int k = 0;k < 5;k++)
			{
			winmethod[counter].pos[k][0] = i;
			winmethod[counter].pos[k][1] = j + k + 1;
		//	str.Format(str + "(%d,%d)",winmethod[counter].pos[k][0],winmethod[counter].pos[k][1]);
			}
	//	MessageBox(str);
		counter++;
		j++;
		}
	}
	//"|"方向，左到右，上到下
	for(i = 1;i <= begin_dial.m_hanglie;i++)
	{
	int j = 0;
	while(j + 5 <= begin_dial.m_hanglie)
		{
		//	CString str = "";
		for(int k = 0;k < 5;k++)
			{
			winmethod[counter].pos[k][0] = j + k + 1;
			winmethod[counter].pos[k][1] = i;
		//	str.Format(str + "(%d,%d)",winmethod[counter].pos[k][0],winmethod[counter].pos[k][1]);
			}
	//	MessageBox(str);
		counter++;
		j++;
		}
	}
	//char aaa[4];
	//itoa(counter,aaa,10);
	//MessageBox(aaa);
	
	ChessOrder = new CPoint[begin_dial.m_hanglie * begin_dial.m_hanglie];
	for(i = 0;i < begin_dial.m_hanglie * begin_dial.m_hanglie;i++)
		ChessOrder[i].x = ChessOrder[i].y = 0;
	//if(begin_dial.player_first)
	//MessageBox("player first");
	//	else
	//MessageBox("pc first");
	player_first = begin_dial.player_first;
	//入电脑先下，第一步下中间
	if(!player_first)
	{
		ChessOrder[ChessOrderCounter].x = (begin_dial.m_hanglie + 1) / 2;
		ChessOrder[ChessOrderCounter].y = (begin_dial.m_hanglie + 1) / 2;
		Chessboard[ChessOrder[ChessOrderCounter].x-1][ChessOrder[ChessOrderCounter].y-1] = -1;

		UpdateLeft(ChessOrder[ChessOrderCounter].x,ChessOrder[ChessOrderCounter].y,1);
		ChessOrderCounter++;
	}
	game_begin = true;
		Invalidate();
		if(begin_dial.time_mode)
		{
		SetTimer(1,1000,NULL);
		}
	//CString sss="";
//	for(int df =0;df < 5;df++)
//	/	sss.Format(sss+"(%d,%d)",winmethod[339].pos[df][0],winmethod[339].pos[df][1]);
	//	sss.Format(sss+"(%d,%d)",winmethod[339].pos[df][0],winmethod[339].pos[df][1]);
//	MessageBox(sss);
		}
		/*if(begin_dial.time_mode)
		MessageBox("yes");
	else
	MessageBox("no");*/
}

int CBmView::UpdateLeft(int x,int y,bool computer)
{
for(int i = 0;i < (4*begin_dial.m_hanglie-8)*(begin_dial.m_hanglie-4);i++)
	{
	for(int j =0 ;j < 5;j++)
		{
		if((winmethod[i].pos[j][0] == x && winmethod[i].pos[j][1] == y) )
		
			{
			if(computer)
				{
				if(computer_left[i] != 6)
					{
					computer_left[i]--;
					if(computer_left[i] == 0)
					{
						for(int f =0;f < 5;f++)
						{
							win_step[f][0] = winmethod[i].pos[f][0];
							win_step[f][1] = winmethod[i].pos[f][1];
						}
						game_finish=1;
						MessageBox("计算机胜出了!!");
						return 1;
					}
					}
					player_left[i] = 6;
				}
			else
				{
				if(player_left[i] != 6)
					{
					player_left[i]--;
					if(player_left[i] == 0)
						{
					
						for(int f =0;f < 5;f++)
						{
							win_step[f][0] = winmethod[i].pos[f][0];
							win_step[f][1] = winmethod[i].pos[f][1];
						}
						game_finish = 1;
						MessageBox("恭喜你胜出了!!");
						return 1;
						}
					}
				computer_left[i] = 6;
				}
			}
		}
	}

return 0;
}

void CBmView::OnRegrret() 
{
	// TODO: Add your command handler code here
	if(game_finish == 2)
		game_finish = 0;
	ChessOrderCounter--;
	Chessboard[ChessOrder[ChessOrderCounter].y - 1][ChessOrder[ChessOrderCounter].x - 1] = 0;
	ChessOrder[ChessOrderCounter].x = 0;
	ChessOrder[ChessOrderCounter].y = 0;
	ChessOrderCounter--;
	Chessboard[ChessOrder[ChessOrderCounter].y - 1][ChessOrder[ChessOrderCounter].x - 1] = 0;
	ChessOrder[ChessOrderCounter].x = 0;
	ChessOrder[ChessOrderCounter].y = 0;
	
		for(int c = 0;c < (4*begin_dial.m_hanglie-8)*(begin_dial.m_hanglie-4);c++)
	{
	player_left[c] = 5;
	computer_left[c] = 5;
	}

	if(player_first)
	for(int i = 0;i < ChessOrderCounter;i++)
	{
	UpdateLeft(ChessOrder[i].y,ChessOrder[i].x,i%2);
	}
	else 
	for(int i = 0;i < ChessOrderCounter;i++)
	{
	UpdateLeft(ChessOrder[i].y,ChessOrder[i].x,(i+1)%2);
	}
	Invalidate();
}

void CBmView::OnUpdateRegrret(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	/*if(!game_begin)
	 pCmdUI->Enable(false);
	else
		pCmdUI->Enable(true);*/
	if(game_begin && (player_first && ChessOrderCounter>=2) || (!player_first && ChessOrderCounter>=3)/* && game_finish == 0*/)
		pCmdUI->Enable(true);
	else
		pCmdUI->Enable(false);
}

void CBmView::OnDapu() 
{
	// TODO: Add your command handler code here
	dapu = !dapu;
	Invalidate();
}

void CBmView::OnUpdateDapu(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(game_begin)
		pCmdUI->Enable(true);
	else
		pCmdUI->Enable(false);
	pCmdUI->SetCheck(dapu);
}

void CBmView::OnTimemode() 
{
	// TODO: Add your command handler code here
	begin_dial.time_mode = !begin_dial.time_mode;
	if(game_begin && !begin_dial.time_mode) KillTimer(1);
	Invalidate();
/*	if(	begin_dial.time_mode )
		MessageBox("yes");
	else
	MessageBox("no");*/
}

void CBmView::OnUpdateTimemode(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(game_begin && game_finish == 0)
		pCmdUI->Enable(true);
	else
		pCmdUI->Enable(false);
	pCmdUI->SetCheck(begin_dial.time_mode);
}

void CBmView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(nIDEvent == 1)
	{
	timer_counter++;
	if(timer_counter == time_limit + 1)
		{
		KillTimer(1);
		MessageBox("时间已到，你输了!!");
		game_finish = 1;
		}
	else 
		{
		CClientDC dc(this);
		CString str;
		str.Format("0%d:",(time_limit - timer_counter)/60);
		if((time_limit - timer_counter)%60<10)
			str+='0';
		str.Format("剩余时间:     "+str+"%d",(time_limit - timer_counter)%60);
	//	str = "剩余时间:" + str;
		CFont font;
		CFont *oldfont;
		font.CreatePointFont(300,"华文行楷",NULL);
		oldfont = dc.SelectObject(&font);
		//char t[3];
		//itoa(time_limit - timer_counter,t,10);
		//str += t;
		dc.TextOut(0,0,"                                         ");
		dc.TextOut(0,0,str);
		dc.SelectObject(oldfont);
		}
	
	}
	CView::OnTimer(nIDEvent);
}

void CBmView::Onzhizhao() 
{
	// TODO: Add your command handler code here
	if(player_first && ChessOrderCounter == 0)
		{
		tip.x = (begin_dial.m_hanglie + 1) / 2;
		tip.y = (begin_dial.m_hanglie + 1) / 2;
		Invalidate();
		return;
		}
	int **Chessboard_temp=new int*[begin_dial.m_hanglie];
	int **score_temp=new int*[begin_dial.m_hanglie];
	//棋盘信息清空
	for(int l=0;l<begin_dial.m_hanglie;l++)
		{		
		Chessboard_temp[l]=new int[begin_dial.m_hanglie];
		score_temp[l]=new int[begin_dial.m_hanglie];
		for(int k=0;k<begin_dial.m_hanglie;k++)
			{
			Chessboard_temp[l][k]=	Chessboard[l][k];//0 没下  1玩家 -1 电脑
			Chessboard[l][k] =-Chessboard[l][k];
			score_temp[l][k]=score[l][k];
			}
		}
	int *player_left_temp = new int[(4*begin_dial.m_hanglie-8)*(begin_dial.m_hanglie-4)];
	int *computer_left_temp = new int[(4*begin_dial.m_hanglie-8)*(begin_dial.m_hanglie-4)];
	for(int c = 0;c < (4*begin_dial.m_hanglie-8)*(begin_dial.m_hanglie-4);c++)
	{
	player_left_temp[c] = player_left[c];
	computer_left_temp[c] = computer_left[c];

	player_left[c] = computer_left_temp[c];
	computer_left[c] = player_left_temp[c];
	}


int i_temp = -1,j_temp = -1;
	int i_temp33 = -1,j_temp33 = -1;
	int best_score = 0;
	for(int dd = 0;dd < (4*begin_dial.m_hanglie-8)*(begin_dial.m_hanglie-4);dd++)
	{
	if(computer_left[dd] == 1)
		{
		for(int i = 0;i < 5;i++)
			{
			if(Chessboard[winmethod[dd].pos[i][0]-1][winmethod[dd].pos[i][1]-1] == 0)
				{
				i_temp = winmethod[dd].pos[i][0]-1;
				j_temp = winmethod[dd].pos[i][1]-1;
				}
			}
		}
	}
	//判断玩家有无连四冲五
	if(i_temp == -1)
	for(int dd = 0;dd < (4*begin_dial.m_hanglie-8)*(begin_dial.m_hanglie-4);dd++)
	{
	if(player_left[dd] == 1)
		{
		for(int i = 0;i < 5;i++)
			{
			if(Chessboard[winmethod[dd].pos[i][0]-1][winmethod[dd].pos[i][1]-1] == 0)
				{
				i_temp = winmethod[dd].pos[i][0]-1;
				j_temp = winmethod[dd].pos[i][1]-1;
				}
			}
		}
	}
	//扫描全盘，计算各个方向计算机子的个数
	 if(i_temp == -1)
		{
		 bool have33 = false;
	for(int aa = 0;aa<begin_dial.m_hanglie;aa++)
		for(int bb =0;bb < begin_dial.m_hanglie;bb++)
			if(Chessboard[aa][bb] == 0)
			{
			int sum[8] ={0,0,0,0,0,0,0,0}; 
			int end[8] ={-2,-2,-2,-2,-2,-2,-2,-2};  
			for(int dr = 1;dr+bb < begin_dial.m_hanglie && Chessboard[aa][dr+bb] == -1;dr++)
					sum[0]++;//右
					if(bb+dr < begin_dial.m_hanglie)
					end[0] = Chessboard[aa][dr+bb];
			for(dr = 1;bb-dr >=0 && Chessboard[aa][bb-dr] == -1;dr++)
					sum[1]++;//左
					if(bb-dr >=0)
					end[1] = Chessboard[aa][bb-dr];
			for(dr = 1;dr+aa < begin_dial.m_hanglie && Chessboard[aa+dr][bb] == -1;dr++)
					sum[2]++;//下
					if(aa+dr < begin_dial.m_hanglie)
					end[2] = Chessboard[aa+dr][bb];
			for(dr = 1;aa-dr >=0 && Chessboard[aa-dr][bb] == -1;dr++)
					sum[3]++;//上
					if(aa-dr>=0)
					end[3] = Chessboard[aa-dr][bb];
			for(dr = 1;bb-dr >=0 && aa - dr >=0 && Chessboard[aa-dr][bb-dr] == -1;dr++)
					sum[4]++;//左上
					if(aa-dr>=0&&bb-dr>=0)
					end[4] = Chessboard[aa-dr][bb-dr];
			for(dr = 1;bb+dr < begin_dial.m_hanglie && aa+dr < begin_dial.m_hanglie && Chessboard[aa+dr][bb+dr] == -1;dr++)
					sum[5]++;//右下
					if(aa+dr< begin_dial.m_hanglie && bb+dr< begin_dial.m_hanglie)
					end[5] = Chessboard[aa+dr][bb+dr];
			for(dr = 1;dr+aa < begin_dial.m_hanglie && bb-dr >= 0 && Chessboard[aa+dr][bb-dr] == -1;dr++)
					sum[6]++;//左下
					if(aa+dr< begin_dial.m_hanglie&&bb-dr >=0)
					end[6] = Chessboard[aa+dr][bb-dr] ;
			for(dr = 1;aa-dr >=0 && bb + dr < begin_dial.m_hanglie && Chessboard[aa-dr][bb+dr] == -1;dr++)
					sum[7]++;//右上
					if(aa-dr >=0&& bb+dr <begin_dial.m_hanglie)
					end[7] = Chessboard[aa-dr][bb+dr];			
			int win_33 = 0;
			//判断计算机有误空头三
			for(int cc = 0;cc < 8;cc++)
			{
			if(sum[cc] >=3 && end[cc] == 0 )
				{
				i_temp = aa;
				j_temp = bb;
				}
			//判断计算机有无创造33，34棋型可能
			if(sum[cc] >=2 && end[cc] == 0)
				win_33++;
			}
			if(win_33 >1 && i_temp == -1)
				{
				i_temp33 = aa;
				j_temp33 = bb;
				have33 =true;
				}
			//判断有无两头可以冲
			if(i_temp == -1 && !have33)
			{
			for(int cc = 0;cc < 4;cc++)
			{
				if(sum[cc*2] + sum[cc*2+1] >=3 && (end[cc*2]==0 && end[cc*2+1]==0) && attackmode)
				{
				i_temp = aa;
				j_temp = bb;
				}
				else if(sum[cc*2] + sum[cc*2+1] >=3 && (end[cc*2]==0 || end[cc*2+1]==0) && !attackmode)
				{
				i_temp = aa;
				j_temp = bb;
				}

			}
			}

			}
		}
//扫描全盘，计算各个方向玩家子的个数
 if(i_temp == -1)
		{
	 bool have33 = false;
	for(int aa = 0;aa<begin_dial.m_hanglie;aa++)
		for(int bb =0;bb < begin_dial.m_hanglie;bb++)
			if(Chessboard[aa][bb] == 0)
			{
			int sum[8] ={0,0,0,0,0,0,0,0}; 
			int end[8] ={-2,-2,-2,-2,-2,-2,-2,-2};  
			for(int dr = 1;dr+bb < begin_dial.m_hanglie && Chessboard[aa][dr+bb] == 1;dr++)
					sum[0]++;//右
					if(bb+dr < begin_dial.m_hanglie)
					end[0] = Chessboard[aa][dr+bb];
			for(dr = 1;bb-dr >=0 && Chessboard[aa][bb-dr] == 1;dr++)
					sum[1]++;//左
					if(bb-dr >=0)
					end[1] = Chessboard[aa][bb-dr];
			for(dr = 1;dr+aa < begin_dial.m_hanglie && Chessboard[aa+dr][bb] == 1;dr++)
					sum[2]++;//下
					if(aa+dr < begin_dial.m_hanglie)
					end[2] = Chessboard[aa+dr][bb];
			for(dr = 1;aa-dr >=0 && Chessboard[aa-dr][bb] == 1;dr++)
					sum[3]++;//上
					if(aa-dr>=0)
					end[3] = Chessboard[aa-dr][bb];
			for(dr = 1;bb-dr >=0 && aa - dr >=0 && Chessboard[aa-dr][bb-dr] == 1;dr++)
					sum[4]++;//左上
					if(aa-dr>=0&&bb-dr>=0)
					end[4] = Chessboard[aa-dr][bb-dr];
			for(dr = 1;bb+dr < begin_dial.m_hanglie && aa+dr < begin_dial.m_hanglie && Chessboard[aa+dr][bb+dr] == 1;dr++)
					sum[5]++;//右下
					if(aa+dr< begin_dial.m_hanglie && bb+dr< begin_dial.m_hanglie)
					end[5] = Chessboard[aa+dr][bb+dr];
			for(dr = 1;dr+aa < begin_dial.m_hanglie && bb-dr >= 0 && Chessboard[aa+dr][bb-dr] == 1;dr++)
					sum[6]++;//左下
					if(aa+dr< begin_dial.m_hanglie&&bb-dr >=0)
					end[6] = Chessboard[aa+dr][bb-dr] ;
			for(dr = 1;aa-dr >=0 && bb + dr < begin_dial.m_hanglie && Chessboard[aa-dr][bb+dr] == 1;dr++)
					sum[7]++;//右上
					if(aa-dr >=0&& bb+dr <begin_dial.m_hanglie)
					end[7] = Chessboard[aa-dr][bb+dr];	
					int win33 = 0;
			for(int cc = 0;cc < 8;cc++)
			{
			if(sum[cc] >=3 && end[cc] == 0)
				{
				i_temp = aa;
				j_temp = bb;
				}
			if(sum[cc] >=2 && end[cc] == 0)
				win33++;
			}
			if(i_temp == -1 && i_temp33 != -1)
				{
				i_temp = i_temp33;
				j_temp = j_temp33;
				}
			if(win33 > 1 && i_temp == -1)
			{
			i_temp = aa;
			j_temp = bb;
			have33 = true;
			}
			if(i_temp == -1 && !have33)
			{
			for(int cc = 0;cc < 4;cc++)
			{
			if(sum[cc*2] + sum[cc*2+1] >=3 && (end[cc*2]==0 && end[cc*2+1]==0) && attackmode)
				{
				i_temp = aa;
				j_temp = bb;
				}
				else if(sum[cc*2] + sum[cc*2+1] >=3 && (end[cc*2]==0 || end[cc*2+1]==0) && !attackmode)
				{
				i_temp = aa;
				j_temp = bb;
				}
			}
			}

			}
		}
		//研究绝对防御。。。这一段可以注释掉
	/*if(i_temp == -1)
	{
	for(int aa = 3;aa<begin_dial.m_hanglie-3;aa++)
		for(int bb =3;bb < begin_dial.m_hanglie-3;bb++)
		{
			if(Chessboard[aa][bb] == 0)
		if((Chessboard[aa-1][bb-2] == 1 && Chessboard[aa-3][bb-1] == 1 && Chessboard[aa-2][bb+1] == 1)||
			(Chessboard[aa-2][bb+1] == 1 && Chessboard[aa-1][bb+3] == 1 && Chessboard[aa+1][bb+2] == 1)||
			(Chessboard[aa-1][bb-2] == 1 && Chessboard[aa+1][bb-3] == 1 && Chessboard[aa+2][bb-1] == 1)||
			(Chessboard[aa+1][bb+2] == 1 && Chessboard[aa+3][bb+1] == 1 && Chessboard[aa+2][bb-1] == 1)||
			(Chessboard[aa+1][bb-2] == 1 && Chessboard[aa-1][bb-3] == 1 && Chessboard[aa-2][bb-1] == 1)||
			(Chessboard[aa-1][bb+2] == 1 && Chessboard[aa-3][bb+1] == 1 && Chessboard[aa-2][bb-1] == 1)||
			(Chessboard[aa+2][bb+1] == 1 && Chessboard[aa-1][bb+2] == 1 && Chessboard[aa+1][bb+3] == 1)||
			(Chessboard[aa-1][bb-2] == 1 && Chessboard[aa+1][bb-2] == 1 && Chessboard[aa+3][bb+1] == 1))
			{
			i_temp = aa;
			j_temp = bb;
			}			
		}
	}
*/
	//若无以上情形，计算计算机各点分数
	
	if(i_temp == -1)
	{
		//MessageBox("这有可能是无理手。。。。");
	for(int i = 0;i < begin_dial.m_hanglie;i++)
		for(int j = 0;j < begin_dial.m_hanglie;j++)
		{
		if(Chessboard[i][j] == 0)
		{
			score[i][j] = 0;
		for(int k = 0;k < (4*begin_dial.m_hanglie-8)*(begin_dial.m_hanglie-4);k++)
			{
			for(int l = 0;l < 5;l++)
				{
				if(i + 1 == winmethod[k].pos[l][0] && j + 1 == winmethod[k].pos[l][1] && computer_left[k] <5)
					score[i][j] += (5-computer_left[k]);//有权相加，若为无权，改为score[i][j] ++;
				}
			}
		if(score[i][j] > best_score)
			{
			best_score = score[i][j];
			i_temp = i;
			j_temp = j;
			}
		}
		}

	


	//计算玩家各点分数
	for(i = 0;i < begin_dial.m_hanglie;i++)
		for(int j = 0;j < begin_dial.m_hanglie;j++)
		{
		if(Chessboard[i][j] == 0)
		{
			score[i][j] = 0;
		for(int k = 0;k < (4*begin_dial.m_hanglie-8)*(begin_dial.m_hanglie-4);k++)
			{
			for(int l = 0;l < 5;l++)
				{
				if(i + 1 == winmethod[k].pos[l][0] && j + 1 == winmethod[k].pos[l][1] && player_left[k] < 5)
					score[i][j] += (5 - player_left[k]);//有权相加，若为无权，改为score[i][j] ++;
				}
			}
		if(score[i][j] > best_score)
			{
			best_score = score[i][j];
			i_temp = i;
			j_temp = j;
			}
		}
		}
	}

//	CString tips;
	//tips.Format("(%d,%c)",i_temp+1,j_temp+'A');
	//MessageBox(tips);
	tip.y = i_temp+1;
	tip.x = j_temp+1;
	
	for(l=0;l<begin_dial.m_hanglie;l++)	
		for(int k=0;k<begin_dial.m_hanglie;k++)
			{
			Chessboard[l][k]=	Chessboard_temp[l][k];//0 没下  1玩家 -1 电脑
			score[l][k]=score_temp[l][k];
			}
	for( c = 0;c < (4*begin_dial.m_hanglie-8)*(begin_dial.m_hanglie-4);c++)
	{
	player_left[c] = player_left_temp[c];
	computer_left[c] = computer_left_temp[c];
	}
	Invalidate();

}

void CBmView::OnUpdatezhizhao(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	if(game_begin && game_finish == 0)
		pCmdUI->Enable(true);
	else
		pCmdUI->Enable(false);
}
