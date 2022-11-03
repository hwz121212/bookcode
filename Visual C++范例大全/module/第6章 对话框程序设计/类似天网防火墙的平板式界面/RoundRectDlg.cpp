// RoundRectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "RoundRect.h"
#include "RoundRectDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRoundRectDlg dialog

CRoundRectDlg::CRoundRectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRoundRectDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRoundRectDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRoundRectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRoundRectDlg)
	DDX_Control(pDX, IDC_BUTTON_TEST, m_btnTest);
	DDX_Control(pDX, IDOK, m_btnOK);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CRoundRectDlg, CDialog)
	//{{AFX_MSG_MAP(CRoundRectDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_NCHITTEST()
	ON_WM_ERASEBKGND()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRoundRectDlg message handlers

BOOL CRoundRectDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	brush.CreateSolidBrush(RGB(223,233,243));
	myrgn.CreateRoundRectRgn(2,2,300,170,15,15);

    SetWindowRgn(myrgn, 1);
	SetWindowText("自制窗口标题");
//-------------------------------------------
	m_strFontFace="宋体";

	lf.lfHeight=GetSystemMetrics(SM_CYCAPTION);
	lf.lfWidth=GetSystemMetrics(SM_CYCAPTION)-8;
	lf.lfWeight=700;
	lf.lfCharSet=DEFAULT_CHARSET;
	lf.lfClipPrecision=CLIP_DEFAULT_PRECIS;
	lf.lfEscapement=0;
	lf.lfItalic=0;
	lf.lfOrientation=0;
	lf.lfOutPrecision=OUT_TT_PRECIS;
	lf.lfPitchAndFamily=DEFAULT_PITCH;
	lf.lfQuality=DEFAULT_QUALITY;
	lf.lfStrikeOut=0;
	lf.lfUnderline=0;

	strcpy(lf.lfFaceName, m_strFontFace);  
	m_fontMe.CreateFontIndirect(&lf);
//---------------------------------------------
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CRoundRectDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
			CDC *pDC=GetDC();
		//	pDC->FillRgn(&myrgn,&brush);
		//	pDC->TextOut(20,20,"dfdsadfdsa");
		//	ReleaseDC(pDC);

			CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CRoundRectDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

LRESULT CRoundRectDlg::OnNcHitTest(CPoint point) 
{
 UINT nHitTest = CDialog :: OnNcHitTest (point);
 return (nHitTest == HTCLIENT)? HTCAPTION: nHitTest;
}

BOOL CRoundRectDlg::OnEraseBkgnd(CDC* pDC) 
{
	CRgn myrgn1,myrgn2;
	myrgn1.CreateRoundRectRgn(1,1,299,169,15,15);
	myrgn2.CreateRectRgn(1,1,299,40);
	CBrush frameBrush,frameBrush1;
	frameBrush.CreateSolidBrush(RGB(178,178,200));
	frameBrush1.CreateSolidBrush(RGB(17,136,255));

	pDC->FillRgn(&myrgn1,&brush);
	pDC->FillRgn(&myrgn2,&frameBrush1);

	pDC->FrameRgn(&myrgn1,&frameBrush,1,1);

	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextColor(0x00ffffff);
	pDC->SelectObject(&m_fontMe);
	pDC->TextOut(45,10,"乔建江提示窗口");

	//pDC->SetBkMode(OPAQUE);
//	pDC->DrawIcon(8,8,LoadIcon(NULL,IDI_INFORMATION));//系统图标这样做
	pDC->DrawIcon(4,4,LoadIcon(::AfxGetInstanceHandle(),MAKEINTRESOURCE(IDI_ASK)));//用户图标这样做
	
	return 1;

//	return CDialog::OnEraseBkgnd(pDC);
}
