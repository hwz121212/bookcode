// MyDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Listbox.h"
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
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void MyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MyDlg)
	DDX_Control(pDX, IDC_LIST1, m_mylistbox);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MyDlg, CDialog)
	//{{AFX_MSG_MAP(MyDlg)
	ON_WM_DRAWITEM()
	ON_LBN_SELCHANGE(IDC_LIST1, OnSelchangeList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MyDlg message handlers

BOOL MyDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
    nIndex=0;

	m_mylistbox.AddString("green colors");
	m_mylistbox.AddString("blue colors");
	m_mylistbox.AddString("black colors");	
	m_mylistbox.AddString("red colors");
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void MyDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	// TODO: Add your message handler code here and/or call default
	CDC dc;
	

	dc.Attach(lpDrawItemStruct->hDC);
	if(nIDCtl=IDC_BUTTON1)
	{
        CWnd *SampleWnd=GetDlgItem(IDC_BUTTON1);
	    CRect SampleRect;
		SampleWnd->GetClientRect(&SampleRect);
		
	
	switch(nIndex)
	{
	case 0:dc.FillSolidRect(&SampleRect,RGB(0,0,0));break;
	case 1:dc.FillSolidRect(&SampleRect,RGB(0,0,255));break;
	case 2:dc.FillSolidRect(&SampleRect,RGB(0,255,0));break;
	case 3:dc.FillSolidRect(&SampleRect,RGB(255,0,0));break;
	default:break;
	}
	}
	CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void MyDlg::OnSelchangeList() 
{
nIndex=m_mylistbox.GetCurSel();
CWnd *pWnd=GetDlgItem(IDC_BUTTON1);
pWnd->Invalidate();
pWnd->UpdateWindow();	
}
