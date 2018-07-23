//////////////////////////////////////////////////////////////////////////////////////
//
//  FileName    :   KG_FileNameHash.h
//  Version     :   1.0
//  Creater     :   Zhu Chengmin
//  Date        :   2009-1-6
//  Comment     :   
//
//////////////////////////////////////////////////////////////////////////////////////

#ifndef _KG_FILE_NAME_HASH_H_
#define _KG_FILE_NAME_HASH_H_

#include "EngineBase.h"
#include <wchar.h>

enum KG_HASH_TYPE
{
    KG_HASH_INVALID = 0,
    KG_HASH_TIME33,
    KG_HASH_DEFAULT = KG_HASH_TIME33,
    KG_HASH_BKDR,

    KG_HASH_TOTAL
};

extern "C"
{
ENGINE_API int KG_StringHashW(KG_HASH_TYPE eHashType, const wchar_t cwszString[], unsigned int *puRetHash);
ENGINE_API int KG_FileNameHash(KG_HASH_TYPE eHashType, const char cszFileName[], unsigned int *puRetHash);
}

#endif //_KG_FILE_NAME_HASH_H_
