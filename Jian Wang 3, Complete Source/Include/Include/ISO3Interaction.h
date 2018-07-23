////////////////////////////////////////////////////////////////////////////////
//
//  FileName    : ISO3Interaction.h
//  Version     : 1.0
//  Creator     : Hu Changyin
//  Create Date : 2008-09-26 14:40:49
//  Comment     : 
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _INCLUDE_ISO3INTERACTION_H_
#define _INCLUDE_ISO3INTERACTION_H_

////////////////////////////////////////////////////////////////////////////////

typedef void (*fnSendResult)(char *pszName, int nResult);
typedef void (*fnRequestResult)(char *pszName, int nResult, BYTE *pbyBuffer, DWORD dwBufferSize);

class ISO3Interaction
{
public:
	virtual int Init() = 0;
	virtual void Exit() = 0;
	virtual void Active() = 0;

	virtual void Clear() = 0;
	virtual int AddParam(const char * pcszParamName, const char * pcszValue, BOOL bFile) = 0;
	virtual int Send(
        const char* pcszName,
        const char* pcszAddress,
        const char* pcszObjectName,
        const char* pcszVerb,
        int nPort,
        fnSendResult fnResult
    ) = 0;
	virtual int Request(
        const char* pcszName,
        const char* pcszAddress,
        const char* pcszObjectName,
        const char* pcszVerb,
        int nPort,
        fnRequestResult fnResult
    ) = 0;
};

#define	FN_CREATE_SO3INTERACTION	"CreateSO3Interaction"
typedef ISO3Interaction*	(*fnCreateSO3Interaction)();

#ifdef SO3INTERACTION_EXPORTS
extern "C" __declspec(dllexport) ISO3Interaction* CreateSO3Interaction();
#else
extern "C" __declspec(dllimport) ISO3Interaction* CreateSO3Interaction();
#endif

#endif //_INCLUDE_ISO3INTERACTION_H_
