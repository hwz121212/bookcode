

/* this ALWAYS GENERATED file contains the proxy stub code */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 11:14:07 2038
 */
/* Compiler settings for ATLSpaceShipSvr.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.01.0622 
    protocol : all , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#if defined(_M_AMD64)


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
#include "ndr64types.h"
#ifndef __RPCPROXY_H_VERSION__
#error this stub requires an updated version of <rpcproxy.h>
#endif /* __RPCPROXY_H_VERSION__ */


#include "ATLSpaceShipSvr_h.h"

#define TYPE_FORMAT_STRING_SIZE   57                                
#define PROC_FORMAT_STRING_SIZE   147                               
#define EXPR_FORMAT_STRING_SIZE   1                                 
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   1            

typedef struct _ATLSpaceShipSvr_MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } ATLSpaceShipSvr_MIDL_TYPE_FORMAT_STRING;

typedef struct _ATLSpaceShipSvr_MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } ATLSpaceShipSvr_MIDL_PROC_FORMAT_STRING;

typedef struct _ATLSpaceShipSvr_MIDL_EXPR_FORMAT_STRING
    {
    long          Pad;
    unsigned char  Format[ EXPR_FORMAT_STRING_SIZE ];
    } ATLSpaceShipSvr_MIDL_EXPR_FORMAT_STRING;


static const RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};

static const RPC_SYNTAX_IDENTIFIER  _NDR64_RpcTransferSyntax = 
{{0x71710533,0xbeba,0x4937,{0x83,0x19,0xb5,0xdb,0xef,0x9c,0xcc,0x36}},{1,0}};



extern const ATLSpaceShipSvr_MIDL_TYPE_FORMAT_STRING ATLSpaceShipSvr__MIDL_TypeFormatString;
extern const ATLSpaceShipSvr_MIDL_PROC_FORMAT_STRING ATLSpaceShipSvr__MIDL_ProcFormatString;
extern const ATLSpaceShipSvr_MIDL_EXPR_FORMAT_STRING ATLSpaceShipSvr__MIDL_ExprFormatString;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IMotion_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IMotion_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IVisual_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IVisual_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IClassicATLSpaceship_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IClassicATLSpaceship_ProxyInfo;


extern const USER_MARSHAL_ROUTINE_QUADRUPLE NDR64_UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ];
extern const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ];

#if !defined(__RPC_WIN64__)
#error  Invalid build platform for this stub.
#endif

static const ATLSpaceShipSvr_MIDL_PROC_FORMAT_STRING ATLSpaceShipSvr__MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure Fly */

			0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/*  2 */	NdrFcLong( 0x0 ),	/* 0 */
/*  6 */	NdrFcShort( 0x7 ),	/* 7 */
/*  8 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 10 */	NdrFcShort( 0x0 ),	/* 0 */
/* 12 */	NdrFcShort( 0x8 ),	/* 8 */
/* 14 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 16 */	0xa,		/* 10 */
			0x41,		/* Ext Flags:  new corr desc, has range on conformance */
/* 18 */	NdrFcShort( 0x0 ),	/* 0 */
/* 20 */	NdrFcShort( 0x0 ),	/* 0 */
/* 22 */	NdrFcShort( 0x0 ),	/* 0 */
/* 24 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 26 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 28 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 30 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetPosition */

/* 32 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 34 */	NdrFcLong( 0x0 ),	/* 0 */
/* 38 */	NdrFcShort( 0x8 ),	/* 8 */
/* 40 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 42 */	NdrFcShort( 0x0 ),	/* 0 */
/* 44 */	NdrFcShort( 0x24 ),	/* 36 */
/* 46 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 48 */	0xa,		/* 10 */
			0x41,		/* Ext Flags:  new corr desc, has range on conformance */
/* 50 */	NdrFcShort( 0x0 ),	/* 0 */
/* 52 */	NdrFcShort( 0x0 ),	/* 0 */
/* 54 */	NdrFcShort( 0x0 ),	/* 0 */
/* 56 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter nPosition */

/* 58 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 60 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 62 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 64 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 66 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 68 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Display */

