// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

// CAlarm wrapper class

class CAlarm : public COleDispatchDriver
{
public:
    CAlarm(){} // Calls COleDispatchDriver default constructor
    CAlarm(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
    CAlarm(const CAlarm& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

    // Attributes
public:

    // Operations
public:


    // IAlarm methods
public:

    // IAlarm properties
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
