#if !defined(AFX_PROPERTIES_H__32F4CF1C_8F40_4FE4_83E7_11C890E2B9F9__INCLUDED_)
#define AFX_PROPERTIES_H__32F4CF1C_8F40_4FE4_83E7_11C890E2B9F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


// Dispatch interfaces referenced by this interface
class CProperty;

/////////////////////////////////////////////////////////////////////////////
// CProperties wrapper class

class CProperties : public COleDispatchDriver
{
public:
	CProperties() {}		// Calls COleDispatchDriver default constructor
	CProperties(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CProperties(const CProperties& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetCount();
	void Refresh();
	CProperty GetItem(const VARIANT& Index);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PROPERTIES_H__32F4CF1C_8F40_4FE4_83E7_11C890E2B9F9__INCLUDED_)
