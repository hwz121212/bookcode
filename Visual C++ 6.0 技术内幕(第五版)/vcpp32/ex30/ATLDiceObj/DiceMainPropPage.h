// DiceMainPropPage.h : Declaration of the CDiceMainPropPage

#ifndef __DICEMAINPROPPAGE_H_
#define __DICEMAINPROPPAGE_H_

#include "resource.h"       // main symbols
#include "atldicesrvr.h"

EXTERN_C const CLSID CLSID_DiceMainPropPage;

/////////////////////////////////////////////////////////////////////////////
// CDiceMainPropPage
class ATL_NO_VTABLE CDiceMainPropPage :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CDiceMainPropPage, &CLSID_DiceMainPropPage>,
	public IPropertyPageImpl<CDiceMainPropPage>,
	public CDialogImpl<CDiceMainPropPage>
{
public:
	CDiceMainPropPage() 
	{
		m_dwTitleID = IDS_TITLEDiceMainPropPage;
		m_dwHelpFileID = IDS_HELPFILEDiceMainPropPage;
		m_dwDocStringID = IDS_DOCSTRINGDiceMainPropPage;
	}

	enum {IDD = IDD_DICEMAINPROPPAGE};

DECLARE_REGISTRY_RESOURCEID(IDR_DICEMAINPROPPAGE)

DECLARE_PROTECT_FINAL_CONSTRUCT()

BEGIN_COM_MAP(CDiceMainPropPage) 
	COM_INTERFACE_ENTRY(IPropertyPage)
END_COM_MAP()

BEGIN_MSG_MAP(CDiceMainPropPage)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDlg);
	COMMAND_HANDLER(IDC_COLOR, CBN_SELENDOK, OnColorChange)
	COMMAND_HANDLER(IDC_TIMESTOROLL, EN_CHANGE, OnTimesToRollChange)
	CHAIN_MSG_MAP(IPropertyPageImpl<CDiceMainPropPage>)
END_MSG_MAP()
// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	STDMETHOD(Apply)(void)
	{
		ATLTRACE(_T("CDiceMainPropPage::Apply\n"));
		for (UINT i = 0; i < m_nObjects; i++)
		{

	    USES_CONVERSION;
		ATLTRACE(_T("CDiceMainPropPage::Apply\n"));
		for (UINT i = 0; i < m_nObjects; i++)
		{
            CComQIPtr<IATLDiceObj, &IID_IATLDiceObj> pATLDiceObj(m_ppUnk[i]);
			HWND hWndComboBox = GetDlgItem(IDC_COLOR);
			short nColor  = (short)::SendMessage(hWndComboBox,
		                                         CB_GETCURSEL,
									             0, 0);
			if(nColor >= 0 && nColor <= 2) {
				if FAILED(pATLDiceObj->put_DiceColor(nColor))
				{
					CComPtr<IErrorInfo> pError;
					CComBSTR            strError;
					GetErrorInfo(0, &pError);
					pError->GetDescription(&strError);
					MessageBox(OLE2T(strError), 
							   _T("Error"), 
							   MB_ICONEXCLAMATION);
					return E_FAIL;
				}		
			}
			short nTimesToRoll = (short)GetDlgItemInt(IDC_TIMESTOROLL);
			if FAILED(pATLDiceObj->put_TimesToRoll(nTimesToRoll))
			{
				CComPtr<IErrorInfo> pError;
				CComBSTR            strError;
				GetErrorInfo(0, &pError);
				pError->GetDescription(&strError);
				MessageBox(OLE2T(strError), _T("Error"), MB_ICONEXCLAMATION);
				return E_FAIL;
			}		
		}
		m_bDirty = FALSE;
		return S_OK;


		}
		m_bDirty = FALSE;
		return S_OK;
	}

    STDMETHOD(Show)( UINT nCmdShow ) {
        HRESULT hr;

		USES_CONVERSION;

		if(nCmdShow == SW_SHOW ||
		   nCmdShow == SW_SHOWNORMAL) {
			for (UINT i = 0; i < m_nObjects; i++)
			{
		        CComQIPtr<IATLDiceObj, &IID_IATLDiceObj> pATLDiceObj(m_ppUnk[i]);
				short nColor = 0;

				if FAILED(pATLDiceObj->get_DiceColor(&nColor))
				{
					CComPtr<IErrorInfo> pError;
					CComBSTR            strError;
					GetErrorInfo(0, &pError);
					pError->GetDescription(&strError);
					MessageBox(OLE2T(strError), _T("Error"), MB_ICONEXCLAMATION);
					return E_FAIL;
				}		
				HWND hWndComboBox = GetDlgItem(IDC_COLOR);
				::SendMessage(hWndComboBox,
			                  CB_SETCURSEL,
					          nColor, 0);

				short nTimesToRoll = 0; 
				if FAILED(pATLDiceObj->get_TimesToRoll(&nTimesToRoll))
				{
					CComPtr<IErrorInfo> pError;
					CComBSTR            strError;
					GetErrorInfo(0, &pError);
					pError->GetDescription(&strError);
					MessageBox(OLE2T(strError), _T("Error"), MB_ICONEXCLAMATION);
					return E_FAIL;
				}		
				SetDlgItemInt(IDC_TIMESTOROLL, nTimesToRoll, FALSE);
			}
		}
		m_bDirty = FALSE;

		hr = IPropertyPageImpl<CDiceMainPropPage>::Show(nCmdShow);
        return hr;
	}


    STDMETHOD(SetObjects)(ULONG nObjects, 
		                  IUnknown** ppUnk ) {
		HRESULT hr = IPropertyPageImpl<CDiceMainPropPage>::SetObjects(nObjects, ppUnk);
		return hr;
	}

    LRESULT OnColorChange(WORD wNotify, WORD wID, HWND hWnd, BOOL& bHandled) {
       SetDirty(TRUE);
       return 0;
	}

    LRESULT OnTimesToRollChange(WORD wNotify, WORD wID, HWND hWnd, BOOL& bHandled) {
       SetDirty(TRUE);
       return 0;
	}

    LRESULT OnInitDlg(UINT uMsg, 
		              WPARAM wParam, 
				      LPARAM lParam, 
				      BOOL& bHandled) {
		HWND hWndComboBox = GetDlgItem(IDC_COLOR);
		::SendMessage(hWndComboBox,
		              CB_ADDSTRING,
		              0, (LPARAM)"White");
		::SendMessage(hWndComboBox,
		              CB_ADDSTRING,
		              0, (LPARAM)"Blue");
		::SendMessage(hWndComboBox,
		              CB_ADDSTRING,
		              0, (LPARAM)"Red");
	    bHandled = TRUE;
        return 0;
	}



	
};

#endif //__DICEMAINPROPPAGE_H_
