//---------------------------------------------------------------------------
// Sword3 Engine (c) 1999-2004 by Kingsoft
// Date:	2001-9-13 10:33:29
// Code:	Romandou
//---------------------------------------------------------------------------
#include "Precompile.h"

#ifndef LUA_V_5

#include "Debug.h"
#include "File.h"
#include "KLuaScript.h"
#include <stdarg.h>
#ifdef __linux
	#include <unistd.h>
#endif

char g_szRunningScript[256];
char g_szRunningFunction[256];

//Added by AQ for Debugger, 2004.11.15
#ifdef LUA_DEBUG
//#include "KFilePath.h"
#define MAX_VARIABLE	256

//调试命令
typedef enum
{
	DBC_NONE = 0,			//无命令，但处于绑定状态，此时会死循环等待命令
	DBC_CONTINUE,			//单步执行下一行脚本代码
	DBC_GET_VAR,			//获取变量名称和数值
	DBC_SET_LOCAL_VAR,		//修改局部变量
	DBC_SET_GLOBAL_VAR,		//修改全局变量
	DBC_RELOAD_SCRIPT,		//重新载入脚本

	DBC_INACTIVE = 0xFEDC	//未绑定
}DEBUG_COMMAND;

//调试消息结构	调试器->脚本虚拟机
typedef struct 
{
	char	szFlag[4];		//绑定时的定位标志"LDMS"
	DWORD	dwCommand;		//调试指令
	DWORD	dwParam1;		//整数参数1
	DWORD	dwParam2;		
	DWORD	dwParam3;
	DWORD	dwParam4;
	char	szParam1[256];	//字符串参数1
	char	szParam2[256];
}DEBUG_MESSAGE;

//调试信息结构	脚本虚拟机->调试器
typedef struct 
{
	char	szFlag[4];		//绑定时的定位标志"LDIS"
	DWORD	dwThis;			//当前KLuaScript的this指针
	DWORD	dwLineCount;	//当前行号
	DWORD	dwBreakCount;	//回调函数执行次数
	DWORD	dwErrorCount;	//错误次数
	char*	lpszScriptFileName;		//脚本文件名指针
	char*	lpszScriptFuncName;		//脚本函数名指针
	DWORD	dwVarCount;		//变量查询次数
	DWORD	dwGlobalTotal;	//全局变量个数
	DWORD	dwLocalTotal;	//局部变量个数
	char	VarNames[MAX_VARIABLE][32];		//变量名称
	char	VarTypes[MAX_VARIABLE];			//变量类型
	DWORD	VarIntValues[MAX_VARIABLE];		//变量整数值
	char	VarStrValues[MAX_VARIABLE][256];//变量字符串值
	char	szErrorMsg[256];
}DEBUG_INFO;

static DEBUG_MESSAGE DebugMessage = {'L', 'D', 'M', 'S', DBC_INACTIVE, 0, 0, 0, 0, ""};
static DEBUG_INFO DebugInfo = {'L', 'D', 'I', 'S', 0, 0, 0, 0, 0, 0, 0};

