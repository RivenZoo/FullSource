#include "Precompile.h"
#include "KGCRT.h"
#if defined(LUA_V_5)
#include "KLuaScriptEx.h"
#include "KGPublic.h"
#include "KGLog.h"
#include "File.h"

using namespace std;

class KLuaScriptEx : public ILuaScriptEx
{
public:
	KLuaScriptEx();

	void Release();

    BOOL Create();
    void Destroy();

	DWORD LoadFromFile(const char cszFileName[]);	

	BOOL LoadFromBuffer(DWORD dwScriptID, const char* pszScriptName, const char* pszBuffer, DWORD dwSize);

	void RegisterFunction(KLuaFunc &LuaFunc);
	void RegisterFunctions(KLuaFunc Funcs[], int nFuncCount = 0);
	void RegisterConstList(KLuaConstList* pLuaConstList);

	BOOL CallFunction(DWORD dwScriptID, const char* pszFuncName, int nResults);
	void AddParamCount();

	void SafeCallBegin(int* pIndex);
	void SafeCallEnd(int nIndex);

	// 从堆栈中取值
	BOOL GetValuesFromStack(const char* pszFormat , ...);
	BOOL GetValuesFromStack(const char* pszFormat , va_list vlist);

	// 指定的函数是否在脚本中存在
	BOOL IsFuncExist(DWORD dwScriptID, const char* pszFuncName);

	// 设定全局数据
	BOOL AddGlobalInteger(const char* pszVarName, int nValue);
	BOOL AddGlobalString(const char* pszValueName, const char* pszValue);

	// 设置文件局部变量
	BOOL AddInteger(DWORD dwScriptID, const char* pszVarName, int nValue);
	BOOL AddString(DWORD dwScriptID, const char* pszValueName, const char* pszValue);

	// 获取Lua堆栈
	lua_State* GetLuaState(void);

	// 判断脚本是否存在
	BOOL IsScriptExist(DWORD dwScriptID);

	// 获取当前正在被调用的脚本
	DWORD GetActiveScriptID();

	// 获取ScriptData
	KLuaScriptData* GetScriptData(DWORD dwScriptID);

	// 把脚本路径转换成hash后的ID
	DWORD ScriptNameToID(const char* pszName);

private:
	typedef std::map<DWORD, KLuaScriptData> SCRIPT_DATA_MAP;
	SCRIPT_DATA_MAP m_mapScriptData; 

	lua_State*			m_pLuaState;
	DWORD				m_dwActiveScript;
	int					m_nParamCount;
	
	// 注册脚本include关联
	static int Include(lua_State* L);		

	// 防止常量表在脚本中被修改,重载__newindex
	static int _NewIndexForConstList(lua_State* L);

	// 重载__index,为了实现新的Include
	static int _IndexForEnv(lua_State* L);

	// 从_include中找
	BOOL _GetVarInInclude(DWORD dwScriptID, const char* pszValueName);

	// 创建变量环境
	BOOL _MakeEnv(const char* szEnvName);
};

KLuaScriptEx::KLuaScriptEx(void)
{
	m_pLuaState         = NULL;
	m_dwActiveScript    = 0;
	m_nParamCount       = 0;
}

BOOL KLuaScriptEx::Create()
{
    BOOL bResult = false;

	assert(m_pLuaState == NULL);

	m_pLuaState = lua_open();
	KG_PROCESS_ERROR(m_pLuaState);

	luaopen_base(m_pLuaState);
	luaopen_table(m_pLuaState);
	luaopen_string(m_pLuaState);
	luaopen_math(m_pLuaState);

	lua_register(m_pLuaState, "Include", Include);

	lua_pushstring(m_pLuaState, LUA_SCRIPT_THIS);
	lua_pushlightuserdata(m_pLuaState, this);
	lua_settable(m_pLuaState, LUA_GLOBALSINDEX);

    bResult = true;
Exit0:
    if (!bResult)
    {
	    if (m_pLuaState)
	    {
		    lua_close(m_pLuaState);
		    m_pLuaState = NULL;
	    }
    }
	return bResult;
}