/* 70 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 72 */	NdrFcLong( 0x0 ),	/* 0 */
/* 76 */	NdrFcShort( 0x3 ),	/* 3 */
/* 78 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 80 */	NdrFcShort( 0x0 ),	/* 0 */
/* 82 */	NdrFcShort( 0x8 ),	/* 8 */
/* 84 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 86 */	0xa,		/* 10 */
			0x41,		/* Ext Flags:  new corr desc, has range on conformance */
/* 88 */	NdrFcShort( 0x0 ),	/* 0 */
/* 90 */	NdrFcShort( 0x0 ),	/* 0 */
/* 92 */	NdrFcShort( 0x0 ),	/* 0 */
/* 94 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 96 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 98 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 100 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure CallStarFleet */

/* 102 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 104 */	NdrFcLong( 0x0 ),	/* 0 */
/* 108 */	NdrFcShort( 0x7 ),	/* 7 */
/* 110 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 112 */	NdrFcShort( 0x8 ),	/* 8 */
/* 114 */	NdrFcShort( 0x8 ),	/* 8 */
/* 116 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 118 */	0xa,		/* 10 */
			0x43,		/* Ext Flags:  new corr desc, clt corr check, has range on conformance */
/* 120 */	NdrFcShort( 0x1 ),	/* 1 */
/* 122 */	NdrFcShort( 0x0 ),	/* 0 */
/* 124 */	NdrFcShort( 0x0 ),	/* 0 */
/* 126 */	NdrFcShort( 0x4 ),	/* 4 */

	/* Parameter fStarDate */

/* 128 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 130 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 132 */	0xa,		/* FC_FLOAT */
			0x0,		/* 0 */

	/* Parameter pbstRecipient */

/* 134 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 136 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 138 */	NdrFcShort( 0x2e ),	/* Type Offset=46 */

	/* Return value */

/* 140 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 142 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 144 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const ATLSpaceShipSvr_MIDL_TYPE_FORMAT_STRING ATLSpaceShipSvr__MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */
/*  2 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/*  4 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */
/*  6 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/*  8 */	NdrFcShort( 0x26 ),	/* Offset= 38 (46) */
/* 10 */	
			0x13, 0x0,	/* FC_OP */
/* 12 */	NdrFcShort( 0x18 ),	/* Offset= 24 (36) */
/* 14 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 16 */	NdrFcShort( 0x2 ),	/* 2 */
/* 18 */	0x9,		/* Corr desc: FC_ULONG */
			0x0,		/*  */
/* 20 */	NdrFcShort( 0xfffc ),	/* -4 */
/* 22 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 24 */	0x0 , 
			0x0,		/* 0 */
/* 26 */	NdrFcLong( 0x0 ),	/* 0 */
/* 30 */	NdrFcLong( 0x0 ),	/* 0 */
/* 34 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 36 */	
			0x17,		/* FC_CSTRUCT */
			0x3,		/* 3 */
/* 38 */	NdrFcShort( 0x8 ),	/* 8 */
/* 40 */	NdrFcShort( 0xffe6 ),	/* Offset= -26 (14) */
/* 42 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 44 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 46 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 48 */	NdrFcShort( 0x0 ),	/* 0 */
/* 50 */	NdrFcShort( 0x8 ),	/* 8 */
/* 52 */	NdrFcShort( 0x0 ),	/* 0 */
/* 54 */	NdrFcShort( 0xffd4 ),	/* Offset= -44 (10) */

			0x0
        }
    };

static const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ] = 
        {
            
            {
            BSTR_UserSize
            ,BSTR_UserMarshal
            ,BSTR_UserUnmarshal
            ,BSTR_UserFree
            }

        };



/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IDispatch, ver. 0.0,
   GUID={0x00020400,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IMotion, ver. 0.0,
   GUID={0x692D03A4,0xC689,0x11CE,{0xB3,0x37,0x88,0xEA,0x36,0xDE,0x9E,0x4E}} */

#pragma code_seg(".orpc")
static const unsigned short IMotion_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    0,
    32
    };



