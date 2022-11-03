// MyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MyMsg.h"
#include "MyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MyDlg dialog


MyDlg::MyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(MyDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(MyDlg)
	m_String = _T("");
	//}}AFX_DATA_INIT
}


void MyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MyDlg)
	DDX_Text(pDX, IDC_MYEDIT, m_String);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MyDlg, CDialog)
	//{{AFX_MSG_MAP(MyDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MyDlg message handlers
