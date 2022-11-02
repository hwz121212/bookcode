/*
  This project was created and edited using the MFC SelfBanner AppWizard.

  Comment: 管道编程－本地CMD.

  Project: ntLocalCmd.
  Author : dhyao
  Date   : 星期一, 二月 02, 2009
*/
/////////////////////////////////////////////////////////////////////
// CmdView.cpp : implementation file
//

#include "StdAfx.h"
#include "CmdView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCmdView

IMPLEMENT_DYNCREATE(CCmdView, CEditView)

CCmdView::CCmdView()
{
	m_dwProcessId = DWORD(-1);
	m_pReadThread = NULL;

	m_hChildStdinRd = NULL;
	m_hChildStdinWr = NULL;
	m_hChildStdoutRd = NULL;
	m_hChildStdoutWr = NULL;

	//	Initialize LOGFONT structure
	memset(&m_lf, 0, sizeof(m_lf));
	m_lf.lfWeight = FW_NORMAL;
	m_lf.lfCharSet = GB2312_CHARSET;	//ANSI_CHARSET;
	m_lf.lfOutPrecision = OUT_DEFAULT_PRECIS;
	m_lf.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	m_lf.lfQuality = DEFAULT_QUALITY;
	m_lf.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
	lstrcpy(m_lf.lfFaceName, _T("FixedSys"));

	m_nHistoryCounter = 0;
}

CCmdView::~CCmdView()
{
}

BEGIN_MESSAGE_MAP(CCmdView, CEditView)
	//{{AFX_MSG_MAP(CCmdView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_WM_CONTEXTMENU()
	//}}AFX_MSG_MAP
	// Standard-Druckbefehle
	ON_COMMAND(ID_FILE_PRINT, CCmdView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CCmdView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CCmdView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCmdView drawing

void CCmdView::OnDraw(CDC* pDC)
{
	UNREFERENCED_PARAMETER(pDC);

	// TODO: add draw code here
}

/////////////////////////////////////////////////////////////////////////////
// CCmdView diagnostics

#ifdef _DEBUG
void CCmdView::AssertValid() const
{
	CEditView::AssertValid();
}

void CCmdView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CCmdView message handlers

int CCmdView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CEditView::OnCreate(lpCreateStruct) == -1)
		return -1;

//	GetEditCtrl().SetReadOnly(TRUE);
	DWORD dwStyle = GetWindowLong(GetEditCtrl().GetSafeHwnd(), GWL_STYLE);
	if (dwStyle)
	{
		dwStyle |= DS_LOCALEDIT;
		SetWindowLong(GetEditCtrl().GetSafeHwnd(), GWL_STYLE, dwStyle);
	}

	if (m_defFont.CreateFontIndirect(&m_lf))
		GetEditCtrl().SetFont(&m_defFont);
	if (!CreateShellRedirect())
		return -1;

	return 0;
}

#define BUFSIZE 4096

