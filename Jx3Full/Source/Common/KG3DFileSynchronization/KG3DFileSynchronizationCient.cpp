#include "stdafx.h"
#include "KG3DFileSynchronizationCient.h"

BOOL g_bThreadExit = FALSE;
extern KG3DFileSynchronizationCient* g_lpFileSync;

KG3DFileSynchronizationCient::KG3DFileSynchronizationCient(void)
{
}


KG3DFileSynchronizationCient::~KG3DFileSynchronizationCient(void)
{
	g_bThreadExit = TRUE;
	m_ThreadFileTimeCheck.Destroy();
}

KG3DJsonFileHelper* KG3DFileSynchronizationCient::RequestJsonHelper(LPSTR pFileName)
{
	KG3DJsonFileHelper* pOut = NULL;

	std::map<string,KG3DJsonFileHelper>::iterator iFind = m_mapJsonFile.find(pFileName);
	if(iFind == m_mapJsonFile.end() )
	{
		KG3DJsonFileHelper newHelper;

		newHelper.m_szJsonFileName = pFileName;
		newHelper.m_pEventConnection = NULL;
		newHelper.m_uUserID = 0;

		m_mapJsonFile[ pFileName ] = newHelper; 
		
		iFind = m_mapJsonFile.find(pFileName);
	}

	pOut = &iFind->second;

	return pOut;
}

/*HRESULT KG3DFileSynchronizationCient::ModifyJsonFile(KG3DJsonFileHelper* pFile)
{
	m_client.SendMessage(pFile->m_szJsonFileName.c_str());
	return S_OK;
}*/

HRESULT KG3DFileSynchronizationCient::SendJsonFileChange(const char Filename[])
{
	m_client.SendFileChange(Filename);
	return S_OK;
}

HRESULT KG3DFileSynchronizationCient::SendJsonMemoryChanged(KG3DJsonFileHelper* pFile)
{
	m_client.SendJsonFileChange(pFile);
	return S_OK;
}


HRESULT KG3DFileSynchronizationCient::OnJsonFileChange(KG3DJsonFileHelper* pHelper)
{
	if(!pHelper)
		return E_FAIL;
	if(!pHelper->m_pEventConnection)
		return E_FAIL;
	return pHelper->m_pEventConnection->OnJsonFileChange( (LPSTR)pHelper->m_szJsonFileName.c_str(), pHelper->m_uUserID);
}

HRESULT KG3DFileSynchronizationCient::OnJsonFileChangeInMemory(KG3DJsonFileHelper* pHelper,LPSTR pJsonFile)
{
	if(!pHelper)
		return E_FAIL;
	
	Json::Reader reader;
	reader.parse(pJsonFile, pHelper->m_Json);

	if(!pHelper->m_pEventConnection)
		return E_FAIL;
	return pHelper->m_pEventConnection->OnJsonMemoryChange( pJsonFile, pHelper->m_uUserID);
}

HRESULT KG3DFileSynchronizationCient::OnJsonFileChange(LPSTR pFileName)
{
	std::map<string,KG3DJsonFileHelper>::iterator iFind = m_mapJsonFile.find(pFileName);
	if(iFind != m_mapJsonFile.end() )
	{
		KG3DJsonFileHelper* pHelper = &iFind->second;
		return OnJsonFileChange(pHelper);
	}
	return E_FAIL;
}

HRESULT KG3DFileSynchronizationCient::OnJsonFileChangeInMemory(LPSTR pFileName,LPSTR pJsonFile)
{
	std::map<string,KG3DJsonFileHelper>::iterator iFind = m_mapJsonFile.find(pFileName);
	if(iFind != m_mapJsonFile.end() )
	{
		KG3DJsonFileHelper* pHelper = &iFind->second;
		return OnJsonFileChangeInMemory(pHelper,pJsonFile);
	}
	return E_FAIL;
}


HRESULT KG3DFileSynchronizationCient::Init()
{
	//m_client.Init();
	//InitThread();
	return S_OK;
}

