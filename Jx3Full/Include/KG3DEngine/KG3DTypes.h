//////////////////////////////////////////////////////////////////////////////////////
//
//  FileName    :   KG3DTypes.h
//  Version     :   1.0
//  Creater     :   YangLin
//  Date        :   2005/7/7 19:33:40
//  Comment     :   
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#ifndef _KG3DTYPES_H_
#define _KG3DTYPES_H_   1
#include <d3d9types.h>
#include <d3dx9tex.h>
#include <string>
#include <vector>
#define MAX_BONE_LOD_LEVEL           1

#define MESHTYPE_DEFAULT              0
#define MESHTYPE_TERRAIN              1
#define MESHTYPE_STRIP                2
#define MESHTYPE_GROUP                3
#define MESHTYPE_SKYBOX               4
#define MESHTYPE_LENSFLARE           5
#define MESHTYPE_MAINTOOL             6
#define MESHTYPE_MOVEGRID             7
#define MESHTYPE_ROTATEGRID			  8
#define MESHTYPE_OBJECTTABLETOOL      9
#define MESHTYPE_MATERIALTOOL         10
#define MESHTYPE_COLORPICK            11
#define MESHTYPE_SLIDEBAR             12
#define MESHTYPE_COMMANDBAR           13
#define MESHTYPE_EDITCTRL             14
#define MESHTYPE_TREECTRL             15
#define MESHTYPE_LISTCTRL             16
#define MESHTYPE_ITEM				  17
#define MESHTYPE_LISTBOX			  18
#define MESHTYPE_ANIMATIONTOOL		  19
#define MESHTYPE_MESHTOOL			  20
#define MESHTYPE_COMBOBOX			  21
#define MESHTYPE_MESHSELECT			  22
#define MESHTYPE_BILLBOARD			  23
#define MESHTYPE_PROPERTYSET		  24
#define MESHTYPE_BLADE				  25
#define MESHTYPE_SCREENSFX			  26
#define MESHTYPE_HALO				  27
#define MESHTYPE_LINEGRASS			  28
#define MESHTYPE_PARTICLESYSTEM		  29
#define MESHTYPE_WINBASE              30
#define MESHTYPE_BUTTON               31
#define MESHTYPE_TERRAINLOD           50
#define MESHTYPE_LAYEREDVOLUMETRICFOG 51
#define MESHTYPE_DYNAMICLIGHTNING     52
#define MESHTYPE_SPEEDTREE			  53
#define MESHTYPE_SCENESFX             54
#define MESHTYPE_MODELST              55
#define MESHTYPE_FARMOUNTAIN		  56///远山
#define MESHTYPE_SUBDEV               60
#define MESHTYPE_WATER                61
#define MESHTYPE_BELT                 62
#define MESHTYPE_POINTLIGHT           63

#define MESHTYPE_SFX                  70
#define MESHTYPE_SUEDE                80

#define MESHTYPE_PHYSX                90
#define MESHTYPE_PARTICLE             100

#define MESH_DELETED       1
#define MESH_OPTIMIZED     (1<<1)
#define MESH_SKINED        (1<<2)
#define MESH_BILLBOARD     (1<<3)
#define MESH_BIND          (1<<4)
#define MESH_NOMATERAIL    (1<<5)
#define MESH_PROGRESS      (1<<6)
#define MESH_4LINK         (1<<7)

//MeshHead Extend Block usage
#define MESH_SAVE_BONEBBOX  1
#define MESH_SAVE_BLENDMESH (1<<1)
#define MESH_KEEP_NORMALMESH (1<<2)
#define MESH_LOADOPTION_RLCALL (1<<3)
//MeshHead Extend Block usage end

#define  SCENETYPE_DEFAULT              0
#define  SCENETYPE_SCENEEDITOR          1
#define  SCENETYPE_MODELEDITOR          2
#define  SCENETYPE_OBJECTEDITOR         3
#define  SCENETYPE_SFXEDITOR            4
#define  SCENETYPE_SWORDTEST            5
#define  SCENETYPE_CLIENT               6//客户端用场景
#define  SCENETYPE_DATAFLOWEDITOR       7
#define  SCENETYPE_PVSEDITOR            8
#define	 SCENETYPE_PHYSICSEDITOR        9
#define	 SCENETYPE_PICTUREVIEWER        10
#define  SCENETYPE_PARSYSEDITOR         11

// ait depth texture format (chiyer)
#define FOURCC_DF16 ((D3DFORMAT) MAKEFOURCC('D','F','1','6'))
#define FOURCC_DF24 ((D3DFORMAT) MAKEFOURCC('D','F','2','4'))

#pragma warning(disable : 4480)
enum SCENEENTITYTYPE : DWORD
{
	SCENEENTITY_NONE                = 0,
	SCENEENTITY_OBJECT              = 1,
	SCENEENTITY_MODEL               = 1 << 1,
	SCENEENTITY_MODELSUBSET         = 1 << 2,
	SCENEENTITY_POSITION            = 1 << 3,
	SCENEENTITY_DIRECTION           = 1 << 4,
	SCENEENTITY_DUMMY		        = 1 << 5,
	SCENEENTITY_TEST		        = 1 << 6,
	SCENEENTITY_LIGHT               = 1 << 7,
	SCENEENTITY_OBJECT_PART         = 1 << 8,
	SCENEENTITY_GROUP               = 1 << 9,
	SCENEENTITY_SOCKET              = 1 << 10,
	SCENEENTITY_SFX_LAUNCHER        = 1 << 11,
	SCENEENTITY_SFX_FORCE_FIELD     = 1 << 12,
	SCENEENTITY_SFX_BILLBOARD       = 1 << 13,
	SCENEENTITY_SFX_TRACK           = 1 << 14,
	SCENEENTITY_SFX_METEOR          = 1 << 15,
	SCENEENTITY_SFX_SUEDE           = 1 << 16,
	SCENEENTITY_SPEEDTREELEAF       = 1 << 17,
	SCENEENTITY_SPEEDTREELEAFGROUP  = 1 << 18,
	SCENEENTITY_TERRAINCONTROLPOINT = 1 << 19,
    SCENEENTITY_PVS_PORTAL          = 1 << 20,
    SCENEENTITY_SCENE_SIGNS         = 1 << 21,
	SCENEENTITY_CAM_ANI_KEY			= 1 << 22,
    SCENEENTITY_SFX_BOX_PROJ        = 1 << 23,
    SCENEENTITY_SFX_GEOMETRY        = 1 << 24,
    SCENEENTITY_ANTI_PORTAL         = 1 << 25,
    SCENEENTITY_LAUNCHER            = 1 << 26,

    SCENEENTITY_ALL                 = 0xffffffff
};

/*
enum {
    REPRESENT_TYPE_NORMAL,//用REPRESENTOBJECT_DEFAULT
    REPRESENT_TYPE_NPC,//用REPRESENTOBJECT_NPC
    REPRESENT_TYPE_PVS,//用REPRESENTOBJECT_PVS

    REPRESENT_TYPE_COUNT	
};*/

typedef enum _TEXTYPE
{
	TEXTYPE_COMMON = 0,
	TEXTYPE_CUBE   = 1,
	TEXTYPE_VOLUME = 2,
	TEXTYPE_RENDER_TARGET = 3,
	TEXTYPE_DEPTH = 4,
}TEXTYPE;

enum SFX_TRACK_TYPE
{
	SFX_TT_COMMON,
};

class KG3DModel;
struct BindExtraInfo
{
	KG3DModel* pModel;
	int nBindIndex;
	int nMatrixIndex;
};

enum enuAnimationJointType
{
	ANI_JOINT_TOP,
	ANI_JOINT_BOTTOM,
	ANI_JOINT_COUNT,
};

const static DWORD MAX_NUM_CAPTION = 4;

enum enuMeshRenderExtInfoType
{
	ENUM_MESHRENDER_EXTR_INFO_MATRIX,
	ENUM_MESHRENDER_EXTR_INFO_MESH,
	ENUM_MESHRENDER_EXTR_INFO_FORCE_DWORD = 0xffffffff,
};

enum
{
	EM_EVENT_STATE_BEGIN = 0,	//在选择开始之前
	EM_EVENT_STATE_END = 1,		//选择结束
	EM_EVENT_STATE_FRAMEMOVE,
};

typedef enum _KG3DCOORD{
	KG3DCOORD_SYSTEM_MIN = 0,
	KG3DCOORD_LOCAL = 0,
	KG3DCOORD_WORLD = 1,
	KG3DCOORD_SYSTEM_MAX = KG3DCOORD_WORLD,

	KG3DCOORD_FIRST_AXIS = 2,
	KG3DCOORD_X = KG3DCOORD_FIRST_AXIS,
	KG3DCOORD_Y = 3,
	KG3DCOORD_Z = 4,
	KG3DCOORD_W = 5,
	KG3DCOORD_AXIS_COUNT = 3,
	KG3DCOORD_AXIS_COUNT_4D = 4,
	KG3DCOORD_INVALID_AXIS = KG3DCOORD_FIRST_AXIS + KG3DCOORD_AXIS_COUNT_4D,

	KG3DCOORD_FIRST_PLANE = KG3DCOORD_INVALID_AXIS,	//下面三个面的Normal分别对应X，Y，Z
	KG3DCOORD_YZ = KG3DCOORD_FIRST_PLANE,
	KG3DCOORD_XZ = KG3DCOORD_FIRST_PLANE + 1,
	KG3DCOORD_XY = KG3DCOORD_FIRST_PLANE + 2,
	KG3DCOORD_PLANE_COUNT = 3,
	KG3DCOORD_INVALID_PLANE = KG3DCOORD_FIRST_PLANE + KG3DCOORD_PLANE_COUNT,

	KG3DCOORD_INTEGRATION = KG3DCOORD_INVALID_PLANE,

	KG3DCOORD_INVALID = KG3DCOORD_INTEGRATION + 1,
	
}KG3DCOORD;

enum
{
	EM_VISITOR_STOP = (HRESULT)E_FAIL,		//结束遍历
	EM_VISITOR_CONTINUE = (HRESULT)S_OK,		//继续遍历
	EM_VISITOR_BREAK = (HRESULT)S_FALSE,		//break
};

#define INVALID_GROUNDTYPE 0xffffffff



struct MeshRenderExtraInfo
{
	enuMeshRenderExtInfoType dwType;
	void* Data;
	void* Data1;
};

enum ENUM_CAMERA_STATE
{
	CAMERA_FLEX_MOVING  = 0x1,    // 弹簧运动
	CAMERA_LINE_MOVING  = 0x2,    // 线性运动
	CAMERA_OBSTRUCTDED  = 0x4,    // 出现遮挡
	CAMERA_IMMOBILEING  = 0x8,    // 稳定状态
};

struct TrackCameraInfo
{
	float   fFlexCoefficient;     // 弹性系数  
	float   fDampCoefficient;     // 阻尼系数
	//float   fFlexRate;            // 拉伸速率(鼠标轮)

	int     nUseObstructdAvert;   // 是否应用遮档避免
	int     nUseFlexibilitySys;   // 是否应用弹簧系统

	BOOL	bEnableTrack;

	TrackCameraInfo()
	{
		fFlexCoefficient   = 0.800000f;
		fDampCoefficient   = 0.700000f;
		//fFlexRate          = 80.00000f;

		nUseObstructdAvert = TRUE;
		nUseFlexibilitySys = TRUE;

		bEnableTrack = TRUE;
	}
};

