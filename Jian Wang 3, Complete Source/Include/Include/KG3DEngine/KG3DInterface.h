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

#include <vector>
#include <set>

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
	virtual unsigned GetcLastUseTime()  = 0;
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
	virtual HRESULT LoadResourceFromFile(const char cszFileName[], unsigned uFileNameHash, unsigned uOption, IKG3DResourceBase **ppRetResource) = 0;
	virtual HRESULT NewOneResourse(unsigned uType,                 IKG3DResourceBase **ppRetResource) = 0;
	//////////////////////////////////////////////////////////////////////////
	virtual HRESULT SetBalance(unsigned uSizeMemeryKB, unsigned uSizeVideoKB) = 0;
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
	MLO_ANI_MULTI          = (0x1 << 5),
	MLO_SFX_EDITING        = (0x1 << 8),
	MLO_MODEL_RECORD       = (0x1 << 9),
	MLO_MODEL_LOD          = (0x1 << 10),
	MLO_FORCE_DWORD         = 0xffffffff,
};

const DWORD MLO_MESH_MASK = MLO_MESH_BIP | MLO_MESH_SPEEDTREE | MLO_MESH_MULTI;
const DWORD MLO_TEXTURE_MASK = MLO_TEXTURE_MULTI;
const DWORD MLO_MATERIAL_MASK = MLO_MATERIAL_NOMAT | MLO_TEXTURE_MASK | MLO_MESH_MULTI;
const DWORD MLO_MULTI = MLO_MESH_MULTI | MLO_TEXTURE_MULTI | MLO_ANI_MULTI;


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

class IKG3DModel : public IKG3DResourceBase
{
public:
    virtual HRESULT SetModelColor(DWORD dwSubset, D3DCOLORVALUE color) = 0;
    virtual HRESULT GetModelColor(DWORD dwSubset, D3DCOLORVALUE* color) = 0;

	virtual HRESULT SetCaptionVisible(DWORD dwIndex, BOOL bVisible) = 0;
	virtual HRESULT SetCaption(DWORD dwIndex, LPCSTR strContent) = 0;
	virtual void    RemoveCaption() = 0;
	virtual HRESULT SetCaptionColor(DWORD dwIndex, const D3DCOLORVALUE& Color) = 0;
	virtual HRESULT SetPercentage(float fPercentage) = 0;
	virtual HRESULT SetPercentageStyle(const D3DCOLORVALUE &Color) = 0;
	virtual HRESULT SetPercentageVisible(BOOL bVisible) = 0;
	virtual void SetCaptionFloorHeight(float fHeight) = 0;

	virtual HRESULT AjustWorldDirection(const D3DXVECTOR3* pVecDir, const D3DXVECTOR3* pSelfDir) = 0;
	virtual HRESULT RegistereEventHandler(IKG3DAnimationEventHandler* pHandler) = 0;
	virtual HRESULT UnregisterEventHandler(IKG3DAnimationEventHandler* pHandler) = 0;
	virtual HRESULT FrameMove() = 0;

	virtual void GetRenderEnviromentParamenter(IKG3DScene* pScene) = 0;
	//载入动画
	virtual HRESULT LoadAnimationFromFile(LPCSTR strFileName,DWORD Option) = 0;
	
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

	virtual HRESULT SetBoneTransform(LPCSTR strBoneName, const BoneTransformationInputData& Data) = 0;
	virtual void EnableBoneTransform(BOOL bEnable) = 0;
	virtual BOOL IsBoneTransformEnable() = 0;
	virtual void SetTranslation(D3DXVECTOR3* pValue) = 0;
	virtual void SetRotation(D3DXQUATERNION* pValue) = 0;
	virtual void SetRotationCenter(D3DXVECTOR3* pValue) = 0;
	virtual void SetScaling(D3DXVECTOR3* pValue) = 0;
	virtual void SetScalingRotation(D3DXQUATERNION* pValue) = 0;
	virtual void SetScalingCenter(D3DXVECTOR3* pValue) = 0;

