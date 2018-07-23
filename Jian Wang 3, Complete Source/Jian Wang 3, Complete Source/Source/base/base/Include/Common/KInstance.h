//*********************************************************************
// file		: KInstance.h
// author	: wangbin
// datetime	: 2004-09-22 15:27
// comment	: 进程唯一实例
//*********************************************************************
#ifndef __KINSTANCE_H__
#define __KINSTANCE_H__

#include <windows.h>
#include <stdio.h>

class KInstance
{
private:
	HANDLE m_handle;

public:
	// 检查是否存在某个名字对应的实例
	static BOOL IsRunning(LPCSTR pszName)
	{
		char szName[MAX_PATH];
		_snprintf(szName, MAX_PATH - 1, "Global\\%s", pszName);
		szName[MAX_PATH - 1] = 0;

		HANDLE handle = ::OpenSemaphore(SEMAPHORE_ALL_ACCESS, FALSE, szName);
		if (handle)
			::CloseHandle(handle);
		return (handle != NULL);
	}

	KInstance(LPCSTR pszName) : m_handle(NULL)
	{
		char szName[MAX_PATH];
		_snprintf(szName, MAX_PATH - 1, "Global\\%s", pszName);
		szName[MAX_PATH - 1] = 0;

		m_handle = ::CreateSemaphore(NULL, 1, 1, szName);
	}

	~KInstance()
	{
		if (m_handle)
		{
			::CloseHandle(m_handle);
			m_handle = 0;
		}
	}
};

#endif //__KINSTANCE_H__