#define MAX_SUBSET_COUNT 32

enum {
    LOOK_OUT_TO_IN,
    LOOK_IN_TO_OUT
};
 
/* the effects apply order is depend on its define order */
enum PostRenderEffectType
{
    //POST_EFFECT_HDR         = 1 << 3,
	POST_EFFECT_FXAA         = 1 << 3,
	POST_EFFECT_AOE          = 1 << 4,
    POST_EFFECT_SSAO         = 1 << 5,
    POST_EFFECT_MOTIONBLUE   = 1 << 6,
    POST_EFFECT_DETAIL       = 1 << 7,
    POST_EFFECT_SOCKWARE     = 1 << 8,
    POST_EFFECT_NEWSHOCKWAVE = 1 << 9,
    POST_EFFECT_GODRAY       = 1 << 10,
    POST_EFFECT_HSI          = 1 << 11,
    POST_EFFECT_CURVE_CMYK   = 1 << 12,
    POST_EFFECT_BLOOM        = 1 << 13,
    POST_EFFECT_SHADOW       = 1 << 14,
    POST_EFFECT_FOG          = 1 << 15,
	POST_EFFECT_DOF          = 1 << 16,
	POST_EFFECT_COLORGRADE   = 1 << 17,
	POST_EFFECT_TRACKBLUR    = 1 << 18,
	POST_EFFECT_CLOUD		 = 1 << 19,
	POST_EFFECT_HDR          = 1 << 29,
	POST_EFFECT_TRANSITIONS  = 1 <<30, //can't be 31,will cause black screen!

	POST_EFFECT_MAX_COUNT	 = 32,

	POST_EFFECT_LAST = 1 << (POST_EFFECT_MAX_COUNT-1)
	
};


//enum PostRenderEffectType
//{
//	SCREEN_HDR    = 0x001,
//	POST_EFFECT_BLOOM  = 0x002,
//	POST_EFFECT_SOCKWARE   = 0x004,
//	POST_EFFECT_HSI    = 0x008,
//	POST_EFFECT_MOTIONBLUE   = 0x010,
//	POST_EFFECT_DETAIL = 0X020,
//    POST_EFFECT_GODRAY = 0x40,
//
//	PRET_HDR      = SCREEN_HDR,
//	PRET_BLOOM    = POST_EFFECT_BLOOM,
//	PRET_SHOCK_WAVE = POST_EFFECT_SOCKWARE
//};

const int MAX_BONE_NAME_LENGTH = 30;
const int MAX_NUM_CHILD_BONE = 30;

//////////////////////////////////////////////////////////////////////////
/************************************************************************/
/*所有的DWORD类型开始。所有的引擎中的类用一个DWORD唯一标识之后，就可以
很方便的得到对应的实际的类了。
*/
/************************************************************************/

typedef enum _KG3D_CLASS_TYPE
{
	KG3DTYPE_NONE_ABSTRUCT = 1,
	KG3DTYPE_NONE = 2,

	KG3DTYPE_INT = 10,
	KG3DTYPE_UINT = 11,
	KG3DTYPE_DWORD = 12,
	
	KG3DTYPE_FLOAT = 15,
	KG3DTYPE_DOUBLE = 16,

    KG3DTYPE_STDSTRING = 18,
    KG3DTYPE_VECTORINT = 19,
    KG3DTYPE_D3DCOLOR = 20,
    KG3DTYPE_D3DXVECTOR3 = 21,
    

	KG3DTYPE_PATH = 29,

	KG3DTYPE_I_INTERFACE = 30,
	KG3DTYPE_IE_INTERFACE = 31,

	KG3DTYPE_COMMON_OBJECT = 50,
	KG3DTYPE_COMMON_OBJECT_SIMPLE = 51,
	KG3DTYPE_COMMON_OBJECT_NODE = 52,
	KG3DTYPE_COMMON_OBJECT_CONTAINER = 53,
	KG3DTYPE_COMMON_OBJECT_POOL = 54,
	KG3DTYPE_COMMON_OBJ_CONTAINER_NODE = 55,

	KG3DTYPE_COLLOCATOR = 100,
	KG3DTYPE_STATE_MACHINE = 101,
	KG3DTYPE_STATE_MACHINE_STATE = 102,
	KG3DTYPE_SCENE = 110,
	KG3DTYPE_SCENE_SCENE_EDITOR = 120,
	

	KG3DTYPE_SCENE_SETTINGS = 150,
	KG3DTYPE_TIME_CLOCK = 160,

	KG3DTYPE_COORD_TRANSLATION = 200,
	KG3DTYPE_COORD_ROTATION = 201,
	KG3DTYPE_COORD_SCALING = 202,

	KG3DTYPE_ENVIRONMENT = 1015,
	KG3DTYPE_ENV_EFFECT = 1016,
	KG3DTYPE_WINDOWS_MESSGE_BROAD_CASTER = 2040,
	KG3DTYPE_ENVEFF_POINTLIGHT_TABLE = 2050,

	KG3DTYPE_SCENE_REGION = 2060,
	KG3DTYPE_SCENE_SECTION = 2061,
	KG3DTYPE_SCENE_ZONE = 2062,

	//2000-2149保留给EnvEff系列
	KG3DTYPE_MODEL_SHADOW_RENDERER = 2150,

	KG3DTYPE_DEFAULT_SHADER_GROUP = 2199,
	KG3DTYPE_REGION_INFO_MANAGER = 2200,
	KG3DTYPE_SCENE_SHADOW_TOOLS = 2221,
	KG3DTYPE_SCENE_OBJECT_PLACEMENT_TOOL = 2230,
	KG3DTYPE_SCENE_SELECTION_TOOL = 2232,

	KG3DTYPE_TRANSFORM_TOOL_BEGIN = 2233,
	KG3DTYPE_TRANSLATION_TOOL = KG3DTYPE_TRANSFORM_TOOL_BEGIN,
	KG3DTYPE_ROTATION_TOOL = 2234,
	KG3DTYPE_SCALING_TOOL = 2235,
	KG3DTYPE_TRANSFORM_TOOL_END = KG3DTYPE_SCALING_TOOL,

	KG3DTYPE_SCENE_TOP_SNAP_TOOL = 2236,
	KG3DTYPE_SNAP_TOOL	= 2237,
	KG3DTYPE_SCENE_CHECKERS = 2238,
    KG3DTYPE_SCENE_RUNNER_TOOL = 2239,
    KG3DTYPE_SCENE_ARCBALL_TOOL = 2240,

	KG3DTYPE_RAY_INTERSECTOR = 2300,
	KG3DTYPE_RAY_INTERSECTOR_CONTAINER = KG3DTYPE_RAY_INTERSECTOR + 1,	

    KG3DTYPE_HELPER_TESTER = 2500,
}KG3D_CLASS_TYPE;
typedef enum _KG3D_CLASS_CONTAINER_TYPE
{
	KG3DTYPE_RESOURCE_TABLE_TYPE = 3000,///这些要组合使用
}KG3D_CLASS_CONTAINER_TYPE;
//注意下面的不要重复
typedef enum _KG3DTYPE_CAM
{
	KG3DTYPE_CAM_MOVEMENT = 1005,
	KG3DTYPE_CAM_ANIMATION = 1006,
}KG3DTYPE_CAM;

typedef enum _KG3DENVEFF_TYPE	//和储存有关系，别胡乱改Type的值
{
	KG3DTYPE_ENVEFF_INVALID_EFFECT = 0,///如果任何一个Effect得到一个0的Type的话是无效的

	KG3DTYPE_ENVEFF_BEGIN = 2000,

	KG3DTYPE_ENVEFF_DUMMY = 2001,

	///<KG3DEnvEffect SubClass Register Point>
	KG3DTYPE_ENVEFF_SKYSYSTEM_SYSTEM = 2020,
	KG3DTYPE_ENVEFF_SKYSYSTEM_SKYBOX = 2021,
	KG3DTYPE_ENVEFF_SKYSYSTEM_FARMOUNTAIN = 2022,
	KG3DTYPE_ENVEFF_SKYSYSTEM_CLOUD = 2023,
	
	KG3DTYPE_ENVEFF_FOG = 2040,
	
	KG3DTYPE_ENVEFF_LENSFLARE = 2043,
	KG3DTYPE_ENVEFF_LENSFLARE_SUN = 2045,
	KG3DTYPE_ENVEFF_LENSFLARE_MOON = 2046,
	KG3DTYPE_ENVEFF_STARRY_NIGHT = 2047,
	
	KG3DTYPE_ENVEFF_LIGHTSET = 2050,
	KG3DTYPE_ENVEFF_LIGHT = 2051,
	KG3DTYPE_ENVEFF_POINTLIGHT = 2052,

	KG3DTYPE_ENVEFF_RAIN = 2080,
	KG3DTYPE_ENVEFF_SNOW = 2081,
	KG3DTYPE_ENVEFF_WIND = 2082,

	KG3DTYPE_ENVEFF_DYNAMIC_WEATHER = 2100,///要保证这个是最大的Effect,以保证他是在最后渲染和FrameMove的

	KG3DTYPE_ENVEFF_END = 2101,

	KG3DTYPE_ENVEFF_KEY_TABLE = 2102,
	KG3DTYPE_ENVEFF_DYNAMIC_WEATHER_KEY_TRACK = 2103,

}KG3DENVEFF_TYPE;

enum enuRegionInfoManagerType
{
	TYPE_RIM_DEFAULT = 0,
	TYPE_RIM_DW = 1,
};
enum enuAnimationMotionTagType
{
	MTT_START,//出招开始, 起手结束
	MTT_END,//攻击完成, 收招开始
	MTT_USERDEFINE,//用户定义, 具体信息在TagSFXCallBackExtraInfo
	MTT_COUNT,
	MTT_FORCE_DWORD = 0xfffffff,
};

#define TAG_NAME_MAX_LENGTH 256

enum enuTagType
{
	TAGTYPE_SFX,
	TAGTYPE_SOUND,
	TAGTYPE_MOTION,
	TAGTYPE_COUNT
};

enum enuMotionTagBlockType
{
	MTBT_DAMAGEPERCENTAGE,//伤害百分比
	MTBT_METEOR,//刀光开关
	MTBT_FACEMOTION,//表情动画
	MTBT_MISSILE,//子弹
	MTBT_EQUIPSFX,//装备特效
	MTBT_GROUNDEFFECT,//地表效果
    MTBT_INVISIBLE,//改变模型的alpha值
    MTBT_TRANSITION,//模型从隐形到出现的过渡
    MTBT_WEAPONMOTION,//武器动画
	MTBT_COUNT,
	MTBT_START = 0xfffffffd,
	MTBT_END = 0xfffffffe,
	MTBT_INVALIDATE =  0xffffffff,
	MTBT_FORCE_DWORD = 0xffffffff,
};

enum enuModelType
{
	MT_SCENERESPONSE,
	MT_REPRESENTLOGIC,
	MT_COUNT
};

struct TagMotionCallBackExtraInfo
{
	enuMotionTagBlockType Type;
	float fData[8];
	DWORD dwData[8];
	TCHAR strData[8][MAX_PATH];
	TagMotionCallBackExtraInfo()
	{
		memset(this, 0, sizeof(TagMotionCallBackExtraInfo));
	}
};

