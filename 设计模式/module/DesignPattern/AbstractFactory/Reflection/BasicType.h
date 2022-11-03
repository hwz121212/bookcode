
/********************************************************************
	CREATED:	2012/01/17
	FILENAME:	BasicType.h
	AUTHOR:		By Robot
	
	PURPOSE:	类型定义
*********************************************************************/

#ifndef __BASIC_TYPE_H__
#define __BASIC_TYPE_H__

#include <windows.h>
#include <shlwapi.h>
#include <Mmsystem.h>

#include <tchar.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <assert.h>

#include <string>
#include <vector>
#include <list>
#include <map>
#include <hash_map>
#include <algorithm>


#ifdef UNICODE
typedef	std::wstring				STRING;
#else
typedef	std::string					STRING;
#endif

#endif
