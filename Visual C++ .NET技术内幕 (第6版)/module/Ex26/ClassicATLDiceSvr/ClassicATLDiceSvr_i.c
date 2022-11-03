

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 11:14:07 2038
 */
/* Compiler settings for ClassicATLDiceSvr.idl:
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

MIDL_DEFINE_GUID(IID, IID_IClassicATLDiceControl,0x90621999,0x47DC,0x46CE,0xAC,0x37,0x8C,0x25,0x0A,0xEC,0x96,0xAA);


MIDL_DEFINE_GUID(IID, LIBID_ClassicATLDiceSvrLib,0xD66265FF,0xD959,0x47FB,0xBC,0x36,0x58,0x5A,0xFC,0x4F,0xFB,0x49);


MIDL_DEFINE_GUID(IID, DIID__IClassicATLDiceControlEvents,0x2FECDCBE,0xD2C8,0x46EF,0xA4,0xA1,0xE8,0x6C,0xDC,0x63,0xB3,0x21);


MIDL_DEFINE_GUID(CLSID, CLSID_ClassicATLDiceControl,0x75E15528,0x7E89,0x431F,0xB1,0x70,0xD6,0x99,0x1C,0x26,0xF9,0x44);


MIDL_DEFINE_GUID(CLSID, CLSID_CDiceMainPropPage,0x7A91E3F2,0x21BB,0x4286,0xB0,0x2E,0x4F,0x06,0x7F,0xD4,0x8D,0xB3);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



