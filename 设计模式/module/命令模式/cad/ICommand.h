// ICommand.h: interface for the CICommand class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ICOMMAND_H__F606FC5A_4B16_4194_BE1C_29302D450E05__INCLUDED_)
#define AFX_ICOMMAND_H__F606FC5A_4B16_4194_BE1C_29302D450E05__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CICommand : public CObject  
{
public:
	virtual BOOL Execute() = 0;
	virtual BOOL Unexecute() = 0;

	CICommand();
	virtual ~CICommand();
	virtual void OnLButtonDown(UINT nFlags, CPoint point) = 0;
	virtual void OnLButtonUp(UINT nFlags, CPoint point) = 0;
	virtual void OnMouseMove(UINT nFlags, CPoint point) = 0;

};

#endif // !defined(AFX_ICOMMAND_H__F606FC5A_4B16_4194_BE1C_29302D450E05__INCLUDED_)
