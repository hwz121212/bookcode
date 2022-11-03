// TestDrawDibDoc.cpp : implementation of the CTestDrawDibDoc class
//

#include "stdafx.h"
#include "TestDrawDib.h"

#include "TestDrawDibDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestDrawDibDoc

IMPLEMENT_DYNCREATE(CTestDrawDibDoc, CDocument)

BEGIN_MESSAGE_MAP(CTestDrawDibDoc, CDocument)
	//{{AFX_MSG_MAP(CTestDrawDibDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestDrawDibDoc construction/destruction

CTestDrawDibDoc::CTestDrawDibDoc()
{
	// TODO: add one-time construction code here
	m_Buf=NULL;
}

CTestDrawDibDoc::~CTestDrawDibDoc()
{
	if(m_Buf != NULL) GlobalFree(m_Buf);
}

/////////////////////////////////////////////////////////////////////////////
// CTestDrawDibDoc serialization

void CTestDrawDibDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CTestDrawDibDoc diagnostics

#ifdef _DEBUG
void CTestDrawDibDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTestDrawDibDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CTestDrawDibDoc commands


BOOL CTestDrawDibDoc::OnOpenDocument(LPCTSTR lpszPathName) 
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	 
	// TODO: Add your specialized creation code here
	LPVOID lpmem = NULL;
	CFile file(lpszPathName,CFile::modeRead);
	BITMAPFILEHEADER fileinfo;
	file.Read(&fileinfo,sizeof(fileinfo));
	if(fileinfo.bfType != (('M'<<8)+'B'))
	{
		AfxMessageBox("Not BMP File!");
		return FALSE;
	}
	m_Off=fileinfo.bfOffBits; 

	UINT length = file.GetLength() - sizeof(BITMAPFILEHEADER);
	if(m_Buf != NULL) 
	{
		GlobalFree(m_Buf);
		m_Buf = NULL;
	}
	m_Buf = GlobalAlloc(GMEM_MOVEABLE|GMEM_DISCARDABLE,length);
	lpmem = GlobalLock(m_Buf);
	if(length != file.Read(lpmem,length))
	{
		GlobalUnlock(m_Buf);
		GlobalFree(m_Buf);
		m_Buf = NULL;
		lpmem = NULL;
		AfxMessageBox("Reading File Error");
		return FALSE;
	}
	GlobalUnlock(m_Buf);
	return TRUE;
}
