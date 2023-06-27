/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0158 */
/* at Thu Jun 18 16:56:52 1998
 */
/* Compiler settings for D:\BookCode\ex30a\atldicesrvr.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )
#ifdef __cplusplus
extern "C"{
#endif 


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

const IID IID_IATLDiceObj = {0x93BC1349,0x065C,0x11D2,{0x8C,0xAA,0xA5,0x27,0x3A,0x38,0x86,0x38}};


const IID LIBID_ATLDICESRVRLib = {0x93BC133D,0x065C,0x11D2,{0x8C,0xAA,0xA5,0x27,0x3A,0x38,0x86,0x38}};


const IID DIID__IATLDiceObjEvents = {0x93BC134B,0x065C,0x11D2,{0x8C,0xAA,0xA5,0x27,0x3A,0x38,0x86,0x38}};


const CLSID CLSID_ATLDiceObj = {0x93BC134A,0x065C,0x11D2,{0x8C,0xAA,0xA5,0x27,0x3A,0x38,0x86,0x38}};


const CLSID CLSID_DiceMainPropPage = {0x93BC134D,0x065C,0x11D2,{0x8C,0xAA,0xA5,0x27,0x3A,0x38,0x86,0x38}};


#ifdef __cplusplus
}
#endif