	virtual void GetTranslation(D3DXVECTOR3* pValue) = 0;
	virtual void GetRotation(D3DXQUATERNION* pValue) = 0;
	virtual void GetRotationCenter(D3DXVECTOR3* pValue) = 0;
	virtual void GetScaling(D3DXVECTOR3* pValue) = 0;
	virtual void GetScalingRotation(D3DXQUATERNION* pValue) = 0;
	virtual void GetScalingCenter(D3DXVECTOR3* pValue) = 0;

	virtual VOID SetAttachType(MODELCLOSEGROUND_TYPE nType,IKG3DScene* pScene = NULL) = 0;

	virtual void ResetTransform() = 0;


	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual HRESULT ChainAdd( IKG3DModel *pOtherModel ) = 0;
	virtual HRESULT ChainRemove( IKG3DModel *pOtherModel ) = 0;

	virtual HRESULT ChainEnable( ) = 0;
	virtual HRESULT ChainDisable( ) = 0;

	virtual void SetBoneLODLevel(unsigned int uLevel) = 0;
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	virtual HRESULT BindToSocket(IKG3DModel *pModel, const char* cszSocketName) = 0;
	virtual HRESULT BindToBone(IKG3DModel *prModel, const char* strBoneName) = 0;
	virtual HRESULT UnBindFromOther() = 0;
	virtual int FindBone(const char* strBoneName, BindExtraInfo* pExtInfo) = 0;
	virtual int FindSocket(const char* strSocketName, BindExtraInfo* pExtInfo) = 0;
	virtual HRESULT GetBoneMatrix(const BindExtraInfo* pInfo, D3DXMATRIX* pmatResult, D3DXVECTOR3* pvec3Offset) = 0;
	virtual HRESULT GetSocketMatrix(const BindExtraInfo* pInfo, D3DXMATRIX* pmatResult, D3DXVECTOR3* pvec3Offset) = 0;
	virtual HRESULT GetSocketMatrix(unsigned int uSocketIndex,D3DXMATRIX& mat,D3DXVECTOR3* pvec3Offset = NULL) =0;
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	virtual int AttachModel(IKG3DModel *pModel) = 0;
	virtual void DetachModel(IKG3DModel* pModel) = 0;

	virtual HRESULT Render(unsigned uOption, void* pExtInfo) = 0;
	virtual HRESULT RenderToScreen(D3DXVECTOR2 const* pA, 
		D3DXVECTOR2 const* pC, 
		D3DXVECTOR2 const* pUVA, 
		D3DXVECTOR2 const* pUVC, 
		float fZ, 
		DWORD dwFlags,
		DWORD dwBackColor,
		void* pExtInfo) = 0;
	
	virtual HRESULT RenderToTexture(DWORD dwTextureID, 
		D3DXVECTOR2 const* pA, 
		D3DXVECTOR2 const* pC, 
		D3DXVECTOR2 const* pUVA, 
		D3DXVECTOR2 const* pUVC,
		float fZ, 
		DWORD dwFlags,
		DWORD dwBackColor,
		DWORD dwRenderOption,
		void* pExtInfo) = 0;

	virtual HRESULT SetAlpha(float fAlpha, BOOL bUseSpecial) = 0;
	virtual void SetHighLightLevel(float fIllumination, BOOL bInherit) = 0;
	virtual float GetHightLightLevel() = 0;
	virtual float GetAlpha() = 0;

	virtual BOOL IsLoaded() = 0;
    virtual BOOL IsVisible() const = 0;

	virtual void GetBBox(D3DXVECTOR3& vec3A, D3DXVECTOR3& vec3B) = 0;

	virtual HRESULT LoadMaterialFromFile(LPCSTR strFileName, DWORD Option) = 0;

	virtual IKG3DAnimationController* GetAnimationController(enuAnimationControllerPriority nPriority) = 0;
    virtual IKG3DAnimationController* GetSplitAnimationContorller(DWORD dwPartIndex, DWORD dwControllerIndex) = 0;

    virtual IKG3DSFXSuede* GetSFXSuede() = 0;
	
	virtual HRESULT GetModel(unsigned int uIndex, IKG3DModel** ppModel) = 0;
    virtual void    GetBindToOrgModel(std::set<IKG3DModel*> &set_OrgModel) = 0;
    // 主要用于在公告版上绘制
    // 得到可绘制纹理数
    virtual HRESULT GetRenderTargetTextureCount(OUT DWORD* pTexCount) = 0;
    virtual HRESULT SetCallbackRender(CallbackRender fpCallbackRender, void* pUserData) = 0;

