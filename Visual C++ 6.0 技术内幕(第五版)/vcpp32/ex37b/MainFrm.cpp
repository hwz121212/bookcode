// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "ex37b.h"

#include "MainFrm.h"
#include "LeftView.h"
#include "ex37bView.h"

#include <mshtml.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	return 0;
}

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/,
	CCreateContext* pContext)
{
	// create splitter window
	if (!m_wndSplitter.CreateStatic(this, 1, 2))
		return FALSE;

	if (!m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CLeftView), CSize(100, 100), pContext) ||
		!m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CEx37bView), CSize(100, 100), pContext))
	{
		m_wndSplitter.DestroyWindow();
		return FALSE;
	}

	return TRUE;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics
void CMainFrame::DoDHTMLExplore(void)
{

	CLeftView *pListView = 
		(CLeftView *)m_wndSplitter.GetPane(0,0);

	CEx37bView * pDHTMLView = 
		(CEx37bView *)m_wndSplitter.GetPane(0,1);

    pListView->GetListCtrl().DeleteAllItems(); //Clear the view and set it up in single mode.
	
	IDispatch* pDisp = pDHTMLView->GetHtmlDocument();
	
	if (pDisp != NULL )
	{
	  IHTMLDocument2* pHTMLDocument2;
	  HRESULT hr;
	  hr = pDisp->QueryInterface( IID_IHTMLDocument2, (void**)&pHTMLDocument2 );
	  if (hr == S_OK)
	  {
         IHTMLElementCollection* pColl = NULL;
		  hr = pHTMLDocument2->get_all( &pColl );
			if (hr == S_OK && pColl != NULL)
			{
				LONG celem;
				hr = pColl->get_length( &celem );

				if ( hr == S_OK )
				{
					for ( int i=0; i< celem; i++ )
					{
						VARIANT varIndex;
						varIndex.vt = VT_UINT;
						varIndex.lVal = i;
						VARIANT var2;
						VariantInit( &var2 );
						IDispatch* pDisp; 

						hr = pColl->item( varIndex, var2, &pDisp );

						if ( hr == S_OK )
						{

							IHTMLElement* pElem;

							hr = pDisp->QueryInterface( IID_IHTMLElement, (void **)&pElem );
							if ( hr == S_OK )
							{

								BSTR bstr;
								hr = pElem->get_tagName(&bstr);
								CString strTag = bstr;

								IHTMLImgElement* pImgElem;

								//Is it an image element?
								hr = pDisp->QueryInterface( IID_IHTMLImgElement, (void **)&pImgElem );
								if ( hr == S_OK )
								{
									pImgElem->get_href(&bstr);
									strTag += " - ";
									strTag += bstr;
									pImgElem->Release();
								}
								else
								{
									IHTMLAnchorElement* pAnchElem;
									//Is it an anchor?
									hr = pDisp->QueryInterface( IID_IHTMLAnchorElement, (void **)&pAnchElem );
									if ( hr == S_OK )
									{
										pAnchElem->get_href(&bstr);
										strTag += " - ";
										strTag += bstr;
										pAnchElem->Release();
									}
								}
								pListView->GetListCtrl().InsertItem(
								pListView->GetListCtrl().GetItemCount(),strTag);
								pElem->Release();
							}
							pDisp->Release();
						}
					}
				}

				pColl->Release();
			}
			pHTMLDocument2->Release();
		}
		pDisp->Release();
	}
}

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

