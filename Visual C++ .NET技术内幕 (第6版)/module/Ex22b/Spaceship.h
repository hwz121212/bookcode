
#pragma once

void ITrace(REFIID iid, const char* str);

// CSpaceship command target

class CSpaceship : public CCmdTarget
{
	DECLARE_DYNCREATE(CSpaceship)

private:
    int m_nPosition; // We can access this from all the interfaces
    int m_nAcceleration;
    int m_nColor;

public:
	CSpaceship();
	virtual ~CSpaceship();

	virtual void OnFinalRelease();

protected:
	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CSpaceship)
	
	BEGIN_INTERFACE_PART(Motion, IMotion)
        STDMETHOD_(void, Fly) ();
        STDMETHOD_(int&, GetPosition) ();
    END_INTERFACE_PART(Motion)
    
    BEGIN_INTERFACE_PART(Visual, IVisual)
        STDMETHOD_(void, Display) ();
    END_INTERFACE_PART(Visual)
    DECLARE_INTERFACE_MAP()
};