    // dwSubIndex 第几块公告版
    // dwTexIndex 第几层纹理
    virtual HRESULT GetRenderTargetTexture(OUT DWORD* pResourceId, IN DWORD dwTexIndex = 0) = 0;
	virtual HRESULT ChangeModel(unsigned int uIndex, IKG3DModel* pModel) = 0;

	virtual HRESULT EnableCloseFloor(int nEnableFlag) = 0;
	
	virtual int GetBindToSocketModel(const char cszSocketName[], std::vector<IKG3DModel*> &vecpModel) = 0;
	virtual HRESULT GetAllChilds(std::vector<IKG3DModel*> &vecpChildsModel) = 0;
	
	virtual void SetbDrawBigBox(BOOL val) = 0;
	virtual HRESULT GetName(LPCTSTR *ppszName) = 0;
	// just for sfx 
    STDMETHOD(UpdateChannelEffectPos)(D3DXVECTOR3 v1, D3DXVECTOR3 v2) PURE;
	virtual void SetFaceMotionMode() = 0;

	virtual HRESULT GetParentModel(IKG3DModel **ppModel) = 0;

	virtual HRESULT SetDetail(int nDefineTable,int nIndex) = 0;//模型偏色和花纹
	virtual HRESULT GetDetail(int* pnDefineTable,int* pnIndex) = 0;

	virtual HRESULT GetMaterialSubsetOption(INT nSubIndex, DWORD* dwOption) = 0;	
	virtual HRESULT SetMaterialSubsetOption(INT nSubIndex, DWORD dwOption) = 0;		
	virtual HRESULT GetNumMaterial(INT* pnCount) = 0;

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
	virtual DWORD GetMotionExtraInfo() = 0;
	virtual void SetMotionExtraInfo(DWORD dwMotionExtraInfo) = 0;
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
#ifndef tstring
#if defined(UNICODE) | defined(_UNICODE)
#define tstring string
#else
#define tstring wstring
#endif
#endif

typedef struct _KG3DREGION_INFORMER_LOADFILE_PARAM  
{
	enum
	{
		MAX_PIXEL_TOLERANCE = UCHAR_MAX,
		INVALID_MAX_TEXTURE_ID = ULONG_MAX/ 2,
	};
	INT		nPixelTolerance;
	INT		nSampleTimes;
	BOOL	m_bNeedPreviewTex;
	DWORD	dwRetTextureID;
	INT		nEliminateIsoDataCount;
	INT		nTotalValue;
	UINT	uHowManyPixelsInOneRegion;
	INT		nRegionXCount;
	INT		nRegionZCount;
	std::tstring	strError;	 
#ifdef __cplusplus
	_KG3DREGION_INFORMER_LOADFILE_PARAM()
	{
		ZeroMemory(this, sizeof(_KG3DREGION_INFORMER_LOADFILE_PARAM));
		nPixelTolerance = 2;
		nSampleTimes = 1;
		m_bNeedPreviewTex = FALSE;
		dwRetTextureID = 0;
		nEliminateIsoDataCount = 0;
		nTotalValue = 0;
		uHowManyPixelsInOneRegion = 1;
	}
#endif
}KG3DREGION_INFORMER_LOADFILE_PARAM;

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

class IKG3DScene : public IKG3DResourceBase
{
public:
	virtual HRESULT FrameMove() = 0;
	virtual HRESULT Render(unsigned uOption) = 0;
	virtual HRESULT RenderToScreen(D3DXVECTOR2 const* pA, D3DXVECTOR2 const* pC, D3DXVECTOR2 const* pUVA, D3DXVECTOR2 const* pUVC, float fZ, DWORD dwFlags) = 0;

	virtual HRESULT AddOutputWindow(LPCTSTR szName, HWND hWnd, DWORD dwType, DWORD_PTR dwOption, int* pOutputWindowID) = 0;
	virtual HRESULT RemoveOutputWindow(int nOutputWindowID) = 0;

    virtual HRESULT EnablePostRenderEffect(int nOutputWindowID, BOOL bEnable) = 0;
    virtual HRESULT EnablePostRenderEffect(int nOutputWindowID, PostRenderEffectType nType, BOOL bEnable) = 0;

