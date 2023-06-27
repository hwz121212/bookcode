// Dialog1.cpp : implementation file
//

#include "stdafx.h"
#include "ex09a.h"
#include "Dialog1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDialog1 dialog


CDialog1::CDialog1(CWnd* pParent /*=NULL*/)
	: CDialog(CDialog1::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDialog1)
	m_strDate1 = _T("");
	m_strDate2 = _T("");
	m_strDate3 = _T("");
	m_strDate4 = _T("");
	m_strDate5 = _T("");
	m_strIPValue = _T("");
	m_strComboEx1 = _T("");
	m_strComboEx2 = _T("");
	//}}AFX_DATA_INIT
}


void CDialog1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDialog1)
	DDX_Control(pDX, IDC_MONTHCALENDAR1, m_MonthCal5);
	DDX_Control(pDX, IDC_DATETIMEPICKER4, m_MonthCal4);
	DDX_Control(pDX, IDC_DATETIMEPICKER3, m_MonthCal3);
	DDX_Control(pDX, IDC_DATETIMEPICKER2, m_MonthCal2);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_MonthCal1);
	DDX_Control(pDX, IDC_IPADDRESS1, m_ptrIPCtrl);
	DDX_Text(pDX, IDC_STATIC1, m_strDate1);
	DDX_Text(pDX, IDC_STATIC2, m_strDate2);
	DDX_Text(pDX, IDC_STATIC3, m_strDate3);
	DDX_Text(pDX, IDC_STATIC4, m_strDate4);
	DDX_Text(pDX, IDC_STATIC5, m_strDate5);
	DDX_Text(pDX, IDC_STATIC6, m_strIPValue);
	DDX_Text(pDX, IDC_STATIC7, m_strComboEx1);
	DDX_Text(pDX, IDC_STATIC8, m_strComboEx2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDialog1, CDialog)
	//{{AFX_MSG_MAP(CDialog1)
	ON_CBN_SELCHANGE(IDC_COMBOBOXEX1, OnSelchangeComboboxex1)
	ON_CBN_SELCHANGE(IDC_COMBOBOXEX2, OnSelchangeComboboxex2)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER1, OnDatetimechangeDatetimepicker1)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER2, OnDatetimechangeDatetimepicker2)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER3, OnDatetimechangeDatetimepicker3)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER4, OnDatetimechangeDatetimepicker4)
	ON_NOTIFY(IPN_FIELDCHANGED, IDC_IPADDRESS1, OnFieldchangedIpaddress1)
	ON_NOTIFY(MCN_SELCHANGE, IDC_MONTHCALENDAR1, OnSelchangeMonthcalendar1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDialog1 message handlers

BOOL CDialog1::OnInitDialog() 
{
	HICON hIcon[8];
	int n;
	COMBOBOXEXITEM	cbi;

	CDialog::OnInitDialog();

	//Initialize the IP Address control with all 0's.
	m_ptrIPCtrl.SetAddress(0L);

	//Initialize the IDC_COMBOBOXEX2
	CComboBoxEx* pCombo =
		(CComboBoxEx*) GetDlgItem(IDC_COMBOBOXEX2);
	//First let's add images to the items there.
	//We have 6 images in bitmaps to match to our strings:

	//CImageList * pImageList = new CImageList();
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

	//Set the imagelist.
	pCombo->SetImageList(&m_imageList);

	cbi.mask = CBEIF_IMAGE|CBEIF_SELECTEDIMAGE|CBEIF_INDENT;
	CString strTemp;
	int nBitmapCount = 0;
	for (int nCount = 0;nCount < 3;nCount++)
	{
		cbi.iItem = nCount;
		cbi.pszText = (LPTSTR)(LPCTSTR)strTemp;
		cbi.cchTextMax = 256;
		pCombo->GetItem(&cbi);
		cbi.iImage = nBitmapCount++;
		cbi.iSelectedImage = nBitmapCount++;
		cbi.iIndent = (nCount & 0x03);
		pCombo->SetItem(&cbi);

	}

	//Now let's insert some color icons

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


	
	cbi.mask = CBEIF_IMAGE|CBEIF_TEXT|CBEIF_OVERLAY|CBEIF_SELECTEDIMAGE;

	for (n = 0; n < 8; n++) {
		cbi.iItem = n;
		cbi.pszText = color[n];
		cbi.iImage = n+6;
		cbi.iSelectedImage = n+6;
		cbi.iOverlay = n+6;
		int nItem = pCombo->InsertItem(&cbi);
		ASSERT(nItem == n);
	}


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//
// Get the selected item from the combo and display it in the static
// control.
//
// Since this is a CComboBoxEx, there is a good bit of logic that has
// to happen...
//
void CDialog1::OnSelchangeComboboxex1() 
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

void CDialog1::OnSelchangeComboboxex2() 
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

void CDialog1::OnDatetimechangeDatetimepicker1(NMHDR* pNMHDR, LRESULT* pResult) 
{

	CTime ct;
	m_MonthCal1.GetTime(ct);
	m_strDate1.Format(_T("%02d/%02d/%2d"),ct.GetMonth(),ct.GetDay(),ct.GetYear());
	UpdateData(FALSE);
	*pResult = 0;
}

void CDialog1::OnDatetimechangeDatetimepicker2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	CTime ct;
	m_MonthCal2.GetTime(ct);
	m_strDate2.Format(_T("%02d/%02d/%2d"),ct.GetMonth(),ct.GetDay(),ct.GetYear());
	UpdateData(FALSE);

	*pResult = 0;
}

void CDialog1::OnDatetimechangeDatetimepicker3(NMHDR* pNMHDR, LRESULT* pResult) 
{
	//NOTE: this one can be null!
	CTime ct;
	int nRetVal = m_MonthCal3.GetTime(ct);
	if (nRetVal)
	{
		m_strDate3 = "NO DATE SPECIFIED!!";
	}
	else
	{
		m_strDate3.Format(_T("%02d/%02d/%2d"),ct.GetMonth(),ct.GetDay(),ct.GetYear());
	}
	UpdateData(FALSE);
	*pResult = 0;
}

void CDialog1::OnDatetimechangeDatetimepicker4(NMHDR* pNMHDR, LRESULT* pResult) 
{
	
	CTime ct;
	m_MonthCal4.GetTime(ct);
	m_strDate4.Format(_T("%02d:%02d:%2d"),ct.GetHour(),ct.GetMinute(),ct.GetSecond());
	UpdateData(FALSE);
	*pResult = 0;
}

void CDialog1::OnFieldchangedIpaddress1(NMHDR* pNMHDR, LRESULT* pResult) 
{
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
		LOBYTE(LOWORD(dwIPAddress))
		);
	UpdateData(FALSE);
	*pResult = 0;
}

void CDialog1::OnSelchangeMonthcalendar1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	//At the time of writing, there was a problem with the
	// CMonthCalCtrl::GetCurSel method. Below is the workaround
	// for that problem. Ideally the first three lines of this
	// method would be replaced with the following:

	//CTime ct;
	//m_MonthCal5.GetCurSel(ct);
	//m_strDate5.Format(_T("%02d/%02d/%2d"),ct.GetMonth(),ct.GetDay(),ct.GetYear());
	
	SYSTEMTIME sysTime;
	::SendMessage(m_MonthCal5.GetSafeHwnd(), MCM_GETCURSEL, 0, (LPARAM)&sysTime);
	m_strDate5.Format(_T("%02d/%02d/%02d"), sysTime.wMonth, sysTime.wDay, sysTime.wYear);

	UpdateData(FALSE);	
	*pResult = 0;
}
