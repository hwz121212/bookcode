
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Wed May 15 15:00:47 2002
 */
/* Compiler settings for _AttributedATLDiceSvr.idl:
    Os, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#if !defined(_M_IA64) && !defined(_M_AMD64)

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
        const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_IAttributedATLDiceControl,0x5321A066,0x9E3A,0x4412,0xA1,0x1A,0x32,0xD5,0xED,0x06,0x01,0x46);


MIDL_DEFINE_GUID(IID, LIBID_AttributedATLDiceSvr,0x1EEE94B7,0xE4A3,0x4059,0x87,0xC6,0x80,0x33,0xA4,0x9B,0xB2,0xDB);


MIDL_DEFINE_GUID(IID, DIID__IAttributedATLDiceControlEvents,0x4AB0D205,0x044E,0x4641,0xA0,0xA5,0xB6,0x06,0xD8,0x68,0x5F,0xE5);


MIDL_DEFINE_GUID(CLSID, CLSID_CAttributedATLDiceControl,0x48350572,0xBE82,0x4FBB,0xAA,0x6F,0xB4,0x69,0x1E,0x30,0x17,0x3A);


MIDL_DEFINE_GUID(CLSID, CLSID_CDiceMainPropPage,0x0B276055,0x2D66,0x4738,0x91,0xD3,0xEF,0x8C,0x1D,0x04,0x97,0xAE);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



#endif /* !defined(_M_IA64) && !defined(_M_AMD64)*/