/* Object interface: IVisual, ver. 0.0,
   GUID={0x692D03A5,0xC689,0x11CE,{0xB3,0x37,0x88,0xEA,0x36,0xDE,0x9E,0x4E}} */

#pragma code_seg(".orpc")
static const unsigned short IVisual_FormatStringOffsetTable[] =
    {
    70
    };



/* Object interface: IClassicATLSpaceship, ver. 0.0,
   GUID={0x45896187,0x46FF,0x4A07,{0xA9,0xDC,0x55,0x73,0x77,0x38,0x05,0x35}} */

#pragma code_seg(".orpc")
static const unsigned short IClassicATLSpaceship_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    102
    };



#endif /* defined(_M_AMD64)*/



/* this ALWAYS GENERATED file contains the proxy stub code */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 11:14:07 2038
 */
/* Compiler settings for ATLSpaceShipSvr.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.01.0622 
    protocol : all , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#if defined(_M_AMD64)



extern const USER_MARSHAL_ROUTINE_QUADRUPLE NDR64_UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ];
extern const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ];

#if !defined(__RPC_WIN64__)
#error  Invalid build platform for this stub.
#endif


#include "ndr64types.h"
#include "pshpack8.h"


typedef 
NDR64_FORMAT_CHAR
__midl_frag19_t;
extern const __midl_frag19_t __midl_frag19;

typedef 
NDR64_FORMAT_CHAR
__midl_frag18_t;
extern const __midl_frag18_t __midl_frag18;

typedef 
struct 
{
    NDR64_FORMAT_UINT32 frag1;
    struct _NDR64_EXPR_VAR frag2;
}
__midl_frag17_t;
extern const __midl_frag17_t __midl_frag17;

typedef 
struct 
{
    struct _NDR64_CONF_ARRAY_HEADER_FORMAT frag1;
    struct _NDR64_ARRAY_ELEMENT_INFO frag2;
}
__midl_frag16_t;
extern const __midl_frag16_t __midl_frag16;

typedef 
struct 
{
    struct _NDR64_CONF_STRUCTURE_HEADER_FORMAT frag1;
}
__midl_frag15_t;
extern const __midl_frag15_t __midl_frag15;

typedef 
struct _NDR64_POINTER_FORMAT
__midl_frag14_t;
extern const __midl_frag14_t __midl_frag14;

typedef 
struct _NDR64_USER_MARSHAL_FORMAT
__midl_frag13_t;
extern const __midl_frag13_t __midl_frag13;

typedef 
struct _NDR64_POINTER_FORMAT
__midl_frag12_t;
extern const __midl_frag12_t __midl_frag12;

typedef 
NDR64_FORMAT_CHAR
__midl_frag11_t;
extern const __midl_frag11_t __midl_frag11;

typedef 
struct 
{
    struct _NDR64_PROC_FORMAT frag1;
    struct _NDR64_PARAM_FORMAT frag2;
    struct _NDR64_PARAM_FORMAT frag3;
    struct _NDR64_PARAM_FORMAT frag4;
}
__midl_frag10_t;
extern const __midl_frag10_t __midl_frag10;

typedef 
struct 
{
    struct _NDR64_PROC_FORMAT frag1;
    struct _NDR64_PARAM_FORMAT frag2;
}
__midl_frag8_t;
extern const __midl_frag8_t __midl_frag8;

typedef 
struct _NDR64_POINTER_FORMAT
__midl_frag5_t;
extern const __midl_frag5_t __midl_frag5;

typedef 
struct 
{
    struct _NDR64_PROC_FORMAT frag1;
    struct _NDR64_PARAM_FORMAT frag2;
    struct _NDR64_PARAM_FORMAT frag3;
}
__midl_frag4_t;
extern const __midl_frag4_t __midl_frag4;

typedef 
NDR64_FORMAT_UINT32
__midl_frag1_t;
extern const __midl_frag1_t __midl_frag1;

static const __midl_frag19_t __midl_frag19 =
0x5    /* FC64_INT32 */;

static const __midl_frag18_t __midl_frag18 =
0x4    /* FC64_INT16 */;

