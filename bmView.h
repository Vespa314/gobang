// bmView.h : interface of the CBmView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BMVIEW_H__23EA2312_13B9_4B5E_9735_936394358512__INCLUDED_)
#define AFX_BMVIEW_H__23EA2312_13B9_4B5E_9735_936394358512__INCLUDED_

#include "Begin.h"	// Added by ClassView
#include "Winmethod.h"
#include "Again.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CBmView : public CView
{
protected: // create from serialization only
	CBmView();
	DECLARE_DYNCREATE(CBmView)

// Attributes
public:
	CBmDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBmView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	CPoint tip;
	int timer_counter;
	int time_limit;
	bool attackmode;
	CAgain again_dial;
	int UpdateLeft(int x,int y,bool computer);//更新computer_left,player_left
	//CDC mdc;
	int ChessOrderCounter;//记录步数
	BOOL game_begin;//游戏开始
	BOOL player_first;//玩家先手
	int game_finish;//游戏结束
	int jiange;//棋盘间隔
	//BOOL turn;
	BOOL dapu;//打谱
	CBegin begin_dial;//游戏设置对话框
	int **Chessboard;//棋盘状况
	CWinmethod *winmethod;//所有胜法
	CPoint *ChessOrder;//下棋顺序
	int **score;//每个位置分数
	int win_step[5][2];//胜利时哪5格连在一起了
	int *player_left;//玩家每种胜法还有几步  6为永远不能胜
	int *computer_left;//同上
	virtual ~CBmView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBmView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBegingame();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRegrret();
	afx_msg void OnUpdateRegrret(CCmdUI* pCmdUI);
	afx_msg void OnDapu();
	afx_msg void OnUpdateDapu(CCmdUI* pCmdUI);
	afx_msg void OnTimemode();
	afx_msg void OnUpdateTimemode(CCmdUI* pCmdUI);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void Onzhizhao();
	afx_msg void OnUpdatezhizhao(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in bmView.cpp
inline CBmDoc* CBmView::GetDocument()
   { return (CBmDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BMVIEW_H__23EA2312_13B9_4B5E_9735_936394358512__INCLUDED_)
