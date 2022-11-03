

/* this ALWAYS GENERATED file contains the proxy stub code */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 11:14:07 2038
 */
/* Compiler settings for _AttributedATLSpaceShipSvr.idl:
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


#include "_AttributedATLSpaceShipSvr.h"

#define TYPE_FORMAT_STRING_SIZE   47                                
#define PROC_FORMAT_STRING_SIZE   147                               
#define EXPR_FORMAT_STRING_SIZE   1                                 
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   1            

typedef struct __AttributedATLSpaceShipSvr_MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } _AttributedATLSpaceShipSvr_MIDL_TYPE_FORMAT_STRING;

typedef struct __AttributedATLSpaceShipSvr_MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } _AttributedATLSpaceShipSvr_MIDL_PROC_FORMAT_STRING;

typedef struct __AttributedATLSpaceShipSvr_MIDL_EXPR_FORMAT_STRING
    {
    long          Pad;
    unsigned char  Format[ EXPR_FORMAT_STRING_SIZE ];
    } _AttributedATLSpaceShipSvr_MIDL_EXPR_FORMAT_STRING;


static const RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};


extern const _AttributedATLSpaceShipSvr_MIDL_TYPE_FORMAT_STRING _AttributedATLSpaceShipSvr__MIDL_TypeFormatString;
extern const _AttributedATLSpaceShipSvr_MIDL_PROC_FORMAT_STRING _AttributedATLSpaceShipSvr__MIDL_ProcFormatString;
extern const _AttributedATLSpaceShipSvr_MIDL_EXPR_FORMAT_STRING _AttributedATLSpaceShipSvr__MIDL_ExprFormatString;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IAttributedATLSpaceShip_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IAttributedATLSpaceShip_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IMotion_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IMotion_ProxyInfo;


extern const MIDL_STUB_DESC Object_StubDesc;


extern const MIDL_SERVER_INFO IVisual_ServerInfo;
extern const MIDL_STUBLESS_PROXY_INFO IVisual_ProxyInfo;


extern const USER_MARSHAL_ROUTINE_QUADRUPLE UserMarshalRoutines[ WIRE_MARSHAL_TABLE_SIZE ];

#if !defined(__RPC_WIN64__)
#error  Invalid build platform for this stub.
#endif

static const _AttributedATLSpaceShipSvr_MIDL_PROC_FORMAT_STRING _AttributedATLSpaceShipSvr__MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure CallStarFleet */

			0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/*  2 */	NdrFcLong( 0x0 ),	/* 0 */
/*  6 */	NdrFcShort( 0x7 ),	/* 7 */
/*  8 */	NdrFcShort( 0x20 ),	/* X64 Stack size/offset = 32 */
/* 10 */	NdrFcShort( 0x8 ),	/* 8 */
/* 12 */	NdrFcShort( 0x8 ),	/* 8 */
/* 14 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x3,		/* 3 */
/* 16 */	0xa,		/* 10 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 18 */	NdrFcShort( 0x1 ),	/* 1 */
/* 20 */	NdrFcShort( 0x0 ),	/* 0 */
/* 22 */	NdrFcShort( 0x0 ),	/* 0 */
/* 24 */	NdrFcShort( 0x4 ),	/* 4 */

	/* Parameter fStarDate */

/* 26 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 28 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 30 */	0xa,		/* FC_FLOAT */
			0x0,		/* 0 */

	/* Parameter pbstrRecipient */

/* 32 */	NdrFcShort( 0x2113 ),	/* Flags:  must size, must free, out, simple ref, srv alloc size=8 */
/* 34 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 36 */	NdrFcShort( 0x20 ),	/* Type Offset=32 */

	/* Return value */

/* 38 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 40 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 42 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Fly */

/* 44 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 46 */	NdrFcLong( 0x0 ),	/* 0 */
/* 50 */	NdrFcShort( 0x7 ),	/* 7 */
/* 52 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 54 */	NdrFcShort( 0x0 ),	/* 0 */
/* 56 */	NdrFcShort( 0x8 ),	/* 8 */
/* 58 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 60 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 62 */	NdrFcShort( 0x0 ),	/* 0 */
/* 64 */	NdrFcShort( 0x0 ),	/* 0 */
/* 66 */	NdrFcShort( 0x0 ),	/* 0 */
/* 68 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 70 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 72 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 74 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure GetPosition */

/* 76 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 78 */	NdrFcLong( 0x0 ),	/* 0 */
/* 82 */	NdrFcShort( 0x8 ),	/* 8 */
/* 84 */	NdrFcShort( 0x18 ),	/* X64 Stack size/offset = 24 */
/* 86 */	NdrFcShort( 0x0 ),	/* 0 */
/* 88 */	NdrFcShort( 0x24 ),	/* 36 */
/* 90 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 92 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 94 */	NdrFcShort( 0x0 ),	/* 0 */
/* 96 */	NdrFcShort( 0x0 ),	/* 0 */
/* 98 */	NdrFcShort( 0x0 ),	/* 0 */
/* 100 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter nPosition */

