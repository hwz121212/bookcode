// CDiceMainPropPage.cpp : Implementation of CDiceMainPropPage

#include "stdafx.h"
#include "CDiceMainPropPage.h"


// CDiceMainPropPage

LRESULT CDiceMainPropPage::OnEnChangeTimestoroll(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    // TODO:  If this is a RICHEDIT control, the control will not
    // send this notification unless you override the __super::OnInitDialog()
    // function and call CRichEditCtrl().SetEventMask()
    // with the ENM_CHANGE flag ORed into the mask.

    // TODO:  Add your control notification handler code here
    SetDirty(TRUE);
    return 0;
}

LRESULT CDiceMainPropPage::OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
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
    return TRUE;
}

LRESULT CDiceMainPropPage::OnCbnSelchangeColor(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    SetDirty(TRUE);
    return 0;
}
