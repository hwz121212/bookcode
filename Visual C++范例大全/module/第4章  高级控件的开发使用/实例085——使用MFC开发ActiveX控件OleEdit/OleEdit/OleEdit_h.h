

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 11:14:07 2038
 */
/* Compiler settings for OleEdit.odl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.01.0622 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */


#ifndef __OleEdit_h_h__
#define __OleEdit_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef ___DOleEdit_FWD_DEFINED__
#define ___DOleEdit_FWD_DEFINED__
typedef interface _DOleEdit _DOleEdit;

#endif 	/* ___DOleEdit_FWD_DEFINED__ */


#ifndef ___DOleEditEvents_FWD_DEFINED__
#define ___DOleEditEvents_FWD_DEFINED__
typedef interface _DOleEditEvents _DOleEditEvents;

#endif 	/* ___DOleEditEvents_FWD_DEFINED__ */


#ifndef __OleEdit_FWD_DEFINED__
#define __OleEdit_FWD_DEFINED__

#ifdef __cplusplus
typedef class OleEdit OleEdit;
#else
typedef struct OleEdit OleEdit;
#endif /* __cplusplus */

#endif 	/* __OleEdit_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_OleEdit_0000_0000 */
/* [local] */ 

#pragma warning(push)
#pragma warning(disable:4001) 
#pragma once
#pragma warning(push)
#pragma warning(disable:4001) 
#pragma once
#pragma warning(pop)
#pragma warning(pop)
#pragma region Desktop Family
#pragma endregion


extern RPC_IF_HANDLE __MIDL_itf_OleEdit_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_OleEdit_0000_0000_v0_0_s_ifspec;


#ifndef __OLEEDITLib_LIBRARY_DEFINED__
#define __OLEEDITLib_LIBRARY_DEFINED__

/* library OLEEDITLib */
/* [control][helpstring][helpfile][version][uuid] */ 


EXTERN_C const IID LIBID_OLEEDITLib;

#ifndef ___DOleEdit_DISPINTERFACE_DEFINED__
#define ___DOleEdit_DISPINTERFACE_DEFINED__

/* dispinterface _DOleEdit */
/* [hidden][helpstring][uuid] */ 


EXTERN_C const IID DIID__DOleEdit;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("288788D5-F3BF-4880-97B4-CD01744E4491")
    _DOleEdit : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DOleEditVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DOleEdit * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DOleEdit * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DOleEdit * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DOleEdit * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DOleEdit * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DOleEdit * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DOleEdit * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } _DOleEditVtbl;

    interface _DOleEdit
    {
        CONST_VTBL struct _DOleEditVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DOleEdit_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DOleEdit_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DOleEdit_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DOleEdit_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DOleEdit_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DOleEdit_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DOleEdit_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DOleEdit_DISPINTERFACE_DEFINED__ */


#ifndef ___DOleEditEvents_DISPINTERFACE_DEFINED__
#define ___DOleEditEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DOleEditEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__DOleEditEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("87969E28-0660-49CB-A99A-3F34552332EA")
    _DOleEditEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DOleEditEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DOleEditEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DOleEditEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DOleEditEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DOleEditEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DOleEditEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DOleEditEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DOleEditEvents * This,
            /* [annotation][in] */ 
            _In_  DISPID dispIdMember,
            /* [annotation][in] */ 
            _In_  REFIID riid,
            /* [annotation][in] */ 
            _In_  LCID lcid,
            /* [annotation][in] */ 
            _In_  WORD wFlags,
            /* [annotation][out][in] */ 
            _In_  DISPPARAMS *pDispParams,
            /* [annotation][out] */ 
            _Out_opt_  VARIANT *pVarResult,
            /* [annotation][out] */ 
            _Out_opt_  EXCEPINFO *pExcepInfo,
            /* [annotation][out] */ 
            _Out_opt_  UINT *puArgErr);
        
        END_INTERFACE
    } _DOleEditEventsVtbl;

    interface _DOleEditEvents
    {
        CONST_VTBL struct _DOleEditEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DOleEditEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _DOleEditEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _DOleEditEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _DOleEditEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _DOleEditEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _DOleEditEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _DOleEditEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DOleEditEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_OleEdit;

#ifdef __cplusplus

class DECLSPEC_UUID("0A2E1C1D-5F28-4850-9129-8D55E9B6BB6D")
OleEdit;
#endif
#endif /* __OLEEDITLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