void KLuaScriptEx::Destroy()
{
	if (m_pLuaState)
	{
		lua_close(m_pLuaState);
		m_pLuaState = NULL;
    }
	m_dwActiveScript = 0;
	m_mapScriptData.clear();
}

DWORD KLuaScriptEx::LoadFromFile(const char cszFileName[])
{
    DWORD   dwResult            = 0;
	BOOL    bRetCode            = false;
	IFile*  piFile              = NULL;
	char*   pszBuffer           = NULL;
	DWORD   dwScriptID          = 0;
	DWORD   dwFileSize          = 0;
    DWORD   dwReadSize          = 0;

	dwScriptID = g_FileNameHash(cszFileName);

	bRetCode = IsScriptExist(dwScriptID);
	KG_PROCESS_SUCCESS(bRetCode);

	piFile = g_OpenFile(cszFileName);
	KG_PROCESS_ERROR(piFile);

	dwFileSize = piFile->Size();

	pszBuffer = new char[dwFileSize];
	KG_PROCESS_ERROR(pszBuffer);

	dwReadSize = piFile->Read(pszBuffer, dwFileSize);
	KG_PROCESS_ERROR(dwReadSize == dwFileSize);

	bRetCode = LoadFromBuffer(dwScriptID, cszFileName, pszBuffer, dwFileSize);
	KG_PROCESS_ERROR(bRetCode);

Exit1:
	dwResult = dwScriptID;
Exit0:
    if (dwResult == 0)
    {
        KGLogPrintf(KGLOG_ERR, "[Lua] Failed to load script: %s", cszFileName);
    }
	KG_DELETE_ARRAY(pszBuffer);
	KG_COM_RELEASE(piFile);
	return dwResult;
}

BOOL KLuaScriptEx::LoadFromBuffer(DWORD dwScriptID, const char* pszScriptName, const char* pszBuffer, DWORD dwSize)
{
    BOOL    bResult             = false;
	int     nRetCode            = 0;
	DWORD   dwOriginalScriptID  = m_dwActiveScript;

	assert(pszScriptName);
	assert(pszBuffer);

	m_dwActiveScript = dwScriptID;

	if (lua_gc(m_pLuaState, LUA_GCCOUNT, 0) > 20480) 
	{
		lua_gc(m_pLuaState, LUA_GCCOLLECT, 0);
	}

	if (dwScriptID == 0)
	{
		nRetCode = luaL_loadbuffer(m_pLuaState, pszBuffer, dwSize, pszScriptName);
		KG_PROCESS_ERROR(nRetCode == 0);
	}
	else
	{
        KLuaScriptData* pScriptData     = NULL;
		char            szEnvName[MAX_ENV_NAME_LEN];

        pScriptData = &m_mapScriptData[dwScriptID];

		nRetCode = snprintf(pScriptData->szName, sizeof(pScriptData->szName), "%s", pszScriptName);
        KGLOG_PROCESS_ERROR(nRetCode > 0 && nRetCode < (int)sizeof(pScriptData->szName));

		sprintf(szEnvName, "%u", dwScriptID);

		_MakeEnv(szEnvName);

		AddInteger(dwScriptID, LUA_SCRIPT_ID, dwScriptID);
		
		nRetCode = luaL_loadbuffer(m_pLuaState, pszBuffer, dwSize, pszScriptName);
		KG_PROCESS_ERROR(nRetCode == 0);

		lua_getglobal(m_pLuaState, szEnvName);
		KG_PROCESS_ERROR(lua_istable(m_pLuaState, -1));
		lua_setfenv(m_pLuaState, -2);	
	}

	nRetCode = lua_pcall(m_pLuaState, 0, 0, 0);
	KG_PROCESS_ERROR(nRetCode == 0);


    bResult = true;
Exit0:
	m_dwActiveScript = dwOriginalScriptID;
    if (!bResult)
    {
	    const char* pszErrorMsg = Lua_ValueToString(m_pLuaState, -1);
	    if (pszErrorMsg)
	    {
            KGLogPrintf(KGLOG_ERR, "[Lua] %s", pszErrorMsg);
	    }
    }
	return bResult;
}

