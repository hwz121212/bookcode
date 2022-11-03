#pragma once
#define WM_USERAPPLY WM_USER + 5
extern CView* g_pView;

// CPage1 dialog

class CPage1 : public CPropertyPage
{
	DECLARE_DYNAMIC(CPage1)

public:
	CPage1();
	virtual ~CPage1();

// Dialog Data
	enum { IDD = IDD_PAGE1 };
	int     m_nFont;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnApply();
    virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()
};
#pragma once


// CPage2 dialog

class CPage2 : public CPropertyPage
{
	DECLARE_DYNAMIC(CPage2)

public:
	CPage2();
	virtual ~CPage2();

// Dialog Data
	enum { IDD = IDD_PAGE2 };
	BOOL m_bBold;
	BOOL m_bItalic;
	BOOL m_bUnderline;


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};
#pragma once


// CPage3 dialog

class CPage3 : public CPropertyPage
{
	DECLARE_DYNAMIC(CPage3)

public:
	CPage3();
	virtual ~CPage3();

// Dialog Data
	enum { IDD = IDD_PAGE3 };
	int m_nColor;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};
#pragma once


// CPage4 dialog

class CPage4 : public CPropertyPage
{
	DECLARE_DYNAMIC(CPage4)

public:
	CPage4();
	virtual ~CPage4();

// Dialog Data
	enum { IDD = IDD_PAGE4 };
	int m_nFontSize;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};
#pragma once



// CFontSheet

class CFontSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CFontSheet)

public:
    CPage1 m_page1;
    CPage2 m_page2;
    CPage3 m_page3;
    CPage4 m_page4;

public:
	CFontSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CFontSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	virtual ~CFontSheet();

protected:
	DECLARE_MESSAGE_MAP()
};


