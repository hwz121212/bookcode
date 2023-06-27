// ex16aView.cpp : implementation of the CEx16aView class
//

#include "stdafx.h"
#include "ex16a.h"

#include "ex16aDoc.h"
#include "ex16aView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CEx16aView

IMPLEMENT_DYNCREATE(CEx16aView, CFormView)

BEGIN_MESSAGE_MAP(CEx16aView, CFormView)
	//{{AFX_MSG_MAP(CEx16aView)
	ON_BN_CLICKED(IDC_ENTER, OnEnter)
	ON_COMMAND(ID_EDIT_CLEAR_ALL, OnEditClearAll)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CLEAR_ALL, OnUpdateEditClearAll)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEx16aView construction/destruction

CEx16aView::CEx16aView()
	: CFormView(CEx16aView::IDD)
{
	//{{AFX_DATA_INIT(CEx16aView)
	m_nGrade = 0;
	m_strName = _T("");
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CEx16aView::~CEx16aView()
{
}

void CEx16aView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEx16aView)
	DDX_Text(pDX, IDC_GRADE, m_nGrade);
	DDV_MinMaxInt(pDX, m_nGrade, 0, 100);
	DDX_Text(pDX, IDC_NAME, m_strName);
	//}}AFX_DATA_MAP
}

BOOL CEx16aView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CEx16aView::OnInitialUpdate()
{   // called on startup
    UpdateControlsFromDoc();

}

/////////////////////////////////////////////////////////////////////////////
// CEx16aView diagnostics

#ifdef _DEBUG
void CEx16aView::AssertValid() const
{
	CFormView::AssertValid();
}

void CEx16aView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CEx16aDoc* CEx16aView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx16aDoc)));
	return (CEx16aDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CEx16aView message handlers

void CEx16aView::OnEnter() 
{
    CEx16aDoc* pDoc = GetDocument();
    UpdateData(TRUE);
    pDoc->m_student.m_nGrade = m_nGrade;
    pDoc->m_student.m_strName = m_strName;
	
}

void CEx16aView::OnEditClearAll() 
{
    GetDocument()->m_student = CStudent(); // "blank" student object
    UpdateControlsFromDoc();
	
}

void CEx16aView::OnUpdateEditClearAll(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable(GetDocument()->m_student != CStudent()); // blank?	
}

void CEx16aView::UpdateControlsFromDoc()
{   // called from OnInitialUpdate and OnEditClearAll
    CEx16aDoc* pDoc = GetDocument();
    m_nGrade = pDoc->m_student.m_nGrade;
    m_strName = pDoc->m_student.m_strName;
    UpdateData(FALSE); // calls DDX

}
