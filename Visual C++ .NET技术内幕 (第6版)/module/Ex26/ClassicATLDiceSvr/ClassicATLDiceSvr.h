

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 11:14:07 2038
 */
/* Compiler settings for ClassicATLDiceSvr.idl:
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

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __ClassicATLDiceSvr_h__
#define __ClassicATLDiceSvr_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IClassicATLDiceControl_FWD_DEFINED__
#define __IClassicATLDiceControl_FWD_DEFINED__
typedef interface IClassicATLDiceControl IClassicATLDiceControl;

#endif 	/* __IClassicATLDiceControl_FWD_DEFINED__ */


#ifndef ___IClassicATLDiceControlEvents_FWD_DEFINED__
#define ___IClassicATLDiceControlEvents_FWD_DEFINED__
typedef interface _IClassicATLDiceControlEvents _IClassicATLDiceControlEvents;

#endif 	/* ___IClassicATLDiceControlEvents_FWD_DEFINED__ */


#ifndef __ClassicATLDiceControl_FWD_DEFINED__
#define __ClassicATLDiceControl_FWD_DEFINED__

#ifdef __cplusplus
typedef class ClassicATLDiceControl ClassicATLDiceControl;
#else
typedef struct ClassicATLDiceControl ClassicATLDiceControl;
#endif /* __cplusplus */

#endif 	/* __ClassicATLDiceControl_FWD_DEFINED__ */


#ifndef __CDiceMainPropPage_FWD_DEFINED__
#define __CDiceMainPropPage_FWD_DEFINED__

#ifdef __cplusplus
typedef class CDiceMainPropPage CDiceMainPropPage;
#else
typedef struct CDiceMainPropPage CDiceMainPropPage;
#endif /* __cplusplus */

#endif 	/* __CDiceMainPropPage_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IClassicATLDiceControl_INTERFACE_DEFINED__
#define __IClassicATLDiceControl_INTERFACE_DEFINED__

/* interface IClassicATLDiceControl */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IClassicATLDiceControl;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("90621999-47DC-46CE-AC37-8C250AEC96AA")
    IClassicATLDiceControl : public IDispatch
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

    typedef struct IClassicATLDiceControlVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IClassicATLDiceControl * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IClassicATLDiceControl * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IClassicATLDiceControl * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IClassicATLDiceControl * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IClassicATLDiceControl * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IClassicATLDiceControl * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IClassicATLDiceControl * This,
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
        
        /* [id][requestedit][bindable][propput] */ HRESULT ( STDMETHODCALLTYPE *put_BackColor )( 
            IClassicATLDiceControl * This,
            /* [in] */ OLE_COLOR clr);
        
        /* [id][requestedit][bindable][propget] */ HRESULT ( STDMETHODCALLTYPE *get_BackColor )( 
            IClassicATLDiceControl * This,
            /* [retval][out] */ OLE_COLOR *pclr);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_DiceColor )( 
            IClassicATLDiceControl * This,
            /* [retval][out] */ SHORT *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_DiceColor )( 
            IClassicATLDiceControl * This,
            /* [in] */ SHORT newVal);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_TimesToRoll )( 
            IClassicATLDiceControl * This,
            /* [retval][out] */ SHORT *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_TimesToRoll )( 
            IClassicATLDiceControl * This,
            /* [in] */ SHORT newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RollDice )( 
            IClassicATLDiceControl * This);
        
        END_INTERFACE
    } IClassicATLDiceControlVtbl;

    interface IClassicATLDiceControl
    {
        CONST_VTBL struct IClassicATLDiceControlVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IClassicATLDiceControl_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IClassicATLDiceControl_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IClassicATLDiceControl_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IClassicATLDiceControl_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IClassicATLDiceControl_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IClassicATLDiceControl_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IClassicATLDiceControl_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IClassicATLDiceControl_put_BackColor(This,clr)	\
    ( (This)->lpVtbl -> put_BackColor(This,clr) ) 

#define IClassicATLDiceControl_get_BackColor(This,pclr)	\
    ( (This)->lpVtbl -> get_BackColor(This,pclr) ) 

#define IClassicATLDiceControl_get_DiceColor(This,pVal)	\
    ( (This)->lpVtbl -> get_DiceColor(This,pVal) ) 

#define IClassicATLDiceControl_put_DiceColor(This,newVal)	\
    ( (This)->lpVtbl -> put_DiceColor(This,newVal) ) 

#define IClassicATLDiceControl_get_TimesToRoll(This,pVal)	\
    ( (This)->lpVtbl -> get_TimesToRoll(This,pVal) ) 

#define IClassicATLDiceControl_put_TimesToRoll(This,newVal)	\
    ( (This)->lpVtbl -> put_TimesToRoll(This,newVal) ) 

#define IClassicATLDiceControl_RollDice(This)	\
    ( (This)->lpVtbl -> RollDice(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IClassicATLDiceControl_INTERFACE_DEFINED__ */



#ifndef __ClassicATLDiceSvrLib_LIBRARY_DEFINED__
#define __ClassicATLDiceSvrLib_LIBRARY_DEFINED__

/* library ClassicATLDiceSvrLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_ClassicATLDiceSvrLib;

#ifndef ___IClassicATLDiceControlEvents_DISPINTERFACE_DEFINED__
#define ___IClassicATLDiceControlEvents_DISPINTERFACE_DEFINED__

/* dispinterface _IClassicATLDiceControlEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__IClassicATLDiceControlEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("2FECDCBE-D2C8-46EF-A4A1-E86CDC63B321")
    _IClassicATLDiceControlEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _IClassicATLDiceControlEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _IClassicATLDiceControlEvents * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _IClassicATLDiceControlEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _IClassicATLDiceControlEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _IClassicATLDiceControlEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _IClassicATLDiceControlEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _IClassicATLDiceControlEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _IClassicATLDiceControlEvents * This,
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
    } _IClassicATLDiceControlEventsVtbl;

    interface _IClassicATLDiceControlEvents
    {
        CONST_VTBL struct _IClassicATLDiceControlEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _IClassicATLDiceControlEvents_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define _IClassicATLDiceControlEvents_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define _IClassicATLDiceControlEvents_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define _IClassicATLDiceControlEvents_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define _IClassicATLDiceControlEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define _IClassicATLDiceControlEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define _IClassicATLDiceControlEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___IClassicATLDiceControlEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_ClassicATLDiceControl;

#ifdef __cplusplus

class DECLSPEC_UUID("75E15528-7E89-431F-B170-D6991C26F944")
ClassicATLDiceControl;
#endif

EXTERN_C const CLSID CLSID_CDiceMainPropPage;

#ifdef __cplusplus

class DECLSPEC_UUID("7A91E3F2-21BB-4286-B02E-4F067FD48DB3")
CDiceMainPropPage;
#endif
#endif /* __ClassicATLDiceSvrLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