//脚本执行每行代码前的回调函数
void KLuaScript::LuaProcessDebugInfo(Lua_State* L, lua_Debug* ar)
{
	BOOL	bFinished = FALSE;

	//获取源代码行号
	DebugInfo.dwLineCount = ar->currentline;
	//回调次数加一
	DebugInfo.dwBreakCount++;
	while (!bFinished)
	{
		switch (DebugMessage.dwCommand)
		{
		case DBC_NONE:
			{
				break;
			}
		case DBC_CONTINUE:
			{
				bFinished = TRUE;
				DebugMessage.dwCommand = DBC_NONE;
				break;
			}
		case DBC_GET_VAR:
			{
				//LUA的调试信息结构
				lua_Debug	ld;

				DebugInfo.dwGlobalTotal = 0;
				DebugInfo.dwLocalTotal = 0;

				//取堆栈信息和函数信息
				if (lua_getstack(L, 0, &ld) && lua_getinfo(L, "flnSu", &ld))
				{
					int nIndex = 0;
					//取全局变量名称和值
					//ld._func->value.i->func->f.l 中为当前函数相关信息
					for (int i = 0; i < ld._func->value.i->func->f.l->nkstr; i++)					
					{
						lua_getglobal(L, (char*)&(ld._func->value.i->func->f.l->kstr[i]->str));
						//该函数的返回值是全局函数的值，在LUA的堆栈中
						//所以设定取栈顶元素
						int nStackPos = -1;
						switch (lua_type(L, nStackPos))
						{
						case LUA_TNONE:
							{
								break;
							}
						case LUA_TUSERDATA:
							{
								strncpy(DebugInfo.VarNames[nIndex], 
									(char*)&(ld._func->value.i->func->f.l->kstr[i]->str), 31);
								DebugInfo.VarNames[nIndex][31] = 0;
								DebugInfo.VarTypes[nIndex] = LUA_TUSERDATA;
								nIndex++;
								break;
							}
						case LUA_TNIL:
							{
								break;
							}
						case LUA_TNUMBER:
							{
								strncpy(DebugInfo.VarNames[nIndex], 
									(char*)&(ld._func->value.i->func->f.l->kstr[i]->str), 31);
								DebugInfo.VarNames[nIndex][31] = 0;
								DebugInfo.VarTypes[nIndex] = LUA_TNUMBER;
								DebugInfo.VarIntValues[nIndex] = (DWORD)lua_tonumber(L, nStackPos);
								nIndex++;
								break;
							}
						case LUA_TSTRING:
							{
								strncpy(DebugInfo.VarNames[nIndex], 
									(char*)&(ld._func->value.i->func->f.l->kstr[i]->str), 31);
								DebugInfo.VarNames[nIndex][31] = 0;
								DebugInfo.VarTypes[nIndex] = LUA_TSTRING;
								strncpy(DebugInfo.VarStrValues[nIndex], (char*)lua_tostring(L, nStackPos), 255);
								DebugInfo.VarStrValues[nIndex][255] = 0;
								nIndex++;
								break;
							}
						case LUA_TTABLE:
							{
								strncpy(DebugInfo.VarNames[nIndex], 
									(char*)&(ld._func->value.i->func->f.l->kstr[i]->str), 31);
								DebugInfo.VarNames[nIndex][31] = 0;
								DebugInfo.VarTypes[nIndex] = LUA_TTABLE;
								nIndex++;
								break;
							}
						case LUA_TFUNCTION:
							{
								break;
							}
						}

					}
					DebugInfo.dwGlobalTotal = nIndex;

					//获取局部变量的名称和数值
					const char* lpszName = NULL;
					int nLocalIndex = 0;

					DebugInfo.dwLocalTotal = ld._func->value.i->func->f.l->nlocvars;
					//取局部变量名称
					for (nLocalIndex = 0; nLocalIndex < (int)DebugInfo.dwLocalTotal; nLocalIndex++)
					{
						strncpy(DebugInfo.VarNames[nIndex], 
							(char*)(&(ld._func->value.i->func->f.l->locvars[nLocalIndex].varname->str)), 
							31);
						DebugInfo.VarNames[nIndex][31] = 0;
						nIndex++;
					}
					//取局部变量中有效值个数
					//局部变量尚未被定义或者使用过的值，不在堆栈中出现
					int nAvailLocalTotal = 0;
					lpszName = lua_getlocal(L, &ld, nAvailLocalTotal + 1);
					while (lpszName != NULL)
					{
						nAvailLocalTotal++;
						lpszName = lua_getlocal(L, &ld, nAvailLocalTotal + 1);
					}
					//从堆栈中取值
					for (int i = 0; i < nAvailLocalTotal; i++)
					{
						//确定堆栈中的位置
						//在LUA中正的堆栈位置表示从栈底往栈顶计数
						//负的堆栈位置表示从栈顶往栈底计数
						int nStackPos = i - nAvailLocalTotal;
						DebugInfo.VarTypes[DebugInfo.dwGlobalTotal + i] = lua_type(L, nStackPos);
						switch (lua_type(L, nStackPos))
						{
						case LUA_TNONE:
							{
								
								break;
							}
						case LUA_TUSERDATA:
							{

								break;
							}
						case LUA_TNIL:
							{

								break;
							}
						case LUA_TNUMBER:
							{
								DebugInfo.VarIntValues[DebugInfo.dwGlobalTotal + i] = (DWORD)lua_tonumber(L, nStackPos);
								break;
							}
						case LUA_TSTRING:
							{
								strncpy(DebugInfo.VarStrValues[DebugInfo.dwGlobalTotal + i], (char*)lua_tostring(L, nStackPos), 255);
								DebugInfo.VarStrValues[DebugInfo.dwGlobalTotal + i][255] = 0;
								break;
							}
						case LUA_TTABLE:
							{

								break;
							}
						case LUA_TFUNCTION:
							{

								break;
							}
						}
					}

					for (int i = nAvailLocalTotal; i < (int)DebugInfo.dwLocalTotal; i++)
					{
						DebugInfo.VarTypes[DebugInfo.dwGlobalTotal + i] = LUA_TNONE;
					}
				}


				DebugMessage.dwCommand = DBC_NONE;
				DebugInfo.dwVarCount++;
				break;
			}
		case DBC_SET_GLOBAL_VAR:
			{
				switch (DebugMessage.dwParam1)
				{
				case LUA_TNUMBER:
					{
						lua_pushnumber(L, DebugMessage.dwParam2);						
						break;
					}
				case LUA_TSTRING:
					{
						lua_pushstring(L, DebugMessage.szParam2);
						break;
					}
				}

				lua_setglobal(L, DebugMessage.szParam1);

				DebugMessage.dwCommand = DBC_NONE;
				break;
			}
		case DBC_SET_LOCAL_VAR:
			{
				lua_Debug	ld;

				if (lua_getstack(L, 0, &ld) && lua_getinfo(L, "flnSu", &ld))
				{
					//计算局部变量在堆栈中的位置
					int nLocalVarIndex = 0;
					while (strncmp(DebugMessage.szParam1, 
								   (char*)(&(ld._func->value.i->func->f.l->locvars[nLocalVarIndex].varname->str)), 
								   255) &&
						nLocalVarIndex < ld._func->value.i->func->f.l->nlocvars)
						nLocalVarIndex++;
					
					if (nLocalVarIndex < ld._func->value.i->func->f.l->nlocvars)
					{
						switch (DebugMessage.dwParam1)
						{
						case LUA_TNUMBER:
							{
								lua_pushnumber(L, DebugMessage.dwParam2);						
								break;
							}
						case LUA_TSTRING:
							{
								lua_pushstring(L, DebugMessage.szParam2);
								break;
							}
						}
						lua_setlocal(L, &ld, nLocalVarIndex);
					}
				}

				DebugMessage.dwCommand = DBC_NONE;
				break;
			}
		case DBC_RELOAD_SCRIPT:
			{
				KLuaScript*	lpThis = (KLuaScript*)DebugInfo.dwThis;
				lpThis->Load(lpThis->m_szScriptName);
				DebugMessage.dwCommand = DBC_NONE;
				break;
			}
		case DBC_INACTIVE:
			{
				bFinished = TRUE;
				break;
			}
		default:
			{
				DebugMessage.dwCommand = DBC_INACTIVE;
				break;
			}
		}
		if (!bFinished)
		{
#ifdef WIN32
			Sleep(10);
#elif __linux
			usleep(10000);
#endif
		}
	}

	return;
}
#endif //LUA_DEBUG
//End Added by AQ

