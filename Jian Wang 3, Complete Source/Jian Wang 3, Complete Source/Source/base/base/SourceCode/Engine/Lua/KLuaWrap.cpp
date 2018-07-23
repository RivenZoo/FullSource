/********************************************************************
	created:	2008/12/09
	created:	9:12:2008   11:12
	filename: 	KLuaWrap.cpp
	author:		lizhi
	
	purpose:	
*********************************************************************/
#include "Precompile.h"
#include <string>
#ifdef WIN32
#include <crtdbg.h>
#endif
#include "File.h"
#include "KGLog.h"
#include "KLuaWrap.h"

// memory pool const define MEM_CHUNK_SIZE and MEM_POOL_MAX_ALLOC % MEM_ALIGN_SIZE must == 0
const unsigned int MEM_CHUNK_SIZE		= 16000;	// default mem chunk size (a little < page size linux = 16k / windows = 4k)
const unsigned int MEM_POOL_MAX_ALLOC	= 4096;		// mempool process max alloc size
const unsigned int MEM_ALIGN_SIZE		= 8;
const unsigned int MEM_BUCKET_COUNT		= (MEM_POOL_MAX_ALLOC / MEM_ALIGN_SIZE);

class LMemChunk
{
public:
	LMemChunk();
	~LMemChunk();

	size_t		available_size() { return m_AvailableSize; }
	void*		allocate(size_t n);
private:
	void		_free_all_chunk();
	void		_chunk_alloc();
private:
	struct ChunkNode
	{
		ChunkNode *pNext;
	};
	char*			m_pChunkList;
	size_t			m_AvailableSize;
};

LMemChunk::LMemChunk()
	:m_pChunkList(NULL)
	,m_AvailableSize(0)
{
}

LMemChunk::~LMemChunk()
{
	_free_all_chunk();
}

void LMemChunk::_free_all_chunk()
{
	ChunkNode *pListNode = (ChunkNode*)m_pChunkList;
	while (pListNode)
	{
		ChunkNode *pCurrent = pListNode;
		pListNode = pListNode->pNext;
		free(pCurrent);
	}
	m_pChunkList = NULL;
}

void LMemChunk::_chunk_alloc()
{	
	ChunkNode *pNode = (ChunkNode*)malloc(sizeof(ChunkNode) + MEM_CHUNK_SIZE);
	pNode->pNext = (ChunkNode*)m_pChunkList;
	m_pChunkList = (char*)pNode;
	
	m_AvailableSize = MEM_CHUNK_SIZE;
}

void *LMemChunk::allocate(size_t n)
{
	if (n > m_AvailableSize)
		_chunk_alloc();

	size_t offset = sizeof(ChunkNode) + MEM_CHUNK_SIZE - m_AvailableSize;
	m_AvailableSize -= n;
	return (char*)m_pChunkList + offset;
}

#define MEM_POOL_ALIGN_UP(x)			(((x) + MEM_ALIGN_SIZE - 1) & ~(MEM_ALIGN_SIZE - 1))
#define MEM_POOL_FIND_BUCKET_INDEX(x)	(((x) / MEM_ALIGN_SIZE) - 1)
#define LMEMORY_POOL_ALLOC_INFO

class LMemPool
{
public:
	LMemPool();
	~LMemPool();

	void*	allocate(size_t n);
	void	deallocate(void *p, size_t n);
	void*	reallocate(void *p, size_t new_n, size_t old_n);

	LMemAllocInfo GetAllocInfo();

private:
	struct mem_free_list
	{
		mem_free_list *next;
	};
	mem_free_list	*m_MemBucket[MEM_BUCKET_COUNT];
	unsigned int	m_MemBucketAllocCount[MEM_BUCKET_COUNT];
	LMemChunk		m_MemChunk;
#ifdef LMEMORY_POOL_ALLOC_INFO
	LMemAllocInfo	m_AllocInfo;
#endif
};

