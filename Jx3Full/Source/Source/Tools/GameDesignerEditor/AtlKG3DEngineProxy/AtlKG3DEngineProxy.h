

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Tue Jul 24 04:03:08 2018
 */
/* Compiler settings for AtlKG3DEngineProxy.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


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

#ifndef __AtlKG3DEngineProxy_h__
#define __AtlKG3DEngineProxy_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IAtlOld3DEngine_FWD_DEFINED__
#define __IAtlOld3DEngine_FWD_DEFINED__
typedef interface IAtlOld3DEngine IAtlOld3DEngine;
#endif 	/* __IAtlOld3DEngine_FWD_DEFINED__ */


#ifndef __IAtlIEKSceneEditorDocLogical_FWD_DEFINED__
#define __IAtlIEKSceneEditorDocLogical_FWD_DEFINED__
typedef interface IAtlIEKSceneEditorDocLogical IAtlIEKSceneEditorDocLogical;
#endif 	/* __IAtlIEKSceneEditorDocLogical_FWD_DEFINED__ */


#ifndef __IAtlBase_FWD_DEFINED__
#define __IAtlBase_FWD_DEFINED__
typedef interface IAtlBase IAtlBase;
#endif 	/* __IAtlBase_FWD_DEFINED__ */


#ifndef __IBaseLib_FWD_DEFINED__
#define __IBaseLib_FWD_DEFINED__
typedef interface IBaseLib IBaseLib;
#endif 	/* __IBaseLib_FWD_DEFINED__ */


#ifndef __ISO3World_FWD_DEFINED__
#define __ISO3World_FWD_DEFINED__
typedef interface ISO3World ISO3World;
#endif 	/* __ISO3World_FWD_DEFINED__ */


#ifndef __IAtlInputProxy_FWD_DEFINED__
#define __IAtlInputProxy_FWD_DEFINED__
typedef interface IAtlInputProxy IAtlInputProxy;
#endif 	/* __IAtlInputProxy_FWD_DEFINED__ */


#ifndef __ISceneEditor_FWD_DEFINED__
#define __ISceneEditor_FWD_DEFINED__
typedef interface ISceneEditor ISceneEditor;
#endif 	/* __ISceneEditor_FWD_DEFINED__ */


#ifndef __AtlBase_FWD_DEFINED__
#define __AtlBase_FWD_DEFINED__

#ifdef __cplusplus
typedef class AtlBase AtlBase;
#else
typedef struct AtlBase AtlBase;
#endif /* __cplusplus */

#endif 	/* __AtlBase_FWD_DEFINED__ */


#ifndef __BaseLib_FWD_DEFINED__
#define __BaseLib_FWD_DEFINED__

#ifdef __cplusplus
typedef class BaseLib BaseLib;
#else
typedef struct BaseLib BaseLib;
#endif /* __cplusplus */

#endif 	/* __BaseLib_FWD_DEFINED__ */


#ifndef __SO3World_FWD_DEFINED__
#define __SO3World_FWD_DEFINED__

#ifdef __cplusplus
typedef class SO3World SO3World;
#else
typedef struct SO3World SO3World;
#endif /* __cplusplus */

#endif 	/* __SO3World_FWD_DEFINED__ */


#ifndef __AtlInputProxy_FWD_DEFINED__
#define __AtlInputProxy_FWD_DEFINED__

#ifdef __cplusplus
typedef class AtlInputProxy AtlInputProxy;
#else
typedef struct AtlInputProxy AtlInputProxy;
#endif /* __cplusplus */

#endif 	/* __AtlInputProxy_FWD_DEFINED__ */


#ifndef __SceneEditor_FWD_DEFINED__
#define __SceneEditor_FWD_DEFINED__

#ifdef __cplusplus
typedef class SceneEditor SceneEditor;
#else
typedef struct SceneEditor SceneEditor;
#endif /* __cplusplus */

#endif 	/* __SceneEditor_FWD_DEFINED__ */


#ifndef __AtlOld3DEngine_FWD_DEFINED__
#define __AtlOld3DEngine_FWD_DEFINED__

#ifdef __cplusplus
typedef class AtlOld3DEngine AtlOld3DEngine;
#else
typedef struct AtlOld3DEngine AtlOld3DEngine;
#endif /* __cplusplus */

#endif 	/* __AtlOld3DEngine_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"
#include "ocidl.h"
#include "ExtraStructDef.h"

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_AtlKG3DEngineProxy_0000_0000 */
/* [local] */ 











extern RPC_IF_HANDLE __MIDL_itf_AtlKG3DEngineProxy_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_AtlKG3DEngineProxy_0000_0000_v0_0_s_ifspec;

#ifndef __IAtlOld3DEngine_INTERFACE_DEFINED__
#define __IAtlOld3DEngine_INTERFACE_DEFINED__