int KLuaScriptEx::Include(lua_State* L)
{
    int             nRetCode    = false;
	DWORD           dwScriptID  = 0;
	DWORD           dwSelfID    = 0;
	int             nSize       = 0;
	int             nIndex      = 0;
	const char*     pszFileName = NULL;
	KLuaScriptEx*   pSelf       = NULL;
	KLuaScriptData* pScriptData = NULL;

    nRetCode = Lua_GetTopIndex(L);
	KG_PROCESS_ERROR(nRetCode == 1);

	// 把文件名hash后添加到脚本的_include表中
	pszFileName = Lua_ValueToString(L, 1);
	KG_PROCESS_ERROR(pszFileName);

	lua_pushstring(L, LUA_SCRIPT_THIS);
	lua_gettable(L, LUA_GLOBALSINDEX);

	pSelf = (KLuaScriptEx*)lua_touserdata(L, 2);
	KG_PROCESS_ERROR(pSelf);

	dwSelfID = pSelf->GetActiveScriptID();
	KG_PROCESS_ERROR(dwSelfID);

	pScriptData = pSelf->GetScriptData(dwSelfID);
	KG_PROCESS_ERROR(pScriptData);
	
	dwScriptID = g_FileNameHash(pszFileName);
	KG_PROCESS_ERROR(dwScriptID);

    nRetCode = pSelf->IsScriptExist(dwScriptID);
	if (!nRetCode)
	{
		dwScriptID = pSelf->LoadFromFile(pszFileName);
		KG_PROCESS_ERROR(dwScriptID);
	}

	nSize = (int)pScriptData->vecIncludeScriptID.size();

	for (nIndex = 0; nIndex < nSize; nIndex++)
	{
		if (pScriptData->vecIncludeScriptID[nIndex] == dwScriptID)
			break;
	}
	KG_PROCESS_ERROR(nIndex == nSize); // 脚本没有重复加载;

	// 把目标ID加入Include表
	pScriptData->vecIncludeScriptID.push_back(dwScriptID);

Exit0:
	return 0;
}

void KLuaScriptEx::RegisterFunction(KLuaFunc &LuaFunc)
{
	assert(m_pLuaState);

	lua_register(m_pLuaState, LuaFunc.pszFuncName, LuaFunc.pFunc);
}

void KLuaScriptEx::RegisterFunctions(KLuaFunc Funcs[], int nFuncCount)
{
	assert(m_pLuaState);

	for (int nIndex = 0; nIndex < nFuncCount; nIndex ++)
    {
		lua_register(m_pLuaState, Funcs[nIndex].pszFuncName, Funcs[nIndex].pFunc);
    }
}

void KLuaScriptEx::SafeCallBegin(int* pIndex)
{
	assert(pIndex);
	assert(m_pLuaState);

	*pIndex         = lua_gettop(m_pLuaState);
	m_nParamCount   = 0;
}

void KLuaScriptEx::SafeCallEnd(int nIndex)
{
	assert(m_pLuaState);
	lua_settop(m_pLuaState, nIndex);
	m_nParamCount = 0;
}

// 从堆栈中取值
// 取值顺序是从栈顶往下
BOOL KLuaScriptEx::GetValuesFromStack(const char* pszFormat , ...)
{
    BOOL    bResult     = false;
    BOOL    bRetCode    = false;
	va_list vlist;

	va_start(vlist, pszFormat);

	bRetCode = GetValuesFromStack(pszFormat, vlist);
	KG_PROCESS_ERROR(bRetCode);

	va_end(vlist);

	bResult = true;
Exit0:
	return bResult;
}

