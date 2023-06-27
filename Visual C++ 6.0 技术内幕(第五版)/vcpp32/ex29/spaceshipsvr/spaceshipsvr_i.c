/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0158 */
/* at Thu Jun 18 16:49:58 1998
 */
/* Compiler settings for D:\BookCode\ex29a\spaceshipsvr\spaceshipsvr.idl:
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

const IID IID_IAtlSpaceShip = {0xA9D750E1,0x51A1,0x11D1,{0x8C,0xAA,0xFD,0x10,0x87,0x2C,0xC8,0x37}};


const IID IID_IMotion = {0x692D03A4,0xC689,0x11CE,{0xB3,0x37,0x88,0xEA,0x36,0xDE,0x9E,0x4E}};


const IID IID_IVisual = {0x692D03A5,0xC689,0x11CE,{0xB3,0x37,0x88,0xEA,0x36,0xDE,0x9E,0x4E}};


const IID LIBID_SPACESHIPSVRLib = {0xA0736061,0x50DF,0x11D1,{0x8C,0xAA,0xFD,0x10,0x87,0x2C,0xC8,0x37}};


const CLSID CLSID_AtlSpaceShip = {0xA9D750E2,0x51A1,0x11D1,{0x8C,0xAA,0xFD,0x10,0x87,0x2C,0xC8,0x37}};


#ifdef __cplusplus
}
#endif