KLuaScript::KLuaScript()
{
	m_szScriptName[0]		= '\0';
	m_LuaState	= lua_open(100);

	if (m_LuaState == NULL)
	{
		ScriptError(LUA_CREATE_ERROR, "");
		m_IsRuning			= false;
	}
	else
	{
		m_IsRuning			= true;
	}
}

//---------------------------------------------------------------------------
// 函数:	KLuaScript::KLuaScript
//---------------------------------------------------------------------------
KLuaScript::KLuaScript(int StackSize/* = 0*/)
{
	m_szScriptName[0]		= '\0';
	m_LuaState				= lua_open(StackSize);

	if (m_LuaState == NULL )
	{
		ScriptError(LUA_CREATE_ERROR, "");
		m_IsRuning = false;
	}
	else
	{
		m_IsRuning	= true;
	}
}


//---------------------------------------------------------------------------
// 函数:	KLuaScript::~KLuaScript
//---------------------------------------------------------------------------
KLuaScript::~KLuaScript()
{
	Exit();
}

//---------------------------------------------------------------------------
// 函数:	KLuaScript::LoadBuffer()
//---------------------------------------------------------------------------
bool KLuaScript::LoadBuffer(const char* pBuffer, unsigned int dwLen)
{
	if (lua_getgccount(m_LuaState) > 2000) 
	{
		lua_setgcthreshold(m_LuaState, 0) ;
		if (m_szScriptName[0])
			printf("lua gcc connect. %s \n", m_szScriptName);
		else
			printf("lua gcc connect.\n");
	}

	if (dwLen < 0)
	{
		ScriptError(LUA_SCRIPT_LEN_ERROR, "");
		return false;
	}
	
	if (Lua_CompileBuffer(m_LuaState,pBuffer, dwLen, NULL) != 0)
	{
		ScriptError(LUA_SCRIPT_COMPILE_ERROR, "");
		return false;
	}
	return true;
}