LMemAllocInfo LMemPool::GetAllocInfo()
{
#ifdef LMEMORY_POOL_ALLOC_INFO
	return m_AllocInfo;
#else
	LMemAllocInfo tmp;
	memset(&tmp, 0, sizeof(tmp));
	return tmp;
#endif
}

LMemPool::LMemPool()
{
	memset(m_MemBucket, 0, sizeof(m_MemBucket));
	memset(m_MemBucketAllocCount, 0, sizeof(m_MemBucketAllocCount));
#ifdef LMEMORY_POOL_ALLOC_INFO
	memset(&m_AllocInfo, 0, sizeof(m_AllocInfo));
#endif
}

LMemPool::~LMemPool()
{
}

void* LMemPool::allocate(size_t n)
{
	assert(n > 0);
	if (n > MEM_POOL_MAX_ALLOC)
	{
#ifdef LMEMORY_POOL_ALLOC_INFO
		m_AllocInfo.SystemMemSize += n;
#endif
		return malloc(n);
	}

	n = MEM_POOL_ALIGN_UP(n);
	int BucketIdx = MEM_POOL_FIND_BUCKET_INDEX(n);
	if (m_MemBucket[BucketIdx])		// 在内存桶中有缓存的内存
	{
#ifdef LMEMORY_POOL_ALLOC_INFO
		m_AllocInfo.UseMemSize += n;
#endif
		mem_free_list *p = m_MemBucket[BucketIdx];
		m_MemBucket[BucketIdx] = p->next;
		return (void*)p;
	}

	// 桶中没有缓存的内存
	size_t ChunkSize = m_MemChunk.available_size();
	if (ChunkSize >= n)	// 内存块中有足够的内存
	{
#ifdef LMEMORY_POOL_ALLOC_INFO
		m_AllocInfo.UseMemSize += n;
#endif
		++m_MemBucketAllocCount[BucketIdx];
		return m_MemChunk.allocate(n);
	}

	// 内存块中还有剩余的内存，但是不够这次分配
	// 让余量的内存还有些"利用价值"
	if (ChunkSize > 0)
	{
		int ChunkBucketIdx = MEM_POOL_FIND_BUCKET_INDEX(ChunkSize);
		mem_free_list *p = (mem_free_list*)m_MemChunk.allocate(ChunkSize);
		p->next = m_MemBucket[ChunkBucketIdx];
		m_MemBucket[ChunkBucketIdx] = p;
		++m_MemBucketAllocCount[ChunkBucketIdx];
	}

#ifdef LMEMORY_POOL_ALLOC_INFO
	m_AllocInfo.UseMemSize += n;
	m_AllocInfo.AllocMemSize += MEM_CHUNK_SIZE;
#endif
	++m_MemBucketAllocCount[BucketIdx];
	return m_MemChunk.allocate(n);
}

void LMemPool::deallocate(void *p, size_t n)
{
	assert(n > 0);
	if (n > MEM_POOL_MAX_ALLOC)
	{
#ifdef LMEMORY_POOL_ALLOC_INFO
		m_AllocInfo.SystemMemSize -= n;
#endif
		free(p);
		return;
	}

	n = MEM_POOL_ALIGN_UP(n);
#ifdef LMEMORY_POOL_ALLOC_INFO
	m_AllocInfo.UseMemSize -= n;
#endif

	int BucketIdx = MEM_POOL_FIND_BUCKET_INDEX(n);
	((mem_free_list*)p)->next = m_MemBucket[BucketIdx];
	m_MemBucket[BucketIdx] = (mem_free_list*)p;
}

void* LMemPool::reallocate(void *p, size_t new_n, size_t old_n)
{
#ifdef LMEMORY_POOL_ALLOC_INFO
	++m_AllocInfo.ReallocCount;
#endif
	if (new_n <= old_n ||
		((MEM_POOL_ALIGN_UP(new_n) == MEM_POOL_ALIGN_UP(old_n)) && (old_n <= MEM_POOL_MAX_ALLOC)))
	{
#ifdef LMEMORY_POOL_ALLOC_INFO
		++m_AllocInfo.ReallocHitCount;
#endif
		return p;
	}

	void *pNew = allocate(new_n);
	::memmove(pNew, p, old_n);		// new_n > old_n
	deallocate(p, old_n);
	return pNew;
}

