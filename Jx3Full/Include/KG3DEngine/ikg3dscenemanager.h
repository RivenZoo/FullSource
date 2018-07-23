#pragma once 
#include "IKG3DActor.h"

enum KG3DACTOR_CLASSS
{
	ACTORCLASS_ENV,
	ACTORCLASS_FAR,
	ACTORCLASS_NORMAL,
	ACTORCLASS_CAMERASPACE,
	ACTORCLASS_LAST,
	ACTORCLASS_COUNT,
};

enum SCENENODE_TREETYPE //子节点的分割方式
{
	TREETYPE_NONE,
	TREETYPE_1D,
	TREETYPE_2D,
	TREETYPE_3D,
};
class BBox;
typedef BBox* LPAABBOX;
typedef BBox AABBOX;

interface IKG3DSceneItem
{
	virtual AABBOX* GetBBox() = 0;
};

interface IKG3DSceneNode
{
	virtual int GetNumSubNode() = 0;
	virtual HRESULT GetNumSubNodeEx(int* pX,int* pY,int* pZ) = 0;//得到子节点数目

	virtual IKG3DSceneNode* GetSubNode(int nIndex) = 0;
	virtual SCENENODE_TREETYPE GetTreeType() = 0;

	virtual AABBOX* GetBBox() = 0;

	virtual int GetNumSceneItem() = 0;
	virtual IKG3DSceneItem* GetSceneItem(int nIndex) = 0;
};

interface IKG3DSceneManger//场景物件管理器
{
	virtual IKG3DSceneNode* GetRootNode(KG3DACTOR_CLASSS eClass) = 0;

	virtual HRESULT StartCull() = 0;//开始裁剪
	virtual HRESULT EndCull() = 0;//结束裁剪
};

interface IEKG3DSceneManger : public IKG3DSceneManger
{
	virtual HRESULT ForceSetBBox(IKG3DSceneNode* pNode,D3DXVECTOR3 A,D3DXVECTOR3 B) = 0;

	virtual IKG3DSceneNode* NewSubNode(IKG3DSceneNode* pNode) = 0;
	virtual HRESULT DeleteSubNode(IKG3DSceneNode* pParent,IKG3DSceneNode* pNode) = 0;

	virtual HRESULT NewSubNodeEx(IKG3DSceneNode* pParent,SCENENODE_TREETYPE,int nX,int nY,int nZ) = 0;
	virtual HRESULT DeleteSubNodeEx(IKG3DSceneNode* pParent) = 0;

	virtual HRESULT ComputeBBox(IKG3DSceneNode* pNode) = 0;

	virtual HRESULT StartModify() = 0;
	virtual HRESULT EndModify() = 0;
};
