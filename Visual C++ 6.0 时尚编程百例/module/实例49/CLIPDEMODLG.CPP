// ClipDemoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ClipDemo.h"
#include "ClipDemoDlg.h"
#include "Clipboard.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CClipDemoDlg dialog

CClipDemoDlg::CClipDemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClipDemoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CClipDemoDlg)
	m_strEdit = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClipDemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClipDemoDlg)
	DDX_Text(pDX, IDC_EDIT1, m_strEdit);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CClipDemoDlg, CDialog)
	//{{AFX_MSG_MAP(CClipDemoDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_COPY, OnCopy)
	ON_BN_CLICKED(IDC_BUTTON_PASTE, OnPaste)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClipDemoDlg message handlers

BOOL CClipDemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CClipDemoDlg::OnPaint() 
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
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CClipDemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CClipDemoDlg::OnCopy()
{
	UpdateData();

	int nSize = m_strEdit.GetLength();
	char* buf = new char[nSize + 1];
	strcpy (buf, m_strEdit);

	CClipboard::SetText(buf);

	delete[] buf;
}

void CClipDemoDlg::OnPaste() 
{
	char* buf;
	unsigned long nSize;
	
	CClipboard::GetTextLength(&nSize);

	buf = new char[nSize + 1];

	CClipboard::GetText(buf, nSize + 1);
	buf[nSize] = 0;

	m_strEdit = buf;
	UpdateData(FALSE);

	delete[] buf;
}
