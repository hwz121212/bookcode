

/* this ALWAYS GENERATED file contains the proxy stub code */


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

#if defined(_M_AMD64)


#pragma warning( disable: 4049 )  /* more than 64k source lines */
#if _MSC_VER >= 1200
#pragma warning(push)
#endif

#pragma warning( disable: 4211 )  /* redefine extern to static */
#pragma warning( disable: 4232 )  /* dllimport identity*/
#pragma warning( disable: 4024 )  /* array to pointer mapping*/
#pragma warning( disable: 4152 )  /* function/data pointer conversion in expression */

#define USE_STUBLESS_PROXY


/* verify that the <rpcproxy.h> version is high enough to compile this file*/
#ifndef __REDQ_RPCPROXY_H_VERSION__
#define __REQUIRED_RPCPROXY_H_VERSION__ 475
#endif


#include "rpcproxy.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif /* __RPCPROXY_H_VERSION__ */


#include "_Ex29c.h"

#define TYPE_FORMAT_STRING_SIZE   989                               
#define PROC_FORMAT_STRING_SIZE   45                                
#define EXPR_FORMAT_STRING_SIZE   1                                 
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   1            

typedef struct __Ex29c_MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } _Ex29c_MIDL_TYPE_FORMAT_STRING;

typedef struct __Ex29c_MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } _Ex29c_MIDL_PROC_FORMAT_STRING;

typedef struct __Ex29c_MIDL_EXPR_FORMAT_STRING
    {
    long          Pad;
    unsigned char  Format[ EXPR_FORMAT_STRING_SIZE ];
    } _Ex29c_MIDL_EXPR_FORMAT_STRING;


static const RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};


extern const _Ex29c_MIDL_TYPE_FORMAT_STRING _Ex29c__MIDL_TypeFormatString;
extern const _Ex29c_MIDL_PROC_FORMAT_STRING _Ex29c__MIDL_ProcFormatString;
extern const _Ex29c_MIDL_EXPR_FORMAT_STRING _Ex29c__MIDL_ExprFormatString;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO ICDHTMLUI_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO ICDHTMLUI_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO ICDHTML_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO ICDHTML_ProxyInfo;


extern const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ];

#if !defined(__RPC_WIN64__)
#error  Invalid build platform for this stub.
#endif

static const _Ex29c_MIDL_PROC_FORMAT_STRING _Ex29c__MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure OnClick */

			0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/*  2 */	NdrFcLong( 0x0 ),	/* 0 */
/*  6 */	NdrFcShort( 0x7 ),	/* 7 */
/*  8 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 10 */	NdrFcShort( 0x0 ),	/* 0 */
/* 12 */	NdrFcShort( 0x8 ),	/* 8 */
/* 14 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x3,		/* 3 */
/* 16 */	0xa,		/* 10 */
			0x85,		/* Ext Flags:  new corr desc, srv corr check, has big byval param */
/* 18 */	NdrFcShort( 0x0 ),	/* 0 */
/* 20 */	NdrFcShort( 0x1 ),	/* 1 */
/* 22 */	NdrFcShort( 0x0 ),	/* 0 */
/* 24 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter pdispBody */

/* 26 */	NdrFcShort( 0xb ),	/* Flags:  must size, must free, in, */
/* 28 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 30 */	NdrFcShort( 0x2 ),	/* Type Offset=2 */

	/* Parameter varColor */

/* 32 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 34 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 36 */	NdrFcShort( 0x3d2 ),	/* Type Offset=978 */

	/* Return value */

/* 38 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 40 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 42 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const _Ex29c_MIDL_TYPE_FORMAT_STRING _Ex29c__MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */
/*  2 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/*  4 */	NdrFcLong( 0x20400 ),	/* 132096 */
/*  8 */	NdrFcShort( 0x0 ),	/* 0 */
/* 10 */	NdrFcShort( 0x0 ),	/* 0 */
/* 12 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 14 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 16 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 18 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 20 */	
			0x11, 0x0,	/* FC_RP */
/* 22 */	NdrFcShort( 0x3bc ),	/* Offset= 956 (978) */
/* 24 */	
			0x12, 0x0,	/* FC_UP */
/* 26 */	NdrFcShort( 0x3a4 ),	/* Offset= 932 (958) */
/* 28 */	
			0x2b,		/* FC_NON_ENCAPSULATED_UNION */
			0x9,		/* FC_ULONG */
