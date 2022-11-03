// PentagramCommand.h: interface for the CPentagramCommand class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PENTAGRAMCOMMAND_H__0F0037BF_36EC_4D9A_96A0_8672200A38FC__INCLUDED_)
#define AFX_PENTAGRAMCOMMAND_H__0F0037BF_36EC_4D9A_96A0_8672200A38FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Shape.h"
#include "ICommand.h"
#include "cadDoc.h"
#include "Pentagram.h"

class CPentagramCommand : public CICommand  
{
	CShape* m_pShape;
	CCadDoc* m_pDoc;
public:
	CPentagramCommand(CCadDoc* pDoc);
	virtual ~CPentagramCommand();
	virtual BOOL Execute();
	virtual BOOL Unexecute();
	virtual void OnLButtonDown(UINT nFlags, CPoint point);
	virtual void OnLButtonUp(UINT nFlags, CPoint point);
	virtual void OnMouseMove(UINT nFlags, CPoint point);
};

#endif // !defined(AFX_PENTAGRAMCOMMAND_H__0F0037BF_36EC_4D9A_96A0_8672200A38FC__INCLUDED_)
