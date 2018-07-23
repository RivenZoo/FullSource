
//////////////////////////////////////////////////////////////////////////////////////
//
//  FileName    :   KG3DEditorInterface.h
//  Version     :   1.0
//  Creater     :   YangLin
//  Date        :   2011/6/21 
//  Comment     :   
//
//////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "KG3DInterface.h"
#define MAX_MATERIAL_DESC 16
#define MAX_MATERIAL_DLL  8

#define MTL_OPTION_SETLIGHT 1

enum EKG3DRenderPass
{
    RENDERPASS_EARLYZ,
    RENDERPASS_TERRAIN,
    RENDERPASS_WATER,
    RENDERPASS_COLOR,
    RENDERPASS_BLUR,
    RENDERPASS_SHOCKWAVE,
    RENDERPASS_LENSFLAREFIRST,
    RENDERPASS_LENSFLAREOTHER,
    RENDERPASS_LENSFLAREOC,

	RENDERPASS_COLORSOFTMASK,
    RENDERPASS_TERRAINLOW,
    RENDERPASS_PREVIEW,
    RENDERPASS_COUNT,
};

enum BlendMode
{
    BLEND_Opaque,               // 不透明
    BLEND_Masked,               // AlphaTest
    BLEND_Translucent,          // 半透明
    BLEND_Additive,             // Add
    BLEND_Modulate,             // Mul
    BLEND_SoftMasked,           // 
    BLEND_AlphaCompositeAdd,    // 预乘alpha add模式c
    BLEND_AlphaCompositeBlend,  // 预乘alpha blend模式
    BLEND_DitheredTranslucent,  // 抖动
    BLEND_TranslucentMasked,    // AlphaTest跟Blend同时开启
};

enum LightingMode
{
	LM_Unlit,//Emissive only  粒子
	LM_Lambert,//Emissive+diffuse  木头
	LM_Phong,//Emissive+diffuse+specular  金属
	LM_Anisotropic,// 各向异性金属
	LM_SSS,//SubsurfaceScattering,  玻璃、皮肤
	LM_JX3,
    LM_XXMesh,
    LM_XXPlayer,
	LM_Custom,
};

enum DistortionMode
{
    DISTORTION_MODE_NONE = 0,
    DISTORTION_MODE_ONLY = 1,
    DISTORTION_MODE_ADD  = 2,
};

enum SpecialType
{
    ST_TIME,
	ST_ModelColor,
	ST_ModelPosition,
	ST_ModelSTPosition,
	ST_CameraFocus,
	ST_PointLight,
    ST_COUNT,
};

enum SharedShaderParam
{
    Shared_SunLight,
    Shared_PlayerLight,
    Shared_FogParam,
    Shared_CamPos,
    Shared_EnvMapTexture,
    Shared_ShadowMapParam,
    Shared_ShadowMapTexture,
    Shared_ShadowDarkValue,
    Shared_CoverRect,
    Shared_CoverMapTexture,
    Shared_CoverPointLightColor,
    Shared_CoverPointLightScreenSize,
	Shared_CameraPlane,
};

enum SpecialTexture
{
    Special_Diffuse,
    Special_Reflect,
    Special_TextureCount,
};

//#define RUNTIMEMACRO_STATIC_COUNT  16
#define RUNTIMEMACRO_DYNAMIC_COUNT 10

enum KG3DStaticRunTimeMacro
{
    // 静态宏，不共存
    RuntimeMacro_Mesh               = 0,
    RuntimeMacro_Skin_Mesh          = 1,    //骨骼动画模型
    RuntimeMacro_Terrain            = 2,    //地形
    RuntimeMacro_Foliage            = 3,    //灌木/植被，有风吹效果
    RuntimeMacro_Fractured_Mesh     = 4,    //可破坏物件（有内外材质）
    RuntimeMacro_SpeedTree          = 5,    //树木
    RuntimeMacro_Fluid_Surfaces     = 6,    //液体表面
    RuntimeMacro_Morph_Target       = 7,    //顶点动画变形
    RuntimeMacro_Particle_Sprites   = 8,    //点粒子
    RuntimeMacro_Particle_Mesh      = 9,    //模型粒子
    RuntimeMacro_Instance           = 10,   //多实体批量绘制
    RuntimeMacro_Static_Lighting    = 11,   //静态光照图
    RuntimeMacro_Lens_Flare         = 12, // 镜头眩光
    //RuntimeMacro_Fog                = 12,   //雾
    //RuntimeMacro_Fog_Volumes        = 13,   //体积雾
    RuntimeMacro_PostRender         = 13,   //PostRender
    RuntimeMacro_SharedShader       = 14,
    RuntimeMacro_Preview            = 15,

