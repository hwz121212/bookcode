/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0158 */
/* at Thu Jun 18 16:49:58 1998
 */
/* Compiler settings for D:\BookCode\ex29a\spaceshipsvr\spaceshipsvr.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
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

#ifndef __spaceshipsvr_h__
#define __spaceshipsvr_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IAtlSpaceShip_FWD_DEFINED__
#define __IAtlSpaceShip_FWD_DEFINED__
typedef interface IAtlSpaceShip IAtlSpaceShip;
#endif 	/* __IAtlSpaceShip_FWD_DEFINED__ */


#ifndef __IMotion_FWD_DEFINED__
#define __IMotion_FWD_DEFINED__
typedef interface IMotion IMotion;
#endif 	/* __IMotion_FWD_DEFINED__ */


#ifndef __IVisual_FWD_DEFINED__
#define __IVisual_FWD_DEFINED__
typedef interface IVisual IVisual;
#endif 	/* __IVisual_FWD_DEFINED__ */


#ifndef __AtlSpaceShip_FWD_DEFINED__
#define __AtlSpaceShip_FWD_DEFINED__

#ifdef __cplusplus
typedef class AtlSpaceShip AtlSpaceShip;
#else
typedef struct AtlSpaceShip AtlSpaceShip;
#endif /* __cplusplus */

#endif 	/* __AtlSpaceShip_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IAtlSpaceShip_INTERFACE_DEFINED__
#define __IAtlSpaceShip_INTERFACE_DEFINED__

/* interface IAtlSpaceShip */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IAtlSpaceShip;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A9D750E1-51A1-11D1-8CAA-FD10872CC837")
    IAtlSpaceShip : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE CallStarFleet( 
            /* [in] */ float fStarDate,
            /* [retval][out] */ BSTR __RPC_FAR *pbstRecipient) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAtlSpaceShipVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IAtlSpaceShip __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IAtlSpaceShip __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IAtlSpaceShip __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IAtlSpaceShip __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IAtlSpaceShip __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IAtlSpaceShip __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IAtlSpaceShip __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *CallStarFleet )( 
            IAtlSpaceShip __RPC_FAR * This,
            /* [in] */ float fStarDate,
            /* [retval][out] */ BSTR __RPC_FAR *pbstRecipient);
        
        END_INTERFACE
    } IAtlSpaceShipVtbl;

    interface IAtlSpaceShip
    {
        CONST_VTBL struct IAtlSpaceShipVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAtlSpaceShip_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAtlSpaceShip_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAtlSpaceShip_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAtlSpaceShip_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IAtlSpaceShip_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IAtlSpaceShip_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IAtlSpaceShip_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IAtlSpaceShip_CallStarFleet(This,fStarDate,pbstRecipient)	\
    (This)->lpVtbl -> CallStarFleet(This,fStarDate,pbstRecipient)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAtlSpaceShip_CallStarFleet_Proxy( 
    IAtlSpaceShip __RPC_FAR * This,
    /* [in] */ float fStarDate,
    /* [retval][out] */ BSTR __RPC_FAR *pbstRecipient);


void __RPC_STUB IAtlSpaceShip_CallStarFleet_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAtlSpaceShip_INTERFACE_DEFINED__ */


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
            /* [retval][out] */ long __RPC_FAR *nPosition) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMotionVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMotion __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMotion __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMotion __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IMotion __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IMotion __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IMotion __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IMotion __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Fly )( 
            IMotion __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetPosition )( 
            IMotion __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *nPosition);
        
        END_INTERFACE
    } IMotionVtbl;

    interface IMotion
    {
        CONST_VTBL struct IMotionVtbl __RPC_FAR *lpVtbl;
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
    IMotion __RPC_FAR * This);


void __RPC_STUB IMotion_Fly_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


HRESULT STDMETHODCALLTYPE IMotion_GetPosition_Proxy( 
    IMotion __RPC_FAR * This,
    /* [retval][out] */ long __RPC_FAR *nPosition);


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
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IVisual __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IVisual __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IVisual __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Display )( 
            IVisual __RPC_FAR * This);
        
        END_INTERFACE
    } IVisualVtbl;

    interface IVisual
    {
        CONST_VTBL struct IVisualVtbl __RPC_FAR *lpVtbl;
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
    IVisual __RPC_FAR * This);


void __RPC_STUB IVisual_Display_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IVisual_INTERFACE_DEFINED__ */



#ifndef __SPACESHIPSVRLib_LIBRARY_DEFINED__
#define __SPACESHIPSVRLib_LIBRARY_DEFINED__

/* library SPACESHIPSVRLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_SPACESHIPSVRLib;

EXTERN_C const CLSID CLSID_AtlSpaceShip;

#ifdef __cplusplus

class DECLSPEC_UUID("A9D750E2-51A1-11D1-8CAA-FD10872CC837")
AtlSpaceShip;
#endif
#endif /* __SPACESHIPSVRLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long __RPC_FAR *, unsigned long            , BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserMarshal(  unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
unsigned char __RPC_FAR * __RPC_USER  BSTR_UserUnmarshal(unsigned long __RPC_FAR *, unsigned char __RPC_FAR *, BSTR __RPC_FAR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long __RPC_FAR *, BSTR __RPC_FAR * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