////////////////////////////////////////////////////////////////////

#define KD_N_BASE_CALL_STACK	512		// 默认C使用的堆栈大小

KLuaWrap::KLuaWrap()
:m_L(NULL)
,m_uMemSize(0)
{
	m_ScriptPackagePath[0] = 0;
	m_pMemPool = new LMemPool();
}

KLuaWrap::~KLuaWrap()
{
	_Exit();
	delete m_pMemPool;
}

bool KLuaWrap::Init(std::string *pReserveGVar, size_t GVarCount, const char *PackagePath /*= NULL*/)
{
	char path[MAX_PATH];
	g_GetRootPath(path);

	if (PackagePath)
	{
#ifdef WIN32
		strcat(path, "\\");
#else
		strcat(path, "/");
#endif
		strcat(path, PackagePath);
	}
	else
	{
#ifdef WIN32
		strcat(path, "\\script\\");
#else
		strcat(path, "/script/");
#endif
	}

	strncpy(m_ScriptPackagePath, path, sizeof(m_ScriptPackagePath));
	m_ScriptPackagePath[sizeof(m_ScriptPackagePath) - 1] = 0;

	_Exit();
	m_L	= lua_newstate(_Alloc_Fun, this);

	KS_CHECK_BOOL(m_L);
	KS_CHECK_BOOL(lua_checkstack(m_L, KD_N_BASE_CALL_STACK));

	luaL_openlibs(m_L);

	if (pReserveGVar)
	{
		lua_tinker::table tReserveGVar(m_L);
		for (size_t c = 0; c < GVarCount; ++c)
		{
			tReserveGVar.set(c + 1, pReserveGVar[c].c_str());
		}
		lua_tinker::set(m_L, "_RESERVE_G_VAR_", tReserveGVar);
	}
	else
	{
		lua_tinker::table tReserveGVar(m_L);
		lua_tinker::set(m_L, "_RESERVE_G_VAR_", tReserveGVar);
	}
	return true;

KS_EXIT:
	return false;
}

void KLuaWrap::RegisterFunctions(const TLua_Funcs *pFuncs, size_t size)
{
	assert(m_L);
	for (size_t i = 0; i < size; ++i)
	{
		lua_pushstring(m_L, pFuncs[i].name);
		lua_pushcfunction(m_L, pFuncs[i].func);
		lua_settable(m_L, LUA_GLOBALSINDEX);
	}
}

int KLuaWrap::SafeCallBegin()
{
	return lua_gettop(m_L);
}

int KLuaWrap::CallFunction(const char *pTable, const char *pFunc, const char *pFormat /*= ""*/, ...)
{
	if (!(pFunc && pFunc[0] && pFormat))
		return 0;

	int ret = 0;
	lua_pushcclosure(m_L, lua_tinker::on_error, 0);
	int ErrFunc = lua_gettop(m_L);
	if (pTable && pTable[0])
	{
		// get table
		lua_getglobal(m_L, pTable);
		if (lua_istable(m_L, -1))
		{
			// get the function
			lua_getfield(m_L, -1, pFunc);
			if (!lua_isfunction(m_L, -1))
			{
				lua_getglobal(m_L, CURRENT_SCRIPT_FILE);
				const char *pCurrentFile = (const char*)lua_tostring(m_L, -1);
				if (pCurrentFile)
					lua_tinker::print_error(m_L, "attempt to call '%s' (not a function) file=%s, env=%s", pFunc, pCurrentFile, pTable);
				else
					lua_tinker::print_error(m_L, "attempt to call '%s' (not a function) env=%s", pFunc, pTable);
			}
			else
			{
				lua_getglobal(m_L, pTable);
				lua_setfenv(m_L, -2);
				// call the function
				va_list vl;
				va_start(vl, pFormat);
				ret = _Call(ErrFunc, pFormat, vl);
				va_end(vl);
			}
		}
	}
	else
	{
		lua_getglobal(m_L, pFunc);
		if (!lua_isfunction(m_L, -1))
		{
			lua_getglobal(m_L, CURRENT_SCRIPT_FILE);
			const char *pCurrentFile = (const char*)lua_tostring(m_L, -1);
			if (pCurrentFile)
				lua_tinker::print_error(m_L, "attempt to call '%s' (not a function) file=%s", pFunc, pCurrentFile);
			else
				lua_tinker::print_error(m_L, "attempt to call '%s' (not a function)", pFunc);
		}
		else
		{
			// call the function
			va_list vl;
			va_start(vl, pFormat);
			ret = _Call(ErrFunc, pFormat, vl);
			va_end(vl);
		}
	}
	return ret;
}

