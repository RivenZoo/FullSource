//////////////////////////////////////////////////////////////////////////////////////
//
//  FileName    :   KG3DInterface.h
//  Version     :   1.0
//  Creater     :   YangLin
//  Date        :   2005/7/5 18:01:18
//  Comment     :   
//
//////////////////////////////////////////////////////////////////////////////////////

#ifndef _KG3DINTERFACE_H_
#define _KG3DINTERFACE_H_

#include <windows.h>

#pragma warning(push)
#pragma warning(disable : 4819)
#include <d3d9.h>
#include <d3dx9.h>
#pragma warning(pop)

#include "KG3DTypes.h"


////////////////////////////////////////////////////////////////////////////////
//
//                  KG3DEngine COM Result
//
////////////////////////////////////////////////////////////////////////////////
//  HRESULTs are 32 bit values layed out as follows:
//
//   3 3 2 2 2 2 2 2 2 2 2 2 1 1 1 1 1 1 1 1 1 1
//   1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0 9 8 7 6 5 4 3 2 1 0
//  +-+-+-+-+-+---------------------+-------------------------------+
//  |S|R|C|N|r|    Facility         |               Code            |
//  +-+-+-+-+-+---------------------+-------------------------------+
// user default facility must use FACILITY_ITF, and code should >= 0x0200 (From MSDN)
#define KG3D_E_NO_FLEXIBLE_BODY_DATA  MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0x0200)

////////////////////////////////////////////////////////////////////////////////

class IKG3DResourceBase : public IUnknown
{
public:
	virtual HRESULT Init() = 0;
	virtual HRESULT UnInit() = 0;

    //////////////////////////////////////////////////////////////////////////
	virtual HRESULT LoadFromFile(const char cszFileName[], unsigned uFileNameHash, unsigned uOption) = 0;
	virtual HRESULT SaveToFile(const char cszFileName[],   unsigned uOption) = 0;
	//////////////////////////////////////////////////////////////////////////
	//type
	virtual unsigned GetType() = 0;
	virtual DWORD    GetID() = 0;
	//////////////////////////////////////////////////////////////////////////
	// memory manager
	virtual HRESULT PrepareRender(unsigned uOption) = 0; 
	virtual HRESULT PostRender() = 0; 
	virtual HRESULT GetDateInformation(int *pnMemory, int *pnVideoMemory, int *pnCompressMem, int *pnCompressVideoMem) = 0;
	virtual unsigned GetLastUseTime()  = 0;
	virtual unsigned GetUseFrequency() = 0;
	//加强版LoadFromFile，主要用于传更多参数(64位系统下面用uOption传递指针会发生Pointer Truncation)
	virtual HRESULT LoadFromFileEx(const char cszFileName[], unsigned uFileNameHash, unsigned uOption, DWORD_PTR WParam, DWORD_PTR LParam) = 0;

	virtual HRESULT RefreshOption(unsigned uOption) = 0;
};

class IKG3DResourceManager
{
public:
	virtual HRESULT Init() = 0;
	virtual HRESULT UnInit() = 0;

    //////////////////////////////////////////////////////////////////////////
	virtual HRESULT LoadResourceFromFile(const char cszFileName[], 
										 unsigned uFileNameHash, 
										 unsigned uOption, 
										 IKG3DResourceBase **ppRetResource, 
										 bool bSyncLoad=true,
										 ResNodeState** res_node_state=NULL) = 0;
	virtual HRESULT NewOneResourse(unsigned uType, IKG3DResourceBase **ppRetResource) = 0;
	//////////////////////////////////////////////////////////////////////////
	virtual HRESULT SetBalance(unsigned uSizeMemeryKB, unsigned uSizeVideoKB) = 0;

	virtual HRESULT LoadAnimationFromFile(const char cszFileName[], void** ppRet) = 0;
	virtual HRESULT UnloadAnimation(void* pResource) = 0;
	virtual HRESULT LoadTagAnimationFromFile(const char cszFileName[], void** ppRet) = 0;
	virtual HRESULT UnloadTagAnimation(void* pResource) = 0;

	virtual HRESULT LoadResourceFromFile(const char cszFileName[], unsigned uFileNameHash, unsigned uOption, HANDLE *pRetHandle) = 0;
	virtual MODEL_LOAD_STATE GetResourceLoadState(HANDLE hResourceHandle) = 0;
	virtual HRESULT GetResourceByHandle(HANDLE hResourceHandle, IKG3DResourceBase **ppRetResource) = 0;
	virtual void CloseResourceHandle(HANDLE hResourceHandle) = 0;
};

class IKG3DModelManager 
{
public:
	virtual HRESULT PreLoadTani(LPCSTR strFileName,BOOL bNerverExpire) = 0;
	virtual HRESULT ReleasePreLoadTani(LPCSTR strFileName) = 0;
};

class IKG3DModel;


typedef void (*CallbackRender)(DWORD dwTextureId, void* pUserData);


#define ANIMATION_SEEK_OFFSET_END 1000 * 60 * 50 //Seek到动作最后

enum enuAniSeekMode
{
	//按照时间
	ANIMATION_SEEK_SET          = 1,//从头开始
	ANIMATION_SEEK_CUR    = (1 << 1),//从当前位置开始
	ANIMATION_SEEK_FORCE_DWORD  = 0xffffffff
};



enum enuAniPlayMode
{
	ENU_ANIMATIONPLAY_CIRCLE,//循环播放动作
	ENU_ANIMATIONPLAY_ONCE,//单次播放动作
	ENU_ANIMATIONPLAY_ADDCURRENT,//在当前位置开始播放下一个动作,并循环
	ENU_ANIMATIONPLAY_ADDCURRENT_ONCE,//在当前位置开始放下一个动作,单次
	ENU_ANIMATIONPLAY_FORCE_DWORD = 0xffffffff,
};

enum enuModelBindType
{
	ENUM_BIND_NONE,
	ENUM_BIND_SOCKET,
	ENUM_BIND_BONE,
    ENUM_BIND_WORLD,// 绑定到世界坐标
	ENUM_BIND_FORCE_DWORD = 0xffffffff,
};

//enum enuModelLoadOption
//{
//	MODEL_LOADOPT_WITHOUTMAT = 0x1,
//	MODEL_LOADOPT_WITHBIP = (0x1<<1),
//	MODEL_LOADOPT_SPEEDTREE = (0x1<<2),
//    MODEL_LOADOPT_TEX_LOAD_IMMEDIATELY = (0x1<<3),  
//	MODEL_LOADOPT_CAN_MULTITHREAD_LOAD = (0x1<<4),
//    MODEL_LOADOPT_EDITING              = (0x1<<8),
//	MODEL_LOADOPT_FORCE_DWORD = 0xffffffff,
//};


enum enuModelLoadOption1
{
	MLO_MATERIAL_NOMAT      =  0x1,
	MLO_MESH_BIP            = (0x1 << 1),
	MLO_MESH_SPEEDTREE      = (0x1 << 2),
	MLO_TEXTURE_MULTI       = (0x1 << 3),
	MLO_MESH_MULTI          = (0x1 << 4),
	MLO_ANI_MULTI           = (0x1 << 5),
	MLO_SFX_EDITING         = (0x1 << 8),
	MLO_MODEL_RECORD        = (0x1 << 9),
	MLO_MODEL_LOD           = (0x1 << 10),
	MLO_MODELST_NOSUBMODEL  = (0x1 << 11),
	MLO_TEXTURE_LOD         = (0x1 << 12),
    MLO_MATERIAL_NOINS      = (0x1 << 13),
	MLO_MESH_SRENTITY       = (0x1 << 14),
    MLO_TEXTURE_NOSCALE     = (0x1 << 15),
	MLO_TEXTURE_AUTOSCALE   = (0x1 << 16),
	MLO_MODEL_RLCALL        = (0x1 << 17),                            //从RepresentLogic调用促发

	MLO_FORCE_DWORD         = 0xffffffff,
};

const DWORD MLO_MODULE_MASK = MLO_MODEL_RLCALL;                      //测试工具统计需要
const DWORD MLO_MESH_MASK = MLO_MESH_BIP | MLO_MESH_SPEEDTREE | MLO_MESH_MULTI | MLO_MESH_SRENTITY | MLO_MODULE_MASK;
const DWORD MLO_TEXTURE_MASK = MLO_TEXTURE_MULTI | MLO_MODULE_MASK;
const DWORD MLO_MATERIAL_MASK = MLO_MATERIAL_NOMAT | MLO_TEXTURE_MASK | MLO_MESH_MULTI | MLO_MODULE_MASK;
const DWORD MLO_MULTI = MLO_MESH_MULTI | MLO_TEXTURE_MULTI | MLO_ANI_MULTI | MLO_MODULE_MASK;


enum enuModelSaveOption
{
	MODEL_SAVEOPT_DEFAULT = 0,
	MODEL_SAVEOPT_SPEEDTREE = 0x1,
	MODEL_SAVEOPT_FORCE_DWORD = 0xffffffff,
};

enum enuBoneTransformationType
{
	ROTATION_LOCALE_X,
	ROTATION_LOCALE_Y,
	ROTATION_LOCALE_Z,
	ROTATION_LOCALE_AXIS,
	ROTATION_WORLD_X,
	ROTATION_WORLD_Y,
	ROTATION_WORLD_Z,
	ROTATION_WORLD_AXIS,
};

struct BoneTransformationInputData
{
	enuBoneTransformationType Type;
	const void*               Data;
};


#define RENDER_NONE             0
#define RENDER_SHADOW           1
#define RENDER_NOTEXTURE    (1<<1)
#define RENDER_REFACTION    (1<<2)
#define RENDER_HIGHTLIGHT   (1<<3)
#define RENDER_NO_UPDATE    (1<<4)
#define RENDER_NO_MATERIAL  (1<<5)
#define RENDER_WITH_WARPER  (1<<6)
#define RENDER_BIP          (1<<7)
#define RENDER_TOTEXTURE    (1<<8)
#define RENDER_PLAYER       (1<<9)
#define RENDER_NOTWICE      (1<<10)
#define RENDER_SHOCKWAVE    (1<<11)
#define RENDER_TEXTURESFX   (1<<12)
#define RENDER_SAVE2DTEXSFX	(1<<13)
#define RENDER_OUTLINE		(1<<14)
#define RENDER_PROJECT      (1<<15)
#define RENDER_SELFDESTRUCT (1<<16)
#define RENDER_NOCHILD     (1<<17)

class IKG3DAnimationController;
class IKG3DSFXSuede;
class IKG3DScene;

class IKG3DAnimationEventHandler
{
public:
	virtual ~IKG3DAnimationEventHandler() {}
	virtual HRESULT OnPlayAnimationFinish(IKG3DAnimationController* pController) = 0;
	virtual HRESULT OnTagPlayingSFX(IKG3DAnimationController* pController, IKG3DModel* pModel, TagSFXCallBackExtraInfo* pCallBackExtraInfo) = 0;
    virtual HRESULT OnMotionNotify(IKG3DAnimationController* pController, DWORD dwMotionInfo, TagMotionCallBackExtraInfo* pMotionCallBackExtraInfo) = 0;
};

class IKG3DEnventCenter
{
public:
	virtual HRESULT RemoveEventHandler(IKG3DAnimationEventHandler* pHandler) = 0;
};

