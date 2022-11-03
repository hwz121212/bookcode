// ClassicATLSpaceship.h : Declaration of the CClassicATLSpaceship

#pragma once
#include "resource.h"       // main symbols

#include "ATLSpaceShipSvr.h"


// CClassicATLSpaceship

class ATL_NO_VTABLE CClassicATLSpaceship : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CClassicATLSpaceship, &CLSID_ClassicATLSpaceship>,
    public IDispatchImpl<IClassicATLSpaceship, &IID_IClassicATLSpaceship, 
                         &LIBID_ATLSpaceShipSvrLib>,
    public IDispatchImpl<IMotion, &IID_IMotion,
                         &LIBID_ATLSpaceShipSvrLib>,
    public IDispatchImpl<IVisual, &IID_IVisual,
                         &LIBID_ATLSpaceShipSvrLib>
{
public:
	CClassicATLSpaceship()
	{
        AtlTrace("Constructing the Classic ATL Spaceship\n");
	}

DECLARE_REGISTRY_RESOURCEID(IDR_CLASSICATLSPACESHIP)


BEGIN_COM_MAP(CClassicATLSpaceship)
    COM_INTERFACE_ENTRY(IClassicATLSpaceship)
    COM_INTERFACE_ENTRY2(IDispatch, IClassicATLSpaceship)
    COM_INTERFACE_ENTRY(IMotion)
    COM_INTERFACE_ENTRY(IVisual)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	
	void FinalRelease() 
	{
	}

long m_lPosition;

public:

    STDMETHOD(CallStarFleet)(FLOAT fStarDate, BSTR* pbstRecipient);

    STDMETHOD(Fly)();
    STDMETHOD(GetPosition)(long* lPosition);

    STDMETHOD(Display)();
};

OBJECT_ENTRY_AUTO(__uuidof(ClassicATLSpaceship), CClassicATLSpaceship)
