// ex24cView.cpp : implementation of the CEx24cView class
//

#include "stdafx.h"
#include "ex24c.h"

#include "ex24cDoc.h"
#include "ex24cView.h"
#include "Interface.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


// {692D03A4-C689-11CE-B337-88EA36DE9E4E}
static const IID IID_IMotion =
{ 0x692d03a4, 0xc689, 0x11ce, { 0xb3, 0x37, 0x88, 0xea, 0x36, 0xde, 0x9e, 0x4e } };

// {692D03A5-C689-11CE-B337-88EA36DE9E4E}
static const IID IID_IVisual =
{ 0x692d03a5, 0xc689, 0x11ce, { 0xb3, 0x37, 0x88, 0xea, 0x36, 0xde, 0x9e, 0x4e } };

/////////////////////////////////////////////////////////////////////////////
// CEx24cView

IMPLEMENT_DYNCREATE(CEx24cView, CView)

BEGIN_MESSAGE_MAP(CEx24cView, CView)
	//{{AFX_MSG_MAP(CEx24cView)
	ON_COMMAND(ID_TEST_SPACESHIP, OnTestSpaceship)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx24cView construction/destruction

CEx24cView::CEx24cView()
{
	// TODO: add construction code here

}

CEx24cView::~CEx24cView()
{
}

BOOL CEx24cView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CEx24cView drawing

void CEx24cView::OnDraw(CDC* pDC)
{
	CEx24cDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CEx24cView diagnostics

#ifdef _DEBUG
void CEx24cView::AssertValid() const
{
	CView::AssertValid();
}

void CEx24cView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx24cDoc* CEx24cView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx24cDoc)));
	return (CEx24cDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx24cView message handlers

void CEx24cView::OnTestSpaceship() 
{
    CLSID clsid;
    LPCLASSFACTORY pClf; 
    LPUNKNOWN pUnk;
    IMotion* pMot;
    IVisual* pVis;
    HRESULT hr;

    if ((hr = ::CLSIDFromProgID(L"Spaceship", &clsid)) != NOERROR) {
        TRACE("unable to find Program ID -- error = %x\n", hr);
        return;
    }
    if ((hr = ::CoGetClassObject(clsid, CLSCTX_INPROC_SERVER,
        NULL, IID_IClassFactory, (void **) &pClf)) != NOERROR) {;
        TRACE("unable to find CLSID -- error = %x\n", hr);
        return;
    }

    pClf->CreateInstance(NULL, IID_IUnknown, (void**) &pUnk);
    pUnk->QueryInterface(IID_IMotion, (void**) &pMot); // All three
    pMot->QueryInterface(IID_IVisual, (void**) &pVis); //  pointers
                                                       //  should work
    TRACE("main: pUnk = %p, pMot = %p, pDis = %p\n", pUnk, pMot, pVis);
    
    // Test all the interface virtual functions
    pMot->Fly();
    int nPos = pMot->GetPosition();
    TRACE("nPos = %d\n", nPos);
    pVis->Display();

    pClf->Release();
    pUnk->Release();
    pMot->Release();
    pVis->Release();
    AfxMessageBox("Test succeeded. See Debug window for output.");
}