BOOL KLuaScriptEx::GetValuesFromStack(const char* pszFormat , va_list vlist)
{
	double* pNumber         = NULL;
	const char** pString    = NULL;
	int* pInteger           = NULL;
	BOOL* pBoolean          = NULL;
    //va_list vlist;
    int nValueNum           = 0;
    int nTopIndex           = 0;
    int nValueCount         = 0;
    int nStackIndex         = 0;
    int nValueIndex         = 0;

	KG_PROCESS_ERROR(m_pLuaState);

	//检测堆栈中参数个数是否足够
	nTopIndex = lua_gettop(m_pLuaState);
	nValueCount = (int)strlen(pszFormat);
	KG_PROCESS_ERROR(nTopIndex >= nValueCount);

	//计算第一个参数在堆栈中的位置
	nStackIndex = nTopIndex - nValueCount + 1;

	//va_start(vlist, pszFormat);     

	nValueIndex = 0;
	while (pszFormat[nValueIndex] != '\0')
	{
		switch(pszFormat[nValueIndex])
		{
		case 'n'://返回值为数值形,Number,此时Lua只传递double形的值
			{
				pNumber = va_arg(vlist, double*);
				KG_PROCESS_ERROR(pNumber);
				KG_PROCESS_ERROR(lua_isnumber(m_pLuaState, nStackIndex));

				*pNumber = lua_tonumber(m_pLuaState, nStackIndex++);
			}
			break;
		case 'd':
			{
				pInteger = va_arg(vlist, int*);
				KG_PROCESS_ERROR(pInteger);
				KG_PROCESS_ERROR(lua_isnumber(m_pLuaState, nStackIndex));

				*pInteger = (int)lua_tonumber(m_pLuaState, nStackIndex++);
			}
			break;
		case 's':
			{
				pString = va_arg(vlist, const char **);
				KG_PROCESS_ERROR(pString);
				KG_PROCESS_ERROR(lua_isstring(m_pLuaState, nStackIndex));

				(*pString) = (const char *)lua_tostring(m_pLuaState, nStackIndex++);
			}
			break;
		case 'b':
			{
				pBoolean = va_arg(vlist, BOOL*);
				KG_PROCESS_ERROR(pBoolean);
				KG_PROCESS_ERROR(lua_isboolean(m_pLuaState, nStackIndex));

				*pBoolean = lua_toboolean(m_pLuaState, nStackIndex++);
			}
		}

		nValueIndex++;	
	}
	//va_end(vlist);

	return TRUE;

Exit0:

	return FALSE;
}

BOOL KLuaScriptEx::IsFuncExist(DWORD dwScriptID, const char* pszFuncName)
{
	BOOL    bResult                 = false;
	DWORD   dwOriginalScriptID      = m_dwActiveScript;
    int     nTest                   = 0;
    int     nTopIndex               = 0;

	assert(pszFuncName);

	m_dwActiveScript = dwScriptID;

	nTest = lua_gettop(m_pLuaState);

	SafeCallBegin(&nTopIndex);

	if (dwScriptID == 0)
	{
		lua_getglobal(m_pLuaState, pszFuncName);
	}
	else
	{
		char szEnvName[MAX_ENV_NAME_LEN];

		sprintf(szEnvName, "%u", dwScriptID);

		lua_getglobal(m_pLuaState, szEnvName);
		if (lua_isnil(m_pLuaState, -1) == 0)
		{
			lua_getfield(m_pLuaState, -1, pszFuncName);
		}
	}
	
	bResult = lua_isfunction(m_pLuaState, lua_gettop(m_pLuaState));

	SafeCallEnd(nTopIndex);

	m_dwActiveScript = dwOriginalScriptID;

	return bResult;
}

