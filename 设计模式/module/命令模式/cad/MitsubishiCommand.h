// MitsubishiCommand.h: interface for the CMitsubishiCommand class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MITSUBISHICOMMAND_H__92274D7E_F049_45AB_81BB_E25D930077DF__INCLUDED_)
#define AFX_MITSUBISHICOMMAND_H__92274D7E_F049_45AB_81BB_E25D930077DF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ICommand.h"
#include "Mitsubishi.h"
#include "cadDoc.h"

class CMitsubishiCommand : public CICommand  
{
	CShape* m_pShape;
	CCadDoc* m_pDoc;
public:
	CMitsubishiCommand(CCadDoc* pDoc);
	virtual ~CMitsubishiCommand();

	virtual BOOL Execute();
	virtual BOOL Unexecute();
	virtual void OnLButtonDown(UINT nFlags, CPoint point);
	virtual void OnLButtonUp(UINT nFlags, CPoint point);
	virtual void OnMouseMove(UINT nFlags, CPoint point);

};

#endif // !defined(AFX_MITSUBISHICOMMAND_H__92274D7E_F049_45AB_81BB_E25D930077DF__INCLUDED_)
