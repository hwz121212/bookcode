// Ex08bDialog.cpp : implementation file
//

#include "stdafx.h"
#include "Ex08b.h"
#include "Ex08bDialog.h"


// CEx08bDialog dialog

IMPLEMENT_DYNAMIC(CEx08bDialog, CDialog)
CEx08bDialog::CEx08bDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CEx08bDialog::IDD, pParent)
	, m_strDate1(_T(""))
	, m_strDate2(_T(""))
	, m_strDate3(_T(""))
	, m_strDate4(_T(""))
	, m_strDate5(_T(""))
	, m_strIPValue(_T(""))
	, m_strComboEx1(_T(""))
	, m_strComboEx2(_T(""))
{
}

CEx08bDialog::~CEx08bDialog()
{
}

void CEx08bDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_MonthCal1);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_MonthCal2);
	DDX_Control(pDX, IDC_DATETIMEPICKER3, m_MonthCal3);
	DDX_Control(pDX, IDC_DATETIMEPICKER4, m_MonthCal4);
	DDX_Control(pDX, IDC_IPADDRESS1, m_ptrIPCtrl);
	DDX_Control(pDX, IDC_MONTHCALENDAR1, m_MonthCal5);
	DDX_Text(pDX, IDC_STATIC1, m_strDate1);
	DDX_Text(pDX, IDC_STATIC2, m_strDate2);
	DDX_Text(pDX, IDC_STATIC3, m_strDate3);
	DDX_Text(pDX, IDC_STATIC4, m_strDate4);
	DDX_Text(pDX, IDC_STATIC5, m_strDate5);
	DDX_Text(pDX, IDC_STATIC6, m_strIPValue);
	DDX_Text(pDX, IDC_STATIC7, m_strComboEx1);
	DDX_Text(pDX, IDC_STATIC8, m_strComboEx2);
}


BEGIN_MESSAGE_MAP(CEx08bDialog, CDialog)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER1, OnDtnDatetimechangeDatetimepicker1)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER2, OnDtnDatetimechangeDatetimepicker2)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER3, OnDtnDatetimechangeDatetimepicker3)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER4, OnDtnDatetimechangeDatetimepicker4)
	ON_NOTIFY(MCN_SELCHANGE, IDC_MONTHCALENDAR1, OnMcnSelchangeMonthcalendar1)
	ON_NOTIFY(IPN_FIELDCHANGED, IDC_IPADDRESS1, OnIpnFieldchangedIpaddress1)
	ON_CBN_SELCHANGE(IDC_COMBOBOXEX1, OnCbnSelchangeComboboxex1)
	ON_CBN_SELCHANGE(IDC_COMBOBOXEX2, OnCbnSelchangeComboboxex2)
END_MESSAGE_MAP()


// CEx08bDialog message handlers

BOOL CEx08bDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Initialize the IP control
	m_ptrIPCtrl.SetAddress(0L);

    // Initialize IDC_COMBOBOXEX1
    CComboBoxEx* pCombo1 =
        (CComboBoxEx*) GetDlgItem(IDC_COMBOBOXEX1);
	CString rgstrTemp1[3];
    rgstrTemp1[0] = "George";
    rgstrTemp1[1] = "Sandy";
    rgstrTemp1[2] = "Teddy";
    
	COMBOBOXEXITEM cbi1;
	cbi1.mask = CBEIF_TEXT;
	for (int nCount = 0; nCount < 3; nCount++)
	{
		cbi1.iItem = nCount;
		cbi1.pszText = (LPTSTR)(LPCTSTR)rgstrTemp1[nCount];
		cbi1.cchTextMax = 256;
		pCombo1->InsertItem(&cbi1);
	}

    // Initialize IDC_COMBOBOXEX2
    CComboBoxEx* pCombo2 =
        (CComboBoxEx*) GetDlgItem(IDC_COMBOBOXEX2);
    // First let's add images to the items there.
    // We have six images in bitmaps to match to our strings:

    m_imageList.Create(32,16,ILC_MASK,12,4);

    CBitmap bitmap;

    bitmap.LoadBitmap(IDB_BMBIRD);
    m_imageList.Add(&bitmap, (COLORREF)0xFFFFFF);
    bitmap.DeleteObject();

    bitmap.LoadBitmap(IDB_BMBIRDSELECTED);
    m_imageList.Add(&bitmap, (COLORREF)0xFFFFFF);
    bitmap.DeleteObject();
    
    bitmap.LoadBitmap(IDB_BMDOG);
    m_imageList.Add(&bitmap, (COLORREF)0xFFFFFF);
    bitmap.DeleteObject();
    
    bitmap.LoadBitmap(IDB_BMDOGSELECTED);
    m_imageList.Add(&bitmap, (COLORREF)0xFFFFFF);
    bitmap.DeleteObject();    
        
    bitmap.LoadBitmap(IDB_BMFISH);
    m_imageList.Add(&bitmap, (COLORREF)0xFFFFFF);
    bitmap.DeleteObject();
    
    bitmap.LoadBitmap(IDB_BMFISHSELECTED);
    m_imageList.Add(&bitmap, (COLORREF)0xFFFFFF);
    bitmap.DeleteObject();    

    // Set the imagelist
    pCombo2->SetImageList(&m_imageList);
	
	CString rgstrTemp2[3];
    rgstrTemp2[0] = "Tweety";
    rgstrTemp2[1] = "Mack";
    rgstrTemp2[2] = "Jaws";
    
	COMBOBOXEXITEM cbi2;
	cbi2.mask = CBEIF_TEXT|CBEIF_IMAGE|CBEIF_SELECTEDIMAGE|CBEIF_INDENT;
	int nBitmapCount = 0;
	for (int nCount = 0; nCount < 3; nCount++)
	{
		cbi2.iItem = nCount;
		cbi2.pszText = (LPTSTR)(LPCTSTR)rgstrTemp2[nCount];
		cbi2.cchTextMax = 256;
		cbi2.iImage = nBitmapCount++;
		cbi2.iSelectedImage = nBitmapCount++;
		cbi2.iIndent = (nCount & 0x03);
		pCombo2->InsertItem(&cbi2);
	}

    HICON hIcon[8];
    int n;
    // Now let's insert some color icons
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

    static char* color[] = {"white", "black", "red",
                            "blue", "yellow", "cyan",
                            "purple", "green"};

    cbi2.mask = CBEIF_IMAGE|CBEIF_TEXT|CBEIF_OVERLAY|
               CBEIF_SELECTEDIMAGE;

    for (n = 0; n < 8; n++) {
        cbi2.iItem = n;
        cbi2.pszText = color[n];
        cbi2.iImage = n+6; // 6 is the offset into the image list from
        cbi2.iSelectedImage = n+6; // the first six items we added...
        cbi2.iOverlay = n+6;
        int nItem = pCombo2->InsertItem(&cbi2);
        ASSERT(nItem == n);
    }

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CEx08bDialog::OnDtnDatetimechangeDatetimepicker1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
    CTime ct;
    m_MonthCal1.GetTime(ct);
    m_strDate1.Format(_T("%02d/%02d/%2d"),
                      ct.GetMonth(),ct.GetDay(),ct.GetYear());
    UpdateData(FALSE);
	*pResult = 0;
}