static const __midl_frag17_t __midl_frag17 =
{ 
/*  */
    (NDR64_UINT32) 1 /* 0x1 */,
    { 
    /* struct _NDR64_EXPR_VAR */
        0x3,    /* FC_EXPR_VAR */
        0x6,    /* FC64_UINT32 */
        (NDR64_UINT16) 0 /* 0x0 */,
        (NDR64_UINT32) 4 /* 0x4 */
    }
};

static const __midl_frag16_t __midl_frag16 =
{ 
/*  */
    { 
    /* struct _NDR64_CONF_ARRAY_HEADER_FORMAT */
        0x41,    /* FC64_CONF_ARRAY */
        (NDR64_UINT8) 1 /* 0x1 */,
        { 
        /* struct _NDR64_CONF_ARRAY_HEADER_FORMAT */
            0,
            0,
            0,
            0,
            0,
            0,
            0,
            0
        },
        (NDR64_UINT8) 0 /* 0x0 */,
        (NDR64_UINT32) 2 /* 0x2 */,
        &__midl_frag17
    },
    { 
    /* struct _NDR64_ARRAY_ELEMENT_INFO */
        (NDR64_UINT32) 2 /* 0x2 */,
        &__midl_frag18
    }
};

static const __midl_frag15_t __midl_frag15 =
{ 
/* FLAGGED_WORD_BLOB */
    { 
    /* FLAGGED_WORD_BLOB */
        0x32,    /* FC64_CONF_STRUCT */
        (NDR64_UINT8) 3 /* 0x3 */,
        { 
        /* FLAGGED_WORD_BLOB */
            0,
            0,
            1,
            0,
            0,
            0,
            0,
            0
        },
        (NDR64_UINT8) 0 /* 0x0 */,
        (NDR64_UINT32) 8 /* 0x8 */,
        &__midl_frag16
    }
};

static const __midl_frag14_t __midl_frag14 =
{ 
/* *FLAGGED_WORD_BLOB */
    0x22,    /* FC64_OP */
    (NDR64_UINT8) 0 /* 0x0 */,
    (NDR64_UINT16) 0 /* 0x0 */,
    &__midl_frag15
};

static const __midl_frag13_t __midl_frag13 =
{ 
/* wireBSTR */
    0xa2,    /* FC64_USER_MARSHAL */
    (NDR64_UINT8) 128 /* 0x80 */,
    (NDR64_UINT16) 0 /* 0x0 */,
    (NDR64_UINT16) 7 /* 0x7 */,
    (NDR64_UINT16) 8 /* 0x8 */,
    (NDR64_UINT32) 8 /* 0x8 */,
    (NDR64_UINT32) 0 /* 0x0 */,
    &__midl_frag14
};

static const __midl_frag12_t __midl_frag12 =
{ 
/* *wireBSTR */
    0x20,    /* FC64_RP */
    (NDR64_UINT8) 4 /* 0x4 */,
    (NDR64_UINT16) 0 /* 0x0 */,
    &__midl_frag13
};

static const __midl_frag11_t __midl_frag11 =
0xb    /* FC64_FLOAT32 */;