/* 30 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 32 */	NdrFcShort( 0xfff8 ),	/* -8 */
/* 34 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 36 */	NdrFcShort( 0x2 ),	/* Offset= 2 (38) */
/* 38 */	NdrFcShort( 0x10 ),	/* 16 */
/* 40 */	NdrFcShort( 0x2f ),	/* 47 */
/* 42 */	NdrFcLong( 0x14 ),	/* 20 */
/* 46 */	NdrFcShort( 0x800b ),	/* Simple arm type: FC_HYPER */
/* 48 */	NdrFcLong( 0x3 ),	/* 3 */
/* 52 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 54 */	NdrFcLong( 0x11 ),	/* 17 */
/* 58 */	NdrFcShort( 0x8001 ),	/* Simple arm type: FC_BYTE */
/* 60 */	NdrFcLong( 0x2 ),	/* 2 */
/* 64 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 66 */	NdrFcLong( 0x4 ),	/* 4 */
/* 70 */	NdrFcShort( 0x800a ),	/* Simple arm type: FC_FLOAT */
/* 72 */	NdrFcLong( 0x5 ),	/* 5 */
/* 76 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 78 */	NdrFcLong( 0xb ),	/* 11 */
/* 82 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 84 */	NdrFcLong( 0xa ),	/* 10 */
/* 88 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 90 */	NdrFcLong( 0x6 ),	/* 6 */
/* 94 */	NdrFcShort( 0xe8 ),	/* Offset= 232 (326) */
/* 96 */	NdrFcLong( 0x7 ),	/* 7 */
/* 100 */	NdrFcShort( 0x800c ),	/* Simple arm type: FC_DOUBLE */
/* 102 */	NdrFcLong( 0x8 ),	/* 8 */
/* 106 */	NdrFcShort( 0xe2 ),	/* Offset= 226 (332) */
/* 108 */	NdrFcLong( 0xd ),	/* 13 */
/* 112 */	NdrFcShort( 0xf6 ),	/* Offset= 246 (358) */
/* 114 */	NdrFcLong( 0x9 ),	/* 9 */
/* 118 */	NdrFcShort( 0xff8c ),	/* Offset= -116 (2) */
/* 120 */	NdrFcLong( 0x2000 ),	/* 8192 */
/* 124 */	NdrFcShort( 0xfc ),	/* Offset= 252 (376) */
/* 126 */	NdrFcLong( 0x24 ),	/* 36 */
/* 130 */	NdrFcShort( 0x2f2 ),	/* Offset= 754 (884) */
/* 132 */	NdrFcLong( 0x4024 ),	/* 16420 */
/* 136 */	NdrFcShort( 0x2ec ),	/* Offset= 748 (884) */
/* 138 */	NdrFcLong( 0x4011 ),	/* 16401 */
/* 142 */	NdrFcShort( 0x2ea ),	/* Offset= 746 (888) */
/* 144 */	NdrFcLong( 0x4002 ),	/* 16386 */
/* 148 */	NdrFcShort( 0x2e8 ),	/* Offset= 744 (892) */
/* 150 */	NdrFcLong( 0x4003 ),	/* 16387 */
/* 154 */	NdrFcShort( 0x2e6 ),	/* Offset= 742 (896) */
/* 156 */	NdrFcLong( 0x4014 ),	/* 16404 */
/* 160 */	NdrFcShort( 0x2e4 ),	/* Offset= 740 (900) */
/* 162 */	NdrFcLong( 0x4004 ),	/* 16388 */
/* 166 */	NdrFcShort( 0x2e2 ),	/* Offset= 738 (904) */
/* 168 */	NdrFcLong( 0x4005 ),	/* 16389 */
/* 172 */	NdrFcShort( 0x2e0 ),	/* Offset= 736 (908) */
/* 174 */	NdrFcLong( 0x400b ),	/* 16395 */
/* 178 */	NdrFcShort( 0x2ca ),	/* Offset= 714 (892) */
/* 180 */	NdrFcLong( 0x400a ),	/* 16394 */
/* 184 */	NdrFcShort( 0x2c8 ),	/* Offset= 712 (896) */
/* 186 */	NdrFcLong( 0x4006 ),	/* 16390 */
/* 190 */	NdrFcShort( 0x2d2 ),	/* Offset= 722 (912) */
/* 192 */	NdrFcLong( 0x4007 ),	/* 16391 */
/* 196 */	NdrFcShort( 0x2c8 ),	/* Offset= 712 (908) */
/* 198 */	NdrFcLong( 0x4008 ),	/* 16392 */
/* 202 */	NdrFcShort( 0x2ca ),	/* Offset= 714 (916) */
/* 204 */	NdrFcLong( 0x400d ),	/* 16397 */
/* 208 */	NdrFcShort( 0x2c8 ),	/* Offset= 712 (920) */
/* 210 */	NdrFcLong( 0x4009 ),	/* 16393 */
/* 214 */	NdrFcShort( 0x2c6 ),	/* Offset= 710 (924) */
/* 216 */	NdrFcLong( 0x6000 ),	/* 24576 */
/* 220 */	NdrFcShort( 0x2c4 ),	/* Offset= 708 (928) */
/* 222 */	NdrFcLong( 0x400c ),	/* 16396 */
/* 226 */	NdrFcShort( 0x2c2 ),	/* Offset= 706 (932) */
/* 228 */	NdrFcLong( 0x10 ),	/* 16 */
/* 232 */	NdrFcShort( 0x8002 ),	/* Simple arm type: FC_CHAR */
/* 234 */	NdrFcLong( 0x12 ),	/* 18 */
/* 238 */	NdrFcShort( 0x8006 ),	/* Simple arm type: FC_SHORT */
/* 240 */	NdrFcLong( 0x13 ),	/* 19 */
/* 244 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 246 */	NdrFcLong( 0x15 ),	/* 21 */
/* 250 */	NdrFcShort( 0x800b ),	/* Simple arm type: FC_HYPER */
/* 252 */	NdrFcLong( 0x16 ),	/* 22 */
/* 256 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 258 */	NdrFcLong( 0x17 ),	/* 23 */
/* 262 */	NdrFcShort( 0x8008 ),	/* Simple arm type: FC_LONG */
/* 264 */	NdrFcLong( 0xe ),	/* 14 */
/* 268 */	NdrFcShort( 0x2a0 ),	/* Offset= 672 (940) */
/* 270 */	NdrFcLong( 0x400e ),	/* 16398 */
/* 274 */	NdrFcShort( 0x2a4 ),	/* Offset= 676 (950) */
/* 276 */	NdrFcLong( 0x4010 ),	/* 16400 */
/* 280 */	NdrFcShort( 0x2a2 ),	/* Offset= 674 (954) */
/* 282 */	NdrFcLong( 0x4012 ),	/* 16402 */
/* 286 */	NdrFcShort( 0x25e ),	/* Offset= 606 (892) */
/* 288 */	NdrFcLong( 0x4013 ),	/* 16403 */
/* 292 */	NdrFcShort( 0x25c ),	/* Offset= 604 (896) */
/* 294 */	NdrFcLong( 0x4015 ),	/* 16405 */
/* 298 */	NdrFcShort( 0x25a ),	/* Offset= 602 (900) */
/* 300 */	NdrFcLong( 0x4016 ),	/* 16406 */
/* 304 */	NdrFcShort( 0x250 ),	/* Offset= 592 (896) */
/* 306 */	NdrFcLong( 0x4017 ),	/* 16407 */
/* 310 */	NdrFcShort( 0x24a ),	/* Offset= 586 (896) */
/* 312 */	NdrFcLong( 0x0 ),	/* 0 */
/* 316 */	NdrFcShort( 0x0 ),	/* Offset= 0 (316) */
/* 318 */	NdrFcLong( 0x1 ),	/* 1 */
/* 322 */	NdrFcShort( 0x0 ),	/* Offset= 0 (322) */
/* 324 */	NdrFcShort( 0xffff ),	/* Offset= -1 (323) */
/* 326 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 328 */	NdrFcShort( 0x8 ),	/* 8 */
/* 330 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 332 */	
			0x12, 0x0,	/* FC_UP */