	virtual HRESULT AddRenderEntity(IKG3DResourceBase *pEntity,    unsigned uClass, BOOL bSelectable,BOOL bLight) = 0;
	virtual HRESULT RemoveRenderEntity(IKG3DResourceBase *pEntity, unsigned uClass, BOOL bSelectable) = 0;
	virtual HRESULT RemoveSelectableModel(IKG3DResourceBase *pEntity) = 0;

	virtual IKG3DCamera *GetCurrentCamera() = 0; 
	virtual HRESULT SetCurrentCamera(IKG3DCamera *pCamera) = 0; 

    virtual HRESULT GetFloor(const D3DXVECTOR3* pvInput, FLOAT* pfRet) = 0;//输入3D坐标，向下发射的射线，查此点场景的高度
	virtual DWORD   GetGroundType(const D3DXVECTOR3 &vec3Pos) = 0;

	virtual HRESULT GetWaterHeight(D3DXVECTOR3* pOut, D3DXVECTOR3* pIn) = 0;
	virtual HRESULT GetHeight(D3DXVECTOR3* pOut,D3DXVECTOR3* pIn) = 0;//得到的是地形的高度，不包括物体

	virtual HRESULT LogicalToScene(D3DXVECTOR3* pPos, float fX, float fY, float fZ, BOOL bOnFloor) = 0;
	virtual HRESULT SceneToLogical(int* pX, int* pY, int* pZ, D3DXVECTOR3 Pos) = 0;
    virtual HRESULT ScenePosToScreenPos(D3DXVECTOR3 const& vScenePos, float& fScreenX, float& fScreenY) = 0;

	virtual HRESULT GetSelectModelList(const D3DXVECTOR2& vPosScreen, std::vector<IKG3DModel*>& pList, BOOL bGetNearestOrAll) = 0;//bGetNearestOrALL如果取TRUE则只得到第一个物件，否则得到已经从近到远排序的一串物件，最多有限制。
	virtual HRESULT GetSelectPosition(D3DXVECTOR2 const& vScale, D3DXVECTOR3& vPosition) = 0;

    virtual HRESULT GetTerrainCross(D3DXVECTOR3* vInter, const D3DXVECTOR3& vSrc, const D3DXVECTOR3& vDst) = 0;
	virtual HRESULT OnResizeWindow(PRECT const pRect) = 0;



	//////////////////////////////////////////////////////////////////////////

	virtual HRESULT GetMinimapLayer(IN const D3DVECTOR &vPos, OUT int &nLayer) = 0;

	///////////////////////////////////////////////////////////////////////////
	virtual HRESULT GetCameraMovement(IKG3DSceneCameraMovement** ppiCameraMovement) = 0;

	//////////////////////////////////////////////////////////////////////////
	virtual HRESULT LoadFromFileEx(const char cszFileName[], unsigned uFileNameHash, unsigned uOption, DWORD_PTR pKG3DSCENE_INITSTRUCT, DWORD_PTR LOption) = 0;

	virtual HRESULT ClearAllHelpLine() = 0;
	virtual HRESULT SetHelpLineSize(size_t nLine, size_t nSize) = 0;
	virtual HRESULT SetHelpLineStart(size_t nLine, size_t nStart) = 0;
	virtual HRESULT SetHelpLine(size_t nLine, int nSetID, size_t nBegin, size_t nCount, D3DCOLOR color, D3DXVECTOR3* pPos) = 0;
	virtual HRESULT GetHelpLine(size_t nLine, size_t* pPoint, D3DXVECTOR3** ppPos) = 0;
    
    virtual HANDLE  AddSceneSigns(const D3DXVECTOR3& vPos) = 0;
    virtual void    DelSceneSings(HANDLE Handle) = 0;
	
	virtual HRESULT SetFocus(D3DXVECTOR3& vecPos) = 0;

	virtual float GetLoadingProcess() = 0;
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
		SoundBallData *pData) = 0;

	virtual HRESULT SaveToFile(LPCTSTR strFileName,
		SoundBallData *pData) = 0;

	virtual void Refresh(LPCSTR strFileName) = 0;
};

typedef void(*pfOnPresent)(double);
typedef void(*pfOnRenderEnd)(double);
struct IKG3DSoundShell;
class IKG3DEngineOptionCaps;