static const __midl_frag10_t __midl_frag10 =
{ 
/* CallStarFleet */
    { 
    /* CallStarFleet */      /* procedure CallStarFleet */
        (NDR64_UINT32) 4849987 /* 0x4a0143 */,    /* auto handle */ /* IsIntrepreted, [object], ServerMustSize, HasReturn, ClientCorrelation */
        (NDR64_UINT32) 32 /* 0x20 */ ,  /* Stack size */
        (NDR64_UINT32) 8 /* 0x8 */,
        (NDR64_UINT32) 8 /* 0x8 */,
        (NDR64_UINT16) 0 /* 0x0 */,
        (NDR64_UINT16) 4 /* 0x4 */,
        (NDR64_UINT16) 3 /* 0x3 */,
        (NDR64_UINT16) 0 /* 0x0 */
    },
    { 
    /* fStarDate */      /* parameter fStarDate */
        &__midl_frag11,
        { 
        /* fStarDate */
            0,
            0,
            0,
            1,
            0,
            0,
            1,
            1,
            0,
            0,
            0,
            0,
            0,
            (NDR64_UINT16) 0 /* 0x0 */,
            0
        },    /* [in], Basetype, ByValue */
        (NDR64_UINT16) 0 /* 0x0 */,
        8 /* 0x8 */,   /* Stack offset */
    },
    { 
    /* pbstRecipient */      /* parameter pbstRecipient */
        &__midl_frag13,
        { 
        /* pbstRecipient */
            1,
            1,
            0,
            0,
            1,
            0,
            0,
            0,
            1,
            0,
            0,
            0,
            0,
            (NDR64_UINT16) 0 /* 0x0 */,
            1
        },    /* MustSize, MustFree, [out], SimpleRef, UseCache */
        (NDR64_UINT16) 0 /* 0x0 */,
        16 /* 0x10 */,   /* Stack offset */
    },
    { 
    /* HRESULT */      /* parameter HRESULT */
        &__midl_frag19,
        { 
        /* HRESULT */
            0,
            0,
            0,
            0,
            1,
            1,
            1,
            1,
            0,
            0,
            0,
            0,
            0,
            (NDR64_UINT16) 0 /* 0x0 */,
            0
        },    /* [out], IsReturn, Basetype, ByValue */
        (NDR64_UINT16) 0 /* 0x0 */,
        24 /* 0x18 */,   /* Stack offset */
    }
};

static const __midl_frag8_t __midl_frag8 =
{ 
/* Display */
    { 
    /* Display */      /* procedure Display */
        (NDR64_UINT32) 524611 /* 0x80143 */,    /* auto handle */ /* IsIntrepreted, [object], HasReturn */
        (NDR64_UINT32) 16 /* 0x10 */ ,  /* Stack size */
        (NDR64_UINT32) 0 /* 0x0 */,
        (NDR64_UINT32) 8 /* 0x8 */,
        (NDR64_UINT16) 0 /* 0x0 */,
        (NDR64_UINT16) 0 /* 0x0 */,
        (NDR64_UINT16) 1 /* 0x1 */,
        (NDR64_UINT16) 0 /* 0x0 */
    },
    { 
    /* HRESULT */      /* parameter HRESULT */
        &__midl_frag19,
        { 
        /* HRESULT */
            0,
            0,
            0,
            0,
            1,
            1,
            1,
            1,
            0,
            0,
            0,
            0,
            0,
            (NDR64_UINT16) 0 /* 0x0 */,
            0
        },    /* [out], IsReturn, Basetype, ByValue */
        (NDR64_UINT16) 0 /* 0x0 */,
        8 /* 0x8 */,   /* Stack offset */
    }
};

static const __midl_frag5_t __midl_frag5 =
{ 
/* *long */
    0x20,    /* FC64_RP */
    (NDR64_UINT8) 12 /* 0xc */,
    (NDR64_UINT16) 0 /* 0x0 */,
    &__midl_frag19
};

static const __midl_frag4_t __midl_frag4 =
{ 
/* GetPosition */
    { 
    /* GetPosition */      /* procedure GetPosition */
        (NDR64_UINT32) 524611 /* 0x80143 */,    /* auto handle */ /* IsIntrepreted, [object], HasReturn */
        (NDR64_UINT32) 24 /* 0x18 */ ,  /* Stack size */
        (NDR64_UINT32) 0 /* 0x0 */,
        (NDR64_UINT32) 40 /* 0x28 */,
        (NDR64_UINT16) 0 /* 0x0 */,
        (NDR64_UINT16) 0 /* 0x0 */,
        (NDR64_UINT16) 2 /* 0x2 */,
        (NDR64_UINT16) 0 /* 0x0 */
    },
    { 
    /* nPosition */      /* parameter nPosition */
        &__midl_frag19,
        { 
        /* nPosition */
            0,
            0,
            0,
            0,
            1,
            0,
            1,
            0,
            1,
            0,
            0,
            0,
            0,
            (NDR64_UINT16) 0 /* 0x0 */,
            1
        },    /* [out], Basetype, SimpleRef, UseCache */
        (NDR64_UINT16) 0 /* 0x0 */,
        8 /* 0x8 */,   /* Stack offset */
    },
    { 
    /* HRESULT */      /* parameter HRESULT */
        &__midl_frag19,
        { 
        /* HRESULT */
            0,
            0,
            0,
            0,
            1,
            1,
            1,
            1,
            0,
            0,
            0,
            0,
            0,
            (NDR64_UINT16) 0 /* 0x0 */,
            0
        },    /* [out], IsReturn, Basetype, ByValue */
        (NDR64_UINT16) 0 /* 0x0 */,
        16 /* 0x10 */,   /* Stack offset */
    }
};

