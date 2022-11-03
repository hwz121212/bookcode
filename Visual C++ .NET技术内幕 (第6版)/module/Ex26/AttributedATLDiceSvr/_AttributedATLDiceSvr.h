
#pragma warning( disable: 4049 )  /* more than 64k source lines */

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0347 */
/* at Wed May 15 15:00:47 2002
 */
/* Compiler settings for _AttributedATLDiceSvr.idl:
    Os, W1, Zp8, env=Win32 (32b run)
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

#ifndef ___AttributedATLDiceSvr_h__
#define ___AttributedATLDiceSvr_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IAttributedATLDiceControl_FWD_DEFINED__
#define __IAttributedATLDiceControl_FWD_DEFINED__
typedef interface IAttributedATLDiceControl IAttributedATLDiceControl;
#endif 	/* __IAttributedATLDiceControl_FWD_DEFINED__ */


#ifndef ___IAttributedATLDiceControlEvents_FWD_DEFINED__
#define ___IAttributedATLDiceControlEvents_FWD_DEFINED__
typedef interface _IAttributedATLDiceControlEvents _IAttributedATLDiceControlEvents;
#endif 	/* ___IAttributedATLDiceControlEvents_FWD_DEFINED__ */


#ifndef __CAttributedATLDiceControl_FWD_DEFINED__
#define __CAttributedATLDiceControl_FWD_DEFINED__

#ifdef __cplusplus
typedef class CAttributedATLDiceControl CAttributedATLDiceControl;
#else
typedef struct CAttributedATLDiceControl CAttributedATLDiceControl;
#endif /* __cplusplus */

#endif 	/* __CAttributedATLDiceControl_FWD_DEFINED__ */


#ifndef __CDiceMainPropPage_FWD_DEFINED__
#define __CDiceMainPropPage_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDiceMainPropPage CDiceMainPropPage;
#else
typedef struct CDiceMainPropPage CDiceMainPropPage;
#endif /* __cplusplus */

#endif 	/* __CDiceMainPropPage_FWD_DEFINED__ */


/* header files for imported files */
#include "prsht.h"
#include "mshtml.h"
#include "mshtmhst.h"
#include "exdisp.h"
#include "objsafe.h"

#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 

#ifndef __IAttributedATLDiceControl_INTERFACE_DEFINED__
#define __IAttributedATLDiceControl_INTERFACE_DEFINED__

