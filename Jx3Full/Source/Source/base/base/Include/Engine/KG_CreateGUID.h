//////////////////////////////////////////////////////////////////////////////////////
//
//  FileName    :   KG_CreateGUID.h
//  Version     :   1.0
//  Creater     :   Freeway Chen
//  Date        :   2004-12-9 16:11:14
//  Comment     :   
//
//////////////////////////////////////////////////////////////////////////////////////

#ifndef _KG_CREATEGUID_H_
#define _KG_CREATEGUID_H_   1

#include "KWin32.h"

#ifndef  ENGINE_API
#define  ENGINE_API
#endif

ENGINE_API int KG_CreateGUID(GUID *pGuid);

#endif