enum enuFaceTextureResolution
{
	FACE_TEXTURE_RES_START = -1, //开始标记
	FACE_TEXTURE_HIGH = 0,   //512*512
	FACE_TEXTURE_MEDIUM,     //256*256
	FACE_TEXTURE_RES_END,    //结束标记
};
interface IKG3DFaceDefinition;
class KG3DFaceDecalDefinition
{
public:
	int nID;
	int nColorID;
	KG3DFaceDecalDefinition()
	{
		nID = 0;
		nColorID = 0;
	};
	~KG3DFaceDecalDefinition(){};
};

class KG3DFaceBaseDefinition
{
public:
	int nRoleType;
	int nTextureID;
	KG3DFaceBaseDefinition()
	{
		nRoleType = 0;
		nTextureID = 0;
	}
	~KG3DFaceBaseDefinition(){};
};

struct KG3D_CHAR_ARRAY 
{
    char *pchData;
    unsigned uCount;
};
struct KG3D_FACE_DECAL_ARRAY 
{
    KG3DFaceDecalDefinition *pData;
    unsigned uCount;
};

class IKG3DModel : public IKG3DResourceBase
{
public:
	virtual void SetOutline(int nLenght, DWORD dwColor) = 0;

	virtual HRESULT SetCaptionVisible(DWORD dwIndex, BOOL bVisible) = 0;
	virtual HRESULT SetCaption(DWORD dwIndex, LPCSTR strContent) = 0;
	virtual void    RemoveCaption() = 0;
    virtual void SetCaptionPosition(const D3DXVECTOR3& vPos, BOOL bUsePosition) = 0;	// 指定头顶名字位置
	virtual HRESULT SetCaptionColor(DWORD dwIndex, const D3DCOLORVALUE& Color) = 0;
    virtual void SetCaptionFloorHeight(float fHeight) = 0;
    virtual float GetCaptionFloorHeight() = 0;
	
    virtual HRESULT SetPercentage(float fPercentage) = 0;
	virtual HRESULT SetPercentageStyle(const D3DCOLORVALUE &Color) = 0;
	virtual HRESULT SetPercentageVisible(BOOL bVisible) = 0;

	virtual HRESULT AjustWorldDirection(const D3DXVECTOR3* pVecDir, const D3DXVECTOR3* pSelfDir) = 0;
	virtual HRESULT FrameMove() = 0;
	
	//播放动画
	virtual HRESULT PlayAnimation(
        DWORD dwPlayType,
        LPCTSTR szAnimationName,
        FLOAT fSpeed,
        int   nOffsetTime,
        PVOID pReserved,
		PVOID pUserdata,
		enuAnimationControllerPriority Priority) = 0;

	virtual HRESULT PlaySplitAnimation(
		LPCSTR strAnimationName,
		DWORD dwSplitType,
		DWORD dwExtraInfo,
		DWORD dwPlayType, 
		FLOAT fSpeed,
		int   nOffsetTime,
		PVOID pReserved,
		PVOID pUserdata,
		enuAnimationControllerPriority Priority) = 0;

	virtual void PauseAnimation(BOOL bPause) = 0;

	virtual void SeekSplitAnimation(DWORD dwSplitType, 
		enuAnimationControllerPriority nPrority,
		DWORD dwSeekType, 
		float fOffset) = 0;

	virtual int GetAnimationOffset(DWORD dwSplitType) = 0;

	virtual HRESULT SetBoneTransform(LPCSTR strBoneName, const BoneTransformationInputData& Data) = 0;
	virtual void EnableBoneTransform(BOOL bEnable) = 0;

	virtual void SetTranslation(const D3DXVECTOR3* pValue) = 0;
	virtual void SetRotation(const D3DXQUATERNION* pValue) = 0;
	virtual void SetScaling(const D3DXVECTOR3* pValue) = 0;

	virtual void GetTranslation(D3DXVECTOR3* pValue) = 0;
	virtual void GetRotation(D3DXQUATERNION* pValue) = 0;
	virtual void GetScaling(D3DXVECTOR3* pValue) = 0;

	virtual void ResetTransform() = 0;


	virtual void SetBoneLODLevel(unsigned int uLevel) = 0;
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual HRESULT BindToSocket(IKG3DModel *pModel, const char* cszSocketName) = 0;
	virtual HRESULT BindToBone(IKG3DModel *prModel, const char* strBoneName) = 0;
	virtual HRESULT UnBindFromOther() = 0;
	virtual int FindBone(const char* strBoneName, BindExtraInfo* pExtInfo) = 0;
	virtual int FindSocket(const char* strSocketName, BindExtraInfo* pExtInfo) = 0;
	virtual HRESULT GetBoneMatrix(const BindExtraInfo* pInfo, D3DXMATRIX* pmatResult, D3DXVECTOR3* pvec3Offset) = 0;
	virtual HRESULT GetSocketMatrix(const BindExtraInfo* pInfo, D3DXMATRIX* pmatResult, D3DXVECTOR3* pvec3Offset) = 0;
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	virtual int AttachModel(IKG3DModel *pModel) = 0;
	virtual void DetachModel(IKG3DModel* pModel) = 0;

	//virtual HRESULT Render(unsigned uOption, void* pExtInfo) = 0;
	
	virtual HRESULT SetAlpha(float fAlpha, BOOL bUseSpecial) = 0;
	virtual void SetHighLightLevel(float fIllumination, BOOL bInherit) = 0;
	virtual float GetHightLightLevel() = 0;
	virtual float GetAlpha() = 0;

	virtual BOOL IsLoaded() = 0;
	virtual BOOL IsResourceReady(BOOL bTestTexture) = 0;
    virtual BOOL IsVisible() const = 0;

	virtual void GetBBox(D3DXVECTOR3& vec3A, D3DXVECTOR3& vec3B) = 0;

	virtual HRESULT LoadMaterialFromFile(LPCSTR strFileName, DWORD Option) = 0;
    virtual HRESULT LoadMtlInsPackFromFile(LPCSTR pszFileName, DWORD dwOption = 0) = 0;

	virtual IKG3DAnimationController* GetAnimationController(enuAnimationControllerPriority nPriority) = 0;
    virtual IKG3DAnimationController* GetSplitAnimationContorller(DWORD dwPartIndex, DWORD dwControllerIndex) = 0;

	virtual HRESULT GetModel(unsigned int uIndex, IKG3DModel** ppModel) = 0;
    // 主要用于在公告版上绘制
    // 得到可绘制纹理数
    virtual HRESULT SetCallbackRender(CallbackRender fpCallbackRender, void* pUserData) = 0;

    // dwSubIndex 第几块公告版
    // dwTexIndex 第几层纹理

	
	virtual HRESULT GetName(LPCTSTR *ppszName) = 0;
	// just for sfx 
    STDMETHOD(UpdateChannelEffectPos)(D3DXVECTOR3 v1, D3DXVECTOR3 v2) PURE;
    virtual HRESULT SetBannerFont(LPCWSTR pszBannerFont) = 0;
    virtual void SetFaceMotionMode() = 0;

	virtual HRESULT SetDetail(int nDefineTable,int nIndex) = 0;//模型偏色和花纹

	//////////////////////////////////////////////////////////////////////////
	//command
	virtual HRESULT ExecuteCommand(LPCTSTR szCommand,LPCTSTR szRet) = 0;
	virtual HRESULT SetImportance(float fValue) = 0;
    
    virtual HRESULT SetCameraShake(BOOL bCameraShake) = 0;

	virtual HRESULT RecalBBox() = 0;
	virtual void SetRuntimeEffect(enuRuntimeShaderFlag Type, void* pExtraData) = 0;
	virtual void SetRenderForShadow(BOOL bRenderForShadow) = 0;
	
	virtual void DisableAnimationTag(int nFlag) = 0;

	virtual void DisableMeteor() = 0;	//禁用绑定在此模型上的拖尾特效

	virtual void EnableSfxSoundTag(BOOL bEnable) = 0;

	virtual void EnableMotionBlur(BOOL bEnable) = 0;
	virtual void EnableWaterEffect(BOOL bEnable) = 0;

	//20131113表现需求接口
	virtual DWORD CalcPixByDis(float fDis) = 0;

    //性能管理器专用 - 避免与游戏逻辑冲突
    virtual void SetPerfVisible(bool visible) = 0;

	//捏脸
	virtual HRESULT GetFaceDefinition(IKG3DFaceDefinition** ppRetFaceDef) = 0;
	virtual HRESULT SetFaceDefinition(
        const KG3D_CHAR_ARRAY &Param,
		const int& nRoleType,
		const KG3D_FACE_DECAL_ARRAY &vDecalDefinition,
		const int& nFacePartID = 0,
		BOOL bForceReloadFromFile = FALSE) = 0;
	virtual HRESULT SetFaceTextureResolution(enuFaceTextureResolution eResoluton) = 0;
	virtual HRESULT LoadFaceDefinitionINI(const char* szFileName) = 0;
	virtual HRESULT SetFaceBoneParams(const KG3D_CHAR_ARRAY &vParams) = 0;
	virtual HRESULT SetFaceDecals(const int& nRoleType,
		const KG3D_FACE_DECAL_ARRAY &vDecalDefinition) = 0;
	virtual HRESULT SetFacePartID(const int& nFacePartID) = 0;
	virtual HRESULT GetFacePartID(int* pFacePartID) = 0;
	//客户端添加的状态机模型
	virtual HRESULT SetSREntityModelByClient(BOOL bSREntityModelByClient) = 0;
	//设置状态机模型相交测试类型
	virtual HRESULT SetSREntityModelRayIntersectUseSkin(BOOL bSREntityModelRayIntersectUseSkin) = 0;
	//Look at
	virtual HRESULT InitLookAtController() = 0;
	virtual HRESULT UninitLookAtController() = 0;
	virtual HRESULT SetLookAtControllerEnabled(BOOL bEnabled) = 0;
	virtual HRESULT SetLookAtTarget(const D3DXVECTOR3& vecTargetWorldPos) = 0;
	virtual HRESULT SetLookAtLocalTarget(const D3DXVECTOR3& vecTargetLocalPos) = 0;
	// Dynamics bone
	virtual HRESULT SetUpDynamicsBone(IKG3DModel* pSpinModel, LPCTSTR szBoneName) = 0;
	virtual void DeleteDynamicsBone(LPCTSTR szBoneName) = 0;
	//CameraObstacle
	virtual HRESULT SetOBJPropertyByType(enuModelType eModelType) = 0;

	// detail data
	virtual void SetDetailColor(int index1, int index2, int index3) = 0;
};


interface IKG3DTimeLine
{
    virtual HRESULT Insert(int nFrame, void* pValue) = 0;
    virtual HRESULT Remove(int nFrame) = 0;
    virtual HRESULT GetData(float fFrame, void* pValue) = 0;

    virtual size_t  GetSize() = 0;
    virtual HRESULT QueryByIndex(size_t uIndex, int* pFrame, void* pValue) = 0;
};

class IKG3DSFXSuede
{
public:
    virtual HRESULT LoadFromBindFile(IKG3DModel *pModel, const char cszBindFileName[]) = 0;
    virtual HRESULT UnBindAll() = 0;
    virtual HRESULT PlayAnimation(DWORD dwType = 1) = 0;
    virtual DWORD GetSFXCount() = 0;
    virtual IKG3DModel* GetSFX(DWORD dwIndex) = 0;
};


