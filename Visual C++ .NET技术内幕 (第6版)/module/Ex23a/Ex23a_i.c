

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 11:14:07 2038
 */
/* Compiler settings for Ex23a.idl:
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

MIDL_DEFINE_GUID(IID, LIBID_Ex23a,0x60BCA7D2,0x14D1,0x4832,0xA2,0x78,0x50,0x67,0x0C,0xD9,0x97,0x5E);


MIDL_DEFINE_GUID(IID, DIID_IEx23a,0x1F013122,0xEA3D,0x414F,0xB5,0x8F,0x5A,0x31,0xA6,0x4E,0xA5,0xD5);


MIDL_DEFINE_GUID(CLSID, CLSID_Ex23a,0x5EE5C98C,0x5CCF,0x46F4,0x9E,0x95,0x17,0xBC,0x06,0x23,0x7D,0x8B);


MIDL_DEFINE_GUID(IID, DIID_IBank,0x8BAD2B0C,0x62CC,0x4952,0x81,0x1C,0xC7,0x36,0xDA,0x06,0x85,0x8E);


MIDL_DEFINE_GUID(CLSID, CLSID_Bank,0x3EC6FA59,0x9F9F,0x4619,0x9F,0x62,0xBA,0x5F,0xE3,0x71,0x76,0xF0);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



