#include "StdAfx.h"
#include "kg3dscenetable.h"
#include "kg3dscenesceneeditor.h"
#include "kg3dscenemodeleditor.h"
#include "kg3dsceneobjecteditor.h"
#include "kg3dscenesfxeditor.h"
#include "KG3DSceneClient.h"
#include "KG3DSceneDataFlowEditor.h"
#include "KG3DScenePvsEditor.h"

#ifdef _DEBUG
#define new DEBUG_NEW_3DENGINE
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

KG3DSceneTable g_cSceneTable;

KG3DSceneTable::KG3DSceneTable(void)
{
	//int i = 0;
}

KG3DSceneTable::~KG3DSceneTable(void)
{
}

HRESULT KG3DSceneTable::LoadResourceFromFile(const char cszFileName[], unsigned uFileNameHash, unsigned uOption, IKG3DResourceBase ** ppRetResource, bool bSyncLoad, ResNodeState ** res_node_state)
{
	return E_NOTIMPL;
}

HRESULT KG3DSceneTable::LoadAnimationFromFile(const char cszFileName[], void ** ppRet)
{
	return E_NOTIMPL;
}

HRESULT KG3DSceneTable::UnloadAnimation(void * pResource)
{
	return E_NOTIMPL;
}

HRESULT KG3DSceneTable::LoadTagAnimationFromFile(const char cszFileName[], void ** ppRet)
{
	return E_NOTIMPL;
}

HRESULT KG3DSceneTable::UnloadTagAnimation(void * pResource)
{
	return E_NOTIMPL;
}

HRESULT KG3DSceneTable::LoadResourceFromFile(const char cszFileName[], unsigned uFileNameHash, unsigned uOption, HANDLE * pRetHandle)
{
	return E_NOTIMPL;
}

MODEL_LOAD_STATE KG3DSceneTable::GetResourceLoadState(HANDLE hResourceHandle)
{
	return MODEL_LOAD_STATE();
}

HRESULT KG3DSceneTable::GetResourceByHandle(HANDLE hResourceHandle, IKG3DResourceBase ** ppRetResource)
{
	return E_NOTIMPL;
}

void KG3DSceneTable::CloseResourceHandle(HANDLE hResourceHandle)
{
}

HRESULT KG3DSceneTable::Get1NewResourcePointer(KG3DScene** ppT, DWORD dwType, DWORD_PTR Option)
{
	HRESULT hRetCode = E_FAIL;

	KG_PROCESS_ERROR(ppT);

	switch(dwType) 
	{
	case SCENETYPE_DEFAULT:
		(*ppT) = new KG3DScene;
		break;
	case SCENETYPE_SCENEEDITOR:
		(*ppT) = new KG3DSceneSceneEditor;
		break;
	case SCENETYPE_MODELEDITOR:
		(*ppT) = new KG3DSceneModelEditor;
		break;
	case SCENETYPE_OBJECTEDITOR:
		(*ppT) = new KG3DSceneObjectEditor;
		break;
	case SCENETYPE_SFXEDITOR:
		(*ppT) = new KG3DSceneSFXEditor;
		break;
	case SCENETYPE_CLIENT:
		(*ppT) = NULL;
//		(*ppT) = new KG3DSceneClient;
		break;
	case SCENETYPE_DATAFLOWEDITOR:
		(*ppT) = new KG3DSceneDataFlowEditor;
		break;
    case SCENETYPE_PVSEDITOR :
        (*ppT) = new KG3DScenePvsEditor;
        break;
	default:
		(*ppT) = NULL;
		break;
	}

	KGLOG_PROCESS_ERROR((*ppT));

	(*ppT)->Init();
	(*ppT)->SetType(dwType);

	hRetCode = S_OK;
Exit0:
	return hRetCode;
}

HRESULT KG3DSceneTable::AutoReload()
{
	list<KG3DScene*>::iterator i = m_listExclusiveRes.begin();
	list<KG3DScene*>::iterator iend = m_listExclusiveRes.end();
	while (i!=iend)
	{
		KG3DScene* pScene = *i;
		pScene->AutoReleadModifiedResource();
		i++;
	}
	return S_OK;
}
