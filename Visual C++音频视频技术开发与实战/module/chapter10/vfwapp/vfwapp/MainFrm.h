// MainFrm.h : CMainFrame ��Ľӿ�
//

#pragma once
/////////////////////////////////////////////////////////////////////////////////////////
#include "vfw.h"

typedef struct{
	int headsize;						//bitmap headsize
	char buffer[1300000];				//bitmap head and data
}DIBINFO, *PDIBINFO;

LRESULT CALLBACK EXPORT ErrorCallbackProc(HWND hWnd, int nErrID, LPSTR lpErrorText);
LRESULT FAR PASCAL StatusCallbackProc(HWND hWnd, int nID, LPSTR lpStatusText);
LRESULT FAR PASCAL VideoCallbackProc(HWND hWnd, LPVIDEOHDR lpVHdr);
/////////////////////////////////////////////////////////////////////////////////////////

class CMainFrame : public CFrameWnd
{
	
protected: // �������л�����
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// ����
public:
	
	DIBINFO m_dibinfo;
	//int test;
	CAPDRIVERCAPS m_caps;
	PAVIFILE       m_pFile;            //AVI�ļ�
	AVISTREAMINFO  strhdr;             //AVI����Ϣ
	PAVISTREAM     ps;                 //AVI��ָ��
	DWORD          m_Frame;            //��¼֡��

// ����
public:

	void InitAVIWriteOpt();
// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnVfwInitvfw();
public:
	afx_msg void OnVfwVideoformat();
public:
	//afx_msg void OnVfwCompressor();
public:
	//afx_msg void OnVfwCapturevideo();
public:
	afx_msg void OnClose();
public:
	afx_msg void OnVfwPreviewvideo();
public:
	afx_msg void OnVfwCodec();
};