class IKG3DAnimationControllerUpdateNotifier;
class IKG3DAnimationController
{
public:
	enum
	{
		INVALID_FRAME = 0xffffffff,
	};
	enum enuMotionTypeInfo
	{
		TYPE_NONE,
		TYPE_PART0,
		TYPE_PART1,
		TYPE_ALLPART,
		TYPE_SFX,
		TYPE_COUNT,
		TYPE_FORCE_DWORD = 0xffffff,
	};
	virtual void PauseAnimation(BOOL bPause) = 0;
	virtual void StartAnimation(DWORD dwPlayType, DWORD dwOffsetTime, float fSpeed) = 0;
	virtual BOOL IsPaused() = 0;
	virtual void SetSpeed(float fSpeed) = 0;
	virtual float GetSpeed() = 0;
	virtual void SeekAnimation(DWORD dwSeekType, int nOffset) = 0;
	virtual BOOL HasAnimation() = 0;
	virtual LPCSTR GetAnimationFileName() = 0;
    virtual int   GetPlayTime() = 0;
	virtual HRESULT RegistereEventHandler(IKG3DAnimationEventHandler* pHandler) = 0;
	virtual HRESULT UnregisterEventHandler(IKG3DAnimationEventHandler* pHandler) = 0;
	virtual IKG3DAnimationEventHandler* GetEventHandler() = 0;
	virtual DWORD64 GetMotionExtraInfo() = 0;
	virtual void SetMotionExtraInfo(DWORD64 dwMotionExtraInfo) = 0;
	virtual IKG3DModel* GetModel() = 0;
	virtual int GetCycleTime() = 0;
	virtual void AddAnimationControllerUpdateNotifier(IKG3DAnimationControllerUpdateNotifier* pNotifier) = 0;
	virtual void RemoveAnimationControllerUpdateNotifier(IKG3DAnimationControllerUpdateNotifier* pNotifier) = 0;
	virtual enuAnimationControllerPriority GetPriority() = 0;
	virtual void SetUserdata(PVOID pUserdata) = 0;
	virtual PVOID GetUserdata() = 0;
	virtual DWORD GetPlayType() = 0;
};

class IKG3DAnimationControllerUpdateNotifier
{
public:
	virtual ~IKG3DAnimationControllerUpdateNotifier() {};
    virtual ULONG STDMETHODCALLTYPE AddRef() = 0;
    virtual ULONG STDMETHODCALLTYPE Release() =0;
	virtual HRESULT FrameMove(IKG3DAnimationController* pController)  = 0;
};



class IKG3DTexture : public IKG3DResourceBase
{
public:
	virtual HRESULT Update(unsigned uMethod, DWORD dwTime) = 0; 
	virtual HRESULT Update(int nFrame) = 0;

	virtual HRESULT OnLostDevice() = 0;
	virtual HRESULT OnResetDevice()    = 0;

	virtual HRESULT GetSize(unsigned *puWidth, unsigned *puHeight) = 0;
};

typedef struct _KG3DREGION_INFORMER_STATE
{
	UINT	uInnerTexWidth;
	UINT	uInnerTexHeight;
	UINT	uHowManyPixelsInOneRegion;
	UINT	uSizeInMemory;
	DWORD	dwID;
	DWORD	dwRest[1];
#ifdef __cplusplus
	_KG3DREGION_INFORMER_STATE(){ZeroMemory(this, sizeof(_KG3DREGION_INFORMER_STATE));}
#endif
}KG3DREGION_INFORMER_STATE;

struct IKG3DRegionInfoManager : public IKG3DResourceBase
{
	virtual HRESULT GetRegionInfoData(D3DXVECTOR3 vecPos, DWORD* pdwData) = 0;
	virtual HRESULT GetState(KG3DREGION_INFORMER_STATE* pState) = 0;
};

struct IKG3DSceneCameraKeyFrame
{
	D3DXVECTOR3 vPositionTangent;
	D3DXVECTOR3 vLookAtTangent;
	D3DXVECTOR3 vPosition;
	D3DXVECTOR3 vLookAt;
};
struct IKG3DSceneCameraKeyFrameEx : public IKG3DSceneCameraKeyFrame
{
    DWORD dwTime;
};
struct IKG3DSceneCameraAnimation
{
	virtual HRESULT StartPlay(BOOL bLoop) = 0;
	virtual HRESULT StopPlay() = 0;
	virtual HRESULT PausePlay(IKG3DSceneCameraKeyFrame* pPauseKey, BOOL* bIsPaused) = 0;///StartPlay之后可以Pause，Pause第一次暂停，再Pause一次恢复，从bIsPaused得到究竟暂停了没有，如果传入了pPauseKey的话，返回用于给调用者对位的Key，Pause恢复的时候会自动从暂停的地方开始
	virtual HRESULT GetName(LPCTSTR *ppcszRetName) = 0;
	virtual HRESULT SetName(LPCTSTR pcszName) = 0;
	virtual HRESULT GetPlayState(BOOL *pbRetIsPlaying) = 0;
};
struct IKG3DSceneCameraMovement 
{
	virtual HRESULT GetCurCamAnimation(IKG3DSceneCameraAnimation **ppiRetCameraAnimation) = 0;
	virtual HRESULT	SetCurCamAnimation(int nIndex) = 0;
	virtual HRESULT GetAnimationCount(DWORD *pdwRetAnimationCount) = 0;
	virtual HRESULT FindCamAniByName(LPCTSTR pstrCamAniName, int nFinded, int* nRetIndex) = 0;///nFinded用1表示要第一个找到的，一般传1
	virtual HRESULT SetCurCamAnimationByName(LPCTSTR pstrCamAniName, int nFinded, IKG3DSceneCameraAnimation **ppiRetCameraAnimation) = 0;///直接找到就可以设为当前且可以直接得到指针
	virtual HRESULT Clear() = 0;
	virtual HRESULT LoadFromFile(LPSTR pFileName) = 0;
};


class IKG3DCamera
{
public:
	virtual IKG3DCamera* GetNew() = 0;// Attation: Destruct outside by youself.
	virtual HRESULT Copy(IKG3DCamera* pCamera) = 0;

    virtual HRESULT UpdateCamera(D3DXVECTOR3 vecPosition, D3DXVECTOR3 vecAxesPos, float fLookAtOffset, float fTargetSpeed) = 0;
	virtual HRESULT GetPosition(D3DXVECTOR3 *pPos) = 0;
	virtual HRESULT SetPosition(D3DXVECTOR3 Pos, BOOL bOutCall = FALSE) = 0;

	virtual HRESULT SetLookAtPosition(D3DXVECTOR3 Pos,BOOL bOutCall = FALSE) = 0;
	virtual HRESULT GetLookAtPosition(D3DXVECTOR3 *pPos) = 0;

    virtual HRESULT SetTrackInfo(TrackCameraInfo  trackInfo)  = 0;
    virtual HRESULT GetTrackInfo(TrackCameraInfo* pTrackInof) = 0;
    virtual DWORD   GetCurrentState() = 0;

	virtual BOOL    IsPerspective() = 0;
    virtual BOOL	GetCrossPosition(const D3DXVECTOR3& VS, const D3DXVECTOR3& VD, D3DXVECTOR3* pVecCrossPos) = 0; //求VS和VD之间最靠近VS的和场景的交点

    virtual HRESULT GetGlobalPerspective(float *pfFovy, float *pfAspect, float *pfzNear, float *pfzFar) = 0;
    virtual HRESULT SetGlobalPerspective(float fFovy, float fAspect, float fzNear, float fzFar) = 0;

    virtual HRESULT GetGlobalOrthogonal(float *pfWidth, float *pfHeight, float *pfzNear, float *pfzFar) = 0;
    virtual HRESULT SetGlobalOrthogonal(float fWidth, float fHeight, float fzNear, float fzFar) = 0;

    virtual HRESULT GetUpDirection(D3DXVECTOR3 *pUp) = 0;
	virtual HRESULT SetUpDirection(D3DXVECTOR3 Up,BOOL bOutCall = FALSE) = 0;

	virtual HRESULT GetFront(D3DXVECTOR3* pFront) = 0;
	virtual HRESULT GetRight(D3DXVECTOR3* pRight) = 0;
	virtual HRESULT GetUp(D3DXVECTOR3* pUp) = 0;

    virtual HRESULT GetPerspective(
        float *pfFovy,
        float *pfAspect,
        float *pfzNear,
        float *pfzFar
        ) = 0;

    virtual HRESULT SetPerspective(
        float fFovy,
        float fAspect,
        float fzNear,
        float fzFar
        ) = 0;

    virtual HRESULT GetOrthogonal(
        float *pfWidth,//获取正交投影参数
        float *pfHeight,
        float *pfzNear,
        float *pfzFar
        ) = 0;

    virtual HRESULT SetOrthogonal(
        float fWidth,
        float fHeight,
        float fzNear,
        float fzFar
        ) = 0;

   /* virtual HRESULT SetProjectionMode(CAMERA_PROJ_MODE Mode) = 0;
    virtual CAMERA_PROJ_MODE GetProjectionMode() = 0;*/
	virtual HRESULT EnableHighPrecise(BOOL bEnable) = 0;
};

class IKG3DLight
{
public:
    virtual unsigned   GetType() = 0;

	virtual HRESULT GetColor(D3DXVECTOR4 *pAmbient,D3DXVECTOR4 *pDiffuse,D3DXVECTOR4 *pSpecular) = 0;
	virtual HRESULT SetColor(D3DXVECTOR4 Ambient,  D3DXVECTOR4  Diffuse, D3DXVECTOR4  Specular)  = 0;

	virtual HRESULT GetPointLight(D3DXVECTOR3 *pPos, float *pfRange, float *pfAttenuation0, float *pfAttenuation1,float *pfAttenuation2) = 0;
	virtual HRESULT SetPointLight(D3DXVECTOR3  Pos,  float  fRange,  float  fAttenuation0,  float  fAttenuation1, float  fAttenuation2)  = 0;

	virtual HRESULT GetDirectionLight(D3DXVECTOR3 *pdir) = 0;
	virtual HRESULT SetDirectionLight(D3DXVECTOR3  dir)  = 0;

	virtual HRESULT GetSpotLight(
        D3DXVECTOR3 *pPos,
		D3DXVECTOR3 *pdir,
		float *ppfRange,
		float *pfAttenuation0,
		float *pfAttenuation1,
		float *pfAttenuation2,
		float *pfFalloff,
		float *pfTheta,
		float *pfPhi
    ) = 0;
	virtual HRESULT SetSpotLight(
        D3DXVECTOR3 Pos,
		D3DXVECTOR3 dir,
		float fRange,
		float fAttenuation0,
		float fAttenuation1,
		float fAttenuation2,
		float fFalloff,
		float fTheta,
		float fPhi
    ) = 0;
};

struct KG3DSCENE_INITSTRUCT 
{
	DWORD m_dwOption;///暂时无用
	D3DXVECTOR3		m_vecGameGPSInitPos;	//游戏开始的时候，玩家站在什么地方,这个值决定预加载
	//bool值请全部集中在一起
	bool			m_bUsePreloadRangeAB;	//如果为true，使用下面的m_vPreloadA和m_vPreloadB来预加载

	D3DXVECTOR3		m_vPreloadA;
	D3DXVECTOR3		m_vPreloadB;	
	DWORD_PTR		m_ArrayReserve[20];

#ifdef __cplusplus
	KG3DSCENE_INITSTRUCT()
	{
		ZeroMemory(this, sizeof(*this));
	}
#endif
} ;

