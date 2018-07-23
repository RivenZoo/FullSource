#ifndef KJX3UIDEFINE_H
#define KJX3UIDEFINE_H

enum { CODE_PAGE_GBK = 936 };

struct KJX3Config
{
    BOOL bConsole;
    BOOL bPakFirst;
    BOOL bPriorExeRootPath;
    BOOL bUTF8;
};

struct KJX3Version
{
	char szVersionEx[32];
	char szVersionLineFullName[64];
	char szVersion[64];
	char szVersionLineName[64];
	char szAddonVersion[64];
	char szServerListUrl[512];
};

#endif // KJX3UIDEFINE_H