/* 102 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 104 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 106 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Return value */

/* 108 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 110 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 112 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Procedure Display */

/* 114 */	0x33,		/* FC_AUTO_HANDLE */
			0x6c,		/* Old Flags:  object, Oi2 */
/* 116 */	NdrFcLong( 0x0 ),	/* 0 */
/* 120 */	NdrFcShort( 0x3 ),	/* 3 */
/* 122 */	NdrFcShort( 0x10 ),	/* X64 Stack size/offset = 16 */
/* 124 */	NdrFcShort( 0x0 ),	/* 0 */
/* 126 */	NdrFcShort( 0x8 ),	/* 8 */
/* 128 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 130 */	0xa,		/* 10 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 132 */	NdrFcShort( 0x0 ),	/* 0 */
/* 134 */	NdrFcShort( 0x0 ),	/* 0 */
/* 136 */	NdrFcShort( 0x0 ),	/* 0 */
/* 138 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Return value */

/* 140 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 142 */	NdrFcShort( 0x8 ),	/* X64 Stack size/offset = 8 */
/* 144 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

			0x0
        }
    };

static const _AttributedATLSpaceShipSvr_MIDL_TYPE_FORMAT_STRING _AttributedATLSpaceShipSvr__MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */
/*  2 */	
			0x11, 0x4,	/* FC_RP [alloced_on_stack] */
/*  4 */	NdrFcShort( 0x1c ),	/* Offset= 28 (32) */
/*  6 */	
			0x13, 0x0,	/* FC_OP */
/*  8 */	NdrFcShort( 0xe ),	/* Offset= 14 (22) */
/* 10 */	
			0x1b,		/* FC_CARRAY */
			0x1,		/* 1 */
/* 12 */	NdrFcShort( 0x2 ),	/* 2 */
/* 14 */	0x9,		/* Corr desc: FC_ULONG */
			0x0,		/*  */
/* 16 */	NdrFcShort( 0xfffc ),	/* -4 */
/* 18 */	NdrFcShort( 0x1 ),	/* Corr flags:  early, */
/* 20 */	0x6,		/* FC_SHORT */
			0x5b,		/* FC_END */
/* 22 */	
			0x17,		/* FC_CSTRUCT */
			0x3,		/* 3 */
/* 24 */	NdrFcShort( 0x8 ),	/* 8 */
/* 26 */	NdrFcShort( 0xfff0 ),	/* Offset= -16 (10) */
/* 28 */	0x8,		/* FC_LONG */
			0x8,		/* FC_LONG */
/* 30 */	0x5c,		/* FC_PAD */
			0x5b,		/* FC_END */
/* 32 */	0xb4,		/* FC_USER_MARSHAL */
			0x83,		/* 131 */
/* 34 */	NdrFcShort( 0x0 ),	/* 0 */
/* 36 */	NdrFcShort( 0x8 ),	/* 8 */
/* 38 */	NdrFcShort( 0x0 ),	/* 0 */
/* 40 */	NdrFcShort( 0xffde ),	/* Offset= -34 (6) */
/* 42 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 44 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */

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


/* Object interface: IAttributedATLSpaceShip, ver. 0.0,
   GUID={0x4B8685BD,0x00F1,0x4D38,{0xAF,0xC1,0x30,0x12,0xC7,0x86,0x48,0x0D}} */

#pragma code_seg(".orpc")
static const unsigned short IAttributedATLSpaceShip_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    0
    };