class IEKG3DSceneOutputWnd;
class IKG3DScene : public IKG3DResourceBase
{
public:
	virtual HRESULT FrameMove() = 0;
	virtual HRESULT Render(unsigned uOption) = 0;
	virtual HRESULT RenderToSingleOutputWnd(IEKG3DSceneOutputWnd* piSceneOutputWnd) = 0;
	virtual HRESULT RenderToScreen(D3DXVECTOR2 const* pA, D3DXVECTOR2 const* pC, D3DXVECTOR2 const* pUVA, D3DXVECTOR2 const* pUVC, float fZ, DWORD dwFlags) = 0;

	virtual HRESULT AddOutputWindow(LPCTSTR szName, HWND hWnd, DWORD dwType, DWORD_PTR dwOption, int* pOutputWindowID) = 0;
	virtual HRESULT RemoveOutputWindow(int nOutputWindowID) = 0;

	virtual HRESULT AddRenderEntity(IKG3DResourceBase *pEntity,    unsigned uClass, BOOL bSelectable,BOOL bForceSceneLight) = 0;
	virtual HRESULT RemoveRenderEntity(IKG3DResourceBase *pEntity, unsigned uClass, BOOL bSelectable) = 0;

	virtual IKG3DCamera *GetCurrentCamera() = 0; 

    virtual HRESULT GetFloor(const D3DXVECTOR3* pvInput, FLOAT* pfRet) = 0;//输入3D坐标，向下发射的射线，查此点场景的高度
	virtual DWORD   GetGroundType(const D3DXVECTOR3 &vec3Pos) = 0;

	virtual HRESULT GetWaterHeight(D3DXVECTOR3* pOut, D3DXVECTOR3* pIn) = 0;
	virtual HRESULT GetHeight(D3DXVECTOR3* pOut,D3DXVECTOR3* pIn) = 0;//得到的是地形的高度，不包括物体

	virtual HRESULT LogicalToScene(D3DXVECTOR3* pPos, float fX, float fY, float fZ, BOOL bOnFloor) = 0;
	virtual HRESULT SceneToLogical(int* pX, int* pY, int* pZ, D3DXVECTOR3 Pos) = 0;
    virtual HRESULT ScenePosToScreenPos(D3DXVECTOR3 const& vScenePos, float& fScreenX, float& fScreenY) = 0;
    virtual HRESULT ScenePosToScreenXYZ(D3DXVECTOR3 const& vScenePos, float& fScreenX, float& fScreenY, float& fZ) = 0;
    virtual HRESULT GetSceneParam(int* pLogicStartX, int* pLogicStartZ, float& fCellLength, float& fLogicalCellCmLength, float& fTerrainMinHeight, float& fPointPerAltitude, float& fAltitudeUnit) = 0;

	virtual HRESULT GetSelectModelList(const D3DXVECTOR2& vPosScreen, BOOL bGetNearestOrAll, unsigned uMaxCount, IKG3DModel *pRetModelList[], unsigned *puRetRealCount) = 0;//bGetNearestOrALL如果取TRUE则只得到第一个物件，否则得到已经从近到远排序的一串物件，最多有限制。
	virtual HRESULT GetSelectModelList(const D3DXVECTOR3& vRayOrig, const D3DXVECTOR3& vRayDir, BOOL bGetNearestOrAll, unsigned uMaxCount, IKG3DModel *pRetModelList[], unsigned *puRetRealCount) = 0;
	virtual HRESULT GetSelectPosition(D3DXVECTOR2 const& vScale, D3DXVECTOR3& vPosition,BOOL bNotIntersectTerrain = FALSE,BOOL bNotIntersectTObject = FALSE) = 0;

	virtual HRESULT OnResizeWindow(PRECT const pRect) = 0;



	//////////////////////////////////////////////////////////////////////////

	virtual HRESULT GetMinimapLayer(IN const D3DVECTOR &vPos, OUT int &nLayer) = 0;

	///////////////////////////////////////////////////////////////////////////
	virtual HRESULT GetCameraMovement(IKG3DSceneCameraMovement** ppiCameraMovement) = 0;

	//////////////////////////////////////////////////////////////////////////
	virtual HRESULT LoadFromFileEx(const char cszFileName[], unsigned uFileNameHash, unsigned uOption, DWORD_PTR pKG3DSCENE_INITSTRUCT, DWORD_PTR LOption) = 0;
	
	virtual HRESULT SetFocus(D3DXVECTOR3& vecPos) = 0;
    virtual IKG3DResourceBase* AddFullScreenEntity(        
        LPCSTR strName,     //模型名字
        LPCSTR strAni,      //动画名字特效不需要
        BOOL bLoop,         //动画是否循环
        BOOL bClearRT,      //是否清除掉rendertarget
        DWORD dwClearColor, //清除rendertarget使用的颜色
        BOOL bAutoFit       //是否自适应缩放对应屏幕大小
    ) = 0;
    virtual HRESULT RemoveFullScreenEntity(IKG3DResourceBase* pEntity) = 0;

	virtual float GetLoadingProcess() = 0;

	virtual BOOL RayIntersection(const D3DXVECTOR3& vSrc
		, const D3DXVECTOR3& vNormalizedDir
		, FLOAT* pfRet	//从vSrc到交点的距离，用vSrc+ vNormalizedDir * T可以得到交点坐标
		, FLOAT fTestRange //检测距离
		, BOOL bCheckTerrain	//是否检查地形
		) = 0;
	
	virtual HRESULT AddOutputWindow(int nOutPutWndID) = 0;
	virtual HRESULT SetActorOnFoliage(D3DXVECTOR3& vActorPos,BOOL bIsMainActor) = 0;//主角需每帧设置，非主角请判断与上一帧位置不一致后再设置进来
	virtual HRESULT SetBatchProjectionCenter(const D3DXVECTOR3& vPos) = 0;
    virtual HRESULT SetParabolaPosition(D3DXVECTOR3* pVecPos, int nNodeNum) = 0;
    virtual HRESULT SetParabolaTexture(LPCSTR pTextureName) = 0;
    virtual HRESULT SetParabolaRenderEnable(BOOL bRenderEnale) = 0;
	virtual HRESULT EnablePostRenderEffect(PostRenderEffectType nType, BOOL bEnable) = 0;

	//预加载
	virtual HRESULT PreLoadResource(LPCTSTR cszFileName, BOOL bSync) = 0;
	virtual HRESULT UnPreLoadResource(LPCTSTR cszFileName) = 0;
	//破碎动画模型attach
	virtual BOOL IsSREntityCreated(DWORD dwSREntityID) = 0;
	virtual BOOL BindEntityToSREntity(DWORD dwSREntityID, IKG3DResourceBase *pEntity) = 0;

	virtual HRESULT LoadSceneTestHeight() = 0;

	virtual HRESULT SetTrackBlurParam(D3DXVECTOR2 vec2TBCenter,
		float fTBSampleStrength,
		float fTBSampleDist) = 0;
};


//-------------------------------------------------------------------------------------------------------------------------
enum
{
	KG3DENG_NONE					=	0x0000,

	KG3DENG_TERRAIN_DYNAMIC_LOAD	=	0x0001,
	KG3DENG_TERRAIN_DYNAMIC_UNLOAD	=	0x0002,	// 如果此标志设置，前一标志必设置，否则引擎内部设置

	KG3DENG_CLIENT                =   0x0004,//此标示表示是客户端还是编辑器
	KG3DENG_RECORD                =   0x0008,//表示是否录像工具调用引擎

	KG3DENG_DESIGN                =   0x0010,//策划场景编辑器
	KG3DENG_BENCHMARK             =   0x0020,//BENCHMARK
};


#ifndef  IPPSPEC_DEFINED
#define  IPPSPEC_DEFINED

	enum
	{
		IPPSPEC_H261,
		IPPSPEC_H263,
		IPPSPEC_H264,

		IPPSPEC_MPEG2,
		IPPSPEC_MPEG4,

		IPPSPEC_COUNT,
		IPPSPEC_DEFAULT = IPPSPEC_MPEG2,

	};


	enum
	{
		IPPSPEC_FPS_25		=	25,
		IPPSPEC_FPS_30		=	30,
		IPPSPEC_FPS_50		=	50,
		IPPSPEC_FPS_60		=	60,

		IPPSPEC_FPS_COUNT	=	IPPSPEC_FPS_60,
		IPPSPEC_FPS_DEFAULT =	IPPSPEC_FPS_25,

	};

	enum 
	{
		IPPSPEC_FILTER_NOT	  = 1,
		IPPSPEC_FILTER_CUBIC  = 2,
		IPPSPEC_FILTER_LINEAR = 3,
	};


	enum 
	{
		IPPSPEC_QUALITY_PIRATE		= 1500000,				// 偷拍
		IPPSPEC_QUALITY_DISC		= 3500000,
		IPPSPEC_QUALITY_CINEMATIC	= 5500000,
		IPPSPEC_QUALITY_CINEMATIC1	= IPPSPEC_QUALITY_CINEMATIC * 2,
		IPPSPEC_QUALITY_CINEMATIC2	= IPPSPEC_QUALITY_CINEMATIC1 * 2,
		IPPSPEC_QUALITY_CINEMATIC3	= IPPSPEC_QUALITY_CINEMATIC2 * 2,
		IPPSPEC_QUALITY_CINEMATIC4	= IPPSPEC_QUALITY_CINEMATIC3 * 2,
		IPPSPEC_QUALITY_MAX			= 5500000 * 16,
	};

#endif  IPPSPEC_DEFINED

class IKG3DUI;
interface IKG3DFaceMotionSettings;

//录像相关
struct IRecPlayer : IUnknown
{
	virtual HRESULT RePlay() = 0;
	virtual HRESULT PauseRePlay() = 0;
	virtual HRESULT StopRePlay() = 0;
	virtual HRESULT LoadRecordFile(LPCSTR szFileName) = 0;
	virtual HRESULT SetReplayWindow(HWND hWnd) = 0;
	virtual HRESULT FrameMoveRePlay() = 0;
	virtual BOOL    IsPlayFinished() = 0;
	virtual HRESULT GetLoadingProgress(float* pnLoadFilePer,float* pnStepToEventPer,int* pnLoadScenePer) = 0;
	virtual HRESULT OnResizeWindow(PRECT const pRect) = 0;
	virtual BOOL    IsLoading() = 0;
	virtual BOOL    IsExiting() = 0;
	virtual ~IRecPlayer(){};
};

class IKG3DSoundBallTable
{
public:
	virtual HRESULT LoadFromFile(LPCTSTR strFileName,
		SoundDataBase *pData) = 0;

	virtual HRESULT SaveToFile(LPCTSTR strFileName,
		SoundDataBase *pData) = 0;

	virtual void Refresh(LPCSTR strFileName) = 0;
};

typedef void(*pfOnPresent)(double);
typedef void(*pfOnRenderEnd)(double);
struct IKG3DSoundShell;
class IKG3DEngineOptionCaps;
interface IKG3DDynamicWeather;
class IKG3DSceneResponseManager;
interface IKG3DFaceMakerManager;
interface IKG3DMeshMergeManager;
interface IKG3DPerformanceTweaker;
interface IEKG3DSceneSceneEditor;
interface IKG3DPSFilterManager;
class KFluencyParam;