struct TagMotionCBExtraInfoDamagePercentage
{
	enuMotionTagBlockType Type;
	float fDamagePercentage;
	float fReserved[7];
	DWORD dwReserved2[8];
	TCHAR strResvered3[8][MAX_PATH];
};

struct TagMoitonCBExtraInfoMissile
{
	enuMotionTagBlockType Type;
	float fDamagePercentage;
	float fReserved[7];
	DWORD dwMissileID;
	DWORD dwReserved2[7];
	TCHAR strResvered3[8][MAX_PATH];
};

struct TagMoitonCBExtraInfoEquipSFX
{
	enuMotionTagBlockType Type;
	float fReserved[8];
	DWORD dwEquipType;
	DWORD dwEquipRepesentID;
	DWORD dwSfxID;
	DWORD dwReserved2[5];
	TCHAR strResvered3[8][MAX_PATH];
};

enum MotionTagRunState
{
	MTRS_NONE,
	MTRS_ACTIVE,
	MRTS_FORCE_DWORD = 0xfffffff,
};

class KG3DAnimationMotionTag;
struct MotionTagDataInfo
{
	friend class KG3DAnimationMotionTag;
	MotionTagDataInfo()
	{
		strTagName[0] = '\0';
		Type = MTT_USERDEFINE;
	}
	TCHAR strTagName[TAG_NAME_MAX_LENGTH];
	TagMotionCallBackExtraInfo ExtraInfo;
	enuAnimationMotionTagType Type;
};

struct MotionTagKeyFrame
{
	MotionTagDataInfo MotionKeyFrameData;
	MotionTagRunState RunState;
	MotionTagKeyFrame()
	{
		RunState = MTRS_NONE;
	}
};

enum enuRuntimeShaderFlag
{
	ENU_SHADER_TECHTYPE_BLENDTEX = 1 ,
	ENU_SHADER_TECHTYPE_GLOW = (1 << 1),
	ENU_SHADER_TECHTYPE_FLOW = (1<< 2),
	ENU_SHADER_TECHTYPE_FLASH = (1<< 3),
	ENU_SHADER_TECHTYPE_OUTLINE = (1<<4),
	ENU_SHADER_TECHTYPE_COUNT = 5,
	ENU_SHADER_TECHTYPE_FORCE_DWORD = 0xffffffff,
};

struct KG3DModel_BlendToColor
{
	DWORD dwBlendStartTime; 
	float m_fBlendSpan;
    float m_fMaxBlendFactor;
	D3DCOLORVALUE m_crSrcColor;
	D3DCOLORVALUE m_cDestColor;
};

//SFX Tag Data
enum SFXFinishState
{
	SFX_FS_LOOP,//循环播放
	SFX_FS_KEEP,//保持最后状态
	SFX_FS_DELETE,//删除
	SFX_FS_LOOPKEEP,// 循环播放，同个动作不中断
};


enum SFXMotionFinshState
{
	SFX_MFS_DELETE,//删除
	SFX_MFS_KEEP,//继续保持
};

enum SFXCallBackExtraType
{
	SCBET_NONE,//没有附加信息
	SCBET_HITINFO,//被击信息
	SCBET_COUNT,
	SCBET_FORCE_DWORD = 0xffffffff,
};

struct TagSFXCallBackExtraInfo
{
	SFXCallBackExtraType Type;
	float fData[8];
	DWORD dwData[8];
};

struct SFXKeyFrameInfo
{
	TCHAR strTagName[TAG_NAME_MAX_LENGTH];
	UINT uID;//在该帧上的ID
	UINT uBindFileIndex;//在bind文件中的索引
	SFXFinishState FinishState;//特效播放完成之后的状态
	float fSpeed;//播放速度
	BOOL bAdaptSpeedToMotion;//是否要根据动作播放的速度来修改实际播放的速度
	BOOL bInterruptable;//特效是否会被下一个特效取消
	SFXMotionFinshState MotionFinishEvent;//动作完成时的处理
	BOOL bNotify;//是否通知表现逻辑
	TagSFXCallBackExtraInfo CallBackExtraInfo;//Notify时候回调的信息
	SFXKeyFrameInfo()
	{
		strTagName[0] = '\0';
		uID = TAG_INVALIDATE_VALUE; 
		uBindFileIndex = TAG_INVALIDATE_VALUE;
		FinishState = SFX_FS_KEEP;
		fSpeed = 1.0f;
		bAdaptSpeedToMotion = FALSE;
		bInterruptable = TRUE;
		MotionFinishEvent = SFX_MFS_DELETE;
		bNotify = FALSE;
	}
	const static DWORD TAG_INVALIDATE_VALUE = 0xffffffff;
};

struct SFXKeyFrameInfoVersion1 : public SFXKeyFrameInfo
{
	BOOL bSetWorldPosition;//留在释放时刻的世界坐标
	DWORD dwRepeatWorldPositionSFX; //如果是世界坐标特效，该标志为true的，则是可以重复触发的
	DWORD dwReserved[31];
	
	// 32 = 1 +31 
	//DWORD dwReserved[32];

	SFXKeyFrameInfoVersion1()
	{
		bSetWorldPosition = FALSE;
		dwRepeatWorldPositionSFX = FALSE;
	}
	const SFXKeyFrameInfoVersion1 &operator =(const SFXKeyFrameInfo &V0)
	{
		memcpy(this, &V0, sizeof(SFXKeyFrameInfo));
		bSetWorldPosition = FALSE;
		return *this;
	}
};

typedef struct _KG3DTEXTURE_DESC 
{
	D3DFORMAT	Format;
	D3DPOOL		Pool;
	UINT		MipLevels;	
	DWORD		Usage;
	UINT        Width;
	UINT        Height;

	UINT	SizeIsFractionOfBackBufferSize;//指定倍数是后缓冲倍数，若是，则大小从BackBuffer计算得到
	_KG3DTEXTURE_DESC()
	{
		ZeroMemory(this, sizeof(*this));
		Format = D3DFMT_FORCE_DWORD;
		_ASSERTE(Pool == D3DPOOL_DEFAULT);
	}
}KG3DTEXTURE_DESC;

//Sound Tag Data
enum enuSoundPlayType
{
	SPT_LOOP,
	SPT_ONCE, 
	SPT_FORCE_DWORD = 0xffffffff,
};

enum enuSoundMotionChangeState
{
	SMCS_KEEP,//动作切换时候保持播放,但是播放方式切换为单次
	SMCS_DELETE,//动作切换时直接停止播放
	
	SMCS_LOOP_RESTART = (1 << 16), // 动作循环时重新播放
};


enum enuSoundPlayInterrupt
{
	SPI_ENABLE,
	SPI_DISABLE,
};

struct SafeFileName
{
	TCHAR strFileName[MAX_PATH];
	TCHAR strErrorHandleFileName[MAX_PATH];
	SafeFileName()
	{
		memset(strFileName, 0, sizeof(TCHAR) * MAX_PATH);
		memset(strErrorHandleFileName, 0, sizeof(TCHAR) * MAX_PATH);
	}
};

struct SoundDataInfo
{
	TCHAR strTagName[TAG_NAME_MAX_LENGTH];
	SafeFileName strSoundFileName;
	BOOL bLoop;
	enuSoundMotionChangeState MotionChangeState;
	enuSoundPlayInterrupt InterruptMode;
};

#define SOUND_TAG_MAX_CANDIDATES 5

struct SoundTagSoundFileCandidate
{
	SafeFileName strSoundFileName;
	float fVolume;
	float fHitRate;
	SoundTagSoundFileCandidate()
	{
		fVolume = 100.0f;
		fHitRate = 100.0f;
	}
};

struct SoundTagSoundFileCandidate1
{
	SafeFileName strSoundFileName;
	float fVolume;
	float fHitRate;
	float fMinDistance;
	float fMaxDistance;
	DWORD dwReserve[32];
	SoundTagSoundFileCandidate1()
	{
		fVolume = 100.0f;
		fHitRate = 100.0f;
		fMinDistance = 1000.0f;
		fMaxDistance = 2500.0f;
	}
};

struct SoundDataInfoVersion1
{
	TCHAR strTagName[TAG_NAME_MAX_LENGTH];
	SoundTagSoundFileCandidate SoundCandidates[SOUND_TAG_MAX_CANDIDATES];
	DWORD dwValidateCandidate;
	BOOL bLoop;
	enuSoundMotionChangeState MotionChangeState;
	enuSoundPlayInterrupt InterruptMode;
	SoundDataInfoVersion1()
	{
		memset(strTagName, 0,sizeof(TCHAR) * TAG_NAME_MAX_LENGTH);
		dwValidateCandidate = 0;
		bLoop = FALSE;
		MotionChangeState = SMCS_KEEP;
		InterruptMode = SPI_ENABLE;
	}
};

struct SoundDataInfoVersion2
{
	TCHAR strTagName[TAG_NAME_MAX_LENGTH];
	SoundTagSoundFileCandidate1 SoundCandidates[SOUND_TAG_MAX_CANDIDATES];
	DWORD dwValidateCandidate;
	BOOL bLoop;
	enuSoundMotionChangeState MotionChangeState;
	enuSoundPlayInterrupt InterruptMode;
	SoundDataInfoVersion2()
	{
		memset(strTagName, 0,sizeof(TCHAR) * TAG_NAME_MAX_LENGTH);
		dwValidateCandidate = 0;
		bLoop = FALSE;
		MotionChangeState = SMCS_KEEP;
		InterruptMode = SPI_ENABLE;
	}
	inline void operator = (const SoundDataInfoVersion2 & src)
	{
		memcpy(this,&src,sizeof(SoundDataInfoVersion2));
	}
};

enum SoundType
{
	SST_NONE = -1,
	SST_COMMON,
	SST_BODY  = SST_COMMON,
    SST_WEAPON,
	SST_COUNT,
};
struct AnimationSoundTagInfo 
{
	SoundType soundType;
    BOOL bLoop;
    enuSoundMotionChangeState MotionChangeState;
    enuSoundPlayInterrupt InterruptMode;
	float fRate;
    BOOL bFlag;
    float fVolume;
    DWORD dwReserved[8];
	AnimationSoundTagInfo()
	{
		soundType = SST_NONE;
        bLoop = FALSE;
        MotionChangeState = SMCS_KEEP;
        InterruptMode = SPI_ENABLE;
		fRate = 0.0;
        fVolume = 0.0;
        bFlag = FALSE;
        memset(dwReserved,0,sizeof(dwReserved));
	}
    inline void operator = (const AnimationSoundTagInfo & src)
    {
        memcpy_s(this,sizeof(AnimationSoundTagInfo),&src,sizeof(AnimationSoundTagInfo));
    }
};


struct SoundDataInfoVersion3 
{        
    AnimationSoundTagInfo TagInfo[SST_COUNT];
    SoundDataInfoVersion3()
    {
        for(int i = 0 ; i < SST_COUNT ; i ++)
        {
            TagInfo[i].soundType = static_cast<SoundType>(i);
        }
    }
    inline void operator = (const SoundDataInfoVersion3 & src)
    {
        memcpy_s(this,sizeof(SoundDataInfoVersion3),&src,sizeof(SoundDataInfoVersion3));
    }
};

struct SoundDataInfoUnion//方便数据的修改 
{
    SoundDataInfoVersion2 Data2;
    SoundDataInfoVersion3 Data3;
	int nCurrentVersion;
	SoundDataInfoUnion()
	{
		nCurrentVersion = 2;
	}
    inline void operator = (const SoundDataInfoUnion & src)
    {
        Data2 = src.Data2;
        Data3 = src.Data3;
		nCurrentVersion = src.nCurrentVersion;
    }
};

