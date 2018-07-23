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

#include "..\base\include\Engine.h"
#include "..\base\include\Engine\PackDef.h"
#include "..\base\include\Engine\IPackFileShell.h"


int g_ReadIni(const char* filename, char * packages, int &nCount);


#endif //__DIFF_PACK_H_