/* interface IAtlOld3DEngine */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_IAtlOld3DEngine;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("9218D1CF-1B03-4677-8904-6F7116467A43")
    IAtlOld3DEngine : public IDispatch
    {
    public:
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Init( 
            LONG hwndBase,
            BSTR strEnginePath,
            BSTR strStartUpPath) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE Render( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FrameMove( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UnInit( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OnResizeWindow( void) = 0;
        
        virtual /* [helpstring][id][propget] */ HRESULT STDMETHODCALLTYPE get_PlayMode( 
            /* [retval][out] */ VARIANT_BOOL *pVal) = 0;
        
        virtual /* [helpstring][id][propput] */ HRESULT STDMETHODCALLTYPE put_PlayMode( 
            /* [in] */ VARIANT_BOOL newVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE OnWndMsg( 
            /* [in] */ BSTR editor_name,
            /* [in] */ PMSG WndMsg,
            /* [retval][out] */ INT *pnRet) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadFile( 
            BSTR strFileName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UnloadFile( 
            BSTR strFileName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadPlayerModel( 
            BSTR strFileName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE BindToPlayer( 
            BSTR strFileName,
            DWORD dwType,
            BSTR strBindToObj) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadAni( 
            BSTR strFileName,
            BOOL bLoop) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ZoomView( 
            LONG lDelta) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ChangeModelPart( 
            BSTR filename,
            INT PartID) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadFace( 
            BSTR strFileName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ItemsClear( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SaveMDLToFile( 
            BSTR strFileName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadMaterial( 
            /* [in] */ BSTR strFileName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadAnimation( 
            /* [in] */ BSTR strFileName,
            BOOL bLoopPlay) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadPluginModel( 
            /* [in] */ BSTR strFileName,
            BSTR strBindDest) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ClearPluginModel( 
            /* [in] */ BSTR strBindDest) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ActivateScene( 
            /* [in] */ BSTR editor_name) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RemoveScene( 
            /* [in] */ BSTR editor_name) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddScene( 
            /* [in] */ LONG hwndOutput,
            /* [in] */ BSTR editor_name,
            /* [in] */ LONG iOption) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetEditorSceneCount( 
            /* [in] */ BSTR editor_name,
            /* [out] */ LONG *count) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadSelectorSfxFile( 
            /* [in] */ BSTR sfx_name) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ScaleSelectorSfx( 
            /* [in] */ FLOAT x,
            /* [in] */ FLOAT y,
            /* [in] */ FLOAT z) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadOneMap_NoOutputWindow( 
            /* [in] */ BSTR filename,
            /* [out] */ LONG *ptrScene) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadBillboardSfx( 
            /* [in] */ BSTR filename) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetBillboardHeight( 
            /* [in] */ INT npc_height,
            /* [in] */ INT head_top_adjust) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ToggleRotateModelEditor( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetCameraInfo( 
            LONG pX,
            LONG pY,
            LONG pZ,
            LONG lX,
            LONG lY,
            LONG lZ,
            LONG width,
            LONG height) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCameraInfo( 
            /* [out] */ LONG *pX,
            /* [out] */ LONG *pY,
            /* [out] */ LONG *pZ,
            /* [out] */ LONG *lX,
            /* [out] */ LONG *lY,
            /* [out] */ LONG *lZ,
            /* [out] */ LONG *width,
            /* [out] */ LONG *height) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AdjustCameraOrthogonal( 
            /* [in] */ LONG iOffset) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetModelScale( 
            /* [in] */ FLOAT fScale) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SaveModelToImageFile( 
            /* [in] */ BSTR fileName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadSkillSfx( 
            /* [in] */ BSTR filename,
            /* [in] */ FLOAT scale,
            /* [in] */ BSTR socketName,
            /* [in] */ LONG iIndex) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ReadMapTerrainInfo( 
            /* [in] */ LONG ptrScene,
            /* [out] */ LONG *width,
            /* [out] */ LONG *height) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE FileToImage( 
            /* [in] */ BSTR src3DFileName,
            /* [in] */ BSTR desImageFileName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetCurSceneIndex( 
            /* [out] */ LONG *index) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ActivateSceneByIndex( 
            /* [in] */ LONG index) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SaveMdlWithAniToImages( 
            /* [in] */ LONG ptrModel,
            /* [in] */ BSTR filename) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SaveLogicScene( 
            /* [in] */ BSTR iniFile,
            /* [in] */ LONG ptr3DScene) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ShowProgressForm( 
            /* [in] */ BOOL bShow) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE UnloadPlayerModel( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetHeight( 
            /* [in] */ LONG ptrScene,
            /* [in] */ FLOAT x,
            /* [in] */ FLOAT z,
            /* [out] */ FLOAT *y) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetFileNameHash( 
            /* [in] */ BSTR fileName,
            /* [out] */ DWORD *hashid) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE QuaternionRotationByNDir( 
            FLOAT *x,
            FLOAT *y,
            FLOAT *z,
            FLOAT *w,
            /* [in] */ LONG nDir) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadPluginMaterial( 
            /* [in] */ BSTR strSocketName,
            /* [in] */ BSTR strMtlFile) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetAniFrameCount( 
            /* [in] */ BSTR strAniFileName,
            /* [retval][out] */ LONG *count) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadPlaneForSelector( 
            /* [in] */ BSTR strFileName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetCaptionHeight( 
            /* [in] */ FLOAT fHeight) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetCaptionText( 
            /* [in] */ BSTR strName,
            /* [in] */ BSTR strTitle) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetBBoxXY( 
            /* [in] */ BSTR mdl,
            /* [out] */ FLOAT *x,
            /* [out] */ FLOAT *y) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetMdlBBoxMax2DLength( 
            /* [in] */ BSTR mdl,
            /* [retval][out] */ FLOAT *pVal) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetEditorSceneSize( 
            /* [in] */ LONG ptrScene,
            LONG *width,
            LONG *height) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ToggleEngine( void) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetAllPluginModelScale( 
            /* [in] */ FLOAT fScale) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE LoadNPCMarkSfxFile( 
            /* [in] */ BSTR sfx_name,
            /* [in] */ FLOAT fHeight) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetInitInfo( 
            LONG *hwndBase,
            BSTR *strEnginePath,
            BSTR *strStartUpPath) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAtlOld3DEngineVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAtlOld3DEngine * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAtlOld3DEngine * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAtlOld3DEngine * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IAtlOld3DEngine * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IAtlOld3DEngine * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IAtlOld3DEngine * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IAtlOld3DEngine * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Init )( 
            IAtlOld3DEngine * This,
            LONG hwndBase,
            BSTR strEnginePath,
            BSTR strStartUpPath);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *Render )( 
            IAtlOld3DEngine * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *FrameMove )( 
            IAtlOld3DEngine * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *UnInit )( 
            IAtlOld3DEngine * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OnResizeWindow )( 
            IAtlOld3DEngine * This);
        
        /* [helpstring][id][propget] */ HRESULT ( STDMETHODCALLTYPE *get_PlayMode )( 
            IAtlOld3DEngine * This,
            /* [retval][out] */ VARIANT_BOOL *pVal);
        
        /* [helpstring][id][propput] */ HRESULT ( STDMETHODCALLTYPE *put_PlayMode )( 
            IAtlOld3DEngine * This,
            /* [in] */ VARIANT_BOOL newVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *OnWndMsg )( 
            IAtlOld3DEngine * This,
            /* [in] */ BSTR editor_name,
            /* [in] */ PMSG WndMsg,
            /* [retval][out] */ INT *pnRet);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *LoadFile )( 
            IAtlOld3DEngine * This,
            BSTR strFileName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *UnloadFile )( 
            IAtlOld3DEngine * This,
            BSTR strFileName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *LoadPlayerModel )( 
            IAtlOld3DEngine * This,
            BSTR strFileName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *BindToPlayer )( 
            IAtlOld3DEngine * This,
            BSTR strFileName,
            DWORD dwType,
            BSTR strBindToObj);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *LoadAni )( 
            IAtlOld3DEngine * This,
            BSTR strFileName,
            BOOL bLoop);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ZoomView )( 
            IAtlOld3DEngine * This,
            LONG lDelta);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ChangeModelPart )( 
            IAtlOld3DEngine * This,
            BSTR filename,
            INT PartID);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *LoadFace )( 
            IAtlOld3DEngine * This,
            BSTR strFileName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ItemsClear )( 
            IAtlOld3DEngine * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SaveMDLToFile )( 
            IAtlOld3DEngine * This,
            BSTR strFileName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *LoadMaterial )( 
            IAtlOld3DEngine * This,
            /* [in] */ BSTR strFileName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *LoadAnimation )( 
            IAtlOld3DEngine * This,
            /* [in] */ BSTR strFileName,
            BOOL bLoopPlay);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *LoadPluginModel )( 
            IAtlOld3DEngine * This,
            /* [in] */ BSTR strFileName,
            BSTR strBindDest);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ClearPluginModel )( 
            IAtlOld3DEngine * This,
            /* [in] */ BSTR strBindDest);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ActivateScene )( 
            IAtlOld3DEngine * This,
            /* [in] */ BSTR editor_name);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RemoveScene )( 
            IAtlOld3DEngine * This,
            /* [in] */ BSTR editor_name);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddScene )( 
            IAtlOld3DEngine * This,
            /* [in] */ LONG hwndOutput,
            /* [in] */ BSTR editor_name,
            /* [in] */ LONG iOption);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetEditorSceneCount )( 
            IAtlOld3DEngine * This,
            /* [in] */ BSTR editor_name,
            /* [out] */ LONG *count);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *LoadSelectorSfxFile )( 
            IAtlOld3DEngine * This,
            /* [in] */ BSTR sfx_name);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ScaleSelectorSfx )( 
            IAtlOld3DEngine * This,
            /* [in] */ FLOAT x,
            /* [in] */ FLOAT y,
            /* [in] */ FLOAT z);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *LoadOneMap_NoOutputWindow )( 
            IAtlOld3DEngine * This,
            /* [in] */ BSTR filename,
            /* [out] */ LONG *ptrScene);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *LoadBillboardSfx )( 
            IAtlOld3DEngine * This,
            /* [in] */ BSTR filename);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetBillboardHeight )( 
            IAtlOld3DEngine * This,
            /* [in] */ INT npc_height,
            /* [in] */ INT head_top_adjust);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ToggleRotateModelEditor )( 
            IAtlOld3DEngine * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetCameraInfo )( 
            IAtlOld3DEngine * This,
            LONG pX,
            LONG pY,
            LONG pZ,
            LONG lX,
            LONG lY,
            LONG lZ,
            LONG width,
            LONG height);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetCameraInfo )( 
            IAtlOld3DEngine * This,
            /* [out] */ LONG *pX,
            /* [out] */ LONG *pY,
            /* [out] */ LONG *pZ,
            /* [out] */ LONG *lX,
            /* [out] */ LONG *lY,
            /* [out] */ LONG *lZ,
            /* [out] */ LONG *width,
            /* [out] */ LONG *height);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AdjustCameraOrthogonal )( 
            IAtlOld3DEngine * This,
            /* [in] */ LONG iOffset);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetModelScale )( 
            IAtlOld3DEngine * This,
            /* [in] */ FLOAT fScale);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SaveModelToImageFile )( 
            IAtlOld3DEngine * This,
            /* [in] */ BSTR fileName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *LoadSkillSfx )( 
            IAtlOld3DEngine * This,
            /* [in] */ BSTR filename,
            /* [in] */ FLOAT scale,
            /* [in] */ BSTR socketName,
            /* [in] */ LONG iIndex);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ReadMapTerrainInfo )( 
            IAtlOld3DEngine * This,
            /* [in] */ LONG ptrScene,
            /* [out] */ LONG *width,
            /* [out] */ LONG *height);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *FileToImage )( 
            IAtlOld3DEngine * This,
            /* [in] */ BSTR src3DFileName,
            /* [in] */ BSTR desImageFileName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetCurSceneIndex )( 
            IAtlOld3DEngine * This,
            /* [out] */ LONG *index);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ActivateSceneByIndex )( 
            IAtlOld3DEngine * This,
            /* [in] */ LONG index);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SaveMdlWithAniToImages )( 
            IAtlOld3DEngine * This,
            /* [in] */ LONG ptrModel,
            /* [in] */ BSTR filename);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SaveLogicScene )( 
            IAtlOld3DEngine * This,
            /* [in] */ BSTR iniFile,
            /* [in] */ LONG ptr3DScene);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ShowProgressForm )( 
            IAtlOld3DEngine * This,
            /* [in] */ BOOL bShow);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *UnloadPlayerModel )( 
            IAtlOld3DEngine * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetHeight )( 
            IAtlOld3DEngine * This,
            /* [in] */ LONG ptrScene,
            /* [in] */ FLOAT x,
            /* [in] */ FLOAT z,
            /* [out] */ FLOAT *y);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetFileNameHash )( 
            IAtlOld3DEngine * This,
            /* [in] */ BSTR fileName,
            /* [out] */ DWORD *hashid);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *QuaternionRotationByNDir )( 
            IAtlOld3DEngine * This,
            FLOAT *x,
            FLOAT *y,
            FLOAT *z,
            FLOAT *w,
            /* [in] */ LONG nDir);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *LoadPluginMaterial )( 
            IAtlOld3DEngine * This,
            /* [in] */ BSTR strSocketName,
            /* [in] */ BSTR strMtlFile);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetAniFrameCount )( 
            IAtlOld3DEngine * This,
            /* [in] */ BSTR strAniFileName,
            /* [retval][out] */ LONG *count);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *LoadPlaneForSelector )( 
            IAtlOld3DEngine * This,
            /* [in] */ BSTR strFileName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetCaptionHeight )( 
            IAtlOld3DEngine * This,
            /* [in] */ FLOAT fHeight);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetCaptionText )( 
            IAtlOld3DEngine * This,
            /* [in] */ BSTR strName,
            /* [in] */ BSTR strTitle);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetBBoxXY )( 
            IAtlOld3DEngine * This,
            /* [in] */ BSTR mdl,
            /* [out] */ FLOAT *x,
            /* [out] */ FLOAT *y);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetMdlBBoxMax2DLength )( 
            IAtlOld3DEngine * This,
            /* [in] */ BSTR mdl,
            /* [retval][out] */ FLOAT *pVal);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetEditorSceneSize )( 
            IAtlOld3DEngine * This,
            /* [in] */ LONG ptrScene,
            LONG *width,
            LONG *height);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ToggleEngine )( 
            IAtlOld3DEngine * This);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetAllPluginModelScale )( 
            IAtlOld3DEngine * This,
            /* [in] */ FLOAT fScale);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *LoadNPCMarkSfxFile )( 
            IAtlOld3DEngine * This,
            /* [in] */ BSTR sfx_name,
            /* [in] */ FLOAT fHeight);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetInitInfo )( 
            IAtlOld3DEngine * This,
            LONG *hwndBase,
            BSTR *strEnginePath,
            BSTR *strStartUpPath);
        
        END_INTERFACE
    } IAtlOld3DEngineVtbl;

    interface IAtlOld3DEngine
    {
        CONST_VTBL struct IAtlOld3DEngineVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAtlOld3DEngine_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAtlOld3DEngine_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAtlOld3DEngine_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAtlOld3DEngine_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IAtlOld3DEngine_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IAtlOld3DEngine_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IAtlOld3DEngine_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 


#define IAtlOld3DEngine_Init(This,hwndBase,strEnginePath,strStartUpPath)	\
    ( (This)->lpVtbl -> Init(This,hwndBase,strEnginePath,strStartUpPath) ) 

#define IAtlOld3DEngine_Render(This)	\
    ( (This)->lpVtbl -> Render(This) ) 

#define IAtlOld3DEngine_FrameMove(This)	\
    ( (This)->lpVtbl -> FrameMove(This) ) 

#define IAtlOld3DEngine_UnInit(This)	\
    ( (This)->lpVtbl -> UnInit(This) ) 

#define IAtlOld3DEngine_OnResizeWindow(This)	\
    ( (This)->lpVtbl -> OnResizeWindow(This) ) 

#define IAtlOld3DEngine_get_PlayMode(This,pVal)	\
    ( (This)->lpVtbl -> get_PlayMode(This,pVal) ) 

#define IAtlOld3DEngine_put_PlayMode(This,newVal)	\
    ( (This)->lpVtbl -> put_PlayMode(This,newVal) ) 

#define IAtlOld3DEngine_OnWndMsg(This,editor_name,WndMsg,pnRet)	\
    ( (This)->lpVtbl -> OnWndMsg(This,editor_name,WndMsg,pnRet) ) 

#define IAtlOld3DEngine_LoadFile(This,strFileName)	\
    ( (This)->lpVtbl -> LoadFile(This,strFileName) ) 

#define IAtlOld3DEngine_UnloadFile(This,strFileName)	\
    ( (This)->lpVtbl -> UnloadFile(This,strFileName) ) 

#define IAtlOld3DEngine_LoadPlayerModel(This,strFileName)	\
    ( (This)->lpVtbl -> LoadPlayerModel(This,strFileName) ) 

#define IAtlOld3DEngine_BindToPlayer(This,strFileName,dwType,strBindToObj)	\
    ( (This)->lpVtbl -> BindToPlayer(This,strFileName,dwType,strBindToObj) ) 

#define IAtlOld3DEngine_LoadAni(This,strFileName,bLoop)	\
    ( (This)->lpVtbl -> LoadAni(This,strFileName,bLoop) ) 

#define IAtlOld3DEngine_ZoomView(This,lDelta)	\
    ( (This)->lpVtbl -> ZoomView(This,lDelta) ) 

#define IAtlOld3DEngine_ChangeModelPart(This,filename,PartID)	\
    ( (This)->lpVtbl -> ChangeModelPart(This,filename,PartID) ) 

#define IAtlOld3DEngine_LoadFace(This,strFileName)	\
    ( (This)->lpVtbl -> LoadFace(This,strFileName) ) 

#define IAtlOld3DEngine_ItemsClear(This)	\
    ( (This)->lpVtbl -> ItemsClear(This) ) 

#define IAtlOld3DEngine_SaveMDLToFile(This,strFileName)	\
    ( (This)->lpVtbl -> SaveMDLToFile(This,strFileName) ) 

#define IAtlOld3DEngine_LoadMaterial(This,strFileName)	\
    ( (This)->lpVtbl -> LoadMaterial(This,strFileName) ) 

#define IAtlOld3DEngine_LoadAnimation(This,strFileName,bLoopPlay)	\
    ( (This)->lpVtbl -> LoadAnimation(This,strFileName,bLoopPlay) ) 

#define IAtlOld3DEngine_LoadPluginModel(This,strFileName,strBindDest)	\
    ( (This)->lpVtbl -> LoadPluginModel(This,strFileName,strBindDest) ) 

#define IAtlOld3DEngine_ClearPluginModel(This,strBindDest)	\
    ( (This)->lpVtbl -> ClearPluginModel(This,strBindDest) ) 

#define IAtlOld3DEngine_ActivateScene(This,editor_name)	\
    ( (This)->lpVtbl -> ActivateScene(This,editor_name) ) 

#define IAtlOld3DEngine_RemoveScene(This,editor_name)	\
    ( (This)->lpVtbl -> RemoveScene(This,editor_name) ) 

#define IAtlOld3DEngine_AddScene(This,hwndOutput,editor_name,iOption)	\
    ( (This)->lpVtbl -> AddScene(This,hwndOutput,editor_name,iOption) ) 

#define IAtlOld3DEngine_GetEditorSceneCount(This,editor_name,count)	\
    ( (This)->lpVtbl -> GetEditorSceneCount(This,editor_name,count) ) 

#define IAtlOld3DEngine_LoadSelectorSfxFile(This,sfx_name)	\
    ( (This)->lpVtbl -> LoadSelectorSfxFile(This,sfx_name) ) 

#define IAtlOld3DEngine_ScaleSelectorSfx(This,x,y,z)	\
    ( (This)->lpVtbl -> ScaleSelectorSfx(This,x,y,z) ) 

#define IAtlOld3DEngine_LoadOneMap_NoOutputWindow(This,filename,ptrScene)	\
    ( (This)->lpVtbl -> LoadOneMap_NoOutputWindow(This,filename,ptrScene) ) 

#define IAtlOld3DEngine_LoadBillboardSfx(This,filename)	\
    ( (This)->lpVtbl -> LoadBillboardSfx(This,filename) ) 

#define IAtlOld3DEngine_SetBillboardHeight(This,npc_height,head_top_adjust)	\
    ( (This)->lpVtbl -> SetBillboardHeight(This,npc_height,head_top_adjust) ) 

#define IAtlOld3DEngine_ToggleRotateModelEditor(This)	\
    ( (This)->lpVtbl -> ToggleRotateModelEditor(This) ) 

#define IAtlOld3DEngine_SetCameraInfo(This,pX,pY,pZ,lX,lY,lZ,width,height)	\
    ( (This)->lpVtbl -> SetCameraInfo(This,pX,pY,pZ,lX,lY,lZ,width,height) ) 

#define IAtlOld3DEngine_GetCameraInfo(This,pX,pY,pZ,lX,lY,lZ,width,height)	\
    ( (This)->lpVtbl -> GetCameraInfo(This,pX,pY,pZ,lX,lY,lZ,width,height) ) 

#define IAtlOld3DEngine_AdjustCameraOrthogonal(This,iOffset)	\
    ( (This)->lpVtbl -> AdjustCameraOrthogonal(This,iOffset) ) 

#define IAtlOld3DEngine_SetModelScale(This,fScale)	\
    ( (This)->lpVtbl -> SetModelScale(This,fScale) ) 

#define IAtlOld3DEngine_SaveModelToImageFile(This,fileName)	\
    ( (This)->lpVtbl -> SaveModelToImageFile(This,fileName) ) 

#define IAtlOld3DEngine_LoadSkillSfx(This,filename,scale,socketName,iIndex)	\
    ( (This)->lpVtbl -> LoadSkillSfx(This,filename,scale,socketName,iIndex) ) 

#define IAtlOld3DEngine_ReadMapTerrainInfo(This,ptrScene,width,height)	\
    ( (This)->lpVtbl -> ReadMapTerrainInfo(This,ptrScene,width,height) ) 

#define IAtlOld3DEngine_FileToImage(This,src3DFileName,desImageFileName)	\
    ( (This)->lpVtbl -> FileToImage(This,src3DFileName,desImageFileName) ) 

#define IAtlOld3DEngine_GetCurSceneIndex(This,index)	\
    ( (This)->lpVtbl -> GetCurSceneIndex(This,index) ) 

#define IAtlOld3DEngine_ActivateSceneByIndex(This,index)	\
    ( (This)->lpVtbl -> ActivateSceneByIndex(This,index) ) 

#define IAtlOld3DEngine_SaveMdlWithAniToImages(This,ptrModel,filename)	\
    ( (This)->lpVtbl -> SaveMdlWithAniToImages(This,ptrModel,filename) ) 

#define IAtlOld3DEngine_SaveLogicScene(This,iniFile,ptr3DScene)	\
    ( (This)->lpVtbl -> SaveLogicScene(This,iniFile,ptr3DScene) ) 

#define IAtlOld3DEngine_ShowProgressForm(This,bShow)	\
    ( (This)->lpVtbl -> ShowProgressForm(This,bShow) ) 

#define IAtlOld3DEngine_UnloadPlayerModel(This)	\
    ( (This)->lpVtbl -> UnloadPlayerModel(This) ) 

#define IAtlOld3DEngine_GetHeight(This,ptrScene,x,z,y)	\
    ( (This)->lpVtbl -> GetHeight(This,ptrScene,x,z,y) ) 

#define IAtlOld3DEngine_GetFileNameHash(This,fileName,hashid)	\
    ( (This)->lpVtbl -> GetFileNameHash(This,fileName,hashid) ) 

#define IAtlOld3DEngine_QuaternionRotationByNDir(This,x,y,z,w,nDir)	\
    ( (This)->lpVtbl -> QuaternionRotationByNDir(This,x,y,z,w,nDir) ) 

#define IAtlOld3DEngine_LoadPluginMaterial(This,strSocketName,strMtlFile)	\
    ( (This)->lpVtbl -> LoadPluginMaterial(This,strSocketName,strMtlFile) ) 

#define IAtlOld3DEngine_GetAniFrameCount(This,strAniFileName,count)	\
    ( (This)->lpVtbl -> GetAniFrameCount(This,strAniFileName,count) ) 

#define IAtlOld3DEngine_LoadPlaneForSelector(This,strFileName)	\
    ( (This)->lpVtbl -> LoadPlaneForSelector(This,strFileName) ) 

#define IAtlOld3DEngine_SetCaptionHeight(This,fHeight)	\
    ( (This)->lpVtbl -> SetCaptionHeight(This,fHeight) ) 

#define IAtlOld3DEngine_SetCaptionText(This,strName,strTitle)	\
    ( (This)->lpVtbl -> SetCaptionText(This,strName,strTitle) ) 

#define IAtlOld3DEngine_GetBBoxXY(This,mdl,x,y)	\
    ( (This)->lpVtbl -> GetBBoxXY(This,mdl,x,y) ) 

#define IAtlOld3DEngine_GetMdlBBoxMax2DLength(This,mdl,pVal)	\
    ( (This)->lpVtbl -> GetMdlBBoxMax2DLength(This,mdl,pVal) ) 

#define IAtlOld3DEngine_GetEditorSceneSize(This,ptrScene,width,height)	\
    ( (This)->lpVtbl -> GetEditorSceneSize(This,ptrScene,width,height) ) 

#define IAtlOld3DEngine_ToggleEngine(This)	\
    ( (This)->lpVtbl -> ToggleEngine(This) ) 

#define IAtlOld3DEngine_SetAllPluginModelScale(This,fScale)	\
    ( (This)->lpVtbl -> SetAllPluginModelScale(This,fScale) ) 

#define IAtlOld3DEngine_LoadNPCMarkSfxFile(This,sfx_name,fHeight)	\
    ( (This)->lpVtbl -> LoadNPCMarkSfxFile(This,sfx_name,fHeight) ) 

#define IAtlOld3DEngine_GetInitInfo(This,hwndBase,strEnginePath,strStartUpPath)	\
    ( (This)->lpVtbl -> GetInitInfo(This,hwndBase,strEnginePath,strStartUpPath) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAtlOld3DEngine_INTERFACE_DEFINED__ */


#ifndef __IAtlIEKSceneEditorDocLogical_INTERFACE_DEFINED__
#define __IAtlIEKSceneEditorDocLogical_INTERFACE_DEFINED__

/* interface IAtlIEKSceneEditorDocLogical */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAtlIEKSceneEditorDocLogical;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C5B1C478-FD08-400A-834E-D466ED75F316")
    IAtlIEKSceneEditorDocLogical : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetObjCount( 
            /* [in] */ BSTR ObjType,
            /* [in] */ LONG fatherindex,
            LONG *ObjCount) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetObjDisplayInfo( 
            /* [in] */ BSTR ObjType,
            /* [in] */ LONG index,
            /* [in] */ LONG fatherindex,
            BSTR *name,
            BSTR *nickname,
            LONG *hasscript,
            LONG *representObjPtr,
            LONG *logicObjPtr,
            LONG *templateID) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetSelectedLogicObjPtr( 
            /* [in] */ LONG index,
            LONG *logicObjPtr,
            BSTR *ObjType) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetSetObjInfo( 
            /* [in] */ BSTR ObjType,
            AtlObjInfo *objInfo,
            /* [in] */ LONG logicObj,
            /* [in] */ LONG bGet) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE UpdateObjRepresentByLogicObj( 
            AtlObjInfo *objInfo,
            /* [in] */ LONG logicObj) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DecoratedAddOneWayPointSet( 
            LONG *ppNewSet,
            BSTR pName) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DecoratedDeleteWayPointSet( 
            LONG pSet) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddOneWayPoint( 
            LONG wayPointSetID,
            BSTR pName) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE RefreshWayPoint( 
            LONG wayPointPtr,
            INT nType) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddOneBigTrafficPoint( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DecoratedAddOneTrafficPointSet( 
            int trafficID,
            INT bAddPoint) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeleteTrafficPointAndSet( 
            LONG pSelectedObject,
            INT bDeletePoint) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE InsertTrafficPoint( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE RefreshTraffic( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE RefreshWay( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DecoratedNewOneNpcReviveGroup( 
            LONG *dwID,
            BSTR pName,
            int nMin,
            int nMax) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DecoratedNewOneDoodadReviveGroup( 
            LONG *dwID,
            BSTR pName,
            int nMin,
            int nMax) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DecoratedDeleteNpcReviveGroup( 
            LONG dwID) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DecoratedDeleteDoodadReviveGroup( 
            LONG dwID) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeleteSelectedObject( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddOneNewLogicalBrush( 
            LONG *nID) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE EditOneLogicalBrush( 
            LONG nID,
            LONG color,
            BSTR name,
            BSTR script,
            LONG modifyState,
            AtlVector3 *pos) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeleteOneLogicalBrush( 
            LONG nID) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeleteAllLogicalBrush( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeleteSelectedPoly( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetNpcAIParameterInfo( 
            int npcIndex,
            BSTR *infoString) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE UpdateNpcAIParameter( 
            int npcIndex,
            BSTR parameterName,
            int parameterValue) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetMainViewHwnd( 
            LONG iHwnd) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ResortNpcOrderInPatrolPath( 
            INT patrolPathID) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DecoratedNewOneRandomGroup( 
            BSTR groupName,
            BSTR templateInfo) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DecoratedDeleteRandomGroup( 
            INT groupID) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DecoratedAddOneAIGroup( 
            BSTR groupName,
            BSTR groupInfo) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetAIGroupInfo( 
            INT groupID,
            BSTR *infoString) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddNpcToAIGroup( 
            INT npcIndex,
            INT groupID) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DecoratedRemoveNPCFromAIGroup( 
            INT npcIndex) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DecoratedDeleteAIGroup( 
            INT groupID) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetRandomGroupInfo( 
            INT groupID,
            BSTR *groupInfo) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetAIParameterGroupInfo( 
            BSTR *info) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DecoratedSetDoodadReviveGroup( 
            INT groupID,
            BSTR groupName,
            INT minCount,
            INT maxCount) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DecoratedSetNpcReviveGroup( 
            INT groupID,
            BSTR groupName,
            INT minCount,
            INT maxCount) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DecoratedSetRandomGroup( 
            INT groupID,
            BSTR groupName,
            BSTR groupInfo) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DecoratedSetAIGroup( 
            INT groupID,
            BSTR groupName) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetAIParameterSetInfo( 
            INT setID,
            BSTR *info) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ReplaceNpcTemplate( 
            INT templateID,
            BOOL replaceAll) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ReplaceDoodadTemplate( 
            INT templateID,
            BOOL replaceAll) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAtlIEKSceneEditorDocLogicalVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAtlIEKSceneEditorDocLogical * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAtlIEKSceneEditorDocLogical * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAtlIEKSceneEditorDocLogical * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetObjCount )( 
            IAtlIEKSceneEditorDocLogical * This,
            /* [in] */ BSTR ObjType,
            /* [in] */ LONG fatherindex,
            LONG *ObjCount);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetObjDisplayInfo )( 
            IAtlIEKSceneEditorDocLogical * This,
            /* [in] */ BSTR ObjType,
            /* [in] */ LONG index,
            /* [in] */ LONG fatherindex,
            BSTR *name,
            BSTR *nickname,
            LONG *hasscript,
            LONG *representObjPtr,
            LONG *logicObjPtr,
            LONG *templateID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetSelectedLogicObjPtr )( 
            IAtlIEKSceneEditorDocLogical * This,
            /* [in] */ LONG index,
            LONG *logicObjPtr,
            BSTR *ObjType);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetSetObjInfo )( 
            IAtlIEKSceneEditorDocLogical * This,
            /* [in] */ BSTR ObjType,
            AtlObjInfo *objInfo,
            /* [in] */ LONG logicObj,
            /* [in] */ LONG bGet);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *UpdateObjRepresentByLogicObj )( 
            IAtlIEKSceneEditorDocLogical * This,
            AtlObjInfo *objInfo,
            /* [in] */ LONG logicObj);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DecoratedAddOneWayPointSet )( 
            IAtlIEKSceneEditorDocLogical * This,
            LONG *ppNewSet,
            BSTR pName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DecoratedDeleteWayPointSet )( 
            IAtlIEKSceneEditorDocLogical * This,
            LONG pSet);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddOneWayPoint )( 
            IAtlIEKSceneEditorDocLogical * This,
            LONG wayPointSetID,
            BSTR pName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *RefreshWayPoint )( 
            IAtlIEKSceneEditorDocLogical * This,
            LONG wayPointPtr,
            INT nType);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddOneBigTrafficPoint )( 
            IAtlIEKSceneEditorDocLogical * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DecoratedAddOneTrafficPointSet )( 
            IAtlIEKSceneEditorDocLogical * This,
            int trafficID,
            INT bAddPoint);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DeleteTrafficPointAndSet )( 
            IAtlIEKSceneEditorDocLogical * This,
            LONG pSelectedObject,
            INT bDeletePoint);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *InsertTrafficPoint )( 
            IAtlIEKSceneEditorDocLogical * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *RefreshTraffic )( 
            IAtlIEKSceneEditorDocLogical * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *RefreshWay )( 
            IAtlIEKSceneEditorDocLogical * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DecoratedNewOneNpcReviveGroup )( 
            IAtlIEKSceneEditorDocLogical * This,
            LONG *dwID,
            BSTR pName,
            int nMin,
            int nMax);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DecoratedNewOneDoodadReviveGroup )( 
            IAtlIEKSceneEditorDocLogical * This,
            LONG *dwID,
            BSTR pName,
            int nMin,
            int nMax);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DecoratedDeleteNpcReviveGroup )( 
            IAtlIEKSceneEditorDocLogical * This,
            LONG dwID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DecoratedDeleteDoodadReviveGroup )( 
            IAtlIEKSceneEditorDocLogical * This,
            LONG dwID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DeleteSelectedObject )( 
            IAtlIEKSceneEditorDocLogical * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddOneNewLogicalBrush )( 
            IAtlIEKSceneEditorDocLogical * This,
            LONG *nID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *EditOneLogicalBrush )( 
            IAtlIEKSceneEditorDocLogical * This,
            LONG nID,
            LONG color,
            BSTR name,
            BSTR script,
            LONG modifyState,
            AtlVector3 *pos);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DeleteOneLogicalBrush )( 
            IAtlIEKSceneEditorDocLogical * This,
            LONG nID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DeleteAllLogicalBrush )( 
            IAtlIEKSceneEditorDocLogical * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DeleteSelectedPoly )( 
            IAtlIEKSceneEditorDocLogical * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetNpcAIParameterInfo )( 
            IAtlIEKSceneEditorDocLogical * This,
            int npcIndex,
            BSTR *infoString);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *UpdateNpcAIParameter )( 
            IAtlIEKSceneEditorDocLogical * This,
            int npcIndex,
            BSTR parameterName,
            int parameterValue);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetMainViewHwnd )( 
            IAtlIEKSceneEditorDocLogical * This,
            LONG iHwnd);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ResortNpcOrderInPatrolPath )( 
            IAtlIEKSceneEditorDocLogical * This,
            INT patrolPathID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DecoratedNewOneRandomGroup )( 
            IAtlIEKSceneEditorDocLogical * This,
            BSTR groupName,
            BSTR templateInfo);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DecoratedDeleteRandomGroup )( 
            IAtlIEKSceneEditorDocLogical * This,
            INT groupID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DecoratedAddOneAIGroup )( 
            IAtlIEKSceneEditorDocLogical * This,
            BSTR groupName,
            BSTR groupInfo);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetAIGroupInfo )( 
            IAtlIEKSceneEditorDocLogical * This,
            INT groupID,
            BSTR *infoString);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddNpcToAIGroup )( 
            IAtlIEKSceneEditorDocLogical * This,
            INT npcIndex,
            INT groupID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DecoratedRemoveNPCFromAIGroup )( 
            IAtlIEKSceneEditorDocLogical * This,
            INT npcIndex);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DecoratedDeleteAIGroup )( 
            IAtlIEKSceneEditorDocLogical * This,
            INT groupID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetRandomGroupInfo )( 
            IAtlIEKSceneEditorDocLogical * This,
            INT groupID,
            BSTR *groupInfo);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetAIParameterGroupInfo )( 
            IAtlIEKSceneEditorDocLogical * This,
            BSTR *info);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DecoratedSetDoodadReviveGroup )( 
            IAtlIEKSceneEditorDocLogical * This,
            INT groupID,
            BSTR groupName,
            INT minCount,
            INT maxCount);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DecoratedSetNpcReviveGroup )( 
            IAtlIEKSceneEditorDocLogical * This,
            INT groupID,
            BSTR groupName,
            INT minCount,
            INT maxCount);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DecoratedSetRandomGroup )( 
            IAtlIEKSceneEditorDocLogical * This,
            INT groupID,
            BSTR groupName,
            BSTR groupInfo);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DecoratedSetAIGroup )( 
            IAtlIEKSceneEditorDocLogical * This,
            INT groupID,
            BSTR groupName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetAIParameterSetInfo )( 
            IAtlIEKSceneEditorDocLogical * This,
            INT setID,
            BSTR *info);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ReplaceNpcTemplate )( 
            IAtlIEKSceneEditorDocLogical * This,
            INT templateID,
            BOOL replaceAll);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ReplaceDoodadTemplate )( 
            IAtlIEKSceneEditorDocLogical * This,
            INT templateID,
            BOOL replaceAll);
        
        END_INTERFACE
    } IAtlIEKSceneEditorDocLogicalVtbl;

    interface IAtlIEKSceneEditorDocLogical
    {
        CONST_VTBL struct IAtlIEKSceneEditorDocLogicalVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAtlIEKSceneEditorDocLogical_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAtlIEKSceneEditorDocLogical_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAtlIEKSceneEditorDocLogical_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAtlIEKSceneEditorDocLogical_GetObjCount(This,ObjType,fatherindex,ObjCount)	\
    ( (This)->lpVtbl -> GetObjCount(This,ObjType,fatherindex,ObjCount) ) 

#define IAtlIEKSceneEditorDocLogical_GetObjDisplayInfo(This,ObjType,index,fatherindex,name,nickname,hasscript,representObjPtr,logicObjPtr,templateID)	\
    ( (This)->lpVtbl -> GetObjDisplayInfo(This,ObjType,index,fatherindex,name,nickname,hasscript,representObjPtr,logicObjPtr,templateID) ) 

#define IAtlIEKSceneEditorDocLogical_GetSelectedLogicObjPtr(This,index,logicObjPtr,ObjType)	\
    ( (This)->lpVtbl -> GetSelectedLogicObjPtr(This,index,logicObjPtr,ObjType) ) 

#define IAtlIEKSceneEditorDocLogical_GetSetObjInfo(This,ObjType,objInfo,logicObj,bGet)	\
    ( (This)->lpVtbl -> GetSetObjInfo(This,ObjType,objInfo,logicObj,bGet) ) 

#define IAtlIEKSceneEditorDocLogical_UpdateObjRepresentByLogicObj(This,objInfo,logicObj)	\
    ( (This)->lpVtbl -> UpdateObjRepresentByLogicObj(This,objInfo,logicObj) ) 

#define IAtlIEKSceneEditorDocLogical_DecoratedAddOneWayPointSet(This,ppNewSet,pName)	\
    ( (This)->lpVtbl -> DecoratedAddOneWayPointSet(This,ppNewSet,pName) ) 

#define IAtlIEKSceneEditorDocLogical_DecoratedDeleteWayPointSet(This,pSet)	\
    ( (This)->lpVtbl -> DecoratedDeleteWayPointSet(This,pSet) ) 

#define IAtlIEKSceneEditorDocLogical_AddOneWayPoint(This,wayPointSetID,pName)	\
    ( (This)->lpVtbl -> AddOneWayPoint(This,wayPointSetID,pName) ) 

#define IAtlIEKSceneEditorDocLogical_RefreshWayPoint(This,wayPointPtr,nType)	\
    ( (This)->lpVtbl -> RefreshWayPoint(This,wayPointPtr,nType) ) 

#define IAtlIEKSceneEditorDocLogical_AddOneBigTrafficPoint(This)	\
    ( (This)->lpVtbl -> AddOneBigTrafficPoint(This) ) 

#define IAtlIEKSceneEditorDocLogical_DecoratedAddOneTrafficPointSet(This,trafficID,bAddPoint)	\
    ( (This)->lpVtbl -> DecoratedAddOneTrafficPointSet(This,trafficID,bAddPoint) ) 

#define IAtlIEKSceneEditorDocLogical_DeleteTrafficPointAndSet(This,pSelectedObject,bDeletePoint)	\
    ( (This)->lpVtbl -> DeleteTrafficPointAndSet(This,pSelectedObject,bDeletePoint) ) 

#define IAtlIEKSceneEditorDocLogical_InsertTrafficPoint(This)	\
    ( (This)->lpVtbl -> InsertTrafficPoint(This) ) 

#define IAtlIEKSceneEditorDocLogical_RefreshTraffic(This)	\
    ( (This)->lpVtbl -> RefreshTraffic(This) ) 

#define IAtlIEKSceneEditorDocLogical_RefreshWay(This)	\
    ( (This)->lpVtbl -> RefreshWay(This) ) 

#define IAtlIEKSceneEditorDocLogical_DecoratedNewOneNpcReviveGroup(This,dwID,pName,nMin,nMax)	\
    ( (This)->lpVtbl -> DecoratedNewOneNpcReviveGroup(This,dwID,pName,nMin,nMax) ) 

#define IAtlIEKSceneEditorDocLogical_DecoratedNewOneDoodadReviveGroup(This,dwID,pName,nMin,nMax)	\
    ( (This)->lpVtbl -> DecoratedNewOneDoodadReviveGroup(This,dwID,pName,nMin,nMax) ) 

#define IAtlIEKSceneEditorDocLogical_DecoratedDeleteNpcReviveGroup(This,dwID)	\
    ( (This)->lpVtbl -> DecoratedDeleteNpcReviveGroup(This,dwID) ) 

#define IAtlIEKSceneEditorDocLogical_DecoratedDeleteDoodadReviveGroup(This,dwID)	\
    ( (This)->lpVtbl -> DecoratedDeleteDoodadReviveGroup(This,dwID) ) 

#define IAtlIEKSceneEditorDocLogical_DeleteSelectedObject(This)	\
    ( (This)->lpVtbl -> DeleteSelectedObject(This) ) 

#define IAtlIEKSceneEditorDocLogical_AddOneNewLogicalBrush(This,nID)	\
    ( (This)->lpVtbl -> AddOneNewLogicalBrush(This,nID) ) 

#define IAtlIEKSceneEditorDocLogical_EditOneLogicalBrush(This,nID,color,name,script,modifyState,pos)	\
    ( (This)->lpVtbl -> EditOneLogicalBrush(This,nID,color,name,script,modifyState,pos) ) 

#define IAtlIEKSceneEditorDocLogical_DeleteOneLogicalBrush(This,nID)	\
    ( (This)->lpVtbl -> DeleteOneLogicalBrush(This,nID) ) 

#define IAtlIEKSceneEditorDocLogical_DeleteAllLogicalBrush(This)	\
    ( (This)->lpVtbl -> DeleteAllLogicalBrush(This) ) 

#define IAtlIEKSceneEditorDocLogical_DeleteSelectedPoly(This)	\
    ( (This)->lpVtbl -> DeleteSelectedPoly(This) ) 

#define IAtlIEKSceneEditorDocLogical_GetNpcAIParameterInfo(This,npcIndex,infoString)	\
    ( (This)->lpVtbl -> GetNpcAIParameterInfo(This,npcIndex,infoString) ) 

#define IAtlIEKSceneEditorDocLogical_UpdateNpcAIParameter(This,npcIndex,parameterName,parameterValue)	\
    ( (This)->lpVtbl -> UpdateNpcAIParameter(This,npcIndex,parameterName,parameterValue) ) 

#define IAtlIEKSceneEditorDocLogical_SetMainViewHwnd(This,iHwnd)	\
    ( (This)->lpVtbl -> SetMainViewHwnd(This,iHwnd) ) 

#define IAtlIEKSceneEditorDocLogical_ResortNpcOrderInPatrolPath(This,patrolPathID)	\
    ( (This)->lpVtbl -> ResortNpcOrderInPatrolPath(This,patrolPathID) ) 

#define IAtlIEKSceneEditorDocLogical_DecoratedNewOneRandomGroup(This,groupName,templateInfo)	\
    ( (This)->lpVtbl -> DecoratedNewOneRandomGroup(This,groupName,templateInfo) ) 

#define IAtlIEKSceneEditorDocLogical_DecoratedDeleteRandomGroup(This,groupID)	\
    ( (This)->lpVtbl -> DecoratedDeleteRandomGroup(This,groupID) ) 

#define IAtlIEKSceneEditorDocLogical_DecoratedAddOneAIGroup(This,groupName,groupInfo)	\
    ( (This)->lpVtbl -> DecoratedAddOneAIGroup(This,groupName,groupInfo) ) 

#define IAtlIEKSceneEditorDocLogical_GetAIGroupInfo(This,groupID,infoString)	\
    ( (This)->lpVtbl -> GetAIGroupInfo(This,groupID,infoString) ) 

#define IAtlIEKSceneEditorDocLogical_AddNpcToAIGroup(This,npcIndex,groupID)	\
    ( (This)->lpVtbl -> AddNpcToAIGroup(This,npcIndex,groupID) ) 

#define IAtlIEKSceneEditorDocLogical_DecoratedRemoveNPCFromAIGroup(This,npcIndex)	\
    ( (This)->lpVtbl -> DecoratedRemoveNPCFromAIGroup(This,npcIndex) ) 

#define IAtlIEKSceneEditorDocLogical_DecoratedDeleteAIGroup(This,groupID)	\
    ( (This)->lpVtbl -> DecoratedDeleteAIGroup(This,groupID) ) 

#define IAtlIEKSceneEditorDocLogical_GetRandomGroupInfo(This,groupID,groupInfo)	\
    ( (This)->lpVtbl -> GetRandomGroupInfo(This,groupID,groupInfo) ) 

#define IAtlIEKSceneEditorDocLogical_GetAIParameterGroupInfo(This,info)	\
    ( (This)->lpVtbl -> GetAIParameterGroupInfo(This,info) ) 

#define IAtlIEKSceneEditorDocLogical_DecoratedSetDoodadReviveGroup(This,groupID,groupName,minCount,maxCount)	\
    ( (This)->lpVtbl -> DecoratedSetDoodadReviveGroup(This,groupID,groupName,minCount,maxCount) ) 

#define IAtlIEKSceneEditorDocLogical_DecoratedSetNpcReviveGroup(This,groupID,groupName,minCount,maxCount)	\
    ( (This)->lpVtbl -> DecoratedSetNpcReviveGroup(This,groupID,groupName,minCount,maxCount) ) 

#define IAtlIEKSceneEditorDocLogical_DecoratedSetRandomGroup(This,groupID,groupName,groupInfo)	\
    ( (This)->lpVtbl -> DecoratedSetRandomGroup(This,groupID,groupName,groupInfo) ) 

#define IAtlIEKSceneEditorDocLogical_DecoratedSetAIGroup(This,groupID,groupName)	\
    ( (This)->lpVtbl -> DecoratedSetAIGroup(This,groupID,groupName) ) 

#define IAtlIEKSceneEditorDocLogical_GetAIParameterSetInfo(This,setID,info)	\
    ( (This)->lpVtbl -> GetAIParameterSetInfo(This,setID,info) ) 

#define IAtlIEKSceneEditorDocLogical_ReplaceNpcTemplate(This,templateID,replaceAll)	\
    ( (This)->lpVtbl -> ReplaceNpcTemplate(This,templateID,replaceAll) ) 

#define IAtlIEKSceneEditorDocLogical_ReplaceDoodadTemplate(This,templateID,replaceAll)	\
    ( (This)->lpVtbl -> ReplaceDoodadTemplate(This,templateID,replaceAll) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAtlIEKSceneEditorDocLogical_INTERFACE_DEFINED__ */


#ifndef __IAtlBase_INTERFACE_DEFINED__
#define __IAtlBase_INTERFACE_DEFINED__

/* interface IAtlBase */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAtlBase;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C5B1C478-FD08-400A-834E-D466ED75F315")
    IAtlBase : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Init3DEngineManager( 
            BSTR strStartUpPath,
            LONG ihWnd) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE UnInitEngine( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FrameMove( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Render( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ProcessMessage( 
            ULONG message,
            LONG wParam,
            LONG lParam) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetSO3World( 
            ISO3World **ptr) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE InitGlobalVars( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ShowProgressForm( 
            LONG bShow) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ShowTopViewForm( 
            LONG bShow) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE InitLogicalEditorBase( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE InitKeyStateBuf( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE UpdateKeyState( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetFocusScene( 
            LONG pScene) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE MsgOnMouseWheel( 
            SHORT nDelta) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetDefWorkingDir( 
            /* [in] */ BSTR strDir) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetSceneEditorCameraTopScale( 
            /* [retval][out] */ FLOAT *fScale) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetCurDir( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE QuaternionRotationByNDir( 
            FLOAT *x,
            FLOAT *y,
            FLOAT *z,
            FLOAT *w,
            LONG nDir) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetRepresentObjTranslation( 
            /* [in] */ LONG representObjPtr,
            AtlVector3 *vec) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE LoadNpcScene( 
            LONG hwndOutput) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE LoadDoodadScene( 
            LONG hwndOutput) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FocusNpcScene( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE FocusDoodadScene( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE LoadNpcModel( 
            BSTR fileName) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE LoadFace( 
            BSTR meshFileName) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE LoadPluginModel( 
            BSTR strFileName,
            BSTR strBindDest) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE LoadPluginMaterial( 
            BSTR strSocketName,
            BSTR strMtlFile) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE LoadDoodadModel( 
            BSTR fileName) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnWndMsg( 
            PMSG WndMsg,
            INT *pnRet,
            BSTR preViewType) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnResizeNpcWindow( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnResizeDoodadWindow( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ModelPlayAnimation( 
            BSTR fileName) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SwitchNpcBrush( 
            LONG nTemplateID,
            BSTR szNpcName,
            LONG dwDefaultReliveID,
            LONG dwDefaultRandomID,
            LONG dwDefaultAISet) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SwitchDoodadBrush( 
            LONG nTemplateID,
            BSTR szDoodadName,
            LONG dwDefaultReliveID) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE QuaternionNDirByRotation( 
            FLOAT x,
            FLOAT y,
            FLOAT z,
            FLOAT w,
            LONG *nDir) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetRootPath( 
            /* [in] */ BSTR str3DEngineDir) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetShowProfile( 
            /* [in] */ BOOL bShow) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAtlBaseVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAtlBase * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAtlBase * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAtlBase * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Init3DEngineManager )( 
            IAtlBase * This,
            BSTR strStartUpPath,
            LONG ihWnd);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *UnInitEngine )( 
            IAtlBase * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FrameMove )( 
            IAtlBase * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Render )( 
            IAtlBase * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ProcessMessage )( 
            IAtlBase * This,
            ULONG message,
            LONG wParam,
            LONG lParam);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetSO3World )( 
            IAtlBase * This,
            ISO3World **ptr);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *InitGlobalVars )( 
            IAtlBase * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ShowProgressForm )( 
            IAtlBase * This,
            LONG bShow);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ShowTopViewForm )( 
            IAtlBase * This,
            LONG bShow);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *InitLogicalEditorBase )( 
            IAtlBase * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *InitKeyStateBuf )( 
            IAtlBase * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *UpdateKeyState )( 
            IAtlBase * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetFocusScene )( 
            IAtlBase * This,
            LONG pScene);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *MsgOnMouseWheel )( 
            IAtlBase * This,
            SHORT nDelta);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetDefWorkingDir )( 
            IAtlBase * This,
            /* [in] */ BSTR strDir);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetSceneEditorCameraTopScale )( 
            IAtlBase * This,
            /* [retval][out] */ FLOAT *fScale);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetCurDir )( 
            IAtlBase * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *QuaternionRotationByNDir )( 
            IAtlBase * This,
            FLOAT *x,
            FLOAT *y,
            FLOAT *z,
            FLOAT *w,
            LONG nDir);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetRepresentObjTranslation )( 
            IAtlBase * This,
            /* [in] */ LONG representObjPtr,
            AtlVector3 *vec);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *LoadNpcScene )( 
            IAtlBase * This,
            LONG hwndOutput);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *LoadDoodadScene )( 
            IAtlBase * This,
            LONG hwndOutput);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FocusNpcScene )( 
            IAtlBase * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *FocusDoodadScene )( 
            IAtlBase * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *LoadNpcModel )( 
            IAtlBase * This,
            BSTR fileName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *LoadFace )( 
            IAtlBase * This,
            BSTR meshFileName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *LoadPluginModel )( 
            IAtlBase * This,
            BSTR strFileName,
            BSTR strBindDest);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *LoadPluginMaterial )( 
            IAtlBase * This,
            BSTR strSocketName,
            BSTR strMtlFile);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *LoadDoodadModel )( 
            IAtlBase * This,
            BSTR fileName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnWndMsg )( 
            IAtlBase * This,
            PMSG WndMsg,
            INT *pnRet,
            BSTR preViewType);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnResizeNpcWindow )( 
            IAtlBase * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnResizeDoodadWindow )( 
            IAtlBase * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ModelPlayAnimation )( 
            IAtlBase * This,
            BSTR fileName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SwitchNpcBrush )( 
            IAtlBase * This,
            LONG nTemplateID,
            BSTR szNpcName,
            LONG dwDefaultReliveID,
            LONG dwDefaultRandomID,
            LONG dwDefaultAISet);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SwitchDoodadBrush )( 
            IAtlBase * This,
            LONG nTemplateID,
            BSTR szDoodadName,
            LONG dwDefaultReliveID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *QuaternionNDirByRotation )( 
            IAtlBase * This,
            FLOAT x,
            FLOAT y,
            FLOAT z,
            FLOAT w,
            LONG *nDir);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetRootPath )( 
            IAtlBase * This,
            /* [in] */ BSTR str3DEngineDir);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetShowProfile )( 
            IAtlBase * This,
            /* [in] */ BOOL bShow);
        
        END_INTERFACE
    } IAtlBaseVtbl;

    interface IAtlBase
    {
        CONST_VTBL struct IAtlBaseVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAtlBase_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAtlBase_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAtlBase_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAtlBase_Init3DEngineManager(This,strStartUpPath,ihWnd)	\
    ( (This)->lpVtbl -> Init3DEngineManager(This,strStartUpPath,ihWnd) ) 

#define IAtlBase_UnInitEngine(This)	\
    ( (This)->lpVtbl -> UnInitEngine(This) ) 

#define IAtlBase_FrameMove(This)	\
    ( (This)->lpVtbl -> FrameMove(This) ) 

#define IAtlBase_Render(This)	\
    ( (This)->lpVtbl -> Render(This) ) 

#define IAtlBase_ProcessMessage(This,message,wParam,lParam)	\
    ( (This)->lpVtbl -> ProcessMessage(This,message,wParam,lParam) ) 

#define IAtlBase_GetSO3World(This,ptr)	\
    ( (This)->lpVtbl -> GetSO3World(This,ptr) ) 

#define IAtlBase_InitGlobalVars(This)	\
    ( (This)->lpVtbl -> InitGlobalVars(This) ) 

#define IAtlBase_ShowProgressForm(This,bShow)	\
    ( (This)->lpVtbl -> ShowProgressForm(This,bShow) ) 

#define IAtlBase_ShowTopViewForm(This,bShow)	\
    ( (This)->lpVtbl -> ShowTopViewForm(This,bShow) ) 

#define IAtlBase_InitLogicalEditorBase(This)	\
    ( (This)->lpVtbl -> InitLogicalEditorBase(This) ) 

#define IAtlBase_InitKeyStateBuf(This)	\
    ( (This)->lpVtbl -> InitKeyStateBuf(This) ) 

#define IAtlBase_UpdateKeyState(This)	\
    ( (This)->lpVtbl -> UpdateKeyState(This) ) 

#define IAtlBase_SetFocusScene(This,pScene)	\
    ( (This)->lpVtbl -> SetFocusScene(This,pScene) ) 

#define IAtlBase_MsgOnMouseWheel(This,nDelta)	\
    ( (This)->lpVtbl -> MsgOnMouseWheel(This,nDelta) ) 

#define IAtlBase_SetDefWorkingDir(This,strDir)	\
    ( (This)->lpVtbl -> SetDefWorkingDir(This,strDir) ) 

#define IAtlBase_GetSceneEditorCameraTopScale(This,fScale)	\
    ( (This)->lpVtbl -> GetSceneEditorCameraTopScale(This,fScale) ) 

#define IAtlBase_SetCurDir(This)	\
    ( (This)->lpVtbl -> SetCurDir(This) ) 

#define IAtlBase_QuaternionRotationByNDir(This,x,y,z,w,nDir)	\
    ( (This)->lpVtbl -> QuaternionRotationByNDir(This,x,y,z,w,nDir) ) 

#define IAtlBase_GetRepresentObjTranslation(This,representObjPtr,vec)	\
    ( (This)->lpVtbl -> GetRepresentObjTranslation(This,representObjPtr,vec) ) 

#define IAtlBase_LoadNpcScene(This,hwndOutput)	\
    ( (This)->lpVtbl -> LoadNpcScene(This,hwndOutput) ) 

#define IAtlBase_LoadDoodadScene(This,hwndOutput)	\
    ( (This)->lpVtbl -> LoadDoodadScene(This,hwndOutput) ) 

#define IAtlBase_FocusNpcScene(This)	\
    ( (This)->lpVtbl -> FocusNpcScene(This) ) 

#define IAtlBase_FocusDoodadScene(This)	\
    ( (This)->lpVtbl -> FocusDoodadScene(This) ) 

#define IAtlBase_LoadNpcModel(This,fileName)	\
    ( (This)->lpVtbl -> LoadNpcModel(This,fileName) ) 

#define IAtlBase_LoadFace(This,meshFileName)	\
    ( (This)->lpVtbl -> LoadFace(This,meshFileName) ) 

#define IAtlBase_LoadPluginModel(This,strFileName,strBindDest)	\
    ( (This)->lpVtbl -> LoadPluginModel(This,strFileName,strBindDest) ) 

#define IAtlBase_LoadPluginMaterial(This,strSocketName,strMtlFile)	\
    ( (This)->lpVtbl -> LoadPluginMaterial(This,strSocketName,strMtlFile) ) 

#define IAtlBase_LoadDoodadModel(This,fileName)	\
    ( (This)->lpVtbl -> LoadDoodadModel(This,fileName) ) 

#define IAtlBase_OnWndMsg(This,WndMsg,pnRet,preViewType)	\
    ( (This)->lpVtbl -> OnWndMsg(This,WndMsg,pnRet,preViewType) ) 

#define IAtlBase_OnResizeNpcWindow(This)	\
    ( (This)->lpVtbl -> OnResizeNpcWindow(This) ) 

#define IAtlBase_OnResizeDoodadWindow(This)	\
    ( (This)->lpVtbl -> OnResizeDoodadWindow(This) ) 

#define IAtlBase_ModelPlayAnimation(This,fileName)	\
    ( (This)->lpVtbl -> ModelPlayAnimation(This,fileName) ) 

#define IAtlBase_SwitchNpcBrush(This,nTemplateID,szNpcName,dwDefaultReliveID,dwDefaultRandomID,dwDefaultAISet)	\
    ( (This)->lpVtbl -> SwitchNpcBrush(This,nTemplateID,szNpcName,dwDefaultReliveID,dwDefaultRandomID,dwDefaultAISet) ) 

#define IAtlBase_SwitchDoodadBrush(This,nTemplateID,szDoodadName,dwDefaultReliveID)	\
    ( (This)->lpVtbl -> SwitchDoodadBrush(This,nTemplateID,szDoodadName,dwDefaultReliveID) ) 

#define IAtlBase_QuaternionNDirByRotation(This,x,y,z,w,nDir)	\
    ( (This)->lpVtbl -> QuaternionNDirByRotation(This,x,y,z,w,nDir) ) 

#define IAtlBase_SetRootPath(This,str3DEngineDir)	\
    ( (This)->lpVtbl -> SetRootPath(This,str3DEngineDir) ) 

#define IAtlBase_SetShowProfile(This,bShow)	\
    ( (This)->lpVtbl -> SetShowProfile(This,bShow) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAtlBase_INTERFACE_DEFINED__ */


#ifndef __IBaseLib_INTERFACE_DEFINED__
#define __IBaseLib_INTERFACE_DEFINED__

/* interface IBaseLib */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IBaseLib;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("04063539-583C-4CD9-A168-60E2A9B72428")
    IBaseLib : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE InitLog( 
            /* [in] */ BSTR szIdentity,
            /* [in] */ LONG nMaxlineEachFile,
            /* [in] */ LONG Options,
            /* [in] */ BSTR szPath) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE InitMemory( 
            /* [in] */ BSTR memoryName) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE UnInitMemory( void) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IBaseLibVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IBaseLib * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IBaseLib * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IBaseLib * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *InitLog )( 
            IBaseLib * This,
            /* [in] */ BSTR szIdentity,
            /* [in] */ LONG nMaxlineEachFile,
            /* [in] */ LONG Options,
            /* [in] */ BSTR szPath);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *InitMemory )( 
            IBaseLib * This,
            /* [in] */ BSTR memoryName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *UnInitMemory )( 
            IBaseLib * This);
        
        END_INTERFACE
    } IBaseLibVtbl;

    interface IBaseLib
    {
        CONST_VTBL struct IBaseLibVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IBaseLib_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IBaseLib_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IBaseLib_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IBaseLib_InitLog(This,szIdentity,nMaxlineEachFile,Options,szPath)	\
    ( (This)->lpVtbl -> InitLog(This,szIdentity,nMaxlineEachFile,Options,szPath) ) 

#define IBaseLib_InitMemory(This,memoryName)	\
    ( (This)->lpVtbl -> InitMemory(This,memoryName) ) 

#define IBaseLib_UnInitMemory(This)	\
    ( (This)->lpVtbl -> UnInitMemory(This) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IBaseLib_INTERFACE_DEFINED__ */


#ifndef __ISO3World_INTERFACE_DEFINED__
#define __ISO3World_INTERFACE_DEFINED__

/* interface ISO3World */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_ISO3World;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("BE4E2494-48B3-4F0B-A86A-06298C945D7F")
    ISO3World : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Init( 
            /* [in] */ LONG nWorldIndex) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE UnInit( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Activate( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE NewEditorScene( 
            /* [in] */ LONG nRegionWidth,
            /* [in] */ LONG nRegionHeight,
            /* [retval][out] */ LONG *pKScene) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE LoadEditorScene( 
            BSTR cszFileName) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE NewClientScene( 
            /* [in] */ ULONG dwMapID,
            /* [in] */ LONGLONG nMapCopyIndex,
            /* [retval][out] */ LONG *pKScene) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeleteScene( 
            /* [in] */ LONG *pScene) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetScene( 
            /* [in] */ LONG dwMapID,
            /* [in] */ LONGLONG nMapCopyIndex,
            /* [retval][out] */ LONG *pScene) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE NewNpc( 
            /* [in] */ LONG dwNpcID,
            /* [retval][out] */ LONG *pNpc) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeleteNpc( 
            /* [in] */ LONG *pNpc) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddNpc( 
            /* [in] */ LONG *pNpc,
            /* [in] */ LONG *pScene,
            /* [in] */ LONG nX,
            /* [in] */ LONG nY,
            /* [in] */ LONG nZ) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE RemoveNpc( 
            /* [in] */ LONG *pNpc,
            /* [in] */ LONG bKilled) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE NewDoodad( 
            /* [in] */ LONG dwDoodadID,
            /* [retval][out] */ LONG *pDoodad) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DelDoodad( 
            BYTE *pDoodad) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddDoodad( 
            /* [in] */ LONG *pDoodad,
            /* [in] */ LONG *pScene,
            /* [in] */ LONG nX,
            /* [in] */ LONG nY,
            /* [in] */ LONG nZ) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE RemoveDoodad( 
            /* [in] */ LONG *pDoodad) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE NewPlayer( 
            /* [in] */ LONG dwPlayerID,
            /* [retval][out] */ LONG *pPlayer) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DelPlayer( 
            /* [in] */ LONG *pPlayer) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddPlayer( 
            /* [in] */ LONG *pPlayer,
            /* [in] */ LONG *pScene,
            /* [in] */ LONG nX,
            /* [in] */ LONG nY,
            /* [in] */ LONG nZ) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE RemovePlayer( 
            /* [in] */ LONG *pPlayer) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AttachLogicalSceneTo3DScene( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE NewLogicSceneConnectionAndBindLogicalSceneAndSceneEditor( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE NewLogicalDataAndAdviseWithSceneEditor( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE LoadLogicalData( 
            /* [in] */ BSTR fileName) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SaveEditorIni( 
            /* [in] */ BSTR relaPath) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SaveCalcCollision( 
            /* [in] */ LONG bOnlyAppointCell,
            /* [in] */ LONG bClearCell) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE UpdateAllRest( 
            /* [in] */ LONG bRest) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SaveLogicalScene( 
            /* [in] */ BSTR fileName) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetLogicalDataPtr( 
            IAtlIEKSceneEditorDocLogical **ppLogicalData) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISO3WorldVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISO3World * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISO3World * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISO3World * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Init )( 
            ISO3World * This,
            /* [in] */ LONG nWorldIndex);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *UnInit )( 
            ISO3World * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Activate )( 
            ISO3World * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *NewEditorScene )( 
            ISO3World * This,
            /* [in] */ LONG nRegionWidth,
            /* [in] */ LONG nRegionHeight,
            /* [retval][out] */ LONG *pKScene);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *LoadEditorScene )( 
            ISO3World * This,
            BSTR cszFileName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *NewClientScene )( 
            ISO3World * This,
            /* [in] */ ULONG dwMapID,
            /* [in] */ LONGLONG nMapCopyIndex,
            /* [retval][out] */ LONG *pKScene);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DeleteScene )( 
            ISO3World * This,
            /* [in] */ LONG *pScene);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetScene )( 
            ISO3World * This,
            /* [in] */ LONG dwMapID,
            /* [in] */ LONGLONG nMapCopyIndex,
            /* [retval][out] */ LONG *pScene);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *NewNpc )( 
            ISO3World * This,
            /* [in] */ LONG dwNpcID,
            /* [retval][out] */ LONG *pNpc);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DeleteNpc )( 
            ISO3World * This,
            /* [in] */ LONG *pNpc);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddNpc )( 
            ISO3World * This,
            /* [in] */ LONG *pNpc,
            /* [in] */ LONG *pScene,
            /* [in] */ LONG nX,
            /* [in] */ LONG nY,
            /* [in] */ LONG nZ);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveNpc )( 
            ISO3World * This,
            /* [in] */ LONG *pNpc,
            /* [in] */ LONG bKilled);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *NewDoodad )( 
            ISO3World * This,
            /* [in] */ LONG dwDoodadID,
            /* [retval][out] */ LONG *pDoodad);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DelDoodad )( 
            ISO3World * This,
            BYTE *pDoodad);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddDoodad )( 
            ISO3World * This,
            /* [in] */ LONG *pDoodad,
            /* [in] */ LONG *pScene,
            /* [in] */ LONG nX,
            /* [in] */ LONG nY,
            /* [in] */ LONG nZ);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveDoodad )( 
            ISO3World * This,
            /* [in] */ LONG *pDoodad);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *NewPlayer )( 
            ISO3World * This,
            /* [in] */ LONG dwPlayerID,
            /* [retval][out] */ LONG *pPlayer);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DelPlayer )( 
            ISO3World * This,
            /* [in] */ LONG *pPlayer);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddPlayer )( 
            ISO3World * This,
            /* [in] */ LONG *pPlayer,
            /* [in] */ LONG *pScene,
            /* [in] */ LONG nX,
            /* [in] */ LONG nY,
            /* [in] */ LONG nZ);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemovePlayer )( 
            ISO3World * This,
            /* [in] */ LONG *pPlayer);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AttachLogicalSceneTo3DScene )( 
            ISO3World * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *NewLogicSceneConnectionAndBindLogicalSceneAndSceneEditor )( 
            ISO3World * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *NewLogicalDataAndAdviseWithSceneEditor )( 
            ISO3World * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *LoadLogicalData )( 
            ISO3World * This,
            /* [in] */ BSTR fileName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SaveEditorIni )( 
            ISO3World * This,
            /* [in] */ BSTR relaPath);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SaveCalcCollision )( 
            ISO3World * This,
            /* [in] */ LONG bOnlyAppointCell,
            /* [in] */ LONG bClearCell);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *UpdateAllRest )( 
            ISO3World * This,
            /* [in] */ LONG bRest);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SaveLogicalScene )( 
            ISO3World * This,
            /* [in] */ BSTR fileName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetLogicalDataPtr )( 
            ISO3World * This,
            IAtlIEKSceneEditorDocLogical **ppLogicalData);
        
        END_INTERFACE
    } ISO3WorldVtbl;

    interface ISO3World
    {
        CONST_VTBL struct ISO3WorldVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISO3World_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISO3World_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISO3World_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISO3World_Init(This,nWorldIndex)	\
    ( (This)->lpVtbl -> Init(This,nWorldIndex) ) 

#define ISO3World_UnInit(This)	\
    ( (This)->lpVtbl -> UnInit(This) ) 

#define ISO3World_Activate(This)	\
    ( (This)->lpVtbl -> Activate(This) ) 

#define ISO3World_NewEditorScene(This,nRegionWidth,nRegionHeight,pKScene)	\
    ( (This)->lpVtbl -> NewEditorScene(This,nRegionWidth,nRegionHeight,pKScene) ) 

#define ISO3World_LoadEditorScene(This,cszFileName)	\
    ( (This)->lpVtbl -> LoadEditorScene(This,cszFileName) ) 

#define ISO3World_NewClientScene(This,dwMapID,nMapCopyIndex,pKScene)	\
    ( (This)->lpVtbl -> NewClientScene(This,dwMapID,nMapCopyIndex,pKScene) ) 

#define ISO3World_DeleteScene(This,pScene)	\
    ( (This)->lpVtbl -> DeleteScene(This,pScene) ) 

#define ISO3World_GetScene(This,dwMapID,nMapCopyIndex,pScene)	\
    ( (This)->lpVtbl -> GetScene(This,dwMapID,nMapCopyIndex,pScene) ) 

#define ISO3World_NewNpc(This,dwNpcID,pNpc)	\
    ( (This)->lpVtbl -> NewNpc(This,dwNpcID,pNpc) ) 

#define ISO3World_DeleteNpc(This,pNpc)	\
    ( (This)->lpVtbl -> DeleteNpc(This,pNpc) ) 

#define ISO3World_AddNpc(This,pNpc,pScene,nX,nY,nZ)	\
    ( (This)->lpVtbl -> AddNpc(This,pNpc,pScene,nX,nY,nZ) ) 

#define ISO3World_RemoveNpc(This,pNpc,bKilled)	\
    ( (This)->lpVtbl -> RemoveNpc(This,pNpc,bKilled) ) 

#define ISO3World_NewDoodad(This,dwDoodadID,pDoodad)	\
    ( (This)->lpVtbl -> NewDoodad(This,dwDoodadID,pDoodad) ) 

#define ISO3World_DelDoodad(This,pDoodad)	\
    ( (This)->lpVtbl -> DelDoodad(This,pDoodad) ) 

#define ISO3World_AddDoodad(This,pDoodad,pScene,nX,nY,nZ)	\
    ( (This)->lpVtbl -> AddDoodad(This,pDoodad,pScene,nX,nY,nZ) ) 

#define ISO3World_RemoveDoodad(This,pDoodad)	\
    ( (This)->lpVtbl -> RemoveDoodad(This,pDoodad) ) 

#define ISO3World_NewPlayer(This,dwPlayerID,pPlayer)	\
    ( (This)->lpVtbl -> NewPlayer(This,dwPlayerID,pPlayer) ) 

#define ISO3World_DelPlayer(This,pPlayer)	\
    ( (This)->lpVtbl -> DelPlayer(This,pPlayer) ) 

#define ISO3World_AddPlayer(This,pPlayer,pScene,nX,nY,nZ)	\
    ( (This)->lpVtbl -> AddPlayer(This,pPlayer,pScene,nX,nY,nZ) ) 

#define ISO3World_RemovePlayer(This,pPlayer)	\
    ( (This)->lpVtbl -> RemovePlayer(This,pPlayer) ) 

#define ISO3World_AttachLogicalSceneTo3DScene(This)	\
    ( (This)->lpVtbl -> AttachLogicalSceneTo3DScene(This) ) 

#define ISO3World_NewLogicSceneConnectionAndBindLogicalSceneAndSceneEditor(This)	\
    ( (This)->lpVtbl -> NewLogicSceneConnectionAndBindLogicalSceneAndSceneEditor(This) ) 

#define ISO3World_NewLogicalDataAndAdviseWithSceneEditor(This)	\
    ( (This)->lpVtbl -> NewLogicalDataAndAdviseWithSceneEditor(This) ) 

#define ISO3World_LoadLogicalData(This,fileName)	\
    ( (This)->lpVtbl -> LoadLogicalData(This,fileName) ) 

#define ISO3World_SaveEditorIni(This,relaPath)	\
    ( (This)->lpVtbl -> SaveEditorIni(This,relaPath) ) 

#define ISO3World_SaveCalcCollision(This,bOnlyAppointCell,bClearCell)	\
    ( (This)->lpVtbl -> SaveCalcCollision(This,bOnlyAppointCell,bClearCell) ) 

#define ISO3World_UpdateAllRest(This,bRest)	\
    ( (This)->lpVtbl -> UpdateAllRest(This,bRest) ) 

#define ISO3World_SaveLogicalScene(This,fileName)	\
    ( (This)->lpVtbl -> SaveLogicalScene(This,fileName) ) 

#define ISO3World_GetLogicalDataPtr(This,ppLogicalData)	\
    ( (This)->lpVtbl -> GetLogicalDataPtr(This,ppLogicalData) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISO3World_INTERFACE_DEFINED__ */


#ifndef __IAtlInputProxy_INTERFACE_DEFINED__
#define __IAtlInputProxy_INTERFACE_DEFINED__

/* interface IAtlInputProxy */
/* [unique][helpstring][uuid][object] */ 


EXTERN_C const IID IID_IAtlInputProxy;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("C3A159AE-862B-40F1-9C27-1F562FE2D176")
    IAtlInputProxy : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE Init( 
            LONG hWnd) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE CheckInput( 
            PMSG pMsg,
            LONG *pnRet) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IAtlInputProxyVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAtlInputProxy * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAtlInputProxy * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAtlInputProxy * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *Init )( 
            IAtlInputProxy * This,
            LONG hWnd);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *CheckInput )( 
            IAtlInputProxy * This,
            PMSG pMsg,
            LONG *pnRet);
        
        END_INTERFACE
    } IAtlInputProxyVtbl;

    interface IAtlInputProxy
    {
        CONST_VTBL struct IAtlInputProxyVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAtlInputProxy_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAtlInputProxy_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAtlInputProxy_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAtlInputProxy_Init(This,hWnd)	\
    ( (This)->lpVtbl -> Init(This,hWnd) ) 

#define IAtlInputProxy_CheckInput(This,pMsg,pnRet)	\
    ( (This)->lpVtbl -> CheckInput(This,pMsg,pnRet) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IAtlInputProxy_INTERFACE_DEFINED__ */


#ifndef __ISceneEditor_INTERFACE_DEFINED__
#define __ISceneEditor_INTERFACE_DEFINED__

/* interface ISceneEditor */
/* [unique][helpstring][nonextensible][dual][uuid][object] */ 


EXTERN_C const IID IID_ISceneEditor;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("31B2DA9E-0A7C-4B9A-A7D4-F76F94B7FBDD")
    ISceneEditor : public IUnknown
    {
    public:
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddWindowing( 
            BSTR szName,
            LONG ihWnd,
            LONG iWindowType,
            LONG *windowid,
            ULONG editState) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE UpdateTopPosAsMainPos( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE RemoveWindowing( 
            LONG iWindowID) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetCameraTopScale( 
            /* [retval][out] */ FLOAT *scale) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetCameraTopScale( 
            FLOAT scale) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetCameraTopPos( 
            FLOAT x,
            FLOAT z) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetCameraTopPos( 
            AtlVector3 *pos) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetNPCPosition( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetCameraPosLookat( 
            AtlVector3 *pos,
            AtlVector3 *lookat) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetCameraPosLookat( 
            AtlVector3 *pos,
            AtlVector3 *lookat) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetCameraLocation( 
            FLOAT camerax,
            FLOAT cameray,
            FLOAT cameraz,
            FLOAT lookatx,
            FLOAT lookaty,
            FLOAT lookatz) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetSelectedEntityCount( 
            LONG *count) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetFullScreen( 
            BOOL bFullScreen) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE TogglePMode( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE IsPMode( 
            /* [retval][out] */ BOOL *isPMode) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE OnResizeWindow( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE RotateSelectedObject( 
            BSTR *newRotation) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetCameraSpeed( 
            FLOAT fPercent) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE NpcPlayNextAction( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE NpcPlayPreviousAction( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE UpdateSelectableEntityList( 
            LONG doCount) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ClearSelectedEntityList( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE AddSelectedRepresentObject( 
            LONG representObjPtr,
            LONG bAdd) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE BeginAddPolyVertex( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE EndAddPolyVertex( 
            ULONG dwType) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetPolyHeight( 
            FLOAT fHeight) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE EnableRenderPoly( 
            LONG bEnable) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetFocus( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetRenderBlockEdge( 
            BOOL bRenderEdge) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetCameraDis( 
            FLOAT fDis) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetFirstSelectedKing( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DropSelectedEntity( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ZoomToObj( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetEditorSceneSize( 
            LONG *width,
            LONG *height) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetObjectSelectMask( 
            DWORD nMask) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetCurrentOutputWindow( 
            LONG nWindowID) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetEditState( 
            /* [retval][out] */ LONG *nState) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetEditState( 
            LONG nState) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE EnableShowAppointLogicalRegion( 
            LONG bEnable) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetAppointLogicalRegion( 
            LONG xStart,
            LONG zStart,
            LONG xCount,
            LONG zCount) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetAppointLogicalRegion( 
            LONG *xStart,
            LONG *zStart,
            LONG *xCount,
            LONG *zCount) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE GetSetLogicDisplayParams( 
            LONG bGet,
            LONG *bShowCell,
            LONG *bShowTerrainCell,
            LONG *bShowItemCell,
            LONG *bShowSelectedCell) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ClearLogicModifyState( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetLogicModifyState( 
            LONG lstate,
            BSTR scriptName) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetLogicCurrentColor( 
            LONG color) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetLogicBrushParams( 
            LONG brushwidth,
            LONG brushtype,
            LONG displaywidth,
            LONG brushheight) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE SetCurrentEditBrushIndex( 
            LONG nIndex) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeleteCurrentCellInfo( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE DeleteSelectedEntity( void) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE ModifyCurrentCellInfo( 
            LONG oldInfo,
            LONG newInfo,
            BSTR oldScript,
            BSTR newScript) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE TransToEngineFormat( 
            LONG inMask,
            /* [retval][out] */ LONG *outMask) = 0;
        
        virtual /* [helpstring] */ HRESULT STDMETHODCALLTYPE BuildPolyAndSetInHand( 
            LONG VergeNum,
            FLOAT Radius,
            FLOAT Height,
            FLOAT Degree) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetSnapToolScale( 
            FLOAT fScale) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetSpeedTreeLeafScale( 
            FLOAT fScale) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE RenderSceneSnap( 
            BSTR fileName) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SetRenderTreeFlag( 
            LONG bFlag) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE AddRegionInfoManager( 
            BSTR fileName,
            LONG nPixelTolerance,
            LONG nSampleTimes,
            LONG nEliminateIsoDataCount,
            LONG nTotalValue,
            ULONG uHowManyPixelsInOneRegion,
            ULONG *dwHandle) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE ShowRegionInfoMap( 
            LONG ihWnd,
            ULONG dwHandle,
            LONG bShow) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE DelRegionInfoManager( 
            ULONG dwHandle) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE EnableRegionMask( 
            ULONG dwHandle,
            LONG nEnable) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetRegionMapInfo( 
            ULONG dwHandle,
            ULONG *puHeight,
            ULONG *puWidth,
            ULONG *puPixelPerRegion,
            ULONG *puRegionCount,
            ULONG *puMemorySize) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE GetRegionDiffValue( 
            ULONG dwHandle,
            ULONG uIndex,
            LONG *pnValue) = 0;
        
        virtual /* [helpstring][id] */ HRESULT STDMETHODCALLTYPE SaveRegionMap( 
            BSTR filePath,
            ULONG dwHandle) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct ISceneEditorVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ISceneEditor * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ISceneEditor * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ISceneEditor * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddWindowing )( 
            ISceneEditor * This,
            BSTR szName,
            LONG ihWnd,
            LONG iWindowType,
            LONG *windowid,
            ULONG editState);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *UpdateTopPosAsMainPos )( 
            ISceneEditor * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *RemoveWindowing )( 
            ISceneEditor * This,
            LONG iWindowID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetCameraTopScale )( 
            ISceneEditor * This,
            /* [retval][out] */ FLOAT *scale);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetCameraTopScale )( 
            ISceneEditor * This,
            FLOAT scale);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetCameraTopPos )( 
            ISceneEditor * This,
            FLOAT x,
            FLOAT z);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetCameraTopPos )( 
            ISceneEditor * This,
            AtlVector3 *pos);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetNPCPosition )( 
            ISceneEditor * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetCameraPosLookat )( 
            ISceneEditor * This,
            AtlVector3 *pos,
            AtlVector3 *lookat);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetCameraPosLookat )( 
            ISceneEditor * This,
            AtlVector3 *pos,
            AtlVector3 *lookat);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetCameraLocation )( 
            ISceneEditor * This,
            FLOAT camerax,
            FLOAT cameray,
            FLOAT cameraz,
            FLOAT lookatx,
            FLOAT lookaty,
            FLOAT lookatz);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetSelectedEntityCount )( 
            ISceneEditor * This,
            LONG *count);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetFullScreen )( 
            ISceneEditor * This,
            BOOL bFullScreen);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *TogglePMode )( 
            ISceneEditor * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *IsPMode )( 
            ISceneEditor * This,
            /* [retval][out] */ BOOL *isPMode);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *OnResizeWindow )( 
            ISceneEditor * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *RotateSelectedObject )( 
            ISceneEditor * This,
            BSTR *newRotation);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetCameraSpeed )( 
            ISceneEditor * This,
            FLOAT fPercent);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *NpcPlayNextAction )( 
            ISceneEditor * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *NpcPlayPreviousAction )( 
            ISceneEditor * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *UpdateSelectableEntityList )( 
            ISceneEditor * This,
            LONG doCount);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ClearSelectedEntityList )( 
            ISceneEditor * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *AddSelectedRepresentObject )( 
            ISceneEditor * This,
            LONG representObjPtr,
            LONG bAdd);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *BeginAddPolyVertex )( 
            ISceneEditor * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *EndAddPolyVertex )( 
            ISceneEditor * This,
            ULONG dwType);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetPolyHeight )( 
            ISceneEditor * This,
            FLOAT fHeight);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *EnableRenderPoly )( 
            ISceneEditor * This,
            LONG bEnable);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetFocus )( 
            ISceneEditor * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetRenderBlockEdge )( 
            ISceneEditor * This,
            BOOL bRenderEdge);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetCameraDis )( 
            ISceneEditor * This,
            FLOAT fDis);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetFirstSelectedKing )( 
            ISceneEditor * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DropSelectedEntity )( 
            ISceneEditor * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ZoomToObj )( 
            ISceneEditor * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetEditorSceneSize )( 
            ISceneEditor * This,
            LONG *width,
            LONG *height);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetObjectSelectMask )( 
            ISceneEditor * This,
            DWORD nMask);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetCurrentOutputWindow )( 
            ISceneEditor * This,
            LONG nWindowID);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetEditState )( 
            ISceneEditor * This,
            /* [retval][out] */ LONG *nState);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetEditState )( 
            ISceneEditor * This,
            LONG nState);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *EnableShowAppointLogicalRegion )( 
            ISceneEditor * This,
            LONG bEnable);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetAppointLogicalRegion )( 
            ISceneEditor * This,
            LONG xStart,
            LONG zStart,
            LONG xCount,
            LONG zCount);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetAppointLogicalRegion )( 
            ISceneEditor * This,
            LONG *xStart,
            LONG *zStart,
            LONG *xCount,
            LONG *zCount);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *GetSetLogicDisplayParams )( 
            ISceneEditor * This,
            LONG bGet,
            LONG *bShowCell,
            LONG *bShowTerrainCell,
            LONG *bShowItemCell,
            LONG *bShowSelectedCell);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ClearLogicModifyState )( 
            ISceneEditor * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetLogicModifyState )( 
            ISceneEditor * This,
            LONG lstate,
            BSTR scriptName);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetLogicCurrentColor )( 
            ISceneEditor * This,
            LONG color);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetLogicBrushParams )( 
            ISceneEditor * This,
            LONG brushwidth,
            LONG brushtype,
            LONG displaywidth,
            LONG brushheight);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *SetCurrentEditBrushIndex )( 
            ISceneEditor * This,
            LONG nIndex);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DeleteCurrentCellInfo )( 
            ISceneEditor * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *DeleteSelectedEntity )( 
            ISceneEditor * This);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *ModifyCurrentCellInfo )( 
            ISceneEditor * This,
            LONG oldInfo,
            LONG newInfo,
            BSTR oldScript,
            BSTR newScript);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *TransToEngineFormat )( 
            ISceneEditor * This,
            LONG inMask,
            /* [retval][out] */ LONG *outMask);
        
        /* [helpstring] */ HRESULT ( STDMETHODCALLTYPE *BuildPolyAndSetInHand )( 
            ISceneEditor * This,
            LONG VergeNum,
            FLOAT Radius,
            FLOAT Height,
            FLOAT Degree);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetSnapToolScale )( 
            ISceneEditor * This,
            FLOAT fScale);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetSpeedTreeLeafScale )( 
            ISceneEditor * This,
            FLOAT fScale);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *RenderSceneSnap )( 
            ISceneEditor * This,
            BSTR fileName);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SetRenderTreeFlag )( 
            ISceneEditor * This,
            LONG bFlag);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *AddRegionInfoManager )( 
            ISceneEditor * This,
            BSTR fileName,
            LONG nPixelTolerance,
            LONG nSampleTimes,
            LONG nEliminateIsoDataCount,
            LONG nTotalValue,
            ULONG uHowManyPixelsInOneRegion,
            ULONG *dwHandle);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *ShowRegionInfoMap )( 
            ISceneEditor * This,
            LONG ihWnd,
            ULONG dwHandle,
            LONG bShow);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *DelRegionInfoManager )( 
            ISceneEditor * This,
            ULONG dwHandle);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *EnableRegionMask )( 
            ISceneEditor * This,
            ULONG dwHandle,
            LONG nEnable);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetRegionMapInfo )( 
            ISceneEditor * This,
            ULONG dwHandle,
            ULONG *puHeight,
            ULONG *puWidth,
            ULONG *puPixelPerRegion,
            ULONG *puRegionCount,
            ULONG *puMemorySize);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *GetRegionDiffValue )( 
            ISceneEditor * This,
            ULONG dwHandle,
            ULONG uIndex,
            LONG *pnValue);
        
        /* [helpstring][id] */ HRESULT ( STDMETHODCALLTYPE *SaveRegionMap )( 
            ISceneEditor * This,
            BSTR filePath,
            ULONG dwHandle);
        
        END_INTERFACE
    } ISceneEditorVtbl;

    interface ISceneEditor
    {
        CONST_VTBL struct ISceneEditorVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ISceneEditor_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ISceneEditor_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ISceneEditor_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ISceneEditor_AddWindowing(This,szName,ihWnd,iWindowType,windowid,editState)	\
    ( (This)->lpVtbl -> AddWindowing(This,szName,ihWnd,iWindowType,windowid,editState) ) 

#define ISceneEditor_UpdateTopPosAsMainPos(This)	\
    ( (This)->lpVtbl -> UpdateTopPosAsMainPos(This) ) 

#define ISceneEditor_RemoveWindowing(This,iWindowID)	\
    ( (This)->lpVtbl -> RemoveWindowing(This,iWindowID) ) 

#define ISceneEditor_GetCameraTopScale(This,scale)	\
    ( (This)->lpVtbl -> GetCameraTopScale(This,scale) ) 

#define ISceneEditor_SetCameraTopScale(This,scale)	\
    ( (This)->lpVtbl -> SetCameraTopScale(This,scale) ) 

#define ISceneEditor_SetCameraTopPos(This,x,z)	\
    ( (This)->lpVtbl -> SetCameraTopPos(This,x,z) ) 

#define ISceneEditor_GetCameraTopPos(This,pos)	\
    ( (This)->lpVtbl -> GetCameraTopPos(This,pos) ) 

#define ISceneEditor_SetNPCPosition(This)	\
    ( (This)->lpVtbl -> SetNPCPosition(This) ) 

#define ISceneEditor_GetCameraPosLookat(This,pos,lookat)	\
    ( (This)->lpVtbl -> GetCameraPosLookat(This,pos,lookat) ) 

#define ISceneEditor_SetCameraPosLookat(This,pos,lookat)	\
    ( (This)->lpVtbl -> SetCameraPosLookat(This,pos,lookat) ) 

#define ISceneEditor_SetCameraLocation(This,camerax,cameray,cameraz,lookatx,lookaty,lookatz)	\
    ( (This)->lpVtbl -> SetCameraLocation(This,camerax,cameray,cameraz,lookatx,lookaty,lookatz) ) 

#define ISceneEditor_GetSelectedEntityCount(This,count)	\
    ( (This)->lpVtbl -> GetSelectedEntityCount(This,count) ) 

#define ISceneEditor_SetFullScreen(This,bFullScreen)	\
    ( (This)->lpVtbl -> SetFullScreen(This,bFullScreen) ) 

#define ISceneEditor_TogglePMode(This)	\
    ( (This)->lpVtbl -> TogglePMode(This) ) 

#define ISceneEditor_IsPMode(This,isPMode)	\
    ( (This)->lpVtbl -> IsPMode(This,isPMode) ) 

#define ISceneEditor_OnResizeWindow(This)	\
    ( (This)->lpVtbl -> OnResizeWindow(This) ) 

#define ISceneEditor_RotateSelectedObject(This,newRotation)	\
    ( (This)->lpVtbl -> RotateSelectedObject(This,newRotation) ) 

#define ISceneEditor_SetCameraSpeed(This,fPercent)	\
    ( (This)->lpVtbl -> SetCameraSpeed(This,fPercent) ) 

#define ISceneEditor_NpcPlayNextAction(This)	\
    ( (This)->lpVtbl -> NpcPlayNextAction(This) ) 

#define ISceneEditor_NpcPlayPreviousAction(This)	\
    ( (This)->lpVtbl -> NpcPlayPreviousAction(This) ) 

#define ISceneEditor_UpdateSelectableEntityList(This,doCount)	\
    ( (This)->lpVtbl -> UpdateSelectableEntityList(This,doCount) ) 

#define ISceneEditor_ClearSelectedEntityList(This)	\
    ( (This)->lpVtbl -> ClearSelectedEntityList(This) ) 

#define ISceneEditor_AddSelectedRepresentObject(This,representObjPtr,bAdd)	\
    ( (This)->lpVtbl -> AddSelectedRepresentObject(This,representObjPtr,bAdd) ) 

#define ISceneEditor_BeginAddPolyVertex(This)	\
    ( (This)->lpVtbl -> BeginAddPolyVertex(This) ) 

#define ISceneEditor_EndAddPolyVertex(This,dwType)	\
    ( (This)->lpVtbl -> EndAddPolyVertex(This,dwType) ) 

#define ISceneEditor_SetPolyHeight(This,fHeight)	\
    ( (This)->lpVtbl -> SetPolyHeight(This,fHeight) ) 

#define ISceneEditor_EnableRenderPoly(This,bEnable)	\
    ( (This)->lpVtbl -> EnableRenderPoly(This,bEnable) ) 

#define ISceneEditor_SetFocus(This)	\
    ( (This)->lpVtbl -> SetFocus(This) ) 

#define ISceneEditor_SetRenderBlockEdge(This,bRenderEdge)	\
    ( (This)->lpVtbl -> SetRenderBlockEdge(This,bRenderEdge) ) 

#define ISceneEditor_SetCameraDis(This,fDis)	\
    ( (This)->lpVtbl -> SetCameraDis(This,fDis) ) 

#define ISceneEditor_SetFirstSelectedKing(This)	\
    ( (This)->lpVtbl -> SetFirstSelectedKing(This) ) 

#define ISceneEditor_DropSelectedEntity(This)	\
    ( (This)->lpVtbl -> DropSelectedEntity(This) ) 

#define ISceneEditor_ZoomToObj(This)	\
    ( (This)->lpVtbl -> ZoomToObj(This) ) 

#define ISceneEditor_GetEditorSceneSize(This,width,height)	\
    ( (This)->lpVtbl -> GetEditorSceneSize(This,width,height) ) 

#define ISceneEditor_SetObjectSelectMask(This,nMask)	\
    ( (This)->lpVtbl -> SetObjectSelectMask(This,nMask) ) 

#define ISceneEditor_SetCurrentOutputWindow(This,nWindowID)	\
    ( (This)->lpVtbl -> SetCurrentOutputWindow(This,nWindowID) ) 

#define ISceneEditor_GetEditState(This,nState)	\
    ( (This)->lpVtbl -> GetEditState(This,nState) ) 

#define ISceneEditor_SetEditState(This,nState)	\
    ( (This)->lpVtbl -> SetEditState(This,nState) ) 

#define ISceneEditor_EnableShowAppointLogicalRegion(This,bEnable)	\
    ( (This)->lpVtbl -> EnableShowAppointLogicalRegion(This,bEnable) ) 

#define ISceneEditor_SetAppointLogicalRegion(This,xStart,zStart,xCount,zCount)	\
    ( (This)->lpVtbl -> SetAppointLogicalRegion(This,xStart,zStart,xCount,zCount) ) 

#define ISceneEditor_GetAppointLogicalRegion(This,xStart,zStart,xCount,zCount)	\
    ( (This)->lpVtbl -> GetAppointLogicalRegion(This,xStart,zStart,xCount,zCount) ) 

#define ISceneEditor_GetSetLogicDisplayParams(This,bGet,bShowCell,bShowTerrainCell,bShowItemCell,bShowSelectedCell)	\
    ( (This)->lpVtbl -> GetSetLogicDisplayParams(This,bGet,bShowCell,bShowTerrainCell,bShowItemCell,bShowSelectedCell) ) 

#define ISceneEditor_ClearLogicModifyState(This)	\
    ( (This)->lpVtbl -> ClearLogicModifyState(This) ) 

#define ISceneEditor_SetLogicModifyState(This,lstate,scriptName)	\
    ( (This)->lpVtbl -> SetLogicModifyState(This,lstate,scriptName) ) 

#define ISceneEditor_SetLogicCurrentColor(This,color)	\
    ( (This)->lpVtbl -> SetLogicCurrentColor(This,color) ) 

#define ISceneEditor_SetLogicBrushParams(This,brushwidth,brushtype,displaywidth,brushheight)	\
    ( (This)->lpVtbl -> SetLogicBrushParams(This,brushwidth,brushtype,displaywidth,brushheight) ) 

#define ISceneEditor_SetCurrentEditBrushIndex(This,nIndex)	\
    ( (This)->lpVtbl -> SetCurrentEditBrushIndex(This,nIndex) ) 

#define ISceneEditor_DeleteCurrentCellInfo(This)	\
    ( (This)->lpVtbl -> DeleteCurrentCellInfo(This) ) 

#define ISceneEditor_DeleteSelectedEntity(This)	\
    ( (This)->lpVtbl -> DeleteSelectedEntity(This) ) 

#define ISceneEditor_ModifyCurrentCellInfo(This,oldInfo,newInfo,oldScript,newScript)	\
    ( (This)->lpVtbl -> ModifyCurrentCellInfo(This,oldInfo,newInfo,oldScript,newScript) ) 

#define ISceneEditor_TransToEngineFormat(This,inMask,outMask)	\
    ( (This)->lpVtbl -> TransToEngineFormat(This,inMask,outMask) ) 

#define ISceneEditor_BuildPolyAndSetInHand(This,VergeNum,Radius,Height,Degree)	\
    ( (This)->lpVtbl -> BuildPolyAndSetInHand(This,VergeNum,Radius,Height,Degree) ) 

#define ISceneEditor_SetSnapToolScale(This,fScale)	\
    ( (This)->lpVtbl -> SetSnapToolScale(This,fScale) ) 

#define ISceneEditor_SetSpeedTreeLeafScale(This,fScale)	\
    ( (This)->lpVtbl -> SetSpeedTreeLeafScale(This,fScale) ) 

#define ISceneEditor_RenderSceneSnap(This,fileName)	\
    ( (This)->lpVtbl -> RenderSceneSnap(This,fileName) ) 

#define ISceneEditor_SetRenderTreeFlag(This,bFlag)	\
    ( (This)->lpVtbl -> SetRenderTreeFlag(This,bFlag) ) 

#define ISceneEditor_AddRegionInfoManager(This,fileName,nPixelTolerance,nSampleTimes,nEliminateIsoDataCount,nTotalValue,uHowManyPixelsInOneRegion,dwHandle)	\
    ( (This)->lpVtbl -> AddRegionInfoManager(This,fileName,nPixelTolerance,nSampleTimes,nEliminateIsoDataCount,nTotalValue,uHowManyPixelsInOneRegion,dwHandle) ) 

#define ISceneEditor_ShowRegionInfoMap(This,ihWnd,dwHandle,bShow)	\
    ( (This)->lpVtbl -> ShowRegionInfoMap(This,ihWnd,dwHandle,bShow) ) 

#define ISceneEditor_DelRegionInfoManager(This,dwHandle)	\
    ( (This)->lpVtbl -> DelRegionInfoManager(This,dwHandle) ) 

#define ISceneEditor_EnableRegionMask(This,dwHandle,nEnable)	\
    ( (This)->lpVtbl -> EnableRegionMask(This,dwHandle,nEnable) ) 

#define ISceneEditor_GetRegionMapInfo(This,dwHandle,puHeight,puWidth,puPixelPerRegion,puRegionCount,puMemorySize)	\
    ( (This)->lpVtbl -> GetRegionMapInfo(This,dwHandle,puHeight,puWidth,puPixelPerRegion,puRegionCount,puMemorySize) ) 

#define ISceneEditor_GetRegionDiffValue(This,dwHandle,uIndex,pnValue)	\
    ( (This)->lpVtbl -> GetRegionDiffValue(This,dwHandle,uIndex,pnValue) ) 

#define ISceneEditor_SaveRegionMap(This,filePath,dwHandle)	\
    ( (This)->lpVtbl -> SaveRegionMap(This,filePath,dwHandle) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ISceneEditor_INTERFACE_DEFINED__ */



#ifndef __AtlKG3DEngineProxyLib_LIBRARY_DEFINED__
#define __AtlKG3DEngineProxyLib_LIBRARY_DEFINED__

/* library AtlKG3DEngineProxyLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_AtlKG3DEngineProxyLib;

EXTERN_C const CLSID CLSID_AtlBase;

#ifdef __cplusplus

class DECLSPEC_UUID("AE07AEF9-DF57-4D4C-82A4-B9E32457B914")
AtlBase;
#endif

EXTERN_C const CLSID CLSID_BaseLib;

#ifdef __cplusplus

class DECLSPEC_UUID("D30453C5-96C6-4C64-90B9-81A9155BDF99")
BaseLib;
#endif

EXTERN_C const CLSID CLSID_SO3World;

#ifdef __cplusplus

class DECLSPEC_UUID("8AD282F9-2BD4-4782-B4B7-44F872ED7326")
SO3World;
#endif

EXTERN_C const CLSID CLSID_AtlInputProxy;

#ifdef __cplusplus

class DECLSPEC_UUID("DE6DA5FC-0382-4ABB-B9C6-FDA14C68DEF6")
AtlInputProxy;
#endif

EXTERN_C const CLSID CLSID_SceneEditor;

#ifdef __cplusplus

class DECLSPEC_UUID("7EACDC7C-452D-4963-AF03-E0437A5F29E2")
SceneEditor;
#endif

EXTERN_C const CLSID CLSID_AtlOld3DEngine;

#ifdef __cplusplus

class DECLSPEC_UUID("80B73C62-93C8-441C-9D52-F3DAC3B0D6C6")
AtlOld3DEngine;
#endif
#endif /* __AtlKG3DEngineProxyLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

unsigned long             __RPC_USER  BSTR_UserSize(     unsigned long *, unsigned long            , BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserMarshal(  unsigned long *, unsigned char *, BSTR * ); 
unsigned char * __RPC_USER  BSTR_UserUnmarshal(unsigned long *, unsigned char *, BSTR * ); 
void                      __RPC_USER  BSTR_UserFree(     unsigned long *, BSTR * ); 

unsigned long             __RPC_USER  HWND_UserSize(     unsigned long *, unsigned long            , HWND * ); 
unsigned char * __RPC_USER  HWND_UserMarshal(  unsigned long *, unsigned char *, HWND * ); 
unsigned char * __RPC_USER  HWND_UserUnmarshal(unsigned long *, unsigned char *, HWND * ); 
void                      __RPC_USER  HWND_UserFree(     unsigned long *, HWND * ); 

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


