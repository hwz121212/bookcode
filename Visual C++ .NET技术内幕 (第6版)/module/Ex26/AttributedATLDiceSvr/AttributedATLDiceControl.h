// AttributedATLDiceControl.h : Declaration of the CAttributedATLDiceControl
#pragma once
#include "resource.h"       // main symbols
#include <atlctl.h>

#include <time.h>

#include "_attributedatldicesvr_i.c"

// IAttributedATLDiceControl
[
	object,
	uuid(5321A066-9E3A-4412-A11A-32D5ED060146),
	dual,
	helpstring("IAttributedATLDiceControl Interface"),
	pointer_default(unique)
]
__interface IAttributedATLDiceControl : public IDispatch
{
	[propput, bindable, requestedit, id(DISPID_BACKCOLOR)]
	HRESULT BackColor([in]OLE_COLOR clr);
	[propget, bindable, requestedit, id(DISPID_BACKCOLOR)]
	HRESULT BackColor([out,retval]OLE_COLOR* pclr);
    [propget, id(1), helpstring("property DiceColor")] 
    HRESULT DiceColor([out, retval] SHORT* pVal);
    [propput, id(1), helpstring("property DiceColor")] 
    HRESULT DiceColor([in] SHORT newVal);
    [propget, id(2), helpstring("property TimesToRoll")] 
    HRESULT TimesToRoll([out, retval] SHORT* pVal);
    [propput, id(2), helpstring("property TimesToRoll")] 
    HRESULT TimesToRoll([in] SHORT newVal);
    [id(3), helpstring("method RollDice")] HRESULT RollDice(void);
};


// _IAttributedATLDiceControlEvents
[
	uuid("4AB0D205-044E-4641-A0A5-B606D8685FE5"),
	dispinterface,
	helpstring("_IAttributedATLDiceControlEvents Interface")
]
__interface _IAttributedATLDiceControlEvents
{
    [id(1), helpstring("method Doubles")] HRESULT Doubles(SHORT n);
    [id(2), helpstring("method SnakeEyes")] HRESULT SnakeEyes(void);
    [id(3), helpstring("method DiceRolled")] HRESULT DiceRolled(SHORT x, SHORT y);
};

#define MAX_DIEFACES 6


// CAttributedATLDiceControl
[
	coclass,
	threading("apartment"),
	vi_progid("AttributedATLDiceSvr.AttributedATLDiceC"),
	progid("AttributedATLDiceSvr.AttributedATLDic.1"),
	version(1.0),
	uuid("48350572-BE82-4FBB-AA6F-B4691E30173A"),
	helpstring("AttributedATLDiceControl Class"),
	event_source("com"),
	support_error_info(IAttributedATLDiceControl),
	registration_script("control.rgs")
]
class ATL_NO_VTABLE CAttributedATLDiceControl : 
	public CStockPropImpl<CAttributedATLDiceControl, IAttributedATLDiceControl>,
	public IPersistStreamInitImpl<CAttributedATLDiceControl>,
	public IOleControlImpl<CAttributedATLDiceControl>,
	public IOleObjectImpl<CAttributedATLDiceControl>,
	public IOleInPlaceActiveObjectImpl<CAttributedATLDiceControl>,
	public IViewObjectExImpl<CAttributedATLDiceControl>,
	public IOleInPlaceObjectWindowlessImpl<CAttributedATLDiceControl>,
	public IPersistStorageImpl<CAttributedATLDiceControl>,
	public ISpecifyPropertyPagesImpl<CAttributedATLDiceControl>,
	public IQuickActivateImpl<CAttributedATLDiceControl>,
	public IDataObjectImpl<CAttributedATLDiceControl>,
	public CComControl<CAttributedATLDiceControl>
{
public:

   HBITMAP m_dieBitmaps[MAX_DIEFACES];
   unsigned short m_nFirstDieValue;
   unsigned short m_nSecondDieValue;

   short m_nDiceColor;
   short m_nTimesToRoll;
   short m_nTimesRolled;

	CAttributedATLDiceControl()
	{
		m_bWindowOnly = TRUE;

       srand((unsigned)time(NULL));      
       m_nFirstDieValue = (rand() % (MAX_DIEFACES)) + 1;
       m_nSecondDieValue = (rand() % (MAX_DIEFACES)) + 1;

	   m_nTimesToRoll = 15;
	   m_nTimesRolled = 0;
	   m_nDiceColor = 0;

       LoadBitmaps();
	}

DECLARE_OLEMISC_STATUS(OLEMISC_RECOMPOSEONRESIZE | 
	OLEMISC_CANTLINKINSIDE | 
	OLEMISC_INSIDEOUT | 
	OLEMISC_ACTIVATEWHENVISIBLE | 
	OLEMISC_SETCLIENTSITEFIRST
)


BEGIN_PROP_MAP(CAttributedATLDiceControl)
	PROP_DATA_ENTRY("_cx", m_sizeExtent.cx, VT_UI4)
	PROP_DATA_ENTRY("_cy", m_sizeExtent.cy, VT_UI4)
	PROP_ENTRY("BackColor", DISPID_BACKCOLOR, CLSID_StockColorPage)
	PROP_ENTRY("DiceColor", 2, CLSID_CDiceMainPropPage)
	PROP_ENTRY("TimesToRoll", 3, CLSID_CDiceMainPropPage)
END_PROP_MAP()


BEGIN_MSG_MAP(CAttributedATLDiceControl)
    MESSAGE_HANDLER(WM_LBUTTONDBLCLK, OnLButtonDblClk)
    MESSAGE_HANDLER(WM_TIMER, OnTimer)
    CHAIN_MSG_MAP(CComControl<CAttributedATLDiceControl>)
	DEFAULT_REFLECTION_HANDLER()
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	__event __interface _IAttributedATLDiceControlEvents;

// Fire events:

    HRESULT Fire_Doubles(short x) {
      __raise Doubles(x);
      return S_OK;
   }

    HRESULT Fire_DiceRolled(short x, short y) {
      __raise DiceRolled(x, y);
      return S_OK;
   }

   HRESULT Fire_SnakeEyes() {
      __raise SnakeEyes();
      return S_OK;
   }

// IViewObjectEx
	DECLARE_VIEW_STATUS(VIEWSTATUS_SOLIDBKGND | VIEWSTATUS_OPAQUE)

// IAttributedATLDiceControl
public:
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
    LRESULT OnLButtonDblClk(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
    LRESULT OnTimer(UINT_PTR /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
};

