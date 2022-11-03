// SphereCommand.h: interface for the CSphereCommand class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPHERECOMMAND_H__FCA72B23_0FFA_45B9_A37B_30FDB2ADBB92__INCLUDED_)
#define AFX_SPHERECOMMAND_H__FCA72B23_0FFA_45B9_A37B_30FDB2ADBB92__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ICommand.h"
#include "Sphere.h"
#include "cadDoc.h"

class CSphereCommand : public CICommand  
{
	CCadDoc* m_pDoc;
	CShape* m_pShape;
public:
	CSphereCommand(CCadDoc* pDoc);
	virtual ~CSphereCommand();
	
	virtual BOOL Execute();
	virtual BOOL Unexecute();
	virtual void OnLButtonDown(UINT nFlags, CPoint point);
	virtual void OnLButtonUp(UINT nFlags, CPoint point);
	virtual void OnMouseMove(UINT nFlags, CPoint point);
};

#endif // !defined(AFX_SPHERECOMMAND_H__FCA72B23_0FFA_45B9_A37B_30FDB2ADBB92__INCLUDED_)
