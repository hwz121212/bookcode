// GpsServerView.h : interface of the CGpsServerView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GPSSERVERVIEW_H__68ED00ED_E282_4A20_A991_200ABB1A26A2__INCLUDED_)
#define AFX_GPSSERVERVIEW_H__68ED00ED_E282_4A20_A991_200ABB1A26A2__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CGpsServerView : public CHtmlView
{
protected: // create from serialization only
	CGpsServerView();
	DECLARE_DYNCREATE(CGpsServerView)
	

// Attributes
public:
	CGpsServerDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGpsServerView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual void OnInitialUpdate();
	//}}AFX_VIRTUAL

// Implementation
public:
	CMainFrame* GetMainFrame();
	void DrawPositionOnMap(GPSPack *pack);
	
	
	virtual ~CGpsServerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	void InitMap();	
	void ShowPoint(double x, double y, CString name);
	void ExecJavaScript(CString js);

// Generated message map functions
protected:

	//{{AFX_MSG(CGpsServerView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	

	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in GpsServerView.cpp
inline CGpsServerDoc* CGpsServerView::GetDocument()
   { return (CGpsServerDoc*)m_pDocument; }
#endif


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GPSSERVERVIEW_H__68ED00ED_E282_4A20_A991_200ABB1A26A2__INCLUDED_)
