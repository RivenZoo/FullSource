#include "StdAfx.h"
#include "KG3DSceneEntityGroupTable.h"

#ifdef _DEBUG
#define new DEBUG_NEW_3DENGINE
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

KG3DSceneEntityGroupTable g_cSceneEntityGroupTable;

KG3DSceneEntityGroupTable::KG3DSceneEntityGroupTable(void)
{
}

KG3DSceneEntityGroupTable::~KG3DSceneEntityGroupTable(void)
{
}

HRESULT KG3DSceneEntityGroupTable::LoadResourceFromFile(const char cszFileName[], unsigned uFileNameHash, unsigned uOption, IKG3DResourceBase ** ppRetResource, bool bSyncLoad = true, ResNodeState ** res_node_state = NULL)
{
	return E_NOTIMPL;
}

HRESULT KG3DSceneEntityGroupTable::LoadAnimationFromFile(const char cszFileName[], void ** ppRet)
{
	return E_NOTIMPL;
}

HRESULT KG3DSceneEntityGroupTable::UnloadAnimation(void * pResource)
{
	return E_NOTIMPL;
}

HRESULT KG3DSceneEntityGroupTable::LoadTagAnimationFromFile(const char cszFileName[], void ** ppRet)
{
	return E_NOTIMPL;
}

HRESULT KG3DSceneEntityGroupTable::UnloadTagAnimation(void * pResource)
{
	return E_NOTIMPL;
}

HRESULT KG3DSceneEntityGroupTable::LoadResourceFromFile(const char cszFileName[], unsigned uFileNameHash, unsigned uOption, HANDLE * pRetHandle)
{
	return E_NOTIMPL;
}

MODEL_LOAD_STATE KG3DSceneEntityGroupTable::GetResourceLoadState(HANDLE hResourceHandle)
{
	return MODEL_LOAD_STATE();
}

HRESULT KG3DSceneEntityGroupTable::GetResourceByHandle(HANDLE hResourceHandle, IKG3DResourceBase ** ppRetResource)
{
	return E_NOTIMPL;
}

void KG3DSceneEntityGroupTable::CloseResourceHandle(HANDLE hResourceHandle)
{
}