//---------------------------------------------------------------------------
// 函数:	KLuaScript::Load
//---------------------------------------------------------------------------
bool KLuaScript::Load(const char * Filename)
{
	IFile*	pFile = NULL;
	char*	pBuffer = NULL;
	unsigned int	Size;

	if ((pFile = g_OpenFile(Filename)) == NULL)
		return false;

	//Added by AQ for Debugger, 2004.11.15
#ifdef LUA_DEBUG
    strncpy(m_szScriptName, Filename, sizeof(m_szScriptName));
	m_szScriptName[sizeof(m_szScriptName) - 1] = '\0';
	
    g_GetFullPath(m_szFullScriptName, Filename);
	m_szFullScriptName[sizeof(m_szFullScriptName) - 1] = '\0';
#endif //LUA_DEBUG	  this
	//End Added by AQ

	int		nResult = false;

	Size = pFile->Size();
	pBuffer = (char*)malloc(Size + 4);
	if (pBuffer)
	{
		if (pFile->Read(pBuffer, Size) == Size)
		{
			pBuffer[Size] = 0;

			try
			{
				if (LoadBuffer(pBuffer, Size))
					nResult = true;
				else
					ScriptError(LUA_SCRIPT_COMPILE_ERROR, "");
			}
			catch(...)
			{
				printf("Load Script %s 出现异常，请检查!!\n", Filename);
			}
		}
		free(pBuffer);
		pBuffer = NULL;
	}

	pFile->Release();
	pFile = NULL;

	if (!nResult)
		return false;

	return ExecuteCode();
}

//---------------------------------------------------------------------------
// 函数:	KLuaScript::Execute
//---------------------------------------------------------------------------
bool KLuaScript::ExecuteMain()
{
	if (m_IsRuning && m_LuaState)
	{
		strncpy(g_szRunningScript, m_szScriptName, sizeof(g_szRunningScript));
		strncpy(g_szRunningFunction, MAINFUNCTIONNAME, sizeof(g_szRunningFunction));
		return CallFunction(MAINFUNCTIONNAME, 0, "");
	}
	return false;
}

//---------------------------------------------------------------------------
// 函数:	KLuaScript::ExecuteCode
//---------------------------------------------------------------------------
bool KLuaScript::ExecuteCode()
{
	if (!(m_IsRuning && m_LuaState))
	{
		ScriptError(LUA_SCRIPT_EXECUTE_ERROR, "");
		//if (!ExecuteCode()) return false; ZHANGPENG 发现这里可能有错
		return false;
	}

	//Added by AQ for Debugger, 2004.11.15
#ifdef LUA_DEBUG
	if (DebugMessage.dwCommand != DBC_INACTIVE)
	{
		DebugInfo.lpszScriptFileName = m_szScriptName;
		DebugInfo.dwThis = (DWORD)this;
		DebugInfo.lpszScriptFuncName = NULL;
	}
#endif //LUA_DEBUG
	//End Added by AQ

	int state;
	strncpy(g_szRunningScript, m_szScriptName, sizeof(g_szRunningScript));
	g_szRunningFunction[0] = 0;
	if (state = Lua_Execute(m_LuaState) != 0)
	{
		ScriptError(LUA_SCRIPT_EXECUTE_ERROR, state, "");
		return false;
	}

	return	true;
}


