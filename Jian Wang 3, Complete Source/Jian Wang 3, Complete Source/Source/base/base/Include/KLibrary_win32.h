///////////////////////////////////////////////////////////////
//	
//  FileName		:   KLibrary_win32.h
//  Composer		:	wangbin
//	latest Modify	:	2006-01-12
//  Comment			:   动态库的跨平台封装-win32
//	
///////////////////////////////////////////////////////////////
#ifndef __KLIBRARY_WIN32_H__
#define __KLIBRARY_WIN32_H__

#include <windows.h>

#ifndef ASSERT
#define ASSERT(e)
#endif

class KLibrary
{
public:
	KLibrary() : _dll(NULL) {}
	~KLibrary() {
		if (_dll)
			::FreeLibrary(_dll);
	}
	bool Load(const char *pszDllFile) {
		char *pszFile = (char*)alloca(strlen(pszDllFile) + 5);
		sprintf(pszFile, "%s.dll", pszDllFile);
		_dll = ::LoadLibrary(pszFile);
		return _dll != NULL;
	}
	void Free() {
		ASSERT(_dll);
		::FreeLibrary(_dll);
		_dll = NULL;
	}
	void *GetProcAddress(const char *pszProcName) {
		ASSERT(_dll && pszProcName);
		return ::GetProcAddress(_dll, pszProcName);
	}
private:
	HMODULE _dll;
};

#endif //__KLIBRARY_WIN32_H__