static const __midl_frag1_t __midl_frag1 =
(NDR64_UINT32) 0 /* 0x0 */;


#include "poppack.h"


static const USER_MARSHAL_ROUTINE_QUADRUPLE NDR64_UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ] = 
        {
            
            {
            BSTR_UserSize64
            ,BSTR_UserMarshal64
            ,BSTR_UserUnmarshal64
            ,BSTR_UserFree64
            }

        };



/* Object interface: IUnknown, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IDispatch, ver. 0.0,
   GUID={0x00020400,0x0000,0x0000,{0xC0,0x00,0x00,0x00,0x00,0x00,0x00,0x46}} */


/* Object interface: IMotion, ver. 0.0,
   GUID={0x692D03A4,0xC689,0x11CE,{0xB3,0x37,0x88,0xEA,0x36,0xDE,0x9E,0x4E}} */

#pragma code_seg(".orpc")
static const FormatInfoRef IMotion_Ndr64ProcTable[] =
    {
    (FormatInfoRef)(LONG_PTR) -1,
    (FormatInfoRef)(LONG_PTR) -1,
    (FormatInfoRef)(LONG_PTR) -1,
    (FormatInfoRef)(LONG_PTR) -1,
    &__midl_frag8,
    &__midl_frag4
    };


static const MIDL_SYNTAX_INFO IMotion_SyntaxInfo [  2 ] = 
    {
    {
    {{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}},
    0,
    ATLSpaceShipSvr__MIDL_ProcFormatString.Format,
    &IMotion_FormatStringOffsetTable[-3],
    ATLSpaceShipSvr__MIDL_TypeFormatString.Format,
    UserMarshalRoutines,
    0,
    0
    }
    ,{
    {{0x71710533,0xbeba,0x4937,{0x83,0x19,0xb5,0xdb,0xef,0x9c,0xcc,0x36}},{1,0}},
    0,
    0 ,
    (unsigned short *) &IMotion_Ndr64ProcTable[-3],
    0,
    NDR64_UserMarshalRoutines,
    0,
    0
    }
    };

static const MIDL_STUBLESS_PROXY_INFO IMotion_ProxyInfo =
    {
    &Object_StubDesc,
    ATLSpaceShipSvr__MIDL_ProcFormatString.Format,
    &IMotion_FormatStringOffsetTable[-3],
    (RPC_SYNTAX_IDENTIFIER*)&_RpcTransferSyntax,
    2,
    (MIDL_SYNTAX_INFO*)IMotion_SyntaxInfo
    
    };


static const MIDL_SERVER_INFO IMotion_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    ATLSpaceShipSvr__MIDL_ProcFormatString.Format,
    (unsigned short *) &IMotion_FormatStringOffsetTable[-3],
    0,
    (RPC_SYNTAX_IDENTIFIER*)&_NDR64_RpcTransferSyntax,
    2,
    (MIDL_SYNTAX_INFO*)IMotion_SyntaxInfo
    };
CINTERFACE_PROXY_VTABLE(9) _IMotionProxyVtbl = 
{
    &IMotion_ProxyInfo,
    &IID_IMotion,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* IDispatch::GetTypeInfoCount */ ,
    0 /* IDispatch::GetTypeInfo */ ,
    0 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IMotion::Fly */ ,
    (void *) (INT_PTR) -1 /* IMotion::GetPosition */
};


static const PRPC_STUB_FUNCTION IMotion_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall3,
    NdrStubCall3
};

