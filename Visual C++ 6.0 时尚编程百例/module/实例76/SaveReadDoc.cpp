// SaveReadDoc.cpp : implementation of the CSaveReadDoc class
//

#include "stdafx.h"
#include "SaveRead.h"

#include "SaveReadDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSaveReadDoc

IMPLEMENT_DYNCREATE(CSaveReadDoc, CDocument)

BEGIN_MESSAGE_MAP(CSaveReadDoc, CDocument)
	//{{AFX_MSG_MAP(CSaveReadDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSaveReadDoc construction/destruction

CSaveReadDoc::CSaveReadDoc()
{
	strcmp(name,"");
	for(int i=0;i<8;i++){
	m_nSubject[i].score=0.0;
	m_nSubject[i].subject=0;
	}
	total=0;
	// TODO: add one-time construction code here

}

CSaveReadDoc::~CSaveReadDoc()
{
}

BOOL CSaveReadDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSaveReadDoc serialization

void CSaveReadDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar<<name;      //д������
		ar<<total;      //д���ܳɼ�
		for(int i=0;i<9;i++)
		{
			ar<<m_nSubject[i].subject;  //д����Ӧ��Ŀ�����
   			ar<<m_nSubject[i].score;    //д����Ӧ��Ŀ�ĳɼ�
		}
	}
	else
	{
		
		ar>>name;      //��������
		ar>>total ;     //�����ܳɼ�
		for(int i=0;i<9;i++)
		{
			ar>>m_nSubject[i].subject;  //������Ӧ��Ŀ�����
   			ar>>m_nSubject[i].score;    //������Ӧ��Ŀ�ĳɼ�
		}
	}
}

/////////////////////////////////////////////////////////////////////////////
// CSaveReadDoc diagnostics

#ifdef _DEBUG
void CSaveReadDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSaveReadDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSaveReadDoc commands
