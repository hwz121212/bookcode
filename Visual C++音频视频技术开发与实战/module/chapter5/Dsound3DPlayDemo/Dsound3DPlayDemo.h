// Dsound3DPlayDemo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������


// CDsound3DPlayDemoApp:
// �йش����ʵ�֣������ Dsound3DPlayDemo.cpp
//

class CDsound3DPlayDemoApp : public CWinApp
{
public:
	CDsound3DPlayDemoApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CDsound3DPlayDemoApp theApp;
