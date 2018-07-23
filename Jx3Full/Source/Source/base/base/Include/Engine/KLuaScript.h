//---------------------------------------------------------------------------
// Sword3 Engine (c) 1999-2004 by Kingsoft
// Date:	2001-9-11 11:11:09
// Code:	Romandou
//---------------------------------------------------------------------------
#ifndef _ENGINE_LUASCRIPT_H_
#define _ENGINE_LUASCRIPT_H_

#include "../../../DevEnv/Include/LuaAPI.h"
#include <stdarg.h>

//Added by AQ for Debugger, 2004.11.15
#ifdef LUA_DEBUG
	#include "../../../DevEnv/Include/Lua/luadebug.h"
	#include "../../../DevEnv/Include/Lua/ldebug.h"
#endif // LUA_DEBUG
//End Added by AQ

#ifdef __linux
	#include <string.h>
#endif

#define MAINFUNCTIONNAME "main"
enum LUA_ERROR
{
	LUA_CREATE_ERROR			= 1,
	LUA_SCRIPT_LEN_ERROR		= 2,
	LUA_SCRIPT_COMPILE_ERROR	= 3,
	LUA_SCRIPT_EXECUTE_ERROR	= 4,
	LUA_SCRIPT_NOT_NUMBER_ERROR = 10,
	LUA_SCRIPT_NOT_STRING_ERROR = 11,
	LUA_SCRIPT_NOT_TABLE_ERROR	= 12,
	LUA_SCRIPT_STATES_IS_NULL	= 20,
};

struct TLua_Funcs
{
	const char *name;
	lua_CFunction func;	
};

//---------------------------------------------------------------------------
class ENGINE_API KLuaScript
{
public:
	KLuaScript();
	virtual ~KLuaScript();
	KLuaScript(int StackSize);

	bool	Init();
	void	Exit();
	int		Activate()	{ return ExecuteMain(); }

	Lua_State*	GetLuaState() { return m_LuaState; }
	char*		GetScriptName(){ return (char *)m_szScriptName; }

	bool	Load(const char* FileName);
	bool	ExecuteMain();
	bool	CallFunction(const char* cFuncName, int nResults, char* cFormat, ...);
	bool	CallFunction(char* cFuncName, int nResults, char* cFormat, va_list vlist);
	bool	RegisterFunction(const char* FuncName, void* Func);
	void	SetScriptName(const char* scpname);

	int		GetUserTag() { return m_UserTag; };
	bool	RegisterFunctions( TLua_Funcs Funcs[], int n = 0);
	bool	LoadBuffer(const char* pBuffer, unsigned int dwLen);
	void	SafeCallBegin(int * pIndex);//记录当前堆栈栈顶位置，并保存到pIndex指向的数据中
	void	SafeCallEnd (int nIndex);//恢复至调用之前栈顶位置。
	bool	GetValuesFromStack(char * cFormat , ...);			
	
	bool	Stop();
	bool	Resume();
	unsigned int	CreateTable();
	unsigned int	ModifyTable(const char* szTableName); 
	void		PushNumber(double number);
	void		SetGlobalName(char* szName);
	inline void SetTableMember(int nIndex, int Id, const char * szString){Lua_SetTable_StringFromId(m_LuaState,  nIndex, Id, szString);};
	inline void SetTableMember(int nIndex, int Id, double nNumber){Lua_SetTable_DoubleFromId(m_LuaState,  nIndex, Id, nNumber);};
	inline void SetTableMember(int nIndex, int Id, int nNumber){Lua_SetTable_IntFromId(m_LuaState,  nIndex, Id, nNumber);};
	inline void SetTableMember(int nIndex, const char * szMemberName, Lua_CFunction CFun){Lua_SetTable_CFunFromName(m_LuaState,  nIndex, szMemberName, CFun);};
	inline void SetTableMember(int nIndex, int nId, Lua_CFunction CFun){Lua_SetTable_CFunFromId(m_LuaState,  nIndex, nId, CFun);};
	inline void SetTableMember(int nIndex, const char * szMemberName, char * szString){Lua_SetTable_StringFromName(m_LuaState,  nIndex, szMemberName, szString);};
	inline void SetTableMember(int nIndex, const char * szMemberName, int Number){Lua_SetTable_IntFromName(m_LuaState,  nIndex, szMemberName, Number);};
	inline void SetTableMember(int nIndex, const char * szMemberName, double Number){Lua_SetTable_DoubleFromName(m_LuaState,  nIndex, szMemberName, Number);};
	void	ScriptError(int Error, char *szFuncName);
	void	ScriptError(int , int, char*);
	bool	ExecuteCode();

private:
	void		RegisterStandardFunctions();
	bool		m_IsRuning;//是否该脚本有效
//Modified by AQ for debugger, 2004.11.18
//Original code:
//	char m_szScriptName[100];
//New code:
	char m_szFullScriptName[256];
	char m_szScriptName[256];
//End Modified by AQ
	int			m_UserTag;
	Lua_State*	m_LuaState;
//Added by AQ for Debugger, 2004.11.15
#ifdef LUA_DEBUG
private:
	static void LuaProcessDebugInfo(Lua_State* L, lua_Debug* ar);
#endif //LUA_DEBUG
//End Added by AQ

};

ENGINE_API void g_GetExecutingScript(char *pszScriptBuffer, int nScriptBufferLen, char *pszFunctionBuffer, int nFunctionBufferLen);

#endif //_ENGINE_LUASCRIPT_H_

