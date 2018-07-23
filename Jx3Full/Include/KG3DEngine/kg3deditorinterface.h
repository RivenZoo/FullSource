//////////////////////////////////////////////////////////////////////////////////////
//
//  FileName    :   KG3DEditorInterface.h
//  Version     :   1.0
//  Creater     :   YangLin
//  Date        :   2010/3/23 
//  Comment     :   
//
//////////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "KG3DInterface.h"

interface IEKG3DSceneCameraAnimation;
interface IEKG3DEngineManager;
enum EDITORPLUGTYPE
{
	EDITORPLUG_LOGIC = 1,
	EDITORPLUG_ACTGAME = 2,
	EDITORPLUG_SEARCH = 3,
	EDITORPLUG_PMODE = 4,
	EDITORPLUG_PLOT = 5,
	EDITORPLUG_3DENTITY = 6,
};
enum PlugCommandType
{
	PlugCT_LOGIC_ShowPoly = 1,
	PlugCT_LOGIC_NPCProperty = 2,
	PlugCT_LOGIC_TrafficPoint = 3,
	PlugCT_LOGIC_DoodadProperty = 4,
	PlugCT_LOGIC_ObjectBatchAdd = 5,
	PlugCT_LOGIC_ToggleAutoProp = 6,
	PlugCT_LOGIC_QueryAutoProp = 7,
	PlugCT_LOGIC_GetHwndFromTopView = 8,
	PlugCT_LOGIC_ReturnGroundHeight2TopView = 9,
	PlugCT_LOGIC_SelectBatchElementObj = 10,
	PlugCT_LOGIC_QueryPosition = 11,
	PlugCT_LOGIC_ShowWayPoint = 12,
	PlugCT_LOGIC_ShowTrafficPoint = 13,
	PlugCT_LOGIC_NpcNickNameBatchEdit = 14,
	PlugCT_LOGIC_NpcPatrolPathBatchEdit = 15,
	PlugCT_LOGIC_DoodadNickNameBatchEdit = 16,
	PlugCT_LOGIC_MarkNpcWayPointSet = 17,
	PlugCT_LOGIC_ResetWayPointSetMark = 18,
};
interface IKG3DEditorPlug
{
	virtual HRESULT Init(IEKG3DEngineManager* pEngineManager) = 0;
	virtual HRESULT UnInit() = 0;
	virtual HRESULT SetStartupDir(LPSTR szStartupDir) = 0;
	virtual LPSTR   GetPlugName() = 0;

	//////////////////////////////////////////////////////////////////////////
	virtual HRESULT OnOpenFile(LPSTR pFileName) = 0;
	virtual HRESULT OnSaveFile(LPSTR pFileName) = 0;
	virtual HRESULT OnCloseFile() = 0;

	virtual HRESULT Set3DScene(IKG3DResourceManager* pModelMgr,IKG3DScene * pScene) = 0;
	virtual HRESULT SetIECameraAnimation(IEKG3DSceneCameraAnimation* pAni) = 0;

	//////////////////////////////////////////////////////////////////////////
	virtual HRESULT FrameMove() = 0;
	virtual HRESULT OnRenderMainWnd() = 0;
	virtual INT ExecAction(INT nActionID, INT nExecState, WPARAM wParam, LPARAM lParam) = 0;
	virtual HRESULT ExecuteCommand( LPCTSTR strIC, LPCTSTR szRet) = 0;
	virtual HRESULT OnCommand(PlugCommandType CommandType, DWORD_PTR param1, DWORD_PTR param2) = 0;
	//virtual HRESULT GetIEditorPlug(EDITORPLUGTYPE dwType,void** ppEditorPlug) = 0;
	virtual EDITORPLUGTYPE Type() = 0;
	virtual HRESULT GetDialogPanel(void** ppDialog) = 0;
	virtual BOOL DllPreTranslateMessage(MSG* pMsg) = 0;
};

interface IKG3DEnginePlug
{
	virtual HRESULT OnEngineInit(IKG3DEngineManager* pEngineManager) = 0;
	virtual HRESULT OnEngineUninit() = 0;