void KLuaScriptEx::RegisterConstList(KLuaConstList* pLuaConstList)
{
	BOOL    bRetCode        = false;
	int     nIndex          = 0;
	int     nOriginalIndex  = 0;

	assert(pLuaConstList);
    assert(m_pLuaState);

	while (pLuaConstList[nIndex].pConstList && pLuaConstList[nIndex].pszListName)
	{
		KLuaConst* pConstList = pLuaConstList[nIndex].pConstList;
		
		SafeCallBegin(&nOriginalIndex);

		lua_newtable(m_pLuaState);
		int nConstTable = lua_gettop(m_pLuaState);

		lua_newtable(m_pLuaState);
		int nRealTable = lua_gettop(m_pLuaState);

		// 加入全局表中
		lua_pushstring(m_pLuaState, pLuaConstList[nIndex].pszListName);
		lua_pushvalue(m_pLuaState, nConstTable);
		lua_settable(m_pLuaState, LUA_GLOBALSINDEX);

		int nConstIndex = 0;
		while (pConstList[nConstIndex].pszConstName)
		{
			lua_pushstring(m_pLuaState, pConstList[nConstIndex].pszConstName);
			lua_pushnumber(m_pLuaState, pConstList[nConstIndex].nValue);
			lua_settable(m_pLuaState, nRealTable);

			nConstIndex++;
		}

		// 设置常量表的metatable,防止常量表在脚本中被修改
		lua_newtable(m_pLuaState);
		int nMetaTable = lua_gettop(m_pLuaState);

		lua_pushstring(m_pLuaState, "__index");
		lua_pushvalue(m_pLuaState, nRealTable);
		lua_settable(m_pLuaState, nMetaTable);

		lua_pushstring(m_pLuaState, "__newindex");
		lua_pushcfunction(m_pLuaState, KLuaScriptEx::_NewIndexForConstList);
		lua_settable(m_pLuaState, nMetaTable);

		lua_setmetatable(m_pLuaState, nConstTable);

		SafeCallEnd(nOriginalIndex);

		nIndex++;
	}
} 

BOOL KLuaScriptEx::CallFunction(DWORD dwScriptID, const char* pszFuncName, int nResults)
{
    BOOL    bResult                 = false;
	int     nIndex                  = 0;
	DWORD   dwOriginalScriptID      = m_dwActiveScript;
    int     nParam                  = 0;
    int     nRetCode                = 0;

    assert(pszFuncName);
	assert(m_pLuaState);
	assert(m_nParamCount >= 0);

	nParam = lua_gettop(m_pLuaState);

	m_dwActiveScript = dwScriptID;

	// 在堆栈中加入需要调用的函数名
	if (dwScriptID == 0)
	{
		lua_getglobal(m_pLuaState, pszFuncName);
	}
	else
	{
		char szEnvName[MAX_ENV_NAME_LEN];

		sprintf(szEnvName, "%u", dwScriptID);

		lua_getglobal(m_pLuaState, szEnvName);
		if (lua_isnil(m_pLuaState, -1) == 0)
		{
			lua_getfield(m_pLuaState, -1, pszFuncName);
		}

		// 删除原先的表
		lua_insert(m_pLuaState, -2);
		lua_pop(m_pLuaState, 1);
	}

	// 把函数名插到参数前
	lua_insert(m_pLuaState, -(m_nParamCount + 1));

	nRetCode = lua_pcall(m_pLuaState, m_nParamCount, nResults, 0);
	KG_PROCESS_ERROR(nRetCode == 0);

    bResult = true;
Exit0:
	m_dwActiveScript = dwOriginalScriptID;
    if (!bResult)
    {
	    const char* pszErrorMsg = lua_tostring(m_pLuaState, -1);
	    if (pszErrorMsg)
	    {
            KGLogPrintf(KGLOG_ERR, "[Lua] Failed to call function %s: %s\n", pszFuncName, pszErrorMsg);
	    }
    }
	return bResult;
}

void KLuaScriptEx::AddParamCount()
{
	m_nParamCount++;
}

BOOL KLuaScriptEx::AddGlobalInteger(const char* pszVarName, int nValue)
{
	assert(pszVarName);

	lua_pushstring(m_pLuaState, pszVarName);
	lua_pushnumber(m_pLuaState, nValue);
	lua_settable(m_pLuaState, LUA_GLOBALSINDEX);

    return true;
}

