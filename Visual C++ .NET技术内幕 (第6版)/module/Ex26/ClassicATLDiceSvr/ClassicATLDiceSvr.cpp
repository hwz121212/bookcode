// ClassicATLDiceSvr.cpp : Implementation of DLL Exports.

#include "stdafx.h"
#include "resource.h"
#include "ClassicATLDiceSvr.h"

class CClassicATLDiceSvrModule : public CAtlDllModuleT< CClassicATLDiceSvrModule >
{
public :
	DECLARE_LIBID(LIBID_ClassicATLDiceSvrLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_CLASSICATLDICESVR, "{2EFB69BA-53A0-4F9C-9300-BA83683147EE}")
};

CClassicATLDiceSvrModule _AtlModule;

// DLL Entry Point
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
    return _AtlModule.DllMain(dwReason, lpReserved); 
}


// Used to determine whether the DLL can be unloaded by OLE
STDAPI DllCanUnloadNow(void)
{
    return _AtlModule.DllCanUnloadNow();
}


// Returns a class factory to create an object of the requested type
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
    return _AtlModule.DllGetClassObject(rclsid, riid, ppv);
}


// DllRegisterServer - Adds entries to the system registry
STDAPI DllRegisterServer(void)
{
    // registers object, typelib and all interfaces in typelib
    HRESULT hr = _AtlModule.DllRegisterServer();
	return hr;
}


// DllUnregisterServer - Removes entries from the system registry
STDAPI DllUnregisterServer(void)
{
	HRESULT hr = _AtlModule.DllUnregisterServer();
	return hr;
}
