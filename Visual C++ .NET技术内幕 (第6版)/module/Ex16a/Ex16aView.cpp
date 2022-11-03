// Ex16aView.cpp : implementation of the CEx16aView class
//

#include "stdafx.h"
#include "Ex16a.h"
#include "student.h"
#include "Ex16aDoc.h"
#include "Ex16aView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CEx16aView

IMPLEMENT_DYNCREATE(CEx16aView, CFormView)

BEGIN_MESSAGE_MAP(CEx16aView, CFormView)
	ON_COMMAND(ID_STUDENT_HOME, OnStudentHome)
	ON_COMMAND(ID_STUDENT_DELETE, OnStudentDelete)
	ON_COMMAND(ID_STUDENT_END, OnStudentEnd)	
	ON_COMMAND(ID_STUDENT_INSERT, OnStudentInsert)
	ON_COMMAND(ID_STUDENT_NEXT, OnStudentNext)
	ON_COMMAND(ID_STUDENT_PREVIOUS, OnStudentPrevious)	
	ON_UPDATE_COMMAND_UI(ID_STUDENT_HOME, OnUpdateStudentHome)
	ON_UPDATE_COMMAND_UI(ID_STUDENT_DELETE, OnUpdateStudentDelete)
	ON_UPDATE_COMMAND_UI(ID_STUDENT_END, OnUpdateStudentEnd)	
	ON_UPDATE_COMMAND_UI(ID_STUDENT_NEXT, OnUpdateStudentNext)
	ON_UPDATE_COMMAND_UI(ID_STUDENT_PREVIOUS, OnUpdateStudentPrevious)
	ON_BN_CLICKED(IDC_CLEAR, OnBnClickedClear)
END_MESSAGE_MAP()

// CEx16aView construction/destruction

CEx16aView::CEx16aView()
	: CFormView(CEx16aView::IDD)
	, m_nGrade(0)
	, m_strName(_T(""))
	, m_position(NULL)
{
	TRACE("Entering CEx16aView constructor\n");
}

CEx16aView::~CEx16aView()
{
}

void CEx16aView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_GRADE, m_nGrade);
	DDX_Text(pDX, IDC_NAME, m_strName);
}

BOOL CEx16aView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CEx16aView::OnInitialUpdate()
{
	TRACE("Entering CEx16aView::OnInitialUpdate\n");
    m_pList = GetDocument()->GetList();
	CFormView::OnInitialUpdate();
}


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

CEx16aDoc* CEx16aView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEx16aDoc)));
	return (CEx16aDoc*)m_pDocument;
}
#endif //_DEBUG


// CEx16aView message handlers
void CEx16aView::OnStudentHome()
{
	TRACE("Entering CEx16aView::OnStudentHome\n");
    // need to deal with list empty condition
    if (!m_pList->IsEmpty()) {
        m_position = m_pList->GetHeadPosition();
        GetEntry(m_position);
    }

}

void CEx16aView::OnUpdateStudentHome(CCmdUI *pCmdUI)
{
	// called during idle processing and when Student menu drops down
    POSITION pos;

    // enables button if list not empty and not at home already
    pos = m_pList->GetHeadPosition();
    pCmdUI->Enable((m_position != NULL) && (pos != m_position));

}

void CEx16aView::OnStudentDelete()
{
	// deletes current entry and positions to next one or head
    POSITION pos;
    TRACE("Entering CEx16aView::OnStudentDelete\n");
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

void CEx16aView::OnUpdateStudentDelete(CCmdUI *pCmdUI)
{
	// called during idle processing and when Student menu drops down
    pCmdUI->Enable(m_position != NULL);

}

void CEx16aView::OnStudentEnd()
{
	TRACE("Entering CEx16aView::OnStudentEnd\n");
    if (!m_pList->IsEmpty()) {
        m_position = m_pList->GetTailPosition();
        GetEntry(m_position);
    }

}

void CEx16aView::OnUpdateStudentEnd(CCmdUI *pCmdUI)
{
	// called during idle processing and when Student menu drops down
    POSITION pos;

    // enables button if list not empty and not at end already
    pos = m_pList->GetTailPosition();
    pCmdUI->Enable((m_position != NULL) && (pos != m_position));

}

void CEx16aView::OnStudentInsert()
{
	TRACE("Entering CEx16aView::OnStudentInsert\n");
    InsertEntry(m_position);
    GetDocument()->SetModifiedFlag();
    GetDocument()->UpdateAllViews(this);

}

void CEx16aView::OnStudentNext()
{
	POSITION pos;
    TRACE("Entering CEx16aView::OnStudentNext\n");
    if ((pos = m_position) != NULL) {
        m_pList->GetNext(pos);
        if (pos) {
            GetEntry(pos);
            m_position = pos;
        }
    }

}

void CEx16aView::OnUpdateStudentNext(CCmdUI *pCmdUI)
{
	OnUpdateStudentEnd(pCmdUI);
}

void CEx16aView::OnStudentPrevious()
{
	POSITION pos;
    TRACE("Entering CEx16aView::OnStudentPrevious\n");
    if ((pos = m_position) != NULL) {
        m_pList->GetPrev(pos);
        if (pos) {
            GetEntry(pos);
            m_position = pos;
        }
    }

}

void CEx16aView::OnUpdateStudentPrevious(CCmdUI *pCmdUI)
{
	OnUpdateStudentHome(pCmdUI);
}

void CEx16aView::OnUpdate(CView* /*pSender*/, 
	LPARAM /*lHint*/, CObject* /*pHint*/)
{
	// called by OnInitialUpdate and by UpdateAllViews
    TRACE("Entering CEx16aView::OnUpdate\n");
    m_position = m_pList->GetHeadPosition();
    GetEntry(m_position); // initial data for view

}

void CEx16aView::ClearEntry()
{
    m_strName = "";
    m_nGrade = 0;
    UpdateData(FALSE);
    ((CDialog*) this)->GotoDlgCtrl(GetDlgItem(IDC_NAME));
}

void CEx16aView::GetEntry(POSITION position)
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

void CEx16aView::InsertEntry(POSITION position)
{
    if (UpdateData(TRUE)) {
        // UpdateData returns FALSE if it detects a user error
        CStudent* pStudent = new CStudent;
        pStudent->m_strName = m_strName;
        pStudent->m_nGrade = m_nGrade;
        m_position = m_pList->InsertAfter(m_position, pStudent);
    }
}

void CEx16aView::OnBnClickedClear()
{
	TRACE("Entering CEx16aView::OnBnClickedClear\n");
    ClearEntry();

}
