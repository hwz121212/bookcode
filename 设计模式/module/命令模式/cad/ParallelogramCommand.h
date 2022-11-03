// ParallelogramCommand.h: interface for the CParallelogramCommand class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PARALLELOGRAMCOMMAND_H__9FCC55B5_361E_43A4_A191_ED8D7FE5161E__INCLUDED_)
#define AFX_PARALLELOGRAMCOMMAND_H__9FCC55B5_361E_43A4_A191_ED8D7FE5161E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ICommand.h"
#include "cadDoc.h"
#include "Parallelogram.h"

class CParallelogramCommand : public CICommand  
{
	CShape* m_pShape;
	CCadDoc* m_pDoc;
public:
	CParallelogramCommand(CCadDoc* pDoc);
	virtual ~CParallelogramCommand();

	virtual BOOL Execute();
	virtual BOOL Unexecute();
	virtual void OnLButtonDown(UINT nFlags, CPoint point);
	virtual void OnLButtonUp(UINT nFlags, CPoint point);
	virtual void OnMouseMove(UINT nFlags, CPoint point);

};

#endif // !defined(AFX_PARALLELOGRAMCOMMAND_H__9FCC55B5_361E_43A4_A191_ED8D7FE5161E__INCLUDED_)
