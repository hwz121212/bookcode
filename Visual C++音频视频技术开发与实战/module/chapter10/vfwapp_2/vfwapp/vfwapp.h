// vfwapp.h : vfwapp Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CvfwappApp:
// �йش����ʵ�֣������ vfwapp.cpp
//

class CvfwappApp : public CWinApp
{
public:
	CvfwappApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CvfwappApp theApp;