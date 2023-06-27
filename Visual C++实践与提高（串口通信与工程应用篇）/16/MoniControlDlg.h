// MoniControlDlg.h : header file
//

#if !defined(AFX_MONICONTROLDLG_H__276F792F_0FF1_4014_96C1_8D6A1025FB8B__INCLUDED_)
#define AFX_MONICONTROLDLG_H__276F792F_0FF1_4014_96C1_8D6A1025FB8B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "mscomm.h"
/////////////////////////////////////////////////////////////////////////////
// CMoniControlDlg dialog

class CMoniControlDlg : public CDialog
{
// Construction
public:
	CMoniControlDlg(CWnd* pParent = NULL);	// standard constructor
	//CRect	myRect;
	CMSComm	myComm;                     //MSComm控件对象
	CByteArray sendArray;               //发送数据数组
	HICON	hIconU_N,hIconU_O,hIconU_P;
	HICON	hIconD_N,hIconD_O,hIconD_P;
	HICON	hIconL_N,hIconL_O,hIconL_P;
	HICON	hIconR_N,hIconR_O,hIconR_P;
	HICON	hIconLU_N,hIconLU_O,hIconLU_P;
	HICON	hIconLD_N,hIconLD_O,hIconLD_P;
	HICON	hIconRU_N,hIconRU_O,hIconRU_P;
	HICON	hIconRD_N,hIconRD_O,hIconRD_P;
	HICON	hIconB_N,hIconB_O,hIconB_P;
	HICON	hIconS_N,hIconS_O,hIconS_P;
	HICON	hIconF_N,hIconF_O,hIconF_P;
	HICON	hIconN_N,hIconN_O,hIconN_P;
	HICON	hIconLG_N,hIconLG_O,hIconLG_P;
	HICON	hIconSH_N,hIconSH_O,hIconSH_P;
	HICON	hIconO_N,hIconO_O,hIconO_P;
	HICON	hIconC_N,hIconC_O,hIconC_P;
	CRect	m_CRect_U;
	CRect	m_CRect_D;
	CRect	m_CRect_L;
	CRect	m_CRect_R;
	CRect	m_CRect_UM;
	CRect	m_CRect_DM;
	CRect	m_CRect_LM;
	CRect	m_CRect_RM;
	CRect	m_CRect_LU;
	CRect	m_CRect_LD;
	CRect	m_CRect_RU;
	CRect	m_CRect_RD;

	CRect	m_CRect_B;
	CRect	m_CRect_BM;
	CRect	m_CRect_S;
	CRect	m_CRect_SM;
	CRect	m_CRect_F;
	CRect	m_CRect_FM;
	CRect	m_CRect_N;
	CRect	m_CRect_NM;
	CRect	m_CRect_LG;
	CRect	m_CRect_LGM;
	CRect	m_CRect_SH;
	CRect	m_CRect_SHM;

	CRect	m_CRect_OB;
	CRect	m_CRect_CB;
	CRect	m_CRect_OL;
	CRect	m_CRect_CL;

	bool	bMoved;                      //标志，主对话框移动过

	CRect	GetRect(CStatic *pStatic);  //获取静态按钮的位置数据
	void	SendCommand(int iType);
//	void	DisStatus(CString strDis);
// Dialog Data
	//{{AFX_DATA(CMoniControlDlg)
	enum { IDD = IDD_MONICONTROL_DIALOG };
	CStatic	m_UpMicro;
	CStatic	m_Up;
	CStatic	m_SmallMicro;
	CStatic	m_Small;
	CStatic	m_ShortMicro;
	CStatic	m_Short;
	CStatic	m_RightUp;
	CStatic	m_RightMicro;
	CStatic	m_RightDown;
	CStatic	m_Right;
	CStatic	m_OpenLight;
	CButton	m_OpenCom;
	CStatic	m_OpenBrush;
	CStatic	m_NearMicro;
	CStatic	m_Near;
	CStatic	m_LongMicro;
	CStatic	m_Long;
	CStatic	m_LeftUp;
	CStatic	m_LeftMicro;
	CStatic	m_LeftDown;
	CStatic	m_Left;
	CStatic	m_FarMicro;
	CStatic	m_Far;
	CStatic	m_DownMicro;
	CStatic	m_Down;
	CStatic	m_CloseLight;
	CButton	m_CloseCom;
	CStatic	m_CloseBrush;
	CStatic	m_BigMicro;
	CStatic	m_Big;
	CStatic	m_ActStatus;
	int		m_Address;
	int		m_BaudRate;
	int		m_Com;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMoniControlDlg)
	public:
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMoniControlDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnOpencom();
	afx_msg void OnClosecom();
	afx_msg void OnCloseupComboAddress();
	afx_msg void OnMove(int x, int y);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnClose();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MONICONTROLDLG_H__276F792F_0FF1_4014_96C1_8D6A1025FB8B__INCLUDED_)