BOOL CCmdView::CreateShellRedirect()
{
	HANDLE hChildStdoutRdTmp, hChildStdinWrTmp;
	SECURITY_ATTRIBUTES saAttr;
	BOOL bSuccess;

	// Set the bInheritHandle flag so pipe handles are inherited.
	saAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
	saAttr.bInheritHandle = TRUE;
	saAttr.lpSecurityDescriptor = NULL;

	// The steps for redirecting child process's STDOUT: 
	//	 1. Save current STDOUT, to be restored later. 
	//	 2. Create anonymous pipe to be STDOUT for child process. 
	//	 3. Set STDOUT of the parent process to be write handle to 
	//		the pipe, so it is inherited by the child process. 
	//	 4. Create a noninheritable duplicate of the read handle and
	//		close the inheritable read handle.

	// Save the handle to the current STDOUT.
	HANDLE hSaveStdout = GetStdHandle(STD_OUTPUT_HANDLE);

	// Create a pipe for the child process's STDOUT.
	if (!CreatePipe(&hChildStdoutRdTmp, &m_hChildStdoutWr, &saAttr, 0))
	{
		TRACE0(_T("Stdout pipe creation failed\n"));
		return FALSE;
	}

	// Set a write handle to the pipe to be STDOUT.
	if (!SetStdHandle(STD_OUTPUT_HANDLE, m_hChildStdoutWr))
	{
		TRACE0(_T("Redirecting STDOUT failed\n"));
		return FALSE;
	}

	// Create noninheritable read handle and close the inheritable read handle. 
	bSuccess = DuplicateHandle(GetCurrentProcess(), hChildStdoutRdTmp, 
		GetCurrentProcess(), &m_hChildStdoutRd, 
		0, FALSE, 
		DUPLICATE_SAME_ACCESS);
	if (!bSuccess)
	{
		TRACE0(_T("DuplicateHandle failed\n"));
		return FALSE;
	}
	VERIFY(CloseHandle(hChildStdoutRdTmp));

	// The steps for redirecting child process's STDIN: 
	//	 1.  Save current STDIN, to be restored later. 
	//	 2.  Create anonymous pipe to be STDIN for child process. 
	//	 3.  Set STDIN of the parent to be the read handle to the 
	//		 pipe, so it is inherited by the child process. 
	//	 4.  Create a noninheritable duplicate of the write handle, 
	//		 and close the inheritable write handle.

	// Save the handle to the current STDIN. 
	HANDLE hSaveStdin = GetStdHandle(STD_INPUT_HANDLE);

	// Create a pipe for the child process's STDIN.
	if (!CreatePipe(&m_hChildStdinRd, &hChildStdinWrTmp, &saAttr, 0))
	{
		TRACE0(_T("Stdin pipe creation failed\n"));
		return FALSE;
	}
	// Set a read handle to the pipe to be STDIN.
	if (!SetStdHandle(STD_INPUT_HANDLE, m_hChildStdinRd))
	{
		TRACE0(_T("Redirecting Stdin failed\n"));
		return FALSE;
	}
	// Duplicate the write handle to the pipe so it is not inherited.
	bSuccess = DuplicateHandle(GetCurrentProcess(), hChildStdinWrTmp, 
		GetCurrentProcess(), &m_hChildStdinWr, 
		0, FALSE, 				  // not inherited
		DUPLICATE_SAME_ACCESS);
	if (!bSuccess)
	{
		TRACE0(_T("DuplicateHandle failed\n"));
		return FALSE;
	}
	VERIFY(CloseHandle(hChildStdinWrTmp));

	// Now create the child process. 
	if (!CreateChildProcess())
	{
		TRACE0(_T("CreateChildProcess failed\n"));
		return FALSE;
	}
	// After process creation, restore the saved STDIN and STDOUT.
	if (!SetStdHandle(STD_INPUT_HANDLE, hSaveStdin))
	{
		TRACE0(_T("Re-redirecting Stdin failed\n"));
		return FALSE;
	}
	if (!SetStdHandle(STD_OUTPUT_HANDLE, hSaveStdout))
	{
		TRACE0(_T("Re-redirecting Stdout failed\n"));
		return FALSE;
	}
	m_pReadThread = 
		AfxBeginThread(ReadPipeThreadProc, this, THREAD_PRIORITY_BELOW_NORMAL);
	if (!m_pReadThread)
	{
		TRACE0(_T("Cannot start read-redirect thread!\n"));
		return FALSE;
	}
	return TRUE;
}

