// CDHTML.h : Declaration of the CCDHTML

#ifndef __CDHTML_H_
#define __CDHTML_H_

#include "resource.h"       // main symbols
#include <atlctl.h>


/////////////////////////////////////////////////////////////////////////////
// CCDHTML
class ATL_NO_VTABLE CCDHTML : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public IDispatchImpl<ICDHTML, &IID_ICDHTML, &LIBID_EX37CLib>,
	public IDispatchImpl<ICDHTMLUI, &IID_ICDHTMLUI, &LIBID_EX37CLib>,
	public CComControl<CCDHTML>,
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
	public IProvideClassInfo2Impl<&CLSID_CDHTML, NULL, &LIBID_EX37CLib>,
	public CComCoClass<CCDHTML, &CLSID_CDHTML>
{
public:
	CCDHTML()
	{
		m_bWindowOnly = TRUE;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_CDHTML)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CCDHTML)
	COM_INTERFACE_ENTRY(ICDHTML)
	COM_INTERFACE_ENTRY(ICDHTMLUI)
	COM_INTERFACE_ENTRY2(IDispatch, ICDHTML)
	COM_INTERFACE_ENTRY(IViewObjectEx)
	COM_INTERFACE_ENTRY(IViewObject2)
	COM_INTERFACE_ENTRY(IViewObject)
	COM_INTERFACE_ENTRY(IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceObject)
	COM_INTERFACE_ENTRY2(IOleWindow, IOleInPlaceObjectWindowless)
	COM_INTERFACE_ENTRY(IOleInPlaceActiveObject)
	COM_INTERFACE_ENTRY(IOleControl)
	COM_INTERFACE_ENTRY(IOleObject)
	COM_INTERFACE_ENTRY(IPersistStreamInit)
	COM_INTERFACE_ENTRY2(IPersist, IPersistStreamInit)
	COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
	COM_INTERFACE_ENTRY(IQuickActivate)
	COM_INTERFACE_ENTRY(IPersistStorage)
	COM_INTERFACE_ENTRY(IDataObject)
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
END_COM_MAP()

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
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);



// IViewObjectEx
	DECLARE_VIEW_STATUS(0)

// ICDHTML
public:

// ICDHTMLUI
public:
	// Example method called by the HTML to change the <BODY> background color
	STDMETHOD(OnClick)(IDispatch* pdispBody, VARIANT varColor)
	{
		CComQIPtr<IHTMLBodyElement> spBody(pdispBody);
		if (spBody != NULL)
			spBody->put_bgColor(varColor);
		return S_OK;
	}

	LRESULT OnCreate(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		CAxWindow wnd(m_hWnd);
		HRESULT hr = wnd.CreateControl(IDH_CDHTML);
		if (SUCCEEDED(hr))
			hr = wnd.SetExternalDispatch(static_cast<ICDHTMLUI*>(this));
		if (SUCCEEDED(hr))
			hr = wnd.QueryControl(IID_IWebBrowser2, (void**)&m_spBrowser);
		return SUCCEEDED(hr) ? 0 : -1;
	}

	CComPtr<IWebBrowser2> m_spBrowser;
};

#endif //__CDHTML_H_
