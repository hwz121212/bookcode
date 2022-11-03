// Ex08aDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Ex08a.h"
#include "Ex08aDialog.h"

double CEx08aDialog::dValue[5] = {4.0, 5.6, 8.0, 11.0, 16.0};

// CEx08aDialog dialog

IMPLEMENT_DYNAMIC(CEx08aDialog, CDialog)
CEx08aDialog::CEx08aDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CEx08aDialog::IDD, pParent)
	, m_dSpin(0)
{
	m_nProgress = 0;
	m_nSlider1 = 0;
	m_nSlider2 = 0;
}

CEx08aDialog::~CEx08aDialog()
{
}

void CEx08aDialog::DoDataExchange(CDataExchange* pDX)
{
	if (pDX->m_bSaveAndValidate) {
		TRACE("updating slider data members\n");
		CSliderCtrl* pSlide1 =
			(CSliderCtrl*) GetDlgItem(IDC_SLIDER1);
		m_nSlider1 = pSlide1->GetPos();
		CSliderCtrl* pSlide2 =
			(CSliderCtrl*) GetDlgItem(IDC_SLIDER2);
		m_nSlider2 = pSlide2->GetPos();
	}

	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_BUDDY_SPIN1, m_dSpin);
}


BEGIN_MESSAGE_MAP(CEx08aDialog, CDialog)
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LISTVIEW1, OnLvnItemchangedListview1)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREEVIEW1, OnTvnSelchangedTreeview1)
END_MESSAGE_MAP()


// CEx08aDialog message handlers

BOOL CEx08aDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

    // Progress control
    CProgressCtrl* pProg = 
        (CProgressCtrl*) GetDlgItem(IDC_PROGRESS1);
    pProg->SetRange(0, 100);
    pProg->SetPos(m_nProgress);

    // Slider control
    CString strText1;
    CSliderCtrl* pSlide1 = 
        (CSliderCtrl*) GetDlgItem(IDC_SLIDER1);
    pSlide1->SetRange(0, 100);
    pSlide1->SetPos(m_nSlider1);
    strText1.Format("%d", pSlide1->GetPos());
    SetDlgItemText(IDC_STATIC_SLIDER1, strText1);

    CString strText2;
    CSliderCtrl* pSlide2 = 
        (CSliderCtrl*) GetDlgItem(IDC_SLIDER2);
    pSlide2->SetRange(0, 4);
    pSlide2->SetPos(m_nSlider2);
    strText2.Format("%3.1f", dValue[pSlide2->GetPos()]);
    SetDlgItemText(IDC_STATIC_SLIDER2, strText2);

    // Spin control
    CSpinButtonCtrl* pSpin =
        (CSpinButtonCtrl*) GetDlgItem(IDC_SPIN1);
    pSpin->SetRange(0, 100);
    pSpin->SetPos((int) (m_dSpin * 10.0));

    // Icons
    HICON hIcon[8];
    int n;
    m_imageList.Create(16, 16, 0, 8, 8); // 32, 32 for large icons
    hIcon[0] = AfxGetApp()->LoadIcon(IDI_WHITE);
    hIcon[1] = AfxGetApp()->LoadIcon(IDI_BLACK);
    hIcon[2] = AfxGetApp()->LoadIcon(IDI_RED);
    hIcon[3] = AfxGetApp()->LoadIcon(IDI_BLUE);
    hIcon[4] = AfxGetApp()->LoadIcon(IDI_YELLOW);   
    hIcon[5] = AfxGetApp()->LoadIcon(IDI_CYAN);
    hIcon[6] = AfxGetApp()->LoadIcon(IDI_PURPLE);
    hIcon[7] = AfxGetApp()->LoadIcon(IDI_GREEN);
    for (n = 0; n < 8; n++) {
        m_imageList.Add(hIcon[n]);
    }

	// List control
	static char* color[] = {"white", "black", "red",
                            "blue", "yellow", "cyan",
                            "purple", "green"};
    CListCtrl* pList = 
        (CListCtrl*) GetDlgItem(IDC_LISTVIEW1);
    pList->SetImageList(&m_imageList, LVSIL_SMALL); 
    for (n = 0; n < 8; n++) {
        pList->InsertItem(n, color[n], n); 
    }
    pList->SetBkColor(RGB(0, 255, 255)); // UGLY!
    pList->SetTextBkColor(RGB(0, 255, 255));

    // Tree control
    CTreeCtrl* pTree = (CTreeCtrl*) GetDlgItem(IDC_TREEVIEW1);
    pTree->SetImageList(&m_imageList, TVSIL_NORMAL);
    // tree structure common values
    TV_INSERTSTRUCT tvinsert;
    tvinsert.hParent = NULL;
    tvinsert.hInsertAfter = TVI_LAST;
    tvinsert.item.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE |
                         TVIF_TEXT;
    tvinsert.item.hItem = NULL; 
    tvinsert.item.state = 0;
    tvinsert.item.stateMask = 0;
    tvinsert.item.cchTextMax = 6;
    tvinsert.item.iSelectedImage = 1;
    tvinsert.item.cChildren = 0;
    tvinsert.item.lParam = 0;
    // top level
    tvinsert.item.pszText = "Homer";
    tvinsert.item.iImage = 2;
    HTREEITEM hDad = pTree->InsertItem(&tvinsert);
    tvinsert.item.pszText = "Marge";
    HTREEITEM hMom = pTree->InsertItem(&tvinsert);
    // second level     
    tvinsert.hParent = hDad;
    tvinsert.item.pszText = "Bart";
    tvinsert.item.iImage = 3;
    pTree->InsertItem(&tvinsert);
    tvinsert.item.pszText = "Lisa";
    pTree->InsertItem(&tvinsert);
    // second level
    tvinsert.hParent = hMom;
    tvinsert.item.pszText = "Bart";
    tvinsert.item.iImage = 4;
    pTree->InsertItem(&tvinsert);
    tvinsert.item.pszText = "Lisa";
    pTree->InsertItem(&tvinsert);
    tvinsert.item.pszText = "Dilbert";
    HTREEITEM hOther = pTree->InsertItem(&tvinsert);
    // third level
    tvinsert.hParent = hOther;
    tvinsert.item.pszText = "Dogbert";
    tvinsert.item.iImage = 7;
    pTree->InsertItem(&tvinsert);
    tvinsert.item.pszText = "Ratbert";
    pTree->InsertItem(&tvinsert);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CEx08aDialog::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    CSliderCtrl* pSlide = (CSliderCtrl*) pScrollBar;
    CString strText;

    // Two sliders are sending
    //  HSCROLL messages (different processing)
    switch(pScrollBar->GetDlgCtrlID()) {
    case IDC_SLIDER1:
		strText.Format("%d", pSlide->GetPos());
		SetDlgItemText(IDC_STATIC_SLIDER1, strText);
		break;
    case IDC_SLIDER2:
        strText.Format("%3.1f", dValue[pSlide->GetPos()]);
        SetDlgItemText(IDC_STATIC_SLIDER2, strText);
        break;
    }
}