/* 334 */	NdrFcShort( 0xe ),	/* Offset= 14 (348) */
/* 336 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 338 */	NdrFcShort( 0x2 ),	/* 2 */
/* 340 */	0x9,		/* Corr desc: FC_ULONG */
			0x0,		/*  */
/* 342 */	NdrFcShort( 0xfffc ),	/* -4 */
/* 344 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 346 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 348 */	
			0x17,		/* FC_CSTRUCT */
			0x3,		/* 3 */
/* 350 */	NdrFcShort( 0x8 ),	/* 8 */
/* 352 */	NdrFcShort( 0xfff0 ),	/* Offset= -16 (336) */
/* 354 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 356 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 358 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 360 */	NdrFcLong( 0x0 ),	/* 0 */
/* 364 */	NdrFcShort( 0x0 ),	/* 0 */
/* 366 */	NdrFcShort( 0x0 ),	/* 0 */
/* 368 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 370 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 372 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 374 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 376 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 378 */	NdrFcShort( 0x2 ),	/* Offset= 2 (380) */
/* 380 */	
			0x12, 0x0,	/* FC_UP */
/* 382 */	NdrFcShort( 0x1e4 ),	/* Offset= 484 (866) */
/* 384 */	
			0x2a,		/* FC_ENCAPSULATED_UNION */
			0x89,		/* 137 */
