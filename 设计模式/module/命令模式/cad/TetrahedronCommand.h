// TetrahedronCommand.h: interface for the CTetrahedronCommand class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TETRAHEDRONCOMMAND_H__8429D5A9_2EDF_44B5_A7BB_F66637E54A6D__INCLUDED_)
#define AFX_TETRAHEDRONCOMMAND_H__8429D5A9_2EDF_44B5_A7BB_F66637E54A6D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ICommand.h"
#include "Tetrahedron.h"
#include "cadDoc.h"

class CTetrahedronCommand : public CICommand  
{
	CCadDoc* m_pDoc;
	CShape* m_pShape;
public:
	CTetrahedronCommand(CCadDoc* pDoc);
	virtual ~CTetrahedronCommand();
	virtual BOOL Execute();
	virtual BOOL Unexecute();
	virtual void OnLButtonDown(UINT nFlags, CPoint point);
	virtual void OnLButtonUp(UINT nFlags, CPoint point);
	virtual void OnMouseMove(UINT nFlags, CPoint point);
};

#endif // !defined(AFX_TETRAHEDRONCOMMAND_H__8429D5A9_2EDF_44B5_A7BB_F66637E54A6D__INCLUDED_)
