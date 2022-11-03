// AnimateView.cpp : implementation of the CAnimateView class
//

#include "stdafx.h"
#include "Animate.h"

#include "AnimateDoc.h"
#include "AnimateView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAnimateView

IMPLEMENT_DYNCREATE(CAnimateView, CView)

BEGIN_MESSAGE_MAP(CAnimateView, CView)
	//{{AFX_MSG_MAP(CAnimateView)
	ON_COMMAND(ID_OPEN1, OnOpen1)
	ON_COMMAND(ID_ANIMATE, OnAnimate)
	ON_COMMAND(ID_STOP, OnStop)
	ON_UPDATE_COMMAND_UI(ID_OPEN1, OnUpdateOpen1)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAnimateView construction/destruction

CAnimateView::CAnimateView()
{
	m_Animate=NULL; //��ʼ��
	// TODO: add construction code here

}

CAnimateView::~CAnimateView()
{
}

BOOL CAnimateView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CAnimateView drawing

void CAnimateView::OnDraw(CDC* pDC)
{
	CAnimateDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
}

/////////////////////////////////////////////////////////////////////////////
// CAnimateView printing

BOOL CAnimateView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CAnimateView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CAnimateView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CAnimateView diagnostics

#ifdef _DEBUG
void CAnimateView::AssertValid() const
{
	CView::AssertValid();
}

void CAnimateView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CAnimateDoc* CAnimateView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CAnimateDoc)));
	return (CAnimateDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CAnimateView message handlers

void CAnimateView::OnOpen1() 
{
	    	//��һ�����ļ�ͨ�öԻ���
    	CFileDialog  dlg(TRUE,"avi",NULL,
                      OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT,
		             "��Ƶ�ļ�(*.avi)|*.avi|�����ļ�(*.*)|*.*||",this);
		dlg.m_ofn.lpstrTitle="����Ƶ�ļ�";
	  if(dlg.DoModal()==IDCANCEL)
	    	return ;
    	//��ȡѡ�����Ƶ�ļ����ļ���
	    CString filename=dlg.GetPathName();
	
	   CRect rect;
       GetClientRect(rect);
       //������ָ�����ռ�.
	   m_Animate=new CAnimateCtrl();
  	   //����һ����CAnimateCtrl����
       m_Animate->Create(WS_CHILD |WS_VISIBLE,rect,this,0);
	   //���ö�������ͼ���ڵ�λ��
	   OffsetRect(rect,100,100);
	   m_Animate->MoveWindow(rect);
	   //����Ƶ�ļ�
       m_Animate->Open(filename);
	
}

void CAnimateView::OnAnimate() 
{
	//������Ƶ�ļ�
	    m_Animate->Play(0,-1,-1);
	
}

void CAnimateView::OnStop() 
{
	//ֹͣ������Ƶ�ļ�
	m_Animate->Stop();
	//�ͷŷ���ռ�
	delete m_Animate;
	m_Animate=NULL;
}

void CAnimateView::OnUpdateOpen1(CCmdUI* pCmdUI) 
{
	      //����Ѿ�����һ����Ƶ�ļ���˵�����
	     pCmdUI->Enable(m_Animate==NULL);	
}
