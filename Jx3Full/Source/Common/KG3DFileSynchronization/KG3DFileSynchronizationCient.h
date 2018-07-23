#pragma once

#include "IKG3DFileSynchronization.h"
#include "KSOEditorNetClient.h"

class KG3DFileSynchronizationCient :
	public IKG3DFileSynchronization
{
public:
	KG3DFileSynchronizationCient(void);
	virtual ~KG3DFileSynchronizationCient(void);

	virtual KG3DJsonFileHelper* RequestJsonHelper(LPSTR pFileName);

	virtual HRESULT SendJsonFileChange(const char[]);
	virtual HRESULT SendJsonMemoryChanged(KG3DJsonFileHelper* pFile);

	virtual HRESULT Init();
	virtual HRESULT Uninit();
	virtual HRESULT Activate(); 

	virtual HRESULT OnJsonFileChange(LPSTR pFileName);

	virtual HRESULT OnJsonFileChangeInMemory(LPSTR pFileName,LPSTR pJsonFile);

	virtual HRESULT SaveJsonFile(KG3DJsonFileHelper* pFile );
	virtual HRESULT LoadJsonFile(KG3DJsonFileHelper* pFile );

	virtual HRESULT CheckFileChange();

public:
	KSOEditorNetClient m_client;

	KThread m_ThreadFileTimeCheck;

	HRESULT InitThread();

	std::map<string,KG3DJsonFileHelper>m_mapJsonFile;
	KMutex m_mapLock;

protected:
	virtual HRESULT OnJsonFileChangeInMemory(KG3DJsonFileHelper* pHelper,LPSTR pJsonFile);
	virtual HRESULT OnJsonFileChange(KG3DJsonFileHelper* pHelper);

};