CInterfaceStubVtbl _IMotionStubVtbl =
{
    &IID_IMotion,
    &IMotion_ServerInfo,
    9,
    &IMotion_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IVisual, ver. 0.0,
   GUID={0x692D03A5,0xC689,0x11CE,{0xB3,0x37,0x88,0xEA,0x36,0xDE,0x9E,0x4E}} */

#pragma code_seg(".orpc")
static const FormatInfoRef IVisual_Ndr64ProcTable[] =
    {
    &__midl_frag8
    };


static const MIDL_SYNTAX_INFO IVisual_SyntaxInfo [  2 ] = 
    {
    {
    {{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}},
    0,
    ATLSpaceShipSvr__MIDL_ProcFormatString.Format,
    &IVisual_FormatStringOffsetTable[-3],
    ATLSpaceShipSvr__MIDL_TypeFormatString.Format,
    UserMarshalRoutines,
    0,
    0
    }
    ,{
    {{0x71710533,0xbeba,0x4937,{0x83,0x19,0xb5,0xdb,0xef,0x9c,0xcc,0x36}},{1,0}},
    0,
    0 ,
    (unsigned short *) &IVisual_Ndr64ProcTable[-3],
    0,
    NDR64_UserMarshalRoutines,
    0,
    0
    }
    };

static const MIDL_STUBLESS_PROXY_INFO IVisual_ProxyInfo =
    {
    &Object_StubDesc,
    ATLSpaceShipSvr__MIDL_ProcFormatString.Format,
    &IVisual_FormatStringOffsetTable[-3],
    (RPC_SYNTAX_IDENTIFIER*)&_RpcTransferSyntax,
    2,
    (MIDL_SYNTAX_INFO*)IVisual_SyntaxInfo
    
    };


static const MIDL_SERVER_INFO IVisual_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    ATLSpaceShipSvr__MIDL_ProcFormatString.Format,
    (unsigned short *) &IVisual_FormatStringOffsetTable[-3],
    0,
    (RPC_SYNTAX_IDENTIFIER*)&_NDR64_RpcTransferSyntax,
    2,
    (MIDL_SYNTAX_INFO*)IVisual_SyntaxInfo
    };
CINTERFACE_PROXY_VTABLE(4) _IVisualProxyVtbl = 
{
    &IVisual_ProxyInfo,
    &IID_IVisual,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    (void *) (INT_PTR) -1 /* IVisual::Display */
};

const CInterfaceStubVtbl _IVisualStubVtbl =
{
    &IID_IVisual,
    &IVisual_ServerInfo,
    4,
    0, /* pure interpreted */
    CStdStubBuffer_METHODS
};


/* Object interface: IClassicATLSpaceship, ver. 0.0,
   GUID={0x45896187,0x46FF,0x4A07,{0xA9,0xDC,0x55,0x73,0x77,0x38,0x05,0x35}} */

#pragma code_seg(".orpc")
static const FormatInfoRef IClassicATLSpaceship_Ndr64ProcTable[] =
    {
    (FormatInfoRef)(LONG_PTR) -1,
    (FormatInfoRef)(LONG_PTR) -1,
    (FormatInfoRef)(LONG_PTR) -1,
    (FormatInfoRef)(LONG_PTR) -1,
    &__midl_frag10
    };


static const MIDL_SYNTAX_INFO IClassicATLSpaceship_SyntaxInfo [  2 ] = 
    {
    {
    {{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}},
    0,
    ATLSpaceShipSvr__MIDL_ProcFormatString.Format,
    &IClassicATLSpaceship_FormatStringOffsetTable[-3],
    ATLSpaceShipSvr__MIDL_TypeFormatString.Format,
    UserMarshalRoutines,
    0,
    0
    }
    ,{
    {{0x71710533,0xbeba,0x4937,{0x83,0x19,0xb5,0xdb,0xef,0x9c,0xcc,0x36}},{1,0}},
    0,
    0 ,
    (unsigned short *) &IClassicATLSpaceship_Ndr64ProcTable[-3],
    0,
    NDR64_UserMarshalRoutines,
    0,
    0
    }
    };

