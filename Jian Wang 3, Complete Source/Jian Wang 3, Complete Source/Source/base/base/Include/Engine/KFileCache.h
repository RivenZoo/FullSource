// -------------------------------------------------------------------------
//	文件描述	：	文件缓存（适用于Ini，TabFile此类实现了Load(szFilePath)的文件类）
//	创建者		：	Fanghao_Wu
//	创建时间	：	2005-04-12
// -------------------------------------------------------------------------

#ifndef KFILECACHE_H
#define KFILECACHE_H

#include <string>
#include <map>

template < class T >
class KFileCache
{
protected:
	struct KFileNode
	{
		T*			m_pFile;		// 文件指针
		int			m_nRef;			// 文件引用计数
	};

	typedef std::map< std::string, KFileNode > MAPFILESET;
	MAPFILESET m_mpFileSet;			// 缓存文件集

public:
	~KFileCache()
	{
		UnloadAll();
	}

public:
	T* Load(char* szFileName);		// 载入指定文件，指定文件引用计数加1
	bool Unload(char* szFileName);	// 卸载指定文件，指定文件引用计数减1，计数为0时从文件缓存中彻定清除
	bool UnloadAll();				// 不管引用计数，全部从文件缓存中彻定清除
	T* Open(char* szFileName);		// 打开使用指定文件
};

// 载入指定文件，指定文件引用计数加1
template < class T >
T* KFileCache< T >::Load(char* szFileName)
{
	if (!szFileName || !szFileName[0])
		return NULL;

	typename MAPFILESET::iterator it = m_mpFileSet.find(szFileName);
	if (it != m_mpFileSet.end())
	{
		// 文件已存在
		it->second.m_nRef++;
		return it->second.m_pFile;
	}

	
	T* pFile = NULL;
	g_OpenFile(&pFile, szFileName);
	if (!pFile)
		return false;

	KFileNode fileNode;
	fileNode.m_pFile = pFile;
	fileNode.m_nRef = 1;

	m_mpFileSet[szFileName] = fileNode;

	return pFile;
}

// 卸载指定文件，指定文件引用计数减1，计数为0时从文件缓存中彻定清除
template < class T >
bool KFileCache< T >::Unload(char* szFileName)
{
	typename MAPFILESET::iterator it = m_mpFileSet.find(szFileName);

	if (it == m_mpFileSet.end())
		return false;

	it->second.m_nRef--;

	if (it->second.m_nRef == 0)
	{
		SAFE_RELEASE(it->second.m_pFile);
		m_mpFileSet.erase(it);
	}

	return true;
}

// 不管引用计数，全部从文件缓存中彻定清除
template < class T >
bool KFileCache< T >::UnloadAll()
{
	typename MAPFILESET::iterator it;
	for (it = m_mpFileSet.begin(); it != m_mpFileSet.end(); it++)
	{
		SAFE_RELEASE(it->second.m_pFile);
	}
	m_mpFileSet.clear();
	return true;
}

// 打开使用指定文件
template < class T >
T* KFileCache< T >::Open(char* szFileName)
{
	typename MAPFILESET::iterator it = m_mpFileSet.find(szFileName);

	if (it != m_mpFileSet.end())
		return it->second.m_pFile;

	return NULL;
}

#endif	// #ifndef KFILECACHE_H