class IKG3DEngineManager
{
public:
	virtual HRESULT Init(unsigned uMode, unsigned int uFlag, HWND hBaseWindow, HWND hRenderWindow) = 0; // uMode = 0 : windowed, uMode = 1: fullscreen
	virtual HRESULT UnInit() = 0;

    virtual IKG3DResourceManager* Get3DModelTable() = 0;
	virtual IKG3DSoundBallTable* GetSoundBallTable() = 0;
    virtual IKG3DUI* Get3DUI() = 0;
	virtual IKG3DFaceMotionSettings* GetFaceMotionSettings() = 0;

	virtual HRESULT ProcessMessage(unsigned message, WPARAM uParam, LPARAM ulParam) = 0;//没有检索到引用，去掉这个接口，引擎不直接处理Windows消息。即使要，也必须至少进行一次Mapping，没有这一层的话，至少键Map就会很难做，消息处理过才传入比较好	//<PROCESS_MESSAGE>

    virtual HRESULT FrameMove() = 0;
    virtual HRESULT Render() = 0;
	virtual void SetOnPresentCallBackFunc(pfOnPresent pfCallback) = 0;
	virtual void SetOnRenderEndCallBackFunc(pfOnPresent pfCallback) = 0;
	virtual HRESULT NewOneScene(unsigned uType, IKG3DScene **ppRetScene) = 0;
	virtual HRESULT RemoveScene(IKG3DScene *pScene) = 0;

	virtual void SetSoundFocusScene(IKG3DScene *pScene) = 0;
	virtual IKG3DScene* GetSoundFocusScene() = 0;
    // 客户端引擎选项 Add by FengBo 2007-9-5 10:35
	virtual HRESULT GetEngineOption(KG3DEngineOption* pEngineOption) = 0;
	virtual HRESULT SetEngineOption(const KG3DEngineOption* pEngineOption) = 0;	//Set之前先Get，然后改一部分，再Set
	virtual	HRESULT GetEngineCaps(KG3DEngineCaps* pCaps) = 0;

    virtual int GetColorCurveStypeNum() = 0;
    virtual void GetColorCurveStypeName(char szName[], int nIndex) = 0;

	virtual HRESULT ExecuteCommand(LPCTSTR szCommand) = 0;

    // 视频录像
    virtual HRESULT SetIPPVideo(void* pfnCreateIPPCodec) = 0;
	virtual HRESULT MovieRecord(LPCTSTR szFolder, int nSizeScale, UINT uFilter, UINT uQuality, int nEncoder, int nFps) = 0;
	virtual HRESULT MovieStop() = 0;
	virtual BOOL    MovieReady() const = 0;
	virtual VOID    MovieViewport(RECT const& rcViewport) = 0;

	//事件录像
	virtual BOOL    CanRecord() = 0;
	virtual BOOL    IsRecording() = 0;
	virtual HRESULT StartRecord(LPCTSTR szFolder,unsigned uMode) = 0;
	virtual HRESULT StopRecord() = 0;
	
	virtual IRecPlayer* GetNewRecPlayer() = 0;
	virtual RecordOption* GetRecordOption() = 0;
	virtual void SetRecordOption(const RecordOption *pOption) = 0;
	//录像相关End

    
    virtual BOOL	GetRenderOption(RENDER_OPTION opt) = 0;
    virtual HRESULT SetRenderOption(RENDER_OPTION opt, BOOL bEnable) = 0;

    virtual BOOL    GetFrameMoveOption(FRAMEMOVE_OPTION opt) = 0;
    virtual HRESULT SetFrameMoveOption(FRAMEMOVE_OPTION opt, BOOL bEnable) = 0;

    virtual DWORD   GetRenderParam(RENDER_PARAM Param) = 0;
    virtual HRESULT SetRenderParam(RENDER_PARAM Param, DWORD Value) = 0;



	//区域设定///////////////////////////////////////////////////////////////////////
	virtual HRESULT GetRegionInfoManager(const char cszFileName[]
										, unsigned uFileNameHash
										, DWORD_PTR dwOption
										, IKG3DRegionInfoManager** ppRIM) = 0;	// dwOption是KG3DREGION_INFORMER_LOADFILE_PARAM指针，如果传入0，使用默认

