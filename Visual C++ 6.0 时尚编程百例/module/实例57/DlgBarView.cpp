// DlgBarView.cpp : implementation of the CDlgBarView class
//

#include "stdafx.h"
#include "DlgBar.h"

#include "DlgBarDoc.h"
#include "DlgBarView.h"
#include "MainFrm.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgBarView

IMPLEMENT_DYNCREATE(CDlgBarView, CView)

BEGIN_MESSAGE_MAP(CDlgBarView, CView)
	//{{AFX_MSG_MAP(CDlgBarView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
		ON_COMMAND(IDOK,OnButtonClicked)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgBarView construction/destruction

CDlgBarView::CDlgBarView()
{
	// TODO: add construction code here

}

CDlgBarView::~CDlgBarView()
{
}

BOOL CDlgBarView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDlgBarView drawing

void CDlgBarView::OnDraw(CDC* pDC)
{
	CDlgBarDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}
void CDlgBarView::OnButtonClicked()
{
	CString Bmpname;
    CMainFrame *pw=(CMainFrame *)AfxGetMainWnd();
	CDialogBar *pb=pw->GetDialogBar();
	pb->GetDlgItemText(IDC_MYEDIT,Bmpname);
	ShowBitmap(Bmpname);

}
void CDlgBarView::ShowBitmap(CString  Bmpname)
{
	CBitmap m_bitmap;
    CDC *pDC=GetDC();
    HBITMAP hBitmap = (HBITMAP) LoadImage(NULL, _T(Bmpname), IMAGE_BITMAP,
                    0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
              
              m_bitmap.Attach(hBitmap);     
		
	CDC dcImage;
	if (!dcImage.CreateCompatibleDC(pDC))
		return;

	BITMAP bm;
	m_bitmap.GetBitmap(&bm);
	// show the image.
	CBitmap* pOldBitmap = dcImage.SelectObject(&m_bitmap);
	pDC->BitBlt(0, 0, bm.bmWidth, bm.bmHeight, &dcImage, 0, 0, SRCCOPY);
	dcImage.SelectObject(pOldBitmap);
	

}
/////////////////////////////////////////////////////////////////////////////

// CDlgBarView printing

BOOL CDlgBarView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDlgBarView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDlgBarView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CDlgBarView diagnostics

#ifdef _DEBUG
void CDlgBarView::AssertValid() const
{
	CView::AssertValid();
}

void CDlgBarView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDlgBarDoc* CDlgBarView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDlgBarDoc)));
	return (CDlgBarDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDlgBarView message handlers
