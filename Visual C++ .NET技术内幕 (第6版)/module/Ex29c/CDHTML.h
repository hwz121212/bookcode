// CDHTML.h : Declaration of the CCDHTML
#pragma once
#include "resource.h"       // main symbols
#include <atlctl.h>
[
	object, 
	dual,
	uuid(9F3E85AE-09C6-4A3A-A78C-6973F8A328B6),
	helpstring("ICDHTMLUI Interface"),
	pointer_default(unique)
]
__interface ICDHTMLUI : IDispatch
{
	// Example method that will be called by the HTML
	[id(1)] HRESULT OnClick([in]IDispatch* pdispBody, [in]VARIANT varColor);
};
[
	coclass,
	threading("apartment"),
	version(1.0),
	uuid("72DB36B5-154C-427E-9BB0-AAF3C496B6EC"),
	noncreatable
]
class ATL_NO_VTABLE CCDHTMLUI :
	public ICDHTMLUI
{
public:
	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	
	void FinalRelease() 
	{
	}

	// Example method called by the HTML to change the <BODY> background color
	STDMETHOD(OnClick)(IDispatch* pdispBody, VARIANT varColor)
	{
		CComQIPtr<IHTMLBodyElement> spBody(pdispBody);
		if (spBody != NULL)
			spBody->put_bgColor(varColor);
		return S_OK;
	}
};


// ICDHTML
[
	object,
	uuid(C0771F2F-6285-48EA-9356-8AA2A4D8C47D),
	dual,
	helpstring("ICDHTML Interface"),
	pointer_default(unique)
]
__interface ICDHTML : public IDispatch
{
};


// CCDHTML
[
	coclass,
	threading("apartment"),
	vi_progid("Ex29c.CDHTML"),
	progid("Ex29c.CDHTML.1"),
	version(1.0),
	uuid("E672F808-00BC-46AD-9970-8DB5585EAA1E"),
	helpstring("CDHTML Class"),
	support_error_info(ICDHTML),
	registration_script("control.rgs")
]
class ATL_NO_VTABLE CCDHTML : 
	public ICDHTML,
	public IPersistStreamInitImpl<CCDHTML>,
	public IOleControlImpl<CCDHTML>,
	public IOleObjectImpl<CCDHTML>,
	public IOleInPlaceActiveObjectImpl<CCDHTML>,
	public IViewObjectExImpl<CCDHTML>,
	public IOleInPlaceObjectWindowlessImpl<CCDHTML>,
	public IPersistStorageImpl<CCDHTML>,
	public ISpecifyPropertyPagesImpl<CCDHTML>,
	public IQuickActivateImpl<CCDHTML>,
	public IDataObjectImpl<CCDHTML>,
	public IProvideClassInfo2Impl<&__uuidof(CCDHTML), NULL>,
	public CComControl<CCDHTML>
{
public:

	CCDHTML()
	{
		m_bWindowOnly = TRUE;
	}

DECLARE_OLEMISC_STATUS(OLEMISC_RECOMPOSEONRESIZE | 
	OLEMISC_CANTLINKINSIDE | 
	OLEMISC_INSIDEOUT | 
	OLEMISC_ACTIVATEWHENVISIBLE | 
	OLEMISC_SETCLIENTSITEFIRST
)


BEGIN_PROP_MAP(CCDHTML)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	// Example entries
	// PROP_ENTRY("Property Description", dispid, clsid)
	// PROP_PAGE(CLSID_StockColorPage)
END_PROP_MAP()


BEGIN_MSG_MAP(CCDHTML)
	MESSAGE_HANDLER(WM_CREATE, OnCreate)
	CHAIN_MSG_MAP(CComControl<CCDHTML>)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

// ICDHTML

	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		CAxWindow wnd(m_hWnd);
		wnd.ModifyStyle(0, WS_HSCROLL | WS_VSCROLL);
		HRESULT hr = wnd.CreateControl(IDH_CDHTML);
		if (SUCCEEDED(hr))
		{
			CComObject<CCDHTMLUI> *pObject = NULL;
			hr = CComObject<CCDHTMLUI>::CreateInstance(&pObject);
			if (SUCCEEDED(hr) && pObject != NULL)
				hr = wnd.SetExternalDispatch(static_cast<ICDHTMLUI*>(pObject));
		}
		if (SUCCEEDED(hr))
			hr = wnd.QueryControl(IID_IWebBrowser2, (void**)&m_spBrowser);
		return SUCCEEDED(hr) ? 0 : -1;
	}

	STDMETHOD(TranslateAccelerator)(LPMSG pMsg)
	{
		CComPtr<IOleInPlaceActiveObject> spIOleInPlaceActiveObject;
		
		HRESULT hr = m_spBrowser->QueryInterface(&spIOleInPlaceActiveObject);
		if (SUCCEEDED(hr))
			hr = spIOleInPlaceActiveObject->TranslateAccelerator(pMsg);
		if (hr != S_OK)
			hr = IOleInPlaceActiveObjectImpl<CCDHTML>::TranslateAccelerator(pMsg);

		return hr;
	}
	CComPtr<IWebBrowser2> m_spBrowser;

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	
	void FinalRelease() 
	{
	}
};

