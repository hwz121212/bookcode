// ProPSheet1.cpp : implementation file
//

#include "stdafx.h"
#include "PropSheet.h"
#include "ProPSheet1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProPSheet

IMPLEMENT_DYNAMIC(CProPSheet, CPropertySheet)

CProPSheet::CProPSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	AddPage(&m_page1);
    AddPage(&m_page2);

}

CProPSheet::CProPSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	AddPage(&m_page1);
    AddPage(&m_page2);

}

CProPSheet::~CProPSheet()
{
}


BEGIN_MESSAGE_MAP(CProPSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CProPSheet)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProPSheet message handlers