/* 386 */	NdrFcShort( 0x20 ),	/* 32 */
/* 388 */	NdrFcShort( 0xa ),	/* 10 */
/* 390 */	NdrFcLong( 0x8 ),	/* 8 */
/* 394 */	NdrFcShort( 0x50 ),	/* Offset= 80 (474) */
/* 396 */	NdrFcLong( 0xd ),	/* 13 */
/* 400 */	NdrFcShort( 0x70 ),	/* Offset= 112 (512) */
/* 402 */	NdrFcLong( 0x9 ),	/* 9 */
/* 406 */	NdrFcShort( 0x90 ),	/* Offset= 144 (550) */
/* 408 */	NdrFcLong( 0xc ),	/* 12 */
/* 412 */	NdrFcShort( 0xb0 ),	/* Offset= 176 (588) */
/* 414 */	NdrFcLong( 0x24 ),	/* 36 */
/* 418 */	NdrFcShort( 0x102 ),	/* Offset= 258 (676) */
/* 420 */	NdrFcLong( 0x800d ),	/* 32781 */
/* 424 */	NdrFcShort( 0x11e ),	/* Offset= 286 (710) */
/* 426 */	NdrFcLong( 0x10 ),	/* 16 */
/* 430 */	NdrFcShort( 0x138 ),	/* Offset= 312 (742) */
/* 432 */	NdrFcLong( 0x2 ),	/* 2 */
/* 436 */	NdrFcShort( 0x14e ),	/* Offset= 334 (770) */
/* 438 */	NdrFcLong( 0x3 ),	/* 3 */
/* 442 */	NdrFcShort( 0x164 ),	/* Offset= 356 (798) */
/* 444 */	NdrFcLong( 0x14 ),	/* 20 */
/* 448 */	NdrFcShort( 0x17a ),	/* Offset= 378 (826) */
/* 450 */	NdrFcShort( 0xffff ),	/* Offset= -1 (449) */
/* 452 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 454 */	NdrFcShort( 0x0 ),	/* 0 */
/* 456 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 458 */	NdrFcShort( 0x0 ),	/* 0 */
/* 460 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 462 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 466 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 468 */	
			0x12, 0x0,	/* FC_UP */
/* 470 */	NdrFcShort( 0xff86 ),	/* Offset= -122 (348) */
/* 472 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 474 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 476 */	NdrFcShort( 0x10 ),	/* 16 */
/* 478 */	NdrFcShort( 0x0 ),	/* 0 */
/* 480 */	NdrFcShort( 0x6 ),	/* Offset= 6 (486) */
/* 482 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 484 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 486 */	
			0x11, 0x0,	/* FC_RP */
/* 488 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (452) */
/* 490 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 492 */	NdrFcShort( 0x0 ),	/* 0 */
/* 494 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 496 */	NdrFcShort( 0x0 ),	/* 0 */
/* 498 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 500 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 504 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 506 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 508 */	NdrFcShort( 0xff6a ),	/* Offset= -150 (358) */
/* 510 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 512 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 514 */	NdrFcShort( 0x10 ),	/* 16 */
/* 516 */	NdrFcShort( 0x0 ),	/* 0 */
/* 518 */	NdrFcShort( 0x6 ),	/* Offset= 6 (524) */
/* 520 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 522 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 524 */	
			0x11, 0x0,	/* FC_RP */
