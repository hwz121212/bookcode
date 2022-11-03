

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 11:14:07 2038
 */
/* Compiler settings for _Ex29c.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.01.0622 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef ___Ex29c_h__
#define ___Ex29c_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __ICDHTMLUI_FWD_DEFINED__
#define __ICDHTMLUI_FWD_DEFINED__
typedef interface ICDHTMLUI ICDHTMLUI;

#endif 	/* __ICDHTMLUI_FWD_DEFINED__ */


#ifndef __ICDHTML_FWD_DEFINED__
#define __ICDHTML_FWD_DEFINED__
typedef interface ICDHTML ICDHTML;

#endif 	/* __ICDHTML_FWD_DEFINED__ */


#ifndef __CCDHTMLUI_FWD_DEFINED__
#define __CCDHTMLUI_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCDHTMLUI CCDHTMLUI;
#else
typedef struct CCDHTMLUI CCDHTMLUI;
#endif /* __cplusplus */

#endif 	/* __CCDHTMLUI_FWD_DEFINED__ */


#ifndef __CCDHTML_FWD_DEFINED__
#define __CCDHTML_FWD_DEFINED__

#ifdef __cplusplus
typedef class CCDHTML CCDHTML;
#else
typedef struct CCDHTML CCDHTML;
#endif /* __cplusplus */

#endif 	/* __CCDHTML_FWD_DEFINED__ */


/* header files for imported files */
#include "prsht.h"
#include "MsHTML.h"
#include "MsHtmHst.h"
#include "ExDisp.h"
#include "ObjSafe.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __ICDHTMLUI_INTERFACE_DEFINED__
#define __ICDHTMLUI_INTERFACE_DEFINED__

/* interface ICDHTMLUI */
/* [unique][helpstring][uuid][dual][object] */ 


EXTERN_C const IID IID_ICDHTMLUI;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9F3E85AE-09C6-4A3A-A78C-6973F8A328B6")
    ICDHTMLUI : public IDispatch
    {
    public:
        virtual /* [id] */ HRESULT STDMETHODCALLTYPE OnClick( 
            /* [in] */ IDispatch *pdispBody,
            /* [in] */ VARIANT varColor) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ICDHTMLUIVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICDHTMLUI * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICDHTMLUI * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICDHTMLUI * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICDHTMLUI * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICDHTMLUI * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICDHTMLUI * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICDHTMLUI * This,
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
        
        /* [id] */ HRESULT ( STDMETHODCALLTYPE *OnClick )( 
            ICDHTMLUI * This,
            /* [in] */ IDispatch *pdispBody,
            /* [in] */ VARIANT varColor);
        
        END_INTERFACE
    } ICDHTMLUIVtbl;

    interface ICDHTMLUI
    {
        CONST_VTBL struct ICDHTMLUIVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICDHTMLUI_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICDHTMLUI_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICDHTMLUI_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICDHTMLUI_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ICDHTMLUI_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ICDHTMLUI_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ICDHTMLUI_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define ICDHTMLUI_OnClick(This,pdispBody,varColor)	\
    ( (This)->lpVtbl -> OnClick(This,pdispBody,varColor) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICDHTMLUI_INTERFACE_DEFINED__ */


#ifndef __ICDHTML_INTERFACE_DEFINED__
#define __ICDHTML_INTERFACE_DEFINED__

/* interface ICDHTML */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_ICDHTML;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C0771F2F-6285-48EA-9356-8AA2A4D8C47D")
    ICDHTML : public IDispatch
    {
    public:
    };
    
    
#else 	/* C style interface */

    typedef struct ICDHTMLVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICDHTML * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICDHTML * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICDHTML * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            ICDHTML * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            ICDHTML * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            ICDHTML * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            ICDHTML * This,
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
    } ICDHTMLVtbl;

    interface ICDHTML
    {
        CONST_VTBL struct ICDHTMLVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICDHTML_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICDHTML_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICDHTML_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICDHTML_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define ICDHTML_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define ICDHTML_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define ICDHTML_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICDHTML_INTERFACE_DEFINED__ */



#ifndef __Ex29c_LIBRARY_DEFINED__
#define __Ex29c_LIBRARY_DEFINED__

/* library Ex29c */
/* [helpstring][uuid][version] */ 


EXTERN_C const IID LIBID_Ex29c;

EXTERN_C const CLSID CLSID_CCDHTMLUI;

#ifdef __cplusplus

class DECLSPEC_UUID("72DB36B5-154C-427E-9BB0-AAF3C496B6EC")
CCDHTMLUI;
#endif

EXTERN_C const CLSID CLSID_CCDHTML;

#ifdef __cplusplus

class DECLSPEC_UUID("E672F808-00BC-46AD-9970-8DB5585EAA1E")
CCDHTML;
#endif
#endif /* __Ex29c_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  VARIANT_UserSize(     unsigned long *, unsigned long            , VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserMarshal(  unsigned long *, unsigned char *, VARIANT * ); 
unsigned char * __RPC_USER  VARIANT_UserUnmarshal(unsigned long *, unsigned char *, VARIANT * ); 
void                      __RPC_USER  VARIANT_UserFree(     unsigned long *, VARIANT * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