BOOL CCmdView::CreateChildProcess()
{
	PROCESS_INFORMATION piProcInfo;
	STARTUPINFO siStartInfo;

	// Set up members of STARTUPINFO structure.
	ZeroMemory(&siStartInfo, sizeof(STARTUPINFO));
	siStartInfo.cb = sizeof(STARTUPINFO);

	siStartInfo.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
	siStartInfo.wShowWindow = SW_HIDE;
	siStartInfo.hStdInput = m_hChildStdinRd;
	siStartInfo.hStdOutput = m_hChildStdoutWr;
	siStartInfo.hStdError = m_hChildStdoutWr;

	TCHAR shellCmd[_MAX_PATH];
	if (!GetEnvironmentVariable(_T("ComSpec"), shellCmd, _MAX_PATH))
		return FALSE;
#ifdef _UNICODE
	_tcscat(shellCmd, _T(" /U"));
#else
	_tcscat(shellCmd, _T(" /A"));
#endif 
	// Create the child process.
	BOOL bRet = CreateProcess(NULL, 
			shellCmd, 	   // applicatin name
			NULL, 		  // process security attributes 
			NULL, 		  // primary thread security attributes 
			TRUE, 		  // handles are inherited 
			CREATE_NEW_CONSOLE, // creation flags 
			NULL, 		  // use parent's environment 
			NULL, 		  // use parent's current directory 
			&siStartInfo,  // STARTUPINFO pointer 
			&piProcInfo);  // receives PROCESS_INFORMATION 
	if (bRet)
		m_dwProcessId = piProcInfo.dwProcessId;
	return bRet;
}

void CCmdView::WriteToPipe(LPCTSTR line)
{
	DWORD dwWritten;

	WriteFile(m_hChildStdinWr, line, _tcslen(line)*sizeof(TCHAR), 
			&dwWritten, NULL);
}

UINT CCmdView::ReadPipeThreadProc(LPVOID pParam)
{
	DWORD dwRead;
	TCHAR chBuf[BUFSIZE];
	CCmdView* pView = (CCmdView*)pParam;

	TRACE0(_T("ReadPipe Thread begin run\n"));
	for (;;)
	{ 
		if (!ReadFile(pView->m_hChildStdoutRd, chBuf, 
			BUFSIZE, &dwRead, NULL) || dwRead == 0) 
		{
			if (::GetLastError() == ERROR_BROKEN_PIPE)
				break;
			else
				ASSERT(FALSE);
		}
		chBuf[dwRead/sizeof(TCHAR)] = _T('\0');
		pView->AddTexts(chBuf);
		pView->m_nLength = pView->GetEditCtrl().SendMessage(WM_GETTEXTLENGTH);
	}
	VERIFY(CloseHandle(pView->m_hChildStdinRd));
	VERIFY(CloseHandle(pView->m_hChildStdoutWr));
	VERIFY(CloseHandle(pView->m_hChildStdinWr));
	VERIFY(CloseHandle(pView->m_hChildStdoutRd));
	pView->m_pReadThread = NULL;
	pView->m_dwProcessId = DWORD(-1);
	pView->PostMessage(WM_CLOSE);
	return 1;
}

// original version does not work under Win9x,
// new version see below
/*void CCmdView::OnDestroy() 
{
	if (m_dwProcessId != DWORD(-1))
	{
		HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, m_dwProcessId);
		if (hProcess)
		{
			TerminateProcess(hProcess, 0);
			VERIFY(CloseHandle(hProcess));
		}
	}
	if (m_pReadThread)
	{
		TerminateThread(m_pReadThread->m_hThread, 0);
		delete m_pReadThread;
	}
	CCmdView::OnDestroy();
}*/

void CCmdView::OnDestroy() 
{
	if (m_dwProcessId != DWORD(-1))
	{
		HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, m_dwProcessId);
		if (hProcess)
		{
			TerminateProcess(hProcess, 0);

			WriteToPipe(_T("exit\r\n"));
			WaitForSingleObject(hProcess, INFINITE);

			VERIFY(CloseHandle(hProcess));
		}
	}
	if (m_pReadThread)
	{
		TerminateThread(m_pReadThread->m_hThread, 0);
		delete m_pReadThread;
		m_pReadThread = NULL;
	}
	CEditView::OnDestroy();
}

