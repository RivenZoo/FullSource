//*********************************************************************
// file		: KCodePoints.h
// author	: wangbin
// datetime : 2004-06-22 17:30
// comment	: 代码检查点，用来检查内存泄漏
//*********************************************************************
#ifndef _ENGINE_KCODEPOINTS_H_
#define _ENGINE_KCODEPOINTS_H_

#include <stdio.h>
#include <map>
#include <string>
using namespace std;
#include "Debug.h"

class KCodePoints
{
	typedef struct
	{
		enum {BUFLEN = 256};
		char szFile[BUFLEN];	// 文件
		int  nLine;				// 行数
	} CODEPOINT;
public:
	static KCodePoints *GetInstance()
	{
		if (m_bInitialized) 
			return &m_objCodePoints;
		return NULL;
	}
	KCodePoints() {m_bInitialized = true;}
	~KCodePoints()
	{
		_ASSERT(m_mapCodePoints.size() == 0);
		map<unsigned, CODEPOINT>::const_iterator it = m_mapCodePoints.begin();
		for (; it != m_mapCodePoints.end(); it++)
			Log(it->first, it->second);
		m_bInitialized = false;
	}
	void AddPoint(unsigned uAddress, char* pcszFile, int nLine)
	{
		if (!m_bInitialized)
			return;
		_ASSERT(m_mapCodePoints.find(uAddress) == m_mapCodePoints.end());
		CODEPOINT cp = {0};
		::strncpy(cp.szFile, pcszFile, CODEPOINT::BUFLEN - 1);
		cp.nLine = nLine;
		m_mapCodePoints[uAddress] = cp;
	}
	void DelPoint(unsigned uAddress)
	{
		if (!m_bInitialized)
			return;
		map<unsigned, CODEPOINT>::iterator it = m_mapCodePoints.find(uAddress);
		_ASSERT(it != m_mapCodePoints.end());
		if (it != m_mapCodePoints.end())
			m_mapCodePoints.erase(it);
	}
private:
	void Log(unsigned uAddress, const CODEPOINT &cp)
	{
		_ASSERT(cp.szFile && cp.nLine > 0);
		::printf("MEMORY LEAK DETECTED! ====> Address: 0x%x, File: %s, Line: %d\n", uAddress, cp.szFile, cp.nLine);
		// TRACE("MEMORY LEAK DETECTED! ====> File: %s, Line: %d\n", pcszFile, nLine);
	}
private:
	map<unsigned, CODEPOINT>	m_mapCodePoints;
	static KCodePoints			m_objCodePoints;
	static bool					m_bInitialized;		// 初始化成功
};

namespace codepoint
{
	template <typename T>
	T *AddPoint(T *p, char* pcszFile, int nLine)
	{
		_ASSERT(p && pcszFile && nLine > 0);
		KCodePoints *pCodePoints = KCodePoints::GetInstance();
		if (pCodePoints)
			pCodePoints->AddPoint((unsigned)(p), __FILE__, __LINE__);
		return p;
	}
	
	template <typename T>
	T *DelPoint(T *p)
	{
		_ASSERT(p);
		KCodePoints *pCodePoints = KCodePoints::GetInstance();
		if (pCodePoints)
			pCodePoints->DelPoint((unsigned)(p));
		return p;
	}
}

//#define USE_CODEPOINT

#if defined(_DEBUG) && defined(USE_CODEPOINT)
#define IMPLEMENT_CODEPOINTS()		KCodePoints KCodePoints::m_objCodePoints; BOOL KCodePoints::m_bInitialized = FALSE;
#define ADD_CODEPOINT(p)			KCodePoints::GetInstance()->AddPoint((unsigned)(p), __FILE__, __LINE__)
#define DEL_CODEPOINT(p)			KCodePoints::GetInstance()->DelPoint((unsigned)(p))
#define ADDCP_RETURN(p)				codepoint::AddPoint(p, __FILE__, __LINE__)
#define DELCP_RETURN(p)				codepoint::DelPoint(p)
#else
#define IMPLEMENT_CODEPOINTS()		
#define ADD_CODEPOINT(p)			((void)0)
#define DEL_CODEPOINT(p)			((void)0)
#define ADDCP_RETURN(p)				(p)
#define DELCP_RETURN(p)				(p)
#endif //_DEBUG

#endif //_ENGINE_KCODEPOINTS_H_
