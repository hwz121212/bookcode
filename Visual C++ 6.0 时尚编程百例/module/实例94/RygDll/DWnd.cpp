// DWnd.cpp : implementation file
//

#include "stdafx.h"
#include "RygDll.h"
#include "DWnd.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDWnd
LRESULT CALLBACK AFX_EXPORT
		RygWndProc(HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	CWnd *pWnd;

	pWnd=CWnd::FromHandlePermanent(hWnd);
	if(pWnd==NULL){
		pWnd=new CDWnd();
		pWnd->Attach(hWnd);
	}
	ASSERT(pWnd->m_hWnd==hWnd);
	ASSERT(pWnd==CWnd::FromHandlePermanent(hWnd));
	LRESULT lResult=AfxCallWndProc(pWnd,hWnd,message,wParam,lParam);
	
	return lResult;
}
CRect CDWnd::s_rect(-500,1000,500,-1000);
CPoint  CDWnd::s_point(300,300);
CRect  CDWnd::s_rColor[]={ CRect(-250,800,250,300),
						  CRect(-250,250,250,-250),
						  CRect(-250,-300,250,-800)};
CBrush  CDWnd::s_bColor[]={RGB(192,192,192),
                          RGB(0xFF,0x00,0x00),
						  RGB(0xFF,0xFF,0x00),
						  RGB(0x00,0xFF,0x00)};

BOOL CDWnd::RegisterWndClass(HINSTANCE hInstance)
{
	WNDCLASS wc;
	wc.lpszClassName="RGB";
	wc.hInstance=hInstance;
	wc.lpfnWndProc = RygWndProc;
	wc.hCursor=::LoadCursor(NULL,IDC_ARROW);
	wc.hIcon=0;
	wc.lpszMenuName=NULL;
	wc.hbrBackground=(HBRUSH)::GetStockObject(LTGRAY_BRUSH);
	wc.style=CS_GLOBALCLASS;
	wc.cbClsExtra=0;
	wc.cbWndExtra=0;

	return(::RegisterClass(&wc)!=0);
}
CDWnd::CDWnd()
{
	m_nState=0;
}

CDWnd::~CDWnd()
{
}


BEGIN_MESSAGE_MAP(CDWnd, CWnd)
	//{{AFX_MSG_MAP(CDWnd)
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
	ON_MESSAGE(RGB_SETSTATE,OnSetState)
	ON_MESSAGE(RGB_GETSTATE,OnGetState)
END_MESSAGE_MAP()

void CDWnd::SetMapping(CDC *pDC)
{

	CRect clientRect;
	GetClientRect(clientRect);
	pDC->SetMapMode(MM_ISOTROPIC);
	pDC->SetWindowExt(1000,2000);
	pDC->SetViewportExt(clientRect.right,-clientRect.bottom);
	pDC->SetViewportOrg(clientRect.right/2,clientRect.bottom/2);
}

void CDWnd::UpdateColor(CDC *pDC,int n)
{
	if(m_nState==n+1){
		pDC->SelectObject(&s_bColor[n+1]);
	}
	else{
		pDC->SelectObject(&s_bColor[0]);
	}
	pDC->Ellipse(s_rColor[n]);
}
/////////////////////////////////////////////////////////////////////////////
// CDWnd message handlers

void CDWnd::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	
	delete this;
}

void CDWnd::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	
	CWnd::OnLButtonUp(nFlags, point);
}

void CDWnd::OnLButtonDown(UINT nFlags, CPoint point) 
{
	GetParent()->SendMessage(WM_COMMAND,GetDlgCtrlID(),(LONG) GetSafeHwnd());
}

void CDWnd::OnPaint() 
{
		int i;
	CPaintDC dc(this); // device context for painting
	SetMapping(&dc);
	dc.SelectStockObject(DKGRAY_BRUSH);
	dc.RoundRect(s_rect,s_point);
	for(i=0;i<3;i++){
		UpdateColor(&dc,i);
	}	
	// TODO: Add your message handler code here
	
	// Do not call CWnd::OnPaint() for painting messages
}
LRESULT CDWnd::OnSetState(WPARAM wParam,LPARAM lParam)
{
	m_nState=(int)wParam;
	Invalidate(FALSE);
	return 0L;
}

LRESULT CDWnd::OnGetState(WPARAM wParam,LPARAM lParam)
{
		return m_nState;
}