class IKG3DEngineManager
{
public:
	virtual HRESULT Init(unsigned uMode, unsigned int uFlag, HWND hBaseWindow, HWND hRenderWindow) = 0; // uMode = 0 : windowed, uMode = 1: fullscreen
	virtual HRESULT UnInit() = 0;
	virtual BOOL    AttachEventHandle(void* pEventCommon, void* pLogicEventMgr, void* pRepresentEventMgr) = 0;
        virtual BOOL    SetFluencyParam(KFluencyParam* pFluencyParam) = 0;
        virtual KFluencyParam* GetFluencyParam() = 0;

    virtual IKG3DResourceManager* Get3DModelTable() = 0;
	virtual IKG3DModelManager*    Get3DModelTableEx() = 0;

	virtual IKG3DSoundBallTable* GetSoundBallTable() = 0;
	virtual IKG3DSoundBallTable* GetSoundPolygonTable() = 0;
	virtual IKG3DSoundBallTable* GetSoundReverbTable() = 0;
    virtual IKG3DUI* Get3DUI() = 0;
	virtual IKG3DFaceMotionSettings* GetFaceMotionSettings() = 0;

    virtual HRESULT FrameMove() = 0;
    virtual HRESULT Render() = 0;

	virtual HRESULT NewOneScene(unsigned uType, IKG3DScene **ppRetScene) = 0;
	virtual HRESULT RemoveScene(IKG3DScene *pScene) = 0;
    // 客户端引擎选项 Add by FengBo 2007-9-5 10:35
	virtual HRESULT GetEngineOption(KG3DEngineOption* pEngineOption) = 0;
	virtual HRESULT SetEngineOption(const KG3DEngineOption* pEngineOption) = 0;	//Set之前先Get，然后改一部分，再Set
	virtual	HRESULT GetEngineCaps(KG3DEngineCaps* pCaps) = 0;

    virtual int GetColorCurveStypeNum() = 0;
    virtual void GetColorCurveStypeName(char szName[], int nIndex) = 0;

	virtual HRESULT ExecuteCommand(LPCTSTR szCommand) = 0;

    // 视频录像
    virtual int GetVideoDll(HMODULE *pVideoDLL) = 0;

    virtual HRESULT MovieRecord(LPCTSTR szFolder, int nSizeScale, UINT uFilter, UINT uQuality, int nEncoder, int nFps) = 0;
	virtual HRESULT MovieStop() = 0;
	virtual BOOL    MovieReady() const = 0;
	virtual VOID    MovieViewport(RECT const& rcViewport) = 0;

	//事件录像
	virtual BOOL    CanRecord() = 0;
	virtual BOOL    IsRecording() = 0;
	virtual HRESULT StartRecord(LPCTSTR szFolder,unsigned uMode) = 0;
	virtual HRESULT StopRecord() = 0;
	
	//录像相关End

	//截屏
	

    
    virtual BOOL	GetRenderOption(RENDER_OPTION opt) = 0;
    virtual HRESULT SetRenderOption(RENDER_OPTION opt, BOOL bEnable) = 0;


	//区域设定///////////////////////////////////////////////////////////////////////
	virtual HRESULT GetRegionInfoManager(const char cszFileName[]
										, unsigned uFileNameHash
										, DWORD_PTR dwOption
										, IKG3DRegionInfoManager** ppRIM) = 0;	// dwOption是KG3DREGION_INFORMER_LOADFILE_PARAM指针，如果传入0，使用默认

	virtual HRESULT InitGameContext(KG3D_GAME_INIT_CONTEXT* pContext) = 0;	//用于游戏运行时上下文，需要和Init分离，因为有些东西Init的时候不知道
	virtual HRESULT GetInterface(DWORD dwType, DWORD_PTR p1, DWORD_PTR p2, LPVOID* ppInterface) = 0;	//相当于QueryInterface，但不加引用计数

	virtual LPDIRECT3DDEVICE9 GetDevice() = 0;

	virtual void SetSoundShell(IKG3DSoundShell *pShell) = 0;//设置使用的IKG3DSoundShell

    virtual IKG3DEngineOptionCaps* CreateIKG3DEngineOptionCaps() = 0;
    virtual void RemoveKG3DEngineOptionCaps(IKG3DEngineOptionCaps* pIEngineOptionCaps) = 0;

	virtual IKG3DDynamicWeather* GetDynamicWeather() = 0;

    virtual IKG3DFaceMakerManager* GetFaceMakerManager() = 0;

	virtual IKG3DMeshMergeManager* GetMeshMergeManager() = 0;

	virtual IKG3DPSFilterManager* GetPSFilterManager() = 0;

    virtual IKG3DPerformanceTweaker* GetPerformanceTweaker() = 0;
    
	virtual IKG3DSceneResponseManager* GetSceneResponseManager() = 0;

	virtual HRESULT AddOutputWindow(TCHAR szName[],HWND hWnd, DWORD dwType,DWORD_PTR dwOption) = 0;
	virtual HRESULT RemoveOutputWindow(int nID) = 0;
	virtual void    SetPaintThreadID(DWORD dwThreadID) = 0;
	virtual void    SetRenderThreadPaint(BOOL bIsRenderThread) = 0;
	virtual BOOL    IsDeviceLost() const = 0;
	virtual HRESULT ResetDeveice() = 0;


	virtual HRESULT DoGlobalPreLoad() = 0;
	virtual HRESULT UnLoadGlobalPreLoad() = 0;

	virtual HRESULT EnableTextureAutoScale(BOOL bEnable) = 0;

	//PostRender相关

	//SetPostRenderDoFDis	函数设置景深效果焦距距离的函数，默认值为150.0f
	virtual HRESULT SetPostRenderDoFDis(FLOAT fDis) = 0;	
	//GetPostRenderDoFDis	可以通过参数返回得到当前焦距的距离值，默认值为150.0f
	virtual HRESULT GetPostRenderDoFDis(FLOAT* pfDis) = 0;

	//SetPostRenderDoFNear	函数设置近景深的距离值，初始值为10.0f
	virtual HRESULT SetPostRenderDoFNear(FLOAT fNear) = 0;	
	//GetPostRenderDoFNear	参数返回近景深的距离值，初始值为10.0f
	virtual HRESULT GetPostRenderDoFNear(FLOAT* pfNear) = 0;

	//SetPostRenderDoFFar	函数设置远景深的距离值，初始值为80000.0f
	virtual HRESULT SetPostRenderDoFFar(FLOAT fFar) = 0;	
	//GetPostRenderDoFFar	参数返回远景深的距离值，初始值为80000.0f
	virtual HRESULT GetPostRenderDoFFar(FLOAT* pfFar) = 0;

	//SetUseCameraParam		如果传入为TRUE,焦距距离跟随摄像机距离到人物距离为止，如果传入FALSE，则根据传入的固定参数为距离值
	virtual HRESULT SetDofUseCameraParam(BOOL bUseCameraParam) = 0;
	//IsUseCameraParam		获得当前景深焦距参数是哪一种模式的状态
	virtual BOOL IsDofUseCameraParam() = 0;

	virtual HRESULT SetHueScale(IKG3DScene* pScene, FLOAT fHueScale) = 0;
	virtual HRESULT SetHueBias(IKG3DScene* pScene, FLOAT fHueBias) = 0;
	virtual HRESULT SetSaturationScale(IKG3DScene* pScene, FLOAT fSaturationScale) = 0;
	virtual HRESULT SetSaturationBias(IKG3DScene* pScene, FLOAT fSaturationBias) = 0;
	virtual HRESULT SetIntensityScale(IKG3DScene* pScene, FLOAT fIntensityScale) = 0;
	virtual HRESULT SetIntensityBias(IKG3DScene* pScene, FLOAT fIntensityBias) = 0;
	
	virtual HRESULT GetHueScale(IKG3DScene* pScene, FLOAT& fHueScale) = 0;
	virtual HRESULT GetHueBias(IKG3DScene* pScene, FLOAT& fHueBias) = 0;
	virtual HRESULT GetSaturationScale(IKG3DScene* pScene, FLOAT& fSaturationScale) = 0;
	virtual HRESULT GetSaturationBias(IKG3DScene* pScene, FLOAT& fSaturationBias) = 0;
	virtual HRESULT GetIntensityScale(IKG3DScene* pScene, FLOAT& fIntensityScale) = 0;
	virtual HRESULT GetIntensityBias(IKG3DScene* pScene, FLOAT& fIntensityBias) = 0;

	//virtual HRESULT EnablePostRenderHSI(BOOL bEnable) = 0;
};

interface DECLSPEC_NOVTABLE IKG3DTimeClock
{
	virtual HRESULT AdjustClock(DWORD dwMilliSeconds) = 0;
};

class IKG3DGraphicsTool
{
public:
	virtual HRESULT DrawLine(D3DXVECTOR3 *pPoint0, D3DXVECTOR3 *pPoint1, DWORD dwColor0, DWORD dwColor1) = 0;
	
	virtual HRESULT DrawScreenRect(const D3DXVECTOR2 *pPointA, 
		const D3DXVECTOR2 *pPointC,
		float fZ, 
		DWORD dwColor) = 0;
	virtual HRESULT DrawBox( D3DXVECTOR3 &vMin, D3DXVECTOR3 &vMax, D3DCOLOR color, BOOL bEnableZ) = 0;

};


//-------------------------------------------------------------------------------------------------------------------------
enum { KG3DUI_SCENE_NAME_LEN	= 32 };
enum { KG3DUI_TEXTURE_NAME_LEN	= 32 };
enum { KG3DUI_TEXT_LEN			= 16 };

enum { KG3DUI_FLAGS_NONE			 = 0x0000 };
enum { KG3DUI_FLAGS_RENDER_DARKLIGHT = 0x0001 };
enum { KG3DUI_FLAGS_RENDER_HIGHLIGHT = 0x0002 };

enum { KG3DUI_SCENE_FLAGS_NONE				= 0x0000 };
enum { KG3DUI_SCENE_FLAGS_DISABLE_TERRAIN	= 0x0001 };
enum { KG3DUI_SCENE_FLAGS_DISABLE_SKYBOX	= 0x0002 };
enum { KG3DUI_SCENE_FLAGS_DISABLE_WATER		= 0x0004 };
enum { KG3DUI_SCENE_FLAGS_DISABLE_SUNLIGHT	= 0x0008 };
enum { KG3DUI_SCENE_FLAGS_DISABLE_VIEWPORT	= 0x0010 };
enum { KG3DUI_SCENE_FLAGS_ENABLE_FRAMEMOVE	= 0x0020 };
enum { KG3DUI_SCENE_FLAGS_ENABLE_ALPHA	    = 0x0040 };

enum { KG3DUI_TEXT_STYLE_NONE		= 0x00 };
enum { KG3DUI_TEXT_STYLE_BORDER		= 0x01 };
enum { KG3DUI_TEXT_STYLE_VERTICAL	= 0x02 };
enum { KG3DUI_TEXT_STYLE_SHADOW		= 0x04 };
enum { KG3DUI_TEXT_STYLE_MONO		= 0x08 };
enum { KG3DUI_TEXT_STYLE_MIPMAP     = 0x10 };
enum { KG3DUI_TEXT_STYLE_LCD        = 0x20 };

