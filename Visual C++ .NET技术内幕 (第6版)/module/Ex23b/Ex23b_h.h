

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 11:14:07 2038
 */
/* Compiler settings for Ex23b.idl:
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


#ifndef __Ex23b_h_h__
#define __Ex23b_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IEx23bAuto_FWD_DEFINED__
#define __IEx23bAuto_FWD_DEFINED__
typedef interface IEx23bAuto IEx23bAuto;

#endif 	/* __IEx23bAuto_FWD_DEFINED__ */


#ifndef __Ex23bAuto_FWD_DEFINED__
#define __Ex23bAuto_FWD_DEFINED__

#ifdef __cplusplus
typedef class Ex23bAuto Ex23bAuto;
#else
typedef struct Ex23bAuto Ex23bAuto;
#endif /* __cplusplus */

#endif 	/* __Ex23bAuto_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __Ex23b_LIBRARY_DEFINED__
#define __Ex23b_LIBRARY_DEFINED__

/* library Ex23b */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_Ex23b;

#ifndef __IEx23bAuto_DISPINTERFACE_DEFINED__
#define __IEx23bAuto_DISPINTERFACE_DEFINED__

/* dispinterface IEx23bAuto */
/* [uuid] */ 


EXTERN_C const IID DIID_IEx23bAuto;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("125FECB2-734D-49FD-95C7-FE44B77FDE2C")
    IEx23bAuto : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IEx23bAutoVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEx23bAuto * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEx23bAuto * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEx23bAuto * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IEx23bAuto * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IEx23bAuto * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IEx23bAuto * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IEx23bAuto * This,
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
    } IEx23bAutoVtbl;

    interface IEx23bAuto
    {
        CONST_VTBL struct IEx23bAutoVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEx23bAuto_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEx23bAuto_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEx23bAuto_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEx23bAuto_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IEx23bAuto_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IEx23bAuto_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IEx23bAuto_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IEx23bAuto_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_Ex23bAuto;

#ifdef __cplusplus

class DECLSPEC_UUID("BAF3D9ED-4518-43CA-B017-2EBA332CB618")
Ex23bAuto;
#endif
#endif /* __Ex23b_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


