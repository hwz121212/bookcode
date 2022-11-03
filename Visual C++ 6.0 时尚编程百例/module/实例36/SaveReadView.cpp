// SaveReadView.cpp : implementation of the CSaveReadView class
//

#include "stdafx.h"
#include "SaveRead.h"

#include "SaveReadDoc.h"
#include "SaveReadView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSaveReadView

IMPLEMENT_DYNCREATE(CSaveReadView, CFormView)

BEGIN_MESSAGE_MAP(CSaveReadView, CFormView)
	//{{AFX_MSG_MAP(CSaveReadView)
	ON_EN_CHANGE(IDC_NAME, OnChangeName)
	ON_EN_CHANGE(IDC_SCORE, OnChangeScore)
	ON_CBN_SELCHANGE(IDC_SUBJECT, OnSelchangeSubject)
	ON_COMMAND(ID_TEXT, OnText)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSaveReadView construction/destruction

CSaveReadView::CSaveReadView()
	: CFormView(CSaveReadView::IDD)
{
	//{{AFX_DATA_INIT(CSaveReadView)
	m_score = 0.0f;
	m_name = _T("");
	m_total = 0.0f;
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CSaveReadView::~CSaveReadView()
{
}

void CSaveReadView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSaveReadView)
	DDX_Control(pDX, IDC_SUBJECT, m_subject);
	DDX_Text(pDX, IDC_SCORE, m_score);
	DDV_MinMaxFloat(pDX, m_score, 0.f, 100.f);
	DDX_Text(pDX, IDC_NAME, m_name);
	DDX_Text(pDX, IDC_TOTAL, m_total);
	DDV_MinMaxFloat(pDX, m_total, 0.f, 900.f);
	//}}AFX_DATA_MAP
}

BOOL CSaveReadView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CSaveReadView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	ResizeParentToFit();
	//设置控件的字体大小
	CFont font1;
	font1.CreateFont(30,0,0,0,FW_NORMAL,
		            FALSE,FALSE,FALSE,ANSI_CHARSET,OUT_DEFAULT_PRECIS,
					CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH|FF_MODERN,
					"CourierNew");
	GetDlgItem(IDC_STATIC1)->SetFont(&font1);
	GetDlgItem(IDC_STATIC2)->SetFont(&font1);
	GetDlgItem(IDC_STATIC3)->SetFont(&font1);
	GetDlgItem(IDC_STATIC4)->SetFont(&font1);
	GetDlgItem(IDC_STATIC5)->SetFont(&font1);
	m_subject.SetFont(&font1);
	
	//初始化与控件相对应的成员变量并显示
	CSaveReadDoc *pDoc=GetDocument();
	m_name=pDoc->name;
	m_subject.SetCurSel(pDoc->m_nSubject[0].subject);
	m_score=pDoc->m_nSubject[0].score;
	m_total=pDoc->total;
	UpdateData(FALSE);

}

/////////////////////////////////////////////////////////////////////////////
// CSaveReadView printing

BOOL CSaveReadView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSaveReadView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSaveReadView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CSaveReadView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}

/////////////////////////////////////////////////////////////////////////////
// CSaveReadView diagnostics

#ifdef _DEBUG
void CSaveReadView::AssertValid() const
{
	CFormView::AssertValid();
}

void CSaveReadView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CSaveReadDoc* CSaveReadView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSaveReadDoc)));
	return (CSaveReadDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSaveReadView message handlers

void CSaveReadView::OnChangeName() 
{
	CSaveReadDoc *pDoc=GetDocument();  //获取文档类指针
	UpdateData();                    //获取最新的输入
	if(strcmp(pDoc->name,m_name))    //判断姓名是否改变
	{
		pDoc->name=m_name;   //如果姓名已改变,记录新的姓名
 		pDoc->SetModifiedFlag();     //设置文档修改标志
	}
}

void CSaveReadView::OnChangeScore() 
{
	CSaveReadDoc *pDoc=GetDocument();  //获取文档类指针
	UpdateData();                    //获取最新的输入
   	int current=m_subject.GetCurSel();  //获取当前选中项的序号
	 //判断成绩是否改变
	if(pDoc->m_nSubject[current].score!=m_score)
	{
			//从新计算总成绩
		pDoc->total=pDoc->total+m_score-pDoc->m_nSubject[current].score;
	    m_total=pDoc->total;
		pDoc->m_nSubject[current].score=m_score;//记录新成绩
		pDoc->SetModifiedFlag();     //设置文档修改标志
        UpdateData(FALSE);           //重新显示
	}
}

void CSaveReadView::OnSelchangeSubject() 
{
	CSaveReadDoc *pDoc=GetDocument();  //获取文档类指针
	UpdateData();                    //获取最新的输入
    int current=m_subject.GetCurSel();//获取当前选中项的序号
	if(pDoc->m_nSubject[current].score!=m_score)
	{      //判断是否当前科目已改变如果改变显示相应科目的成绩
		m_score=pDoc->m_nSubject[current].score;
		UpdateData(FALSE); //重新显示
	}	
}

void CSaveReadView::OnText() 
{
	CString filename;
	CString str;
	CSaveReadDoc *pDoc=GetDocument();  //获取文档类指针
	UpdateData();     //获取最新的输入
	if(m_name.IsEmpty())      //输入数据中没有输入姓名,则将文件名设为"无名"
		filename="无名.txt";
	else                       //将文件名设为输入的姓名并将其扩展名设为txt
		filename=m_name+".txt";
	CStdioFile file;          //CStdioFile类是CFile类的派生类,它是以流方式操作文本
	if(file.Open(filename,CFile::modeCreate|CFile::modeWrite|CFile::typeText)==0)
	{
		str="创建文件"+filename+"失败";
		AfxMessageBox(str);    //创建文件失败报告并返回
		return;
	}
	str.Format("                   %s的成绩表\n\n",m_name); //写入文件主题
	file.WriteString(str);
	str.Format("                      总成绩:   %.1f分\n\n",m_total);	//写入总成绩
	file.WriteString(str);
	str.Format("             科目:      成绩:  单位(分)\n");    //写入成绩表头
	file.WriteString(str);
    for(int i=0;i<8;i++)
	{
		CString string;
		m_subject.GetLBText(i,string);       //得到科目名称
        str.Format("%18s      %.1f\n",string,pDoc->m_nSubject[i].score);
		file.WriteString(str);               //写入科目名和相应的成绩
	}
     file.SetLength(file.GetPosition());  //设置文件长度
	 file.Close();                     //关闭文件
	 str="notepad "+filename;
	 WinExec(str,SW_SHOW);             //利用记事本打开生成的文本文件
}
