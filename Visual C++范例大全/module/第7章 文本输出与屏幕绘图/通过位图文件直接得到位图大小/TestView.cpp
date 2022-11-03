// TestView.cpp : CTestView 类的实现
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
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CTestView 构造/销毁

CTestView::CTestView()
{
	// TODO: 在此处添加构造代码

}

CTestView::~CTestView()
{
}

BOOL CTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改 CREATESTRUCT cs 来修改窗口类或
	// 样式

	return CView::PreCreateWindow(cs);
}

// CTestView 绘制

void CTestView::OnDraw(CDC* /*pDC*/)
{
	CTestDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: 在此处为本机数据添加绘制代码
}


// CTestView 打印

BOOL CTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CTestView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 打印前添加额外的初始化
}

void CTestView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 打印后添加清除过程
}


// CTestView 诊断

#ifdef _DEBUG
void CTestView::AssertValid() const
{
	CView::AssertValid();
}

void CTestView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTestDoc* CTestView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestDoc)));
	return (CTestDoc*)m_pDocument;
}
#endif //_DEBUG


// CTestView 消息处理程序

void CTestView::OnRButtonDown(UINT nFlags, CPoint point)
{
	CString   StrFilter="位图文件(*.bmp)|*.bmp|所有文件(*.*)|*.*||";
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
	//读位图文件头信息
	if (MyFile.Read((LPSTR)&bmfHeader, sizeof(bmfHeader)) != sizeof(bmfHeader))
		return ;
	//判断是否是BMP
	if (bmfHeader.bfType != ((WORD) ('M' << 8) | 'B'))
		return ; 
	//读位图头信息
	BITMAPINFOHEADER bmiHeader; 
	if (MyFile.Read((LPSTR)&bmiHeader, sizeof(bmiHeader)) !=sizeof(bmiHeader))
		return ;
	//获得大小信息，并显示
	int bmWidth=bmiHeader.biWidth;
	int bmHeight=bmiHeader.biHeight;
	CString StrInfo;
	StrInfo.Format("%s位图的大小为：%d X %d",StrFileName,bmiHeader.biWidth,bmiHeader.biHeight);
	MessageBox(StrInfo,"信息提示",MB_OK);
	CView::OnRButtonDown(nFlags, point);
}
