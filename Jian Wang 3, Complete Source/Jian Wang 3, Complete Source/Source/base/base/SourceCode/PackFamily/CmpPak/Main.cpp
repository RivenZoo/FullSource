/*****************************************************************************************
//	Main.cpp
//	Copyright : Kingsoft 2012
//	Author	:   peikai
//	CreateTime:	2012-09-04
------------------------------------------------------------------------------------------
*****************************************************************************************/
#include<iostream>
#include "DiffPak.h"
#include "Main.h"
#include 	<stdarg.h>
#include 	<stdio.h>
#include	<stdlib.h>
#include	<string.h>

#include	<io.h>
#include	<Windows.h>
#include	<direct.h>

//using namespace std;
IPackFileShell*	g_PackFileShell = NULL;
char			g_StringTable[4][MAX_PATH] = { 0 };
int				g_nPackIndex = -1;

typedef std::map<unsigned int, string> _m;
_m m;

//static ni = 0;
int
visit_path_recursively(const char* pcszPath, const char * pcszFilter){
	static int ni = 0;
	intptr_t		hFind;
	_finddata_t		FindData;
	char			szPath[MAX_PATH];
	int			nRet = 1;

#ifdef _USED_FOR_FORM_
	if ( SetCurrentDirectoryA(pcszPath) == 0 ){
#else
	if ( SetCurrentDirectory(pcszPath) == 0 ){
#endif
		//write_log(LT_BOTH, "Error: Can't set the current directory: %s!\n",
		//	  pcszPath);
		return 0;
	}

	hFind = _findfirst("*.*", &FindData);
	if (hFind == -1)
		return 0;

	do{
		if ( strcmp(FindData.name, ".") == 0 ||
		     strcmp(FindData.name, "..") == 0)
			continue;

		sprintf(szPath, "%s\\%s", pcszPath, FindData.name);
		if ( FindData.attrib & _A_SUBDIR ){
//			if ( strchr(szPath, pcszFilter) ){
//				nRet = dir_func(szPath);
//				if ( nRet == 0 )
//					goto exit;
//				else if ( nRet == 2 ){
//				continue;
//				}
//			}

			nRet = visit_path_recursively(szPath, pcszFilter);
			if ( nRet == 0 )
				goto exit;
			
//			if ( /*dir_func2 != NULL*/ ){
//				nRet = dir_func2(szPath);
//				if ( nRet == 0 )
//					goto exit;
//			}
		}
		else{
#ifdef _USED_FOR_FORM_
			SetFileAttributesA(FindData.name, FILE_ATTRIBUTE_NORMAL);
#else
			SetFileAttributes(FindData.name, FILE_ATTRIBUTE_NORMAL);
#endif
			if ( 1/*file_func != NULL*/ ){
				//nRet = file_func( szPath );
				ni++;
				if (ni %100 == 0)
				{
					printf("+");
				}
				KSmartFile SrcFile;
				SrcFile = g_OpenFile(szPath, true, false);
				unsigned char * pSrcBuffer = (unsigned char*)SrcFile->GetBuffer();
				int	nSrcSize = SrcFile->Size();
				unsigned int uPakCRC = Misc_CRC32(0, pSrcBuffer, nSrcSize);
				_m::iterator it = m.find(uPakCRC);
				if (it != m.end())
				{
					printf("%s  &&  %s\n", it->second.c_str(), szPath);
				}
				else
					m.insert(make_pair(uPakCRC, szPath));
				//printf("1.%s - %u\n",szPath, uPakCRC);
				//if ( nRet == 0 )
				//	goto exit;
			}
		}
	}while ( _findnext(hFind, &FindData) == 0 );

 exit:
	if ( _findclose(hFind) )
	//	write_log(LT_BOTH, "Error: Can't close directory %s!\n", 
	//		  pcszPath);
	
	return nRet;
//#endif //WIN32
}

int main(int arg, char **argv)
{
	//
	char packages[2048];
	int nCount = 0;

//	g_ReadIni("package.ini", packages, nCount);
	//LoadPackFileList("package.ini", "package", 0);
	if (arg < 2 )
	{
		printf("No params!\n");
	}
	if (argv[2])
	{
		visit_path_recursively(argv[1], argv[2]);
	}
	else
		visit_path_recursively(argv[1], ".svn");

	printf("Over\n");
	//
	getchar();

	return 0;
}