	virtual HRESULT InitGameContext(KG3D_GAME_INIT_CONTEXT* pContext) = 0;	//用于游戏运行时上下文，需要和Init分离，因为有些东西Init的时候不知道
	virtual HRESULT GetInterface(DWORD dwType, DWORD_PTR p1, DWORD_PTR p2, LPVOID* ppInterface) = 0;	//相当于QueryInterface，但不加引用计数

	virtual IKG3DEnventCenter* GetEventCenter() = 0;
	
	virtual LPDIRECT3DDEVICE9 GetDevice() = 0;
	virtual LPDIRECT3D9	GetD3D() = 0;

	virtual void SetSoundShell(IKG3DSoundShell *pShell) = 0;//设置使用的IKG3DSoundShell

    virtual IKG3DEngineOptionCaps* CreateIKG3DEngineOptionCaps() = 0;
    virtual void RemoveKG3DEngineOptionCaps(IKG3DEngineOptionCaps* pIEngineOptionCaps) = 0;
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

enum { KG3DUI_IMAGE_FLAGS_NONE          = 0x00 };
enum { KG3DUI_IMAGE_FLAGS_POOL_DEFAULT  = 0x01 };   // 尽量少用，没这标志的为POOL_MANAGED
enum { KG3DUI_IMAGE_FLAGS_HDC           = 0x02 };   // 符合 HDC 要求的图像格式

enum
{
	KG3DUI_PART_TYPE_TIMER,
	KG3DUI_PART_TYPE_X_MIN_TO_MAX,
	KG3DUI_PART_TYPE_X_MAX_TO_MIN,
	KG3DUI_PART_TYPE_Y_MIN_TO_MAX,
	KG3DUI_PART_TYPE_Y_MAX_TO_MIN,
};

enum RS2_FONT_ITEM_PARAM 
{ 
	RS2_MAX_FONT_ITEM_NUM = 8 
};

struct KG3DUIVertex2
{
	D3DXVECTOR2	v2Vertex;
	D3DCOLOR	crDiffuse;
};

struct KG3DUILine2
{
	D3DXVECTOR2	v2Min;
	D3DXVECTOR2	v2Max;
	D3DCOLOR	crMin;
	D3DCOLOR	crMax;
};

struct KG3DUIRect2
{
	D3DXVECTOR2	v2Min;
	D3DXVECTOR2 v2Max;
	D3DCOLOR	crDiffuse;
};

struct KG3DUIRectPart2 : public KG3DUIRect2
{
	DWORD		dwType;
	float		fRatio;
};

struct KG3DUIText2
{
	D3DXVECTOR2 v2Min;
	D3DXVECTOR2 v2Max;
	D3DCOLOR	crFont;
	D3DCOLOR	crBorder;
	D3DCOLOR	crShadow;
	DWORD		dwFontID;
	float		fScale;
	float		fSpacing;
	int			nTextLength;
	WCHAR		wszText[KG3DUI_TEXT_LEN];
	BYTE		byAlpha;
	BYTE		byBorder;
	BYTE		byShadow;
	BYTE		byPading;
};


struct KG3DUIImage2
{
	D3DXVECTOR2 v2Min;
	D3DXVECTOR2 v2Max;
	D3DXVECTOR2	v2UVMin;
	D3DXVECTOR2 v2UVMax;
	D3DXCOLOR	crDiffuse;
	DWORD		dwImageID;
};


struct KG3DUIImageRotate2 : public KG3DUIImage2
{
	union
	{
		float fRotationCW;
		float fRatio;
	};
};

struct KG3DUIImagePart2 : public KG3DUIImageRotate2
{
	DWORD dwType;
};


struct KG3DUIScene2
{
	D3DXVECTOR2 v2Min;
	D3DXVECTOR2 v2Max;
	IKG3DScene*	p3DScene;
	DWORD		dwFlags;
    UINT        uViewportWidth;
    UINT        uViewportHeight;
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

struct KG3DUIImageRect
{
	float top;
	float left;

	float width;
	float height;
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
};

class IKG3DUI
{
public:
	virtual ~IKG3DUI() {}

	virtual HRESULT SetHWnd(HWND hWnd) = 0;

