

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 11:14:07 2038
 */
/* Compiler settings for OleEdit.odl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.01.0622 
    protocol : dce , ms_ext, c_ext, robust
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

MIDL_DEFINE_GUID(IID, LIBID_OLEEDITLib,0xE88D840C,0xCAD4,0x4468,0xA1,0x72,0x04,0xF0,0x15,0x3E,0xD7,0xBD);


MIDL_DEFINE_GUID(IID, DIID__DOleEdit,0x288788D5,0xF3BF,0x4880,0x97,0xB4,0xCD,0x01,0x74,0x4E,0x44,0x91);


MIDL_DEFINE_GUID(IID, DIID__DOleEditEvents,0x87969E28,0x0660,0x49CB,0xA9,0x9A,0x3F,0x34,0x55,0x23,0x32,0xEA);


MIDL_DEFINE_GUID(CLSID, CLSID_OleEdit,0x0A2E1C1D,0x5F28,0x4850,0x91,0x29,0x8D,0x55,0xE9,0xB6,0xBB,0x6D);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



