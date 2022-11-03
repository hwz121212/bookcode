#include "afxwin.h"
class CMyApp : public CWinApp
{
public:
	virtual BOOL InitInstance();
};
class CMainFrame : public CFrameWnd
{};
CMyApp myApp;

BOOL CMyApp::InitInstance()
{
m_pMainWnd= new CMainFrame;
((CMainFrame*)m_pMainWnd)->Create(NULL,"The MFC Application");
m_pMainWnd->ShowWindow(m_nCmdShow);

								 
    return TRUE;
}
