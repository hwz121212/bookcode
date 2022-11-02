/*
  This project was created and edited using the MFC SelfBanner AppWizard.

  Comment: 管道编程－本地CMD.

  Project: ntLocalCmd.
  Author : dhyao
  Date   : 星期一, 二月 02, 2009
*/
/////////////////////////////////////////////////////////////////////

// ntLocalCmdDoc.cpp : implementation of the CNtLocalCmdDoc class
//

#include "stdafx.h"
#include "ntLocalCmd.h"
#include "CmdView.h"
#include "ntLocalCmdDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CNtLocalCmdDoc

IMPLEMENT_DYNCREATE(CNtLocalCmdDoc, CDocument)

BEGIN_MESSAGE_MAP(CNtLocalCmdDoc, CDocument)
	//{{AFX_MSG_MAP(CNtLocalCmdDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CNtLocalCmdDoc construction/destruction

CNtLocalCmdDoc::CNtLocalCmdDoc()
{
	// TODO: add one-time construction code here

}

CNtLocalCmdDoc::~CNtLocalCmdDoc()
{
}

BOOL CNtLocalCmdDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	((CCmdView*)m_viewList.GetHead())->SetWindowText(NULL);

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CNtLocalCmdDoc serialization

void CNtLocalCmdDoc::Serialize(CArchive& ar)
{
	// CCmdView contains an edit control which handles all serialization
	((CCmdView*)m_viewList.GetHead())->SerializeRaw(ar);
}

/////////////////////////////////////////////////////////////////////////////
// CNtLocalCmdDoc diagnostics

#ifdef _DEBUG
void CNtLocalCmdDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CNtLocalCmdDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CNtLocalCmdDoc commands
