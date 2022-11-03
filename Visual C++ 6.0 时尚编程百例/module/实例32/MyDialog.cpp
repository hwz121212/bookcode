// MyDialog.cpp : implementation file
//

#include "stdafx.h"
#include "DrawBottun.h"
#include "MyDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MyDialog dialog


MyDialog::MyDialog(CWnd* pParent /*=NULL*/)
	: CDialog(MyDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(MyDialog)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void MyDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(MyDialog)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(MyDialog, CDialog)
	//{{AFX_MSG_MAP(MyDialog)
	ON_WM_DRAWITEM()
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	ON_BN_CLICKED(IDC_RADIO3, OnRadio3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MyDialog message handlers

void MyDialog::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
    CDC dc;
	

	dc.Attach(lpDrawItemStruct->hDC);
	if(nIDCtl=IDC_SAMPLE)
	{
        CWnd *SampleWnd=GetDlgItem(IDC_SAMPLE);
	    CRect SampleRect;
		SampleWnd->GetClientRect(&SampleRect);
		dc.FillSolidRect(&SampleRect,m_colors);
		

	}
	CDialog::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

BOOL MyDialog::OnInitDialog() 
{

	
	CDialog::OnInitDialog();
	m_colors=RGB(192,192,192);
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void MyDialog::OnRadio1() 
{
m_colors=RGB(255,0,0);
CWnd *SampleWnd=GetDlgItem(IDC_SAMPLE);
SampleWnd->Invalidate();
SampleWnd->UpdateWindow();
	
}

void MyDialog::OnRadio2() 
{
m_colors=RGB(0,255,0);
CWnd *SampleWnd=GetDlgItem(IDC_SAMPLE);
SampleWnd->Invalidate();
SampleWnd->UpdateWindow();
	
}

void MyDialog::OnRadio3() 
{
m_colors=RGB(0,0,255);
CWnd *SampleWnd=GetDlgItem(IDC_SAMPLE);
SampleWnd->Invalidate();
SampleWnd->UpdateWindow();
	
}
