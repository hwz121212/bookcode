// AtlSpaceShip.cpp : Implementation of CAtlSpaceShip
#include "stdafx.h"
#include "Spaceshipsvr.h"
#include "AtlSpaceShip.h"

/////////////////////////////////////////////////////////////////////////////
// CAtlSpaceShip


STDMETHODIMP CAtlSpaceShip::CallStarFleet(float fStarDate, BSTR *pbstRecipient)
{
	ATLTRACE("Calling Star fleet");
	return S_OK;
}

STDMETHODIMP CAtlSpaceShip::Fly() {
	// not doing too much here-- we're really just interested in the structure
    OutputDebugString("Entering CSpaceship::XMotion::Fly\n");
    ATLTRACE("m_nPosition = %d\n", m_nPosition);
    ATLTRACE("m_nAcceleration = %d\n", m_nAcceleration);
	return S_OK;
}

STDMETHODIMP CAtlSpaceShip::GetPosition(long* nPosition) {
	// not doing too much here-- we're really just interested in the structure
    ATLTRACE("CATLSpaceShip::GetPosition\n");
    ATLTRACE("m_nPosition = %d\n", m_nPosition);
    ATLTRACE("m_nAcceleration = %d\n", m_nAcceleration);
	*nPosition = m_nPosition;
	return S_OK;
}

STDMETHODIMP CAtlSpaceShip::Display() {
	// not doing too much here-- we're really just interested in the structure
    ATLTRACE("CSpaceship::XVisual::Display\n");
    ATLTRACE("m_nPosition = %d\n", m_nPosition);
    ATLTRACE("m_nColor = %d\n", m_nColor);
	return S_OK;
}
