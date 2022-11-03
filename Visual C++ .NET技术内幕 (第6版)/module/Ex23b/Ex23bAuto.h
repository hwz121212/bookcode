
#pragma once


// CEx23bAuto command target

class CEx23bAuto : public CCmdTarget
{
	DECLARE_DYNCREATE(CEx23bAuto)

public:
	CEx23bAuto();
	virtual ~CEx23bAuto();

	virtual void OnFinalRelease();

protected:
	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CEx23bAuto)
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
    void OnLongDataChanged(void);
    LONG m_lData;

    enum 
    {
        dispidDisplayDialog = 3L,        
        dispidTextData = 2,        
        dispidLongData = 1
    };
    void OnTextDataChanged(void);
    VARIANT m_vaTextData;
    VARIANT_BOOL DisplayDialog(void);
};