HRESULT KG3DFileSynchronizationCient::Uninit()
{
	//m_client.Uninit();
	delete this;
	g_lpFileSync = NULL;
	return S_OK;
}

HRESULT KG3DFileSynchronizationCient::Activate()
{
	//m_client.Activate();
	return S_OK;
}

void g_MultiThreadFileCheck(void * pInput)        //多线程加载主函数
{
	KG3DFileSynchronizationCient* pClient = (KG3DFileSynchronizationCient*)(pInput);
	while (!g_bThreadExit)
	{

		pClient->Activate();

		Sleep(1000);
	}
};

HRESULT KG3DFileSynchronizationCient::InitThread()
{
	m_ThreadFileTimeCheck.Create(g_MultiThreadFileCheck,this);
	return S_OK;
}


BOOL GetModifyTime(LPCTSTR szPath, FILETIME &modifyTime)
{
	HANDLE hFile = ::CreateFile(
		szPath,
		GENERIC_READ,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		NULL,
		OPEN_EXISTING,
		0,
		NULL
		);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}

	::GetFileTime(hFile, NULL, NULL, &modifyTime);
	CloseHandle(hFile);

	return TRUE;
}

HRESULT KG3DFileSynchronizationCient::SaveJsonFile(KG3DJsonFileHelper* pHelper )
{
	if(!pHelper)
		return E_FAIL;

	LPSTR pFileName = (LPSTR)pHelper->m_szJsonFileName.c_str();

	Json::StyledWriter writer;
	string rewrite = writer.write( pHelper->m_Json );
	FILE *fout = fopen( pFileName, "wt" );
	if ( !fout )
	{
		printf( "Failed to create rewrite file: %s\n", pFileName );
		return E_FAIL;
	}
	fprintf( fout, "%s\n", rewrite.c_str() );
	fclose( fout );

	GetModifyTime(pFileName,pHelper->m_JsonFileTime);

	return S_OK;
}

HRESULT KG3DFileSynchronizationCient::LoadJsonFile(KG3DJsonFileHelper* pHelper )
{
	if(!pHelper)
		return E_FAIL;

	FILE *file = fopen( pHelper->m_szJsonFileName.c_str(), "rb" );
	if ( !file )
		return E_FAIL;

	fseek( file, 0, SEEK_END );
	long size = ftell( file );
	fseek( file, 0, SEEK_SET );

	char *buffer = new char[size+1];
	buffer[size] = 0;

	fread( buffer, 1, size, file );

	fclose( file );

	Json::Reader reader;

	reader.parse(buffer, pHelper->m_Json);

	delete[] buffer;

	return S_OK;
}

HRESULT KG3DFileSynchronizationCient::CheckFileChange()
{
	vector<KG3DJsonFileHelper*>vecChange;

	m_mapLock.Lock();
	std::map<string,KG3DJsonFileHelper>::iterator i = m_mapJsonFile.begin();
	std::map<string,KG3DJsonFileHelper>::iterator iend = m_mapJsonFile.end();
	while (i!=iend)
	{
		KG3DJsonFileHelper* pHelper = &i->second;

		FILETIME newTime;
		GetModifyTime(pHelper->m_szJsonFileName.c_str(),newTime);

		if(newTime.dwHighDateTime != pHelper->m_JsonFileTime.dwHighDateTime ||
			newTime.dwLowDateTime != pHelper->m_JsonFileTime.dwLowDateTime)
		{
			vecChange.push_back(pHelper);
		}

		i++;
	}
	m_mapLock.Unlock();
	//////////////////////////////////////////////////////////////////////////
	for (size_t i=0;i<vecChange.size();i++)
	{
		KG3DJsonFileHelper* pHelper = vecChange[i];
		if(pHelper->m_pEventConnection)
		{
			pHelper->m_pEventConnection->OnJsonFileChange(
				(LPSTR)pHelper->m_szJsonFileName.c_str(),
				pHelper->m_uUserID);
		}
	}
	return S_OK;
}