    RUNTIMEMACRO_STATIC_COUNT,
    // PostRender一堆也跟SkinMesh这些同级
    //RuntimeMacro_Mask           = 0x3f,
};

enum KG3DDynamicRunTimeMacro
{
    // 动态宏，可共存
    RuntimeMacro_CoverPointLight  = 0x1,   // 动态点光源
    RuntimeMacro_CoverMap         = 0x2,   // 动态CoverMap
    RuntimeMacro_Interactive      = 0x4,  // 交互
    RuntimeMacro_ProjectiveTex    = 0x8,  // 投影贴图

    RuntimeMacro_NormalMap        = 0x10,
    RuntimeMacro_ShadowMap        = 0x20,
    RuntimeMacro_Fog              = 0x40,
	RuntimeMacro_Specular		  = 0x80,
    RuntimeMacro_ParticleSubUV    = 0x100,    //可以切分uv
    RuntimeMacro_PointLight       = 0x200,
};

enum EKG3DRUNTIMEMACRO
{
	RUNTIMEMACRO_SKIN_MESH,//骨骼动画模型
	RUNTIMEMACRO_TERRAIN,//地形
	RUNTIMEMACRO_FOLIAGE,//树木，有风吹效果
	RUNTIMEMACRO_FRACTURED_MESH,//可破坏物件（有内外材质）
	RUNTIMEMACRO_SPEEDTREE,//树木
	RUNTIMEMACRO_LENS_FLARE,//镜头眩光
	RUNTIMEMACRO_FLUID_SURFACES,//液体表面
	RUNTIMEMACRO_MORPH_TARGET,//顶点动画变形
	RUNTIMEMACRO_DECALS,//细节贴花
	RUNTIMEMACRO_PARTICLE_SPRITES,//点粒子
	RUNTIMEMACRO_PARTICLE_SUB_UV,//粒子，有UV变化
	RUNTIMEMACRO_BEAM_TRAILS,//拖尾
	RUNTIMEMACRO_INSTANCE,  //多实体批量绘制
	RUNTIMEMACRO_POINTLIGHT,//点光源
	RUNTIMEMACRO_STATIC_LIGHTING,//静态光照图
	RUNTIMEMACRO_SHADOWMAP,//实时阴影
	RUNTIMEMACRO_FOG,//雾
	RUNTIMEMACRO_FOG_VOLUMES,//体积雾
	RUNTIMEMACRO_BLUR,//运动模糊
	RUNTIMEMACRO_GLOW,//辉光
	RUNTIMEMACRO_SHOCKWAVE,//屏幕扭曲
	RUNTIMEMACRO_ACTORONFOLIAGE,//草木受人影响，需开启RUNTIMEMACRO_FOLIAGE
	RUNTIMEMACRO_COUNT,
};

enum TerrainRenderConstSet
{
    TERRAIN_NONE,       
    TERRAIN_HEIGHTMAP,
    TERRAIN_NORMALMAP,
    TERRAIN_TEXBLEND,
    TERRAIN_TEXDIFFUSE,
    TERRAIN_BLENDINDEX,
    TERRAIN_TEXSCALE,
    TERRAIN_POSOFFSET,
    TERRAIN_TEXSIZE,
    TERRAIN_DIFFUSERECT,
    TERRAIN_BLENDMAPSIZE,
};

enum GrassRenderConstSet
{
    GRASS_ANIMATION,
    GRASS_TIME,
    GRASS_WINDSET,
};

class KG3DTextureTable;
struct KG3D_PointLight_Info;
struct _KG3DWIND_DESCSTRUCT;

