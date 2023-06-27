// AtlSpaceShip.h : Declaration of the CAtlSpaceShip

#ifndef __ATLSPACESHIP_H_
#define __ATLSPACESHIP_H_

#include "resource.h"       // main symbols


/////////////////////////////////////////////////////////////////////////////
// CAtlSpaceShip
class ATL_NO_VTABLE CAtlSpaceShip : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CAtlSpaceShip, &CLSID_AtlSpaceShip>,
	public IDispatchImpl<IAtlSpaceShip, &IID_IAtlSpaceShip, &LIBID_SPACESHIPSVRLib>,
    public IDispatchImpl<IVisual, &IID_IVisual,
                         &LIBID_SPACESHIPSVRLib>,
    public IDispatchImpl<IMotion, &IID_IMotion,
                         &LIBID_SPACESHIPSVRLib>

{
public:
	CAtlSpaceShip()
	{
		m_nPosition = 0;
		m_nAcceleration = 0;
		m_nColor = 0;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ATLSPACESHIP)

BEGIN_COM_MAP(CAtlSpaceShip)
	COM_INTERFACE_ENTRY(IAtlSpaceShip)
	COM_INTERFACE_ENTRY(IMotion)
	COM_INTERFACE_ENTRY2(IDispatch, IAtlSpaceShip)
	COM_INTERFACE_ENTRY(IVisual)
END_COM_MAP()

// IAtlSpaceShip
public:
	STDMETHOD(CallStarFleet)(/*[in]*/float fStarDate, /*[out, retval]*/BSTR* pbstRecipient);
	STDMETHOD(Fly)();
	STDMETHOD(GetPosition)(long* nPosition);
	STDMETHOD(Display)();

    int m_nPosition;
	int m_nAcceleration;
	int m_nColor;

};

#endif //__ATLSPACESHIP_H_
