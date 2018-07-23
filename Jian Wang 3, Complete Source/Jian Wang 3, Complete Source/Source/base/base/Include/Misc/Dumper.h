#ifndef _DUMPER_H_
#define _DUMPER_H_

#ifdef DUMPER_EXPORTS
    #define DUMPER_API extern "C" __declspec(dllexport)
#else
    #define DUMPER_API extern "C" __declspec(dllimport)
#endif

struct DUMPER_PARAMETER
{
    TCHAR szIP[IP_LENGTH];
    int   nPort;
    TCHAR szProductVersion[VERSION_LENGTH];
};

DUMPER_API int SetDumperParameter(const DUMPER_PARAMETER *pDumperParam);
typedef int (*fnSetDumperParameter)(const DUMPER_PARAMETER *pDumperParam);

#endif //_DUMPER_H_