#define EVENT_TAG_NAME "FMOD"

enum FindFrameType
{
	FFT_LESSEQUAL,
	FFT_GREATEREQUAL,
	FFT_EQUAL,
	FFT_LESS,
	FFT_GREATER,
	FFT_COUNT,
};


enum enuModelPlayAnimationType
{
	MPAT_NORMAL,
	MPAT_TAGGED,
	MPAT_COUNT,
	MPAT_INVALIDATE,
	MPAT_FORCE_DWORD = 0xffffff,
};

enum enuAniTagDisableType
{
	ATDT_SOUND = 1,
	ATDT_MOTION = 1 <<1,
	ATDT_SFX = 1 << 2,
	ATDT_NONE = 0,
	ATDT_ALL = (ATDT_SOUND | ATDT_MOTION |ATDT_SFX),
};
enum enuJointTopInfo0
{
	JOINT_TOPINFO_COMPOSERINDEX = 0,//上半身动作对应0号Composer
	JOINT_TOPINFO_ANI_TOP_INDEX = 1,//上半身动作在0号Composer中是第1号动作
	JOINT_TOPINFO_ANI_BOTTOM_INDEX = 0,//下半身动作在0号Composer中是0号动作
};

enum enuJointBottomInfo0
{
	JOINT_BOTTOMINFO_COMPOSERINDEX = 1,//下半身动作对应1号Composer
	JOINT_BOTTOMINFO_ANI_BOTTOM_INDEX = 0,//下半身动作在1号Composer中是第0号动作
};


struct KG3DPhysiscParam {
    struct LIMIT
    {
        float fValue;
        float fRestitution;
        float fHardness;
    };
    struct SPRING 
    {
        float fSpring;
        float fDamper;
    };
    struct SPHERICAL_JOINT
    {
        BOOL  bEnableTwistLimit;
        LIMIT TwistLimitLow;
        LIMIT TwistLimitHigh;

        BOOL  bEnableSwingLimit;
        LIMIT SwingLimit;

        BOOL   bEnableTwistSpring;
        SPRING TwistSpring;

        BOOL   bEnableSwingSpring;
        SPRING SwingSpring;

        BOOL   bEnableJointSpring;
        SPRING JointSpring;
    };

	float fRadius;
	float fDensity;
    int   nSolverIterationCount;
	float fLinearDamping;
	float fAngularDamping;
    SPHERICAL_JOINT SphericalJoint;
};

enum enuPlaySoundType
{
	BG_MUSIC = 0,    // 背景音乐
	UI_SOUND,        // 界面音效
	UI_ERROR_SOUND,  // 错误提示音
	SCENE_SOUND,     // 环境音效
	CHARACTER_SOUND, // 角色音效,包括打击，特效的音效
	CHARACTER_SPEAK, // 角色对话
	FRESHER_TIP,     // 新手提示音
	SYSTEM_TIP,      // 系统提示音
	TREATYANI_SOUND, // 协议动画声音

	// 注意：新增Type请加在本行之前且不要指定具体取值！
	_PLAYSOUNDTYPE_MAX_
};

#define SOUND_FMOD_DSP_MAX          8                                              //限制DSP最大个数为8
#define BG_MUSIC_PRIORITY			255
#define CHARACTER_SPEAK_PRIORITY	168

#define SCENE_LOADOPTION_PRELOAD  1
#define SCENE_DISABLE_DYNAMICLOAD 2
#define SCENE_FIX_CAMRERANGLE     4
#define SCENE_MINISCENE			  8

struct OBJECT_PDROP_INFO 
{
	unsigned nID;                                   // The Drop Object ID 
	unsigned nNumber;                               // The Drop Object Number

	OBJECT_PDROP_INFO()
	{
		nID     = 0;
		nNumber = 0; 
	}
};

// Object Type
enum
{
	REPRESENTOBJECT_DEFAULT				= 0, //默认值，一般是MESH类型 
	REPRESENTOBJECT_NPC					= 1, //编辑器用的NPC显示            
	REPRESENTOBJECT_PROP				= 2, //未使用             
	REPRESENTOBJECT_MAGIC				= 3,//未使用
	REPRESENTOBJECT_EFFECT				= 4,//未使用
	REPRESENTOBJECT_SKILL				= 5,//未使用
	REPRESENTOBJECT_SET					= 6, //模型包    
	REPRESENTOBJECT_VISIBLESET			= 7, //可视集合
	REPRESENTOBJECT_DOODAD				= 8, //编辑器用的DOODAD显示
	REPRESENTOBJECT_WAYPOINT			= 9, //路径点
	REPRESENTOBJECT_REFRESHPOINT		= 10, //刷新点
	REPRESENTOBJECT_POLY				= 11, //多边形区域
	REPRESENTOBJECT_SOUNDBALL			= 12, //音效球
	REPRESENTOBJECT_PVS					= 13, //带视口的可视集合
	REPRESENTOBJECT_ANTIPORTAL			= 14, //阻挡片
	REPRESENTOBJECT_NODE				= 15, //道路河流编辑所使用的节点
	REPRESENTOBJECT_BLOCK				= 16, //复制地形块
	REPRESENTOBJECT_DATAFLOWDATA		= 17,
	REPRESENTOBJECT_DATAFLOWPROCESSOR	= 18,
	REPRESENTOBJECT_DATAFLOWARC			= 19,
	REPRESENTOBJECT_POINTLIGHT			= 20,//点光源
	REPRESENTOBJECT_TEST				= 21,//预留的测试用ＯＢＪ
	REPRESENTOBJECT_TRAFFICPOINT		= 22,//交通点
	REPRESENTOBJECT_WALL                = 23,//围墙，栏杆工具
	REPRESENTOBJECT_DUMMY				= 24,//用于Observer模式的通用模型
	REPRESENTOBJECT_OBSTACLE            = 25,//用于生成逻辑的透明障碍
	REPRESENTOBJECT_RULERNODE           = 26,//场景的测距标尺节点
	REPRESENTOBJECT_RULER               = 27,//场景的测距标尺对象
	REPRESENTOBJECT_BEZIER_HANDLE       = 28,//贝塞尔曲线的把手节点
	REPRESENTOBJECT_BEZIER_NODE			= 29,//贝塞尔曲线的节点
	REPRESENTOBJECT_BEZIER_PATH			= 30,//整条贝塞尔曲线
	REPRESENTOBJECT_3DENTITY            = 31,//破碎动画物件
	REPRESENTOBJECT_VOLUME              = 32,//
	REPRESENTOBJECT_ENVIRONMENTVOLUME   = 33,
	REPRESENTOBJECT_SIGNPOINT           = 34,//通用的标记点，如KEYPOINT,TRAFFICPOINT,WAYPOINT等等
	REPRESENTOBJECT_SOUNDPOLYGON        = 35,//多边形音效
	REPRESENTOBJECT_SOUNDREVERB         = 36,//音效混响区域
	REPRESENTOBJECT_TYPE_COUNT,			//添加新的ObjType的时候，请比这个值小，如果值不够用了，可以增大这个值(理论上这个值是由编译器自动递增的)，但不要太大，因为需要空间的，反正要所有的ObjType都比这个值小，这样Table中就可以利用Begin End做线性查找了
	REPRESENTOBJECT_NONE = 0x0FFFFFFF,
	REPRESENTOBJECT_FORCEDWORD = 0xFFFFFFFF,
};

// 高16位作为扩展
#define EXT_REPRESENTOBJECT_DEFAULT     (REPRESENTOBJECT_DEFAULT << 16) + 0x0000FFFF
#define EXT_REPRESENTOBJECT_DEFAULT2    (REPRESENTOBJECT_DEFAULT << 24) + 0x00FFFFFF
#define EXT_REPRESENTOBJECT_SET2        (REPRESENTOBJECT_SET << 24)    + 0x00FFFFFF

#define MAX_TEXT 128                               
#define MAX_DROP 32     
// PS : 为了跟策划文档一致,所以使用中文注解

// 物件属性 : 显示相关 
struct OBJECT_PROPERTY_DISPLAY
{
	char    szModelFile[MAX_PATH];                   // 模型文件
	char    szReplaceableTextureFile[MAX_PATH];      // 纹理文件
	char    szSpecial[MAX_PATH];                     // 特效绑定
	char    szMinimapText[MAX_TEXT];                 // 小地图显示文字    
	DWORD   dwTintingColor;                          // 整体偏色

	DWORD   dwChangeColor;                           // 区域染色
	DWORD   dwShadowColor;                           // 阴影颜色

	DWORD   dwMinimapShowColor;                      // 小地图显示文字颜色
	int     dwDecayTime;                             // 死亡后消失时间

	float   fElevationRadius;                        // 与地表拼接高度
	int     nInteractionSpecial;                     // 互动特效

	int     nOrder;                                  // 显示层次
	int     nVisabilityLevel;                        // 可见优先级

	bool    bHighLight;                              // 是否受高光影响
	bool    bAmbientLight;                           // 是否受环境光影响
	bool    bShadow;                                 // 有否阴影
	bool    bMinimapShow;                            // 是否在小地图显示图像
	bool    bMinimapShowText;                        // 是否在小地图显示文字
	bool    bReplaceableTexture;                     // 是否能换纹理
	bool    bTranslucence;                           // 是否会被半透明
	bool    bHighLightScene;                         // 是否参与场景高光运算

	OBJECT_PROPERTY_DISPLAY()
	{
		memset(szModelFile, 0, sizeof(szModelFile));
		memset(szReplaceableTextureFile, 0, sizeof(szReplaceableTextureFile));
		memset(szSpecial, 0, sizeof(szSpecial));
		memset(szMinimapText, 0, sizeof(szMinimapText));

		dwTintingColor      = 0xFFFFFFFF;
		dwShadowColor       = 0x00000000;
		dwMinimapShowColor  = 0xFFFF0000;

		dwDecayTime         = 1000;
		fElevationRadius    = 1.0f;

		nInteractionSpecial = 0;
		nOrder              = 0;
		nVisabilityLevel    = 0;

		bHighLight          = false;
		bAmbientLight       = true;
		bShadow             = false;
		bReplaceableTexture = false;
		bTranslucence       = false;
		bHighLightScene     = false;
		bMinimapShow        = true;
		bMinimapShowText    = true;
	}
};

// 物件属性 : 声音相关
struct OBJECT_PROPERTY_SOUND
{
	char    szRevive[MAX_PATH];                      // 物件重生音效
	char    szDeath[MAX_PATH];                       // 物件死亡音效
	char    szMove[MAX_PATH];                        // 物价移动音效
	char    szLooping[MAX_PATH];                     // 物件随机音效
	int     dwLoopingTime;                           // 随机音效间隔

	int     dwFadeOutRate;                           // 音效淡出率
	int     dwFadeInRate;                            // 音效淡入率

	int     dwAffectArea;                            // 音效影响范围
	int     dwReserved;                              // 保留值

	OBJECT_PROPERTY_SOUND()
	{
		memset(szRevive, 0, sizeof(szRevive));
		memset(szDeath, 0, sizeof(szDeath));
		memset(szMove, 0, sizeof(szMove));
		memset(szLooping, 0, sizeof(szLooping));

		dwLoopingTime       = 1000;                          
		dwFadeOutRate       = 10;                          
		dwFadeInRate        = 10;                          
		dwAffectArea        = 100;                          
	}
};

