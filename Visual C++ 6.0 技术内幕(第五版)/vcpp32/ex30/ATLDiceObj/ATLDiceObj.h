// ATLDiceObj.h : Declaration of the CATLDiceObj

#ifndef __ATLDICEOBJ_H_
#define __ATLDICEOBJ_H_

#include "resource.h"       // main symbols
#include <atlctl.h>
#include "time.h"
#include "atldicesrvrCP.h"

#define MAX_DIEFACES 6

/////////////////////////////////////////////////////////////////////////////
// CATLDiceObj
class CATLDiceObj : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CStockPropImpl<CATLDiceObj, IATLDiceObj, &IID_IATLDiceObj, &LIBID_ATLDICESRVRLib>,
	public CComControl<CATLDiceObj>,
	public IPersistStreamInitImpl<CATLDiceObj>,
	public IOleControlImpl<CATLDiceObj>,
	public IOleObjectImpl<CATLDiceObj>,
	public IOleInPlaceActiveObjectImpl<CATLDiceObj>,
	public IViewObjectExImpl<CATLDiceObj>,
	public IOleInPlaceObjectWindowlessImpl<CATLDiceObj>,
	public IConnectionPointContainerImpl<CATLDiceObj>,
	public IPersistStorageImpl<CATLDiceObj>,
	public ISpecifyPropertyPagesImpl<CATLDiceObj>,
	public IQuickActivateImpl<CATLDiceObj>,
	public IDataObjectImpl<CATLDiceObj>,
	public IProvideClassInfo2Impl<&CLSID_ATLDiceObj, &DIID__IATLDiceObjEvents, &LIBID_ATLDICESRVRLib>,
	public IPropertyNotifySinkCP<CATLDiceObj>,
	public CComCoClass<CATLDiceObj, &CLSID_ATLDiceObj>,
	public CProxy_IATLDiceObjEvents< CATLDiceObj >
{
public:
	CATLDiceObj()
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

DECLARE_REGISTRY_RESOURCEID(IDR_ATLDICEOBJ)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CATLDiceObj)
	COM_INTERFACE_ENTRY_IMPL(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(IATLDiceObj)
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
	COM_INTERFACE_ENTRY(IConnectionPointContainer)
	COM_INTERFACE_ENTRY(ISpecifyPropertyPages)
	COM_INTERFACE_ENTRY(IQuickActivate)
	COM_INTERFACE_ENTRY(IPersistStorage)
	COM_INTERFACE_ENTRY(IDataObject)
	COM_INTERFACE_ENTRY(IProvideClassInfo)
	COM_INTERFACE_ENTRY(IProvideClassInfo2)
END_COM_MAP()

BEGIN_PROP_MAP(CATLDiceObj)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	PROP_ENTRY("BackColor", DISPID_BACKCOLOR, CLSID_StockColorPage)
	PROP_ENTRY("DiceColor", 2, CLSID_DiceMainPropPage)
	PROP_ENTRY("TimesToRoll", 3, CLSID_DiceMainPropPage)
END_PROP_MAP()

BEGIN_CONNECTION_POINT_MAP(CATLDiceObj)
	CONNECTION_POINT_ENTRY(DIID__IATLDiceObjEvents)
	CONNECTION_POINT_ENTRY(IID_IPropertyNotifySink)
END_CONNECTION_POINT_MAP()

BEGIN_MSG_MAP(CATLDiceObj)
	CHAIN_MSG_MAP(CComControl<CATLDiceObj>)
	DEFAULT_REFLECTION_HANDLER()
	MESSAGE_HANDLER(WM_TIMER, OnTimer);
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);



   LRESULT OnTimer(UINT msg, WPARAM wParam, 
                   LPARAM lParam, BOOL& bHandled);


   BOOL LoadBitmaps();

   void ShowFirstDieFace(ATL_DRAWINFO& di);
   void ShowSecondDieFace(ATL_DRAWINFO& di);
   
   HBITMAP m_dieBitmaps[MAX_DIEFACES];
   unsigned short m_nFirstDieValue;
   unsigned short m_nSecondDieValue;

   short m_nDiceColor;
   short m_nTimesToRoll;
   short m_nTimesRolled;


// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

// IATLDiceObj
public:
	STDMETHOD(get_DiceColor)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_DiceColor)(/*[in]*/ short newVal);
	STDMETHOD(get_TimesToRoll)(/*[out, retval]*/ short *pVal);
	STDMETHOD(put_TimesToRoll)(/*[in]*/ short newVal);
	STDMETHOD(RollDice)();

	HRESULT OnDraw(ATL_DRAWINFO& di)
	{
		RECT& rc = *(RECT*)di.prcBounds;

		ShowFirstDieFace(di);
		ShowSecondDieFace(di);
		return S_OK;
	}
	OLE_COLOR m_clrBackColor;
};

#endif //__ATLDICEOBJ_H_
