/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0158 */
/* at Thu Jun 18 16:56:52 1998
 */
/* Compiler settings for D:\BookCode\ex30a\atldicesrvr.idl:
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

#ifndef __atldicesrvr_h__
#define __atldicesrvr_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IATLDiceObj_FWD_DEFINED__
#define __IATLDiceObj_FWD_DEFINED__
typedef interface IATLDiceObj IATLDiceObj;
#endif 	/* __IATLDiceObj_FWD_DEFINED__ */


#ifndef ___IATLDiceObjEvents_FWD_DEFINED__
#define ___IATLDiceObjEvents_FWD_DEFINED__
typedef interface _IATLDiceObjEvents _IATLDiceObjEvents;
#endif 	/* ___IATLDiceObjEvents_FWD_DEFINED__ */


#ifndef __ATLDiceObj_FWD_DEFINED__
#define __ATLDiceObj_FWD_DEFINED__

#ifdef __cplusplus
typedef class ATLDiceObj ATLDiceObj;
#else
typedef struct ATLDiceObj ATLDiceObj;
#endif /* __cplusplus */

#endif 	/* __ATLDiceObj_FWD_DEFINED__ */


#ifndef __DiceMainPropPage_FWD_DEFINED__
#define __DiceMainPropPage_FWD_DEFINED__

#ifdef __cplusplus
typedef class DiceMainPropPage DiceMainPropPage;
#else
typedef struct DiceMainPropPage DiceMainPropPage;
#endif /* __cplusplus */

#endif 	/* __DiceMainPropPage_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IATLDiceObj_INTERFACE_DEFINED__
#define __IATLDiceObj_INTERFACE_DEFINED__

