// -------------------------------------------------------------------------
//	文件名		：	inoutmac.h
//	创建者		：	谢茂培 (Hsie)
//	创建时间	：	2003-07-20 14:47:18
//	功能描述	：	
//
// -------------------------------------------------------------------------
#ifndef __INOUTMAC_H__
#define __INOUTMAC_H__
#include "EngineBase.h"
//此函数会确保两个地址均有
//返回值为网卡数量
ENGINE_API int gGetMacAndIPAddress(
    unsigned char *pMacAddressIn,   unsigned long *pIPAddressIn, 
    unsigned char  *pMacAddressOut, unsigned long *pIPAddressOut, 
    unsigned uMask = 0x0000a8c0, 
    int nMacLength = 6
);

#endif // __INOUTMAC_H__
