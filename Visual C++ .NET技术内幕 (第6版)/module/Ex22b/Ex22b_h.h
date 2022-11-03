

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 11:14:07 2038
 */
/* Compiler settings for Ex22b.idl:
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


#ifndef __Ex22b_h_h__
#define __Ex22b_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ISpaceship_FWD_DEFINED__
#define __ISpaceship_FWD_DEFINED__
typedef interface ISpaceship ISpaceship;

#endif 	/* __ISpaceship_FWD_DEFINED__ */


#ifndef __Spaceship_FWD_DEFINED__
#define __Spaceship_FWD_DEFINED__

#ifdef __cplusplus
typedef class Spaceship Spaceship;
#else
typedef struct Spaceship Spaceship;
#endif /* __cplusplus */

#endif 	/* __Spaceship_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __Ex22b_LIBRARY_DEFINED__
#define __Ex22b_LIBRARY_DEFINED__

/* library Ex22b */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_Ex22b;

#ifndef __ISpaceship_DISPINTERFACE_DEFINED__
#define __ISpaceship_DISPINTERFACE_DEFINED__

/* dispinterface ISpaceship */
/* [uuid] */ 


EXTERN_C const IID DIID_ISpaceship;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("A1E91507-C075-4AA5-B653-149C482E71DA")
    ISpaceship : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct ISpaceshipVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISpaceship * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISpaceship * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISpaceship * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ISpaceship * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ISpaceship * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ISpaceship * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ISpaceship * This,
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
    } ISpaceshipVtbl;

    interface ISpaceship
    {
        CONST_VTBL struct ISpaceshipVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISpaceship_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISpaceship_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISpaceship_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISpaceship_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ISpaceship_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ISpaceship_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ISpaceship_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __ISpaceship_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_Spaceship;

#ifdef __cplusplus

class DECLSPEC_UUID("DF55C608-9598-4EDD-B9ED-9198426471B3")
Spaceship;
#endif
#endif /* __Ex22b_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


