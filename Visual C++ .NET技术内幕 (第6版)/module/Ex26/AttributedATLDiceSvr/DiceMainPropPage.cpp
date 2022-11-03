// DiceMainPropPage.cpp : Implementation of CDiceMainPropPage

#include "stdafx.h"
#include "DiceMainPropPage.h"


// CDiceMainPropPage


LRESULT CDiceMainPropPage::OnCbnSelchangeDicecolor(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
    // TODO: Add your control notification handler code here
    SetDirty(TRUE);
    return 0;
}

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
    HWND hWndComboBox = GetDlgItem(IDC_DICECOLOR);
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
