// MFCWizardPropertyPageView.cpp : implementation of the CMFCWizardPropertyPageView class
//

#include "stdafx.h"
#include "MFCWizardPropertyPage.h"

#include "MFCWizardPropertyPageDoc.h"
#include "MFCWizardPropertyPageView.h"

#include "WizardSheet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMFCWizardPropertyPageView

IMPLEMENT_DYNCREATE(CMFCWizardPropertyPageView, CView)

BEGIN_MESSAGE_MAP(CMFCWizardPropertyPageView, CView)
	//{{AFX_MSG_MAP(CMFCWizardPropertyPageView)
	ON_COMMAND(IDC_WIZARD, OnWizard)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMFCWizardPropertyPageView construction/destruction

CMFCWizardPropertyPageView::CMFCWizardPropertyPageView()
{
	// TODO: add construction code here
	m_nCareer=-1;
	m_strCity="";
	for(int i=0;i<4;++i){
		m_bFlag[i]=FALSE;
	}
	m_strSalary="";
}

CMFCWizardPropertyPageView::~CMFCWizardPropertyPageView()
{
}

BOOL CMFCWizardPropertyPageView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CMFCWizardPropertyPageView drawing

void CMFCWizardPropertyPageView::OnDraw(CDC* pDC)
{
	CMFCWizardPropertyPageDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here
	CString strInfo="ְҵ:";
	switch(m_nCareer){
		case 0:
			strInfo+="����Ա";
			break;
		case 1:
			strInfo+="�˶�Ա";
			break;
		case 2:
			strInfo+="����Ա";
			break;
	}
	pDC->TextOut(0,0,strInfo);
	strInfo="���ڳ���:";
	strInfo+=m_strCity;
	//��ȡ��ǰʹ�õ�������Ϣ
	TEXTMETRIC tm;
	pDC->GetTextMetrics(&tm);
	pDC->TextOut(0,tm.tmHeight,strInfo);
	strInfo="����:";
	if(m_bFlag[0]){
		strInfo+="���  ";
	}
	if(m_bFlag[1]){
		strInfo+="��Ӿ  ";
	}
	if(m_bFlag[2]){
		strInfo+="����  ";
	}
	if(m_bFlag[3]){
		strInfo+="��ɽ  ";
	}
	pDC->TextOut(0,2*tm.tmHeight,strInfo);
	strInfo="нˮ��Χ";
	strInfo+=m_strSalary;
	pDC->TextOut(0,3*tm.tmHeight,strInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CMFCWizardPropertyPageView printing

BOOL CMFCWizardPropertyPageView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMFCWizardPropertyPageView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMFCWizardPropertyPageView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CMFCWizardPropertyPageView diagnostics

#ifdef _DEBUG
void CMFCWizardPropertyPageView::AssertValid() const
{
	CView::AssertValid();
}

void CMFCWizardPropertyPageView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCWizardPropertyPageDoc* CMFCWizardPropertyPageView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCWizardPropertyPageDoc)));
	return (CMFCWizardPropertyPageDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMFCWizardPropertyPageView message handlers

void CMFCWizardPropertyPageView::OnWizard() 
{
	// TODO: Add your command handler code here
	CWizardSheet cws("��ʽ");
	//���ó���ʽ
	cws.SetWizardMode();
	if(cws.DoModal()!=ID_WIZFINISH){
		return;
	}
	//��ֵ���ݸ���ͼ����ʾ����
	m_nCareer=cws.m_pageCityCareer.m_nCareer;
	m_strCity=cws.m_pageCityCareer.m_strCity;
	m_bFlag[0]=cws.m_pageHobby.m_bProgramming;
	m_bFlag[1]=cws.m_pageHobby.m_bSwim;
	m_bFlag[2]=cws.m_pageHobby.m_bTravel;
	m_bFlag[3]=cws.m_pageHobby.m_bMountain;
	m_strSalary=cws.m_pageSalary.m_strSalary;
	//��ͼ�ػ�
	Invalidate();
}