//---------------------------------------------------------------------------
// 函数:	KLuaScript::CallFunction
// 功能:	调用Lua脚本内的函数
// 参数:	char* cFuncName
// 参数:	int nResults
// 参数:	char* cFormat  调用时所传参数的类型 
//			n:数字型(double) d:整形(int) s:字符串型 f:C函数型  n:Nil v:Value p:Point
//        v形为Lua支持的，参数为整形的数index，指明将index所指堆栈的变量作为
//			 该函数的调用参数。
//	注意：由于该函数有不定参数…,对于数字，系统并不确定数是以double还是以int
//  存在，两种保存形式是不同的。因此需要注意当传入的数是整形时，格式符应用d
//  而不能用n,或者强行改变为double形。否则会出现计算的错误。
//   
// 参数:	...
// 返回:	bool 
//---------------------------------------------------------------------------
bool KLuaScript::CallFunction(char* cFuncName, int nResults, char* cFormat, va_list vlist)
{
	double nNumber;
	char * cString	= NULL;
	void * pPoint	= NULL;
	Lua_CFunction CFunc;
	int i=0;
	int nArgnum = 0;
	int nIndex = 0;
	int nRetcode;		//调用脚本函数后的返回码

	if (! (m_IsRuning && m_LuaState))
	{
		ScriptError(LUA_SCRIPT_STATES_IS_NULL, cFuncName);
		return false;
	}

	//Added by AQ for Debugger, 2004.11.15
#ifdef LUA_DEBUG
	if (DebugMessage.dwCommand != DBC_INACTIVE)
	{
		DebugInfo.lpszScriptFileName = m_szScriptName;
		DebugInfo.lpszScriptFuncName = cFuncName;
		DebugInfo.dwThis = (DWORD)this;
	}
#endif //LUA_DEBUG
	//End Added by AQ
	
	{
		Lua_GetGlobal(m_LuaState, cFuncName); //在堆栈中加入需要调用的函数名

		while (cFormat[i] != '\0')
		{
			switch(cFormat[i])
			{
			case 'n'://输入的数据是double形 NUMBER，Lua来说是Double型
				{ 
					nNumber = va_arg(vlist, double );
					Lua_PushNumber(m_LuaState, nNumber);
					nArgnum ++;							

				}
				break;
			
			case 'd'://输入的数据为整形
				{
					nNumber = (double)(va_arg(vlist, int));
					Lua_PushNumber(m_LuaState, (double) nNumber);
					nArgnum ++;
				}
				break;
				
			case 's'://字符串型
				{
					cString = va_arg(vlist, char *);
					Lua_PushString(m_LuaState, cString);
					nArgnum ++;							
				}
				break;
			case 'N'://NULL
				{
					Lua_PushNil(m_LuaState);
					nArgnum ++;
				}
				break;
			
			case 'f'://输入的是CFun形，即内部函数形
				{
					CFunc = va_arg(vlist, Lua_CFunction);
					Lua_PushCFunction(m_LuaState, CFunc) ;
					nArgnum ++;
				}
				break;
			
			case 'v'://输入的是堆栈中Index为nIndex的数据类型
				{
					nNumber = va_arg(vlist, int);
					int nIndex1 = (int) nNumber;
					Lua_PushValue(m_LuaState, nIndex1);
					nArgnum ++;
				}
				break;
			case 't'://输入为一Table类型
				{
					
					

				}
				break;
			
			case 'p':
				{
					pPoint = va_arg(vlist, void *);

					Lua_PushUserTag(m_LuaState, pPoint,m_UserTag);
					nArgnum ++;
				}
				break;
			}
				
			i++;	
		}
		
	}  
    		
	nRetcode = Lua_Call(m_LuaState, nArgnum, nResults);
	
	if (nRetcode != 0)
	{
		ScriptError(LUA_SCRIPT_EXECUTE_ERROR, nRetcode, cFuncName);
		return false;
	}
	

	return	true;
}


//---------------------------------------------------------------------------
// 函数:	KLuaScript::CallFunction
//---------------------------------------------------------------------------
bool KLuaScript::CallFunction(const char* cFuncName, int nResults, char* cFormat, ...)
{
	bool bResult  = false;
	strncpy(g_szRunningScript, m_szScriptName, sizeof(g_szRunningScript));
	strncpy(g_szRunningFunction, cFuncName, sizeof(g_szRunningFunction));
	va_list vlist;
	va_start(vlist, cFormat);
	// MikeDai[2004-12-14]
	// Potential function Invoking confusion between the following two functions:
	// bool KLuaScript::CallFunction(const char* cFuncName, int nResults, char* cFormat, ...)
	// bool KLuaScript::CallFunction(char* cFuncName, int nResults, char* cFormat, va_list vlist)
	bResult = CallFunction((char*)cFuncName, nResults, cFormat, vlist);
	va_end(vlist);
	return bResult;
}


