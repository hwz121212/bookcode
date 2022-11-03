
#include "stdafx.h"
#include "BasicType.h"
#include "tUtil.h"

INT	ConvertStringToVector(LPCTSTR strStrintgSource, std::vector< STRING >& vRet, LPCTSTR szKey, BOOL bOneOfKey, BOOL bIgnoreEmpty)
{
	vRet.clear();

	//------------------------------------------------------------
	//合法性
	if(!strStrintgSource || strStrintgSource[0] == '\0') return 0;

	STRING strSrc = strStrintgSource;

	//------------------------------------------------------------
	//查找第一个分割点
	STRING::size_type nLeft = 0;
	STRING::size_type nRight;
	if(bOneOfKey)
	{
		nRight = strSrc.find_first_of(szKey);
	}
	else
	{
		nRight = strSrc.find(szKey);
	}

	if(nRight == std::string::npos)
	{
		nRight = strSrc.length();
	}
	while(TRUE)
	{
		STRING strItem = strSrc.substr(nLeft, nRight-nLeft);
		if(strItem.length() > 0 || !bIgnoreEmpty)
		{
			vRet.push_back(strItem);
		}

		if(nRight == strSrc.length())
		{
			break;
		}

		nLeft = nRight + (bOneOfKey ? 1 : _tcslen(szKey));

		if(bOneOfKey)
		{
			STRING strTemp = strSrc.substr(nLeft);
			nRight = strTemp.find_first_of(szKey);
			if(nRight != STRING::npos) nRight += nLeft;
		}
		else
		{
			nRight = strSrc.find(szKey, nLeft);
		}

		if(nRight == std::string::npos)
		{
			nRight = strSrc.length();
		}
	}

	return (INT)vRet.size();
}
