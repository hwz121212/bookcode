// ex28bDoc.cpp : implementation of the CEx28bDoc class
//

#include "stdafx.h"
#include "ex28b.h"

#include "ex28bDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
const OLECHAR* CEx28bDoc::s_szSub = L"sub";   // static                                       ";

/////////////////////////////////////////////////////////////////////////////
// CEx28bDoc

IMPLEMENT_DYNCREATE(CEx28bDoc, CDocument)

BEGIN_MESSAGE_MAP(CEx28bDoc, CDocument)
	//{{AFX_MSG_MAP(CEx28bDoc)
	ON_COMMAND(ID_EDIT_CLEAR_ALL, OnEditClearAll)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_INTERFACE_MAP(CEx28bDoc, CDocument)
	INTERFACE_PART(CEx28bDoc, IID_IOleClientSite, OleClientSite)
	INTERFACE_PART(CEx28bDoc, IID_IAdviseSink, AdviseSink)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// Implementation of IOleClientSite

STDMETHODIMP_(ULONG) CEx28bDoc::XOleClientSite::AddRef()
{
	TRACE("CEx28bDoc::XOleClientSite::AddRef\n");
	METHOD_PROLOGUE(CEx28bDoc, OleClientSite)
	return pThis->InternalAddRef();
}

STDMETHODIMP_(ULONG) CEx28bDoc::XOleClientSite::Release()
{
	TRACE("CEx28bDoc::XOleClientSite::Release\n");
	METHOD_PROLOGUE(CEx28bDoc, OleClientSite)
	return pThis->InternalRelease();
}

STDMETHODIMP CEx28bDoc::XOleClientSite::QueryInterface(
	REFIID iid, LPVOID* ppvObj)
{
	ITrace(iid, "CEx28bDoc::XOleClientSite::QueryInterface");
	METHOD_PROLOGUE(CEx28bDoc, OleClientSite)
	return pThis->InternalQueryInterface(&iid, ppvObj);
}

STDMETHODIMP CEx28bDoc::XOleClientSite::SaveObject()
{
	TRACE("CEx28bDoc::XOleClientSite::SaveObject\n");
	METHOD_PROLOGUE(CEx28bDoc, OleClientSite)
	ASSERT_VALID(pThis);

	LPPERSISTSTORAGE lpPersistStorage;
	pThis->m_lpOleObj->QueryInterface(IID_IPersistStorage, 
		(void**) &lpPersistStorage);
	ASSERT(lpPersistStorage != NULL);
	HRESULT hr = NOERROR;
	if (lpPersistStorage->IsDirty() == NOERROR)
	{
		// NOERROR == S_OK != S_FALSE, therefore object is dirty!
		hr = ::OleSave(lpPersistStorage, pThis->m_pTempStgSub, TRUE);
		if (hr != NOERROR)
			hr = lpPersistStorage->SaveCompleted(NULL);

		// Mark the document as dirty, if save successful
		pThis->SetModifiedFlag();
	}
	lpPersistStorage->Release();
	pThis->UpdateAllViews(NULL);
	return hr;
}

STDMETHODIMP CEx28bDoc::XOleClientSite::GetMoniker(
	DWORD dwAssign, DWORD dwWhichMoniker, LPMONIKER* ppMoniker)
{
	TRACE("CEx28bDoc::XOleClientSite::GetMoniker\n");
	return E_NOTIMPL;
}

STDMETHODIMP CEx28bDoc::XOleClientSite::GetContainer(
	LPOLECONTAINER* ppContainer)
{
	TRACE("CEx28bDoc::XOleClientSite::GetContainer\n");
	return E_NOTIMPL;
}

STDMETHODIMP CEx28bDoc::XOleClientSite::ShowObject()
{
	TRACE("CEx28bDoc::XOleClientSite::ShowObject\n");
	METHOD_PROLOGUE(CEx28bDoc, OleClientSite)
	ASSERT_VALID(pThis);
	pThis->UpdateAllViews(NULL);
	return NOERROR;
}

STDMETHODIMP CEx28bDoc::XOleClientSite::OnShowWindow(BOOL fShow)
{
	TRACE("CEx28bDoc::XOleClientSite::OnShowWindow\n");
	METHOD_PROLOGUE(CEx28bDoc, OleClientSite)
	ASSERT_VALID(pThis);
	pThis->m_bHatch = fShow;
	pThis->UpdateAllViews(NULL);
	return NOERROR;
}

STDMETHODIMP CEx28bDoc::XOleClientSite::RequestNewObjectLayout()
{
	TRACE("CEx28bDoc::XOleClientSite::RequestNewObjectLayout\n");
	return E_NOTIMPL;
}

/////////////////////////////////////////////////////////////////////////////
// Implementation of IAdviseSink

STDMETHODIMP_(ULONG) CEx28bDoc::XAdviseSink::AddRef()
{
	TRACE("CEx28bDoc::XAdviseSink::AddRef\n");
	METHOD_PROLOGUE(CEx28bDoc, AdviseSink)
	return pThis->InternalAddRef();
}

STDMETHODIMP_(ULONG) CEx28bDoc::XAdviseSink::Release()
{
	TRACE("CEx28bDoc::XAdviseSink::Release\n");
	METHOD_PROLOGUE(CEx28bDoc, AdviseSink)
	return pThis->InternalRelease();
}