// 物件属性 : 状态相关
struct OBJECT_PROPERTY_STATES
{
	float   fLife;                                   // 生命值
	float   fLifeReplenish;                          // 生命回复速度

	float   fInsaideDefence;                         // 内功防御
	float   fOutsaideDefence;                        // 外功防御

	bool    bAttackable;                             // 可否被攻击
	bool    bSelectable;                             // 可否被角色点选
	bool    bUnitWalkable;                           // 角色可否能通过
	bool    bUnitCanPass;                            // 角色可否能跳过
	bool    bBulletWalkable;                         // 子弹可否能通过
	bool    bBulletCanPass;                          // 子弹可否能跳过
	bool    bAutoPathing;                            // 自动生成障碍
	bool    bDropOnDeath;                            // 死亡是否掉东西

	int     nPathingType;                            // 障碍类型
	float   fPathingHeight;                          // 障碍高度

	int     nDeathType;                              // 死亡类型
	float   fReviveDelay;                            // 物件再生时间间隔

	float   fReviveTime;                             // 物件再生过程时间
	int     nDropNumber;                             // 物品掉落数量

	OBJECT_PDROP_INFO   DropTable[MAX_DROP];         // 物品掉落表

	OBJECT_PROPERTY_STATES()
	{
		fLife               = 0.0f;  
		fLifeReplenish      = 0.0f;                         

		fInsaideDefence     = 0.0f;                        
		fOutsaideDefence    = 0.0f;                       

		bAttackable         = false;                            
		bSelectable         = false;                            
		bUnitWalkable       = false;                          
		bUnitCanPass        = false;                          
		bBulletWalkable     = false;                       
		bBulletCanPass      = false;                        
		bAutoPathing        = false;                     
		bDropOnDeath        = false;                          

		nPathingType        = 0;                        
		fPathingHeight      = 0.0f;                    

		nDeathType          = 0;                        
		fReviveDelay        = 0.0f;                      

		fReviveTime         = 0.0f;                          
		nDropNumber         = 0;                           

		memset(DropTable, 0, sizeof(DropTable));   
	}
};

// 物件属性 : 动作相关
struct OBJECT_PROPERTY_ACTION
{
	char    szDeathFile1[MAX_PATH];                        // 文件路径
	DWORD   dwDeathTime1;                                  // 时间

	char    szDeathFile2[MAX_PATH];                        // 文件路径
	DWORD   dwDeathTime2;                                  // 时间

	char    szReserveFile1[MAX_PATH];                      // 文件路径
	DWORD   dwReserveTime1;                                // 时间

	char    szReserveFile2[MAX_PATH];                      // 文件路径
	DWORD   dwReserveTime2;                                // 时间

	char    szReserveFile3[MAX_PATH];                      // 文件路径
	DWORD   dwReserveTime3;                                // 时间

	char    szReserveFile4[MAX_PATH];                      // 文件路径
	DWORD   dwReserveTime4;                                // 时间

	char    szReserveFile5[MAX_PATH];                      // 文件路径
	DWORD   dwReserveTime5;                                // 时间

	char    szReserveFile6[MAX_PATH];                      // 文件路径
	DWORD   dwReserveTime6;                                // 时间

	OBJECT_PROPERTY_ACTION()
	{
		memset(szDeathFile1, 0, sizeof(szDeathFile1));
		memset(szDeathFile2, 0, sizeof(szDeathFile2));

		memset(szReserveFile1, 0, sizeof(szReserveFile1));
		memset(szReserveFile2, 0, sizeof(szReserveFile2));
		memset(szReserveFile3, 0, sizeof(szReserveFile3));
		memset(szReserveFile4, 0, sizeof(szReserveFile4));
		memset(szReserveFile5, 0, sizeof(szReserveFile5));
		memset(szReserveFile6, 0, sizeof(szReserveFile6));

		dwDeathTime1 = 0;
		dwDeathTime2 = 0;

		dwReserveTime1 = 0;
		dwReserveTime2 = 0;
		dwReserveTime3 = 0;
		dwReserveTime4 = 0;
		dwReserveTime5 = 0;
		dwReserveTime6 = 0;
	}
};

// 物件属性 : 技能相关
struct OBJECT_PROPERTY_ABILITIES
{
	int nAbilitiesID;                                      // 技能ID

	OBJECT_PROPERTY_ABILITIES()
	{
		nAbilitiesID    = 0;
	}
};

// 物件属性 : 标示相关
struct OBJECT_PROPERTY_TEXT
{
	char    szName[MAX_TEXT];                              // 名字
	char    szSuffix[MAX_TEXT];                            // 名字后缀
	char    szNote[MAX_TEXT];                              // 说明
	char    szFile[MAX_PATH];                              // 文件名
	int     nType;                                         // 类别
	int     nReserve;                                      // 保留值

	OBJECT_PROPERTY_TEXT()
	{
		memset(szName, 0, sizeof(szName));
		memset(szSuffix, 0, sizeof(szSuffix));
		memset(szNote, 0, sizeof(szNote));
		memset(szFile, 0, sizeof(szFile));

		nType    = 0;
		nReserve = 0;
	}
};

//---07.9.4---
//Engine Option
enum
{
	EM_LOD_HIGH_TO_MIDDLE = 0,
	EM_LOD_MIDDLE_TO_LOW = 1,
};

enum
{
	EM_MODEL_SHADOW_TYPE_NONE = 0,
	EM_MODEL_SHADOW_TYPE_LOW = 1,
	EM_MODEL_SHADOW_TYPE_MIDDLE = 2,
	EM_MODEL_SHADOW_TYPE_HIGH = 3,
	EM_MODEL_SHADOW_TYPE_SUPER_HIGH = 4,
	EM_MODEL_SHADOW_TYPE_COUNT,
};

struct KG3DDeviceSettings
{
    UINT uWidth;
    UINT uHeight;
	BOOL bMaximize;
    BOOL bFullScreen;
    BOOL bPanauision;
    BOOL bExclusiveMode;
    BOOL bTripleBuffering;
    BOOL bLockableBackBuffer;
    BOOL bVSync;
    UINT uRefreshRate;
    UINT uColorDepth;
    int nMultiSampleType;
    DWORD dwMultiSampleQuality;
};

struct KADAPTERMODE
{
    UINT uWidth;
    UINT uHeight;
    UINT uRefreshRates[32];
};

struct KG3DEngineOption
{	
	int nSampMipFilter;
	int nSampMinFilter;
	int nSampMagFilter;
	DWORD dwMaxAnisotropy;
    BOOL bCameraShake;
	BOOL bEnableAntiPortal;

	BOOL bOutputUsedResource;   //输出资源使用到文件并拷贝文件到一个目录
	BOOL bWaterReflection;		//是否水面反射
	BOOL bWaterRefraction;		//是否水面折射
    
	BOOL bWaterReflectEnvironment; //是否反射环境
	BOOL bWaterReflectGround;         
	BOOL bWaterReflectNPC;
	BOOL bWaterReflectEntity;     

	BOOL bRenderGrass;				//是否渲染草
	BOOL bGrassAnimation;			//是否对草播放动画
	BOOL bGrassAlphaBlend;
	BOOL bGrassActorAffect;			//是否启用新的草渲染，增加人物碰撞
	int  nTextureScale;			//材质精度
    int  nMeshScale;			//模型精度

	BOOL bTextureScaleCheck;

	float fCameraDistance;     //摄像机距离
	float fCameraAngle;        //摄像机视角

	BOOL bImportOldScene;

	BOOL bAmbientShaderOnly;	//是否只进行AmbientShader

	// 如果客户端要提供二次渲染的选项，请在config文件中将此设为1
	BOOL bPostEffectEnable;		//是否开启二次渲染

	//二次渲染的选项
	BOOL bBloomEnable;			//是否柔化
	BOOL bShockWaveEnable;		//是否ShockWave
	BOOL bHSIEnable;				//是否HSI着色
	BOOL bMotionBlur;
	BOOL bDetail;
    BOOL bGodRay;
    BOOL bSSAO;
	BOOL bGlobalFog;
    BOOL bCurveCMYK;
	BOOL bDOF;
    int nActiveCurveStype;

	BOOL bHDR;
	BOOL bColorGrade;
	BOOL bFXAA;
	int nFXAALevel;
	BOOL bTransition;

	INT nForceShaderModel;	//强制使用某个ShaderModel，这样同时引起DefaultShaderGroup管理的Shader的变化

	//模型阴影的选项
	ULONG ModelShadowType;		//类型，0表示关闭，1表示用脚底片片，2表示实时光影
	FLOAT ModelShadowParams[8];	//暂时定义8个参数，不管什么Shadow都自己管理这些参数究竟代表什么

	// Speed Tree
	BOOL bUseSpeedTreeLod;

    // BillBoard Cloud
    float fBillBoardCloudInureDistance;

	BOOL bEnableSpecialAlphaBlend;
	BOOL bDynamicLoadAnimation;

	//材质偏色默认值
	D3DCOLORVALUE ColorCast[8];

	BOOL bEnableRecord;

	BOOL bTrackCameraOrSimpleCamera;	//使用带弹簧和遮挡的摄像机还是普通摄像机

	FLOAT	fModelLODSwitchGates[2];		//LOD切换的距离
	FLOAT	fLODSwitchAngleGates[2];		//LOD切换的角度阈值
	int     nTerrainLODGates[3];      //LOD切换的距离 
	BOOL bUseTerrainLOD; //地形LOD
	BOOL bAreaShadow; //面积阴影效果

	BOOL bEnableDynamicConverMap;

	BOOL bCpuSkin;
	int  nNumCpuThread;
	BOOL bFlexBodySmooth;//平滑柔体
	BOOL bCpuProcessModelThreadLock;
	BOOL bEnablePhysics;
	BOOL bMultiTextureRender;//多张贴图批量绘制
	int  nTerrainDetail;
	int  nVegetationDensity;
	int  nWaterDetail;
    float fWaterAlphaMin;
    float fWaterReduHeight;
    int  nWaterRefrTextSize;
    int  nWaterReflTextSize;

	BOOL bUseRenderTarget_DepthTexture;
	BOOL bNeedStretchRect;

    BOOL bEnableBladesSmoot;
	BOOL bEnableDynamicUnload;

	BOOL bEnableDefaultDynamicWeather;
	BOOL bEnableNormalMap;
	BOOL bEnableGroundNormalMap;
	BOOL bEnableSpeedTreeNormalMap;
	BOOL bEnableTimeOptimizeLog;
	BOOL bEnableDebugBBox;

	float fMinSoundRange;

    BOOL bUseModelBsp;
	BOOL bEnableModelLod;

	BOOL bEnablePointLight;
    BOOL bEnableCuda;
	BOOL bUseLinearDepth;
	BOOL bUse2DCaption;//这个是当前使用的caption是2d还是3d的标志
	BOOL b2DCaptionSave;//这个是设置的caption是2d还是3d的标志， 下次启动之后生效

    BOOL bEnableScaleOutput; //是否使用缩放输出，即渲染使用1024然后拉伸输出到屏幕
    int  nScaleOutputSize;
    BOOL bScaleOutputSmooth;
    int  nMDLRenderLimit; // 同屏人数
    int  nClientSFXLimit; // 特效个数限制
	int nRenderTwiceLimit;//绘制两次alpha效果模型个数限制
	float fRenderTwiceCullLODLevel;//绘制两次alpha效果lod距离阈值