// original version,
// new version see below
/*void CCmdView::AddTexts(LPCTSTR string)
{
	MoveToEnd();
	GetEditCtrl().ReplaceSel(string);
}*/

void CCmdView::AddTexts(LPCTSTR string, BOOL bReplace)
{
	// replace '\n' by '\r''\n'
	int k, counter = 0, strLen = _tcslen(string);
	for (k = 0; k <= strLen; k++)
	{
		if (string[k] == _T('\n') && (k == 0 || string[k-1] != _T('\r')))
			counter++;
	}
	LPTSTR str = (LPTSTR)GlobalAlloc(0, (strLen+counter+1)*sizeof(TCHAR));
	for (k = strLen; k >= 0; k--)
	{
		str[k+counter] = string[k];
		if (string[k] == _T('\n') && (k == 0 || string[k-1] != _T('\r')))
		{
			counter--;
			str[k+counter] = _T('\r');
		}
	}

	if (bReplace)
		MoveToPrompt();
	else
		MoveToEnd();
	GetEditCtrl().ReplaceSel(str);
	GlobalFree(str);
}

void CCmdView::AddTexts(TCHAR ch)
{
	TCHAR string[2];
	string[0] = ch;
	string[1] = _T('\0');
	AddTexts((LPCTSTR)string);
}

void CCmdView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	int nPos = GetCurrentPosition();
	if (nChar == 8 && nPos  <= m_nLength)
		return;
	if (nPos  < m_nLength)
		MoveToEnd();
	CEditView::OnChar(nChar, nRepCnt, nFlags);
	if (nChar == 13)
	{
		CString input, history;
		GetUserInput(input);

		if (input.Right(2) == _T("\r\n"))
			history = input.Left(input.GetLength()-2);
		else
			history = input;
		history.TrimLeft();
		history.TrimRight();

		if (!history.IsEmpty() && (m_History.GetSize() == 0 || m_History.GetAt(m_History.GetSize()-1) != history))
			m_History.Add(history);
		m_nHistoryCounter = m_History.GetSize();

		WriteToPipe(input);

		if (history == _T("exit"))
			GetParentFrame()->SendMessage(WM_CLOSE);
	}
}

void CCmdView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	if (nChar == VK_LEFT || nChar == VK_RIGHT)
		return;
	if (nChar == VK_UP)
	{
		int nHistorySize = m_History.GetSize();
		if (nHistorySize == 0)
			return;
		if (--m_nHistoryCounter < 0)
			m_nHistoryCounter = 0;
		AddTexts(m_History.GetAt(m_nHistoryCounter), TRUE);
		return;
	}
	if (nChar == VK_DOWN)
	{
		int nHistorySize = m_History.GetSize();
		if (nHistorySize == 0)
			return;
		if (++m_nHistoryCounter > nHistorySize)
			m_nHistoryCounter = nHistorySize;
		if (m_nHistoryCounter == nHistorySize)
			AddTexts(_T(""), TRUE);
		else
			AddTexts(m_History.GetAt(m_nHistoryCounter), TRUE);
		return;
	}
	if (nChar == VK_DELETE)
	{
		if (GetCurrentPosition() < m_nLength)
			return;
	}
	CEditView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CCmdView::MoveToEnd()
{
	int nLen = GetEditCtrl().SendMessage(WM_GETTEXTLENGTH);
	GetEditCtrl().SetSel(nLen, nLen);
}

void CCmdView::MoveToPrompt()
{
	int nLen = GetEditCtrl().SendMessage(WM_GETTEXTLENGTH);
	GetEditCtrl().SetSel(m_nLength, nLen);
}

int CCmdView::GetCurrentPosition()
{
	GetEditCtrl().SetSel(-1, -1);
	int nstart, nstop;
	GetEditCtrl().GetSel(nstart, nstop);
	return nstart;
}

