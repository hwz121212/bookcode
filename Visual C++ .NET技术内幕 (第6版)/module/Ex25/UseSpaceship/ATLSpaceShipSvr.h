
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Mon Apr 08 03:57:56 2002
 */
/* Compiler settings for ATLSpaceShipSvr.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __ATLSpaceShipSvr_h__
#define __ATLSpaceShipSvr_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IMotion_FWD_DEFINED__
#define __IMotion_FWD_DEFINED__
typedef interface IMotion IMotion;
#endif 	/* __IMotion_FWD_DEFINED__ */


#ifndef __IVisual_FWD_DEFINED__
#define __IVisual_FWD_DEFINED__
typedef interface IVisual IVisual;
#endif 	/* __IVisual_FWD_DEFINED__ */


#ifndef __IClassicATLSpaceship_FWD_DEFINED__
#define __IClassicATLSpaceship_FWD_DEFINED__
typedef interface IClassicATLSpaceship IClassicATLSpaceship;
#endif 	/* __IClassicATLSpaceship_FWD_DEFINED__ */


#ifndef __ClassicATLSpaceship_FWD_DEFINED__
#define __ClassicATLSpaceship_FWD_DEFINED__

#ifdef __cplusplus
typedef class ClassicATLSpaceship ClassicATLSpaceship;
#else
typedef struct ClassicATLSpaceship ClassicATLSpaceship;
#endif /* __cplusplus */

#endif 	/* __ClassicATLSpaceship_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

#ifndef __IMotion_INTERFACE_DEFINED__
#define __IMotion_INTERFACE_DEFINED__

/* interface IMotion */
/* [helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IMotion;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("692D03A4-C689-11CE-B337-88EA36DE9E4E")
    IMotion : public IDispatch
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Fly( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetPosition( 
            /* [retval][out] */ long *nPosition) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMotionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IMotion * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IMotion * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IMotion * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IMotion * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IMotion * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IMotion * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IMotion * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE *Fly )( 
            IMotion * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetPosition )( 
            IMotion * This,
            /* [retval][out] */ long *nPosition);
        
        END_INTERFACE
    } IMotionVtbl;

    interface IMotion
    {
        CONST_VTBL struct IMotionVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMotion_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMotion_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMotion_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMotion_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMotion_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMotion_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMotion_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMotion_Fly(This)	\
    (This)->lpVtbl -> Fly(This)

#define IMotion_GetPosition(This,nPosition)	\
    (This)->lpVtbl -> GetPosition(This,nPosition)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IMotion_Fly_Proxy( 
    IMotion * This);


void __RPC_STUB IMotion_Fly_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMotion_GetPosition_Proxy( 
    IMotion * This,
    /* [retval][out] */ long *nPosition);


void __RPC_STUB IMotion_GetPosition_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMotion_INTERFACE_DEFINED__ */


#ifndef __IVisual_INTERFACE_DEFINED__
#define __IVisual_INTERFACE_DEFINED__

/* interface IVisual */
/* [helpstring][uuid][object] */ 


EXTERN_C const IID IID_IVisual;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("692D03A5-C689-11CE-B337-88EA36DE9E4E")
    IVisual : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE Display( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IVisualVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IVisual * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IVisual * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IVisual * This);
        
        HRESULT ( STDMETHODCALLTYPE *Display )( 
            IVisual * This);
        
        END_INTERFACE
    } IVisualVtbl;

    interface IVisual
    {
        CONST_VTBL struct IVisualVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IVisual_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IVisual_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IVisual_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IVisual_Display(This)	\
    (This)->lpVtbl -> Display(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



HRESULT STDMETHODCALLTYPE IVisual_Display_Proxy( 
    IVisual * This);


void __RPC_STUB IVisual_Display_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVisual_INTERFACE_DEFINED__ */


#ifndef __IClassicATLSpaceship_INTERFACE_DEFINED__
#define __IClassicATLSpaceship_INTERFACE_DEFINED__

/* interface IClassicATLSpaceship */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IClassicATLSpaceship;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("45896187-46FF-4A07-A9DC-557377380535")
    IClassicATLSpaceship : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CallStarFleet( 
            /* [in] */ FLOAT fStarDate,
            /* [retval][out] */ BSTR *pbstRecipient) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IClassicATLSpaceshipVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IClassicATLSpaceship * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IClassicATLSpaceship * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IClassicATLSpaceship * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IClassicATLSpaceship * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IClassicATLSpaceship * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IClassicATLSpaceship * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IClassicATLSpaceship * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *CallStarFleet )( 
            IClassicATLSpaceship * This,
            /* [in] */ FLOAT fStarDate,
            /* [retval][out] */ BSTR *pbstRecipient);
        
        END_INTERFACE
    } IClassicATLSpaceshipVtbl;

    interface IClassicATLSpaceship
    {
        CONST_VTBL struct IClassicATLSpaceshipVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IClassicATLSpaceship_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IClassicATLSpaceship_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IClassicATLSpaceship_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IClassicATLSpaceship_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IClassicATLSpaceship_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IClassicATLSpaceship_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IClassicATLSpaceship_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IClassicATLSpaceship_CallStarFleet(This,fStarDate,pbstRecipient)	\
    (This)->lpVtbl -> CallStarFleet(This,fStarDate,pbstRecipient)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IClassicATLSpaceship_CallStarFleet_Proxy( 
    IClassicATLSpaceship * This,
    /* [in] */ FLOAT fStarDate,
    /* [retval][out] */ BSTR *pbstRecipient);


void __RPC_STUB IClassicATLSpaceship_CallStarFleet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IClassicATLSpaceship_INTERFACE_DEFINED__ */



#ifndef __ATLSpaceShipSvrLib_LIBRARY_DEFINED__
#define __ATLSpaceShipSvrLib_LIBRARY_DEFINED__

/* library ATLSpaceShipSvrLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_ATLSpaceShipSvrLib;

EXTERN_C const CLSID CLSID_ClassicATLSpaceship;

#ifdef __cplusplus

class DECLSPEC_UUID("E485E21E-A23C-413F-A93B-909318565113")
ClassicATLSpaceship;
#endif
#endif /* __ATLSpaceShipSvrLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


