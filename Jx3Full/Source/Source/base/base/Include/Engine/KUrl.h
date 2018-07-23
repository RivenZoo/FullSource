//*********************************************************************
// file		: CUrl.h
// author	: wangbin
// url		: http://www.codeproject.com/internet/urlnewwindow.asp#xx554258xx
// datetime	: 2004-07-05
// comment	: 在已有浏览器窗口或者新的浏览器窗口中打开指定URL。windows平台适用
//*********************************************************************
#ifndef __ENGINE_CURL_H__
#define __ENGINE_CURL_H__

#ifdef WIN32
#include <assert.h>
#include <shellapi.h>

class KUrl
{
private:
	// The default browser
	char	m_szBrowser[MAX_PATH];
public:
	KUrl()
	{
		memset(m_szBrowser, 0, sizeof(m_szBrowser));
	}

	// Open a URL
	void Open(LPCTSTR lpszURL, bool bNewWindow = true)
	{
		if (bNewWindow)
			::ShellExecute(NULL, NULL, GetBrowser(), lpszURL, NULL, SW_SHOWNORMAL);
		else
			::ShellExecute(NULL, NULL, lpszURL, NULL, NULL, SW_SHOWNORMAL);
	}

	// Get the default browser from the registry
	LPCTSTR GetBrowser(void)
	{
		// Have we already got the browser?
		if ( m_szBrowser[0] != '\0' )
			return m_szBrowser;
		// Get the default browser from HKCR\http\shell\open\command
		HKEY hKey = NULL;
		char szBrowse[MAX_PATH+64];
		// Open the registry
		if (::RegOpenKeyEx(HKEY_CLASSES_ROOT, "http\\shell\\open\\command",
			0, KEY_READ, &hKey) == ERROR_SUCCESS)
		{
			// Data size
			DWORD cbData = 0;

			// Get the default value
			if (::RegQueryValueEx(hKey, NULL, NULL, NULL, NULL, &cbData) == ERROR_SUCCESS && cbData > 0)
			{
				if (::RegQueryValueEx(hKey, NULL, NULL, NULL, (LPBYTE)szBrowse, &cbData) != ERROR_SUCCESS)
				{
					::RegCloseKey(hKey);
					return "";
				}
			}

			::RegCloseKey(hKey);
		}

		char* pTemp = strrchr(szBrowse, '.');
		if ( pTemp != NULL && (strnicmp(pTemp+1, "exe", strlen("exe")) == 0) )
		{
			*(pTemp+4) = '\0';
			if (*(szBrowse) == '"')
				strcpy(m_szBrowser, szBrowse+1);
			else
				strcpy(m_szBrowser, szBrowse);
			return m_szBrowser;
		}

		return "";
	}
};

#endif	//WIN32
#endif	//__ENGINE_CURL_H__
