// HardDeskInfo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ������


// CHardDeskInfoApp:
// �йش����ʵ�֣������ HardDeskInfo.cpp
//

class CHardDeskInfoApp : public CWinApp
{
public:
	CHardDeskInfoApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CHardDeskInfoApp theApp;
