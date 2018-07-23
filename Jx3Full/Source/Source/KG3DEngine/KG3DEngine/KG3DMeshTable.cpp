#include "StdAfx.h"
#include "kg3dmeshtable.h"
#include "../../../Include/kg3dengine/KG3DTypes.h"
#include "kg3dsfx.h"

#ifdef _DEBUG
#define new DEBUG_NEW_3DENGINE
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

KG3DMeshTable g_cMeshTable;
static TypeInfo s_MeshTableTypes[] = { 
	{".mesh", MESHTYPE_DEFAULT, FALSE},
	{".blade", MESHTYPE_BLADE, TRUE},
	{".stree", MESHTYPE_SPEEDTREE, TRUE},
	{".scene", MESHTYPE_TERRAIN, FALSE}
};

KG3DMeshTable::KG3DMeshTable(void)
{
	m_dwReleaseQueueSize = 200;
}

KG3DMeshTable::~KG3DMeshTable(void)
{
}

HRESULT KG3DMeshTable::Init()
{
	HRESULT hRetCode = TKG3DResourceManagerBase<KG3DMesh>::Init();
	m_RefTable = s_MeshTableTypes;
	m_pDefaultType = NULL;
	m_RefTableSize = sizeof(s_MeshTableTypes) / sizeof(TypeInfo);
	return hRetCode;
}
HRESULT KG3DMeshTable::UnInit()
{
	return TKG3DResourceManagerBase<KG3DMesh>::UnInit();
}

HRESULT KG3DMeshTable::Get1NewResourse(IKG3DResourceBase** ppResource,DWORD dwType)
{
	return TKG3DResourceManagerBase<KG3DMesh>::Get1NewResource((KG3DMesh**)(ppResource), dwType, 0);
}
HRESULT KG3DMeshTable::GetResourse(IKG3DResourceBase** ppResource,DWORD dwID)
{
	return TKG3DResourceManagerBase<KG3DMesh>::GetResource((KG3DMesh**)ppResource,dwID);
}
//////////////////////////////////////////////////////////////////////////
HRESULT KG3DMeshTable::SetBalance(DWORD nSizeMemery,DWORD nSzieVideo)
{
	return S_OK;
}

void KG3DMeshTable::ChangeMesh2CpuProcess()
{
    for (map<DWORD, KG3DMesh*>::iterator i = m_mapResource.begin();
        i != g_cMeshTable.m_mapResource.end(); ++i) 
    {
        KG3DMesh* mesh = i->second;
        
        if (mesh)
            mesh->CreateDataForCpuProcess();
    }
}

HRESULT KG3DMeshTable::Get1NewResourcePointer(KG3DMesh** ppT, 
											  DWORD dwType, 
											  DWORD_PTR Option)
{
	HRESULT hRetCode = E_FAIL;
	KG_PROCESS_ERROR(ppT);

	switch(dwType)
	{
	case MESHTYPE_DEFAULT:
		(*ppT) = new KG3DMesh;
		break;
	default:
		{
			ASSERT(0);
			break;
		}
	}
	KG_PROCESS_ERROR(*ppT);
	(*ppT)->Init();
	(*ppT)->SetType(dwType);
	
	hRetCode = S_OK;
Exit0:
	if (FAILED(hRetCode))
	{
		KGLogPrintf(KGLOG_ERR, "KG3DMeshTable::¥¥Ω®Mesh ß∞‹.");
	}
	return hRetCode;
}

HRESULT KG3DMeshTable::LoadResourceFromFile(const char cszFileName[], unsigned uFileNameHash, unsigned uOption, IKG3DResourceBase ** ppRetResource, bool bSyncLoad = true, ResNodeState ** res_node_state = NULL)
{
	return E_NOTIMPL;
}

HRESULT KG3DMeshTable::LoadAnimationFromFile(const char cszFileName[], void ** ppRet)
{
	return E_NOTIMPL;
}

HRESULT KG3DMeshTable::UnloadAnimation(void * pResource)
{
	return E_NOTIMPL;
}

HRESULT KG3DMeshTable::LoadTagAnimationFromFile(const char cszFileName[], void ** ppRet)
{
	return E_NOTIMPL;
}

HRESULT KG3DMeshTable::UnloadTagAnimation(void * pResource)
{
	return E_NOTIMPL;
}

HRESULT KG3DMeshTable::LoadResourceFromFile(const char cszFileName[], unsigned uFileNameHash, unsigned uOption, HANDLE * pRetHandle)
{
	return E_NOTIMPL;
}

MODEL_LOAD_STATE KG3DMeshTable::GetResourceLoadState(HANDLE hResourceHandle)
{
	return MODEL_LOAD_STATE();
}

HRESULT KG3DMeshTable::GetResourceByHandle(HANDLE hResourceHandle, IKG3DResourceBase ** ppRetResource)
{
	return E_NOTIMPL;
}

void KG3DMeshTable::CloseResourceHandle(HANDLE hResourceHandle)
{
}