//---------------------------------------------------------------------------
// 函数:	KLuaScript::GetValuesFromStack
// 功能:	从堆栈中获得变量
//---------------------------------------------------------------------------
bool KLuaScript::GetValuesFromStack(char * cFormat, ...)	
{
	va_list vlist;
	double* pNumber = NULL;
	const char **   pString ;
	int * pInt = NULL;
	int i = 0;
	int nTopIndex = 0;
	int nIndex = 0;
	int nValueNum = 0;//cFormat的字符长度，表示需要取的参数数量

	if (! m_LuaState)
		return false;

	nTopIndex = Lua_GetTopIndex(m_LuaState);	
	nValueNum = strlen(cFormat);
	
	if (nTopIndex == 0 || nValueNum == 0)//当堆栈中无数据或不取参数是返回false
		return false;

	if (nTopIndex < nValueNum)
		return false;

	nIndex = nTopIndex - nValueNum +1;
	
	{
		va_start(vlist, cFormat);     
		
		while (cFormat[i] != '\0')
		{
			
			switch(cFormat[i])
			{
			case 'n'://返回值为数值形,Number,此时Lua只传递double形的值
				{
					pNumber = va_arg(vlist, double *);
					
					if (pNumber == NULL)
						return false;

					if (Lua_IsNumber(m_LuaState, nIndex ))
					{
						* pNumber = Lua_ValueToNumber(m_LuaState, nIndex ++ );
												
					}
					else
					{
						ScriptError(LUA_SCRIPT_NOT_NUMBER_ERROR, "");
						return false;
					}
					
					
				}
				break;
			case 'd':
				{
					pInt = va_arg(vlist, int *);
					if (pInt == NULL)
						return false;
					if ( Lua_IsNumber(m_LuaState, nIndex))
					{
						* pInt = (int ) Lua_ValueToNumber(m_LuaState, nIndex ++);
					}
					else
					{
						ScriptError(LUA_SCRIPT_NOT_NUMBER_ERROR, "");
						return false;
					}

				}
				break;
			case 's'://字符串形
				{
					pString = va_arg(vlist, const char **);
					
					if (pString == NULL)
						return false;
					
					if (Lua_IsString(m_LuaState, nIndex))
					{
						(*pString) = (const char *)Lua_ValueToString(m_LuaState, nIndex++);
						
					}
					else
					{
						ScriptError(LUA_SCRIPT_NOT_STRING_ERROR, "");
						return false;
					}
				}
				break;
			
			}
			
			
		i ++;	
		}
		va_end(vlist);     		/* Reset variable arguments.      */
		
	}
	return	true;
}

//---------------------------------------------------------------------------
// 函数:	KLuaScript::Init
// 功能:	初始化脚本对象，注册系统标准函数库
// 返回:	bool 
//---------------------------------------------------------------------------
bool KLuaScript::Init()
{
	Exit();
	if (! m_LuaState)
	{
		m_LuaState	= Lua_Create(0);
		if (m_LuaState == NULL)
		{
			ScriptError(LUA_CREATE_ERROR, "");
			m_IsRuning	= false;
			return false;
		}
		//Added by AQ for Debugger, 2004.11.15
		//设置行回调函数
#ifdef	LUA_DEBUG
		m_LuaState->linehook = LuaProcessDebugInfo;
#endif //LUA_DEBUG
		//End Added by AQ

		m_IsRuning	= true;
		m_UserTag = lua_newtag(m_LuaState)	;
	}

	RegisterStandardFunctions();
	return	true;
}

//---------------------------------------------------------------------------
// 函数:	KLuaScript::ReleaseScript
// 功能:	释放该脚本资源。
//---------------------------------------------------------------------------
void KLuaScript::Exit()
{
	m_szScriptName[0] = '\0';
	m_IsRuning = false;
	if (m_LuaState)
	{
		Lua_Release(m_LuaState);
		m_LuaState = NULL;
	}
}