/* 526 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (490) */
/* 528 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 530 */	NdrFcShort( 0x0 ),	/* 0 */
/* 532 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 534 */	NdrFcShort( 0x0 ),	/* 0 */
/* 536 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 538 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 542 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 544 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 546 */	NdrFcShort( 0xfde0 ),	/* Offset= -544 (2) */
/* 548 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 550 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 552 */	NdrFcShort( 0x10 ),	/* 16 */
/* 554 */	NdrFcShort( 0x0 ),	/* 0 */
/* 556 */	NdrFcShort( 0x6 ),	/* Offset= 6 (562) */
/* 558 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 560 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 562 */	
			0x11, 0x0,	/* FC_RP */
/* 564 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (528) */
/* 566 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 568 */	NdrFcShort( 0x0 ),	/* 0 */
/* 570 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 572 */	NdrFcShort( 0x0 ),	/* 0 */
/* 574 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 576 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 580 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 582 */	
			0x12, 0x0,	/* FC_UP */
/* 584 */	NdrFcShort( 0x176 ),	/* Offset= 374 (958) */
/* 586 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 588 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 590 */	NdrFcShort( 0x10 ),	/* 16 */
/* 592 */	NdrFcShort( 0x0 ),	/* 0 */
/* 594 */	NdrFcShort( 0x6 ),	/* Offset= 6 (600) */
/* 596 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 598 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 600 */	
			0x11, 0x0,	/* FC_RP */
/* 602 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (566) */
/* 604 */	
			0x2f,		/* FC_IP */
			0x5a,		/* FC_CONSTANT_IID */
/* 606 */	NdrFcLong( 0x2f ),	/* 47 */
/* 610 */	NdrFcShort( 0x0 ),	/* 0 */
/* 612 */	NdrFcShort( 0x0 ),	/* 0 */
/* 614 */	0xc0,		/* 192 */
			0x0,		/* 0 */
/* 616 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 618 */	0x0,		/* 0 */
			0x0,		/* 0 */
/* 620 */	0x0,		/* 0 */
			0x46,		/* 70 */
/* 622 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 624 */	NdrFcShort( 0x1 ),	/* 1 */
/* 626 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 628 */	NdrFcShort( 0x4 ),	/* 4 */
/* 630 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 632 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 634 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 636 */	NdrFcShort( 0x18 ),	/* 24 */
/* 638 */	NdrFcShort( 0x0 ),	/* 0 */
/* 640 */	NdrFcShort( 0xa ),	/* Offset= 10 (650) */
/* 642 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 644 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 646 */	NdrFcShort( 0xffd6 ),	/* Offset= -42 (604) */
/* 648 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 650 */	
			0x12, 0x0,	/* FC_UP */
/* 652 */	NdrFcShort( 0xffe2 ),	/* Offset= -30 (622) */
/* 654 */	
			0x21,		/* FC_BOGUS_ARRAY */
			0x3,		/* 3 */
/* 656 */	NdrFcShort( 0x0 ),	/* 0 */
/* 658 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 660 */	NdrFcShort( 0x0 ),	/* 0 */
/* 662 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 664 */	NdrFcLong( 0xffffffff ),	/* -1 */
/* 668 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 670 */	
			0x12, 0x0,	/* FC_UP */
/* 672 */	NdrFcShort( 0xffda ),	/* Offset= -38 (634) */
/* 674 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 676 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 678 */	NdrFcShort( 0x10 ),	/* 16 */
/* 680 */	NdrFcShort( 0x0 ),	/* 0 */
/* 682 */	NdrFcShort( 0x6 ),	/* Offset= 6 (688) */
/* 684 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 686 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 688 */	
			0x11, 0x0,	/* FC_RP */
/* 690 */	NdrFcShort( 0xffdc ),	/* Offset= -36 (654) */
/* 692 */	
			0x1d,		/* FC_SMFARRAY */
			0x0,		/* 0 */
/* 694 */	NdrFcShort( 0x8 ),	/* 8 */
/* 696 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 698 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 700 */	NdrFcShort( 0x10 ),	/* 16 */
/* 702 */	0x8,		/* FC_LONG */
			0x6,		/* FC_SHORT */
/* 704 */	0x6,		/* FC_SHORT */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 706 */	0x0,		/* 0 */
			NdrFcShort( 0xfff1 ),	/* Offset= -15 (692) */
			0x5b,		/* FC_END */