interface IKG3DMaterial2Instance
{
	virtual int AddRef() = 0;
	virtual int Release() = 0;

	//////////////////////////////////////////////////////////////////////////
	virtual DWORD GetType() = 0;
	virtual DWORD GetID() = 0;

	//////////////////////////////////////////////////////////////////////////
	virtual HRESULT UpdateMatrix(D3DXMATRIX* pWorld,D3DXMATRIX* pView,D3DXMATRIX* pProj) = 0;
    virtual HRESULT LoadFromFile(LPCSTR pFileName) = 0;
    virtual HRESULT LoadFromBuffer(unsigned char* pbyBuffer, unsigned long uSize, DWORD dwTextureOption) = 0;
    virtual HRESULT SaveToFile(LPCSTR pFileName) = 0;    
    virtual DWORD   SaveToFile(FILE* pFile) = 0;
    virtual HRESULT GetDefineName(LPSTR pszFileName) = 0;

	//////////////////////////////////////////////////////////////////////////
	virtual DWORD GetNumUserData() = 0;//获取材质中的自定义数据个数
	virtual HRESULT GetUserData(DWORD dwIndex,DWORD* pdwSize,VOID** ppData) = 0;//得到自定义数据指针
	virtual HRESULT NewUserData(DWORD* pdwIndex,DWORD dwSize) = 0;//创建自定义数据
	virtual HRESULT DeleteUserData(DWORD dwIndex) = 0;//删除自定义数据

    virtual HRESULT SetStaticRuntimeMacro(KG3DStaticRunTimeMacro eMacro, BOOL bEnable) = 0;
	virtual HRESULT SetDynamicRuntimeMacro(KG3DDynamicRunTimeMacro eMacro,BOOL bEnable) = 0;
	virtual HRESULT RefreshRuntimeMaterial() = 0;//在用SetRunTimeMaterialMacro设置后，刷新运行时的材质和选项

    virtual HRESULT SetStaticData(KG3DStaticRunTimeMacro eMacro, void* pData, size_t uDataSize) = 0;
    virtual HRESULT SetDynamicData(KG3DDynamicRunTimeMacro eMacro, void* pData, size_t uDataSize) = 0;
    virtual HRESULT SetShaderSharedParams(SharedShaderParam ShaderType, void* pData, size_t uDataSize) = 0;
	//virtual HRESULT SetDataForGrassAniWithActor(BOOL bAnimation, D3DXVECTOR4 vActorData)=0;
	virtual HRESULT SetSpecialParams(SpecialType eType, void* pData, size_t uDataSize) = 0;
	virtual BOOL    CheckSpecialData(SpecialType eType)=0;

	virtual BOOL    IsValid() = 0;//是否可用
    virtual HRESULT OnSetMaterial(EKG3DRenderPass eTechniqueType, DWORD dwOption) = 0;
    virtual HRESULT OnRestoreMaterial() = 0;
    virtual HRESULT OnSetParameters() = 0;
	virtual HRESULT OnSetRenderState() = 0;
	virtual HRESULT OnRestoreRenderState() = 0;
    virtual HRESULT UpdateTexture(int nIndexInShaderGroup, LPDIRECT3DTEXTURE9 pTexture) = 0;
    virtual HRESULT CommitChanges() = 0;

    virtual BlendMode GetBlendMode() = 0;
    virtual DWORD     GetAlphaRefValue() = 0;
    virtual LightingMode GetLightingMode() = 0;
    virtual DistortionMode GetDistortionMode() = 0;
    virtual int     GetRenderState() = 0;

    virtual HRESULT SetBlendModeFlag(BlendMode eBlendMode) = 0;
    virtual HRESULT SetAlphaRefValue(DWORD dwAlphaRef) = 0;
    virtual HRESULT SetDistortionModeFlag(DistortionMode eDistortionMode) = 0;
    virtual HRESULT SetRenderState(int nRenderState) = 0;
    virtual HRESULT GetRenderTarget(IKG3DTexture** ppTexture, UINT uRTType) = 0;
};

interface IKG3DMaterial2Define;

