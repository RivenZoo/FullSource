/********************************************************************
	created:	2008/12/09
	created:	9:12:2008   10:38
	filename: 	KLuaWrap.h
	author:		lizhi
	
	purpose:	lua5的c++封装
*********************************************************************/

#ifndef __KLuaWrap_h__
#define __KLuaWrap_h__

#include <cassert>
#include <vector>
#include "lua_tinker.h"

struct TLua_Funcs
{
	const char *name;
	lua_CFunction func;
};

class LMemPool;
struct LMemAllocInfo
{
	unsigned int	AllocMemSize;
	unsigned int	UseMemSize;
	unsigned int	SystemMemSize;
	unsigned int	ReallocCount;
	unsigned int	ReallocHitCount;
};

class ENGINE_API KLuaWrap
{
public:
	void			RegisterFunctions(const TLua_Funcs *pFuncs, size_t size);
	int				SafeCallBegin();
	int				CallFunction(const char *pTable, const char *pFunc, const char *pFormat = "", ...);
	int				CallFunctionV(const char *pTable, const char *pFunc, const char *pFormat, va_list vl);
	void			SafeCallEnd(int TopIndex);
	bool			DoScriptFile(const char *ScriptFile, const char *EnvName = NULL);
	bool			DoBuffer(const char *pBuffer, size_t size, const char *EnvName = NULL);

	LMemAllocInfo	GetMemAllocInfo();
	void			SetCallRetTypeAlert(bool AlertOpen) { m_CallRetTypeAlert = AlertOpen; }	// 是否开启函数返回值类型错误检测的输出

	template<typename T, typename P>
	void set(const char *EnvName, P p, T obj)
	{
		assert(m_L);
		if (EnvName && EnvName[0])
		{
			lua_tinker::table EnvTable = lua_tinker::get<lua_tinker::table>(m_L, EnvName);
			if (EnvTable.m_obj->m_pointer)
			{
				EnvTable.set(p, obj);
			}
		}
		else
			lua_tinker::set(m_L, p, obj);
	}

	template<typename T>
	T get(const char *EnvName, const char *name)
	{
		assert(m_L);
		if (EnvName && EnvName[0])
		{
			lua_tinker::table EnvTable = lua_tinker::get<lua_tinker::table>(m_L, EnvName);
			return EnvTable.get<T>(name);
		}
		else
			return lua_tinker::get<T>(m_L, name);
	}

	bool isnil(const char *EnvName, const char *name)
	{
		assert(m_L);
		if (EnvName && EnvName[0])
		{
			lua_tinker::table EnvTable = lua_tinker::get<lua_tinker::table>(m_L, EnvName);
			if (EnvTable)
				return EnvTable.isnil(name);
			else
				return true;
		}
		else
		{
			bool ret = false;
			lua_getglobal(m_L, name);
			if (lua_isnil(m_L, -1))
				ret = true;
			lua_pop(m_L, 1);
			return ret;
		}
	}

public:
	KLuaWrap();
	~KLuaWrap();

	bool			Init(std::string *pReserveGVar, size_t GVarCount, const char *ScriptRootPath = NULL);
	void			LoadJitOpt();
	lua_State*		GetLuaState(){ return m_L; }

private:
	void			_Exit();
	int				_Call(int ErrFunc, const char *pFormat, va_list vl);

	// 供Lua用的内存分配函数
	static void*	_Alloc_Fun(void* pScript, void* pMem, size_t nOldSize, size_t nNewSize);
private:
	lua_State		*m_L;

	unsigned int	m_uMemSize;			// 已分配内存大小

	char			m_ScriptPackagePath[80];
	LMemPool*		m_pMemPool;

	bool			m_CallRetTypeAlert;
};

#endif // __KLuaWrap_h__
