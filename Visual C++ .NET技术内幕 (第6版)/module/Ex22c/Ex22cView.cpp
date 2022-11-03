// Ex22cView.cpp : implementation of the CEx22cView class
//

#include "stdafx.h"
#include "Ex22c.h"

#include "Ex22cDoc.h"
#include "Ex22cView.h"

#include "interface.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEx22cView

// {692D03A4-C689-11CE-B337-88EA36DE9E4E}
static const IID IID_IMotion =
{ 0x692d03a4, 0xc689, 0x11ce, { 0xb3, 0x37, 0x88, 0xea, 0x36, 0xde, 0x9e, 0x4e } };

// {692D03A5-C689-11CE-B337-88EA36DE9E4E}
static const IID IID_IVisual =
{ 0x692d03a5, 0xc689, 0x11ce, { 0xb3, 0x37, 0x88, 0xea, 0x36, 0xde, 0x9e, 0x4e } };


IMPLEMENT_DYNCREATE(CEx22cView, CView)

BEGIN_MESSAGE_MAP(CEx22cView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	ON_COMMAND(ID_TEST_SPACESHIP, OnTestSpaceship)
END_MESSAGE_MAP()

// CEx22cView construction/destruction

CEx22cView::CEx22cView()
{
	// TODO: add construction code here

}

CEx22cView::~CEx22cView()
{
}

BOOL CEx22cView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CEx22cView drawing

void CEx22cView::OnDraw(CDC* /*pDC*/)
{
	CEx22cDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}


// CEx22cView printing

BOOL CEx22cView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CEx22cView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CEx22cView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CEx22cView diagnostics

#ifdef _DEBUG
void CEx22cView::AssertValid() const
{
	CView::AssertValid();
}

void CEx22cView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CEx22cDoc* CEx22cView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx22cDoc)));
	return (CEx22cDoc*)m_pDocument;
}
#endif //_DEBUG


// CEx22cView message handlers

void CEx22cView::OnTestSpaceship()
{
	CLSID clsid;
    LPCLASSFACTORY pClf; 
    LPUNKNOWN pUnk;
    IMotion* pMot;
    IVisual* pVis;
    
    HRESULT hr;
    if ((hr = ::CLSIDFromProgID(L"Ex22b.Spaceship", &clsid)) != NOERROR) {
        TRACE("unable to find Program ID -- error = %x\n", hr);
        return;
    }
    if ((hr = ::CoGetClassObject(clsid, CLSCTX_INPROC_SERVER,
        NULL, IID_IClassFactory, (void **) &pClf)) != NOERROR) {
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