static const MIDL_STUBLESS_PROXY_INFO IClassicATLSpaceship_ProxyInfo =
    {
    &Object_StubDesc,
    ATLSpaceShipSvr__MIDL_ProcFormatString.Format,
    &IClassicATLSpaceship_FormatStringOffsetTable[-3],
    (RPC_SYNTAX_IDENTIFIER*)&_RpcTransferSyntax,
    2,
    (MIDL_SYNTAX_INFO*)IClassicATLSpaceship_SyntaxInfo
    
    };


static const MIDL_SERVER_INFO IClassicATLSpaceship_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    ATLSpaceShipSvr__MIDL_ProcFormatString.Format,
    (unsigned short *) &IClassicATLSpaceship_FormatStringOffsetTable[-3],
    0,
    (RPC_SYNTAX_IDENTIFIER*)&_NDR64_RpcTransferSyntax,
    2,
    (MIDL_SYNTAX_INFO*)IClassicATLSpaceship_SyntaxInfo
    };
CINTERFACE_PROXY_VTABLE(8) _IClassicATLSpaceshipProxyVtbl = 
{
    &IClassicATLSpaceship_ProxyInfo,
    &IID_IClassicATLSpaceship,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* IDispatch::GetTypeInfoCount */ ,
    0 /* IDispatch::GetTypeInfo */ ,
    0 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IClassicATLSpaceship::CallStarFleet */
};


static const PRPC_STUB_FUNCTION IClassicATLSpaceship_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall3
};

CInterfaceStubVtbl _IClassicATLSpaceshipStubVtbl =
{
    &IID_IClassicATLSpaceship,
    &IClassicATLSpaceship_ServerInfo,
    8,
    &IClassicATLSpaceship_table[-3],
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
    ATLSpaceShipSvr__MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x60001, /* Ndr library version */
    0,
    0x801026e, /* MIDL Version 8.1.622 */
    0,
    UserMarshalRoutines,
    0,  /* notify & notify_flag routine table */
    0x2000001, /* MIDL flag */
    0, /* cs routines */
    0,   /* proxy/server info */
    0
    };

const CInterfaceProxyVtbl * const _ATLSpaceShipSvr_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_IClassicATLSpaceshipProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IMotionProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IVisualProxyVtbl,
    0
};

const CInterfaceStubVtbl * const _ATLSpaceShipSvr_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_IClassicATLSpaceshipStubVtbl,
    ( CInterfaceStubVtbl *) &_IMotionStubVtbl,
    ( CInterfaceStubVtbl *) &_IVisualStubVtbl,
    0
};

PCInterfaceName const _ATLSpaceShipSvr_InterfaceNamesList[] = 
{
    "IClassicATLSpaceship",
    "IMotion",
    "IVisual",
    0
};

const IID *  const _ATLSpaceShipSvr_BaseIIDList[] = 
{
    &IID_IDispatch,
    &IID_IDispatch,
    0,
    0
};


#define _ATLSpaceShipSvr_CHECK_IID(n)	IID_GENERIC_CHECK_IID( _ATLSpaceShipSvr, pIID, n)

int __stdcall _ATLSpaceShipSvr_IID_Lookup( const IID * pIID, int * pIndex )
{
    IID_BS_LOOKUP_SETUP

    IID_BS_LOOKUP_INITIAL_TEST( _ATLSpaceShipSvr, 3, 2 )
    IID_BS_LOOKUP_NEXT_TEST( _ATLSpaceShipSvr, 1 )
    IID_BS_LOOKUP_RETURN_RESULT( _ATLSpaceShipSvr, 3, *pIndex )
    
}

const ExtendedProxyFileInfo ATLSpaceShipSvr_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & _ATLSpaceShipSvr_ProxyVtblList,
    (PCInterfaceStubVtblList *) & _ATLSpaceShipSvr_StubVtblList,
    (const PCInterfaceName * ) & _ATLSpaceShipSvr_InterfaceNamesList,
    (const IID ** ) & _ATLSpaceShipSvr_BaseIIDList,
    & _ATLSpaceShipSvr_IID_Lookup, 
    3,
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

