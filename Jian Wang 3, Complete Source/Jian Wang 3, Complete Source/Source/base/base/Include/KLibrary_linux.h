///////////////////////////////////////////////////////////////
//	
//  FileName		:   KLibrary_linux.h
//  Composer		:	wangbin
//	latest Modify	:	2006-01-12
//  Comment			:   动态库的跨平台封装-linux
//	
///////////////////////////////////////////////////////////////
#ifndef __KLIBRARY_LINUX_H__
#define __KLIBRARY_LINUX_H__

#include <dlfcn.h>
#include <stdio.h>
#include <alloca.h>
#include <string.h>

#ifndef ASSERT
#define ASSERT(e)
#endif

class KLibrary
{
public:
	KLibrary() : _dll(0) {}
	~KLibrary() {
		if (_dll)
			dlclose(_dll);
	}
	bool Load(const char *pszDllFile) {
		ASSERT(pszDllFile);
		if (*pszDllFile == 0)
			return false;
		int len = strlen(pszDllFile) + 1;
		char *pszPath = (char*)alloca(len);
		char *pszName = (char*)alloca(len);
		Parse(pszDllFile, pszPath, pszName);
		
		// 缺省目录是当前目录
		char *pszFile = (char*)alloca(len + 6);
		if (pszPath[0] != 0)
			sprintf(pszFile, "%slib%s.so", pszPath, pszName);
		else
			sprintf(pszFile, "./lib%s.so", pszName);
			
		_dll = dlopen(pszFile, RTLD_NOW);
		return _dll != 0;
	}
	void Free() {
		ASSERT(_dll);
		dlclose(_dll);
		_dll = 0;
	}
	void *GetProcAddress(const char *pszProcName) {
		ASSERT(_dll && pszProcName);
		return dlsym(_dll, pszProcName);
	}
private:
	// 拆分路径和文件名
	void Parse(const char *pszPathFile, char *pszPath, char *pszName) {
		char *pos = strrchr(pszPathFile, '/');
		if (!pos) {
			*pszPath = 0;
			strcpy(pszName, pszPathFile);
			return;
		}
		int len = pos - pszPathFile + 1;
		memcpy(pszPath, pszPathFile, len);
		pszPath[len] = 0;
		strcpy(pszName, pos + 1);
	}
private:
	void *_dll;
};

#endif //__KLIBRARY_LINUX_H__
