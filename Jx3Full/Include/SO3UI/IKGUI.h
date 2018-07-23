////////////////////////////////////////////////////////////////////////////////
//
//  FileName    : IKGUI.h
//  Version     : 1.0
//  Creator     : Hu Changyin
//  Create Date : 2007-11-30 10:37:08
//  Comment     : 
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _INCLUDE_IKGUI_H_
#define _INCLUDE_IKGUI_H_

////////////////////////////////////////////////////////////////////////////////

interface IKG3DUI;
interface IKG3DEngineManager;
interface IKG3DResourceManager;
struct IKG3DSoundShell;

struct lua_State;
struct luaL_reg;
struct KLuaConstList;
struct KLuaFunc;
class KSO3Client;
struct IKG3DSoundShellHolder;

struct KGUI_EVENT
{
	LPCSTR pszName;
	int nID;
};

struct KGUI_INIT_PARAM
{
	HINSTANCE hInst;
	HWND hWnd;
	IKG3DUI* p3DUI;
	IKG3DEngineManager* p3DEngineManager;
	IKG3DResourceManager* p3DModelManager;
	IKG3DSoundShellHolder* pSoundShellHolder;

    char szKLVideoDllPath[MAX_PATH];
    char szConfigPath[MAX_PATH];
    char szVersionPath[MAX_PATH];

    HWND* phwndEmbedWebPage;
    unsigned int uCodePage;
};

class IKGUI
{
public:
	virtual int Init(const KGUI_INIT_PARAM *pParam) = 0;
	virtual int NeedReset() = 0;
	virtual void Reset() = 0;
	virtual void Run() = 0;
	virtual void Exit() = 0;
	virtual void SetSoundShell(IKG3DSoundShell *pShell) = 0;

	virtual LRESULT WndProc(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0;
	virtual void Active() = 0;
	virtual void Paint() = 0;

	virtual lua_State* GetLuaState() = 0;

	//当然，也可以取得lua_State，自己写函数注册这些变量
	virtual void RegisterMetaTable(LPCSTR pszTable, luaL_reg const* pMetaFunc) = 0;
	virtual void RegisterLibTable(LPCSTR pszTable, luaL_reg const* pLibFunc) = 0;
	virtual void RegisterFunctions(luaL_reg const* pFunc) = 0;
	virtual void RegisterFunctions(KLuaFunc const* pFunc, int nCount) = 0;
	virtual void RegisterConstList(KLuaConstList const* pConstList) = 0;

	//获取输入框密码
	virtual BOOL GetPassword(LPCSTR szTreePath, char szDestMD5String[64]) = 0;

	virtual void PushArg(LPCSTR szName, bool bParam) = 0;
	virtual void PushArg(LPCSTR szName, int nParam) = 0;
	virtual void PushArg(LPCSTR szName, DWORD dwParam) = 0;
	virtual void PushArg(LPCSTR szName, float fParam) = 0;
	virtual void PushArg(LPCSTR szName, double dblParam) = 0;
	virtual void PushArg(LPCSTR szName, LPCSTR pcszParam) = 0;
	virtual void FireEvent(LPCSTR szEvent, DWORD dwCookie) = 0;

    virtual int SetCodePage(unsigned int uCodePage) = 0;
    virtual unsigned int GetCodePage() = 0;
};

#define	FN_CREATE_KGUI	"CreateKGUI"
typedef IKGUI*	(*fnCreateKGUI)();

#ifdef KGUI_EXPORTS
extern "C" __declspec(dllexport) IKGUI* CreateKGUI();
#else
extern "C" __declspec(dllimport) IKGUI* CreateKGUI();
#endif

#endif //_INCLUDE_IKGUI_H_