/* 710 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 712 */	NdrFcShort( 0x20 ),	/* 32 */
/* 714 */	NdrFcShort( 0x0 ),	/* 0 */
/* 716 */	NdrFcShort( 0xa ),	/* Offset= 10 (726) */
/* 718 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 720 */	0x36,		/* FC_POINTER */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 722 */	0x0,		/* 0 */
			NdrFcShort( 0xffe7 ),	/* Offset= -25 (698) */
			0x5b,		/* FC_END */
/* 726 */	
			0x11, 0x0,	/* FC_RP */
/* 728 */	NdrFcShort( 0xff12 ),	/* Offset= -238 (490) */
/* 730 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 732 */	NdrFcShort( 0x1 ),	/* 1 */
/* 734 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 736 */	NdrFcShort( 0x0 ),	/* 0 */
/* 738 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 740 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 742 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 744 */	NdrFcShort( 0x10 ),	/* 16 */
/* 746 */	NdrFcShort( 0x0 ),	/* 0 */
/* 748 */	NdrFcShort( 0x6 ),	/* Offset= 6 (754) */
/* 750 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 752 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 754 */	
			0x12, 0x0,	/* FC_UP */
/* 756 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (730) */
/* 758 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 760 */	NdrFcShort( 0x2 ),	/* 2 */
/* 762 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 764 */	NdrFcShort( 0x0 ),	/* 0 */
/* 766 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 768 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 770 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 772 */	NdrFcShort( 0x10 ),	/* 16 */
/* 774 */	NdrFcShort( 0x0 ),	/* 0 */
/* 776 */	NdrFcShort( 0x6 ),	/* Offset= 6 (782) */
/* 778 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 780 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 782 */	
			0x12, 0x0,	/* FC_UP */
/* 784 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (758) */
/* 786 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 788 */	NdrFcShort( 0x4 ),	/* 4 */
/* 790 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 792 */	NdrFcShort( 0x0 ),	/* 0 */
/* 794 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 796 */	0x8,		/* FC_LONG */
			0x5b,		/* FC_END */
/* 798 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 800 */	NdrFcShort( 0x10 ),	/* 16 */
/* 802 */	NdrFcShort( 0x0 ),	/* 0 */
/* 804 */	NdrFcShort( 0x6 ),	/* Offset= 6 (810) */
/* 806 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 808 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 810 */	
			0x12, 0x0,	/* FC_UP */
/* 812 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (786) */
/* 814 */	
			0x1b,		/* FC_CARRAY */
			0x7,		/* 7 */
/* 816 */	NdrFcShort( 0x8 ),	/* 8 */
/* 818 */	0x19,		/* Corr desc:  field pointer, FC_ULONG */
			0x0,		/*  */
/* 820 */	NdrFcShort( 0x0 ),	/* 0 */
/* 822 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 824 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 826 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 828 */	NdrFcShort( 0x10 ),	/* 16 */
/* 830 */	NdrFcShort( 0x0 ),	/* 0 */
/* 832 */	NdrFcShort( 0x6 ),	/* Offset= 6 (838) */
/* 834 */	0x8,		/* FC_LONG */
			0x40,		/* FC_STRUCTPAD4 */
/* 836 */	0x36,		/* FC_POINTER */
			0x5b,		/* FC_END */
/* 838 */	
			0x12, 0x0,	/* FC_UP */
/* 840 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (814) */
/* 842 */	
			0x15,		/* FC_STRUCT */
			0x3,		/* 3 */
/* 844 */	NdrFcShort( 0x8 ),	/* 8 */
/* 846 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 848 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 850 */	
			0x1b,		/* FC_CARRAY */
			0x3,		/* 3 */
/* 852 */	NdrFcShort( 0x8 ),	/* 8 */
/* 854 */	0x7,		/* Corr desc: FC_USHORT */
			0x0,		/*  */
/* 856 */	NdrFcShort( 0xffc8 ),	/* -56 */
/* 858 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 860 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 862 */	NdrFcShort( 0xffec ),	/* Offset= -20 (842) */
/* 864 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 866 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x3,		/* 3 */
/* 868 */	NdrFcShort( 0x38 ),	/* 56 */
/* 870 */	NdrFcShort( 0xffec ),	/* Offset= -20 (850) */
/* 872 */	NdrFcShort( 0x0 ),	/* Offset= 0 (872) */
/* 874 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 876 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 878 */	0x40,		/* FC_STRUCTPAD4 */
			0x4c,		/* FC_EMBEDDED_COMPLEX */
