// CaptureVideo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCaptureVideoApp:
// �йش����ʵ�֣������ CaptureVideo.cpp
//

class CCaptureVideoApp : public CWinApp
{
public:
	CCaptureVideoApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CCaptureVideoApp theApp;