// MediaPlayer.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMediaPlayerApp:
// �йش����ʵ�֣������ MediaPlayer.cpp
//

class CMediaPlayerApp : public CWinApp
{
public:
	CMediaPlayerApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMediaPlayerApp theApp;