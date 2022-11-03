// AVIView.cpp : implementation of the CAVIView class
//

#include "stdafx.h"
#include "AVI.h"

#include "AVIDoc.h"
#include "AVIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAVIView

IMPLEMENT_DYNCREATE(CAVIView, CView)

BEGIN_MESSAGE_MAP(CAVIView, CView)
	//{{AFX_MSG_MAP(CAVIView)
	ON_COMMAND(ID_AVI, OnAvi)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAVIView construction/destruction

CAVIView::CAVIView()
{
	m_hwndMCI=NULL;
}

CAVIView::~CAVIView()
{
}

BOOL CAVIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CAVIView drawing

void CAVIView::OnDraw(CDC* pDC)
{
	CAVIDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CAVIView printing

BOOL CAVIView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CAVIView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CAVIView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CAVIView diagnostics

#ifdef _DEBUG
void CAVIView::AssertValid() const
{
	CView::AssertValid();
}

void CAVIView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAVIDoc* CAVIView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAVIDoc)));
	return (CAVIDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAVIView message handlers

void CAVIView::OnAvi() 
{
	CString filename;
	//��һ�����ļ���ͨ�öԻ�������ѡ��AVI�ļ�
	CFileDialog dlg(TRUE,"avi",NULL,
		            OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
					"AVI�ļ�(*.avi)|*.avi||");
	if(dlg.DoModal()==IDOK)
	{
		filename=dlg.GetPathName();   //�õ��ļ���
		//�ж��Ƿ��Ѿ�����һ��MCIWnd����,�����,����ر�
		if(m_hwndMCI!=NULL)
			MCIWndDestroy(m_hwndMCI);
		//����һ��MCIWnd����
		m_hwndMCI=MCIWndCreate(m_hWnd,AfxGetInstanceHandle(),0,filename);
	}	
}