STDMETHODIMP CEx28bDoc::XAdviseSink::QueryInterface(
	REFIID iid, LPVOID* ppvObj)
{
	ITrace(iid, "CEx28bDoc::XAdviseSink::QueryInterface");
	METHOD_PROLOGUE(CEx28bDoc, AdviseSink)
	return pThis->InternalQueryInterface(&iid, ppvObj);
}

STDMETHODIMP_(void) CEx28bDoc::XAdviseSink::OnDataChange(
	LPFORMATETC lpFormatEtc, LPSTGMEDIUM lpStgMedium)
{
	TRACE("CEx28bDoc::XAdviseSink::OnDataChange\n");
	METHOD_PROLOGUE(CEx28bDoc, AdviseSink)
	ASSERT_VALID(pThis);

	// Interesting only for advanced containers.  Forward it such that
	//  containers do not have to implement the entire interface.
}

STDMETHODIMP_(void) CEx28bDoc::XAdviseSink::OnViewChange(
	DWORD aspects, LONG /*lindex*/)
{
	TRACE("CEx28bDoc::XAdviseSink::OnViewChange\n");
	METHOD_PROLOGUE(CEx28bDoc, AdviseSink)
	ASSERT_VALID(pThis);

	pThis->UpdateAllViews(NULL);	// the really important one
}

STDMETHODIMP_(void) CEx28bDoc::XAdviseSink::OnRename(
	LPMONIKER /*lpMoniker*/)
{
	TRACE("CEx28bDoc::XAdviseSink::OnRename\n");
	// Interesting only to the OLE link object. Containers ignore this.
}

STDMETHODIMP_(void) CEx28bDoc::XAdviseSink::OnSave()
{
	TRACE("CEx28bDoc::XAdviseSink::OnSave\n");
	METHOD_PROLOGUE(CEx28bDoc, AdviseSink)
	ASSERT_VALID(pThis);

	pThis->UpdateAllViews(NULL);
}

STDMETHODIMP_(void) CEx28bDoc::XAdviseSink::OnClose()
{
	TRACE("CEx28bDoc::XAdviseSink::OnClose\n");
	METHOD_PROLOGUE(CEx28bDoc, AdviseSink)
	ASSERT_VALID(pThis);

	pThis->UpdateAllViews(NULL);
}

/////////////////////////////////////////////////////////////////////////////
// CEx28bDoc construction/destruction

CEx28bDoc::CEx28bDoc()
{
	m_lpOleObj = NULL;
	m_pTempStgRoot = NULL;
	m_pTempStgSub = NULL;
	m_bHatch = FALSE;
}

CEx28bDoc::~CEx28bDoc()
{
}

BOOL CEx28bDoc::OnNewDocument()
{
	TRACE("Entering CEx28bDoc::OnNewDocument\n");
	// Create a structured storage home for the object (m_pTempStgSub).
	//  This is a temporary file -- random name supplied by OLE.
	VERIFY(::StgCreateDocfile(NULL,
		STGM_READWRITE|STGM_SHARE_EXCLUSIVE|STGM_CREATE|
		STGM_DELETEONRELEASE,
		0, &m_pTempStgRoot) == S_OK);
	ASSERT(m_pTempStgRoot!= NULL);
	
    VERIFY(m_pTempStgRoot->CreateStorage(OLESTR("sub"),
    	   STGM_CREATE|STGM_READWRITE|STGM_SHARE_EXCLUSIVE,
    	   0, 0, &m_pTempStgSub) == S_OK);
	ASSERT(m_pTempStgSub != NULL);
	return CDocument::OnNewDocument();
}

/////////////////////////////////////////////////////////////////////////////
// CEx28bDoc serialization

void CEx28bDoc::Serialize(CArchive& ar)
{
	// no hookup to MFC serialization
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CEx28bDoc diagnostics

#ifdef _DEBUG
void CEx28bDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx28bDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx28bDoc commands

void CEx28bDoc::OnCloseDocument() 
{
	m_pTempStgSub->Release(); // must release BEFORE calling base class
	m_pTempStgRoot->Release();
	CDocument::OnCloseDocument();
}

void CEx28bDoc::DeleteContents() 
{
	if(m_lpOleObj != NULL) {
	   // If object is running, close it, which releases our IOleClientSite
		m_lpOleObj->Close(OLECLOSE_NOSAVE);
		m_lpOleObj->Release(); // should be final release (or else..)
		m_lpOleObj = NULL;
	}
}

void CEx28bDoc::OnEditClearAll() 
{
    DeleteContents();
    UpdateAllViews(NULL);
    SetModifiedFlag();
	m_bHatch = FALSE;
}

BOOL CEx28bDoc::SaveModified() 
{
	// Eliminate "save to file" message
	return TRUE;
}

void ITrace(REFIID iid, const char* str)
{
	OLECHAR* lpszIID;
	::StringFromIID(iid, &lpszIID);
	CString strIID = lpszIID;
	TRACE("%s - %s\n", (const char*) strIID, (const char*) str);
	AfxFreeTaskMem(lpszIID);
}