interface IEKG3DMaterial2Instance : public IKG3DMaterial2Instance
{
	virtual int GetNumTexture() = 0;
	virtual int GetNumFloat() = 0;
	virtual int GetNumVector2() = 0;
	virtual int GetNumVector3() = 0;
	virtual int GetNumVector4() = 0;
	virtual int GetNumColor() = 0;

	virtual HRESULT GetTexture(int nIndex,LPSTR pName,int nMaxName,LPSTR pFile,int nMaxFile) = 0;
	virtual HRESULT SetTexture(int nIndex,LPCSTR pFile) = 0;
	virtual HRESULT GetFloat(int nIndex,LPSTR pName,int nMaxName,float* pValue) = 0;
	virtual HRESULT SetFloat(int nIndex,float* pValue) = 0;
	virtual HRESULT GetVector2(int nIndex,LPSTR pName,int nMaxName,D3DXVECTOR2* pValue) = 0;
	virtual HRESULT SetVector2(int nIndex,D3DXVECTOR2* pValue) = 0;
	virtual HRESULT GetVector3(int nIndex,LPSTR pName,int nMaxName,D3DXVECTOR3* pValue) = 0;
	virtual HRESULT SetVector3(int nIndex,D3DXVECTOR3* pValue) = 0;
	virtual HRESULT GetVector4(int nIndex,LPSTR pName,int nMaxName,D3DXVECTOR4* pValue) = 0;
	virtual HRESULT SetVector4(int nIndex,D3DXVECTOR4* pValue) = 0;
	virtual HRESULT GetColor(int nIndex,LPSTR pName,int nMaxName,D3DXVECTOR4* pValue) = 0;
	virtual HRESULT SetColor(int nIndex,D3DXVECTOR4* pValue) = 0;

    virtual int FindTexture(int nIndexInShaderGroup) = 0; // 返回处于当前列表中的位置，-1表示没有这个值
    virtual int FindFloat(int nIndexInShaderGroup) = 0;
    virtual int FindVector2(int nIndexInShaderGroup) = 0;
    virtual int FindVector3(int nIndexInShaderGroup) = 0;
	virtual int FindVector4(int nIndexInShaderGroup) = 0;
	virtual int FindColor(int nIndexInShaderGroup) = 0;

    virtual HRESULT AddTexture(int nIndexInShaderGroup, LPCSTR pszFileName) = 0;
    virtual HRESULT AddFloat(int nIndexInShaderGroup, float fValue) = 0;
    virtual HRESULT AddVector2(int nIndexInShaderGroup, D3DXVECTOR2 vValue) = 0;
    virtual HRESULT AddVector3(int nIndexInShaderGroup, D3DXVECTOR3 vValue) = 0;
	virtual HRESULT AddVector4(int nIndexInShaderGroup, D3DXVECTOR4 vValue) = 0;
	virtual HRESULT AddColor(int nIndexInShaderGroup, D3DXVECTOR4 vValue) = 0;

    virtual HRESULT RemoveTexture(int nIndex) = 0;
    virtual HRESULT RemoveFloat(int nIndex) = 0;
    virtual HRESULT RemoveVector2(int nIndex) = 0;
    virtual HRESULT RemoveVector3(int nIndex) = 0;
	virtual HRESULT RemoveVector4(int nIndex) = 0;
	virtual HRESULT RemoveColor(int nIndex) = 0;

    virtual HRESULT GetParentDefine(IKG3DMaterial2Define** ppDefine) = 0;
    virtual int     GetSpecTextureIndex(SpecialTexture eSpecialTexture) = 0;
    virtual HRESULT SetWireframeFlag(BOOL bWireframe) = 0;
    virtual HRESULT SetIsPreview(BOOL bPreview) = 0;
    virtual DWORD   GetNumInstructions() = 0;
    virtual HRESULT SetOverWriteRS(BOOL bOverWriteRS) = 0;
};

interface IKG3DMaterial2Define
{
	virtual int AddRef() = 0;
	virtual int Release() = 0;

	virtual HRESULT LoadFromFile(LPCSTR pszFileName) = 0;
	virtual HRESULT SaveToFile(LPCSTR pszFileName) = 0;

