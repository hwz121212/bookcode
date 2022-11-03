// ClassicATLDiceControl.h : Declaration of the CClassicATLDiceControl
#pragma once
#include "resource.h"       // main symbols
#include <atlctl.h>
#include "time.h"
#include "ClassicATLDiceSvr.h"
#include "_IClassicATLDiceControlEvents_CP.h"


#define MAX_DIEFACES 6


// CClassicATLDiceControl
class ATL_NO_VTABLE CClassicATLDiceControl : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CStockPropImpl<CClassicATLDiceControl, IClassicATLDiceControl>,
	public IPersistStreamInitImpl<CClassicATLDiceControl>,
	public IOleControlImpl<CClassicATLDiceControl>,
	public IOleObjectImpl<CClassicATLDiceControl>,
	public IOleInPlaceActiveObjectImpl<CClassicATLDiceControl>,
	public IViewObjectExImpl<CClassicATLDiceControl>,
	public IOleInPlaceObjectWindowlessImpl<CClassicATLDiceControl>,
	public ISupportErrorInfo,
	public IConnectionPointContainerImpl<CClassicATLDiceControl>,
	public CProxy_IClassicATLDiceControlEvents<CClassicATLDiceControl>, 
	public IPersistStorageImpl<CClassicATLDiceControl>,
	public ISpecifyPropertyPagesImpl<CClassicATLDiceControl>,
	public IQuickActivateImpl<CClassicATLDiceControl>,
	public IDataObjectImpl<CClassicATLDiceControl>,
	public IProvideClassInfo2Impl<&CLSID_ClassicATLDiceControl, &__uuidof(_IClassicATLDiceControlEvents), &LIBID_ClassicATLDiceSvrLib>,
	public IPropertyNotifySinkCP<CClassicATLDiceControl>,
	public CComCoClass<CClassicATLDiceControl, &CLSID_ClassicATLDiceControl>,
	public CComControl<CClassicATLDiceControl>
{
public:

   HBITMAP m_dieBitmaps[MAX_DIEFACES];
   unsigned short m_nFirstDieValue;
   unsigned short m_nSecondDieValue;

   short m_nDiceColor;
   short m_nTimesToRoll;
   short m_nTimesRolled;


	CClassicATLDiceControl()
	{
		m_bWindowOnly = TRUE;

       LoadBitmaps();
       srand((unsigned)time(NULL));      
       m_nFirstDieValue = (rand() % (MAX_DIEFACES)) + 1;
       m_nSecondDieValue = (rand() % (MAX_DIEFACES)) + 1;

	   m_nTimesToRoll = 15;
	   m_nTimesRolled = 0;
	   m_nDiceColor = 0;
	}

DECLARE_OLEMISC_STATUS(OLEMISC_RECOMPOSEONRESIZE | 
	OLEMISC_CANTLINKINSIDE | 
	OLEMISC_INSIDEOUT | 
	OLEMISC_ACTIVATEWHENVISIBLE | 
	OLEMISC_SETCLIENTSITEFIRST
)

DECLARE_REGISTRY_RESOURCEID(IDR_CLASSICATLDICECONTROL)

BEGIN_COM_MAP(CClassicATLDiceControl)
	COM_INTERFACE_ENTRY(IClassicATLDiceControl)
	COM_INTERFACE_ENTRY(IDispatch)
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
	COM_INTERFACE_ENTRY(ISupportErrorInfo)
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
	COM_INTERFACE_ENTRY(IQuickActivate)
	COM_INTERFACE_ENTRY(IPersistStorage)
	COM_INTERFACE_ENTRY(IDataObject)
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
END_COM_MAP()

BEGIN_PROP_MAP(CClassicATLDiceControl)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	PROP_ENTRY("BackColor", DISPID_BACKCOLOR, CLSID_StockColorPage)
	PROP_ENTRY("DiceColor", 2, CLSID_CDiceMainPropPage)
	PROP_ENTRY("TimesToRoll", 3, CLSID_CDiceMainPropPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CClassicATLDiceControl)
	CONNECTION_POINT_ENTRY(__uuidof(_IClassicATLDiceControlEvents))
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CClassicATLDiceControl)
    MESSAGE_HANDLER(WM_TIMER, OnTimer)
    MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnLButtonDblClk)
    CHAIN_MSG_MAP(CComControl<CClassicATLDiceControl>)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

// ISupportsErrorInfo
	STDMETHOD(InterfaceSupportsErrorInfo)(REFIID riid)
	{
		static const IID* arr[] = 
		{
			&IID_IClassicATLDiceControl,
		};

		for (int i=0; i<sizeof(arr)/sizeof(arr[0]); i++)
		{
			if (InlineIsEqualGUID(*arr[i], riid))
				return S_OK;
		}
		return S_FALSE;
	}

// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

// IClassicATLDiceControl
public:

    // Prototypes
    BOOL LoadBitmaps();
    void ShowFirstDieFace(ATL_DRAWINFO& di);
    void ShowSecondDieFace(ATL_DRAWINFO& di);

	HRESULT OnDraw(ATL_DRAWINFO& di)
	{
        RECT& rc = *(RECT*)di.prcBounds;

        HBRUSH hBrush = CreateSolidBrush(m_clrBackColor);
        HBRUSH hOldBrush = (HBRUSH)SelectObject(di.hdcDraw, hBrush);

        Rectangle(di.hdcDraw, rc.left, rc.top, rc.right, rc.bottom);

        SelectObject(di.hdcDraw, hOldBrush);
        DeleteObject(hBrush);

	    ShowFirstDieFace(di);
    	ShowSecondDieFace(di);

		return S_OK;
	}

	OLE_COLOR m_clrBackColor;
	void OnBackColorChanged()
	{
		ATLTRACE(_T("OnBackColorChanged\n"));
	}

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	
	void FinalRelease() 
	{
	}
    STDMETHOD(get_DiceColor)(SHORT* pVal);
    STDMETHOD(put_DiceColor)(SHORT newVal);
    STDMETHOD(get_TimesToRoll)(SHORT* pVal);
    STDMETHOD(put_TimesToRoll)(SHORT newVal);
    STDMETHOD(RollDice)(void);
    LRESULT OnTimer(UINT_PTR /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnLButtonDblClk(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
};

OBJECT_ENTRY_AUTO(__uuidof(ClassicATLDiceControl), CClassicATLDiceControl)
