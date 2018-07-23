#pragma  once
#include "json/json.h"

#ifdef KG3DFILESYNC_EXPORTS
#define KG3DFILESYNC_API __declspec(dllexport)
#else
#define KG3DFILESYNC_API __declspec(dllimport)
#endif





struct IKG3DJsonFileEventConnection
{
	virtual HRESULT OnJsonFileChange(LPSTR pFileName,UINT uID) = 0;
	virtual HRESULT OnJsonMemoryChange(LPSTR pJsonFile,UINT uID) = 0;
};

struct KG3DJsonFileHelper
{
	Json::Value  m_Json;
	FILETIME     m_JsonFileTime;
	std::string  m_szJsonFileName;
	IKG3DJsonFileEventConnection* m_pEventConnection;
	UINT         m_uUserID;
};

struct IKG3DFileSynchronization
{
	virtual KG3DJsonFileHelper* RequestJsonHelper(LPSTR pFileName) = 0;
	//virtual HRESULT ModifyJsonFile(KG3DJsonFileHelper* pFile) = 0;

	virtual HRESULT SendJsonFileChange(const char[]) = 0;
	virtual HRESULT SendJsonMemoryChanged(KG3DJsonFileHelper* pFile) = 0;

	virtual HRESULT Init() = 0;
	virtual HRESULT Uninit() = 0;

	virtual HRESULT Activate() = 0;

	virtual HRESULT SaveJsonFile(KG3DJsonFileHelper* pFile ) = 0;
	virtual HRESULT LoadJsonFile(KG3DJsonFileHelper* pFile ) = 0;

	virtual HRESULT CheckFileChange() = 0;
};


#define	FN_CREATE_KG3DFILESYNC	"CreateFileSync"
typedef IKG3DFileSynchronization*	(*fnCreateFileSync)();

extern "C" KG3DFILESYNC_API IKG3DFileSynchronization* CreateFileSync();