    virtual int GetNumTexture() = 0;
	virtual int GetNumRenderTarget() = 0;
    virtual int GetNumFloat() = 0;
    virtual int GetNumVector2() = 0;
    virtual int GetNumVector3() = 0;
	virtual int GetNumVector4() = 0;
	virtual int GetNumColor() = 0;

	virtual LPCSTR GetFileName() = 0;
    virtual HRESULT GetTexture(int nIndex, LPSTR pName, int nMaxName, LPSTR pFile, int nMaxFile) = 0;
	virtual HRESULT GetRenderTarget(int nIndex, LPSTR pName, int nMaxName, LPSTR pFile, int nMaxFile) = 0;
    virtual HRESULT GetFloat(int nIndex, LPSTR pName, int nMaxName, float* pValue) = 0;
    virtual HRESULT GetVector2(int nIndex, LPSTR pName, int nMaxName, D3DXVECTOR2* pValue) = 0;
    virtual HRESULT GetVector3(int nIndex, LPSTR pName, int nMaxName, D3DXVECTOR3* pValue) = 0;
	virtual HRESULT GetVector4(int nIndex, LPSTR pName, int nMaxName, D3DXVECTOR4* pValue) = 0;
	virtual HRESULT GetColor(int nIndex, LPSTR pName, int nMaxName, D3DXVECTOR4* pValue) = 0;

    virtual HRESULT SetShaderFileName(LPCSTR pszFileName) = 0;
    virtual HRESULT SetShaderSourceCode(LPCSTR pszSourceCode) = 0;
    virtual HRESULT ParamsClear() = 0;
	virtual HRESULT AddTexture(LPCSTR pszFileName, LPCSTR pszInName, LPCSTR pszOutName) = 0;
	virtual HRESULT AddRenderTarget(LPCSTR pszFileName, LPCSTR pszInName, LPCSTR pszOutName, UINT uWidth, UINT uHeigh, UINT uRTType = 0) = 0;
	virtual HRESULT AddFloat(LPCSTR pszInName, LPCSTR pszOutName, float fValue) = 0;
	virtual HRESULT AddVector2(LPCSTR pszInName, LPCSTR pszOutName, D3DXVECTOR2 vValue) = 0;
	virtual HRESULT AddVector3(LPCSTR pszInName, LPCSTR pszOutName, D3DXVECTOR3 vValue) = 0;
	virtual HRESULT AddVector4(LPCSTR pszInName, LPCSTR pszOutName, D3DXVECTOR4 vValue) = 0;
	virtual HRESULT AddColor(LPCSTR pszInName, LPCSTR pszOutName, D3DXVECTOR4 vValue) = 0;
	virtual HRESULT SetFlag(DWORD dwFlag1, DWORD dwFlag2) = 0;
	virtual HRESULT GetFlag(DWORD* pdwFlag1, DWORD* pdwFlag2) = 0;
	virtual HRESULT SetBlendModeFlag(BlendMode eBlendMode) = 0;
	virtual HRESULT SetLightingModeFlag(LightingMode eLightingMode) = 0;
	virtual HRESULT SetAlphaRefValue(DWORD dwAlphaRef) = 0;
	virtual HRESULT SetWireframeFlag(BOOL bWireframe) = 0;
	virtual HRESULT SetTwoSideFlag(BOOL bTwoSide) = 0;
    virtual HRESULT SetDistortionModeFlag(DistortionMode eDistortionMode) = 0;
};
interface IKG3DMaterialSystem;
//interface IKG3DMaterialDLL
//{
//	virtual HRESULT Init(IKG3DMaterialSystem* pSystem) = 0;
//	virtual HRESULT UnInit() = 0;
//
//	virtual HRESULT OnRequestMaterialDefine(IKG3DMaterial2Define** ppMtl,LPSTR pFileName) = 0;//分配一个新材质定义
//	virtual HRESULT OnFreeMaterialDefine(IKG3DMaterial2Define* pMtl) = 0;//删除材质定义
//
//	virtual HRESULT OnRequestMaterial(IKG3DMaterial2Instance** ppMtl,IKG3DMaterial2Define* pDefine) = 0;//分配一个新材质
//
//	virtual HRESULT OnSetMaterial(IKG3DMaterial2Instance* pMtl,EKG3DRenderPass ePass,DWORD dwOption) = 0;//设置材质
//	virtual HRESULT OnRestoreMaterial(IKG3DMaterial2Instance* pMtl,EKG3DRenderPass ePass,DWORD dwOption) = 0;//恢复材质
//
//};
class KG3DTextureTable;