BOOL KLuaScriptEx::AddGlobalString(const char* pszVarName, const char* pszValue)
{
	assert(pszVarName);
	assert(pszValue);

	lua_pushstring(m_pLuaState, pszVarName);
	lua_pushstring(m_pLuaState, pszValue);
	lua_settable(m_pLuaState, LUA_GLOBALSINDEX);

	return true;
}

BOOL KLuaScriptEx::AddInteger(DWORD dwScriptID, const char* pszVarName, int nValue)
{
	int nTopIndex = 0;

	assert(pszVarName);

	if (dwScriptID == 0)
	{
		AddGlobalInteger(pszVarName, nValue);
	}
	else
	{
	    char szEnvName[MAX_ENV_NAME_LEN];

		sprintf(szEnvName, "%u", dwScriptID);

		lua_getglobal(m_pLuaState, szEnvName);
		nTopIndex = Lua_GetTopIndex(m_pLuaState);
		
		if (lua_istable(m_pLuaState, -1))
		{
			lua_pushstring(m_pLuaState, pszVarName);
			lua_pushnumber(m_pLuaState, nValue);
			lua_settable(m_pLuaState, nTopIndex);
		}

		lua_pop(m_pLuaState, 1);
	}

	return true;
}

BOOL KLuaScriptEx::AddString(DWORD dwScriptID, const char* pszValueName, const char* pszValue)
{
	int nTopIndex = 0;

	assert(pszValueName);

	if (dwScriptID == 0)
	{
		AddGlobalString(pszValueName, pszValue);
	}
	else
	{
	    char szEnvName[MAX_ENV_NAME_LEN];

		sprintf(szEnvName, "%u", dwScriptID);

		lua_getglobal(m_pLuaState, szEnvName);
		nTopIndex = Lua_GetTopIndex(m_pLuaState);

		if (lua_istable(m_pLuaState, -1))
		{
			lua_pushstring(m_pLuaState, pszValueName);
			lua_pushstring(m_pLuaState, pszValue);
			lua_settable(m_pLuaState, nTopIndex);
		}

		lua_pop(m_pLuaState, 1);
	}
	
	return true;
}

lua_State* KLuaScriptEx::GetLuaState(void)
{
	return m_pLuaState;
}

BOOL KLuaScriptEx::IsScriptExist(DWORD dwScriptID)
{
	SCRIPT_DATA_MAP::iterator it = m_mapScriptData.find(dwScriptID);
	if (it != m_mapScriptData.end())
    {
        return true;
    }

	return false;
}

DWORD KLuaScriptEx::GetActiveScriptID()
{
	return m_dwActiveScript;
}

KLuaScriptData* KLuaScriptEx::GetScriptData(DWORD dwScriptID)
{
	SCRIPT_DATA_MAP::iterator it = m_mapScriptData.find(dwScriptID);
	if (it != m_mapScriptData.end())
	{
		return &it->second;
	}

	return NULL;
}

int KLuaScriptEx::_NewIndexForConstList(lua_State* L)
{
	const char* pszKey  = lua_tostring(L, 2);

	if (pszKey)
    {
        KGLogPrintf(KGLOG_ERR, "[Lua] Try to set const value: %s\n", pszKey);
    }

	return 0;
}

int KLuaScriptEx::_IndexForEnv(lua_State* L)
{
    int             nResult     = 0;
	BOOL            bRetCode    = false;
	DWORD           dwScriptID  = 0;
    KLuaScriptEx*   pSelf       = NULL;
	const char*     pszKey      = lua_tostring(L, 2);

	assert(pszKey);

	lua_pushstring(L, LUA_SCRIPT_THIS);
	lua_gettable(L, LUA_GLOBALSINDEX);

	pSelf = (KLuaScriptEx*)lua_touserdata(L, -1);
	KGLOG_PROCESS_ERROR(pSelf);

	dwScriptID = pSelf->GetActiveScriptID();

	bRetCode = pSelf->_GetVarInInclude(dwScriptID, pszKey);
	if (!bRetCode)
	{
		lua_getglobal(L, pszKey);
	}
	
	nResult = 1;
Exit0:
	return nResult;
}

