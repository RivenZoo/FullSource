/*****************************************************************************************
//  无贴图的图形资源管理
//	Copyright : Kingsoft 2002-2003
//	Author	: Wooy(Wu yue)
//	CreateTime:	2002-11-11
*****************************************************************************************/
#include "Precompile.h"
#include "ObjCache.h"
#include "File.h"
#ifdef __linux
	#include <sys/times.h>
#endif


static int DefObjCacheLoadObjCallback(const char* pszObjName, void** ppObject)
{
	if (ppObject)
		*ppObject = NULL;
	return false;
}

static int DefObjCacheOperOnObjCallback(void* pObject, void* pParam)
{
	return 0;
}

KObjCache::KObjCache()
{
	m_pObjectList = NULL;
	m_nNumReserved = 0;
	m_nNumObjs  = 0;
	m_nBalanceNum = ISBP_BALANCE_NUM_DEF;
	m_uCheckPoint = ISBP_CHECK_POINT_DEF;
	m_uObjAccessCounter = 0;
	m_fnLoadObj = NULL;
	m_fnFreeObj = NULL;
}

KObjCache::~KObjCache()
{
	FreeAllObj();
}

//初始化KObjCache对象,设置加载/卸载/停止对象的回调函数
void KObjCache::Init(fnObjCacheLoadObjCallback fnLoad, 
					 fnObjCacheOperOnObjCallback fnFree,
					 fnObjCacheOperOnObjCallback fnObjIsInUsing)
{
	m_fnLoadObj         = fnLoad         ? fnLoad         : DefObjCacheLoadObjCallback;
	m_fnFreeObj	        = fnFree         ? fnFree         : DefObjCacheOperOnObjCallback;
	m_fnObjIsInUsing    = fnObjIsInUsing ? fnObjIsInUsing : DefObjCacheOperOnObjCallback;
}

void KObjCache::FreeAllObj()
{
	if (m_pObjectList)
	{
		for (int i = 0; i < m_nNumObjs; i++)
		{
			if (m_pObjectList[i].pObject)
			{
				m_fnFreeObj(m_pObjectList[i].pObject, 0);
				m_pObjectList[i].pObject = NULL;
			}
		}

		free(m_pObjectList);
		m_pObjectList = NULL;
	}
	m_nNumObjs = 0;
	m_nNumReserved = 0;
	m_uObjAccessCounter = 0;
}

void KObjCache::FreeObj(const char* pszObj)
{
	unsigned int uObj = g_FileNameHash(pszObj);
	int nIdx = FindObj(uObj, 0);

	if (nIdx >= 0)
	{
		if (m_pObjectList[nIdx].pObject)
		{
			m_fnFreeObj(m_pObjectList[nIdx].pObject, 0);
			m_pObjectList[nIdx].pObject = NULL;
		}

		m_nNumObjs--;
		for (int i = nIdx; i < m_nNumObjs; i++)
			m_pObjectList[i] = m_pObjectList[i + 1];
	}
}

void KObjCache::ActionForAllObj(fnObjCacheOperOnObjCallback fnActionForAll, void* pParam)
{
	if (m_pObjectList && fnActionForAll)
	{
		for (int i = 0; i < m_nNumObjs; i++)
			if(m_pObjectList[i].pObject)
                fnActionForAll(m_pObjectList[i].pObject, pParam);
	}
}

