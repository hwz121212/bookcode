// DlgLogin.cpp : implementation file
//

#include "stdafx.h"
#include "GpsServer.h"
#include "DlgLogin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgLogin dialog


CDlgLogin::CDlgLogin(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLogin::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgLogin)
	m_pass = _T("");
	m_user = _T("");
	m_bUseDB = FALSE;
	//}}AFX_DATA_INIT
}


void CDlgLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLogin)
	DDX_Control(pDX, IDC_CHECK_USEDB, m_buttonUseDB);
	DDX_Control(pDX, IDC_EDIT_USER, m_editUser);
	DDX_Control(pDX, IDC_EDIT_PASS, m_editPass);
	DDX_Text(pDX, IDC_EDIT_PASS, m_pass);
	DDV_MaxChars(pDX, m_pass, 50);
	DDX_Text(pDX, IDC_EDIT_USER, m_user);
	DDV_MaxChars(pDX, m_user, 50);
	DDX_Check(pDX, IDC_CHECK_USEDB, m_bUseDB);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLogin, CDialog)
	//{{AFX_MSG_MAP(CDlgLogin)
	ON_BN_CLICKED(IDC_CHECK_USEDB, OnCheckUsedb)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLogin message handlers

///////////////////////////////////////////////////////////////////
// 函数名：	OnCheckUsedb
// 功  能：	判断用户是否选择使用数据库
// 参  数：	
// 返回值：	
// 备  注：
//////////////////////////////////////////////////////////////////
void CDlgLogin::OnCheckUsedb() 
{
	// TODO: Add your control notification handler code here
	if (!m_buttonUseDB.GetCheck())
	{
		m_editUser.SetReadOnly(true);		
		m_editPass.SetReadOnly(true);
	}
	else
	{
		m_editUser.SetReadOnly(false);		
		m_editPass.SetReadOnly(false);
	}
}