void CEx08bDialog::OnDtnDatetimechangeDatetimepicker2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
    CTime ct;
    m_MonthCal2.GetTime(ct);
    m_strDate2.Format(_T("%02d/%02d/%2d"),
                      ct.GetMonth(),ct.GetDay(),ct.GetYear());
    UpdateData(FALSE);
	*pResult = 0;
}

void CEx08bDialog::OnDtnDatetimechangeDatetimepicker3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
    //NOTE: this one can be null!
    CTime ct;
    int nRetVal = m_MonthCal3.GetTime(ct);
    if (nRetVal) //If not zero, it's null; and if it is,
                 // do the right thing.
    {
        m_strDate3 = "NO DATE SPECIFIED!!";
    }
    else
    {
        m_strDate3.Format(_T("%02d/%02d/%2d"),ct.GetMonth(),
                          ct.GetDay(),ct.GetYear());
    }
    UpdateData(FALSE);
	*pResult = 0;
}

void CEx08bDialog::OnDtnDatetimechangeDatetimepicker4(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
    CTime ct;
    m_MonthCal4.GetTime(ct);
    m_strDate4.Format(_T("%02d:%02d:%2d"),
                      ct.GetHour(),ct.GetMinute(),ct.GetSecond());
    UpdateData(FALSE);
	*pResult = 0;
}

void CEx08bDialog::OnMcnSelchangeMonthcalendar1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMSELCHANGE pSelChange = reinterpret_cast<LPNMSELCHANGE>(pNMHDR);
    CTime ct;
    m_MonthCal5.GetCurSel(ct);
    m_strDate5.Format(_T("%02d/%02d/%2d"),
                      ct.GetMonth(),ct.GetDay(),ct.GetYear());
    UpdateData(FALSE);
	*pResult = 0;
}

void CEx08bDialog::OnIpnFieldchangedIpaddress1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMIPADDRESS pIPAddr = reinterpret_cast<LPNMIPADDRESS>(pNMHDR);
    DWORD dwIPAddress;
    m_ptrIPCtrl.GetAddress(dwIPAddress);
    
    m_strIPValue.Format("%d.%d.%d.%d   %x.%x.%x.%x",
        HIBYTE(HIWORD(dwIPAddress)),
        LOBYTE(HIWORD(dwIPAddress)),
        HIBYTE(LOWORD(dwIPAddress)),
        LOBYTE(LOWORD(dwIPAddress)),
        HIBYTE(HIWORD(dwIPAddress)),
        LOBYTE(HIWORD(dwIPAddress)),
        HIBYTE(LOWORD(dwIPAddress)),
        LOBYTE(LOWORD(dwIPAddress)));
    UpdateData(FALSE);
	*pResult = 0;
}

void CEx08bDialog::OnCbnSelchangeComboboxex1()
{
    COMBOBOXEXITEM cbi;
    CString str ("dummy_string");
    CComboBoxEx * pCombo = (CComboBoxEx *)GetDlgItem(IDC_COMBOBOXEX1);
    int nSel = pCombo->GetCurSel();
    cbi.iItem = nSel;
    cbi.pszText = (LPTSTR)(LPCTSTR)str;
    cbi.mask = CBEIF_TEXT;
    cbi.cchTextMax = str.GetLength();
    pCombo->GetItem(&cbi);
    SetDlgItemText(IDC_STATIC7,str);
    return;
}

void CEx08bDialog::OnCbnSelchangeComboboxex2()
{
    COMBOBOXEXITEM cbi;
    CString str ("dummy_string");
    CComboBoxEx * pCombo = (CComboBoxEx *)GetDlgItem(IDC_COMBOBOXEX2);
    int nSel = pCombo->GetCurSel();
    cbi.iItem = nSel;
    cbi.pszText = (LPTSTR)(LPCTSTR)str;
    cbi.mask = CBEIF_TEXT;
    cbi.cchTextMax = str.GetLength();
    pCombo->GetItem(&cbi);
    SetDlgItemText(IDC_STATIC8,str);
    return;
}
