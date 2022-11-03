
/********************************************************************
	CREATED:	2012/01/17
	FILENAME:	tUtil.h
	AUTHOR:		By Robot
	
	PURPOSE:	¹¤¾ßº¯Êý
*********************************************************************/

#pragma once

#include "BasicType.h"

INT	ConvertStringToVector(LPCTSTR strStrintgSource, std::vector< STRING >& vRet, 
						  LPCTSTR szKey=_T("\\/"), BOOL bOneOfKey = TRUE, BOOL bIgnoreEmpty = TRUE);