enum { KG3DUI_IMAGE_FLAGS_NONE          = 0x00 };
enum { KG3DUI_IMAGE_FLAGS_POOL_DEFAULT  = 0x01 };   // 尽量少用，没这标志的为POOL_MANAGED
enum { KG3DUI_IMAGE_FLAGS_HDC           = 0x02 };   // 符合 HDC 要求的图像格式
enum { KG3DUI_IMAGE_FLAGS_DXT5          = 0x04 };  //ui合并小贴图成大贴图使用的格式
enum { KG3DUI_IMAGE_FLAGS_DXT1          = 0x08 };  //ui合并小贴图成大贴图使用的格式

enum RS2_FONT_ITEM_PARAM 
{ 
	RS2_MAX_FONT_ITEM_NUM = 9 
};

struct KG3DUITextureUsage
{
	UINT uMemoryUsage;
	UINT uTextureUsage;
	UINT uSliceUsage;
};

struct VideoMemoryInfo
{
    // 显存
    DWORD   dwLocalTatal;           
    DWORD   dwLocalFree;

    // AGP 显存
    DWORD   dwNonLocalTatal;
    DWORD   dwNonLocalFree;

    // Texture 可用显存
    DWORD   dwTextureTatal;
    DWORD   dwTexturnFree;

    // 3D 可用显存
    DWORD   dwD3DTotal;
    DWORD   dwD3DFree;
};

enum KDrawState
{
    DRAW_STATE_NONE,
    DRAW_STATE_LINE,
    DRAW_STATE_FILL,
    DRAW_STATE_TEXT,
    DRAW_STATE_IMAGE,
    DRAW_STATE_SCENE,
};

typedef void (*KG3DUIDrawUserdata)(BYTE* pBits, INT nPitch, UINT uWidth, UINT uHeight, D3DFORMAT Format, void* pUserdata);

class IKG3DeviceCallback
{
public:
    virtual bool IsDeviceAcceptable(D3DCAPS9* pCaps, D3DFORMAT AdapterFormat, D3DFORMAT BackBufferFormat, bool bWindowed) = 0;
    virtual bool ModifyDeviceSettings(KG3DDeviceSettings const* pSettings, D3DCAPS9 const* pCaps) = 0;
    virtual HRESULT OnCreateDevice(LPDIRECT3DDEVICE9 pd3dDevice, D3DSURFACE_DESC const* pBackBufferSurfaceDesc, D3DPRESENT_PARAMETERS const* pPresentParameters) = 0;
    virtual HRESULT OnDestroyDevice() = 0;
    virtual HRESULT OnLostDevice() = 0;
    virtual HRESULT OnResetDevice(LPDIRECT3DDEVICE9 pd3dDevice, D3DSURFACE_DESC const* pBackBufferSurfaceDesc, D3DPRESENT_PARAMETERS const* pPresentParameters) = 0;
    virtual HRESULT OnResetViewport(UINT uWidth, UINT uHeight) = 0;
};

struct K2DDiffuseVertex
{
    enum { FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE };

    FLOAT x, y, z;		// The transformed position for the vertex
    D3DCOLOR color;			// The vertex color
};

struct K2DTex1Vertex
{
    enum { FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 };

    FLOAT x, y, z;		// The transformed position for the vertex
    D3DCOLOR color;		// The vertex color
    FLOAT tu,tv;
};


class IKG3DFontTexture
{
public:
    virtual ~IKG3DFontTexture() {};

    virtual HRESULT Prepare() = 0;
    virtual HRESULT Flush() = 0;
    virtual BOOL    BeginBatchDraw() = 0;
    virtual BOOL    EndBatchDraw() = 0;
    virtual void    Draw2DText(FLOAT x, FLOAT y, FLOAT z, LPCWSTR wszText, int nTextLen, FLOAT cchSpace) = 0;
    virtual void    Draw2DText(DWORD dwColor, FLOAT x, FLOAT y, FLOAT z, LPCWSTR wszText, int nTextLen, FLOAT cchSpace, float fScale) = 0;
    virtual void    Draw2DTextBorder(DWORD dwColor, int nBorderSize, FLOAT x, FLOAT y, FLOAT z, LPCWSTR wszText, int nTextLen, FLOAT cchSpace, float fScale) = 0;
    virtual int     IsSameRender(IKG3DFontTexture *pFont) = 0;

    virtual void    SetTextEffect(DWORD dwEffect) = 0;
    virtual void    SetTextBorder(DWORD dwColor, DWORD dwWeight) = 0;
    virtual void    SetTextShadow(DWORD dwColor, DWORD dwOffset) = 0;
    virtual void    SetTextScaling(FLOAT fScalingX, FLOAT fScalingY) = 0;
    virtual void    LoadText(LPCWSTR wszText, int nLen, int nBorder = 0) = 0;
    virtual void    Draw2DTextDX11(LPCWSTR wszText, int nTextLen, FLOAT x, FLOAT y, FLOAT z, DWORD dwFontColor, DWORD dwShadowColor, DWORD dwBorderColor, int nShadowSize, int nBorderSize, FLOAT cchSpace, float fScale) = 0;
};

class IKG3DUI
{
public:
	virtual ~IKG3DUI() {};

	virtual HRESULT SetHWnd(HWND hWnd) = 0;

    // only call by init

    virtual HRESULT SetDeviceCallback(IKG3DeviceCallback* pCallback) = 0;

    virtual HRESULT CreateImage(UINT uWidth, UINT uHeight, LPDWORD pdwImageID, DWORD dwFlags) = 0;
    virtual HRESULT DuplicateImage(DWORD dwImageID, DWORD dwFlags, LPDWORD pdwNewImageID) = 0;
    virtual HRESULT GrayImage(DWORD dwImageID, RECT const& DstRect, LPDWORD pdwNewImageID) = 0;
    virtual HRESULT LoadImage(LPCTSTR szFilePath, LPDWORD pdwImageID, int bGray = false) = 0;
    virtual HRESULT FillImage(DWORD dwDstImageID, LPCTSTR szImageFile, RECT const& SrcRect, RECT const& DstRect, int bGray) = 0;

    virtual HRESULT UnloadImage(DWORD dwImageID) = 0;
    virtual HRESULT UnloadAllImage() = 0;

    virtual HRESULT FillTextGlyph(DWORD dwFontID, const wchar_t* pwszText, int nLen = -1, int nBorder = 0) = 0;
public:
	virtual HRESULT LoadFont(DWORD dwFontID, LPCSTR szFilePath, long nFaceIndex, float fPixel, DWORD dwStyle, int bAlonemgr = false) = 0;
	virtual HRESULT UnloadFont(DWORD dwFontID) = 0;
	virtual HRESULT UnloadAllFont() = 0;

	virtual HRESULT MaskImage(DWORD dwImageID, DWORD dwMaskImageID) = 0;
    virtual HRESULT SaveImage(LPCTSTR szFilePath, DWORD dwImageID) = 0;
	
	virtual HRESULT CreateScene(IKG3DScene** pp3DScene, const char* cszEnvFileName = NULL) = 0;
	virtual HRESULT UnloadScene(IKG3DScene* p3DScene) = 0;
	virtual HRESULT GetImageData(DWORD dwImageID, UINT uWidth, UINT uHeight, BYTE* pData, UINT uLength, BOOL bUpToDown) const = 0;
	virtual HRESULT GetImageSize(DWORD dwImageID, UINT* puWidth, UINT* puHeight) const = 0;

    /*
      the nQuality (0 ~ 100) just use to D3DXIFF_JPG file format
     */
    virtual HRESULT ScreenShot(const char szFilePath[], D3DXIMAGE_FILEFORMAT eType, int nQuality, RECT const& ShotRect) = 0;
	virtual HRESULT ScreenShotEx(const char szFilePath[], D3DXIMAGE_FILEFORMAT eType, DWORD nWidth, DWORD nHeight) = 0;
	virtual HRESULT OverSamplingScreenShot(LPCTSTR tszFilePath, D3DXIMAGE_FILEFORMAT eType,  INT nMagnification = 2, BOOL bOuputSourceScreenShot = FALSE) = 0;

	virtual HRESULT DrawUserdataToImage(DWORD dwImageID, KG3DUIDrawUserdata DrawUserdata,void* pUserData) = 0;
	virtual HRESULT DrawOleToImage(LPUNKNOWN pUnknown, DWORD dwImageID) = 0;
    
    virtual void    DrawScreen3DSfx(IKG3DModel* p3DModel, D3DXVECTOR2 Pos, float fBoxW, float fBoxH, int bClearZ, int bRenderBox) = 0;
    virtual HRESULT GetModelBoxSize(IKG3DModel *pModel, float& rfWidth, float& rfHeight) = 0;

	virtual HRESULT BeginScene() = 0;
	virtual HRESULT EndScene() = 0;

	virtual HRESULT BeginRenderToScreen() = 0;
	virtual HRESULT EndRenderToScreen() = 0;

    virtual HRESULT Present() = 0;
    virtual void ResetDrawState() = 0;

	virtual HRESULT BeginRenderToTextureEx(DWORD dwTextureID, UINT uMipmapLevel) = 0;
	virtual HRESULT EndRenderToTexture() = 0;
    virtual HRESULT BeginRenderToTexture(DWORD_PTR dwTextureID, UINT uMipmapLevel) = 0;

	virtual HRESULT BeginRenderToImage(DWORD dwImageID) = 0;
	virtual HRESULT EndRenderToImage() = 0;
	virtual HRESULT BeginStencil() = 0;
	virtual HRESULT SetStencilFunc() = 0;
	virtual HRESULT EndStencil() = 0;

    virtual void TransformSceneCoorSys() = 0;
    virtual void TransformUICoorSys() = 0;
    virtual void RestoreCoorSys() = 0;

	virtual HRESULT GetCharWidth(DWORD dwFontID, FLOAT fScale, FLOAT& fWidth) const = 0;
	virtual HRESULT GetCharHeight(DWORD dwFontID, FLOAT fScale, FLOAT& fHeight) const = 0;
	virtual HRESULT GetTextExtent(DWORD dwFontID, LPCWSTR wszText, int nTextLength, FLOAT &fWidth, FLOAT &fHeight, FLOAT fSpace, FLOAT fScale, int nBorder = 0) const = 0;
	virtual HRESULT GetTextPosExtent(DWORD dwFontID, LPCWSTR wszText, int nTextLength, FLOAT fCursorPos, LPINT lpCharPos, FLOAT fSpace, FLOAT fScale, int nBorder = 0) const = 0;

    virtual HRESULT OnCreateDevice(LPDIRECT3DDEVICE9 pd3dDevice, D3DSURFACE_DESC const* pBackBufferSurfaceDesc, D3DPRESENT_PARAMETERS const* pPresentParameters) = 0;
    virtual HRESULT OnDestroyDevice() = 0;
	virtual HRESULT OnLostDevice() = 0;
	virtual HRESULT OnResetDevice(LPDIRECT3DDEVICE9 pd3dDevice, D3DSURFACE_DESC const* pBackBufferSurfaceDesc, D3DPRESENT_PARAMETERS const* pPresentParameters) = 0;
    virtual HRESULT OnResetViewport(UINT uWidth, UINT uHeight) = 0;

    virtual HRESULT GetDeviceSettings(KG3DDeviceSettings* pSettings) = 0;
    virtual HRESULT SetDeviceSettings(KG3DDeviceSettings* pSettings) = 0;
	virtual HRESULT SetViewportSize(UINT uWidth, UINT uHeight) = 0;

