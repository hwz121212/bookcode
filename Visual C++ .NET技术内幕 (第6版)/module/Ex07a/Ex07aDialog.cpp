// Ex07aDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Ex07a.h"
#include "Ex07aDialog.h"


// CEx07aDialog dialog

IMPLEMENT_DYNAMIC(CEx07aDialog, CDialog)
CEx07aDialog::CEx07aDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CEx07aDialog::IDD, pParent)
	, m_strBio(_T(""))
	, m_nCat(0)
	, m_strDept(_T(""))
	, m_bInsDis(FALSE)
	, m_strEduc(_T(""))
	, m_nLang(0)
	, m_bInsLife(FALSE)
	, m_nLoyal(0)
	, m_bInsMed(FALSE)
	, m_strName(_T(""))
	, m_nRely(0)
	, m_strSkill(_T(""))
	, m_nSsn(0)
{
}

CEx07aDialog::~CEx07aDialog()
{
}

void CEx07aDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_BIO, m_strBio);
	DDV_MaxChars(pDX, m_strBio, 1000);
	DDX_Radio(pDX, IDC_CAT, m_nCat);
	DDX_LBString(pDX, IDC_DEPT, m_strDept);
	DDX_Check(pDX, IDC_DIS, m_bInsDis);
	DDX_CBString(pDX, IDC_EDUC, m_strEduc);
	DDX_CBIndex(pDX, IDC_LANG, m_nLang);
	DDX_Check(pDX, IDC_LIFE, m_bInsLife);
	DDX_Scroll(pDX, IDC_LOYAL, m_nLoyal);
	DDX_Check(pDX, IDC_MED, m_bInsMed);
	DDX_Text(pDX, IDC_NAME, m_strName);
	DDX_Scroll(pDX, IDC_RELY, m_nRely);
	DDX_CBString(pDX, IDC_SKILL, m_strSkill);
	DDX_Text(pDX, IDC_SSN, m_nSsn);
	DDV_MinMaxInt(pDX, m_nSsn, 0, 999999999);
}


BEGIN_MESSAGE_MAP(CEx07aDialog, CDialog)
	ON_BN_CLICKED(IDC_SPECIAL, OnBnClickedSpecial)
	ON_BN_CLICKED(IDC_OK, OnBnClickedOk)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CEx07aDialog message handlers

void CEx07aDialog::OnBnClickedSpecial()
{
	TRACE("CEx07aDialog::OnBnClickedSpecial\n");
}

BOOL CEx07aDialog::OnInitDialog()
{
	// Be careful to call CDialog::OnInitDialog
	//  only once in this function
	CListBox* pLB = (CListBox*) GetDlgItem(IDC_DEPT);
	pLB->InsertString(-1, "Documentation");
	pLB->InsertString(-1, "Accounting");
	pLB->InsertString(-1, "Human Relations");
	pLB->InsertString(-1, "Security");

    CScrollBar* pSB = (CScrollBar*) GetDlgItem(IDC_LOYAL);
    pSB->SetScrollRange(nMin, nMax);

    pSB = (CScrollBar*) GetDlgItem(IDC_RELY);
    pSB->SetScrollRange(nMin, nMax);

	// Call after initialization
	return CDialog::OnInitDialog();
}

void CEx07aDialog::OnOK()
{
	// dummy OnOK function -- do NOT call CDialog::OnOK()
	TRACE("CEx07aDialog::OnOK\n");
}

void CEx07aDialog::OnBnClickedOk()
{
	TRACE("CEx07aDialog::OnClickedOk\n");
	CDialog::OnOK();
}

void CEx07aDialog::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
    int nTemp1, nTemp2;

    nTemp1 = pScrollBar->GetScrollPos();
    switch(nSBCode) {
    case SB_THUMBPOSITION:
        pScrollBar->SetScrollPos(nPos);
        break;
    case SB_LINELEFT: // left arrow button
        nTemp2 = (nMax - nMin) / 10;
        if ((nTemp1 - nTemp2) > nMin) {
            nTemp1 -= nTemp2;
        }
        else {
            nTemp1 = nMin;
        }
        pScrollBar->SetScrollPos(nTemp1);
        break;
    case SB_LINERIGHT: // right arrow button
        nTemp2 = (nMax - nMin) / 10;
        if ((nTemp1 + nTemp2) < nMax) {
            nTemp1 += nTemp2;
        }
        else {
            nTemp1 = nMax;
        }
        pScrollBar->SetScrollPos(nTemp1);
        break;
    }
}
