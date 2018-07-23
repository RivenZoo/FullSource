/*****************************************************************************************
//	Main.h
//	Copyright : Kingsoft 2012
//	Author	:   peikai
//	CreateTime:	2012-09-04
------------------------------------------------------------------------------------------
*****************************************************************************************/

#ifndef __DIFF_PACK_H_
#define __DIFF_PACK_H_

#include <iostream>
#include <string>
using namespace std;

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

int g_ReadIni(const char* filename, char * packages, int &nCount);
IPackFileShell* LoadPackFileList(const char* pList, const char* pSection, int test);


#endif //__DIFF_PACK_H_