	virtual HRESULT OnLostDevice() = 0;
	virtual HRESULT OnRestDevice() = 0;

	virtual HRESULT OnEngine_BeforeFrameMove() = 0;
	virtual HRESULT OnEngine_AfterFrameMove() = 0;

	virtual HRESULT OnSceneFrameMove(IKG3DScene* pScene) = 0;

	virtual HRESULT OnSceneRender_BeforeCameraProcess(IKG3DScene* pScene) = 0;
	virtual HRESULT OnSceneRender_AfterCameraProcess(IKG3DScene* pScene) = 0;
	virtual HRESULT OnSceneRender_BeforeEaryZ(IKG3DScene* pScene) = 0;
	virtual HRESULT OnSceneRender_AfterEaryZ(IKG3DScene* pScene) = 0;
	virtual HRESULT OnSceneRender_BeforeColor(IKG3DScene* pScene) = 0;
	virtual HRESULT OnSceneRender_AfterColor(IKG3DScene* pScene) = 0;
	virtual HRESULT OnSceneRender_BeforeSFX(IKG3DScene* pScene) = 0;
	virtual HRESULT OnSceneRender_AfterSFX(IKG3DScene* pScene) = 0;
    
	virtual HRESULT OnPostSceneRender() = 0;
    virtual HRESULT OnSceneRender_AfterRenderEnd() = 0;
	virtual HRESULT ExecuteCommand(LPCTSTR szCommand) = 0;

	virtual HRESULT OnSceneInit(IKG3DScene* pScene) = 0;
	virtual HRESULT OnSceneUninit(IKG3DScene* pScene) = 0;
    virtual HRESULT SetPresentParameters(const D3DPRESENT_PARAMETERS &Par) = 0;
};

struct KG3DEnginePlugSolid : public IKG3DEnginePlug
{
	virtual HRESULT OnEngineInit(IKG3DEngineManager* pEngineManager){return E_NOTIMPL;}
	virtual HRESULT OnEngineUninit(){return E_NOTIMPL;}

	virtual HRESULT OnLostDevice(){return E_NOTIMPL;}
	virtual HRESULT OnRestDevice(){return E_NOTIMPL;}

	virtual HRESULT OnEngine_BeforeFrameMove(){return E_NOTIMPL;}
	virtual HRESULT OnEngine_AfterFrameMove(){return E_NOTIMPL;}
	virtual HRESULT OnSceneFrameMove(IKG3DScene* pScene){return E_NOTIMPL;}

	virtual HRESULT OnSceneRender_BeforeCameraProcess(IKG3DScene* pScene){return E_NOTIMPL;}
	virtual HRESULT OnSceneRender_AfterCameraProcess(IKG3DScene* pScene){return E_NOTIMPL;}
	virtual HRESULT OnSceneRender_BeforeEaryZ(IKG3DScene* pScene){return E_NOTIMPL;}
	virtual HRESULT OnSceneRender_AfterEaryZ(IKG3DScene* pScene){return E_NOTIMPL;}
	virtual HRESULT OnSceneRender_BeforeColor(IKG3DScene* pScene){return E_NOTIMPL;}
	virtual HRESULT OnSceneRender_AfterColor(IKG3DScene* pScene){return E_NOTIMPL;}
	virtual HRESULT OnSceneRender_BeforeSFX(IKG3DScene* pScene){return E_NOTIMPL;}
	virtual HRESULT OnSceneRender_AfterSFX(IKG3DScene* pScene){return E_NOTIMPL;}

	virtual HRESULT OnPostSceneRender(){return E_NOTIMPL;}
	virtual HRESULT OnSceneRender_AfterRenderEnd(){return E_NOTIMPL;}
	virtual HRESULT ExecuteCommand(LPCTSTR szCommand){return E_NOTIMPL;}

	virtual HRESULT OnSceneInit(IKG3DScene* pScene){return E_NOTIMPL;}
	virtual HRESULT OnSceneUninit(IKG3DScene* pScene){return E_NOTIMPL;}
	virtual HRESULT SetPresentParameters(const D3DPRESENT_PARAMETERS &Par){return E_NOTIMPL;}
};