//---------------------------------------------------------------------------
// 函数:	KLuaScript::RegisterFunction
// 功能:	注册某内部C函数至脚本中
// 参数:	char* FuncName  在脚本中使用的函数名
// 参数:	void* Func    实际相应的C函数指针
// 参数:	int Args = 0 //与KScript接口相容，无用
// 参数:	int Flag = 0 //与KScript接口相容, 无用
// 返回:	bool 
//---------------------------------------------------------------------------
bool KLuaScript::RegisterFunction(const char* FuncName , void* Func)
{
	if (! m_LuaState)
		return false;
	Lua_Register(m_LuaState, FuncName, (Lua_CFunction)Func);
	return true;
}

//---------------------------------------------------------------------------
// 函数:	KLuaScript::RegisterFunctions
// 功能:	批量注册Lua的内部C函数，各个函数的信息保存在TLua_Funcs的数据中
// 参数:	TLua_Funcs *Funcs 数组的指针
// 参数:	int n 函数数量。可以为零，由系统计算得到。
// 返回:	bool 
//---------------------------------------------------------------------------
bool KLuaScript::RegisterFunctions(TLua_Funcs Funcs[], int n)
{
	if (! m_LuaState)
		return false;
	if (n == 0)
		n = sizeof(Funcs) / sizeof(Funcs[0]);
	for (int i = 0; i < n; i ++)
		Lua_Register(m_LuaState, Funcs[i].name, Funcs[i].func);
	return true;
}

//---------------------------------------------------------------------------
// 函数:	KLuaScript::RegisterStandardFunctions
// 功能:	注册Lua系统标准的函数库
// 返回:	void 
//---------------------------------------------------------------------------
void KLuaScript::RegisterStandardFunctions()
{
	if (! m_LuaState)
		return ;
	Lua_OpenBaseLib(m_LuaState);//Lua基本库
	Lua_OpenIOLib(m_LuaState);//输入输出库
	Lua_OpenStrLib(m_LuaState);//字符串处理库
	Lua_OpenMathLib(m_LuaState);//数值运算库
	//Lua_OpenDBLib(m_LuaState);//调试库
}

//---------------------------------------------------------------------------
// 函数:	KLuaScript::ScriptError
//---------------------------------------------------------------------------
void KLuaScript::ScriptError(int Error, char *szExtendInfo)
{
//Modified by AQ for debugger, 2004.11.18
//Original code:
//	char lszErrMsg[200];
//	sprintf(lszErrMsg, "ScriptError %d. (%s) \n", Error, m_szScriptName);
//	lua_outerrmsg(lszErrMsg);
//New code:
#ifdef LUA_DEBUG
	sprintf(DebugInfo.szErrorMsg, "ScriptError %d. (%s:%s) \n", Error, m_szScriptName, (szExtendInfo && szExtendInfo[0]) ? szExtendInfo : "");
	//KGLogPrintf(LOG_WARNING, DebugInfo.szErrorMsg);
	lua_outerrmsg(DebugInfo.szErrorMsg);
	DebugInfo.dwErrorCount++;
#endif	//LUA_DEBUG
//End Modified by AQ
}

//---------------------------------------------------------------------------
// 函数:	KLuaScript::ScriptError
//---------------------------------------------------------------------------
void KLuaScript::ScriptError(int Error1 ,int Error2, char *szExtendInfo)
{
//Modified by AQ for debugger, 2004.11.18
//Original code:
//	char lszErrMsg[200];
//	sprintf(lszErrMsg, "ScriptError %d:[%d] (%s) \n", Error1, Error2, m_szScriptName);
//	lua_outerrmsg(lszErrMsg);
//New code:
#ifdef LUA_DEBUG
	sprintf(DebugInfo.szErrorMsg, "ScriptError %d:[%d] (%s:%s) \n", Error1, Error2, m_szScriptName, (szExtendInfo && szExtendInfo[0]) ? szExtendInfo : "");
	//KGLogPrintf(LOG_WARNING, DebugInfo.szErrorMsg);
	lua_outerrmsg(DebugInfo.szErrorMsg);
	DebugInfo.dwErrorCount++;
#endif	//LUA_DEBUG
//End Modified by AQ
}

