// Singleton.cpp : �������̨Ӧ�ó������ڵ㡣
//

/********************************************************************
	CREATED:	2012/01/19
	FILENAME:	main.cpp
	AUTHOR:		By Robot
	
	PURPOSE:	����ģʽ���Գ���
*********************************************************************/

#include "stdafx.h"
#include "Singleton.h"
#include <iostream>


class ImagesetManager : public Singleton<ImagesetManager>
{
public:
	ImagesetManager() {}
	~ImagesetManager() {}
};

//WX_IMPLEMENT_SINGLEON(ImagesetManager);


int _tmain(int argc, _TCHAR* argv[])
{
	
	ImagesetManager *pInstance1 = ImagesetManager::GetSinglePtr();
	ImagesetManager *pInstance2 = ImagesetManager::GetSinglePtr();
	if (pInstance1 == pInstance2)
	{
		std::cout << "����ʵ��������ͬ��" <<std::endl;
	}
	delete pInstance1;

	system("pause");
	return 0;
}



