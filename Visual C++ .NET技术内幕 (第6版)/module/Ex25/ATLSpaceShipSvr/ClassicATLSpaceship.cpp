// ClassicATLSpaceship.cpp : Implementation of CClassicATLSpaceship

#include "stdafx.h"
#include "ClassicATLSpaceship.h"


// CClassicATLSpaceship


STDMETHODIMP CClassicATLSpaceship::CallStarFleet(FLOAT fStarDate, BSTR* pbstRecipient)
{
    AtlTrace("Calling Star Fleet from the Classic ATL object\n");

    return S_OK;
}

STDMETHODIMP CClassicATLSpaceship::Fly()
{
    AtlTrace("Flying the Classic ATL object\n");
    return S_OK;
}

STDMETHODIMP CClassicATLSpaceship::GetPosition(long* lPosition)
{
    AtlTrace("Getting the position of the Classic ATL object\n");
    *lPosition = m_lPosition;
    return S_OK;
}

STDMETHODIMP CClassicATLSpaceship::Display()
{
    AtlTrace("Displaying the classic ATL object\n");
    return S_OK;
}