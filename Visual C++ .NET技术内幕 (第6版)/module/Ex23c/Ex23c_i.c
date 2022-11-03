

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 11:14:07 2038
 */
/* Compiler settings for Ex23c.idl:
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

MIDL_DEFINE_GUID(IID, LIBID_Ex23c,0x02AF3B57,0x774B,0x4F74,0xB8,0x6D,0xB6,0x1C,0x74,0x6A,0x2F,0x8C);


MIDL_DEFINE_GUID(IID, DIID_IEx23c,0x74084826,0xF896,0x446F,0x84,0x14,0x3F,0xF2,0xBB,0x91,0x1A,0x63);


MIDL_DEFINE_GUID(CLSID, CLSID_CEx23cDoc,0x488A97C7,0xEBD1,0x4725,0x98,0x04,0xC3,0x1B,0x94,0x0D,0x0D,0xCA);


MIDL_DEFINE_GUID(IID, DIID_IAlarm,0x8DB7D0FB,0x355F,0x464B,0xBB,0xD5,0x0F,0x17,0x55,0x3E,0x71,0xC8);


MIDL_DEFINE_GUID(CLSID, CLSID_Alarm,0x052D0691,0xA19F,0x426F,0xBA,0x06,0xE6,0x22,0x34,0xB4,0x05,0xF3);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



