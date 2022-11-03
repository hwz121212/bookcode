// PENWILDDLG.cpp : implementation file
//

#include "stdafx.h"
#include "MyPen.h"
#include "PENWILDDLG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// PENWILDDLG dialog


PENWILDDLG::PENWILDDLG(CWnd* pParent /*=NULL*/)
	: CDialog(PENWILDDLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(PENWILDDLG)
	m_penwild = 1;
	//}}AFX_DATA_INIT
}


void PENWILDDLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(PENWILDDLG)
	DDX_Control(pDX, IDC_SPIN_WILD, m_cwildspin);
	DDX_Control(pDX, IDC_EDIT_WILD, m_cpenwild);
	DDX_Text(pDX, IDC_EDIT_WILD, m_penwild);
	DDV_MinMaxInt(pDX, m_penwild, 1, 100);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(PENWILDDLG, CDialog)
	//{{AFX_MSG_MAP(PENWILDDLG)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// PENWILDDLG message handlers
