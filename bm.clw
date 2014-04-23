; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CBmView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "bm.h"
LastPage=0

ClassCount=8
Class1=CBmApp
Class2=CBmDoc
Class3=CBmView
Class4=CMainFrame

ResourceCount=4
Resource1=IDD_ABOUTBOX
Resource2=IDD_DIALOG1
Class5=CAboutDlg
Class6=CBegin
Resource3=IDR_MAINFRAME
Class7=CAgain
Class8=CSplashWnd
Resource4=IDD_DIALOG2

[CLS:CBmApp]
Type=0
HeaderFile=bm.h
ImplementationFile=bm.cpp
Filter=N

[CLS:CBmDoc]
Type=0
HeaderFile=bmDoc.h
ImplementationFile=bmDoc.cpp
Filter=N

[CLS:CBmView]
Type=0
HeaderFile=bmView.h
ImplementationFile=bmView.cpp
Filter=C
BaseClass=CView
VirtualFilter=VWC
LastObject=IDC_zhizhao


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=DC_BEGINGAME




[CLS:CAboutDlg]
Type=0
HeaderFile=bm.cpp
ImplementationFile=bm.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=DC_BEGINGAME
Command9=IDC_REGRRET
Command10=IDC_DAPU
Command11=IDC_TIMEMODE
Command12=IDC_zhizhao
Command13=ID_APP_ABOUT
CommandCount=13

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_EDIT_COPY
Command2=DC_BEGINGAME
Command3=ID_FILE_NEW
Command4=ID_FILE_OPEN
Command5=ID_FILE_PRINT
Command6=ID_FILE_SAVE
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_UNDO
Command9=ID_EDIT_CUT
Command10=ID_NEXT_PANE
Command11=ID_PREV_PANE
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_EDIT_CUT
Command15=ID_EDIT_UNDO
CommandCount=15

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_OPEN
Command2=ID_FILE_SAVE
Command3=DC_BEGINGAME
Command4=IDC_REGRRET
Command5=IDC_TIMEMODE
Command6=IDC_DAPU
Command7=IDC_zhizhao
Command8=ID_APP_ABOUT
CommandCount=8

[DLG:IDD_DIALOG1]
Type=1
Class=CBegin
ControlCount=14
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT1,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_RADIO1,button,1342308361
Control6=IDC_RADIO2,button,1342177289
Control7=IDC_STATIC,button,1342177287
Control8=IDC_CHECK1,button,1342242819
Control9=IDC_SLIDER1,msctls_trackbar32,1342242840
Control10=IDC_STATIC,button,1342177287
Control11=IDC_RADIO3,button,1342308361
Control12=IDC_RADIO4,button,1342177289
Control13=IDC_STATIC,button,1342177287
Control14=IDC_EDIT2,edit,1350631552

[CLS:CBegin]
Type=0
HeaderFile=Begin.h
ImplementationFile=Begin.cpp
BaseClass=CDialog
Filter=D
LastObject=IDOK
VirtualFilter=dWC

[DLG:IDD_DIALOG2]
Type=1
Class=CAgain
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352

[CLS:CAgain]
Type=0
HeaderFile=Again.h
ImplementationFile=Again.cpp
BaseClass=CDialog
Filter=D
LastObject=CAgain

[CLS:CSplashWnd]
Type=0
HeaderFile=Splash.h
ImplementationFile=Splash.cpp
BaseClass=CWnd
LastObject=CSplashWnd