/* interface IAttributedATLDiceControl */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IAttributedATLDiceControl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("5321A066-9E3A-4412-A11A-32D5ED060146")
    IAttributedATLDiceControl : public IDispatch
    {
    public:
        virtual /* [id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE put_BackColor( 
            /* [in] */ OLE_COLOR clr) = 0;
        
        virtual /* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE get_BackColor( 
            /* [retval][out] */ OLE_COLOR *pclr) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_DiceColor( 
            /* [retval][out] */ SHORT *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_DiceColor( 
            /* [in] */ SHORT newVal) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_TimesToRoll( 
            /* [retval][out] */ SHORT *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_TimesToRoll( 
            /* [in] */ SHORT newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RollDice( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAttributedATLDiceControlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAttributedATLDiceControl * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAttributedATLDiceControl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAttributedATLDiceControl * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IAttributedATLDiceControl * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IAttributedATLDiceControl * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IAttributedATLDiceControl * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IAttributedATLDiceControl * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [id][requestedit][bindable][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BackColor )( 
            IAttributedATLDiceControl * This,
            /* [in] */ OLE_COLOR clr);
        
        /* [id][requestedit][bindable][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BackColor )( 
            IAttributedATLDiceControl * This,
            /* [retval][out] */ OLE_COLOR *pclr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DiceColor )( 
            IAttributedATLDiceControl * This,
            /* [retval][out] */ SHORT *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DiceColor )( 
            IAttributedATLDiceControl * This,
            /* [in] */ SHORT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TimesToRoll )( 
            IAttributedATLDiceControl * This,
            /* [retval][out] */ SHORT *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TimesToRoll )( 
            IAttributedATLDiceControl * This,
            /* [in] */ SHORT newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RollDice )( 
            IAttributedATLDiceControl * This);
        
        END_INTERFACE
    } IAttributedATLDiceControlVtbl;

    interface IAttributedATLDiceControl
    {
        CONST_VTBL struct IAttributedATLDiceControlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAttributedATLDiceControl_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IAttributedATLDiceControl_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IAttributedATLDiceControl_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IAttributedATLDiceControl_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IAttributedATLDiceControl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IAttributedATLDiceControl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IAttributedATLDiceControl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IAttributedATLDiceControl_put_BackColor(This,clr)	\
    (This)->lpVtbl -> put_BackColor(This,clr)

#define IAttributedATLDiceControl_get_BackColor(This,pclr)	\
    (This)->lpVtbl -> get_BackColor(This,pclr)

#define IAttributedATLDiceControl_get_DiceColor(This,pVal)	\
    (This)->lpVtbl -> get_DiceColor(This,pVal)

#define IAttributedATLDiceControl_put_DiceColor(This,newVal)	\
    (This)->lpVtbl -> put_DiceColor(This,newVal)

#define IAttributedATLDiceControl_get_TimesToRoll(This,pVal)	\
    (This)->lpVtbl -> get_TimesToRoll(This,pVal)

#define IAttributedATLDiceControl_put_TimesToRoll(This,newVal)	\
    (This)->lpVtbl -> put_TimesToRoll(This,newVal)

#define IAttributedATLDiceControl_RollDice(This)	\
    (This)->lpVtbl -> RollDice(This)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [id][requestedit][bindable][propput] */ HRESULT STDMETHODCALLTYPE IAttributedATLDiceControl_put_BackColor_Proxy( 
    IAttributedATLDiceControl * This,
    /* [in] */ OLE_COLOR clr);


void __RPC_STUB IAttributedATLDiceControl_put_BackColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [id][requestedit][bindable][propget] */ HRESULT STDMETHODCALLTYPE IAttributedATLDiceControl_get_BackColor_Proxy( 
    IAttributedATLDiceControl * This,
    /* [retval][out] */ OLE_COLOR *pclr);


void __RPC_STUB IAttributedATLDiceControl_get_BackColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAttributedATLDiceControl_get_DiceColor_Proxy( 
    IAttributedATLDiceControl * This,
    /* [retval][out] */ SHORT *pVal);


void __RPC_STUB IAttributedATLDiceControl_get_DiceColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IAttributedATLDiceControl_put_DiceColor_Proxy( 
    IAttributedATLDiceControl * This,
    /* [in] */ SHORT newVal);


void __RPC_STUB IAttributedATLDiceControl_put_DiceColor_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE IAttributedATLDiceControl_get_TimesToRoll_Proxy( 
    IAttributedATLDiceControl * This,
    /* [retval][out] */ SHORT *pVal);


void __RPC_STUB IAttributedATLDiceControl_get_TimesToRoll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE IAttributedATLDiceControl_put_TimesToRoll_Proxy( 
    IAttributedATLDiceControl * This,
    /* [in] */ SHORT newVal);


void __RPC_STUB IAttributedATLDiceControl_put_TimesToRoll_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [helpstring][id] */ HRESULT STDMETHODCALLTYPE IAttributedATLDiceControl_RollDice_Proxy( 
    IAttributedATLDiceControl * This);


void __RPC_STUB IAttributedATLDiceControl_RollDice_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IAttributedATLDiceControl_INTERFACE_DEFINED__ */



#ifndef __AttributedATLDiceSvr_LIBRARY_DEFINED__
#define __AttributedATLDiceSvr_LIBRARY_DEFINED__

/* library AttributedATLDiceSvr */
/* [helpstring][uuid][version] */ 


EXTERN_C const IID LIBID_AttributedATLDiceSvr;

#ifndef ___IAttributedATLDiceControlEvents_DISPINTERFACE_DEFINED__
#define ___IAttributedATLDiceControlEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IAttributedATLDiceControlEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IAttributedATLDiceControlEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("4AB0D205-044E-4641-A0A5-B606D8685FE5")
    _IAttributedATLDiceControlEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IAttributedATLDiceControlEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IAttributedATLDiceControlEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IAttributedATLDiceControlEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IAttributedATLDiceControlEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IAttributedATLDiceControlEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IAttributedATLDiceControlEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IAttributedATLDiceControlEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IAttributedATLDiceControlEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _IAttributedATLDiceControlEventsVtbl;

    interface _IAttributedATLDiceControlEvents
    {
        CONST_VTBL struct _IAttributedATLDiceControlEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IAttributedATLDiceControlEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _IAttributedATLDiceControlEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _IAttributedATLDiceControlEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _IAttributedATLDiceControlEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _IAttributedATLDiceControlEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _IAttributedATLDiceControlEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _IAttributedATLDiceControlEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IAttributedATLDiceControlEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_CAttributedATLDiceControl;

#ifdef __cplusplus

class DECLSPEC_UUID("48350572-BE82-4FBB-AA6F-B4691E30173A")
CAttributedATLDiceControl;
#endif

EXTERN_C const CLSID CLSID_CDiceMainPropPage;

#ifdef __cplusplus

class DECLSPEC_UUID("0B276055-2D66-4738-91D3-EF8C1D0497AE")
CDiceMainPropPage;
#endif
#endif /* __AttributedATLDiceSvr_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


