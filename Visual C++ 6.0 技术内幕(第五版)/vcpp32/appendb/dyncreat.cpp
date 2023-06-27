#include <stdio.h>

#define RUNTIME_CLASS(class_name) (&class_name::class##class_name)

class CObject;

struct CRuntimeClass
{
    char m_lpszClassName[21];
    int m_nObjectSize;
    CObject* (*m_pfnCreateObject)();
    CObject* CreateObject();
};

// not a true abstract class because there are no pure 
//  virtual functions, but user can't create CObject objects 
//  because of the protected constructor
class CObject
{
public:
    // not pure because derived classes don't necessarily
    // implement it
    virtual CRuntimeClass* GetRuntimeClass() const { return NULL; }
        
    // We never construct objects of class CObject, but in MFC we
    //  use this to get class hierarchy information
    static CRuntimeClass classCObject;        // DYNAMIC
     virtual ~CObject() {};  // gotta have it
protected:
    CObject() { printf("CObject constructor\n"); }
};

CRuntimeClass CObject::classCObject = { "CObject", 
    sizeof(CObject), NULL };

CObject* CRuntimeClass::CreateObject()
{
    return (*m_pfnCreateObject)(); // indirect function call
}

class CAlpha : public CObject
{
public:
    virtual CRuntimeClass* GetRuntimeClass() 
        const { return &classCAlpha; }
    static CRuntimeClass classCAlpha;        // DYNAMIC
    static CObject* CreateObject();          // DYNCREATE
protected:
    CAlpha() { printf("CAlpha constructor\n"); }
};

CRuntimeClass CAlpha::classCAlpha = { "CAlpha", 
    sizeof(CAlpha), CAlpha::CreateObject };

CObject* CAlpha::CreateObject() // static function
{
    return new CAlpha;    
}

class CBeta : public CObject
{
public:
    virtual CRuntimeClass* GetRuntimeClass() 
        const { return &classCBeta; }
    static CRuntimeClass classCBeta;         // DYNAMIC
    static CObject* CreateObject();          // DYNCREATE
protected:
    CBeta() { printf("CBeta constructor\n"); }
};

CRuntimeClass CBeta::classCBeta = { "CBeta", 
    sizeof(CBeta), CBeta::CreateObject };

CObject* CBeta::CreateObject() // static function
{
    return new CBeta;    
}

int main()
{
    printf("Entering dyncreate main\n");

    CRuntimeClass* pRTCAlpha = RUNTIME_CLASS(CAlpha);
    CObject* pObj1 = pRTCAlpha->CreateObject();
    printf("class of pObj1 = %s\n", 
        pObj1->GetRuntimeClass()->m_lpszClassName);

    CRuntimeClass* pRTCBeta = RUNTIME_CLASS(CBeta);
    CObject* pObj2 = pRTCBeta->CreateObject();
    printf("class of pObj2 = %s\n", 
        pObj2->GetRuntimeClass()->m_lpszClassName);

    delete pObj1;
    delete pObj2;
    return 0;
}
