#pragma once

#include "KG3DInterface.h"

enum ObjCullFlags
{
	OCCLUDER        = (1<<0), /*!< The object is an occluder. */
	TARGET          = (1<<1), /*!< The object can be occluded. */
	GATE            = (1<<2), /*!< The object is a gate which can be opened and closed at runtime. */
	VOLUME          = (1<<3)  /*!< The object's entire interior volume acts as a target. */
};
enum ObjTriangleWinding
{
	Tri_WINDING_CCW,        /*!< counterclockwise */
	Tri_WINDING_CW,         /*!< clockwise */
	Tri_WINDING_TWO_SIDED   /*!< double-sided triangles */
};

enum class KG3DCullSystemType
{
	Umbra,
};

enum class KG3DCullResultType
{
	Enumerator,
	Debuger,
};

enum class KG3DCullVisType
{
	Portal,
	Frustum,
};

enum class KG3DCullSystemInterfaceType
{
	IKG3DCullSystemQuery,
	IKG3DCullSystemImporter,
};

interface IKG3DCullSystemModel
{
	;
};

interface IKG3DCullSystemObject
{
	;
};

namespace detail
{
	struct KG3DCullNode
	{
		KG3DCullNode()
			: MappedId(0)
			, ObjHandle(0)
			, ObjType(0)
			, Reserve(0)
		{

		}

		KG3DCullNode(UINT mappedId, UINT objHandle, DWORD objType, UINT modelIndex)
			: MappedId(mappedId)
			, ObjHandle(objHandle)
			, ObjType(objType)
			, Reserve(modelIndex)
		{

		}

		UINT	MappedId;
		UINT	ObjHandle;
		DWORD	ObjType;
		UINT	Reserve;
	};
};

interface IKG3DCullSystemEnumerator
{
	typedef detail::KG3DCullNode const& ItemType;

	virtual ItemType Item() = 0;
	virtual BOOL AtEnd() = 0;
	virtual void MoveNext() = 0;
	virtual UINT Count() = 0;
};

interface IKG3DCullSystemDebuger
{
	virtual HRESULT GetOccluBufferDesc(int& nWidth, int& nHeight, int& nStride, DWORD& dwFormat) = 0;
	virtual HRESULT GetOccluBuffer(void** ppData) = 0;
	virtual HRESULT RenderDebugInfo(IKG3DGraphicsTool* pGraphicsTool) = 0;
};

interface IKG3DCullSystemExporter
{
	virtual void Release() = 0;

	virtual IKG3DCullSystemModel* ExportGeomData(const float* vertices, const WORD* indices, int vertexCount, int triangleCount) = 0;
	virtual HRESULT ExportModelObject(IKG3DCullSystemModel* pModel, D3DXMATRIX const& transform, int id, int flags, int winding) = 0;
	virtual HRESULT ExportViewVolume(float* volume, int id) = 0;
	virtual HRESULT ExportIndexMap(UINT mappedID, UINT handle, DWORD type, UINT reserve) = 0;
	virtual BOOL BeginCalculation(IIniFile* param) = 0;
	virtual BOOL UpdateCalculation(std::size_t& step, float& progress) = 0;
	virtual HRESULT Serialization(LPCTSTR file) = 0;
};

interface IKG3DCullSystem
{
	virtual void Release() = 0;
	virtual HRESULT QueryInterface(KG3DCullSystemInterfaceType type, void** pInterface) = 0;
	virtual HRESULT GetExporter(IKG3DCullSystemExporter** ppExporter) = 0;
	virtual BOOL GetRunningFlag() = 0;
};

interface IKG3DCullSystemFactory
{
	virtual void Release() = 0;
	virtual HRESULT CreateCullSystem(IKG3DCullSystem** ppCullSystem, KG3DCullSystemType type) = 0;
};

interface IKG3DCullSystemQuery
{
	virtual void UpdateCamera(D3DXVECTOR3 &vPos,D3DXMATRIX& matView,float fFOV,float fAspect,float ZNear,float ZFar) = 0;
	virtual HRESULT QueryVisibility() = 0;
	virtual HRESULT GetQueryResult(KG3DCullResultType type, void** ppResultInterface) = 0;
};

interface IKG3DCullSystemImporter
{
	virtual HRESULT ResetCullData(LPCTSTR sceneName) = 0;
	virtual HRESULT UpdateCullData(int* begin, int* end, DWORD renderCount) = 0;
};

IKG3DCullSystem* GetCullSystemEx();