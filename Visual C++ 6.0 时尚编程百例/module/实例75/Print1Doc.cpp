// Print1Doc.cpp : implementation of the CPrint1Doc class
//

#include "stdafx.h"
#include "Print1.h"

#include "Print1Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrint1Doc

IMPLEMENT_DYNCREATE(CPrint1Doc, CDocument)

BEGIN_MESSAGE_MAP(CPrint1Doc, CDocument)
	//{{AFX_MSG_MAP(CPrint1Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrint1Doc construction/destruction

CPrint1Doc::CPrint1Doc()
{
	// TODO: add one-time construction code here

}

CPrint1Doc::~CPrint1Doc()
{
}

BOOL CPrint1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;
    m_StringArray.SetSize(9);
	m_StringArray[0]="               画菊     ";
    m_StringArray[1]="         诗余戏笔不知狂,        ";
	m_StringArray[2]="         岂是丹青费较量.    ";
	m_StringArray[3]="         聚叶泼成千点墨,      ";
	m_StringArray[4]="         攒花染出几痕霜. ";
	m_StringArray[5]="         淡浓神会风前影,";
	m_StringArray[6]="         跳脱秋生腕底香.       ";
	m_StringArray[7]="         莫认东篱闲采掇,";
	m_StringArray[8]="         粘屏聊以慰重阳. ";
	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CPrint1Doc serialization

void CPrint1Doc::Serialize(CArchive& ar)
{
	m_StringArray.Serialize(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CPrint1Doc diagnostics

#ifdef _DEBUG
void CPrint1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPrint1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPrint1Doc commands

void CPrint1Doc::DeleteContents() 
{
   m_StringArray.RemoveAll();
}