static const MIDL_STUBLESS_PROXY_INFO IAttributedATLSpaceShip_ProxyInfo =
    {
    &Object_StubDesc,
    _AttributedATLSpaceShipSvr__MIDL_ProcFormatString.Format,
    &IAttributedATLSpaceShip_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IAttributedATLSpaceShip_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    _AttributedATLSpaceShipSvr__MIDL_ProcFormatString.Format,
    &IAttributedATLSpaceShip_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
CINTERFACE_PROXY_VTABLE(8) _IAttributedATLSpaceShipProxyVtbl = 
{
    &IAttributedATLSpaceShip_ProxyInfo,
    &IID_IAttributedATLSpaceShip,
    IUnknown_QueryInterface_Proxy,
    IUnknown_AddRef_Proxy,
    IUnknown_Release_Proxy ,
    0 /* IDispatch::GetTypeInfoCount */ ,
    0 /* IDispatch::GetTypeInfo */ ,
    0 /* IDispatch::GetIDsOfNames */ ,
    0 /* IDispatch_Invoke_Proxy */ ,
    (void *) (INT_PTR) -1 /* IAttributedATLSpaceShip::CallStarFleet */
};


static const PRPC_STUB_FUNCTION IAttributedATLSpaceShip_table[] =
{
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    STUB_FORWARDING_FUNCTION,
    NdrStubCall2
};

CInterfaceStubVtbl _IAttributedATLSpaceShipStubVtbl =
{
    &IID_IAttributedATLSpaceShip,
    &IAttributedATLSpaceShip_ServerInfo,
    8,
    &IAttributedATLSpaceShip_table[-3],
    CStdStubBuffer_DELEGATING_METHODS
};


/* Object interface: IMotion, ver. 0.0,
   GUID={0x692D03A4,0xC689,0x11CE,{0xB3,0x37,0x88,0xEA,0x36,0xDE,0x9E,0x4E}} */

#pragma code_seg(".orpc")
static const unsigned short IMotion_FormatStringOffsetTable[] =
    {
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    (unsigned short) -1,
    44,
    76
    };

static const MIDL_STUBLESS_PROXY_INFO IMotion_ProxyInfo =
    {
    &Object_StubDesc,
    _AttributedATLSpaceShipSvr__MIDL_ProcFormatString.Format,
    &IMotion_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IMotion_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    _AttributedATLSpaceShipSvr__MIDL_ProcFormatString.Format,
    &IMotion_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
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
    NdrStubCall2,
    NdrStubCall2
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
static const unsigned short IVisual_FormatStringOffsetTable[] =
    {
    114
    };

static const MIDL_STUBLESS_PROXY_INFO IVisual_ProxyInfo =
    {
    &Object_StubDesc,
    _AttributedATLSpaceShipSvr__MIDL_ProcFormatString.Format,
    &IVisual_FormatStringOffsetTable[-3],
    0,
    0,
    0
    };


static const MIDL_SERVER_INFO IVisual_ServerInfo = 
    {
    &Object_StubDesc,
    0,
    _AttributedATLSpaceShipSvr__MIDL_ProcFormatString.Format,
    &IVisual_FormatStringOffsetTable[-3],
    0,
    0,
    0,
    0};
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
    _AttributedATLSpaceShipSvr__MIDL_TypeFormatString.Format,
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

const CInterfaceProxyVtbl * const __AttributedATLSpaceShipSvr_ProxyVtblList[] = 
{
    ( CInterfaceProxyVtbl *) &_IMotionProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IVisualProxyVtbl,
    ( CInterfaceProxyVtbl *) &_IAttributedATLSpaceShipProxyVtbl,
    0
};

const CInterfaceStubVtbl * const __AttributedATLSpaceShipSvr_StubVtblList[] = 
{
    ( CInterfaceStubVtbl *) &_IMotionStubVtbl,
    ( CInterfaceStubVtbl *) &_IVisualStubVtbl,
    ( CInterfaceStubVtbl *) &_IAttributedATLSpaceShipStubVtbl,
    0
};

PCInterfaceName const __AttributedATLSpaceShipSvr_InterfaceNamesList[] = 
{
    "IMotion",
    "IVisual",
    "IAttributedATLSpaceShip",
    0
};

const IID *  const __AttributedATLSpaceShipSvr_BaseIIDList[] = 
{
    &IID_IDispatch,
    0,
    &IID_IDispatch,
    0
};


#define __AttributedATLSpaceShipSvr_CHECK_IID(n)	IID_GENERIC_CHECK_IID( __AttributedATLSpaceShipSvr, pIID, n)

int __stdcall __AttributedATLSpaceShipSvr_IID_Lookup( const IID * pIID, int * pIndex )
{
    IID_BS_LOOKUP_SETUP

    IID_BS_LOOKUP_INITIAL_TEST( __AttributedATLSpaceShipSvr, 3, 2 )
    IID_BS_LOOKUP_NEXT_TEST( __AttributedATLSpaceShipSvr, 1 )
    IID_BS_LOOKUP_RETURN_RESULT( __AttributedATLSpaceShipSvr, 3, *pIndex )
    
}

const ExtendedProxyFileInfo _AttributedATLSpaceShipSvr_ProxyFileInfo = 
{
    (PCInterfaceProxyVtblList *) & __AttributedATLSpaceShipSvr_ProxyVtblList,
    (PCInterfaceStubVtblList *) & __AttributedATLSpaceShipSvr_StubVtblList,
    (const PCInterfaceName * ) & __AttributedATLSpaceShipSvr_InterfaceNamesList,
    (const IID ** ) & __AttributedATLSpaceShipSvr_BaseIIDList,
    & __AttributedATLSpaceShipSvr_IID_Lookup, 
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