// original version does not work under Win9x,
// new version see below
/*void CCmdView::GetUserInput(CString &input)
{
	int where = GetCurrentPosition();
	HLOCAL hBuffer = GetEditCtrl().GetHandle();
	if (hBuffer)
	{
		LPCTSTR szBuffer = (LPCTSTR)LocalLock(hBuffer);
		if (szBuffer)
		{
			input = CString(szBuffer+m_nLength, (where-m_nLength));
			LocalUnlock(hBuffer);
		}
	}
}*/

void CCmdView::GetUserInput(CString &input)
{
	int where = GetCurrentPosition();

	LPCTSTR szBuffer = LockBuffer();
	if (szBuffer)
	{
		input = CString(szBuffer+m_nLength, (where-m_nLength));
		UnlockBuffer();
	}
}

int CCmdView::GetSelLength()
{
	int nstart, nstop;
	GetEditCtrl().GetSel(nstart, nstop);
	return (nstart-nstop);
}

BOOL CCmdView::PreCreateWindow(CREATESTRUCT& cs) 
{
	return CEditView::PreCreateWindow(cs);
}

void CCmdView::OnEditPaste() 
{
	MoveToEnd();
	CEditView::OnEditPaste();
}

//#define MES_UNDO        _T("&Undo")
//#define MES_CUT         _T("Cu&t")
#define MES_COPY        _T("&Copy")
#define MES_PASTE       _T("&Paste")
//#define MES_DELETE      _T("&Delete")
#define MES_SELECTALL   _T("Select &All")
#define ME_SELECTALL    WM_USER + 0x7000



void CCmdView::OnContextMenu(CWnd* pWnd, CPoint point) 
{
	// TODO: Add your message handler code here
	SetFocus();
    CMenu menu;
    menu.CreatePopupMenu();
    BOOL bReadOnly = GetStyle() & ES_READONLY;
	DWORD flags;
 //   DWORD flags = GetEditCtrl().CanUndo() && !bReadOnly ? 0 : MF_GRAYED;
//    menu.InsertMenu(0, MF_BYPOSITION | flags, EM_UNDO,
 //       MES_UNDO);

//    menu.InsertMenu(1, MF_BYPOSITION | MF_SEPARATOR);

    DWORD sel = GetEditCtrl().GetSel();
    flags = LOWORD(sel) == HIWORD(sel) ? MF_GRAYED : 0;
    menu.InsertMenu(2, MF_BYPOSITION | flags, WM_COPY,
        MES_COPY);

//    flags = (flags == MF_GRAYED || bReadOnly) ? MF_GRAYED : 0;
//    menu.InsertMenu(2, MF_BYPOSITION | flags, WM_CUT,
//        MES_CUT);
//    menu.InsertMenu(4, MF_BYPOSITION | flags, WM_CLEAR,
//        MES_DELETE);

    flags = IsClipboardFormatAvailable(CF_TEXT) &&
        !bReadOnly ? 0 : MF_GRAYED;
    menu.InsertMenu(4, MF_BYPOSITION | flags, WM_PASTE,
        MES_PASTE);

    menu.InsertMenu(6, MF_BYPOSITION | MF_SEPARATOR);

    int len = GetWindowTextLength();
    flags = (!len || (LOWORD(sel) == 0 && HIWORD(sel) ==
        len)) ? MF_GRAYED : 0;
    menu.InsertMenu(7, MF_BYPOSITION | flags, ME_SELECTALL,
        MES_SELECTALL);

    menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON |
        TPM_RIGHTBUTTON, point.x, point.y, this);


}

BOOL CCmdView::OnCommand(WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	switch (LOWORD(wParam))
    {
//    case EM_UNDO:
//    case WM_CUT:
    case WM_COPY:
//    case WM_CLEAR:
    case WM_PASTE:
        return SendMessage(LOWORD(wParam));
    case ME_SELECTALL:
        return SendMessage (EM_SETSEL, 0, -1);
    default:
        return CEditView::OnCommand(wParam, lParam);
    }
}