	virtual VideoMemoryInfo GetVideoMemeryInfo() const = 0;
	virtual UINT    GetAvailableTextureMem() const = 0;
	virtual void    GetUITextureUsage(KG3DUITextureUsage& Usage) const = 0;

	virtual UINT    GetAllowableAdapterModeCount() const = 0;
    virtual HRESULT GetAllowableAdapterMode(D3DDISPLAYMODE* pAdapterMode, UINT* puCount) const = 0;

    virtual HRESULT SetCodePage(unsigned int uCodePage) = 0;
    virtual unsigned int GetCodePage() = 0;

    virtual int LockDiffuseVertexBuff(UINT uVertexCnt, K2DDiffuseVertex** ppVer, UINT* pnRetStartVertex) = 0;
    virtual int UnLockDiffuseVertexBuff() = 0;
    virtual size_t GetDiffuseVertexNums() = 0;
    virtual HRESULT DrawPrimitive(D3DPRIMITIVETYPE PrimitiveType, UINT StartVertex, UINT nCount) = 0;

    virtual int LockTex1VertexBuff(UINT uVertexCnt, K2DTex1Vertex** ppVer, UINT* pnRetStartVertex) = 0;
    virtual int UnLockTex1VertexBuff() = 0;
    virtual size_t GetTex1VertexNums() = 0;
    virtual HRESULT DrawPrimitive(D3DPRIMITIVETYPE PrimitiveType, DWORD_PTR dwTextureID, UINT StartVertex, UINT nCount) = 0;

    virtual HRESULT BeginDrawMultiScene() = 0;
    virtual HRESULT EndDrawMultiScene() = 0;

    virtual DWORD_PTR GetImageTexture(DWORD dwImageID, D3DFORMAT* pFormat) = 0;
    virtual void ChangeDrawState(KDrawState DrawState) = 0;
    virtual HRESULT GetTextureRenderData(DWORD_PTR dwTextureID, UINT uWidth, UINT uHeight, BYTE* pData, size_t uLength, BOOL bUpToDown) = 0;

    virtual HRESULT CreateTexture(UINT uWidth, UINT uHeight, DWORD_PTR* pdwTextureID) = 0;
    virtual void    ReleaseTexture(DWORD_PTR dwTextureID) = 0;
    virtual IKG3DFontTexture* GetFont(DWORD dwFontID) = 0;
#if defined(DEBUG) | defined(_DEBUG)
	virtual LPDIRECT3DDEVICE9 GetDevice() = 0;
#endif

    virtual HRESULT GetTextRange(DWORD dwFontID, LPCWSTR wszText, int nTextLen, LPCWSTR wszEnd, FLOAT fCursorPos, FLOAT fSpace, FLOAT fScale, LPINT lpCharPos, FLOAT &fWidth, FLOAT &fHeight, int nBorder = 0) const = 0;
    virtual HRESULT ReloadTexture(LPCTSTR szFilePath, DWORD dwImageID, int bGray) = 0;
};

class IKG3DDebugInfo
{
public:
	virtual~IKG3DDebugInfo() {}

	virtual void	Enable(BOOL bEnable) = 0;
	virtual BOOL	IsEnable() const = 0;

	virtual int		GetTotalStateChanges() const = 0;
	virtual void	ResetTotalStateChanges() = 0;
};


typedef struct _IKG3DRTTITypeDescStruct 
{
	enum
	{
		MAX_RTTI_NAME_LENGTH = 32,
	};
	DWORD	m_dwType;
	TCHAR	m_tczName[MAX_RTTI_NAME_LENGTH];
}IKG3DRTTITypeDescStruct;

struct  IKG3DRTTIType
{
	virtual HRESULT GetInfo(IKG3DRTTITypeDescStruct* pDescStruct) = 0;
	virtual HRESULT IsEqual(IKG3DRTTIType* pOtherType) = 0;
	virtual HRESULT GetName(LPTSTR tczName, INT nBufferSize) = 0;
	virtual HRESULT GetType(DWORD* pdwType) = 0;
};

struct	IKG3DRTTITypeManager
{
	virtual HRESULT GetRTTIType(DWORD dwType, IKG3DRTTIType** pRetType) = 0;
};

class IKG3DModelMesh  : public IKG3DResourceBase
{
public:
	//////////////////////////////////////////////////////////////////////////
	//骨骼相关
	virtual HRESULT	SetBoneIndex(WORD* pIndex) = 0;
	virtual int     FindBone(LPCSTR strBoneName) = 0;

	//////////////////////////////////////////////////////////////////////////
	//绘制
	virtual HRESULT RenderWithoutStateChange(float fAlpha) = 0;
	//////////////////////////////////////////////////////////////////////////
	//LOD
	virtual HRESULT SetLOD(float fLod) = 0;

};



interface IKG3DFaceMotionSettings
{
	virtual LPCSTR GetFaceMotionTypeName(DWORD dwIndex) = 0;
	virtual LPCSTR GetFaceMotionSuffixName(DWORD dwIndex) = 0;
	virtual LPCSTR GetFaceMotionModifyPath() = 0;
	virtual void GetFaceMotionPathFromFacePath(LPSTR strFacePath) = 0;
	virtual DWORD GetNumFaceMotion() = 0;
};

struct KG3D_INT_ARRAY
{
    int *pnData;
    unsigned uCount;
};
struct KG3D_ENGINE_OPTION_CAPS
{
    KADAPTERMODE *pAdapterModes;
    unsigned uAdapterModelCount;

    KG3D_INT_ARRAY MultiSampleType;
    KG3D_INT_ARRAY ShaderModel;
    KG3D_INT_ARRAY ScaleOutputSize;
    KG3D_INT_ARRAY MDLRenderLimit;
    KG3D_INT_ARRAY ClientSFXLimit;
    KG3D_INT_ARRAY ModelShadowType;
};
class IKG3DEngineOptionCaps
{
public:
    virtual HRESULT UpdateCaps(const KG3DEngineOption& EngineOption) = 0;
    virtual const KG3D_ENGINE_OPTION_CAPS *GetCaps() = 0;

    virtual DWORD GetMaxAnisotropy() = 0;
    virtual DWORD GetMinAnisotropy() = 0;
    virtual BOOL GetRenderGrass() = 0;
    virtual BOOL GetGrassAnimation() = 0;
    virtual BOOL GetGrassAlphaBlend() = 0;
    virtual int  GetMinTextureScale() = 0;
    virtual int  GetMaxTextureScale() = 0;
    virtual float GetMinCameraDistance() = 0;
    virtual float GetMaxCameraDistance() = 0;
    virtual float GetMinCameraAngle() = 0;
    virtual float GetMaxCameraAngle() = 0;
    virtual BOOL GetPostEffectEnable() = 0;
    virtual BOOL GetBloomEnable() = 0;
    virtual BOOL GetHDREnable() = 0;
    virtual BOOL GetDOFEnable() = 0;
    virtual BOOL GetShockWaveEnable() = 0;
    virtual BOOL GetHSIEnable() = 0;
    virtual BOOL GetMotionBlur() = 0;
    virtual BOOL GetDetail() = 0;
    virtual BOOL GetGodRay() = 0;
    virtual BOOL GetSSAO() = 0;
    virtual BOOL GetGlobalFog() = 0;
    virtual BOOL GetCurveCMYK() = 0;
    virtual BOOL GetEnableDynamicConverMap() = 0;
    virtual BOOL GetCpuSkin() = 0;
    virtual int  GetMaxNumCpuThread() = 0;
    virtual int  GetMinNumCpuThread() = 0;
    virtual BOOL GetFlexBodySmooth() = 0;
    virtual int  GetMaxTerrainDetail() = 0;
    virtual int  GetMinTerrainDetail() = 0;
    virtual int  GetMaxVegetationDensity() = 0;
    virtual int  GetMinVegetationDensity() = 0;
    virtual int  GetMinWaterDetail() = 0;
    virtual int  GetMaxWaterDetail() = 0;
    virtual BOOL GetEnableScaleOutput() = 0;
    virtual BOOL GetScaleOutputSmooth() = 0;
};

enum EM_ENGINEX_LOGIC_INTERSECT
{
    EM_ENGINEX_LOGIC_INTERSECT_DEFAULT_RANGE = 25600,
    EM_ENGINEX_LOGIC_INTERSECT_CAMERA = 1 << 0, //专用的标志，用于摄像机的碰撞方式
    EM_ENGINEX_LOGIC_INTERSECT_LOGIC = 1 << 1,  //专用的标志，用于和逻辑物件碰撞
    EM_ENGINEX_LOGIC_INTERSECT_OBJECT = 1 << 2,
    EM_ENGINEX_LOGIC_INTERSECT_TERRAIN = 1 << 3,
    EM_ENGINEX_LOGIC_INTERSECT_WATER = 1 << 4,
    EM_ENGINEX_LOGIC_INTERSECT_PLANE = 1 << 8,
    EM_ENGINEX_LOGIC_INTERSECT_SPHERE = 1 << 9,
    EM_ENGINEX_LOGIC_INTERSECT_LOGIC_ALL = 0xFFFFFFFF,
};

struct DECLSPEC_NOVTABLE IKG3DEngineXRepresentLogic 
{
    /*
    We always use the argument form of a line as intersection ray, which means
    , P(t)= vSrc + vNormalizedDir * t. This form is most commonly used in 3D maths.

    pfRet--return the t of the intersection point P, the coordinate of the P should be (vSrc + vNormalized * t).
    fTestRange--can be set as EM_ENGINEX_LOGIC_INTERSECT_DEFAULT_RANGE
    intersectType--combination of enum like EM_ENGINEX_LOGIC_INTERSECT_CAMERA
                    , for example, EM_ENGINEX_LOGIC_INTERSECT_CAMERA | EM_ENGINEX_LOGIC_INTERSECT_LOGIC
    */
    virtual ULONG RayIntersection(IKG3DScene* pScene, const D3DXVECTOR3& vSrc
        , const D3DXVECTOR3& vNormalizedDir, FLOAT fTestRange, DWORD intersectType, FLOAT* pfRet) = 0;   

    virtual HRESULT GetPickRayFromPrimaryWnd(IKG3DScene* pScene, const D3DXVECTOR2& vScreenPos, D3DXVECTOR3* pSrc, D3DXVECTOR3* pNormalizedDir) = 0;//input mouse pos, output the ray cast from the point direct into the screen.

    virtual HRESULT PickRayWalk(IKG3DScene* pScene, const D3DXVECTOR3& vSrc
        , const D3DXVECTOR3& vNormalizedDir, const D3DXVECTOR3& curPlayerPos, FLOAT fMaxWalkRange
        , D3DXVECTOR3* pPosToWalkTo, INT* pIntersectType);  //因为光和地形物件碰撞可能无结果,所以提供人物脚底和人物为中心的球两种补充碰撞。对应的，pIntersectType返回的结果可能是0, EM_ENGINEX_LOGIC_INTERSECT_PLANE, EM_ENGINEX_LOGIC_INTERSECT_SPHERE。3种。可以自行剔除。
};

interface IKG3DDynamicWeather
{
	// 天气效果
	virtual	VOID Enable(BOOL bEnable) = 0;
	virtual BOOL IsEnable() = 0;
	virtual VOID SetParameters(FLOAT fDensity, FLOAT fSpeed, 
		FLOAT fLength, FLOAT fWidth, FLOAT fAlpha, FLOAT fWind) = 0;
	virtual VOID GetParameters(FLOAT *pfDensity, FLOAT *pfSpeed, 
		FLOAT *pfLength, FLOAT *pfWidth, FLOAT *pfAlpha, FLOAT *pfWind) = 0;

