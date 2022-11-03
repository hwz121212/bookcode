

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 11:14:07 2038
 */
/* Compiler settings for _AttributedATLSpaceShipSvr.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.01.0622 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        EXTERN_C __declspec(selectany) const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif // !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_IAttributedATLSpaceShip,0x4B8685BD,0x00F1,0x4D38,0xAF,0xC1,0x30,0x12,0xC7,0x86,0x48,0x0D);


MIDL_DEFINE_GUID(IID, IID_IMotion,0x692D03A4,0xC689,0x11CE,0xB3,0x37,0x88,0xEA,0x36,0xDE,0x9E,0x4E);


MIDL_DEFINE_GUID(IID, IID_IVisual,0x692D03A5,0xC689,0x11CE,0xB3,0x37,0x88,0xEA,0x36,0xDE,0x9E,0x4E);


MIDL_DEFINE_GUID(IID, LIBID_AttributedATLSpaceShipSvr,0xFD11BA43,0x99D4,0x4857,0x83,0x66,0x97,0x49,0xB0,0x31,0x90,0x4C);


MIDL_DEFINE_GUID(CLSID, CLSID_CAttributedATLSpaceShip,0xCE07EBA4,0x0858,0x4A81,0xAD,0x1C,0xC1,0x27,0x10,0xB4,0xA1,0xA2);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



