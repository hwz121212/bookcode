// vfwappDoc.cpp : CvfwappDoc ���ʵ��
//

#include "stdafx.h"
#include "vfwapp.h"

#include "vfwappDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CvfwappDoc

IMPLEMENT_DYNCREATE(CvfwappDoc, CDocument)

BEGIN_MESSAGE_MAP(CvfwappDoc, CDocument)
END_MESSAGE_MAP()


// CvfwappDoc ����/����

CvfwappDoc::CvfwappDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CvfwappDoc::~CvfwappDoc()
{
}

BOOL CvfwappDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CvfwappDoc ���л�

void CvfwappDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// CvfwappDoc ���

#ifdef _DEBUG
void CvfwappDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CvfwappDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CvfwappDoc ����
