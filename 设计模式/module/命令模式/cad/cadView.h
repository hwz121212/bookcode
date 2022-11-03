// cadView.h : interface of the CCadView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_CADVIEW_H__6188166C_7C5F_4163_B786_66D3F552111D__INCLUDED_)
#define AFX_CADVIEW_H__6188166C_7C5F_4163_B786_66D3F552111D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "MemDC.h"
#include "LineCommand.h"
#include "EllipseCommand.h"
#include "RectangleCommand.h"
#include "CommandManager.h"
#include "TriangleCommand.h"
#include "PentagonCommand.h"
#include "PentagramCommand.h"
#include "RightTriangleCommand.h"
#include "CircleCommand.h"
#include "ParallelogramCommand.h"
#include "DiamondCommand.h"
#include "LadderCommand.h"
#include "HexagonalCommand.h"
#include "ArcCommand.h"
#include "CubeCommand.h"
#include "TetrahedronCommand.h"
#include "MitsubishiCommand.h"
#include "CylinderCommand.h"
#include "SphereCommand.h"
#include "OctaCommand.h"
#include "RyotaiCommand.h"
#include "ConeCommand.h"


class CCadView : public CView
{
	CICommand* m_pCommand;
	int m_nShapeType;
	CCommandManager	 m_CommandManager;
protected: // create from serialization only
	CCadView();
	DECLARE_DYNCREATE(CCadView)

// Attributes
public:
	CCadDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCadView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:

	CICommand* CreateCommand();
	virtual ~CCadView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CCadView)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLine();
	afx_msg void OnRectangle();
	afx_msg void OnTriangle();
	afx_msg void OnEllipse();
	afx_msg void OnSelect();
	afx_msg void OnRedo();
	afx_msg void OnUndo();
	afx_msg void OnUpdateUndo(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRedo(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLine(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTrangle(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRectangle(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEllipse(CCmdUI* pCmdUI);
	afx_msg void OnPentagon();
	afx_msg void OnUpdatePentagon(CCmdUI* pCmdUI);
	afx_msg void OnPentagram();
	afx_msg void OnUpdatePentagram(CCmdUI* pCmdUI);
	afx_msg void OnRighttriangle();
	afx_msg void OnUpdateRighttriangle(CCmdUI* pCmdUI);
	afx_msg void OnCircle();
	afx_msg void OnUpdateCircle(CCmdUI* pCmdUI);
	afx_msg void OnParallelogram();
	afx_msg void OnUpdateParallelogram(CCmdUI* pCmdUI);
	afx_msg void OnDiamond();
	afx_msg void OnUpdateDiamond(CCmdUI* pCmdUI);
	afx_msg void OnLadder();
	afx_msg void OnUpdateLadder(CCmdUI* pCmdUI);
	afx_msg void OnHexagonal();
	afx_msg void OnUpdateHexagonal(CCmdUI* pCmdUI);
	afx_msg void OnArc();
	afx_msg void OnUpdateArc(CCmdUI* pCmdUI);
	afx_msg void OnCube();
	afx_msg void OnUpdateCube(CCmdUI* pCmdUI);
	afx_msg void OnTetrahedron();
	afx_msg void OnUpdateTetrahedron(CCmdUI* pCmdUI);
	afx_msg void OnMitsubishi();
	afx_msg void OnUpdateMitsubishi(CCmdUI* pCmdUI);
	afx_msg void OnCylinder();
	afx_msg void OnUpdateCylinder(CCmdUI* pCmdUI);
	afx_msg void OnSphere();
	afx_msg void OnUpdateSphere(CCmdUI* pCmdUI);
	afx_msg void OnOcta();
	afx_msg void OnUpdateOcta(CCmdUI* pCmdUI);
	afx_msg void OnRyotai();
	afx_msg void OnUpdateRyotai(CCmdUI* pCmdUI);
	afx_msg void OnCone();
	afx_msg void OnUpdateCone(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSelect(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEditUndo();
	afx_msg void OnEditRedo();
};

#ifndef _DEBUG  // debug version in cadView.cpp
inline CCadDoc* CCadView::GetDocument()
   { return (CCadDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CADVIEW_H__6188166C_7C5F_4163_B786_66D3F552111D__INCLUDED_)