void CEx08aDialog::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    if (nSBCode == SB_ENDSCROLL) {
        return; // Reject spurious messages
    }
    // Process scroll messages from IDC_SPIN1 only
    if (pScrollBar->GetDlgCtrlID() == IDC_SPIN1) {
        CString strValue;
        strValue.Format("%3.1f", (double) nPos / 10.0);
        ((CSpinButtonCtrl*) pScrollBar)->GetBuddy()
                                       ->SetWindowText(strValue);
    }

	CDialog::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CEx08aDialog::OnLvnItemchangedListview1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
    CListCtrl* pList =
        (CListCtrl*) GetDlgItem(IDC_LISTVIEW1);
    int nSelected = pNMLV->iItem;
    if (nSelected >= 0) {
        CString strItem = pList->GetItemText(nSelected, 0);
         SetDlgItemText(IDC_STATIC_LISTVIEW1, strItem);
    }
	*pResult = 0;
}

void CEx08aDialog::OnTvnSelchangedTreeview1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
    CTreeCtrl* pTree = (CTreeCtrl*) GetDlgItem(IDC_TREEVIEW1);
    HTREEITEM hSelected = pNMTreeView->itemNew.hItem;
    if (hSelected != NULL) {
        char text[31];
        TV_ITEM item;
        item.mask = TVIF_HANDLE | TVIF_TEXT;
        item.hItem = hSelected;
        item.pszText = text;
        item.cchTextMax = 30;
        VERIFY(pTree->GetItem(&item));
        SetDlgItemText(IDC_STATIC_TREEVIEW1, text);
    }
	*pResult = 0;
}
