////////////////////////////////////////////////////////////////////////////////
//
//  FileName    : ISO3UI.h
//  Version     : 1.0
//  Creator     : Hu Changyin
//  Create Date : 2007-11-29 9:40:49
//  Comment     : 
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _INCLUDE_ISO3UI_H_
#define _INCLUDE_ISO3UI_H_

////////////////////////////////////////////////////////////////////////////////

struct lua_State;
struct luaL_reg;
struct KLuaConstList;
struct KLuaFunc;
struct IKG3DSoundShell;
class IKSO3GameWorldUIHandler;
class IKG3DUI;
class IKG3DEngineManager;
class IKG3DResourceManager;
class IKSO3RepresentHandler;
class IKGUI;
struct IKG3DSoundShellHolder;

typedef BOOL (*fnStringToID)(LPCTSTR, int&);

struct SO3UI_INIT_PARAM
{
	HINSTANCE hInst;
	HWND hWnd;

	//游戏逻辑改为DLL后，这两个参数将不存在，到时候保留一个游戏逻辑接口的指针，游戏逻辑的接口里面应该包含这两个方法。
	fnStringToID fnAttribute; //将游戏逻辑将attribute的key值变为id
	fnStringToID fnRequire; //将游戏逻辑将require的key值变为id

	IKG3DUI* p3DUI;
	IKG3DEngineManager* p3DEngineManager;
	IKG3DResourceManager* p3DModelManager;
	IKSO3RepresentHandler* pRepresent;
	IKG3DSoundShellHolder* pSoundShellHolder;

    char szKGUIDllPath[MAX_PATH];
    char szJX3InteractionDllPath[MAX_PATH];
    char szKLVideoDllPath[MAX_PATH];
    char szIceClientLibDllPath[MAX_PATH];
    char szConfigPath[MAX_PATH];
    char szVersionPath[MAX_PATH];

    HWND* phwndEmbedWebPage;
    unsigned int uCodePage;
};

class ISO3UI
{
public:
	virtual int Init(const SO3UI_INIT_PARAM *pParam) = 0;
    virtual void UnInit() = 0;
	virtual int NeedReset() = 0;
	virtual void Reset() = 0;
	virtual void Run() = 0;
	virtual void Exit() = 0;
	virtual void SetSoundShell(IKG3DSoundShell *pShell) = 0;

	virtual LRESULT WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
	virtual void Active() = 0;
	virtual void Paint() = 0;
    virtual void BeginPaint() = 0;
    virtual void EndPaint() = 0;

    virtual IKGUI* GetIKGUI() = 0;

	virtual IKSO3GameWorldUIHandler &GetGameWorldUIHandler() = 0;
};

#define	FN_CREATE_SO3UI	"CreateSO3UI"
typedef ISO3UI*	(*fnCreateSO3UI)();

#ifdef SO3UI_EXPORTS
extern "C" __declspec(dllexport) ISO3UI* CreateSO3UI();
#else
extern "C" __declspec(dllimport) ISO3UI* CreateSO3UI();
#endif

#endif //_INCLUDE_ISO3UI_H_