	BOOL bEnablePrecomputeMeteor;//是否开启预计算刀光
    BOOL bRenderTextureSFX;
	BOOL bNewMethod_TerrainLOD; //使用新的地形LOD算法
	BOOL bLoadBin;
	BOOL bLoadOptiVerAni;//优化的顶点动画

	BOOL bPackMeshVertex;//老外建议的顶点数据压缩

	BOOL bUsePrecomipledShader;
	
	DWORD dwEnvironmentSettingType;
	BOOL bForceReloadEnvironment;// 强制重新加载环境文件

    BOOL bEnableTextureLOD;

	BOOL bEnableModelCullMax;
	BOOL bEnableTerrainMedium;

    BOOL bEnableFaceDeform; //是否允许捏脸相关
    
    BOOL bEnableShaderStringOpt; // Shader 字符串Key优化
    BOOL bUseSimplePhysics;      // 在启用物理运算时，不使用physx，使用自实现的简单物理系统
	BOOL bEnableLoadOpt; // 资源加载的优化. 将渲染线程与加载线程完全解耦
	BOOL bUseIPPVideo;		// 是否允许屏蔽IPPVideo（可以节省内存占用）

    BOOL bEnableDrawFacesCount;
	BOOL bEnableMaxRangeOfVisibility;
	BOOL bEnableDynamicLoadByFrustum;
	float fAngleCullValue;
	BOOL bEnableOutputSceneInfomation;
	BOOL bBatchModelST;//是否批量绘制modelst

	BOOL bUseCullSystem;
	BOOL bUseShaderBinary;

	BOOL bPostCloud;
#ifdef __cplusplus
	KG3DEngineOption(){memset(this, 0, sizeof(KG3DEngineOption));}//加大保险系数，虽然在EngineManager中有ZeroMemory
	
	//bool IsShadowMapEnable()const{return ModelShadowType > EM_MODEL_SHADOW_TYPE_LOW;}//注意，因为暂时没有比实时影子高的影子，所以MIDDLE和HIGH都是实时影子，返回值是bool，可以自动升成BOOL，反过来是不行的。不要改，这样可以直接比较XX.IsShadowMapEnable() != YY.IsShadowMapEnable()。BOOL不行
	//VOID EnableShadowMap(BOOL bEnable)//等界面改完影子的选项之后要去掉
	//{
	//	if(bEnable)
	//		ModelShadowType = EM_MODEL_SHADOW_TYPE_MIDDLE;
	//	else
	//	{
	//		if(ModelShadowType > EM_MODEL_SHADOW_TYPE_LOW)
	//			ModelShadowType = EM_MODEL_SHADOW_TYPE_NONE;
	//	}
	//}//<Shadow Sign>
#endif

};

struct KG3DEngineCaps 
{
	D3DCAPS9	D3DCaps;
	
	BOOL	IsShadowTypeAvailable[EM_MODEL_SHADOW_TYPE_COUNT];	//要检查是否支持低精度影子就 Caps.IsShadowTypeAvailable[EM_MODEL_SHADOW_TYPE_LOW]

	enum
	{
		EM_MAX_SHADER_MODEL_SUPPORTED = 3,
	};

#ifdef __cplusplus
	KG3DEngineCaps()
	{
		memset(this, 0, sizeof(KG3DEngineCaps));
	}
#endif
};

enum
{
	EM_GAME_BOOST_DEFAULT = 1,		//默认服务器时间是实际时间的6倍
	EM_GAME_INIT_TIME_DEFAULT = 7,	//游戏默认是7点
};

struct KG3D_GAMETIME_INITSTRUCT
{
	DWORD dwInitTimeMS;		//游戏时间从什么时候开始，单位：微秒，最小时间是 0 最大是 3600 * 24 * 1000
	FLOAT fBoostFactor;	//游戏时间是现实时间的多少倍
} ;
//逻辑的常用值在引擎传进来就可以了，不要把逻辑的头文件搅合到引擎
struct KG3DLogicalConstances 
{
	FLOAT logicalCellCmLength;
	FLOAT regionGridHeight;
	FLOAT regionGridWidth;
	FLOAT terrainMinHeight;
	FLOAT terrainMaxHeight;
	FLOAT cellLength;
	FLOAT pointPerAltitude;
	FLOAT altitudeUnit;
	INT   invalidObstableGroup;
};
struct KG3D_GAME_INIT_CONTEXT 
{
	KG3D_GAMETIME_INITSTRUCT gameTime;
	KG3DLogicalConstances	logicalConstance;
};

enum // ssao level
{
    SSAO_LEVEL_LOWER,
    SSAO_LEVEL_NORMAL,
    SSAO_LEVEL_HIGH
};


struct PostRenderParams
{
    /* bloom */
    float fBloomExposure1;        
    float fBloomExposure2;           
    float fBloomDelay;      
    float fBloomGate;
    float fBloomGaussCoefficient;     
    int   nBloomSampleNum;

    /* detail */
    float fDetailPower;
    float fBlurPower;
    float fBlurDistance;

    /* hsi */
    float fHueScale;
    float fHueBias;
    float fSaturationScale;
    float fSaturationBias;
    float fIntensityScale;
    float fIntensityBias;

    /* shock wave */
    float fShockWavePower;

    /* god ray */
    int   nGodRaySampleNum;
    float fGodRayDensity;
    float fGodRayWeight;
    float fGodRayDecay;
    float fGodRayExposure;
    float fLimitAngle;

    /* ssao */
    int   nSSAOLevel;        
    float fSSAOSampleRadius;
    float fSSAODarkFact;
    float fBlurWeight;

    // color curve
    int  nCurveStype;
    BYTE CurveRed[256];
    BYTE CurveGreen[256];
    BYTE CurveBlue[256];

    float fKC;
    float fKM;
    float fKY;

    /* fog */
    float fFogDensityV;
    float fSlopeThreshold;
    float fHeightFalloff;
    D3DXVECTOR4 vecFogcolor;

    /* shadow */
    BOOL  bEnableAreaShadow;
    float fSoftness;
    float fJitter;
	float fShadowDark;
	float fKernerSize;
	float fDepthBias;
	float fBiasSlope;

	/* hdr */
	float fHDRBrightGate;
	float fHDRRectify;
	float fHDRGrayLevel;
	int nHDRStarType;
	BOOL bHDREnableBlueShift;
	float fHDRBloomScale;
	float fHDRStarScale;
		/* ColorGrade*/
	char szLut[MAX_PATH];
	float fBrightness;
	float fSaturation;
	float fContrast;

	/* dof */
	BOOL bDofUseCameraParam;
	float fDofDis;
	float fDofNear; /* 10 */
	float fDofFar;  /* 80000 */
	float fDofBlurRadius;
	float fDofBlurCorrectValue;

	/*TRACKBLUR*/
	float fTBSampleDist;
	float fTBSampleStrength;
	D3DXVECTOR2 vec2TBCenter;

	/*PostCloud*/
	float fCloudHeightMax;
	float fCloudHeightMin;
	float fCloudDensity;
	float fCloudThickness;
	float fCloudSpeed;
	D3DXVECTOR3 vCloudDir;
	D3DXVECTOR4 vCloudTexture3DUV;
	float fCloud3DNoiseUV;
	float fCloud3DNoiseBase;
	float fCloud3DNoiseScale;
	float fCloudRayStepAdd;
	float fCloudRayStep;
};

////因为是编辑器用的``故把下面结构体移到IEEditorType.h里去 Modify by huangjinshou 2011-3-30
// Editor Engine Option
//struct KG3DEngineEditorOption
//{
//	//以下几项如果要客户端使用，则要放到上面的结构中
//	//并改变用到的地方
//	BOOL bUseLogical;
//	BOOL bUseLogicalObject;
//	BOOL bRenderTerrain;
//	BOOL bRenderGround;
//	BOOL bTerrDynamic;
//	BOOL bUseMultiThreadLoad;
//	BOOL bUseMultiThreadCull;//是否使用多线程裁剪
//	BOOL bUseProgressMeshLOD;//是否使用模型LOD
//	BOOL bShowTestDlg;
//
//	TCHAR szWaterConfigFile[MAX_PATH];	
//
//	//float fBloomExposure1;             // now use to exposure 1
//	//float fBloomExposure2;             // now use to exposure 2
//	//float fBloomRate;          // bloom 当前的变化率
//	//float fBloomDelay;         // bloom 的过度时间
//	//float fBloomGate;
//	//float fBloomGaussCoefficient;     
//	//int   nBloomSampleNum;
//	//float fShockWavePower;
//	//float fHueScale;
//	//float fHueBias;
//	//float fSaturationScale;
//	//float fSaturationBias;
//	//float fIntensityScale;
//	//float fIntensityBias;
//
// //   float fDetailPower;
// //   float fBlurPower;
// //   float fBlurDistance;
//
//    //// color curve CMYK
//    //int  nCurveStype;
//    //BYTE CurveRed[256];
//    //BYTE CurveGreen[256];
//    //BYTE CurveBlue[256];
//
//    //float fKC;
//    //float fKM;
//    //float fKY;
//
// //   // god ray
// //   int   nGodRaySampleNum;
// //   float fGodRayDensity;
// //   float fGodRayWeight;
// //   float fGodRayDecay;
// //   float fGodRayExposure;
// //   float fLimitAngle;
//
// //   // ssao
// //   int   nSSAOLevel;        
// //   float fSSAOSampleRadius;
// //   float fSSAODarkFact;
// //   float fBlurWeight;
//	//
//	BOOL bStopSpecialElements;
//
//	////fog
//	//float fFogDensityV;
//	//float fSlopeThreshold;
//	//float fHeightFalloff;
//	//D3DXVECTOR4 vecFogcolor;
//	// Shadow map
//	BOOL bEnableAutoReLoadTexture;
//
//	INT  nFlySpeedX; //飞行模式X加速度
//	INT  nFlySpeedY; //飞行模式Y加速度
//	
//	BOOL bEnableWireFrameModeTerrain;
//#ifdef __cplusplus
//	KG3DEngineEditorOption(){memset(this, 0, sizeof(KG3DEngineEditorOption));}
//#endif
//};
/////////////////////////////////////////////////////////////////////////////////////////////////
enum SkinShaderPass
{
	PASS_SkinShader_old,
	PASS_SkinShader_spec,
	PASS_SkinShader_emap,
	PASS_SkinShader_diff,
	PASS_SkinShader_all,
};

enum NewLightShaderPass
{
	DEFST_NEWLIGHT_SPECULAR,
	DEFST_NEWLIGHT_ENV,
	DEFST_NEWLIGHT_DIFFUSE,
	DEFST_NEWLIGHT_ALL,
};

