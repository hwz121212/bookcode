#if !defined(AFX_GPSPUBLIC_H__0A8F2C45_4CAD_4B0E_8852_4258E86B3B8B__INCLUDED_)
#define AFX_GPSPUBLIC_H__0A8F2C45_4CAD_4B0E_8852_4258E86B3B8B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GPSPublic.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGPSPublic window

class CGPSPublic : public CWnd
{
// Construction
public:
	CGPSPublic();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGPSPublic)
	//}}AFX_VIRTUAL

// Implementation
public:
	static CString GetLongitudeType(char type);
	static CString GetLatitudeType(char type);

	static CString GetGPSStatu(char type);
	static CString GetGPSValid(char type);
	static CString GetGPSMode(char type);
	static CString GetMode(char type);
	static CString GetPosType(char type, int stardand);
	static CString GetTextPosStatu(char type);

	static CString GetCommStatu(char type);
	static CString GetDiffSource(char type);
	static CString GetDiffStatu(char type);

	static CString GetDirectXType(char type);
	static CString GetDirectYType(char type);
	static CString GetDirectZType(char type);


	static CString GetFaultStatu(char type);
	static CString GetSaveStatu(char type);
	static CString GetOffsetStatu(char type);
	static CString GetCollectStatu(char type);

	static void ConvertToLongitude(double& longitude, CString inStr);
	static void ConvertToLongitudeHavePoint(double& longitude, CString inStr);
	static void ConvertToLatitude(double& latitude, CString inStr);
	static void ConvertToLatitudeHavePoint(double& latitude, CString inStr);
	static void ConvertToDouble(double& value, CString inStr);
	static void ConvertToDoubleAddPoint(double& value, CString inStr, int pos);
	static void ConvertToInt(int& value, CString inStr);
	static void ConvertToChar(char& value, CString inStr, int length);

	virtual ~CGPSPublic();

	// Generated message map functions
protected:
	//{{AFX_MSG(CGPSPublic)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GPSPUBLIC_H__0A8F2C45_4CAD_4B0E_8852_4258E86B3B8B__INCLUDED_)
