/*****************************************************************************************
//	对打包文件进行各种维护操作（生成、展开、修改、合并等等）的工具程序
//	Copyright : Kingsoft 2005
//	Author	:   Wooy(Wu yue)
//	CreateTime:	2005-3-23
------------------------------------------------------------------------------------------
*****************************************************************************************/
#ifndef __TOOL_PACK_FILE_H_
#define __TOOL_PACK_FILE_H_

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include "..\..\..\include\Engine.h"
#include "..\..\..\include\Engine\PackDef.h"
#include "..\..\..\include\Engine\IPackFileShell.h"

enum PACK_OPER_INDEX
{
	PACK_OPER_NONE,
	PACK_OPER_PAK,
	PACK_OPER_EXTRACT,
	PACK_OPER_COMBIN,
	PACK_OPER_DIFF,
	PACK_OPER_UPDATE,
};

enum OPER_PACK_STRING_INDEX
{
	OPER_PACK_PACKFILE_NAME,
	OPER_PACK_ELEM_ROOT_PATH,
	OPER_PACK_BATCH_FILE,
	OPER_PACK_FOLDER_TO_ADD,
};

enum OPER_EXTRACT_STRING_INDEX
{
	OPER_EXTRACT_PACKFILE_NAME,
	OPER_EXTRACT_ELEM_ROOT_PATH,
	OPER_EXTRACT_FILE_TO_EXTRACT,
	OPER_EXTRACT_DEST_FILE_NAME,
};

enum OPER_COMBIN_STRING_INDEX
{
	OPER_COMBIN_PACKFILE_NAME,
	OPER_COMBIN_ADDED_PACKFILE_NAME,
};

enum OPER_UPDATE_STRING_INDEX
{
	OPER_UPDATE_DIFF_PACK_FILE,
	OPER_UPDATE_OLD_PACK_LIST,
	OPER_UPDATE_NEW_PACK_LIST,
};

enum OPER_DIFF_STRING_INDEX
{
	OPER_DIFF_DIFF_PACK,
	OPER_DIFF_OLD_PACK,
	OPER_DIFF_NEW_PACK,
};

extern char				g_StringTable[4][MAX_PATH];
extern IPackFileShell*	g_PackFileShell;
extern int				g_nPackIndex;

#endif //__TOOL_PACK_FILE_H_
