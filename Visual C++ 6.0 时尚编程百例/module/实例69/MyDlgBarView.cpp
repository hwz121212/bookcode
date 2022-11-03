// MyDlgBarView.cpp : implementation of the CMyDlgBarView class
//

#include "stdafx.h"
#include "MyDlgBar.h"

#include "MyDlgBarDoc.h"
#include "MyDlgBarView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyDlgBarView

IMPLEMENT_DYNCREATE(CMyDlgBarView, CView)

BEGIN_MESSAGE_MAP(CMyDlgBarView, CView)
	//{{AFX_MSG_MAP(CMyDlgBarView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
		ON_COMMAND_RANGE(IDC_BUTTON1,IDC_BUTTON4,OnChioce)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyDlgBarView construction/destruction

CMyDlgBarView::CMyDlgBarView()
{	MyBitmap1.LoadBitmap("IDB_BITMAP1U");
   
    MyBitmap2.LoadBitmap("IDB_BITMAP2U");
    MyBitmap3.LoadBitmap("IDB_BITMAP3U");
    MyBitmap4.LoadBitmap("IDB_BITMAP4U");
	MyBitmapID=-1;
	
}

CMyDlgBarView::~CMyDlgBarView()
{
}

BOOL CMyDlgBarView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMyDlgBarView drawing

void CMyDlgBarView::OnDraw(CDC* pDC)
{
	CMyDlgBarDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	int i=LoadMyBitmapID();

    if(i>=0)
	{   
		CRect r;
	    GetClientRect(&r);
	    int x = r.right / 4, y = r.bottom / 2;
		CDC dc;
    	dc.CreateCompatibleDC(pDC);
		
		
		BITMAP bm;
		switch(i)
		{
	    	case 1:MyBitmap1.GetObject(sizeof(BITMAP),&bm);
				   dc.SelectObject(&MyBitmap1);
				   break;
	    	case 2:MyBitmap2.GetObject(sizeof(BITMAP),&bm);
				   dc.SelectObject(&MyBitmap2);x=x/5*6;
				   break;
	    	case 3:MyBitmap3.GetObject(sizeof(BITMAP),&bm); 
				   dc.SelectObject(&MyBitmap3);x=x/5*7;
				   break;
	    	case 4:MyBitmap4.GetObject(sizeof(BITMAP),&bm);
				   dc.SelectObject(&MyBitmap4);x=x/5*8;
				   break;
        }
	    pDC->BitBlt(x,y,bm.bmWidth,bm.bmHeight,&dc,0,0,SRCCOPY);
	
	}
	// TODO: add draw code for native data here


}
void CMyDlgBarView::OnChioce(UINT nID)
{
	switch(nID)
	{
	case IDC_BUTTON1:SetMyBitmapID(1);break;
    case IDC_BUTTON2:SetMyBitmapID(2);break;
	case IDC_BUTTON3:SetMyBitmapID(3);break;
	case IDC_BUTTON4:SetMyBitmapID(4);break;
	}
	Invalidate();
}
void CMyDlgBarView::SetMyBitmapID(int id)
{
	MyBitmapID=id;
}
int CMyDlgBarView::LoadMyBitmapID()
{
	return MyBitmapID;
}
/////////////////////////////////////////////////////////////////////////////
// CMyDlgBarView printing

BOOL CMyDlgBarView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMyDlgBarView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMyDlgBarView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMyDlgBarView diagnostics

#ifdef _DEBUG
void CMyDlgBarView::AssertValid() const
{
	CView::AssertValid();
}

void CMyDlgBarView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyDlgBarDoc* CMyDlgBarView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyDlgBarDoc)));
	return (CMyDlgBarDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyDlgBarView message handlers
