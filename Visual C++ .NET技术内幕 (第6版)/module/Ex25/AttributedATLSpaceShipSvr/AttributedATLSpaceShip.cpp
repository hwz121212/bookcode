// AttributedATLSpaceShip.cpp : Implementation of CAttributedATLSpaceShip

#include "stdafx.h"
#include "AttributedATLSpaceShip.h"


// CAttributedATLSpaceShip


STDMETHODIMP CAttributedATLSpaceShip::CallStarFleet(FLOAT fStarDate, BSTR* pbstrRecipient)
{
    // TODO: Add your implementation code here

    AtlTrace("Calling Star Fleet from the Attributed ATL object\n");
    return S_OK;
}
