// Ex15aView.cpp : implementation of the CEx15aView class
//

#include "stdafx.h"
#include "Ex15a.h"
#include "student.h"

#include "Ex15aDoc.h"
#include "Ex15aView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEx15aView

IMPLEMENT_DYNCREATE(CEx15aView, CFormView)

BEGIN_MESSAGE_MAP(CEx15aView, CFormView)
	ON_BN_CLICKED(IDC_ENTER, OnBnClickedEnter)
	ON_COMMAND(ID_EDIT_CLEARALL, OnEditClearall)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CLEARALL, OnUpdateEditClearall)
END_MESSAGE_MAP()

// CEx15aView construction/destruction

CEx15aView::CEx15aView()
	: CFormView(CEx15aView::IDD)
	, m_nGrade(0)
	, m_strName(_T(""))
{
	// TODO: add construction code here

}

CEx15aView::~CEx15aView()
{
}

void CEx15aView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_GRADE, m_nGrade);
	DDV_MinMaxInt(pDX, m_nGrade, 0, 100);
	DDX_Text(pDX, IDC_NAME, m_strName);
}

BOOL CEx15aView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CEx15aView::OnInitialUpdate()
{
	//called on startup
	CFormView::OnInitialUpdate();
	UpdateControlsFromDoc();
}


// CEx15aView diagnostics

#ifdef _DEBUG
void CEx15aView::AssertValid() const
{
	CFormView::AssertValid();
}

void CEx15aView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CEx15aDoc* CEx15aView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx15aDoc)));
	return (CEx15aDoc*)m_pDocument;
}
#endif //_DEBUG


// CEx15aView message handlers

void CEx15aView::OnBnClickedEnter()
{
	CEx15aDoc* pDoc = GetDocument();
    UpdateData(TRUE);
    pDoc->m_student.m_nGrade = m_nGrade;
    pDoc->m_student.m_strName = m_strName;

}

void CEx15aView::OnEditClearall()
{
	GetDocument()->m_student = CStudent(); // "blank" student object
    UpdateControlsFromDoc();

}

void CEx15aView::OnUpdateEditClearall(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetDocument()->m_student != CStudent()); // blank?
}

void CEx15aView::UpdateControlsFromDoc(void)
{
	// called from OnInitialUpdate and OnEditClearAll
	CEx15aDoc* pDoc = GetDocument();
	m_nGrade = pDoc->m_student.m_nGrade;
    m_strName = pDoc->m_student.m_strName;
    UpdateData(FALSE); // calls DDX

}