int KLuaWrap::CallFunctionV(const char *pTable, const char *pFunc, const char *pFormat, va_list vl)
{
	if (!(pFunc && pFunc[0]))
		return 0;

	int ret = 0;
	lua_pushcclosure(m_L, lua_tinker::on_error, 0);
	int ErrFunc = lua_gettop(m_L);
	if (pTable && pTable[0])
	{
		// get table
		lua_getglobal(m_L, pTable);
		if (lua_istable(m_L, -1))
		{
			// get the function
			lua_getfield(m_L, -1, pFunc);
			if (!lua_isfunction(m_L, -1))
			{
				lua_getglobal(m_L, CURRENT_SCRIPT_FILE);
				const char *pCurrentFile = (const char*)lua_tostring(m_L, -1);
				if (pCurrentFile)
					lua_tinker::print_error(m_L, "attempt to call '%s' (not a function) file=%s, env=%s", pFunc, pCurrentFile, pTable);
				else
					lua_tinker::print_error(m_L, "attempt to call '%s' (not a function) env=%s", pFunc, pTable);
			}
			else
			{
				lua_getglobal(m_L, pTable);
				lua_setfenv(m_L, -2);
				// call the function
				ret = _Call(ErrFunc, pFormat, vl);
			}
		}
	}
	else
	{
		lua_getglobal(m_L, pFunc);
		if (!lua_isfunction(m_L, -1))
		{
			lua_getglobal(m_L, CURRENT_SCRIPT_FILE);
			const char *pCurrentFile = (const char*)lua_tostring(m_L, -1);
			if (pCurrentFile)
				lua_tinker::print_error(m_L, "attempt to call '%s' (not a function) file=%s", pFunc, pCurrentFile);
			else
				lua_tinker::print_error(m_L, "attempt to call '%s' (not a function)", pFunc);
		}
		else
		{
			ret = _Call(ErrFunc, pFormat, vl);
		}
	}
	return ret;
}

void KLuaWrap::SafeCallEnd(int TopIndex)
{
	lua_settop(m_L, TopIndex);
}

