// DynMenuView.cpp : implementation of the CDynMenuView class
//

#include "stdafx.h"
#include "DynMenu.h"

#include "DynMenuDoc.h"
#include "DynMenuView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDynMenuView

IMPLEMENT_DYNCREATE(CDynMenuView, CView)

BEGIN_MESSAGE_MAP(CDynMenuView, CView)
	//{{AFX_MSG_MAP(CDynMenuView)
	ON_COMMAND(ID_EXPAND, OnExpand)
	ON_COMMAND(ID_STANDARD, OnStandard)
	ON_UPDATE_COMMAND_UI_RANGE(ID_STANDARD,ID_EXPAND,  OnUpdateOptions)
	ON_COMMAND(ID_BLACK, OnBlack)
	ON_COMMAND(ID_RED, OnRed)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDynMenuView construction/destruction

CDynMenuView::CDynMenuView()
{
	// TODO: add construction code here

}

CDynMenuView::~CDynMenuView()
{
}

BOOL CDynMenuView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDynMenuView drawing

void CDynMenuView::OnDraw(CDC* pDC)
{
	CDynMenuDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CDynMenuView printing

BOOL CDynMenuView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDynMenuView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDynMenuView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDynMenuView diagnostics

#ifdef _DEBUG
void CDynMenuView::AssertValid() const
{
	CView::AssertValid();
}

void CDynMenuView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDynMenuDoc* CDynMenuView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDynMenuDoc)));
	return (CDynMenuDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDynMenuView message handlers

void CDynMenuView::OnExpand() 
{
    CMenu *pAddinMenu, *pTopMenu;
	
	pTopMenu = AfxGetMainWnd()->GetMenu();

	pAddinMenu = pTopMenu->GetSubMenu(1);
	ASSERT(pAddinMenu != NULL);
	

	pAddinMenu->AppendMenu(MF_SEPARATOR);


	CString MenuName;
	for (int i = 0; i < 2; i++)
	{
		MenuName.LoadString(IDS_BLUE + i);
		pAddinMenu->AppendMenu(MF_STRING, 
						IDS_BLUE+ i, MenuName);
	}	// TODO: Add your command handler code here
	
}

void CDynMenuView::OnStandard() 
{
    CMenu *pAddinMenu, *pTopMenu;
	
	pTopMenu = AfxGetMainWnd()->GetMenu();

	
	pAddinMenu = pTopMenu->GetSubMenu(1);

	int i = pAddinMenu->GetMenuItemCount();

	if (5 == i)
	{
		i--;			
		while(i > 1)
		{
			pAddinMenu->RemoveMenu(i, MF_BYPOSITION);
			i--;
		}
	}
	else

	{
		
		pAddinMenu->DeleteMenu(3, MF_BYPOSITION);
		
	
		pAddinMenu->RemoveMenu(2, MF_BYPOSITION);
	}
	
}
void CDynMenuView::OnUpdateOptions(CCmdUI* pCmdUI)
{
	CMenu *pAddinMenu, *pTopMenu;
	pTopMenu = AfxGetMainWnd()->GetMenu();
	pAddinMenu = pTopMenu->GetSubMenu(1);

	switch (pCmdUI->m_nID)
	{
		case ID_EXPAND:pCmdUI->Enable(pAddinMenu->GetMenuItemCount() == 2);
			           break;
		case ID_STANDARD:
			pCmdUI->Enable(pAddinMenu->GetMenuItemCount() != 2);
	}
}

void CDynMenuView::OnBlack() 
{
	// TODO: Add your command handler code here
	
}

void CDynMenuView::OnRed() 
{
	// TODO: Add your command handler code here
	
}
