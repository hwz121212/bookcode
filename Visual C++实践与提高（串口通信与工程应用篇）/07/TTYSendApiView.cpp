// TTYSendApiView.cpp : implementation of the CTTYSendApiView class
//

#include "stdafx.h"
#include "TTYSendApi.h"

#include "TTYSendApiDoc.h"
#include "TTYSendApiView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CTTYSendApiView

IMPLEMENT_DYNCREATE(CTTYSendApiView, CEditView)

BEGIN_MESSAGE_MAP(CTTYSendApiView, CEditView)
	//{{AFX_MSG_MAP(CTTYSendApiView)
	ON_WM_CREATE()
	ON_COMMAND(ID_SETUPCOM, OnSetupcom)
	ON_COMMAND(ID_OPENCOM, OnOpencom)
	ON_COMMAND(ID_CLOSECOM, OnClosecom)
	ON_UPDATE_COMMAND_UI(ID_CLOSECOM, OnUpdateClosecom)
	ON_UPDATE_COMMAND_UI(ID_OPENCOM, OnUpdateOpencom)
	ON_UPDATE_COMMAND_UI(ID_SETUPCOM, OnUpdateSetupcom)
	ON_UPDATE_COMMAND_UI(ID_APP_EXIT, OnUpdateAppExit)
	ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTTYSendApiView construction/destruction

CTTYSendApiView::CTTYSendApiView()
{
	// TODO: add construction code here

}

CTTYSendApiView::~CTTYSendApiView()
{
}

BOOL CTTYSendApiView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// Enable word-wrapping

	return bPreCreated;
}

/////////////////////////////////////////////////////////////////////////////
// CTTYSendApiView drawing

void CTTYSendApiView::OnDraw(CDC* pDC)
{
	CTTYSendApiDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CTTYSendApiView diagnostics

#ifdef _DEBUG
void CTTYSendApiView::AssertValid() const
{
	CEditView::AssertValid();
}

void CTTYSendApiView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CTTYSendApiDoc* CTTYSendApiView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTTYSendApiDoc)));
	return (CTTYSendApiDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTTYSendApiView message handlers

BOOL CTTYSendApiView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CWnd::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}

int CTTYSendApiView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CEditView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	blnOpened=false;                          //串口打开标志置假
	return 0;
}

void CTTYSendApiView::OnSetupcom() 
{
	// TODO: Add your command handler code here
	CString strStatus;
	if(mySetupDlg.DoModal()==IDOK)
	{
		switch (mySetupDlg.m_Com)
		{
		case 0:
			{
			strStatus="COM1";
			myCom="COM1";
			break;
			}
		case 1:
			{
			strStatus="COM2";
			myCom="COM2";
			break;
			}

		case 2:
			{
			strStatus="COM3";
			myCom="COM3";
			break;
			}

		case 3:
			{
			strStatus="COM4";
			myCom="COM4";
			break;
			}

		case 4:
			{
			strStatus="COM5";
			myCom="COM5";
			}
			break;
		case 5:
			{
			strStatus="COM6";
			myCom="COM6";
			}
			break;
		}
		strStatus+=",";
		switch(mySetupDlg.m_BaudRate)
		{

		case 0:
			{
			strStatus+="19200";
			myBaudRate=CBR_19200;
			break;
			}
		case 1:
			{
			strStatus+="9600";
			myBaudRate=CBR_9600;
			break;
			}
		case 2:
			{
			strStatus+="4800";
			myBaudRate=CBR_4800;
			break;
			}
		case 3:
			{
			strStatus+="2400";
			myBaudRate=CBR_2400;
			break;
			}
		}
		strStatus+=",";
		switch(mySetupDlg.m_Parity)
		{
		case 0:
			{
			myfParity=false;
			myParity=NOPARITY;
			strStatus+="N";
			break;
			}
		case 1:
			{
			myfParity=TRUE;
			myParity=ODDPARITY;
			strStatus+="O";
			break;
			}
		case 2:
			{
			myfParity=true;
			myParity=EVENPARITY;
			strStatus+="E";
			break;
			}
		}
		strStatus+=",8,1";

		CMainFrame* m_pGetFrame=(CMainFrame*) AfxGetApp()->m_pMainWnd ;
		strStatus="TTY 发送程序-"+strStatus;
		m_pGetFrame->SetWindowText(strStatus);
	}
}

void CTTYSendApiView::OnOpencom() 
{
	// TODO: Add your command handler code here
	CString strDis;
	hCom=CreateFile(myCom,                                //创建串口
		GENERIC_READ | GENERIC_WRITE, 
		0,
		NULL,
		OPEN_EXISTING, 
		FILE_ATTRIBUTE_NORMAL |FILE_FLAG_OVERLAPPED,     //使用重叠方式
		 NULL );
	if( hCom !=INVALID_HANDLE_VALUE) 
	{
		SetupComm(hCom,1024,512);
		DCB myDCB;
		GetCommState( hCom, &myDCB );
		myDCB.BaudRate=myBaudRate;
		myDCB.fBinary=TRUE;
		myDCB.fParity=myfParity;
		myDCB.ByteSize=8;
		myDCB.Parity=myParity;
		myDCB.StopBits=ONESTOPBIT;
		SetCommState(hCom,&myDCB);

		AfxMessageBox("串口打开成功！");

		blnOpened=true;
	}
	else
	{
		AfxMessageBox("串口打开失败！");
		blnOpened=false;
	}	
}

void CTTYSendApiView::OnClosecom() 
{
	// TODO: Add your command handler code here
	if ((blnOpened) && (hCom!=NULL))
	{
		CloseHandle(hCom);
		AfxMessageBox("串口已经关闭！");
		blnOpened=false;
	}
	else
	{
		AfxMessageBox("串口未打开！");
	}
}

void CTTYSendApiView::OnUpdateClosecom(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	//根据串口是否打开，决定是否允许“关闭”命令
	if (blnOpened)
	{
		pCmdUI->Enable(true);
	}
	else
	{
		pCmdUI->Enable(false);
	}
}

void CTTYSendApiView::OnUpdateOpencom(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	//根据串口是否打开，决定是否允许“打开”命令
	if (!blnOpened)
	{
		pCmdUI->Enable(true);
	}
	else
	{
		pCmdUI->Enable(false);
	}
}

void CTTYSendApiView::OnUpdateSetupcom(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	//根据串口是否打开，决定是否允许“设置”命令
	if (!blnOpened)
	{
		pCmdUI->Enable(true);
	}
	else
	{
		pCmdUI->Enable(false);
	}
}

void CTTYSendApiView::OnUpdateAppExit(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	//根据串口是否打开，决定是否允许“退出”命令
	if (blnOpened)
	{
		pCmdUI->Enable(false);
	}
	else
	{
		pCmdUI->Enable(true);
	}
}

void CTTYSendApiView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	myWByte[0]=nChar;
	dataWLen=1;
	Wol.Internal=0;                        //设置OVERLAPPED结构Wol
	Wol.InternalHigh=0;
	Wol.Offset=0;
	Wol.OffsetHigh=0;
	Wol.hEvent=CreateEvent(NULL,          //创建Wol的hEvent成员为无信号状态
         TRUE,
         FALSE,
         NULL);
	WriteFile(hCom,&myWByte,dataWLen,NULL,&Wol);
	Beep(1000,10);
	CEditView::OnChar(nChar, nRepCnt, nFlags);
}
