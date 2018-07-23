#pragma once

#include "../../../Include/kg3dengine/kg3dinterface.h"
#include "KG3DTemplates.h"
#include "KG3DSceneEntityGroup.h"

class KG3DSceneEntityGroupTable : public
	TKG3DResourceManagerBase<KG3DSceneEntityGroup>
{
public:
	KG3DSceneEntityGroupTable(void);
public:
	virtual ~KG3DSceneEntityGroupTable(void);

	// Inherited via TKG3DResourceManagerBase
	virtual HRESULT LoadResourceFromFile(const char cszFileName[], unsigned uFileNameHash, unsigned uOption, IKG3DResourceBase ** ppRetResource, bool bSyncLoad = true, ResNodeState ** res_node_state = NULL) override;
	virtual HRESULT LoadAnimationFromFile(const char cszFileName[], void ** ppRet) override;
	virtual HRESULT UnloadAnimation(void * pResource) override;
	virtual HRESULT LoadTagAnimationFromFile(const char cszFileName[], void ** ppRet) override;
	virtual HRESULT UnloadTagAnimation(void * pResource) override;
	virtual HRESULT LoadResourceFromFile(const char cszFileName[], unsigned uFileNameHash, unsigned uOption, HANDLE * pRetHandle) override;
	virtual MODEL_LOAD_STATE GetResourceLoadState(HANDLE hResourceHandle) override;
	virtual HRESULT GetResourceByHandle(HANDLE hResourceHandle, IKG3DResourceBase ** ppRetResource) override;
	virtual void CloseResourceHandle(HANDLE hResourceHandle) override;
};

extern KG3DSceneEntityGroupTable g_cSceneEntityGroupTable;

