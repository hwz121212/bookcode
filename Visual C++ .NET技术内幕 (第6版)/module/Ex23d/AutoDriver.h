// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

// CEx23bAuto wrapper class

class CEx23bAuto : public COleDispatchDriver
{
public:
    CEx23bAuto(){} // Calls COleDispatchDriver default constructor
    CEx23bAuto(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
    CEx23bAuto(const CEx23bAuto& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

    // Attributes
public:

    // Operations
public:


    // IEx23bAuto methods
public:
    BOOL DisplayDialog()
    {
        BOOL result;
        InvokeHelper(0x3, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
        return result;
    }

    // IEx23bAuto properties
public:
    long GetLongData()
    {
        long result;
        GetProperty(0x1, VT_I4, (void*)&result);
        return result;
    }
    void SetLongData(long propVal)
    {
        SetProperty(0x1, VT_I4, propVal);
    }
    VARIANT GetTextData()
    {
        VARIANT result;
        GetProperty(0x2, VT_VARIANT, (void*)&result);
        return result;
    }
    void SetTextData(const VARIANT& propVal)
    {
        SetProperty(0x2, VT_VARIANT, &propVal);
    }

};
