#include "StdAfx.h"
#include "kg3dmaterialtable.h"

#ifdef _DEBUG
#define new DEBUG_NEW_3DENGINE
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

KG3DMaterialTable g_cMaterialTable;
static TypeInfo s_MaterialTableDefault = {"", 0, FALSE };
KG3DMaterialTable::KG3DMaterialTable(void)
{
	m_dwReleaseQueueSize = 80;
}

KG3DMaterialTable::~KG3DMaterialTable(void)
{
}

HRESULT KG3DMaterialTable::Init()
{
	HRESULT hRetCode = TKG3DResourceManagerBase<KG3DMaterial>::Init();
	m_RefTable = NULL;
	m_RefTableSize = 0;
	m_pDefaultType = &s_MaterialTableDefault;
	return hRetCode;
}

HRESULT KG3DMaterialTable::LoadResourceFromFile(const char cszFileName[], unsigned uFileNameHash, unsigned uOption, IKG3DResourceBase ** ppRetResource, bool bSyncLoad = true, ResNodeState ** res_node_state = NULL)
{
	return E_NOTIMPL;
}

HRESULT KG3DMaterialTable::LoadAnimationFromFile(const char cszFileName[], void ** ppRet)
{
	return E_NOTIMPL;
}

HRESULT KG3DMaterialTable::UnloadAnimation(void * pResource)
{
	return E_NOTIMPL;
}

HRESULT KG3DMaterialTable::LoadTagAnimationFromFile(const char cszFileName[], void ** ppRet)
{
	return E_NOTIMPL;
}

HRESULT KG3DMaterialTable::UnloadTagAnimation(void * pResource)
{
	return E_NOTIMPL;
}

HRESULT KG3DMaterialTable::LoadResourceFromFile(const char cszFileName[], unsigned uFileNameHash, unsigned uOption, HANDLE * pRetHandle)
{
	return E_NOTIMPL;
}

MODEL_LOAD_STATE KG3DMaterialTable::GetResourceLoadState(HANDLE hResourceHandle)
{
	return MODEL_LOAD_STATE();
}

HRESULT KG3DMaterialTable::GetResourceByHandle(HANDLE hResourceHandle, IKG3DResourceBase ** ppRetResource)
{
	return E_NOTIMPL;
}

void KG3DMaterialTable::CloseResourceHandle(HANDLE hResourceHandle)
{
}

