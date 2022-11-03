// Machine generated IDispatch wrapper class(es) created with Add Class from Typelib Wizard

// CBank wrapper class

class CBank : public COleDispatchDriver
{
public:
    CBank(){} // Calls COleDispatchDriver default constructor
    CBank(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
    CBank(const CBank& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

    // Attributes
public:

    // Operations
public:


    // IBank methods
public:
    double Withdrawal(double dAmount)
    {
        double result;
        static BYTE parms[] = VTS_R8 ;
        InvokeHelper(0x1, DISPATCH_METHOD, VT_R8, (void*)&result, parms, dAmount);
        return result;
    }
    void Deposit(double dAmount)
    {
        static BYTE parms[] = VTS_R8 ;
        InvokeHelper(0x2, DISPATCH_METHOD, VT_EMPTY, NULL, parms, dAmount);
    }

    // IBank properties
public:
    double GetBalance()
    {
        double result;
        GetProperty(0x3, VT_R8, (void*)&result);
        return result;
    }
    void SetBalance(double propVal)
    {
        SetProperty(0x3, VT_R8, propVal);
    }

};
