////////////////////////////////////////////////////////////////////////////////
//
//  FileName    : KEnchantLib.h
//  Version     : 1.0
//  Creator     : Xia Yong
//  Create Date : 2008-03-05 15:42:00
//  Comment     : 
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _KENCHANTLIB_H_
#define _KENCHANTLIB_H_

#include <map>

struct KAttribute;
struct KENCHANT 
{
    KAttribute* pAttribute;
	int         nRepresentIndex;
	int         nRepresentID;
    int         nTime; // 附魔时间,单位: 秒; <=0表示永久附魔
	int         nDestItemSubType;
    DWORD       dwTabType;  // 镶嵌的道具
    DWORD       dwTabIndex; 
    int         nPackageSize; // 镶嵌的背包大小
#ifdef _CLIENT
    DWORD       dwUIID;
#endif
};

class KEnchantLib
{
public:
    BOOL Init();
    void UnInit();

    KENCHANT* GetEnchantInfo(DWORD dwEnchantID);

private:
    typedef std::map<DWORD, KENCHANT> KENCHANT_MAP;
    KENCHANT_MAP m_Enchant;

private:
    KAttribute* LoadLineAttribute(ITabFile* piFile, int nLine);
};

#endif