bool KLuaWrap::DoScriptFile(const char *ScriptFile, const char *EnvName /*= NULL*/)
{
	bool ret = false;
	assert(m_L);
	if (!(ScriptFile && ScriptFile[0]))
		return false;

	IFile*	pFile = NULL;
	char*	pBuffer = NULL;
	unsigned int	size;

	if ((pFile = g_OpenFile(ScriptFile)) == NULL)
	{
		printf("%s is not exist!\n", ScriptFile);
		KGLogPrintf(KGLOG_WARNING, "[Lua] %s is not exist!\n", ScriptFile);
		return false;
	}

	size = pFile->Size();
	pBuffer = (char*)malloc(size + 1024);
	if (pBuffer)
	{
		char tmp[128];
		int pos = 0;
		int tmpLen = sprintf(tmp, "package.path = \"%s?.lua\"", m_ScriptPackagePath);
#ifdef WIN32
		for (int i = 0; i < tmpLen; ++i)
		{
			pBuffer[pos++] = tmp[i];
			if (tmp[i] == '\\')
			{
				pBuffer[pos++] = '\\';
			}
		}
#endif
		if (EnvName && EnvName[0])
			pos += sprintf(pBuffer + pos, "%s={} setmetatable(%s,{__index=_G,__newindex=function(t,i,v)for _,r in pairs(_RESERVE_G_VAR_)do if i==r then _G[i] = v return end end rawset(t,i,v)end}) setfenv(1,%s)", EnvName, EnvName, EnvName);

		if (pFile->Read(pBuffer + pos, size) == size)
		{
			ret = lua_tinker::dobuffer(m_L, pBuffer, size + pos, ScriptFile);
			if (ret && EnvName && EnvName[0])
			{
				lua_getglobal(m_L, EnvName);
				lua_pushstring(m_L, "CURRENT_SCRIPT_FILE");
				lua_pushstring(m_L, ScriptFile);
				lua_settable(m_L, -3);
				lua_pop(m_L, 1);
			}
		}
		free(pBuffer);
		pBuffer = NULL;
	}

	pFile->Release();
	pFile = NULL;
	return ret;
}

bool KLuaWrap::DoBuffer(const char *pBuffer, size_t size, const char *EnvName /*= NULL*/)
{
	bool ret = false;
	assert(m_L);
	if (!(pBuffer && pBuffer[0]))
		return false;

	if (EnvName && EnvName[0])
	{
		char *p = (char*)malloc(size + 1024);
		if (p)
		{
			char tmp[128];
			int pos = 0;
			int tmpLen = sprintf(tmp, "package.path = \"%s?.lua\"", m_ScriptPackagePath);
#ifdef WIN32
			for (int i = 0; i < tmpLen; ++i)
			{
				p[pos++] = tmp[i];
				if (tmp[i] == '\\')
				{
					p[pos++] = '\\';
				}
			}
#endif
			pos += sprintf(p + pos, "%s={} setmetatable(%s,{__index=_G,__newindex=function(t,i,v)for _,r in pairs(_RESERVE_G_VAR_)do if i==r then _G[i] = v return end end rawset(t,i,v)end}) setfenv(1,%s)", EnvName, EnvName, EnvName);
			memcpy(p + pos, pBuffer, size);
			ret = lua_tinker::dobuffer(m_L, p, size + pos, "KLuaWrap::DoBuffer");
			free(p);
			p = NULL;
		}
	}
	else
	{
		ret = lua_tinker::dobuffer(m_L, pBuffer, size, "KLuaWrap::DoBuffer");
	}
	return ret;
}

int KLuaWrap::_Call(int ErrFunc, const char *pFormat, va_list vl)
{
	int Args, Rets;			// number of arguments and results
	Args = 0;
	// push arguments
	while (*pFormat)
	{
		switch (*pFormat++)
		{
		case 'f':	// double argument
			lua_pushnumber(m_L, va_arg(vl, double));
			break;
		case 'd':	// int argument
			lua_pushnumber(m_L, va_arg(vl, int));
			break;
		case 's':	// string argument
			lua_pushstring(m_L, va_arg(vl, char *));
			break;
		case '>':	// result
			goto endwhile;
		default:
			lua_tinker::print_error(m_L, "invalid option (%c)", *(pFormat - 1));
		}
		Args++;
		luaL_checkstack(m_L, 1, "too many arguments");
	}
endwhile:
	// do the call
	Rets = (int)strlen(pFormat);	// number of expected results

	if (lua_pcall(m_L, Args, Rets, ErrFunc) != 0)
		return 0;
	// retrieve results
	Rets = -Rets;		// stack index of first result
	while (*pFormat)
	{
		switch (*pFormat++)
		{
		case 'f':	// double result
			if (lua_type(m_L, Rets) != LUA_TNUMBER)
			{
				if (m_CallRetTypeAlert)
					lua_tinker::print_error(m_L, "wrong result type");
				return 0;
			}
			*va_arg(vl, double*) = lua_tonumber(m_L, Rets);
			break;
		case 'd':	// int result
			if (lua_type(m_L, Rets) != LUA_TNUMBER)
			{
				if (m_CallRetTypeAlert)
					lua_tinker::print_error(m_L, "wrong result type");
				return 0;
			}
			*va_arg(vl, int*) = (int)lua_tonumber(m_L, Rets);
			break;
		case 's':	// string result
			if (lua_type(m_L, Rets) != LUA_TSTRING)
			{
				if (m_CallRetTypeAlert)
					lua_tinker::print_error(m_L, "wrong result type");
				return 0;
			}
			*va_arg(vl, const char**) = (const char*)lua_tostring(m_L, Rets);
			break;
		case 'v':// uncertain result type
			break;
		default:
			lua_tinker::print_error(m_L, "invalid option (%c)", *(pFormat - 1));
			return 0;
		}
		Rets++;
	}
	return 1;
}

