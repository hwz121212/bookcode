

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 11:14:07 2038
 */
/* Compiler settings for Ex23c.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.01.0622 
    protocol : all , ms_ext, c_ext, robust
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


#ifndef __Ex23c_h_h__
#define __Ex23c_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IEx23c_FWD_DEFINED__
#define __IEx23c_FWD_DEFINED__
typedef interface IEx23c IEx23c;

#endif 	/* __IEx23c_FWD_DEFINED__ */


#ifndef __CEx23cDoc_FWD_DEFINED__
#define __CEx23cDoc_FWD_DEFINED__

#ifdef __cplusplus
typedef class CEx23cDoc CEx23cDoc;
#else
typedef struct CEx23cDoc CEx23cDoc;
#endif /* __cplusplus */

#endif 	/* __CEx23cDoc_FWD_DEFINED__ */


#ifndef __IAlarm_FWD_DEFINED__
#define __IAlarm_FWD_DEFINED__
typedef interface IAlarm IAlarm;

#endif 	/* __IAlarm_FWD_DEFINED__ */


#ifndef __Alarm_FWD_DEFINED__
#define __Alarm_FWD_DEFINED__

#ifdef __cplusplus
typedef class Alarm Alarm;
#else
typedef struct Alarm Alarm;
#endif /* __cplusplus */

#endif 	/* __Alarm_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __Ex23c_LIBRARY_DEFINED__
#define __Ex23c_LIBRARY_DEFINED__

/* library Ex23c */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_Ex23c;

#ifndef __IEx23c_DISPINTERFACE_DEFINED__
#define __IEx23c_DISPINTERFACE_DEFINED__

/* dispinterface IEx23c */
/* [uuid] */ 


EXTERN_C const IID DIID_IEx23c;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("74084826-F896-446F-8414-3FF2BB911A63")
    IEx23c : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IEx23cVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEx23c * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEx23c * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEx23c * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IEx23c * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IEx23c * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IEx23c * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IEx23c * This,
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
    } IEx23cVtbl;

    interface IEx23c
    {
        CONST_VTBL struct IEx23cVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEx23c_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEx23c_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEx23c_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEx23c_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IEx23c_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IEx23c_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IEx23c_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IEx23c_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_CEx23cDoc;

#ifdef __cplusplus

class DECLSPEC_UUID("488A97C7-EBD1-4725-9804-C31B940D0DCA")
CEx23cDoc;
#endif

#ifndef __IAlarm_DISPINTERFACE_DEFINED__
#define __IAlarm_DISPINTERFACE_DEFINED__

/* dispinterface IAlarm */
/* [uuid] */ 


EXTERN_C const IID DIID_IAlarm;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("8DB7D0FB-355F-464B-BBD5-0F17553E71C8")
    IAlarm : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IAlarmVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAlarm * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAlarm * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAlarm * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IAlarm * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IAlarm * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IAlarm * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IAlarm * This,
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
    } IAlarmVtbl;

    interface IAlarm
    {
        CONST_VTBL struct IAlarmVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAlarm_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAlarm_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAlarm_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAlarm_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IAlarm_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IAlarm_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IAlarm_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IAlarm_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_Alarm;

#ifdef __cplusplus

class DECLSPEC_UUID("052D0691-A19F-426F-BA06-E62234B405F3")
Alarm;
#endif
#endif /* __Ex23c_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


