// ex28cDoc.cpp : implementation of the CEx28cDoc class
//

#include "stdafx.h"
#include "ex28c.h"

#include "ex28cDoc.h"
#include "TextDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx28cDoc

IMPLEMENT_DYNCREATE(CEx28cDoc, CDocument)

BEGIN_INTERFACE_MAP(CEx28cDoc, CDocument)
	INTERFACE_PART(CEx28cDoc, IID_IOleObject, OleObject)
	INTERFACE_PART(CEx28cDoc, IID_IDataObject, DataObject)
	INTERFACE_PART(CEx28cDoc, IID_IPersistStorage, PersistStorage)
END_INTERFACE_MAP()

BEGIN_MESSAGE_MAP(CEx28cDoc, CDocument)
	//{{AFX_MSG_MAP(CEx28cDoc)
	ON_COMMAND(ID_MODIFY, OnModify)
	ON_COMMAND(ID_FILE_UPDATE, OnFileUpdate)
	ON_UPDATE_COMMAND_UI(ID_FILE_UPDATE, OnUpdateFileUpdate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// CEx28cDoc OLE interface functions
STDMETHODIMP_(ULONG) CEx28cDoc::XOleObject::AddRef()
{
	TRACE("CEx28cDoc::XOleObject::AddRef\n");
	METHOD_PROLOGUE(CEx28cDoc, OleObject)
	return pThis->InternalAddRef();
}

STDMETHODIMP_(ULONG) CEx28cDoc::XOleObject::Release()
{
	TRACE("CEx28cDoc::XOleObject::Release\n");
	METHOD_PROLOGUE(CEx28cDoc, OleObject)
	return pThis->InternalRelease();
}

STDMETHODIMP CEx28cDoc::XOleObject::QueryInterface(
	REFIID iid, LPVOID* ppvObj)
{
	ITrace(iid, "CEx28cDoc::XOleObject::QueryInterface");
	METHOD_PROLOGUE(CEx28cDoc, OleObject)
	return pThis->InternalQueryInterface(&iid, ppvObj);
}

STDMETHODIMP CEx28cDoc::XOleObject::SetClientSite(
	LPOLECLIENTSITE pClientSite)
{
	TRACE("CEx28cDoc::XOleObject::SetClientSite\n");
	METHOD_PROLOGUE(CEx28cDoc, OleObject)
	// linked objects do not support SetClientSite
	if (pClientSite != NULL)
		pClientSite->AddRef();
	if(pThis->m_lpClientSite != NULL) pThis->m_lpClientSite->Release();
	pThis->m_lpClientSite = pClientSite;

	return NOERROR;
}

STDMETHODIMP CEx28cDoc::XOleObject::GetClientSite(
	LPOLECLIENTSITE* ppClientSite)
{
	TRACE("CEx28cDoc::XOleObject::GetClientSite\n");
	METHOD_PROLOGUE(CEx28cDoc, OleObject)

	*ppClientSite = pThis->m_lpClientSite;
        if (pThis->m_lpClientSite != NULL)
                pThis->m_lpClientSite->AddRef();  // IMPORTANT
	return NOERROR;
}

STDMETHODIMP CEx28cDoc::XOleObject::SetHostNames(
	LPCOLESTR szContainerApp, LPCOLESTR szContainerObj)
{
	TRACE("CEx28cDoc::XOleObject::SetHostNames\n");
	METHOD_PROLOGUE(CEx28cDoc, OleObject)
	
	CString strTitle = "EX28C object embedded in ";
	if(szContainerApp != NULL) {
		strTitle += CString(szContainerApp);
	}
	CWnd* pWnd = AfxGetMainWnd();
	pWnd->SetWindowText(strTitle);
	
	return NOERROR;
}

STDMETHODIMP CEx28cDoc::XOleObject::Close(DWORD /*dwSaveOption*/)
{
	TRACE("CEx28cDoc::XOleObject::Close\n");
	// linked objects do not support close

	return E_NOTIMPL;
}

STDMETHODIMP CEx28cDoc::XOleObject::SetMoniker(
	DWORD /*dwWhichMoniker*/, LPMONIKER /*pmk*/)
{
	TRACE("CEx28cDoc::XOleObject::SetMoniker\n");
	// linked objects do not support SetMoniker

	return E_NOTIMPL;
}

STDMETHODIMP CEx28cDoc::XOleObject::GetMoniker(
	DWORD dwAssign, DWORD dwWhichMoniker, LPMONIKER* ppMoniker)
{
	TRACE("CEx28cDoc::XOleObject::GetMoniker\n");
	return E_NOTIMPL;
}

STDMETHODIMP CEx28cDoc::XOleObject::InitFromData(
	LPDATAOBJECT /*pDataObject*/, BOOL /*fCreation*/, DWORD /*dwReserved*/)
{
	TRACE("CEx28cDoc::XOleObject::InitFromData\n");
	// linked objects do not support InitFromData

	return E_NOTIMPL;
}

STDMETHODIMP CEx28cDoc::XOleObject::GetClipboardData(
	DWORD /*dwReserved*/, LPDATAOBJECT* ppDataObject)
{
	TRACE("CEx28cDoc::XOleObject::GetClipboardData\n");
	return E_NOTIMPL;
}

STDMETHODIMP CEx28cDoc::XOleObject::DoVerb(
	LONG iVerb, LPMSG lpmsg, LPOLECLIENTSITE pActiveSite, LONG lindex,
	HWND hwndParent, LPCRECT lpPosRect)
{										 
	TRACE("CEx28cDoc::XOleObject::DoVerb - %d\n", iVerb);
	METHOD_PROLOGUE(CEx28cDoc, OleObject)
	ASSERT_VALID(pThis);

	pThis->InternalAddRef();    // protect this object
	CWnd* pWnd = AfxGetMainWnd();
	switch (iVerb)
	{
	// open - maps to OnOpen
	case OLEIVERB_OPEN:
	case -OLEIVERB_OPEN-1:  // allows positive OLEIVERB_OPEN-1 in registry
	case OLEIVERB_PRIMARY:  // OLEIVERB_PRIMARY is 0 and "Edit" in registry
	case OLEIVERB_SHOW:
		pWnd->ShowWindow(SW_SHOW);
		pWnd->SetActiveWindow();
		pWnd->SetForegroundWindow();
		break;

	// hide maps to OnHide
	case OLEIVERB_HIDE:
	case -OLEIVERB_HIDE-1:  // allows positive OLEIVERB_HIDE-1 in registry
		return E_NOTIMPL;
		
	default:
		// negative verbs not understood should return E_NOTIMPL
		if (iVerb < 0)
			return E_NOTIMPL;

		AfxThrowOleException(OLEOBJ_S_INVALIDVERB);
	}
	pThis->InternalRelease();   // may 'delete this'
	pThis->m_lpClientSite->OnShowWindow(TRUE); // hatch

	return NOERROR;
}

STDMETHODIMP CEx28cDoc::XOleObject::EnumVerbs(
	IEnumOLEVERB** ppenumOleVerb)
{
	TRACE("CEx28cDoc::XOleObject::EnumVerbs\n");
	return E_NOTIMPL;
}

STDMETHODIMP CEx28cDoc::XOleObject::Update()
{
	TRACE("CEx28cDoc::XOleObject::Update\n");
	METHOD_PROLOGUE(CEx28cDoc, OleObject)
	return E_NOTIMPL;
}

STDMETHODIMP CEx28cDoc::XOleObject::IsUpToDate()
{
	TRACE("CEx28cDoc::XOleObject::IsUpToDate\n");
	return E_NOTIMPL;
}

STDMETHODIMP CEx28cDoc::XOleObject::GetUserClassID(CLSID* pClsid)
{
	TRACE("CEx28cDoc::XOleObject::GetUserClassID\n");
	METHOD_PROLOGUE(CEx28cDoc, OleObject)
	ASSERT_VALID(pThis);

	return pThis->m_xPersistStorage.GetClassID(pClsid);
}

STDMETHODIMP CEx28cDoc::XOleObject::GetUserType(
	DWORD dwFormOfType, LPOLESTR* ppszUserType)
{
	TRACE("CEx28cDoc::XOleObject::GetUserType\n");
	METHOD_PROLOGUE(CEx28cDoc, OleObject)
	ASSERT_VALID(pThis);

	*ppszUserType = NULL;

	CLSID clsid;
	pThis->m_xOleObject.GetUserClassID(&clsid);
	return OleRegGetUserType(clsid, dwFormOfType, ppszUserType);
}

STDMETHODIMP CEx28cDoc::XOleObject::SetExtent(
	DWORD /*dwDrawAspect*/, LPSIZEL /*lpsizel*/)
{
	TRACE("CEx28cDoc::XOleObject::SetExtent\n");
	return E_FAIL;
}

STDMETHODIMP CEx28cDoc::XOleObject::GetExtent(
	DWORD dwDrawAspect, LPSIZEL lpsizel)
{
	TRACE("CEx28cDoc::XOleObject::GetExtent\n");
	METHOD_PROLOGUE(CEx28cDoc, OleObject)
	ASSERT_VALID(pThis);
	// handler returns extent in metafilepict
	return E_NOTIMPL;
}

STDMETHODIMP CEx28cDoc::XOleObject::Advise(
	IAdviseSink* pAdvSink, DWORD* pdwConnection)
{
	TRACE("CEx28cDoc::XOleObject::Advise\n");
	METHOD_PROLOGUE(CEx28cDoc, OleObject)
	ASSERT_VALID(pThis);
	*pdwConnection = 0;
	if (pThis->m_lpOleAdviseHolder == NULL &&
		::CreateOleAdviseHolder(&pThis->m_lpOleAdviseHolder) 
		!= NOERROR) {
		return E_OUTOFMEMORY;
	}
	ASSERT(pThis->m_lpOleAdviseHolder != NULL);
	return pThis->m_lpOleAdviseHolder->Advise(pAdvSink, pdwConnection);
}

STDMETHODIMP CEx28cDoc::XOleObject::Unadvise(DWORD dwConnection)
{
	TRACE("CEx28cDoc::XOleObject::Unadvise\n");
	METHOD_PROLOGUE(CEx28cDoc, OleObject)
	ASSERT_VALID(pThis);
	return E_NOTIMPL;
}

STDMETHODIMP CEx28cDoc::XOleObject::EnumAdvise(
	LPENUMSTATDATA* ppenumAdvise)
{
	TRACE("CEx28cDoc::XOleObject::EnumAdvise\n");
	METHOD_PROLOGUE(CEx28cDoc, OleObject)
	ASSERT_VALID(pThis);
	return E_NOTIMPL;
}

STDMETHODIMP CEx28cDoc::XOleObject::GetMiscStatus(
	DWORD dwAspect, DWORD* pdwStatus)
{
	TRACE("CEx28cDoc::XOleObject::GetMiscStatus\n");
	METHOD_PROLOGUE(CEx28cDoc, OleObject)
	ASSERT_VALID(pThis);

	*pdwStatus = 0;

	CLSID clsid;
	pThis->m_xOleObject.GetUserClassID(&clsid);
	return OleRegGetMiscStatus(clsid, dwAspect, pdwStatus);
}

STDMETHODIMP CEx28cDoc::XOleObject::SetColorScheme(LPLOGPALETTE lpLogpal)
{
	TRACE("CEx28cDoc::XOleObject::SetColorScheme\n");
	METHOD_PROLOGUE(CEx28cDoc, OleObject)
	ASSERT_VALID(pThis);

	return E_NOTIMPL;
}

/////////////////////////////////////////////////////////////////////////////
// CEx28cDoc::XDataObject
// delegate many calls to embedded COleDataSource object, which manages formats

STDMETHODIMP_(ULONG) CEx28cDoc::XDataObject::AddRef()
{
	TRACE("CEx28cDoc::XDataObject::AddRef\n");
	METHOD_PROLOGUE(CEx28cDoc, DataObject)
	return pThis->InternalAddRef();
}

STDMETHODIMP_(ULONG) CEx28cDoc::XDataObject::Release()
{
	TRACE("CEx28cDoc::XDataObject::Release\n");
	METHOD_PROLOGUE(CEx28cDoc, DataObject)
	return pThis->InternalRelease();
}

STDMETHODIMP CEx28cDoc::XDataObject::QueryInterface(
	REFIID iid, LPVOID* ppvObj)
{
	ITrace(iid, "CEx28cDoc::XDataObject::QueryInterface");
	METHOD_PROLOGUE(CEx28cDoc, DataObject)
	return pThis->InternalQueryInterface(&iid, ppvObj);
}

STDMETHODIMP CEx28cDoc::XDataObject::GetData(
	LPFORMATETC lpFormatEtc, LPSTGMEDIUM lpStgMedium)
{
	TRACE("CEx28cDoc::XDataObject::GetData -- %d\n", 
		  lpFormatEtc->cfFormat);
	METHOD_PROLOGUE(CEx28cDoc, DataObject)
	ASSERT_VALID(pThis);
	
	if(lpFormatEtc->cfFormat != CF_METAFILEPICT) {
		return S_FALSE;
	}
	HGLOBAL hPict = pThis->MakeMetaFile();
	lpStgMedium->tymed = TYMED_MFPICT;
	lpStgMedium->hMetaFilePict = hPict;
	lpStgMedium->pUnkForRelease = NULL;
	return S_OK;
}

STDMETHODIMP CEx28cDoc::XDataObject::GetDataHere(
	LPFORMATETC lpFormatEtc, LPSTGMEDIUM lpStgMedium)
{
	TRACE("CEx28cDoc::XDataObject::GetDataHere\n");
	METHOD_PROLOGUE(CEx28cDoc, DataObject)
	ASSERT_VALID(pThis);
	return E_NOTIMPL;
}

STDMETHODIMP CEx28cDoc::XDataObject::QueryGetData(LPFORMATETC lpFormatEtc)
{
	TRACE("CEx28cDoc::XDataObject::QueryGetData -- %d\n", lpFormatEtc->cfFormat);
	METHOD_PROLOGUE(CEx28cDoc, DataObject)
	ASSERT_VALID(pThis);
	if(lpFormatEtc->cfFormat != CF_METAFILEPICT) {
		return S_FALSE;
	}
	return S_OK;
}

STDMETHODIMP CEx28cDoc::XDataObject::GetCanonicalFormatEtc(
	LPFORMATETC /*lpFormatEtcIn*/, LPFORMATETC /*lpFormatEtcOut*/)
{
	TRACE("CEx28cDoc::XDataObject::GetCanonicalFormatEtc\n");
	return DATA_S_SAMEFORMATETC;
}

STDMETHODIMP CEx28cDoc::XDataObject::SetData(
	LPFORMATETC lpFormatEtc, LPSTGMEDIUM lpStgMedium, BOOL bRelease)
{
	TRACE("CEx28cDoc::XDataObject::SetData\n");
	METHOD_PROLOGUE(CEx28cDoc, DataObject)
	ASSERT_VALID(pThis);
	return E_NOTIMPL;
}

STDMETHODIMP CEx28cDoc::XDataObject::EnumFormatEtc(DWORD dwDirection,
								LPENUMFORMATETC* ppenumFormatEtc)
{
	TRACE("CEx28cDoc::XDataObject::EnumFormatEtc\n");
	METHOD_PROLOGUE(CEx28cDoc, DataObject)
	ASSERT_VALID(pThis);
	return E_NOTIMPL;
}

STDMETHODIMP CEx28cDoc::XDataObject::DAdvise(FORMATETC* pFormatEtc,
	DWORD advf, LPADVISESINK pAdvSink, DWORD* pdwConnection)
{
	TRACE("CEx28cDoc::XDataObject::DAdvise\n");
	METHOD_PROLOGUE(CEx28cDoc, DataObject)
	ASSERT_VALID(pThis);

	*pdwConnection = 555;
	// create the advise holder, if necessary
	if (pThis->m_lpDataAdviseHolder == NULL &&
		CreateDataAdviseHolder(&pThis->m_lpDataAdviseHolder) != S_OK) {
		return E_OUTOFMEMORY;
	}
	ASSERT(pThis->m_lpDataAdviseHolder != NULL);
	HRESULT hr = pThis->m_lpDataAdviseHolder->Advise(this, pFormatEtc, advf,
		pAdvSink, pdwConnection);
	return hr;
}

STDMETHODIMP CEx28cDoc::XDataObject::DUnadvise(DWORD dwConnection)
{
	TRACE("CEx28cDoc::XDataObject::DUnadvise\n");
	METHOD_PROLOGUE(CEx28cDoc, DataObject)
	ASSERT_VALID(pThis);
 
	return E_NOTIMPL;
}

STDMETHODIMP CEx28cDoc::XDataObject::EnumDAdvise(
	LPENUMSTATDATA* ppenumAdvise)
{
	TRACE("CEx28cDoc::XDataObject::EnumDAdvise\n");
	METHOD_PROLOGUE(CEx28cDoc, DataObject)
	ASSERT_VALID(pThis);

	return E_NOTIMPL;
}

/////////////////////////////////////////////////////////////
STDMETHODIMP_(ULONG) CEx28cDoc::XPersistStorage::AddRef()
{
	TRACE("CEx28cDoc::XPersistStorage:::AddRef\n");
	METHOD_PROLOGUE(CEx28cDoc, PersistStorage)
	return pThis->InternalAddRef();
}

STDMETHODIMP_(ULONG) CEx28cDoc::XPersistStorage::Release()
{
	TRACE("CEx28cDoc::XPersistStorage::Release\n");
	METHOD_PROLOGUE(CEx28cDoc, PersistStorage)
	return pThis->InternalRelease();
}

STDMETHODIMP CEx28cDoc::XPersistStorage::QueryInterface(
	REFIID iid, LPVOID* ppvObj)
{
	ITrace(iid, "CEx28cDoc::XPersistStorage::QueryInterface");
	METHOD_PROLOGUE(CEx28cDoc, PersistStorage)
	return pThis->InternalQueryInterface(&iid, ppvObj);
}

STDMETHODIMP CEx28cDoc::XPersistStorage::GetClassID(LPCLSID lpClassID)
{
	TRACE("CEx28cDoc::XPersistStorage::GetClassID\n");
	METHOD_PROLOGUE(CEx28cDoc, PersistStorage)
	ASSERT_VALID(pThis);
	*lpClassID = clsid;
	return NOERROR;
}

STDMETHODIMP CEx28cDoc::XPersistStorage::IsDirty()
{
	TRACE("CEx28cDoc::XPersistStorage::IsDirty\n");
	METHOD_PROLOGUE(CEx28cDoc, PersistStorage)
	ASSERT_VALID(pThis);

	return pThis->IsModified() ? NOERROR : S_FALSE;
}

STDMETHODIMP CEx28cDoc::XPersistStorage::InitNew(LPSTORAGE pStg)
{
	TRACE("CEx28cDoc::XPersistStorage::InitNew\n");
	METHOD_PROLOGUE(CEx28cDoc, PersistStorage)
	ASSERT_VALID(pThis);
	ASSERT(pStg != NULL);

	pThis->SetModifiedFlag();  // new storage-based documents are dirty!
	pThis->SendInitialUpdate(); // in CDocument
	return NOERROR;
}

STDMETHODIMP CEx28cDoc::XPersistStorage::Load(LPSTORAGE pStgLoad)
{
	TRACE("CEx28cDoc::XPersistStorage::Load\n");
	METHOD_PROLOGUE(CEx28cDoc, PersistStorage)
	ASSERT_VALID(pThis);

	ASSERT(pStgLoad != NULL);
	LPSTREAM pStream;
	ULONG nBytesRead;
	char buffer[101]; // 100 characters max for m_strText
	try {
		pThis->DeleteContents();
		if(pStgLoad->OpenStream(L"Ex28c Text", NULL,
				STGM_READ|STGM_SHARE_EXCLUSIVE,
				0, &pStream) == NOERROR) {
			pStream->Read(buffer, 100, &nBytesRead);
			pStream->Release();
			pThis->m_strText = buffer;
		}
	}
	catch(CException* pe) {
		pe->Delete();
		return E_FAIL;
	}

	pThis->SetModifiedFlag();  // new storage-based documents are dirty!
	pThis->SendInitialUpdate(); // in CDocument
	return NOERROR;
}

STDMETHODIMP CEx28cDoc::XPersistStorage::Save(LPSTORAGE pStgSave,
								BOOL fSameAsLoad)
{
	TRACE("CEx28cDoc::XPersistStorage::Save\n");
	METHOD_PROLOGUE(CEx28cDoc, PersistStorage)
	ASSERT_VALID(pThis);

	// don't bother saving if destination is up-to-date
	if (fSameAsLoad && !pThis->IsModified())
		return NOERROR;

	ASSERT(pStgSave != NULL);
	LPSTREAM pStream;
	ULONG nBytesWritten;
	try	{
		if(pStgSave->CreateStream(L"Ex28c Text",
				STGM_CREATE|STGM_READWRITE|STGM_SHARE_EXCLUSIVE,
				0, 0, &pStream) == NOERROR) {
			pStream->Write((const char*) pThis->m_strText,
					pThis->m_strText.GetLength() + 1, &nBytesWritten);
			pStream->Release();
		}
		else return E_FAIL;
	}
	catch(CException* pe) {
		pe->Delete();
		return E_FAIL;
	}

	pThis->SetModifiedFlag();  // new storage-based documents are dirty!
	pThis->SendInitialUpdate(); // in CDocument
	return NOERROR;
}

STDMETHODIMP CEx28cDoc::XPersistStorage::SaveCompleted(LPSTORAGE pStgSaved)
{
	TRACE("CEx28cDoc::XPersistStorage::SaveCompleted\n");
	METHOD_PROLOGUE(CEx28cDoc, PersistStorage)
	ASSERT_VALID(pThis);

	return E_NOTIMPL;
}

STDMETHODIMP CEx28cDoc::XPersistStorage::HandsOffStorage()
{
	TRACE("CEx28cDoc::XPersistStorage::HandsOffStorage\n");
	METHOD_PROLOGUE(CEx28cDoc, PersistStorage)
	ASSERT_VALID(pThis);

	return E_NOTIMPL;
}


/////////////////////////////////////////////////////////////////////////////
// CEx28cDoc construction/destruction

CEx28cDoc::CEx28cDoc()
{
	// TODO: add one-time construction code here

	TRACE("CEx28cDoc ctor\n");
	m_lpClientSite = NULL;
	m_lpOleAdviseHolder = NULL;
	m_lpDataAdviseHolder = NULL;
}

CEx28cDoc::~CEx28cDoc()
{
	TRACE("CEx28cDoc dtor\n");
}

BOOL CEx28cDoc::OnNewDocument()
{
	TRACE("CEx28cDoc::OnNewDocument\n");
	if (!CDocument::OnNewDocument())
		return FALSE;
	m_strText = "Default text";
	return TRUE;
}

HGLOBAL CEx28cDoc::MakeMetaFile()
{
	HGLOBAL hPict;
	CMetaFileDC dcm;
	VERIFY(dcm.Create());
	CSize size(5000, 5000); // initial size of object in Excel & Word
	dcm.SetMapMode(MM_ANISOTROPIC);
	dcm.SetWindowOrg(0,0);
	dcm.SetWindowExt(size.cx, -size.cy);
	// drawing code
	dcm.Rectangle(CRect(500, -1000, 1500, -2000));
    CFont font;
    font.CreateFont(-500, 0, 0, 0, 400, FALSE, FALSE, 0,
                    ANSI_CHARSET, OUT_DEFAULT_PRECIS,
                    CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                    DEFAULT_PITCH | FF_SWISS, "Arial");
    CFont* pFont = dcm.SelectObject(&font);
	dcm.TextOut(0, 0, m_strText);
    dcm.SelectObject(pFont);
	
	HMETAFILE hMF = dcm.Close();
	ASSERT(hMF != NULL);
	hPict = ::GlobalAlloc(GMEM_SHARE|GMEM_MOVEABLE, sizeof(METAFILEPICT));
	ASSERT(hPict != NULL);
	LPMETAFILEPICT lpPict;
	lpPict = (LPMETAFILEPICT) ::GlobalLock(hPict);
	ASSERT(lpPict != NULL);
	lpPict->mm = MM_ANISOTROPIC;
	lpPict->hMF = hMF;
	lpPict->xExt = size.cx;
	lpPict->yExt = size.cy;  // HIMETRIC height
	::GlobalUnlock(hPict);
	return hPict;
}
/////////////////////////////////////////////////////////////////////////////
// CEx28cDoc serialization

void CEx28cDoc::Serialize(CArchive& ar)
{
	// not needed by OLE
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
// CEx28cDoc diagnostics

#ifdef _DEBUG
void CEx28cDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CEx28cDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// global diagnostic function
void ITrace(REFIID iid, const char* str)
{
	LPOLESTR lpszIID;
	::StringFromIID(iid, &lpszIID);
	CString strIID = lpszIID;
	TRACE("%s - %s\n", (const char*) strIID, (const char*) str);
	AfxFreeTaskMem(lpszIID);
}

/////////////////////////////////////////////////////////////////////////////
// CEx28cDoc commands

void CEx28cDoc::OnFinalRelease() 
{
	TRACE("CEx28cDoc::OnFinalRelease\n"); // so we can see it happen
	CDocument::OnFinalRelease();
}

void CEx28cDoc::OnCloseDocument() 
{
    InternalAddRef();

    if(m_lpClientSite != NULL) {
        m_lpClientSite->OnShowWindow(FALSE); // no hatch
        m_lpClientSite->Release();
    }

    if (m_lpOleAdviseHolder != NULL)
        m_lpOleAdviseHolder->SendOnClose();  // you need to send a close notification

    // finish closing the document (before m_lpClientSite->Release)
    BOOL bAutoDelete = m_bAutoDelete;
    m_bAutoDelete = FALSE;
    CDocument::OnCloseDocument();

    // disconnect the object
    LPUNKNOWN lpUnknown = (LPUNKNOWN)GetInterface(&IID_IUnknown);
    ASSERT(lpUnknown != NULL);
    CoDisconnectObject(lpUnknown, 0);     // this is very important to close circular references

    if(m_lpOleAdviseHolder != NULL)
        m_lpOleAdviseHolder->Release();
    if(m_lpDataAdviseHolder != NULL)
        m_lpDataAdviseHolder->Release();

    m_lpClientSite = NULL;
    m_lpOleAdviseHolder = NULL;
    m_lpDataAdviseHolder = NULL;

    InterlockedDecrement(&m_dwRef);              // remove InternalAddRef above
    if (bAutoDelete) {
        delete this;
	}
}

void CEx28cDoc::OnModify() 
{
	CTextDialog dlg;
	dlg.m_strText = m_strText;
	if(dlg.DoModal() == IDOK) {
		m_strText = dlg.m_strText;
		UpdateAllViews(NULL); // redraw view
		// Notify the client that the metafile has changed.
		//  Client must call IViewObject::SetAdvise.
		LPDATAOBJECT lpDataObject = 
			(LPDATAOBJECT) GetInterface(&IID_IDataObject);
		HRESULT hr = 
			m_lpDataAdviseHolder->SendOnDataChange(lpDataObject, 0, NULL);
		ASSERT(hr == NOERROR);
		SetModifiedFlag(); // won't update without this
	}	
}

void CEx28cDoc::OnFileUpdate() 
{
	if(m_lpClientSite == NULL) return;
	VERIFY(m_lpClientSite->SaveObject() == NOERROR);
    if (m_lpOleAdviseHolder != NULL)
            m_lpOleAdviseHolder->SendOnSave();  
	SetModifiedFlag(FALSE);
}

void CEx28cDoc::OnUpdateFileUpdate(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(IsModified());
	
}

BOOL CEx28cDoc::SaveModified() 
{
	OnFileUpdate();
	return TRUE;
}