/* 880 */	0x0,		/* 0 */
			NdrFcShort( 0xfe0f ),	/* Offset= -497 (384) */
			0x5b,		/* FC_END */
/* 884 */	
			0x12, 0x0,	/* FC_UP */
/* 886 */	NdrFcShort( 0xff04 ),	/* Offset= -252 (634) */
/* 888 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 890 */	0x1,		/* FC_BYTE */
			0x5c,		/* FC_PAD */
/* 892 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 894 */	0x6,		/* FC_SHORT */
			0x5c,		/* FC_PAD */
/* 896 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 898 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/* 900 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 902 */	0xb,		/* FC_HYPER */
			0x5c,		/* FC_PAD */
/* 904 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 906 */	0xa,		/* FC_FLOAT */
			0x5c,		/* FC_PAD */
/* 908 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 910 */	0xc,		/* FC_DOUBLE */
			0x5c,		/* FC_PAD */
/* 912 */	
			0x12, 0x0,	/* FC_UP */
/* 914 */	NdrFcShort( 0xfdb4 ),	/* Offset= -588 (326) */
/* 916 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 918 */	NdrFcShort( 0xfdb6 ),	/* Offset= -586 (332) */
/* 920 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 922 */	NdrFcShort( 0xfdcc ),	/* Offset= -564 (358) */
/* 924 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 926 */	NdrFcShort( 0xfc64 ),	/* Offset= -924 (2) */
/* 928 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 930 */	NdrFcShort( 0xfdd6 ),	/* Offset= -554 (376) */
/* 932 */	
			0x12, 0x10,	/* FC_UP [pointer_deref] */
/* 934 */	NdrFcShort( 0x2 ),	/* Offset= 2 (936) */
/* 936 */	
			0x12, 0x0,	/* FC_UP */
/* 938 */	NdrFcShort( 0x14 ),	/* Offset= 20 (958) */
/* 940 */	
			0x15,		/* FC_STRUCT */
			0x7,		/* 7 */
/* 942 */	NdrFcShort( 0x10 ),	/* 16 */
/* 944 */	0x6,		/* FC_SHORT */
			0x1,		/* FC_BYTE */
/* 946 */	0x1,		/* FC_BYTE */
			0x8,		/* FC_LONG */
/* 948 */	0xb,		/* FC_HYPER */
			0x5b,		/* FC_END */
/* 950 */	
			0x12, 0x0,	/* FC_UP */
/* 952 */	NdrFcShort( 0xfff4 ),	/* Offset= -12 (940) */
/* 954 */	
			0x12, 0x8,	/* FC_UP [simple_pointer] */
/* 956 */	0x2,		/* FC_CHAR */
			0x5c,		/* FC_PAD */
/* 958 */	
			0x1a,		/* FC_BOGUS_STRUCT */
			0x7,		/* 7 */
/* 960 */	NdrFcShort( 0x20 ),	/* 32 */
/* 962 */	NdrFcShort( 0x0 ),	/* 0 */
/* 964 */	NdrFcShort( 0x0 ),	/* Offset= 0 (964) */
/* 966 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 968 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 970 */	0x6,		/* FC_SHORT */
			0x6,		/* FC_SHORT */
/* 972 */	0x4c,		/* FC_EMBEDDED_COMPLEX */
			0x0,		/* 0 */
/* 974 */	NdrFcShort( 0xfc4e ),	/* Offset= -946 (28) */
/* 976 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 978 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 980 */	NdrFcShort( 0x0 ),	/* 0 */
/* 982 */	NdrFcShort( 0x18 ),	/* 24 */
/* 984 */	NdrFcShort( 0x0 ),	/* 0 */
/* 986 */	NdrFcShort( 0xfc3e ),	/* Offset= -962 (24) */

			0x0
        }
    };

static const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ] = 
        {
            
            {
            VARIANT_UserSize
            ,VARIANT_UserMarshal
            ,VARIANT_UserUnmarshal
            ,VARIANT_UserFree
            }

        };



