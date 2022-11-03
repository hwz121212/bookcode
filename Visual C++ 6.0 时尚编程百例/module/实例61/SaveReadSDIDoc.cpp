// SaveReadSDIDoc.cpp : implementation of the CSaveReadSDIDoc class
//

#include "stdafx.h"
#include "SaveReadSDI.h"

#include "SaveReadSDIDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSaveReadSDIDoc

IMPLEMENT_DYNCREATE(CSaveReadSDIDoc, CDocument)

BEGIN_MESSAGE_MAP(CSaveReadSDIDoc, CDocument)
	//{{AFX_MSG_MAP(CSaveReadSDIDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSaveReadSDIDoc construction/destruction

CSaveReadSDIDoc::CSaveReadSDIDoc()
{
	strcmp(name,"");
	for(int i=0;i<8;i++){
	m_nSubject[i].score=0.0;
	m_nSubject[i].subject=0;
	}
	total=0;
	// TODO: add one-time construction code here

}

CSaveReadSDIDoc::~CSaveReadSDIDoc()
{
}

BOOL CSaveReadSDIDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSaveReadSDIDoc serialization

void CSaveReadSDIDoc::Serialize(CArchive& ar)
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
// CSaveReadSDIDoc diagnostics

#ifdef _DEBUG
void CSaveReadSDIDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSaveReadSDIDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSaveReadSDIDoc commands