enum FunctionType
{
	FT_NONE = 0,
	//From KG3DModelST
	//From KG3DModel
	FT_KG3DMODEL_SETTRANSLATION = 1,
	FT_KG3DMODEL_SETROTATION = 2,
	FT_KG3DMODEL_SETROTATIONCENTER = 3,
	FT_KG3DMODEL_SETSCALING = 4,
	FT_KG3DMODEL_SETSCALINGROTATION = 5,
	FT_KG3DMODEL_SETSCALINGCENTER = 6,
	FT_KG3DMODEL_RESETTRANSFORM = 7,
	FT_KG3DMODEL_LOADFROMFILE = 8,
	FT_KG3DMODEL_DESTRUCT = 9,
	FT_KG3DMODEL_BINDTOSOCKET = 10,
	FT_KG3DMODEL_BINDTOBONE = 11,
	FT_KG3DMODEL_ATTACHMODEL = 12,
	FT_KG3DMODEL_DETCHMODEL = 13,
	FT_KG3DMODEL_PLAYANIMATION = 14,
	FT_KG3DMODEL_PALYSPLITANIMATION = 15,
	FT_KG3DMODEL_LOADMATERIALFROMFILE = 16,
	FT_KG3DMODEL_SETALPHA =17,
	FT_KG3DMODEL_SETCALLBACKRENDER = 18,
	//From KG3DScene
	FT_KG3DSCENEEDITOR_DESTRUCT = 19,
	FT_KG3DSCENEEDITOR_LOADFROMFILE = 20,
	FT_KG3DSCENEEDITOR_ADDRENDERENTITY = 21,
	FT_KG3DSCENEEDITOR_REMOVERENDERENTITY = 22,
	FT_KG3DSCENEEDITOR_ADDOUTPUTWINDOW = 23,

	//From KG3DTrackCamera
	//From KG3DCameraq
	FT_KG3DCAMERA_SETTRACKINFO = 24,
	FT_KG3DCAMERA_UPDATECAMERA = 25,	
	FT_KG3DCAMERA_SETPOSITION = 26,
	FT_KG3DCAMERA_SETLOOKATPOSITION = 27,
	FT_KG3DCAMERA_SETUPDIRECTION = 28,
	FT_KG3DCAMERA_SETGLOBALPERSPECTIVE = 29,
	FT_KG3DCAMERA_SETGLOBALORTHOGONAL = 30,

	//From KG3DSoundShell
	FT_KG3DSOUND_PLAYBGMUSIC = 31,
	FT_KG3DSOUND_STOPBGMUSIC = 32,
	FT_KG3DSOUND_SETBGMUSICVOLUME = 33,
	FT_KG3DSOUND_SETBGMUSICLOOP = 34,

	FT_PLAY_CAMERA_ANI = 60,
    FT_PLAY_DYNAMIC_WEATHER = 61,
    FT_PLAY_LOOP_CONTROL=62,
    FT_PROCESS_ACTOR_PHYSX = 63,
};


struct RecordOption
{
	SIZE                 Size;
	FLOAT                fInterval;
	D3DTEXTUREFILTERTYPE FiterType;
	D3DXIMAGE_FILEFORMAT ImageType;
	INT                  nAutoScale;
	BOOL                 bKeep;
};

struct Parameters
{
	static const int sMaxNum = 10;
	int nNum;
	int nFrom[sMaxNum];
	size_t size_tDataSize;
	char* pData; 
	Parameters()
	{
		nNum = 0;
		size_tDataSize = 0;
		pData = NULL; 
	};
};

struct EventRecord
{
	DWORD dwID;
	FunctionType EventFunction;
	DWORD dwTime;
	DWORD dwFrame;
	Parameters AParameters;
	EventRecord* pNextEvent;
	EventRecord()
	{
		dwID = 0;
		EventFunction = FT_NONE;
		dwTime = 0;
		dwFrame = 0;
		pNextEvent = NULL;
	};
};

enum TrueType{TT_NONE,TT_MODEL,TT_TRACKCAMERA,TT_MODELST,TT_SCENEEDITOR,TT_SFX};
struct RecObj
{		
	std::string ObjName;
	TrueType ObjType;
	EventRecord* pEventHead;
	EventRecord* pCurrentEvent;
};

enum KG3DWALLELEMENTTYPE
{
	WALLELEMENT_WALL,
	WALLELEMENT_DOOR,
	WALLELEMENT_STARTEND,
	WALLELEMENT_CORNER_90,
	WALLELEMENT_CORNER_60,
	WALLELEMENT_CORNER_ALL,
};



/* KG3DRESULT */

#define E_CDN_NUMBER    MAKE_HRESULT(1, FACILITY_ITF, 0xF0)
#define E_CDN_TYPE      MAKE_HRESULT(1, FACILITY_ITF, 0xF1)
#define E_MUTL_LOAD_ARRAY_FULL          MAKE_HRESULT(1, FACILITY_ITF, 0xF2)
#define E_MUTL_LOAD_ALREADY_IN_ARRAY    MAKE_HRESULT(1, FACILITY_ITF, 0xF3)

//动画控制器优先级
enum enuAnimationControllerPriority
{
	ANICTL_PRIMARY,//主控制器
	ANICTL_SECONDARY,//辅助控制器, 辅助的渲染优先级高于主的
	ANICTL_COUNT,
	ANICTL_FORCEDWORD = 0xffffffff,
};

struct TweenTimeSpan
{
	DWORD dwTweenIn;
    DWORD dwTweenOut;
	float fTweenWeigth;
	TweenTimeSpan()
	{
		dwTweenIn = 0;
		dwTweenOut = 0;
		fTweenWeigth = 1.0F;
	}
};

#define MAXVERTEX  65535

//用于渲染用的结构体，需要多少参数都加进去，这样就不需要和KG3DLight这个类搅合在一起了
struct  KG3DLightParam
{
	D3DXVECTOR3		dir;
	D3DCOLORVALUE	diffuse;
	D3DCOLORVALUE	specular;
	D3DCOLORVALUE	sceneAmbient;//SceneAmbient相当于D3DRS_AMBIENT和Light的Ambient是不一样的，参考D3D光照公式ambient = sceneambient * lightambient * texcolor...
	
	D3DCOLORVALUE	sky_light;
	D3DCOLORVALUE	com_light;	//补光
	
	KG3DLightParam(){ZeroMemory(this,sizeof(KG3DLightParam)); dir.y = -1;}
	KG3DLightParam(const KG3DLightParam& other)
	{
		memcpy_s(this, sizeof(KG3DLightParam), &other, sizeof(KG3DLightParam));
	}
	KG3DLightParam& operator=(const KG3DLightParam& other)
	{
		memcpy_s(this, sizeof(KG3DLightParam), &other, sizeof(KG3DLightParam));
		return *this;
	}
};

//同样是用于渲染用的结构体，避免和Fog类耦合
struct KG3DFogParamShader	//这个和Shader里面的定义必须一致，不然SetValue进去就会失败
{
	D3DXCOLOR vColor;
	FLOAT  fStart;
	float  fDensityDevidedBy_endMinusStart;	//(density / (end - start))
};
struct KG3DFogParam : public KG3DFogParamShader
{
	FLOAT	fEnd;
	BOOL	bEnable;		//默认FALSE
	INT		nFogMode;		//默认是D3DFOG_LINEAR
	BOOL	bUseTableFog;	//默认FALSE
	KG3DFogParam(){ZeroMemory(this,sizeof(*this));}
};

#define MAX_POINTLIGHT  4

enum /*WaterDetail*/ 
{
    WD_LOWER,
    WD_MEDIUM,
    WD_HIGH,
    WD_VERY_HIGH,
    WD_FULL_EFFECTIVE,

    WD_COUNT
};

enum RENDER_PARAM : DWORD
{
    RENDER_PARAM_ZFAR           = 0,
    RENDER_PARAM_MP_CPU_NUM     = 1,
    RENDER_PARAM_CAMERA_ANGEL   = 2

};

enum FRAMEMOVE_OPTION : DWORD
{
    FRAMEMOVE_SKIN_MESH         =   (1 << 0),
    FRAMEMOVE_NORL_MESH         =   (1 << 1),
    FRAMEMOVE_SPEEDTREE         =   (1 << 2),
    FRAMEMOVE_SFX               =   (1 << 3),
    FRAMEMOVE_PHYSICS           =   (1 << 4),
    FRAMEMOVE_ENVIRONMENT       =   (1 << 5),
    FRAMEMOVE_CLIENT_OBJ        =   (1 << 6),
	FRAMEMOVE_PHYSX             =   (1 << 7),
    FRAMEMOVE_PARTICLE          =   (1 << 8),
    FRAMEMOVE_ALL               =   0xffffffff
};

enum RENDER_OPTION : DWORD
{
	RENDER_TERRAIN              =	(1 << 0),       // terrain
	RENDER_GRASS	            =	(1 << 1),       // grass
	RENDER_ENVIRONMENT	        =	(1 << 2),
	RENDER_WATER	            =	(1 << 3),       // water
	RENDER_ENTITY	            =	(1 << 4),
	RENDER_TERR_TOPVIEW		    =	(1 << 5),
	RENDER_GRASS_TOPVIEW	    =	(1 << 6),
	RENDER_ENVIRONMENT_TOPVIEW	=   (1 << 7),
	RENDER_WATER_TOPVIEW	    =	(1 << 8),
	RENDER_ENTITY_TOPVIEW	    =	(1 << 9),
	RENDER_TERREDGE_TOPVIEW     =   (1 << 10),
	RENDER_TREE                 =   (1 << 11),      // speed tree
	RENDER_INFO                 =   (1 << 12),
	RENDER_VIDEO_MEMERY_INFO    =   (1 << 13),
	RENDER_STONE                =   (1 << 14),
	RENDER_FRUTEX               =   (1 << 15),
	RENDER_FPSHISTROY           =   (1 << 16),
    RENDER_SKIN_MESH            =   (1 << 17),
    RENDER_NORL_MESH            =   (1 << 18),
    RENDER_SFX                  =   (1 << 19),
    RENDER_CLIENT_OBJ           =   (1 << 20),
    RENDER_WATER_REFLECTION     =   (1 << 21),
    RENDER_DRAWABLE_BILLBOARD   =   (1 << 22),
    RENDER_CPU_MODEL_PROCESS    =   (1 << 23),
    RENDER_POINT_SIGN           =   (1 << 24),		//这个指所有点状标志，不单单是点光源的
    RENDER_SCENE_AID_OBJ        =   (1 << 25),
	RENDER_ENVIRONMENTVOLUME    =   (1 << 26),
    RENDER_ALL		            =	0xffffffff,
};


enum MODELCLOSEGROUND_TYPE
{
	MODELCLOSE_NONE,
	MODELCLOSE_FACINGDIR,
	MODELCLOSE_FACINGCROSSDIR,
	MODELCLOSE_FREE
};

//fmod reverb的预设(见fmod.h带FMOD_PRESET_前缀的宏)
enum SOUNDREVERB_TYPE
{
	SOUNDREVERB_OFF,
	SOUNDREVERB_GENERIC,
	SOUNDREVERB_PADDEDCELL,
	SOUNDREVERB_ROOM,
	SOUNDREVERB_BATHROOM,
	SOUNDREVERB_LIVINGROOM,
	SOUNDREVERB_STONEROOM,
	SOUNDREVERB_AUDITORIUM,
	SOUNDREVERB_CONCERTHALL,
	SOUNDREVERB_CAVE,
	SOUNDREVERB_ARENA,
	SOUNDREVERB_HANGAR,
	SOUNDREVERB_CARPETTEDHALLWAY,
	SOUNDREVERB_HALLWAY,
	SOUNDREVERB_STONECORRIDOR,
	SOUNDREVERB_ALLEY,
	SOUNDREVERB_FOREST,
	SOUNDREVERB_CITY,
	SOUNDREVERB_MOUNTAINS,
	SOUNDREVERB_QUARRY,
	SOUNDREVERB_PLAIN,
	SOUNDREVERB_PARKINGLOT ,
	SOUNDREVERB_SEWERPIPE,
	SOUNDREVERB_UNDERWATER,

