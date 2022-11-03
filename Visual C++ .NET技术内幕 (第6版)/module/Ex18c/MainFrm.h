// MainFrm.h : interface of the CMainFrame class
//


#pragma once
class CMainFrame : public CFrameWnd
{
	
private:
    enum eView { STRING = 1, HEX = 2 };
    void SwitchToView(eView nView);

protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnViewHexview();
	afx_msg void OnUpdateViewHexview(CCmdUI *pCmdUI);
	afx_msg void OnViewStingview();
	afx_msg void OnUpdateViewStingview(CCmdUI *pCmdUI);
};


