/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0158 */
/* at Mon Jun 22 15:22:06 1998
 */
/* Compiler settings for D:\BookCode\invcpp5\ex37c\ex37c.idl:
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

const IID IID_ICDHTML = {0x4B8FDD5C,0x09D1,0x11D2,{0xB3,0x0A,0x00,0x80,0xC7,0x36,0x0D,0xC1}};


const IID IID_ICDHTMLUI = {0x4B8FDD5E,0x09D1,0x11D2,{0xB3,0x0A,0x00,0x80,0xC7,0x36,0x0D,0xC1}};


const IID LIBID_EX37CLib = {0x4B8FDD50,0x09D1,0x11D2,{0xB3,0x0A,0x00,0x80,0xC7,0x36,0x0D,0xC1}};


const CLSID CLSID_CDHTML = {0x4B8FDD5D,0x09D1,0x11D2,{0xB3,0x0A,0x00,0x80,0xC7,0x36,0x0D,0xC1}};


#ifdef __cplusplus
}
#endif