void* KObjCache::GetObj(const char* pszObj, unsigned int& uObj, int& nObjPosition)
{
	if (uObj == 0)
	{
		if ((uObj = g_FileNameHash(pszObj)) == 0)
			return NULL;
	}

	if ((nObjPosition = FindObj(uObj, nObjPosition)) >= 0)
	{
		KObj&	obj = m_pObjectList[nObjPosition];

#ifdef WIN32
		obj.nRef = GetTickCount();
#elif __linux
		obj.nRef = times(NULL);
#endif

		//为了执行效率所以未把下面的判断放在CheckBalance函数体里面。下同。
		if (m_nNumObjs > m_nBalanceNum && (++m_uObjAccessCounter) > m_uCheckPoint)
		{
			CheckBalance();
		}
		return obj.pObject;
	}

	void* pObject = NULL;
	if (m_nNumObjs < m_nNumReserved || ExpandSpace())
	{
		nObjPosition = - nObjPosition - 1;	// FindObj时已经找好位置了
		for (int i = m_nNumObjs; i > nObjPosition; i--)
		{
			m_pObjectList[i] = m_pObjectList[i - 1];
		}
		m_nNumObjs++;
		KObj& ImgObj = m_pObjectList[nObjPosition];

#ifdef WIN32
		ImgObj.nRef = GetTickCount();
#elif __linux
		ImgObj.nRef = times(NULL);
#endif
		ImgObj.pObject = NULL;
		ImgObj.uId = uObj;
		if (m_fnLoadObj(pszObj, &pObject))
			ImgObj.pObject = pObject;
		if (m_nNumObjs > m_nBalanceNum && (++m_uObjAccessCounter) > m_uCheckPoint)
			CheckBalance();
	}
	return pObject;
}

void KObjCache::SetBalanceParam(int nNumImage, unsigned int uCheckPoint)
{
	m_nBalanceNum = nNumImage;
	m_uCheckPoint = uCheckPoint;
}

void KObjCache::CheckBalance()
{
	m_uObjAccessCounter = 0;
	int nMaxInterval = 100000;

#ifdef WIN32
	int nCurTime = GetTickCount();
#elif __linux
	int nCurTime = times(NULL);
#endif

	if (m_nNumObjs > m_nBalanceNum)
	{
	    int nNewNumObjects = 0;
	    for (int i = 0; i < m_nNumObjs; i++)
		{
			if (nCurTime - m_pObjectList[i].nRef >= nMaxInterval &&
				CanBeFree(m_pObjectList[i].pObject))
			{
				m_fnFreeObj(m_pObjectList[i].pObject, 0);
				m_pObjectList[i].pObject = NULL;
			    continue;
            }
	        m_pObjectList[nNewNumObjects] = m_pObjectList[i];
		    nNewNumObjects++;
		}
	    m_nNumObjs =  nNewNumObjects;
	}
}

bool KObjCache::ExpandSpace()
{
	KObj* pNewList = (KObj *)realloc(m_pObjectList,
						(m_nNumReserved + ISBP_EXPAND_SPACE_STEP) * sizeof(KObj));
	if (pNewList)
	{
		m_pObjectList = pNewList;
		m_nNumReserved += ISBP_EXPAND_SPACE_STEP;
		return true;
	}
	return false;
}

int KObjCache::FindObj(unsigned int uObj, int nPossiblePosition)
{
	int nPP = nPossiblePosition;
	if (nPP < 0 || nPP >= m_nNumObjs)
	{
		if (m_nNumObjs <= 0)
		{
			return -1;
		}
		else
		{
			nPP = m_nNumObjs / 2;
		}
	}
	if (m_pObjectList[nPP].uId == uObj)
		return nPP;
	int nFrom, nTo, nTryRange;
	nTryRange = ISBP_TRY_RANGE_DEF;
	if (m_pObjectList[nPP].uId > uObj)
	{
		nFrom = 0;
		nTo = nPP - 1;
		nPP -= nTryRange;
	}
	else
	{
		nFrom = nPP + 1;
		nTo = m_nNumObjs - 1;
		nPP += nTryRange;
	}
	if (nFrom + nTryRange >= nTo)
		nPP = (nFrom + nTo) / 2;

	while (nFrom < nTo)
	{
		if (m_pObjectList[nPP].uId < uObj)
		{
			nFrom = nPP + 1;
		}
		else if (m_pObjectList[nPP].uId > uObj)
		{
			nTo = nPP - 1;
		}
		else
		{
			return nPP;
		}
		nPP = (nFrom + nTo) / 2;
	}
	if (nFrom == nTo)
	{
		if (m_pObjectList[nPP].uId > uObj)
		{
			nPP = - nPP - 1;
		}
		else if (m_pObjectList[nPP].uId < uObj)
		{
			nPP = - nPP - 2;
		}
	}
	else
	{
		nPP = - nFrom -1;
	}
	return nPP;
}