struct KG3DLightParam;
struct KG3DFogParamShader;
struct IKG_Buffer;

template <class T>
interface TKG3D_LoadEvent
{
	virtual HRESULT OnLoaded(T* pLoaded) = 0;
	virtual HRESULT OnLoadFailed(T* pLoaded) = 0;
};;

typedef TKG3D_LoadEvent<IKG3DMaterial2Instance> IKG3DMtlIns_LoadEvent;
typedef TKG3D_LoadEvent<IKG3DMaterial2Define> IKG3DMtlDef_LoadEvent;
typedef TKG3D_LoadEvent<IIniFile> IKG3DIniFile_LoadEvent;
typedef TKG3D_LoadEvent<IKG_Buffer> IKG3DFile_LoadEvent;

interface IKG3DMaterialSystem
{
    virtual HRESULT Init(LPDIRECT3DDEVICE9 pD3DDevice, KG3DTextureTable* pTextureTable, BOOL bClient, BOOL bUseShaderBinary) = 0;
    virtual HRESULT Uninit() = 0;

    virtual HRESULT OnLostDevice() = 0;
    virtual HRESULT OnResetDevice() = 0;

    virtual HRESULT LoadMaterialInstance(IKG3DMaterial2Instance** ppMtl, LPCSTR pFileName) = 0; // 加载
    virtual HRESULT RequestMaterialDefine(IKG3DMaterial2Define** ppMtl, LPCSTR pFileName) = 0; // 新建Define
    virtual HRESULT RequestMaterialInstance(IKG3DMaterial2Instance** ppMtl, LPCSTR pDefineFileName) = 0; // 新建材质
    virtual HRESULT RequestMaterialInstance(IKG3DMaterial2Instance** ppMtl, IKG3DMaterial2Define* pDefine = NULL) = 0; // 新建材质
    virtual HRESULT RequestDefaultMaterialInstance(IKG3DMaterial2Instance** ppMtl) = 0;
    virtual HRESULT GetSharedShader(IKG3DMaterial2Instance** ppMtl) = 0;
	virtual HRESULT GetDefaultShader(IKG3DMaterial2Instance** ppMtl) = 0;
	virtual HRESULT GetDefaultSkinShader(IKG3DMaterial2Instance** ppMtl) = 0;

    virtual HRESULT MtlIns_LoadMultiThread(IKG3DMtlIns_LoadEvent* pEvent, LPCSTR pszFileName) = 0; // 多线程加载
    virtual HRESULT MtlIns_StopLoad(IKG3DMtlIns_LoadEvent* pEvent) = 0;

    virtual HRESULT SetDefineFileName(IKG3DMaterial2Define* pDefine, LPCSTR pszNewFileName) = 0;
    virtual HRESULT FrameMove() = 0;
};

IKG3DMaterialSystem *g_NewMaterialSystem();//获取材质系统
HRESULT g_DeleteMaterialSystem();//删除材质系统

//////////////////////////////////////////////////////////////////////////
interface IKG3DTextureConvert
{
	virtual HRESULT Convert(LPDIRECT3DDEVICE9 pDevice,LPSTR pSrc,LPSTR pDest,D3DFORMAT Format) = 0;
};

IKG3DTextureConvert* g_NewTextureConvert();
HRESULT g_DeleteTextureConvert();

struct KG3DTextureInfo : public D3DXIMAGE_INFO
{
	UINT m_uSmallTextureMipmapStart;
};

enum
{
    RenderState_ZWriteEnable  = 1,
    RenderState_ZWriteDisable = 2,
    RenderState_TwoSide       = 4,
};

enum KG3DRENDERTARGETTYPE
{
    RENDERTARGETTYPE_NORMAL = 1,
    RENDERTARGETTYPE_BANNER = 2,
};