	virtual HRESULT LoadTexture(const char *pFileName) = 0;
	virtual HRESULT GetTextureName(LPCSTR *ppszName) = 0;
	virtual void EnableSnowcover(BOOL bEnable) = 0;
	virtual BOOL IsSnowcover() = 0;
	virtual float GetSnowPrecent() = 0;
	virtual void SetSnowPrecent(float fPercent) = 0;

	virtual void EnableSplash(BOOL bEnable) = 0;
	virtual BOOL IsEnableSplash() = 0;
	virtual void EnableWaterDrop(BOOL bEnable) = 0;
	virtual BOOL IsEnableWaterDrop() = 0;
	virtual void EnableWaterDropShockWave(BOOL bEnable) = 0;
	virtual BOOL IsEnableWaterDropShockWave() = 0;

	virtual void GetGateValue(float &fSpeedGate,float &fDensityGate) = 0;
	virtual void SetGateValue(float fSpeedGate,float fDensityGate) = 0;

	virtual float GetBrightNessPrecent() = 0;
	virtual void SetBrightNessPrecent(float fPercent) = 0;
	// 编辑器专用（主要处理编辑器多场景显示的情况）
	//virtual VOID SetParametersForEditor(IKG3DScene* p3DScene, FLOAT fDensity, FLOAT fSpeed, 
	//	FLOAT fLength, FLOAT fWidth, FLOAT fAlpha, FLOAT fWind) = 0;
};

//class KG3DTextureHolder;
typedef enum
{
    MIRROR_AXIS_X = 0,
    MIRROR_AXIS_Y,
}FaceMirrorAxis;

typedef enum
{
    PASTE_MATHOD_REPLACE = 0,
    PASTE_MATHOD_ALPHABLEND,
}FacePasteMethod;

struct DecalInfo
{
	int nRoleType;	//角色体型
    int nType;//贴花类型
    int nShowID;  //贴花在该类型中的次序	
    TCHAR strFileName[MAX_PATH];//贴图名字
    TCHAR strAnnotate[MAX_PATH];//注释
    int nX;    //x
    int nY;    //y
    int nWidth;    //width
    int nHeight;   //height
    int nNeedMirror; //是否需要左右镜像
    FaceMirrorAxis nMirrorAxis; //镜像轴
    int nMirrorValue;  //镜像轴的值
    FacePasteMethod nPasteMethod;    //粘贴方法
    int nNeedShadow;    //是否需要名为"*_shadow"的底部阴影贴图
	int nNeedFlip;	//是否需要翻转
    inline bool operator<(const DecalInfo& other) const
    {
        return (nRoleType < other.nRoleType) 
			|| ((!(other.nRoleType < nRoleType) && nType < other.nType)) 
            || ((!(other.nRoleType < nRoleType) && !(other.nType < nType) && (nShowID < other.nShowID)));
    }
    bool operator==(const DecalInfo& other) const
    {
        return (nRoleType == other.nRoleType)
			&& (nType == other.nType)
            && (nShowID == other.nShowID)
            && !strcmp(strFileName, other.strFileName)
            && !strcmp(strAnnotate, other.strAnnotate)
            && (nX == other.nX)
            && (nY == other.nY)
            && (nWidth == other.nWidth)
            && (nHeight == other.nHeight)
            && (nNeedMirror == other.nNeedMirror)
            && (nMirrorAxis == other.nMirrorAxis)
            && (nMirrorValue == other.nMirrorValue)
            && (nPasteMethod == other.nPasteMethod)
            && (nNeedShadow == other.nNeedShadow)
			&& (nNeedFlip == other.nNeedFlip);
    }
    DecalInfo& operator=(const DecalInfo& other)
    {
		nRoleType = other.nRoleType;
        nType = other.nType;
        nShowID = other.nShowID;
        strncpy_s(strFileName, other.strFileName, MAX_PATH);
        strncpy_s(strAnnotate, other.strAnnotate, MAX_PATH);
        nX = other.nX;
        nY = other.nY;
        nWidth = other.nWidth;
        nHeight = other.nHeight;
        nNeedMirror = other.nNeedMirror;
        nMirrorAxis = other.nMirrorAxis;
        nMirrorValue = other.nMirrorValue;
        nPasteMethod = other.nPasteMethod;
        nNeedShadow = other.nNeedShadow;
		nNeedFlip = other.nNeedFlip;
        return *this;
    }
};

struct FaceBaseInfo
{
	int nRoleType;
    int nID;
    TCHAR strName[MAX_PATH];
    TCHAR strFileName[MAX_PATH];//贴图名字
    inline bool operator<(const FaceBaseInfo& other) const
    {
        return (nRoleType < other.nRoleType) || 
			(!(nRoleType < other.nRoleType) && (nID < other.nID));
    }
    bool operator==(const FaceBaseInfo& other) const
    {
        return (nRoleType == other.nRoleType)
			&& (nID == other.nID)
            && !strcmp(strName, other.strName)
            && !strcmp(strFileName, other.strFileName);
    }
    FaceBaseInfo& operator=(const FaceBaseInfo& other)
    {
		nRoleType = other.nRoleType;
        nID = other.nID;
        strncpy_s(strName, other.strName, MAX_PATH);
        strncpy_s(strFileName, other.strFileName, MAX_PATH);
        return *this;
    }
	FaceBaseInfo& operator=(const DecalInfo& decalInfo)
	{
		nRoleType = decalInfo.nRoleType;
		nID = decalInfo.nShowID;
		strncpy_s(strName, decalInfo.strAnnotate, MAX_PATH);
		strncpy_s(strFileName, decalInfo.strFileName, MAX_PATH);
		return *this;
	}
};

struct KG3DFaceDetail
{    
    int           m_nColorID;
    TCHAR         m_szName[MAX_PATH];
    float         m_fMainColorMin;
    float         m_fMainColorMax;
    float         m_fMainColorScale;
    D3DCOLORVALUE m_cMainColor;
    inline bool operator<(const KG3DFaceDetail& other) const
    {
        return m_nColorID < other.m_nColorID;
    }
    bool operator==(const KG3DFaceDetail& other) const
    {
        return (m_nColorID == other.m_nColorID)
            && (fabs(m_fMainColorMin - other.m_fMainColorMin) < 0.000001)
            && (fabs(m_fMainColorMax - other.m_fMainColorMax) < 0.000001)
            && (fabs(m_fMainColorScale - other.m_fMainColorScale) < 0.000001)
            && (fabs(m_cMainColor.r - other.m_cMainColor.r) < 0.000001)
            && (fabs(m_cMainColor.g - other.m_cMainColor.g) < 0.000001)
            && (fabs(m_cMainColor.b - other.m_cMainColor.b) < 0.000001)
            && (fabs(m_cMainColor.a - other.m_cMainColor.a) < 0.000001)
            && !strcmp(m_szName, other.m_szName);
    }
    KG3DFaceDetail& operator=(const KG3DFaceDetail& other)
    {
        m_nColorID = other.m_nColorID;
        m_fMainColorMin = other.m_fMainColorMin;
        m_fMainColorMax = other.m_fMainColorMax;
        m_fMainColorScale = other.m_fMainColorScale;
        m_cMainColor = other.m_cMainColor;
        strncpy_s(m_szName, other.m_szName, MAX_PATH);
        return *this;
    }
};
class IKG3DFaceDefinition;
interface IKG3DFaceMakerManager
{
	virtual HRESULT GetDecalDetail(KG3DFaceDetail& detail, int nRoleType, int nType, int nID, int nColorID) = 0;
    virtual int GetNumDecalTypes() = 0;
    virtual int GetNumBoneParams() = 0;
	//LoadFaceDefinitionFromINIFile使用后无需delete *ppRetFaceDefinition;
	virtual HRESULT LoadFaceDefinitionFromINIFile(IKG3DFaceDefinition** ppRetFaceDefinition, const char* szFileName) = 0;
};

interface IKG3DMeshMergeManager
{
	virtual const KG3D_FACE_PART_INFO_ARRAY* GetFacePartInfo(const int& nRoleType) = 0;
};

interface IKG3DFaceDefinition
{
    virtual const KG3D_CHAR_ARRAY *GetFaceParams() = 0;
    virtual const KG3D_FACE_DECAL_ARRAY *GetFaceDecals()  = 0;
	virtual int GetRoleType() = 0;
	virtual int GetFacePartID() = 0;
	virtual HRESULT SaveToFile(const char* szFileName) = 0;
};

//look at
interface IKG3DPSImage
{
	virtual HRESULT LoadSourceFromFile(const char* cszFileName) = 0;
	virtual HRESULT SaveToFile(const char* cszFileName) = 0;
	virtual HRESULT SetPSParam(const KG3DPSFilterType& FilterType, const KG3DPSImageParam& ImageParam) = 0;
	virtual HRESULT ReleaseImage() = 0;
};

interface IKG3DPSFilterManager
{
	virtual HRESULT GetPSImage(IKG3DPSImage** ppPSImage) = 0;
	virtual HRESULT SaveThumnail(const char* cszSourceFileName, const char* cszThumbnailFileName,
		int nWidth, int nHeight) = 0;
};



IKG3DEngineManager   *g_GetEngineManager();
IKG3DResourceManager *g_GetModelManager();

IKG3DUI&              g_GetUI();
IKG3DDebugInfo&       g_GetDebugInfo();

#define MAX_CHAR_PART 32
#define MAX_CHAR_BINDMODEL 32

struct KG3DModelInfo
{
	LPSTR szNameMesh;
	LPSTR szNameMaterial;
	int   nDetailTable;
	int   nDetailIndex;
};

struct KG3DBindModelInfo
{
	LPSTR m_szBindName;
};

struct KG3DCharacterDefine
{
	LPSTR szMDLName;
	int   m_nNumPart;
	KG3DModelInfo m_Parts[MAX_CHAR_PART];
	KG3DBindModelInfo m_BindModel[MAX_CHAR_BINDMODEL];
	
	KG3DCharacterDefine()
	{
		ZeroMemory(this,sizeof(KG3DCharacterDefine));
	}
};

typedef VOID* KG3DHANDLE;

interface IKG3DCharacter
{
	virtual HRESULT ForceSetBBox(D3DXVECTOR3 A,D3DXVECTOR3 B) = 0;
};

interface IKG3DCharacterTable
{
	virtual KG3DHANDLE LoadCharacter(KG3DCharacterDefine& Define) = 0;
	virtual IKG3DCharacter* FitcheResult(KG3DHANDLE hModel) = 0;
};

IKG3DCharacterTable *g_GetCharacterTable();


// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the DLL1_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// DLL1_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifndef DLLKG3DENGINE_API
#ifdef KG3DENGINE_DLL_EXPORTS
#define DLLKG3DENGINE_API extern "C" __declspec(dllexport)
#else
#define DLLKG3DENGINE_API extern "C" __declspec(dllimport)
#endif
#endif

DLLKG3DENGINE_API HRESULT Get3DEngineInterface(void** pEngineManager);
DLLKG3DENGINE_API HRESULT Get3DEngineXLogicInterface(void** ppEngineXLogic); //IKG3DEngineXRepresentLogic

#endif  // _KG3DINTERFACE_H_
