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
	m_StringArray[0]="               ����     ";
    m_StringArray[1]="         ʫ��Ϸ�ʲ�֪��,        ";
	m_StringArray[2]="         ���ǵ���ѽ���.    ";
	m_StringArray[3]="         ��Ҷ�ó�ǧ��ī,      ";
	m_StringArray[4]="         �ܻ�Ⱦ������˪. ";
	m_StringArray[5]="         ��Ũ����ǰӰ,";
	m_StringArray[6]="         �������������.       ";
	m_StringArray[7]="         Ī�϶����вɶ�,";
	m_StringArray[8]="         ճ������ο����. ";
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
