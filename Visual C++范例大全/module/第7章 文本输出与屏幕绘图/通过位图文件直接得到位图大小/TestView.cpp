// TestView.cpp : CTestView ���ʵ��
//

#include "stdafx.h"
#include "Test.h"

#include "TestDoc.h"
#include "TestView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestView

IMPLEMENT_DYNCREATE(CTestView, CView)

BEGIN_MESSAGE_MAP(CTestView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CTestView ����/����

CTestView::CTestView()
{
	// TODO: �ڴ˴���ӹ������

}

CTestView::~CTestView()
{
}

BOOL CTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ������
	// ��ʽ

	return CView::PreCreateWindow(cs);
}

// CTestView ����

void CTestView::OnDraw(CDC* /*pDC*/)
{
	CTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CTestView ��ӡ

BOOL CTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��ӡǰ��Ӷ���ĳ�ʼ��
}

void CTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��ӡ������������
}


// CTestView ���

#ifdef _DEBUG
void CTestView::AssertValid() const
{
	CView::AssertValid();
}

void CTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTestDoc* CTestView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestDoc)));
	return (CTestDoc*)m_pDocument;
}
#endif //_DEBUG


// CTestView ��Ϣ�������

void CTestView::OnRButtonDown(UINT nFlags, CPoint point)
{
	CString   StrFilter="λͼ�ļ�(*.bmp)|*.bmp|�����ļ�(*.*)|*.*||";
	CFileDialog  Dlg(TRUE,NULL,NULL,NULL,StrFilter,this);	
	CString StrFileName;
	if(!Dlg.DoModal()==IDOK)
	{
		return ;
	}
	StrFileName=Dlg.GetPathName();
	CFile MyFile;
	if(!MyFile.Open(StrFileName,CFile::modeRead))
		return;
	BITMAPFILEHEADER bmfHeader;
	//��λͼ�ļ�ͷ��Ϣ
	if (MyFile.Read((LPSTR)&bmfHeader, sizeof(bmfHeader)) != sizeof(bmfHeader))
		return ;
	//�ж��Ƿ���BMP
	if (bmfHeader.bfType != ((WORD) ('M' << 8) | 'B'))
		return ; 
	//��λͼͷ��Ϣ
	BITMAPINFOHEADER bmiHeader; 
	if (MyFile.Read((LPSTR)&bmiHeader, sizeof(bmiHeader)) !=sizeof(bmiHeader))
		return ;
	//��ô�С��Ϣ������ʾ
	int bmWidth=bmiHeader.biWidth;
	int bmHeight=bmiHeader.biHeight;
	CString StrInfo;
	StrInfo.Format("%sλͼ�Ĵ�СΪ��%d X %d",StrFileName,bmiHeader.biWidth,bmiHeader.biHeight);
	MessageBox(StrInfo,"��Ϣ��ʾ",MB_OK);
	CView::OnRButtonDown(nFlags, point);
}
