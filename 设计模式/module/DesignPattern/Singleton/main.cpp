// Singleton.cpp : 定义控制台应用程序的入口点。
//

/********************************************************************
	CREATED:	2012/01/19
	FILENAME:	main.cpp
	AUTHOR:		By Robot
	
	PURPOSE:	单例模式测试程序
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
		std::cout << "两个实例对象相同！" <<std::endl;
	}
	delete pInstance1;

	system("pause");
	return 0;
}



