// MyIeView.cpp : implementation of the CMyIeView class
//

#include "stdafx.h"
#include "MyIe.h"

#include "MyIeDoc.h"
#include "MyIeView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyIeView

IMPLEMENT_DYNCREATE(CMyIeView, CHtmlView)

BEGIN_MESSAGE_MAP(CMyIeView, CHtmlView)
	//{{AFX_MSG_MAP(CMyIeView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
		ON_COMMAND_RANGE(IDC_BUTTON1,IDC_BUTTON6,OnMyAddress)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CHtmlView::OnFilePrint)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyIeView construction/destruction

CMyIeView::CMyIeView()
{
	// TODO: add construction code here
MyAddressStr="http://www.cctv.com";
}

CMyIeView::~CMyIeView()
{
}

BOOL CMyIeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CHtmlView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMyIeView drawing

void CMyIeView::OnDraw(CDC* pDC)
{
	CMyIeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

void CMyIeView::OnInitialUpdate()
{
	CHtmlView::OnInitialUpdate();

	// TODO: This code navigates to a popular spot on the web.
	//  change the code to go where you'd like.
	Navigate2(_T(MyAddressStr),NULL,NULL);
}
void CMyIeView::OnMyAddress(UINT nID)
{
	switch(nID)
	{
	case IDC_BUTTON1:MyAddressStr="http://www.cctv.com";break;
	case IDC_BUTTON2:MyAddressStr="http://www.http://bbs2.sina.com.cn/show.shtml?games:games";break;
    case IDC_BUTTON3:MyAddressStr="http://www.fm365.com";break;
	case IDC_BUTTON4:MyAddressStr="http://www.sports.cctv.com";break;
	case IDC_BUTTON5:MyAddressStr="http://www.music.com";break;
	case IDC_BUTTON6:MyAddressStr="http://www.8848.com";break;
		}
		Navigate2(_T(MyAddressStr),NULL,NULL);
	Refresh();
}
/////////////////////////////////////////////////////////////////////////////
// CMyIeView printing


/////////////////////////////////////////////////////////////////////////////
// CMyIeView diagnostics

#ifdef _DEBUG
void CMyIeView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CMyIeView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}

CMyIeDoc* CMyIeView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyIeDoc)));
	return (CMyIeDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMyIeView message handlers