/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IDispatch, ver. 0.0,
   GUID={0x00020400,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: ICDHTMLUI, ver. 0.0,
   GUID={0x9F3E85AE,0x09C6,0x4A3A,{0xA7,0x8C,0x69,0x73,0xF8,0xA3,0x28,0xB6}} */

#pragma code_seg(".orpc")
static const unsigned short ICDHTMLUI_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO ICDHTMLUI_ProxyInfo =
    {
    &Object_StubDesc,
    _Ex29c__MIDL_ProcFormatString.Format,
    &ICDHTMLUI_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO ICDHTMLUI_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    _Ex29c__MIDL_ProcFormatString.Format,
    &ICDHTMLUI_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(8) _ICDHTMLUIProxyVtbl = 
{
    &ICDHTMLUI_ProxyInfo,
    &IID_ICDHTMLUI,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* IDispatch::GetTypeInfoCount */ ,
    0 /* IDispatch::GetTypeInfo */ ,
    0 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* ICDHTMLUI::OnClick */
};


static const PRPC_STUB_FUNCTION ICDHTMLUI_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2
};

CInterfaceStubVtbl _ICDHTMLUIStubVtbl =
{
    &IID_ICDHTMLUI,
    &ICDHTMLUI_ServerInfo,
    8,
    &ICDHTMLUI_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: ICDHTML, ver. 0.0,
   GUID={0xC0771F2F,0x6285,0x48EA,{0x93,0x56,0x8A,0xA2,0xA4,0xD8,0xC4,0x7D}} */

#pragma code_seg(".orpc")
static const unsigned short ICDHTML_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO ICDHTML_ProxyInfo =
    {
    &Object_StubDesc,
    _Ex29c__MIDL_ProcFormatString.Format,
    &ICDHTML_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO ICDHTML_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    _Ex29c__MIDL_ProcFormatString.Format,
    &ICDHTML_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(7) _ICDHTMLProxyVtbl = 
{
    0,
    &IID_ICDHTML,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* IDispatch::GetTypeInfoCount */ ,
    0 /* IDispatch::GetTypeInfo */ ,
    0 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */
};


static const PRPC_STUB_FUNCTION ICDHTML_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION
};

CInterfaceStubVtbl _ICDHTMLStubVtbl =
{
    &IID_ICDHTML,
    &ICDHTML_ServerInfo,
    7,
    &ICDHTML_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};

static const MIDL_STUB_DESC Object_StubDesc = 
    {
    0,
    NdrOleAllocate,
    NdrOleFree,
    0,
    0,
    0,
    0,
    0,
    _Ex29c__MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x50002, /* Ndr library version */
    0,
    0x801026e, /* MIDL Version 8.1.622 */
    0,
    UserMarshalRoutines,
    0,  /* notify & notify_flag routine table */
    0x1, /* MIDL flag */
    0, /* cs routines */
    0,   /* proxy/server info */
    0
    };

const CInterfaceProxyVtbl * const __Ex29c_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_ICDHTMLProxyVtbl,
    ( CInterfaceProxyVtbl *) &_ICDHTMLUIProxyVtbl,
    0
};

const CInterfaceStubVtbl * const __Ex29c_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_ICDHTMLStubVtbl,
    ( CInterfaceStubVtbl *) &_ICDHTMLUIStubVtbl,
    0
};

PCInterfaceName const __Ex29c_InterfaceNamesList[] = 
{
    "ICDHTML",
    "ICDHTMLUI",
    0
};

const IID *  const __Ex29c_BaseIIDList[] = 
{
    &IID_IDispatch,
    &IID_IDispatch,
    0
};


#define __Ex29c_CHECK_IID(n)	IID_GENERIC_CHECK_IID( __Ex29c, pIID, n)

int __stdcall __Ex29c_IID_Lookup( const IID * pIID, int * pIndex )
{
    IID_BS_LOOKUP_SETUP

    IID_BS_LOOKUP_INITIAL_TEST( __Ex29c, 2, 1 )
    IID_BS_LOOKUP_RETURN_RESULT( __Ex29c, 2, *pIndex )
    
}

const ExtendedProxyFileInfo _Ex29c_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & __Ex29c_ProxyVtblList,
    (PCInterfaceStubVtblList *) & __Ex29c_StubVtblList,
    (const PCInterfaceName * ) & __Ex29c_InterfaceNamesList,
    (const IID ** ) & __Ex29c_BaseIIDList,
    & __Ex29c_IID_Lookup, 
    2,
    2,
    0, /* table of [async_uuid] interfaces */
    0, /* Filler1 */
    0, /* Filler2 */
    0  /* Filler3 */
};
#if _MSC_VER >= 1200
#pragma warning(pop)
#endif


#endif /* defined(_M_AMD64)*/