    virtual HRESULT SetDeviceCallback(IKG3DeviceCallback* pCallback) = 0;

	virtual HRESULT LoadFont(DWORD dwFontID, LPCSTR szFilePath, float fPixel, DWORD dwStyle) = 0;
	virtual HRESULT UnloadFont(DWORD dwFontID) = 0;
	virtual HRESULT UnloadAllFont() = 0;

	virtual HRESULT CreateImage(UINT uWidth, UINT uHeight, LPDWORD pdwImageID, DWORD dwFlags) = 0;
	virtual HRESULT DuplicateImage(DWORD dwImageID, DWORD dwFlags, LPDWORD pdwNewImageID) = 0;
	virtual HRESULT GrayImage(DWORD dwImageID, LPDWORD pdwNewImageID) = 0;
	virtual HRESULT MaskImage(DWORD dwImageID, DWORD dwMaskImageID) = 0;
	virtual HRESULT LoadImage(LPCTSTR szFilePath, LPDWORD pdwImageID) = 0;
	virtual HRESULT UnloadImage(DWORD dwImageID) = 0;
	virtual HRESULT UnloadAllImage() = 0;
    virtual HRESULT SaveImage(LPCTSTR szFilePath, DWORD dwImageID) = 0;
	virtual HRESULT RegisterSliceImageSize(UINT uWidth, UINT uHeight) = 0;

    virtual HRESULT SetupD3DDeviceCursor() = 0;
    virtual HRESULT SetD3D9DeviceCursor(HCURSOR hCursor) = 0;
    virtual HRESULT SetD3D9DeviceCursorPosition(INT nX, INT nY, DWORD dwFlags) = 0;
    virtual HRESULT ShowD3D9DeviceCursor(BOOL bShow) = 0;
    virtual HRESULT ClipD3DDeviceCursor(BOOL bClip) = 0;
    virtual BOOL IsShowD3D9DeviceCursor() const = 0;
    virtual BOOL IsClipD3D9DeviceCursor() const = 0;

	virtual HRESULT CreateScene(IKG3DScene** pp3DScene) = 0;
	virtual HRESULT UnloadScene(IKG3DScene* p3DScene) = 0;
	virtual HRESULT GetImageData(DWORD dwImageID, UINT uWidth, UINT uHeight, BYTE* pData, UINT uLength, BOOL bUpToDown) const = 0;
	virtual HRESULT GetImageSize(DWORD dwImageID, UINT* puWidth, UINT* puHeight) const = 0;

	virtual HRESULT FillTriangleFan(KG3DUIVertex2 const* pBuffer, size_t nCount) = 0;

    /*
      the nQuality (0 ~ 100) just use to D3DXIFF_JPG file format
     */
    virtual HRESULT ScreenShot(const char szFilePath[], D3DXIMAGE_FILEFORMAT eType, int nQuality) = 0;  
	virtual HRESULT LoadText(KG3DUIText2 const& text) = 0;

	virtual HRESULT DrawMultiLine(KG3DUILine2 const* pBuffer, size_t nCount) = 0;
	virtual HRESULT DrawMultiRect(KG3DUIRect2 const* pBuffer, size_t nCount) = 0;
	virtual HRESULT DrawMultiText(KG3DUIText2 const* pBuffer, size_t nCount) = 0;
	virtual HRESULT FillMultiRect(KG3DUIRect2 const* pBuffer, size_t nCount) = 0;
	virtual HRESULT DrawMultiImage(KG3DUIImage2 const* pBuffer, size_t nCount) = 0;
	virtual HRESULT DrawMultiScene(KG3DUIScene2 const* pBuffer, size_t nCount) = 0;
	virtual HRESULT FillMultiRectPart(KG3DUIRectPart2 const* pBuffer, size_t nCount) = 0;
	virtual HRESULT DrawMultiImagePart(KG3DUIImagePart2 const* pBuffer, size_t nCount) = 0;
	virtual HRESULT DrawMultiImageRotate(KG3DUIImageRotate2 const* pBuffer, size_t nCount) = 0;

	virtual HRESULT DrawMultiImageToBuffer(KG3DUIImage2 const* pBuffer, size_t nCount, UINT uWidth, UINT uHeight, BYTE *pData, size_t uLength, BOOL bUpToDown) = 0;

