/************************************************************************/
/* Lua V5.02脚本														*/
/* Copyright : Kingsoft 2006											*/
/* Author	 : Zhu Jianqiu												*/
/* History	 :															*/
/*		2006.02.18	Create												*/
/* Comment	 :															*/
/*		封装了Lua5脚本的操作											*/
/************************************************************************/

#ifndef _KLUA_SCRIPT_EX_H_
#define _KLUA_SCRIPT_EX_H_

#include <map>
#include <vector>

#include "../../DevEnv/Include/Lua5/lualib.h"
#include "../../DevEnv/Include/Lua5/lauxlib.h"

#define MAX_SCIRPT_NAME_LEN		256
#define MAX_ENV_NAME_LEN		16

#define LUA_SCRIPT_THIS		"KLuaScriptExThis"
#define LUA_SCRIPT_ID		"ScriptID"

struct KLuaFunc
{
	const char*		pszFuncName;
	lua_CFunction	pFunc;	
};

struct KLuaConst
{
	const char*		pszConstName;
	int				nValue;
};

struct KLuaConstList
{
	const char*		pszListName;
	KLuaConst*		pConstList;
};


struct KLuaScriptData
{
	char                szName[MAX_SCIRPT_NAME_LEN];
	std::vector<DWORD>  vecIncludeScriptID;
};

// 脚本ID计算函数: g_FileNameHash()

struct ILuaScriptEx
{
	virtual void	Release() = 0;

	virtual DWORD	LoadFromFile(const char* pszFileName) = 0;
	virtual BOOL	LoadFromBuffer(DWORD dwScriptID, const char* pszScriptName, const char* pszBuffer, DWORD dwSize) = 0;

	virtual void	RegisterFunction(KLuaFunc &LuaFunc) = 0;
	virtual void	RegisterFunctions(KLuaFunc Funcs[], int nFuncCount = 0) = 0;
	virtual void	RegisterConstList(KLuaConstList* pLuaConstList) = 0;

	virtual void	SafeCallBegin(int* pIndex) = 0;
	virtual void	SafeCallEnd(int nIndex) = 0;
	virtual BOOL	IsFuncExist(DWORD dwScriptID, const char* pszFuncName) = 0;
	virtual BOOL	CallFunction(DWORD dwScriptID, const char* pszFuncName, int nResults) = 0;
	virtual void	AddParamCount() = 0;
	virtual BOOL	GetValuesFromStack(const char* pszFormat , ...) = 0;
	virtual BOOL	GetValuesFromStack(const char* pszFormat , va_list vlist) = 0;
	
	virtual lua_State*	GetLuaState(void) = 0;

	virtual BOOL		IsScriptExist(DWORD dwScriptID) = 0;

	virtual DWORD		GetActiveScriptID() = 0;

	virtual KLuaScriptData* GetScriptData(DWORD dwScriptID) = 0;

	template<class T> void PushValueToStack(T value);	
};

template<class T>
inline void ILuaScriptEx::PushValueToStack(T value)
{
	value->LuaGetObj(GetLuaState());

	AddParamCount();
}

template<>
inline void ILuaScriptEx::PushValueToStack(int value)
{
	lua_pushinteger(GetLuaState(), value);

	AddParamCount();
}

template<> 
inline void ILuaScriptEx::PushValueToStack(DWORD value)
{
	lua_pushinteger(GetLuaState(), (int)value);

	AddParamCount();
}

template<> 
inline void ILuaScriptEx::PushValueToStack(BYTE value)
{
	lua_pushinteger(GetLuaState(), (int)value);

	AddParamCount();
}

template<>
inline void ILuaScriptEx::PushValueToStack(double value)
{
	lua_pushnumber(GetLuaState(), value);

	AddParamCount();
}

template<>
inline void ILuaScriptEx::PushValueToStack(const char* value)
{
	lua_pushstring(GetLuaState(), value);

	AddParamCount();
}

template<>
inline void ILuaScriptEx::PushValueToStack(Lua_CFunction value)
{
	lua_pushcfunction(GetLuaState(), value);

	AddParamCount();
}


C_ENGINE_API ILuaScriptEx* CreateLuaInterface();

#endif	//_KLUA_SCRIPT_EX_H_