void KLuaWrap::_Exit()
{
	m_CallRetTypeAlert = true;
	if (m_L)
	{
		lua_close(m_L);
		m_L = NULL;
	}
}

void* KLuaWrap::_Alloc_Fun(void *pScript, void *pMem, size_t nOldSize, size_t nNewSize)
{
	LPVOID pRet	= NULL;
	KLuaWrap* pcScript	= (KLuaWrap*)pScript;
#ifdef WIN32
	if (nNewSize == 0)
	{
		if (pMem)
			pcScript->m_pMemPool->deallocate(pMem, nOldSize);
	}
	else
	{
		if (pMem)
			pRet = pcScript->m_pMemPool->reallocate(pMem, nNewSize, nOldSize);
		else
			pRet = pcScript->m_pMemPool->allocate(nNewSize);
		assert(pRet);
	}
#else
	if (nNewSize == 0)
	{
		if (pMem)
			free(pMem);
	}
	else
	{
		if (pMem)
			pRet = realloc(pMem, nNewSize);
		else
			pRet = malloc(nNewSize);
	}
#endif
	pcScript->m_uMemSize += (nNewSize - nOldSize);
	return pRet;
}

LMemAllocInfo KLuaWrap::GetMemAllocInfo()
{
	return m_pMemPool->GetAllocInfo();
}

void KLuaWrap::LoadJitOpt()
{
	IFile*	pFile = NULL;

	if ((pFile = g_OpenFile("\\script\\lib\\jit\\opt.lua")) == NULL)
	{
		lua_tinker::print_error(m_L, "\\script\\lib\\jit\\opt.lua is not exist!\n");
		return;
	}
	if (luaL_loadbuffer(m_L, (const char*)pFile->GetBuffer(), pFile->Size(), "load jit opt"))
	{
		lua_tinker::print_error(m_L, "%s", lua_tostring(m_L, -1));
		lua_pop(m_L, 1);
		return;
	}
	pFile->Release();

	if ((pFile = g_OpenFile("\\script\\lib\\jit\\opt_inline.lua")) == NULL)
	{
		lua_tinker::print_error(m_L, "\\script\\lib\\jit\\opt_inline.lua is not exist!\n");
		return;
	}
	if (luaL_loadbuffer(m_L, (const char*)pFile->GetBuffer(), pFile->Size(), "load jit opt_inline"))
	{
		lua_tinker::print_error(m_L, "%s", lua_tostring(m_L, -1));
		lua_pop(m_L, 1);
		return;
	}
	pFile->Release();

	lua_getglobal(m_L, "package");
	lua_getfield(m_L, -1, "preload");
	lua_insert(m_L, 1);
	lua_pop(m_L, 1);

	lua_setfield(m_L, 1, "jit.opt_inline");
	lua_setfield(m_L, 1, "jit.opt");

	lua_pop(m_L, 1);
}
