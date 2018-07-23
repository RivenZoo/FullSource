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

//using namespace std;

int main(int arg, char **argv)
{
	//
	char packages[2048];
	int nCount = 0;

	g_ReadIni("package.ini", packages, nCount);


	getchar();

	return 0;
}