// AttributedATLSpaceShip.h : Declaration of the CAttributedATLSpaceShip

#pragma once
#include "resource.h"       // main symbols


// IAttributedATLSpaceShip
[
	object,
	uuid("4B8685BD-00F1-4D38-AFC1-3012C786480D"),
	dual,	helpstring("IAttributedATLSpaceShip Interface"),
	pointer_default(unique)
]
__interface IAttributedATLSpaceShip : IDispatch
{
    [id(1), helpstring("method CallStarFleet")] HRESULT CallStarFleet([in] FLOAT fStarDate, [out,retval] BSTR* pbstrRecipient);
};

[
    object,
    uuid("692D03A4-C689-11CE-B337-88EA36DE9E4E"),
    dual,
    helpstring("IMotion interface")
]
__interface IMotion : IDispatch
{
    HRESULT Fly();
    HRESULT GetPosition([out,retval]long* nPosition);
};

[
    object,
    uuid("692D03A5-C689-11CE-B337-88EA36DE9E4E"),
    helpstring("IVisual interface")
]

__interface IVisual : IUnknown
{
    HRESULT Display();
};


// CAttributedATLSpaceShip

[
    coclass,
    threading("apartment"),
    vi_progid("AttributedATLSpaceShipSvr.AttributedATL"),
    progid("AttributedATLSpaceShipSvr.AttributedA.1"),
    version(1.0),
    uuid("CE07EBA4-0858-4A81-AD1C-C12710B4A1A2"),
    helpstring("AttributedATLSpaceShip Class")
]
class ATL_NO_VTABLE CAttributedATLSpaceShip : 
    public IAttributedATLSpaceShip,
    public IMotion,
    public IVisual
{
public:
    CAttributedATLSpaceShip()
    {
    }


    DECLARE_PROTECT_FINAL_CONSTRUCT()

    HRESULT FinalConstruct()
    {
        return S_OK;
    }

    void FinalRelease() 
    {
    }

public:

    STDMETHOD(CallStarFleet)(FLOAT fStarDate, BSTR* pbstrRecipient);

    // IMotion Methods
public:
    STDMETHOD(Fly)()
    {
        AtlTrace("Flying the Attributed ATL object\n");
        // Add your function implementation here.
        return E_NOTIMPL;
    }
    STDMETHOD(GetPosition)(long * nPosition)
    {
        AtlTrace("Getting the position of the Attributed ATL object\n");
        return E_NOTIMPL;
    }

    // IVisual Methods
public:
    STDMETHOD(Display)()
    {
        AtlTrace("Displaying the Attributed ATL object\n");
        return E_NOTIMPL;
    }
};

