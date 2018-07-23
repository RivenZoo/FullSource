//////////////////////////////////////////////////////////////////////////////////////
//
//  FileName    :   CRC32.H
//  Creater     :   Freeway Chen
//  Date        :   2000-6-15 18:25:43
//  Comment     :   Get source code from Zlib Project
//
//////////////////////////////////////////////////////////////////////////////////////

#ifndef __ENGINE_CRC32_H__
#define __ENGINE_CRC32_H__

// most CRC first value is 0
extern "C" unsigned Misc_CRC32(unsigned CRC, const void *pvBuf, unsigned uLen);

#endif  // __ENGINE_CRC32_H__
