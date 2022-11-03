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
	//���ÿؼ��������С
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
	
	//��ʼ����ؼ����Ӧ�ĳ�Ա��������ʾ
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
	CSaveReadDoc *pDoc=GetDocument();  //��ȡ�ĵ���ָ��
	UpdateData();                    //��ȡ���µ�����
	if(strcmp(pDoc->name,m_name))    //�ж������Ƿ�ı�
	{
		pDoc->name=m_name;   //��������Ѹı�,��¼�µ�����
 		pDoc->SetModifiedFlag();     //�����ĵ��޸ı�־
	}
}

void CSaveReadView::OnChangeScore() 
{
	CSaveReadDoc *pDoc=GetDocument();  //��ȡ�ĵ���ָ��
	UpdateData();                    //��ȡ���µ�����
   	int current=m_subject.GetCurSel();  //��ȡ��ǰѡ��������
	 //�жϳɼ��Ƿ�ı�
	if(pDoc->m_nSubject[current].score!=m_score)
	{
			//���¼����ܳɼ�
		pDoc->total=pDoc->total+m_score-pDoc->m_nSubject[current].score;
	    m_total=pDoc->total;
		pDoc->m_nSubject[current].score=m_score;//��¼�³ɼ�
		pDoc->SetModifiedFlag();     //�����ĵ��޸ı�־
        UpdateData(FALSE);           //������ʾ
	}
}

void CSaveReadView::OnSelchangeSubject() 
{
	CSaveReadDoc *pDoc=GetDocument();  //��ȡ�ĵ���ָ��
	UpdateData();                    //��ȡ���µ�����
    int current=m_subject.GetCurSel();//��ȡ��ǰѡ��������
	if(pDoc->m_nSubject[current].score!=m_score)
	{      //�ж��Ƿ�ǰ��Ŀ�Ѹı�����ı���ʾ��Ӧ��Ŀ�ĳɼ�
		m_score=pDoc->m_nSubject[current].score;
		UpdateData(FALSE); //������ʾ
	}	
}

void CSaveReadView::OnText() 
{
	CString filename;
	CString str;
	CSaveReadDoc *pDoc=GetDocument();  //��ȡ�ĵ���ָ��
	UpdateData();     //��ȡ���µ�����
	if(m_name.IsEmpty())      //����������û����������,���ļ�����Ϊ"����"
		filename="����.txt";
	else                       //���ļ�����Ϊ�����������������չ����Ϊtxt
		filename=m_name+".txt";
	CStdioFile file;          //CStdioFile����CFile���������,����������ʽ�����ı�
	if(file.Open(filename,CFile::modeCreate|CFile::modeWrite|CFile::typeText)==0)
	{
		str="�����ļ�"+filename+"ʧ��";
		AfxMessageBox(str);    //�����ļ�ʧ�ܱ��沢����
		return;
	}
	str.Format("                   %s�ĳɼ���\n\n",m_name); //д���ļ�����
	file.WriteString(str);
	str.Format("                      �ܳɼ�:   %.1f��\n\n",m_total);	//д���ܳɼ�
	file.WriteString(str);
	str.Format("             ��Ŀ:      �ɼ�:  ��λ(��)\n");    //д��ɼ���ͷ
	file.WriteString(str);
    for(int i=0;i<8;i++)
	{
		CString string;
		m_subject.GetLBText(i,string);       //�õ���Ŀ����
        str.Format("%18s      %.1f\n",string,pDoc->m_nSubject[i].score);
		file.WriteString(str);               //д���Ŀ������Ӧ�ĳɼ�
	}
     file.SetLength(file.GetPosition());  //�����ļ�����
	 file.Close();                     //�ر��ļ�
	 str="notepad "+filename;
	 WinExec(str,SW_SHOW);             //���ü��±������ɵ��ı��ļ�
}
