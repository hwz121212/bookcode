// UTil.h: interface for the CUTil class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UTIL_H__02F708FE_5E00_4FC3_AA9A_33A867F50BC4__INCLUDED_)
#define AFX_UTIL_H__02F708FE_5E00_4FC3_AA9A_33A867F50BC4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CUTil  
{
public:
	static bool CreateDir(char *dir);
	CUTil();
	virtual ~CUTil();

protected:
	static bool DirExists(const char *dir);
};

#endif // !defined(AFX_UTIL_H__02F708FE_5E00_4FC3_AA9A_33A867F50BC4__INCLUDED_)