BOOL KLuaScriptEx::_GetVarInInclude(DWORD dwScriptID, const char* pszValueName)
{
    BOOL            bResult         = false;
	BOOL            bRetCode        = false;
	KLuaScriptData* pScriptData     = NULL;
	int             nIndex          = 0;
	int             nSize           = 0;
	char            szEnvName[MAX_ENV_NAME_LEN];
	
	assert(pszValueName);

	pScriptData = GetScriptData(dwScriptID);
	KG_PROCESS_ERROR(pScriptData);

	nSize = (int)pScriptData->vecIncludeScriptID.size();

	// 为了让Include的文件看起来是可以覆盖的,这里倒过来遍历include表,找到直接跳出
	for (nIndex = nSize - 1; nIndex >= 0; nIndex--)
	{
		DWORD dwTargetScriptID = pScriptData->vecIncludeScriptID[nIndex];
		if (dwTargetScriptID == 0)
			continue;
		
		sprintf(szEnvName, "%u", dwTargetScriptID);

		lua_getglobal(m_pLuaState, szEnvName);

		// 可能目标脚本还没加载,所以环境可能取不到
		if (lua_istable(m_pLuaState, -1) == 0)
			continue;

		lua_pushstring(m_pLuaState, pszValueName);
		lua_rawget(m_pLuaState, -2);
		lua_remove(m_pLuaState, -2); // 删去EnvTab;

		if (lua_isnil(m_pLuaState, -1))
		{
			lua_remove(m_pLuaState, -1);

			bRetCode = _GetVarInInclude(dwTargetScriptID, pszValueName);
			if (!bRetCode)
				continue; // 还是没找到
		}

		break;
	}

	KG_PROCESS_ERROR(nIndex >= 0); // nIndex>=0表示找到,中途跳出
	
	bResult = true;
Exit0:
	return bResult;
}

// 生成环境
BOOL KLuaScriptEx::_MakeEnv(const char* szEnvName)
{
	BOOL bResult = FALSE;
	int nTopIndex = 0;
	int nMetaTableIndex = 0;

	KG_PROCESS_ERROR(szEnvName);

	lua_newtable(m_pLuaState);
	nTopIndex = lua_gettop(m_pLuaState);
	nMetaTableIndex = nTopIndex;

	lua_newtable(m_pLuaState);
	nTopIndex = lua_gettop(m_pLuaState);
	lua_pushstring(m_pLuaState, "__index");
	//lua_getglobal(m_LuaState, "_G");
	lua_pushcfunction(m_pLuaState, KLuaScriptEx::_IndexForEnv);

	//生成metatable表
	lua_settable(m_pLuaState, nTopIndex);

	//设置metatable表
	lua_setmetatable(m_pLuaState, nMetaTableIndex); 

	//保存环境到全局table
	lua_setglobal(m_pLuaState, szEnvName);

	bResult = TRUE;
Exit0:
	return bResult; 
}

void KLuaScriptEx::Release()
{
	Destroy();
    delete this;
}

ILuaScriptEx* CreateLuaInterface()
{
    ILuaScriptEx*   piResult    = NULL;
    BOOL            bRetCode    = false;
	KLuaScriptEx*   pLua        = NULL;

    pLua = new KLuaScriptEx;
    KGLOG_PROCESS_ERROR(pLua);

    bRetCode = pLua->Create();
    KGLOG_PROCESS_ERROR(bRetCode);

    piResult = (ILuaScriptEx*)pLua;
Exit0:
    if (piResult == NULL)
    {
        KG_DELETE(pLua);
    }
    return piResult;
}

#endif	//LUA_V_5
