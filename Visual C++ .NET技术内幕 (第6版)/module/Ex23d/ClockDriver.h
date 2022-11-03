// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

// CEx23c wrapper class

class CEx23c : public COleDispatchDriver
{
public:
    CEx23c(){} // Calls COleDispatchDriver default constructor
    CEx23c(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
    CEx23c(const CEx23c& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

    // Attributes
public:

    // Operations
public:


    // IEx23c methods
public:
    void ShowWin()
    {
        InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
    }
    LPDISPATCH CreateAlarm(DATE Time)
    {
        LPDISPATCH result;
        static BYTE parms[] = VTS_DATE ;
        InvokeHelper(0x3, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Time);
        return result;
    }
    void RefreshWin()
    {
        InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
    }
    VARIANT get_Figure(short n)
    {
        VARIANT result;
        static BYTE parms[] = VTS_I2 ;
        InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms, n);
        return result;
    }
    void put_Figure(short n, VARIANT newValue)
    {
        static BYTE parms[] = VTS_I2 VTS_VARIANT ;
        InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, n, &newValue);
    }

    // IEx23c properties
public:
    DATE GetTime()
    {
        DATE result;
        GetProperty(0x1, VT_DATE, (void*)&result);
        return result;
    }
    void SetTime(DATE propVal)
    {
        SetProperty(0x1, VT_DATE, propVal);
    }

};
