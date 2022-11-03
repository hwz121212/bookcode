// Ex09bView.cpp : implementation of the CEx09bView class
//

#include "stdafx.h"
#include "Ex09b.h"

#include "Ex09bDoc.h"
#include "Ex09bView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEx09bView

IMPLEMENT_DYNCREATE(CEx09bView, CView)

BEGIN_MESSAGE_MAP(CEx09bView, CView)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()


BEGIN_EVENTSINK_MAP(CEx09bView, CView)
    ON_EVENT(CEx09bView, ID_BROWSER_SEARCH, 100,            
        OnBeforeNavigateExplorer1, VTS_BSTR VTS_I4 VTS_BSTR 
        VTS_PVARIANT VTS_BSTR VTS_PBOOL)
    ON_EVENT(CEx09bView, ID_BROWSER_TARGET, 113,            
        OnTitleChangeExplorer2, VTS_BSTR)
END_EVENTSINK_MAP()

// CEx09bView construction/destruction

CEx09bView::CEx09bView()
{
	// TODO: add construction code here

}

CEx09bView::~CEx09bView()
{
}

BOOL CEx09bView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CEx09bView drawing

void CEx09bView::OnDraw(CDC* /*pDC*/)
{
	CEx09bDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}


// CEx09bView diagnostics

#ifdef _DEBUG
void CEx09bView::AssertValid() const
{
	CView::AssertValid();
}

void CEx09bView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx09bDoc* CEx09bView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx09bDoc)));
	return (CEx09bDoc*)m_pDocument;
}
#endif //_DEBUG

const char CEx09bView::s_engineGoogle[] = "http://www.google.com/";

// CEx09bView message handlers

int CEx09bView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	DWORD dwStyle = WS_VISIBLE | WS_CHILD;    
    if (m_search.Create(NULL, dwStyle, CRect(0, 0, 100, 100),
                        this, ID_BROWSER_SEARCH) == 0) {
        AfxMessageBox("Unable to create search control!\n");
        return -1;
    }
    m_search.Navigate(s_engineGoogle, NULL, NULL, NULL, NULL);

    if (m_target.Create(NULL, dwStyle, CRect(0, 0, 100, 100),
                        this, ID_BROWSER_TARGET) == 0) {
        AfxMessageBox("Unable to create target control!\n");
        return -1;
    }
    m_target.GoHome(); // as defined in Internet Explorer options


	return 0;
}

void CEx09bView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	CRect rectClient;
    GetClientRect(rectClient);
    CRect rectBrowse(rectClient);
    rectBrowse.right = rectClient.right / 2;
    CRect rectSearch(rectClient);
    rectSearch.left = rectClient.right / 2;

    m_target.put_Width(rectBrowse.right - rectBrowse.left);
    m_target.put_Height(rectBrowse.bottom - rectBrowse.top);
    m_target.UpdateWindow();

    m_search.put_Left(rectSearch.left);
    m_search.put_Width(rectSearch.right - rectSearch.left);
    m_search.put_Height(rectSearch.bottom - rectSearch.top);
    m_search.UpdateWindow();

}

void CEx09bView::OnBeforeNavigateExplorer1(LPCTSTR URL,
    long Flags, LPCTSTR TargetFrameName,
    VARIANT FAR* PostData, LPCTSTR Headers, BOOL FAR* Cancel)
{
    TRACE("CEx09bView::OnBeforeNavigateExplorer1 -- URL = %s\n", URL);

     if (!strnicmp(URL, s_engineGoogle, strlen(s_engineGoogle))) {
        return;
    }
    m_target.Navigate(URL, NULL, NULL, PostData, NULL);
    *Cancel = TRUE;
}

void CEx09bView::OnTitleChangeExplorer2(LPCTSTR Text)
{
    // Careful!  Event could fire before we’re ready.
    CWnd* pWnd = AfxGetApp()->m_pMainWnd;
    if (pWnd != NULL) {
        if (::IsWindow(pWnd->m_hWnd)) {
            pWnd->SetWindowText(Text);
        }
    }
}
