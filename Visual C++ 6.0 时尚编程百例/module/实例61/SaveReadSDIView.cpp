// SaveReadSDIView.cpp : implementation of the CSaveReadSDIView class
//

#include "stdafx.h"
#include "SaveReadSDI.h"

#include "SaveReadSDIDoc.h"
#include "SaveReadSDIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSaveReadSDIView

IMPLEMENT_DYNCREATE(CSaveReadSDIView, CFormView)

BEGIN_MESSAGE_MAP(CSaveReadSDIView, CFormView)
	//{{AFX_MSG_MAP(CSaveReadSDIView)
	ON_EN_CHANGE(IDC_NAME, OnChangeName)
	ON_EN_CHANGE(IDC_SCORE, OnChangeScore)
	ON_CBN_SELCHANGE(IDC_SUBJECT, OnSelchangeSubject)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSaveReadSDIView construction/destruction

CSaveReadSDIView::CSaveReadSDIView()
	: CFormView(CSaveReadSDIView::IDD)
{
	//{{AFX_DATA_INIT(CSaveReadSDIView)
	m_name = _T("");
	m_score = 0.0f;
	m_total = 0.0f;
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CSaveReadSDIView::~CSaveReadSDIView()
{
}

void CSaveReadSDIView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSaveReadSDIView)
	DDX_Control(pDX, IDC_SUBJECT, m_subject);
	DDX_Text(pDX, IDC_NAME, m_name);
	DDX_Text(pDX, IDC_SCORE, m_score);
	DDV_MinMaxFloat(pDX, m_score, 0.f, 100.f);
	DDX_Text(pDX, IDC_TOTAL, m_total);
	DDV_MinMaxFloat(pDX, m_total, 0.f, 900.f);
	//}}AFX_DATA_MAP
}

BOOL CSaveReadSDIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CSaveReadSDIView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
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
	CSaveReadSDIDoc *pDoc=GetDocument();
	m_name=pDoc->name;
	m_subject.SetCurSel(pDoc->m_nSubject[0].subject);
	m_score=pDoc->m_nSubject[0].score;
	m_total=pDoc->total;
	UpdateData(FALSE);

}

/////////////////////////////////////////////////////////////////////////////
// CSaveReadSDIView printing

BOOL CSaveReadSDIView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSaveReadSDIView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSaveReadSDIView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CSaveReadSDIView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}

/////////////////////////////////////////////////////////////////////////////
// CSaveReadSDIView diagnostics

#ifdef _DEBUG
void CSaveReadSDIView::AssertValid() const
{
	CFormView::AssertValid();
}

void CSaveReadSDIView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CSaveReadSDIDoc* CSaveReadSDIView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSaveReadSDIDoc)));
	return (CSaveReadSDIDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSaveReadSDIView message handlers

void CSaveReadSDIView::OnChangeName() 
{
	CSaveReadSDIDoc *pDoc=GetDocument();  //获取文档类指针
	UpdateData();                    //获取最新的输入
	if(strcmp(pDoc->name,m_name))    //判断姓名是否改变
	{
		pDoc->name=m_name;   //如果姓名已改变,记录新的姓名
 		pDoc->SetModifiedFlag();     //设置文档修改标志
	}
}

void CSaveReadSDIView::OnChangeScore() 
{
	CSaveReadSDIDoc *pDoc=GetDocument();  //获取文档类指针
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

void CSaveReadSDIView::OnSelchangeSubject() 
{
	CSaveReadSDIDoc *pDoc=GetDocument();  //获取文档类指针
	UpdateData();                    //获取最新的输入
    int current=m_subject.GetCurSel();//获取当前选中项的序号
	if(pDoc->m_nSubject[current].score!=m_score)
	{      //判断是否当前科目已改变如果改变显示相应科目的成绩
		m_score=pDoc->m_nSubject[current].score;
		UpdateData(FALSE); //重新显示
	}	
}