	SOUNDREVERB_NUM,                   //enum个数
};

struct SoundDataBase
{
};

struct SoundBallData : public SoundDataBase
{
	TCHAR strFileName[MAX_PATH];//声音文件名
	//soundball都是循环播放的， 这里的循环播放的意思是连续循环播放，如果不连续， 那么就会等待检测间隔设置的时间来检测是否播放
	BOOL bLoop;//是否循环播放，循环和播放几率是互斥的
	float fRation;//播放频率
	BOOL bTimeEnable;//是否根据时间
	int nTimeStart;//出现时间
	int nTimeEnd;//结束时间
	float fRadius;//作用半径
	int nTimeCheckSpan;//检测间隔
	int nSoundCount;//声音的个数，兼容老版本用
	int nRef;
	SoundBallData()
	{
		memset(strFileName, 0, MAX_PATH);
		fRation = 1.0f;
		bTimeEnable = FALSE;
		nTimeStart = 0;
		nTimeEnd = 0;
		fRadius = 1000;
		nTimeCheckSpan = 10000;
		nSoundCount = 1;
		nRef = 0;
		bLoop = FALSE;
	}
};

struct SoundPolygonData : public SoundDataBase
{
	TCHAR strFileName[MAX_PATH];//声音文件名
	//soundball都是循环播放的， 这里的循环播放的意思是连续循环播放，如果不连续， 那么就会等待检测间隔设置的时间来检测是否播放
	BOOL bLoop;//是否循环播放，循环和播放几率是互斥的
	float fRation;//播放频率
	BOOL bTimeEnable;//是否根据时间
	int nTimeStart;//出现时间
	int nTimeEnd;//结束时间
	int nTimeCheckSpan;//检测间隔
	int nRef;
	SoundPolygonData()
	{
		memset(strFileName, 0, MAX_PATH);
		fRation = 1.0f;
		bTimeEnable = FALSE;
		nTimeStart = 0;
		nTimeEnd = 0;
		nTimeCheckSpan = 10000;
		nRef = 0;
		bLoop = FALSE;
	}
};

struct SoundReverbData :  public SoundDataBase
{
	//数据
	BOOL bApply;
	int nType;
	float fVolume;
	float fFadeTime; 
	float fExteriorVolume;
	float fExteriorTime;
	float fExteriorLPF;                 //LPF(LowPassFilter)
	float fExteriorLPFTime;
	float fInteriorVolume;
	float fInteriorTime;
	float fInteriorLPF;
	float fInteriorLPFTime;

	//其它
	int nRef;
	SoundReverbData()
	{
		bApply = TRUE;
		nType = SOUNDREVERB_OFF;
		fVolume = 0.5f;
		fFadeTime = 0.5f;
		fExteriorVolume = 0.0f;
		fExteriorTime = 0.01f;
		fExteriorLPF = 0.0f;
		fExteriorLPFTime = 0.01f;
		fInteriorVolume = 1.0f;
		fInteriorTime = 0.5f;
		fInteriorLPF = 1.0f;
		fInteriorLPFTime = 0.5f;

		nRef = 0;
	}
};

#define BLOCK_LIST_STATE_NODATA   0
#define BLOCK_LIST_STATE_DATAOK   1
///////////////////////////////////////////////////////////////////////////////////////////////
////因为是编辑器用的``故把下面结构体移到IEEditorType.h里去 Modify by huangjinshou 2011-10-11
//enum
//{
//	EM_SELMASK_MODEL       = (1 << 0),
//	EM_SELMASK_MODELSET    = (1 << 1),       
//	EM_SELMASK_SPEEDTREE   = (1 << 2),
//	EM_SELMASK_SFX		   = (1 << 3),
//	EM_SELMASK_OBJSET      = (1 << 4),
//	EM_SELMASK_LOGICOBJ    = (1 << 5),
//	EM_SELMASK_NODE        = (1 << 6),
//	EM_SELMASK_SOUNDBALL   = (1 << 7),
//	EM_SELMASK_NOSMALLOBJ  = (1 << 8),//不选择小物件
//	EM_SELMASK_NOBIGOBJ    = (1 << 9), //不选择大物件
//	EM_SELMASK_CLIENT_SELABLE = (1 << 10), //客户端的选取屏蔽
//	
//	EM_SELMASK_ALL = EM_SELMASK_MODEL|EM_SELMASK_MODELSET|EM_SELMASK_SPEEDTREE|EM_SELMASK_SFX|EM_SELMASK_OBJSET|
//				     EM_SELMASK_LOGICOBJ|EM_SELMASK_NODE |EM_SELMASK_SOUNDBALL,
//    EM_SELMASK_NONE = (1 << 31) // 强制关闭所有的选择过滤，所有物件都能选中
//	//0xffffffff & (~(EM_SELMASK_NOSMALLOBJ)) & (~(EM_SELMASK_NOBIGOBJ)),
//
//};
/////////////////////////////////////////////////////////////////////////////////////////////////
enum ModelDetailType
{
    MainModel,
    ChildModel,
    BindModel,
    SelectModel,
};
struct  ModelDetail
{
    int nVertex;
    int nFace;
    int nBone;
    int nSubset;
    int nNumTexture;
    std::vector<std::string>  TextureType;
    std::vector<std::string>  TextureName;
    std::string szModelName;
    ModelDetailType type;
    ModelDetail()
    {
        type = MainModel;
        nVertex = 0;
        nFace = 0;
        nBone = 0;
        nSubset = 0;
        nNumTexture = 0;
        szModelName = "";
    }
    ~ModelDetail()
    {
    }
};
struct ModelDetailOption 
{
    BOOL bShow;//总开关
    BOOL bShowTextureName;//是否显示贴图名称
    BOOL bShowTextureType;//是否显示贴图类型
    BOOL bShowChildDetail;//是否显示子模型信息
    BOOL bShowBindDetail;// 是否显示绑定模型信息
    BOOL bShowSingleChildDetail;// 是否显示被选中的单个模型信息
    BOOL bShowBaseData;// 显示基础数据 ，顶点 ，面。。。

    BOOL bShowTextureNameChild;
    BOOL bShowTextureTypeChild;
    BOOL bShowBaseDataChild;

    BOOL bShowTextureNameSelect;
    BOOL bShowTextureTypeSelect;
    BOOL bShowBaseDataSelect;
    ModelDetailOption()
    {
        bShow = FALSE;
        bShowTextureName = FALSE;
        bShowTextureType = FALSE;
        bShowChildDetail = FALSE;
        bShowBindDetail = FALSE;
        bShowSingleChildDetail = FALSE;
        bShowBaseData = TRUE;
        bShowTextureNameChild = FALSE;
        bShowTextureTypeChild = FALSE;
        bShowBaseDataChild = TRUE;

        bShowTextureNameSelect = FALSE;
        bShowTextureTypeSelect = FALSE;
        bShowBaseDataSelect = TRUE;
    }
};

enum SaveMeshBlockType
{
	SMBT_NORMAL,
	SMBT_OPTIMIZED,
	SMBT_BLENDED,
	SMBT_ACTIVE,
	SMBT_COUNT,			//新的类型加在这个值前面
	SMBT_FORCE_DWORD = 0xffffffff,
};

enum PostRenderEffectTransitionsType
{
	PostRenderEffectTransitionsType_None = -1,
	PostRenderEffectTransitionsType_OverLapping,
	PostRenderEffectTransitionsType_FadeIn,
	PostRenderEffectTransitionsType_FadeOut,
	PostRenderEffectTransitionsType_Count,
};
typedef SaveMeshBlockType MeshType;

enum CULLER_INDEX
{
	CULLER_SCENE_MAIN,
	CULLER_SHADOW_0,
	CULLER_SHADOW_1,
	CULLER_SHADOW_2,
	CULLER_TOPVIEW,
	CULLER_SNAPTOOL,
	CULLER_COUNT,
};

enum MODEL_LOAD_STATE
{
	MLS_INVALID,
	MLS_LOADING,
	MLS_SUCCESS,
	MLS_FAILED
};

enum ResNodeState  //KG3DTemplate.h内定义的资源管理器里的资源节点的状态
{
	RES_INIT = 0,	//初始态.节点刚创建时的状态
	RES_WAIT_LOAD,	//仅在异步时能由render填充:推送加载队列前设置
	RES_UNDO_LOAD,	//仅异步时能由render填充:通知loader:本资源无需再加载,loader发现其为该值时将重置为FAIL,以便render删除节点
	RES_LOADING,	//仅异步时能由loader填充:表明其已开始加载该资源
	RES_LOAD_SUCC,	//同步时由render,异步时由loader填充:表明资源确实需要加载且最终加载成功
	RES_LOAD_FAIL	//同步时由render,异步时由loader填充:表明资源加载失败,render发现后会将该资源节点UnInit
};

class FacePartInfo
{
public:
	int nRoleType;
	int nID;
	TCHAR szName[MAX_PATH];
	TCHAR szMesh[MAX_PATH];
	TCHAR szTexture[MAX_PATH];
	int nWidth;
	int nHeight;
	FacePartInfo()
	{
		nRoleType = 0;
		nID = 0;
		memset(szName, MAX_PATH, 0);
		memset(szMesh, MAX_PATH, 0);
		memset(szTexture, MAX_PATH, 0);
		nWidth = 0;
		nHeight = 0;
	}
	FacePartInfo& operator=(const FacePartInfo& other)
	{
		nRoleType = other.nRoleType;
		nID = other.nID;
		strncpy_s(szName, other.szName, MAX_PATH);
		strncpy_s(szMesh, other.szMesh, MAX_PATH);
		strncpy_s(szTexture, other.szTexture, MAX_PATH);
		nWidth = other.nWidth;
		nHeight = other.nHeight;
		return *this;
	}
};

struct KG3D_FACE_PART_INFO_ARRAY 
{
	FacePartInfo *pData;
	unsigned uCount;
};

struct KG3DPSImageParam
{
	float fGamma;
	float fBrightness;
	float fContrast;
	KG3DPSImageParam()
		: fGamma(1.0f)
		, fBrightness(0.0f)
		, fContrast(0.0f)
	{

	}
};

enum KG3DPSFilterType
{
	PSFilter_None = 0,			//无
	PSFilter_AutoLevel,			//直方图增强	唯美
	PSFilter_BlackWhite,		//黑白	黑白色
	PSFilter_BrightContrast,	//亮度对比度	印象
	PSFilter_Convolution,		//移轴镜头（景深/渐变模糊）
	PSFilter_Edge,				//描边	描边（蜡笔）
	PSFilter_Feather,			//羽化	羽化（白色晕影）
	PSFilter_GaussianBlur,		//高斯模糊	高斯模糊
	PSFilter_Light,				//强光	强光（经典LOMO）
	PSFilter_OldPhoto,			//旧照片	老照片
	PSFilter_RainBow,			//彩虹
	PSFilter_SaturationModify,	//饱和度	经典影楼
	PSFilter_Lomo,				//黑色光晕
	PSFilter_Scene,				//使用第一种Gradient参数	潘多拉
	PSFilter_Film,				//电影胶卷	胶片
	PSFilter_Gamma,				//颜色加深
	PSFilter_Count,
};
//------------
#endif // _KG3DTYPES_H_