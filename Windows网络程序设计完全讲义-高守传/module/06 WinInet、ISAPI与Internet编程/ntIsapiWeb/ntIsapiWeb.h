#if !defined(AFX_NTISAPIWEB_H__F753B261_BF9D_43EE_AFC1_524137F915EA__INCLUDED_)
#define AFX_NTISAPIWEB_H__F753B261_BF9D_43EE_AFC1_524137F915EA__INCLUDED_

// NTISAPIWEB.H - Header file for your Internet Server
//    ntIsapiWeb Extension

#include "resource.h"

class CNtIsapiWebExtension:public CHttpServer
{
public:
	CNtIsapiWebExtension();
	~CNtIsapiWebExtension();

// Overrides
	// ClassWizard generated virtual function overrides
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//{{AFX_VIRTUAL(CNtIsapiWebExtension)
	public:
	virtual BOOL GetExtensionVersion(HSE_VERSION_INFO* pVer);
	//}}AFX_VIRTUAL
	virtual BOOL TerminateExtension(DWORD dwFlags);

	// TODO: Add handlers for your commands here.
	// For example:
	void Test(CHttpServerContext* pCtxt, double m_Height, double m_Weight, LPTSTR m_Sex);
	void Default(CHttpServerContext* pCtxt);

	DECLARE_PARSE_MAP()

	//{{AFX_MSG(CNtIsapiWebExtension)
	//}}AFX_MSG
};


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NTISAPIWEB_H__F753B261_BF9D_43EE_AFC1_524137F915EA__INCLUDED)
