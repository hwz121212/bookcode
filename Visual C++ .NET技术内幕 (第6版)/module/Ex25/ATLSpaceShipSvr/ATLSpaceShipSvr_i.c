

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 11:14:07 2038
 */
/* Compiler settings for ATLSpaceShipSvr.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.01.0622 
    protocol : all , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



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

MIDL_DEFINE_GUID(IID, IID_IMotion,0x692D03A4,0xC689,0x11CE,0xB3,0x37,0x88,0xEA,0x36,0xDE,0x9E,0x4E);


MIDL_DEFINE_GUID(IID, IID_IVisual,0x692D03A5,0xC689,0x11CE,0xB3,0x37,0x88,0xEA,0x36,0xDE,0x9E,0x4E);


MIDL_DEFINE_GUID(IID, IID_IClassicATLSpaceship,0x45896187,0x46FF,0x4A07,0xA9,0xDC,0x55,0x73,0x77,0x38,0x05,0x35);


MIDL_DEFINE_GUID(IID, LIBID_ATLSpaceShipSvrLib,0xF5FD4043,0x22AE,0x470D,0x8C,0x43,0x1A,0xC9,0x04,0xD2,0xE8,0xE0);


MIDL_DEFINE_GUID(CLSID, CLSID_ClassicATLSpaceship,0xE485E21E,0xA23C,0x413F,0xA9,0x3B,0x90,0x93,0x18,0x56,0x51,0x13);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



