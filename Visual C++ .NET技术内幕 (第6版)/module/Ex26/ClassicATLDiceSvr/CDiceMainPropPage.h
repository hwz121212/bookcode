// CDiceMainPropPage.h : Declaration of the CDiceMainPropPage


#pragma once

#include "resource.h"       // main symbols
#include "ClassicATLDiceSvr.h"

// CDiceMainPropPage

class ATL_NO_VTABLE CDiceMainPropPage :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CDiceMainPropPage, &CLSID_CDiceMainPropPage>,
	public IPropertyPageImpl<CDiceMainPropPage>,
	public CDialogImpl<CDiceMainPropPage>
{
public:
	CDiceMainPropPage() 
	{
		m_dwTitleID = IDS_TITLECDiceMainPropPage;
		m_dwHelpFileID = IDS_HELPFILECDiceMainPropPage;
		m_dwDocStringID = IDS_DOCSTRINGCDiceMainPropPage;
	}

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	
	void FinalRelease() 
	{
	}

	enum {IDD = IDD_CDICEMAINPROPPAGE};

DECLARE_REGISTRY_RESOURCEID(IDR_CDICEMAINPROPPAGE)


BEGIN_COM_MAP(CDiceMainPropPage) 
	COM_INTERFACE_ENTRY(IPropertyPage)
END_COM_MAP()

BEGIN_MSG_MAP(CDiceMainPropPage)
    COMMAND_HANDLER(IDC_TIMESTOROLL, EN_CHANGE, OnEnChangeTimestoroll)
    MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
    COMMAND_HANDLER(IDC_COLOR, CBN_SELCHANGE, OnCbnSelchangeColor)
    CHAIN_MSG_MAP(IPropertyPageImpl<CDiceMainPropPage>)
END_MSG_MAP()

// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnUIChange(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled)
	{
		wNotifyCode; wID; hWndCtl; bHandled;
		SetDirty(true);
		return 0;
	}

	typedef IPropertyPageImpl<CDiceMainPropPage> PPGBaseClass;

	STDMETHOD(Apply)(void)
	{
        USES_CONVERSION;
	   	ATLTRACE(_T("CDiceMainPropPage::Apply\n"));
    	for (UINT i = 0; i < m_nObjects; i++)
	   	{
            CComQIPtr<IClassicATLDiceControl, 
                   &IID_IClassicATLDiceControl> pClassicATLDiceControl(m_ppUnk[i]);
    		HWND hWndComboBox = GetDlgItem(IDC_COLOR);
	   		short nColor  = (short)::SendMessage(hWndComboBox,
	                                             CB_GETCURSEL,
			   						             0, 0);
   			if(nColor >= 0 && nColor <= 2) {
    			if FAILED(pClassicATLDiceControl->put_DiceColor(nColor))
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
    		if FAILED(pClassicATLDiceControl->put_TimesToRoll(nTimesToRoll))
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

	STDMETHOD(Activate)(HWND hWndParent, LPCRECT prc, BOOL bModal)
	{
		// If we don't have any objects, this method should not be called
		// Note that OleCreatePropertyFrame will call Activate even if a call to SetObjects fails, so this check is required
		if (!m_ppUnk)
			return E_UNEXPECTED;

		// Use Activate to update the property page's UI with information
		// obtained from the objects in the m_ppUnk array

		// We update the page to display the Name and ReadOnly properties of the document

		// Call the base class
        HRESULT hr;
        hr = IPropertyPageImpl<CDiceMainPropPage>::Activate(hWndParent, prc, bModal);
		if (FAILED(hr))
			return hr;

		for (UINT i = 0; i < m_nObjects; i++)
        {
		    CComQIPtr<IClassicATLDiceControl, 
                &IID_IClassicATLDiceControl> pClassicATLDiceControl(m_ppUnk[i]);
			short nColor = 0;

			if FAILED(pClassicATLDiceControl->get_DiceColor(&nColor))
			{
                return E_FAIL;
			}		
			HWND hWndComboBox = GetDlgItem(IDC_COLOR);
			::SendMessage(hWndComboBox,
			              CB_SETCURSEL,
					      nColor, 0);

			short nTimesToRoll = 0; 
			if FAILED(pClassicATLDiceControl->get_TimesToRoll(&nTimesToRoll))
			{
                return E_FAIL;
			}		
			SetDlgItemInt(IDC_TIMESTOROLL, nTimesToRoll, FALSE);
		}
		return S_OK;
	}


    LRESULT OnEnChangeTimestoroll(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
    LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    LRESULT OnCbnSelchangeColor(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
};


OBJECT_ENTRY_AUTO(__uuidof(CDiceMainPropPage), CDiceMainPropPage)
