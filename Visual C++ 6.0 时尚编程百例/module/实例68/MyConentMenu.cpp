// MyConentMenu.cpp : implementation file
//

#include "stdafx.h"
#include "ListBox.h"
#include "MyConentMenu.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MyConentMenu

MyConentMenu::MyConentMenu()
{
	State=0;
}

MyConentMenu::~MyConentMenu()
{
}


BEGIN_MESSAGE_MAP(MyConentMenu, CListBox)
	//{{AFX_MSG_MAP(MyConentMenu)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MyConentMenu message handlers

void MyConentMenu::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
CDC *pDC=CDC::FromHandle(lpDrawItemStruct->hDC);
	CRect           rcItem(lpDrawItemStruct->rcItem);
    CRect           rClient(rcItem);
    CRect           rText;
    CPoint          Pt(((rcItem.Width() - 32) /2 ), rcItem.top + 15);
    
    HICON           hIcon = AfxGetApp()->LoadIcon(IDI_MYICON);
    HICON           hIcon1=AfxGetApp()->LoadIcon(IDI_MYICON1);
    HICON           hIcon2=AfxGetApp()->LoadIcon(IDI_MYICON2);
    rClient.DeflateRect(5,10);
	rcItem.CopyRect(rClient);
    rText.CopyRect(rClient);
    rText.top += 35;

    pDC->SetBkMode(TRANSPARENT);

    pDC->DrawIcon(Pt, hIcon);
	Pt.y=Pt.y+35;
	pDC->DrawIcon(Pt,hIcon1);
	Pt.y=Pt.y+35;
	pDC->DrawIcon(Pt,hIcon2);
//	pDC->FillSolidRect(rClient,GetSysColor(COLOR_WINDOW));
	
}

void MyConentMenu::OnLButtonDown(UINT nFlags, CPoint point) 
{

	CListBox::OnLButtonDown(nFlags, point);
}


void MyConentMenu::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CListBox::OnMouseMove(nFlags, point);
}