	virtual HRESULT DrawUserdataToImage(DWORD dwImageID, KG3DUIDrawUserdata DrawUserdata,void* pUserData) = 0;

	virtual HRESULT DrawOleToImage(LPUNKNOWN pUnknown, DWORD dwImageID) = 0;

	virtual HRESULT BeginScene() = 0;
	virtual HRESULT EndScene() = 0;

	virtual HRESULT BeginRenderToScreen() = 0;
	virtual HRESULT EndRenderToScreen() = 0;

    virtual HRESULT Present() = 0;

	virtual HRESULT BeginRenderToTexture(DWORD dwTextureID, UINT uMipmapLevel) = 0;
	virtual HRESULT EndRenderToTexture() = 0;

	virtual HRESULT BeginRenderToImage(DWORD dwImageID) = 0;
	virtual HRESULT EndRenderToImage() = 0;
	virtual HRESULT BeginStencil() = 0;
	virtual HRESULT SetStencilFunc() = 0;
	virtual HRESULT EndStencil() = 0;

	virtual HRESULT GetCharWidth(DWORD dwFontID, FLOAT fScale, FLOAT& fWidth) const = 0;
	virtual HRESULT GetCharHeight(DWORD dwFontID, FLOAT fScale, FLOAT& fHeight) const = 0;
	virtual HRESULT GetTextExtent(DWORD dwFontID, LPCWSTR wszText, int nTextLength, FLOAT &fWidth, FLOAT &fHeight, FLOAT fSpace, FLOAT fScale, BOOL bBorder) const = 0;
	virtual HRESULT GetTextPosExtent(DWORD dwFontID, LPCWSTR wszText, int nTextLength, FLOAT fCursorPos, LPINT lpCharPos, FLOAT fSpace, FLOAT fScale, BOOL bBorder) const = 0;

    virtual HRESULT OnCreateDevice(LPDIRECT3DDEVICE9 pd3dDevice, D3DSURFACE_DESC const* pBackBufferSurfaceDesc, D3DPRESENT_PARAMETERS const* pPresentParameters) = 0;
    virtual HRESULT OnDestroyDevice() = 0;
	virtual HRESULT OnLostDevice() = 0;
	virtual HRESULT OnResetDevice(LPDIRECT3DDEVICE9 pd3dDevice, D3DSURFACE_DESC const* pBackBufferSurfaceDesc, D3DPRESENT_PARAMETERS const* pPresentParameters) = 0;

    virtual HRESULT GetDeviceSettings(KG3DDeviceSettings* pSettings) = 0;
    virtual HRESULT SetDeviceSettings(KG3DDeviceSettings* pSettings) = 0;
	virtual HRESULT SetViewportSize(UINT uWidth, UINT uHeight) = 0;

	virtual HRESULT UpdateMultiSceneViewport(KG3DUIScene2 const* pBuffer, size_t nCount) = 0;

	virtual VideoMemoryInfo GetVideoMemeryInfo() const = 0;
	virtual UINT GetAvailableTextureMem() const = 0;
	virtual void GetUITextureUsage(KG3DUITextureUsage& Usage) const = 0;

	virtual UINT GetAllowableAdapterModeCount() const = 0;
    virtual HRESULT GetAllowableAdapterMode(D3DDISPLAYMODE* pAdapterMode, UINT* puCount) const = 0;

#if defined(DEBUG) | defined(_DEBUG)
	virtual LPDIRECT3DDEVICE9 GetDevice() = 0;
#endif
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

class IKG3DEngineOptionCaps
{
public:
    virtual HRESULT GetEngineOptionCaps(KG3DEngineOption& EngineOption) = 0;
    virtual std::vector<KADAPTERMODE>* GetAdapterModes() = 0;
    virtual std::vector<int>* GetMultiSampleType() = 0;
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
    virtual int*  GetModelShadowType() = 0;
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
    virtual std::vector<int>* GetShaderModel() = 0;
};


IKG3DEngineManager   *g_GetEngineManager();
IKG3DResourceManager *g_GetModelManager();

IKG3DUI&              g_GetUI();
IKG3DDebugInfo&       g_GetDebugInfo();

#endif  // _KG3DINTERFACE_H_