// ModellessView.cpp : implementation of the CModellessView class
//

#include "stdafx.h"
#include "Modelless.h"

#include "ModellessDoc.h"
#include "ModellessView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModellessView

IMPLEMENT_DYNCREATE(CModellessView, CView)

BEGIN_MESSAGE_MAP(CModellessView, CView)
	//{{AFX_MSG_MAP(CModellessView)
	ON_COMMAND(ID_MODELLESS, OnModelless)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModellessView construction/destruction

CModellessView::CModellessView()
{
	// TODO: add construction code here
	m_pModelless=NULL;//初始化指针
}

CModellessView::~CModellessView()
{
	// TODO: add construction code here
	//判断是否分配了内存,如果是便释放
	if(m_pModelless!=NULL)
	{
		delete m_pModelless;
	}
}

BOOL CModellessView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CModellessView drawing

void CModellessView::OnDraw(CDC* pDC)
{
	CModellessDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CModellessView printing

BOOL CModellessView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CModellessView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CModellessView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CModellessView diagnostics

#ifdef _DEBUG
void CModellessView::AssertValid() const
{
	CView::AssertValid();
}

void CModellessView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CModellessDoc* CModellessView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CModellessDoc)));
	return (CModellessDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CModellessView message handlers

void CModellessView::OnModelless() 
{
	// TODO: add cleanup after printing
	//判断指针是否为NULL,如果为NULL,说明对话框没有创建,则动态创建对话框
	if(m_pModelless==NULL)
	{
		m_pModelless=new CModellessDialog();
		m_pModelless->Create(IDD_DIALOG1,this);
	}
	//显示对话框
	m_pModelless->ShowWindow(SW_SHOW);
}
