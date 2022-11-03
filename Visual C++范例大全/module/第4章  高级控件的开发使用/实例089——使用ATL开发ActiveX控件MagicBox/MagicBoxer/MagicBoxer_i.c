

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 11:14:07 2038
 */
/* Compiler settings for MagicBoxer.idl:
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

MIDL_DEFINE_GUID(IID, IID_IMagicBox,0x463C57B6,0xCA1D,0x4E3A,0x91,0x0C,0x05,0x63,0xA6,0x99,0x2F,0xFA);


MIDL_DEFINE_GUID(IID, LIBID_MAGICBOXERLib,0x0A9BCD72,0xB597,0x455F,0x87,0x4A,0xFE,0x0B,0xE7,0x2E,0x92,0xB9);


MIDL_DEFINE_GUID(IID, DIID__IMagicBoxEvents,0xF56D5432,0xD8AD,0x40D2,0x92,0x55,0x81,0xA6,0x41,0x42,0xFF,0x88);


MIDL_DEFINE_GUID(CLSID, CLSID_MagicBox,0x9C4A11F3,0x7AA3,0x4587,0xBB,0x40,0x7A,0x53,0x69,0x06,0x31,0x37);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



