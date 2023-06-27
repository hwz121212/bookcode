// StuView.cpp : implementation of the CStudentView class
//

#include "stdafx.h"
#include "ex17a.h"

#include "StuDoc.h"
#include "StuView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CStudentView

IMPLEMENT_DYNCREATE(CStudentView, CFormView)

BEGIN_MESSAGE_MAP(CStudentView, CFormView)
	//{{AFX_MSG_MAP(CStudentView)
	ON_BN_CLICKED(IDC_CLEAR, OnClear)
	ON_COMMAND(ID_STUDENT_HOME, OnStudentHome)
	ON_COMMAND(ID_STUDENT_END, OnStudentEnd)
	ON_COMMAND(ID_STUDENT_PREV, OnStudentPrev)
	ON_COMMAND(ID_STUDENT_NEXT, OnStudentNext)
	ON_COMMAND(ID_STUDENT_INS, OnStudentIns)
	ON_COMMAND(ID_STUDENT_DEL, OnStudentDel)
	ON_UPDATE_COMMAND_UI(ID_STUDENT_HOME, OnUpdateStudentHome)
	ON_UPDATE_COMMAND_UI(ID_STUDENT_END, OnUpdateStudentEnd)
	ON_UPDATE_COMMAND_UI(ID_STUDENT_PREV, OnUpdateStudentHome)
	ON_UPDATE_COMMAND_UI(ID_STUDENT_NEXT, OnUpdateStudentEnd)
	ON_UPDATE_COMMAND_UI(ID_STUDENT_DEL, OnUpdateStudentDel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStudentView construction/destruction

CStudentView::CStudentView()
	: CFormView(CStudentView::IDD)
{
    TRACE("Entering CStudentView constructor\n");
	//{{AFX_DATA_INIT(CStudentView)
	m_nGrade = 0;
	m_strName = _T("");
	//}}AFX_DATA_INIT
    m_position = NULL;
}

CStudentView::~CStudentView()
{
}

void CStudentView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStudentView)
	DDX_Text(pDX, IDC_GRADE, m_nGrade);
	DDV_MinMaxInt(pDX, m_nGrade, 0, 100);
	DDX_Text(pDX, IDC_NAME, m_strName);
	DDV_MaxChars(pDX, m_strName, 20);
	//}}AFX_DATA_MAP
}

BOOL CStudentView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CStudentView::OnInitialUpdate()
{
    TRACE("Entering CStudentView::OnInitialUpdate\n");
    m_pList = GetDocument()->GetList();
	CFormView::OnInitialUpdate();

}

/////////////////////////////////////////////////////////////////////////////
// CStudentView diagnostics

#ifdef _DEBUG
void CStudentView::AssertValid() const
{
	CFormView::AssertValid();
}

void CStudentView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CStudentDoc* CStudentView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CStudentDoc)));
	return (CStudentDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CStudentView message handlers

void CStudentView::OnClear() 
{
    TRACE("Entering CStudentView::OnClear\n");
    ClearEntry();
	
}

void CStudentView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint) 
{
    // called by OnInitialUpdate and by UpdateAllViews
    TRACE("Entering CStudentView::OnUpdate\n");
    m_position = m_pList->GetHeadPosition();
    GetEntry(m_position); // initial data for view
	
	
}

void CStudentView::OnStudentHome() 
{
    TRACE("Entering CStudentView::OnStudentHome\n");
    // need to deal with list empty condition
    if (!m_pList->IsEmpty()) {
        m_position = m_pList->GetHeadPosition();
        GetEntry(m_position);
    }
	
}

void CStudentView::OnStudentEnd() 
{
    TRACE("Entering CStudentView::OnStudentEnd\n");
    if (!m_pList->IsEmpty()) {
        m_position = m_pList->GetTailPosition();
        GetEntry(m_position);
    }
	
}

void CStudentView::OnStudentPrev() 
{
    POSITION pos;
    TRACE("Entering CStudentView::OnStudentPrev\n");
    if ((pos = m_position) != NULL) {
        m_pList->GetPrev(pos);
        if (pos) {
            GetEntry(pos);
            m_position = pos;
        }
    }
	
}

void CStudentView::OnStudentNext() 
{
    POSITION pos;
    TRACE("Entering CStudentView::OnStudentNext\n");
    if ((pos = m_position) != NULL) {
        m_pList->GetNext(pos);
        if (pos) {
            GetEntry(pos);
            m_position = pos;
        }
    }
	
}

void CStudentView::OnStudentIns() 
{
    TRACE("Entering CStudentView::OnStudentIns\n");
    InsertEntry(m_position);
    GetDocument()->SetModifiedFlag();
    GetDocument()->UpdateAllViews(this);
	
}

void CStudentView::OnStudentDel() 
{
    // deletes current entry and positions to next one or head
    POSITION pos;
    TRACE("Entering CStudentView::OnStudentDel\n");
    if ((pos = m_position) != NULL) {
        m_pList->GetNext(pos);
        if (pos == NULL) {
            pos = m_pList->GetHeadPosition();
            TRACE("GetHeadPos = %ld\n", pos);
            if (pos == m_position) {
                pos = NULL;
            }
        }
        GetEntry(pos);
        CStudent* ps = m_pList->GetAt(m_position);
        m_pList->RemoveAt(m_position);
        delete ps;
        m_position = pos;
        GetDocument()->SetModifiedFlag();
        GetDocument()->UpdateAllViews(this);
    }
	
}

void CStudentView::OnUpdateStudentHome(CCmdUI* pCmdUI) 
{
    // called during idle processing and when Student menu drops down
    POSITION pos;

    // enables button if list not empty and not at home already
    pos = m_pList->GetHeadPosition();
    pCmdUI->Enable((m_position != NULL) && (pos != m_position));
	
}

void CStudentView::OnUpdateStudentEnd(CCmdUI* pCmdUI) 
{
    // called during idle processing and when Student menu drops down
    POSITION pos;

    // enables button if list not empty and not at end already
    pos = m_pList->GetTailPosition();
    pCmdUI->Enable((m_position != NULL) && (pos != m_position));
	
}

void CStudentView::OnUpdateStudentDel(CCmdUI* pCmdUI) 
{
    // called during idle processing and when Student menu drops down
    pCmdUI->Enable(m_position != NULL);
	
}

void CStudentView::GetEntry(POSITION position)
{
    if (position) {
        CStudent* pStudent = m_pList->GetAt(position);
        m_strName = pStudent->m_strName;
        m_nGrade = pStudent->m_nGrade;
    }
    else {
        ClearEntry();
    }
    UpdateData(FALSE);
}

void CStudentView::InsertEntry(POSITION position)
{
    if (UpdateData(TRUE)) {
        // UpdateData returns FALSE if it detects a user error
        CStudent* pStudent = new CStudent;
        pStudent->m_strName = m_strName;
        pStudent->m_nGrade = m_nGrade;
        m_position = m_pList->InsertAfter(m_position, pStudent);
    }
}

void CStudentView::ClearEntry()
{
    m_strName = "";
    m_nGrade = 0;
    UpdateData(FALSE);
    ((CDialog*) this)->GotoDlgCtrl(GetDlgItem(IDC_NAME));
}
