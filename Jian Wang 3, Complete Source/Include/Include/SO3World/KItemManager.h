////////////////////////////////////////////////////////////////////////////////
//
//  FileName    : KItemManager.h
//  Version     : 1.0
//  Creator     : Xia Yong
//  Create Date : 2008-03-05 15:42:00
//  Comment     : 
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _KITEMMANAGER_H_
#define _KITEMMANAGER_H_
#include "KEnchantLib.h"
#include "../../Source/Common/SO3World/Src/KItemLib.h"

class KItemManager
{
public:
	BOOL        Init();
    void        UnInit();

    KItem*      GenerateItem(
        DWORD   dwTabType,  
        DWORD   dwTabIndex, 
        time_t  nGenTime,
        DWORD   dwId = ERROR_ID,    
        DWORD   dwRandSeed = 0,   
        int     nMagicNum = 0, 
        int     nQuality = 0, 
        int     nMagic[] = NULL  
    );

    BOOL        GenerateItemTo(
        KItem*  pDestItem,      
        DWORD   dwTabType,      
        DWORD   dwTabIndex,
        time_t  nGenTime,
        DWORD   dwId        = ERROR_ID, 
        DWORD   dwRandSeed  = 0, 
        int     nMagicNum   = 0, 
        int     nQuality    = 0,    
        int     nMagic[]    = NULL
    );
    
    KItem*      GenerateItemFromBinaryData(DWORD dwItemID, void* pvBuffer, size_t uBufferSize);

    KItem*      CloneItem(const KItem* pItem);
	KItemInfo*  GetItemInfo(DWORD dwTabType, DWORD dwIndex);
	BOOL        GetSetAttrib(KAttribute& pAttr, DWORD dwSetID, int nSetNum);
    BOOL        FreeItem(KItem* pItem);

public:
	KItemLib            m_ItemLib;
    KEnchantLib         m_EnchantLib;
};
#endif
