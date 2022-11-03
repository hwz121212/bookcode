

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 11:14:07 2038
 */
/* Compiler settings for _Ex29c.idl:
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

MIDL_DEFINE_GUID(IID, IID_ICDHTMLUI,0x9F3E85AE,0x09C6,0x4A3A,0xA7,0x8C,0x69,0x73,0xF8,0xA3,0x28,0xB6);


MIDL_DEFINE_GUID(IID, IID_ICDHTML,0xC0771F2F,0x6285,0x48EA,0x93,0x56,0x8A,0xA2,0xA4,0xD8,0xC4,0x7D);


MIDL_DEFINE_GUID(IID, LIBID_Ex29c,0xD937DD91,0xEAED,0x40FC,0xAD,0x14,0x1A,0x5D,0xAB,0x14,0xBF,0xC2);


MIDL_DEFINE_GUID(CLSID, CLSID_CCDHTMLUI,0x72DB36B5,0x154C,0x427E,0x9B,0xB0,0xAA,0xF3,0xC4,0x96,0xB6,0xEC);


MIDL_DEFINE_GUID(CLSID, CLSID_CCDHTML,0xE672F808,0x00BC,0x46AD,0x99,0x70,0x8D,0xB5,0x58,0x5E,0xAA,0x1E);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



