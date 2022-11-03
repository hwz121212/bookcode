// FormColorView.cpp : implementation of the CFormColorView class
//

#include "stdafx.h"
#include "FormColor.h"

#include "FormColorDoc.h"
#include "FormColorView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFormColorView

IMPLEMENT_DYNCREATE(CFormColorView, CFormView)

BEGIN_MESSAGE_MAP(CFormColorView, CFormView)
	//{{AFX_MSG_MAP(CFormColorView)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
	ON_COMMAND_RANGE(IDC_RADIO1,IDC_RADIO3,OnChioce)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFormColorView construction/destruction

CFormColorView::CFormColorView()
	: CFormView(CFormColorView::IDD)
{
	//{{AFX_DATA_INIT(CFormColorView)
	m_string = _T("VC++°ÙÀý");
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CFormColorView::~CFormColorView()
{
}

void CFormColorView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFormColorView)
	DDX_Text(pDX, IDC_EDIT1, m_string);
	//}}AFX_DATA_MAP
}

BOOL CFormColorView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CFormColorView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}

/////////////////////////////////////////////////////////////////////////////
// CFormColorView printing

BOOL CFormColorView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CFormColorView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CFormColorView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CFormColorView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}
void CFormColorView::OnChioce(UINT nID)
{
	
	switch(nID)
	{
	case IDC_RADIO1:m_pColor=RGB(255,0,0);break;
	case IDC_RADIO2:m_pColor=RGB(0,0,255);break;
	case IDC_RADIO3:m_pColor=RGB(0,255,0);break;
	}

	CWnd * pWnd = GetDlgItem(IDC_EDIT1);

	pWnd->Invalidate();
}
/////////////////////////////////////////////////////////////////////////////
// CFormColorView diagnostics

#ifdef _DEBUG
void CFormColorView::AssertValid() const
{
	CFormView::AssertValid();
}

void CFormColorView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CFormColorDoc* CFormColorView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFormColorDoc)));
	return (CFormColorDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CFormColorView message handlers

HBRUSH CFormColorView::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = CFormView::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO: Change any attributes of the DC here
	if( GetDlgItem(IDC_EDIT1)->m_hWnd == pWnd->m_hWnd)
	{
	//		CFormColorDoc * pDoc = (CFormColorDoc *)GetDocument();
		
    pDC->SetTextColor(m_pColor);
				}
	// TODO: Return a different brush if the default is not desired
	return hbr;
}