/* interface IATLDiceObj */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IATLDiceObj;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("93BC1349-065C-11D2-8CAA-A5273A388638")
    IATLDiceObj : public IDispatch
    {
    public:
        virtual /* [id][propput] */ HRESULT STDMETHODCALLTYPE put_BackColor( 
            /* [in] */ OLE_COLOR clr) = 0;
        
        virtual /* [id][propget] */ HRESULT STDMETHODCALLTYPE get_BackColor( 
            /* [retval][out] */ OLE_COLOR __RPC_FAR *pclr) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RollDice( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TimesToRoll( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_TimesToRoll( 
            /* [in] */ short newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DiceColor( 
            /* [retval][out] */ short __RPC_FAR *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DiceColor( 
            /* [in] */ short newVal) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IATLDiceObjVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IATLDiceObj __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IATLDiceObj __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IATLDiceObj __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IATLDiceObj __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IATLDiceObj __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IATLDiceObj __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IATLDiceObj __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_BackColor )( 
            IATLDiceObj __RPC_FAR * This,
            /* [in] */ OLE_COLOR clr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_BackColor )( 
            IATLDiceObj __RPC_FAR * This,
            /* [retval][out] */ OLE_COLOR __RPC_FAR *pclr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *RollDice )( 
            IATLDiceObj __RPC_FAR * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_TimesToRoll )( 
            IATLDiceObj __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_TimesToRoll )( 
            IATLDiceObj __RPC_FAR * This,
            /* [in] */ short newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_DiceColor )( 
            IATLDiceObj __RPC_FAR * This,
            /* [retval][out] */ short __RPC_FAR *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_DiceColor )( 
            IATLDiceObj __RPC_FAR * This,
            /* [in] */ short newVal);
        
        END_INTERFACE
    } IATLDiceObjVtbl;

    interface IATLDiceObj
    {
        CONST_VTBL struct IATLDiceObjVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IATLDiceObj_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IATLDiceObj_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IATLDiceObj_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IATLDiceObj_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IATLDiceObj_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IATLDiceObj_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IATLDiceObj_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IATLDiceObj_put_BackColor(This,clr)	\
    (This)->lpVtbl -> put_BackColor(This,clr)

#define IATLDiceObj_get_BackColor(This,pclr)	\
    (This)->lpVtbl -> get_BackColor(This,pclr)

#define IATLDiceObj_RollDice(This)	\
    (This)->lpVtbl -> RollDice(This)

#define IATLDiceObj_get_TimesToRoll(This,pVal)	\
    (This)->lpVtbl -> get_TimesToRoll(This,pVal)

#define IATLDiceObj_put_TimesToRoll(This,newVal)	\
    (This)->lpVtbl -> put_TimesToRoll(This,newVal)

#define IATLDiceObj_get_DiceColor(This,pVal)	\
    (This)->lpVtbl -> get_DiceColor(This,pVal)

#define IATLDiceObj_put_DiceColor(This,newVal)	\
    (This)->lpVtbl -> put_DiceColor(This,newVal)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][propput] */ HRESULT STDMETHODCALLTYPE IATLDiceObj_put_BackColor_Proxy( 
    IATLDiceObj __RPC_FAR * This,
    /* [in] */ OLE_COLOR clr);


void __RPC_STUB IATLDiceObj_put_BackColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][propget] */ HRESULT STDMETHODCALLTYPE IATLDiceObj_get_BackColor_Proxy( 
    IATLDiceObj __RPC_FAR * This,
    /* [retval][out] */ OLE_COLOR __RPC_FAR *pclr);


void __RPC_STUB IATLDiceObj_get_BackColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IATLDiceObj_RollDice_Proxy( 
    IATLDiceObj __RPC_FAR * This);


void __RPC_STUB IATLDiceObj_RollDice_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IATLDiceObj_get_TimesToRoll_Proxy( 
    IATLDiceObj __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB IATLDiceObj_get_TimesToRoll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IATLDiceObj_put_TimesToRoll_Proxy( 
    IATLDiceObj __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB IATLDiceObj_put_TimesToRoll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IATLDiceObj_get_DiceColor_Proxy( 
    IATLDiceObj __RPC_FAR * This,
    /* [retval][out] */ short __RPC_FAR *pVal);


void __RPC_STUB IATLDiceObj_get_DiceColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IATLDiceObj_put_DiceColor_Proxy( 
    IATLDiceObj __RPC_FAR * This,
    /* [in] */ short newVal);


void __RPC_STUB IATLDiceObj_put_DiceColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IATLDiceObj_INTERFACE_DEFINED__ */



#ifndef __ATLDICESRVRLib_LIBRARY_DEFINED__
#define __ATLDICESRVRLib_LIBRARY_DEFINED__

/* library ATLDICESRVRLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_ATLDICESRVRLib;

#ifndef ___IATLDiceObjEvents_DISPINTERFACE_DEFINED__
#define ___IATLDiceObjEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IATLDiceObjEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IATLDiceObjEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("93BC134B-065C-11D2-8CAA-A5273A388638")
    _IATLDiceObjEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IATLDiceObjEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            _IATLDiceObjEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            _IATLDiceObjEvents __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            _IATLDiceObjEvents __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            _IATLDiceObjEvents __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            _IATLDiceObjEvents __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            _IATLDiceObjEvents __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            _IATLDiceObjEvents __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        END_INTERFACE
    } _IATLDiceObjEventsVtbl;

    interface _IATLDiceObjEvents
    {
        CONST_VTBL struct _IATLDiceObjEventsVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IATLDiceObjEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IATLDiceObjEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IATLDiceObjEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IATLDiceObjEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IATLDiceObjEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IATLDiceObjEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IATLDiceObjEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IATLDiceObjEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_ATLDiceObj;

#ifdef __cplusplus

class DECLSPEC_UUID("93BC134A-065C-11D2-8CAA-A5273A388638")
ATLDiceObj;
#endif

EXTERN_C const CLSID CLSID_DiceMainPropPage;

#ifdef __cplusplus

class DECLSPEC_UUID("93BC134D-065C-11D2-8CAA-A5273A388638")
DiceMainPropPage;
#endif
#endif /* __ATLDICESRVRLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
