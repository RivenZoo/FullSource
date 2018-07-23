#ifndef KG3DSCENERESPONSEINTERFACE_H
#define KG3DSCENERESPONSEINTERFACE_H

#include "KG3DSceneResponseType.h"

class IKSREntityNotify;
struct KSRCommandArg;
interface IKEventSender;
class IKG3DSceneResponseManager
{
public:
	//////////////////////////////////////////////////////////////////////////
	// 以下方法引擎内部自己调用
	virtual HRESULT Init(IKG3DEngineManager *pEngineManager,DWORD dwOption) = 0;
	virtual void    UnInit() = 0;

	virtual HRESULT FrameMove() = 0;
	virtual BOOL    SetShowModelByEngine(BOOL bShowModelByEngine) = 0;
	virtual HRESULT OnNewScene(IKG3DScene *pScene,BOOL bForce = FALSE) = 0;
	virtual HRESULT OnDeleteScene(IKG3DScene *pScene) = 0;
		
	virtual HRESULT OnLoadScene(IKG3DScene *pScene,LPCSTR pFileName,DWORD dwOption) = 0;// 在场景物件加载前调用
	virtual HRESULT OnSaveScene(IKG3DScene *pScene,LPCSTR pFileName) = 0;    

	virtual HRESULT On3DEntityDynamicload(IKG3DScene *pScene ,DWORD dwEntityID,IKSREntityNotify *pRSEntityNotify) = 0;
	virtual HRESULT On3DEntityDynamicUnload(IKG3DScene *pScene,DWORD dwEntityID) = 0;

	virtual HRESULT RegisterEmptySMTemplate(IKG3DScene *pScene,LPCSTR pszEntityStateData,DWORD *pdwID) = 0;
	virtual HRESULT RegisterSMTempalte(IKG3DScene* pScene,LPCSTR pszEntityStateData,DWORD dwOption ,DWORD *pdwID) = 0;
	virtual HRESULT AttachSMTemplate(IKG3DScene* pScene,DWORD dwEntityID, DWORD dwID) = 0;

	virtual HRESULT OnNew3DEntity(IKG3DScene* pScene,DWORD *pdwEntityID) = 0;
	virtual HRESULT OnNew3DEntityByID(IKG3DScene *pScene,DWORD dwEntityID) = 0;
	virtual HRESULT OnRemove3DEntity(IKG3DScene *pScene,DWORD dwEntityID) = 0;
	
	virtual HRESULT OnDataFunction(IKG3DScene *p3DScene,KSRCommandArg *pCommandArg) = 0;
	virtual HRESULT OnAction(IKG3DScene* p3DScene,KSRCommandArg* pCommandArg) = 0;

	virtual HRESULT CreateModelByStateFile(LPCSTR pszStateFile,IKG3DModel** ppModel,std::vector<IKG3DModel*>& VecSubModels, BOOL bSync) = 0;
	virtual HRESULT CreateModelByStateFile(LPCSTR pszStateFile,int nStateID,IKG3DModel** ppModel,std::vector<IKG3DModel*>& VecSubModels, BOOL bSync) = 0;

	virtual HRESULT GetModelByStateID(LPCSTR pszStateFile, int nStateID, IKG3DModel** ppModel, BOOL bSync) = 0;
	virtual HRESULT GetStateIDList(LPCSTR pszStateFile, int *pnIDList, int *pnNum) = 0;
	virtual HRESULT GetStartStateID(LPCSTR pszStateFile, int *pStartStateID) = 0;
	virtual HRESULT GetEndStateID(LPCSTR pszStateFile, int *pEndStateID) = 0;

	//PVS状态机ID
	virtual void ComposeEntityIDInPVS(DWORD* pComposeID, DWORD dwPVSID, DWORD dwEntityIndex) = 0;
	virtual void DecomposeEntityIDInPVS(DWORD* pPVSID, DWORD* pEntityIndex, DWORD dwComposeID) = 0;
	virtual BOOL IsEntityInPVS(DWORD dwEntityID) = 0;

	virtual HRESULT SetEventSender(IKEventSender *pSender) = 0;
	
	
	//////////////////////////////////////////////////////////////////////////
	
	virtual HRESULT GetSREntityTransformation(IKG3DScene *pScene,DWORD dwEntityID,
		D3DXVECTOR3 *pTrans,D3DXVECTOR3 *pScal,D3DXQUATERNION *pRotation) = 0;

	virtual HRESULT GetSREntityIDList(IKG3DScene *pScene,int *pnSREntityIdList,int *pnSREntityNum) = 0;
	
	virtual BOOL SetEntityValue(IKG3DScene* pScene,DWORD dwEntityID,int nPropertyID,void* pValue,DWORD dwOption = KSRSTATE_PROPERTY_OP_CHANGE) = 0;
	virtual BOOL GetEntityValue(IKG3DScene* pScene,DWORD dwEntityID,int nPropertyID, void* pValue) = 0;

	virtual HRESULT OnCommand(IKG3DScene *pScene,DWORD dwEntityID,int nCommandType,void *pValue) = 0;

	virtual HRESULT GetSREntityBBox(IKG3DScene* pScene,DWORD dwEntityID,
		D3DXVECTOR3 *pvA,D3DXVECTOR3 *pVb) = 0;

	virtual HRESULT GetStateIDList(IKG3DScene* pScene,DWORD dwEntityID,int *pnIDList,int *pnIDNum) = 0;

	virtual void GetOption(KSROption *pOption) = 0;
	virtual void SetOption(KSROption* pOption) = 0;

	virtual IKG3DModel* Get3DModel(IKG3DScene* pi3DScene, DWORD dwEntityID) = 0;
};

class IKSREntityNotify
{
public:
	virtual HRESULT OnRenderModelChange(IKG3DModel *pModel) = 0;
};

typedef IKG3DSceneResponseManager* (*fnGetSceneResponseManager)();

#ifdef KG3DSCENERESPONSE_EXPORTS
#define DLLSCENERESPONSE_API extern "C" __declspec(dllexport)
#else
#define DLLSCENERESPONSE_API extern "C" __declspec(dllimport)
#endif

#endif