//---------------------------------------------------------------------------
// 函数:	KLuaScript::SafeCallBegin
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
// SafeCallBegin与SafeCallEnd两函数应搭配使用，以防止在调用Lua的外部函数之后，
//有多余数据在堆栈中未被清除。达到调用前与调用后堆栈的占用大小不变。
//上述情况只需用在调用外部函数时，内部函数不需如此处理。
//																	Romandou
//---------------------------------------------------------------------------
void KLuaScript::SafeCallBegin(int * pIndex)
{
	if (! m_LuaState)
		return ;
	Lua_SafeBegin(m_LuaState, pIndex);
}

//---------------------------------------------------------------------------
// 函数:	KLuaScript::SafeCallEnd
// 功能:	
// 参数:	int nIndex
// 返回:	void 
//---------------------------------------------------------------------------
void KLuaScript::SafeCallEnd(int nIndex)
{
	if (! m_LuaState)
		return;
	Lua_SafeEnd(m_LuaState, nIndex);
}

//---------------------------------------------------------------------------
// 函数:	KLuaScript::StopScript
// 功能:	中止脚本
// 参数:	void
// 返回:	bool 
//---------------------------------------------------------------------------
bool KLuaScript::Stop()
{
	if (!m_IsRuning)
		return true;
	if (!m_LuaState)
		return false;
	m_IsRuning =  false;
	return true;
}

//---------------------------------------------------------------------------
// 函数:	KLuaScript::ResumeScript
// 功能:	恢复已中止的脚本
// 参数:	void
// 返回:	bool 
//---------------------------------------------------------------------------
bool KLuaScript::Resume()
{
	if ((! m_IsRuning) && (m_LuaState))
	{
		m_IsRuning = true;
		return true;
	}
	return false;
}


//---------------------------------------------------------------------------
// 函数:	KLuaScript::CreateTable
// 功能:	建立一个Lua的Table，在调用该函数并设置Table各个成员之后，必须调用
//			SetGlobalName()来给这个Table指定一个名字。
// 返回:	unsigned int 
//---------------------------------------------------------------------------
unsigned int KLuaScript::CreateTable()
{
	 int nIndex = 0;
	
	nIndex = Lua_GetTopIndex(m_LuaState) ;
	Lua_NewTable(m_LuaState);
	if (Lua_GetTopIndex(m_LuaState) != ++nIndex ) 
		return (unsigned int)(-1);

	return nIndex;
}

void KLuaScript::PushNumber(double number)
{
	if (m_LuaState)
		Lua_PushNumber(m_LuaState, number);
}

//---------------------------------------------------------------------------
// 函数:	KLuaScript::SetGlobalName
// 功能:	设置Lua堆栈顶部的数据一个名字
// 参数:	char* szName
// 返回:	void 
//---------------------------------------------------------------------------
void KLuaScript::SetGlobalName(char* szName)
{
	if (!szName)
		return ;
	Lua_SetGlobal(m_LuaState, szName);
}

//---------------------------------------------------------------------------
// 函数:	KLuaScript::ModifyTable
// 功能:	将指定名称的LuaTable置堆栈顶端，并返回顶端Index
// 参数:	char* szTableName
// 返回:	unsigned int 若Lua中不存在该Table则返回-1
//---------------------------------------------------------------------------
unsigned int KLuaScript::ModifyTable(const char* szTableName) 
{
	if (! szTableName[0])
		return (unsigned int)(-1);
	
	int nIndex = Lua_GetTopIndex(m_LuaState);
	
	Lua_GetGlobal(m_LuaState, szTableName);

	if (Lua_GetTopIndex(m_LuaState) != ++nIndex)
		return (unsigned int)(-1);
	
	return nIndex;
}

void KLuaScript::SetScriptName(const char* scpname)
{
	strncpy(m_szScriptName, scpname, sizeof(m_szScriptName));
	m_szScriptName[sizeof(m_szScriptName) - 1] = 0;
}


void g_GetExecutingScript(char *pszScriptBuffer, int nScriptBufferLen, char *pszFunctionBuffer, int nFunctionBufferLen)
{
	if (pszScriptBuffer)
	{
		strncpy(pszScriptBuffer, g_szRunningScript, nScriptBufferLen);
		pszScriptBuffer[nScriptBufferLen - 1] = 0;
	}
	if (pszFunctionBuffer)
	{
		strncpy(pszFunctionBuffer, g_szRunningFunction, nFunctionBufferLen);
		pszFunctionBuffer[nFunctionBufferLen - 1] = 0;
	}
}

#endif	//not LUA_V_5