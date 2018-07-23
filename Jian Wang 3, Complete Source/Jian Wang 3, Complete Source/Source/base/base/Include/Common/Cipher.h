/********************************************************************
	created:	2003/06/18
	file base:	Cipher
	file ext:	h
	author:		liupeng
	
	purpose:	
*********************************************************************/
#ifndef __INCLUDE_CIPHER_H__
#define __INCLUDE_CIPHER_H__

/*
 * ProtocolType same as s2c_accountbegin in the protocol.h file
 */
#define CIPHER_PROTOCOL_TYPE	0x20


#pragma pack(push, 1)


typedef struct 
{
	BYTE			ProtocolType;
    BYTE            Mode;
    BYTE            Reserve1[6];
    unsigned        ClientKey;
    BYTE            Reserve3[5];
    unsigned        ServerKey;
    BYTE            Reserve2[21];
} ACCOUNT_BEGIN;
#define NE_MAKEKEY(key)		(((~((((key) & 0xFF000000) >> 24) | (((key) & 0x000000FF) << 24) | ((key) & 0x00FFFF00))) + 0x2E6D2399) ^ 0x2E6D23CF)
#define NE_GETKEY(key)		((((~( ((key) ^ 0x2E6D23CF) - 0x2E6D2399 )) & 0xFF000000) >> 24) | ((~(((key) ^ 0x2E6D23CF) - 0x2E6D2399) & 0x000000FF) << 24) | (~(((key) ^ 0x2E6D23CF) - 0x2E6D2399) & 0x00FFFF00))


typedef struct 
{
	BYTE			ProtocolType;
    BYTE            Mode;
    BYTE            Reserve1[6];
    unsigned        ServerKey;
    unsigned        ClientKey;
    BYTE            Reserve2[16];
} EASYCRYPT_ACCOUNT_BEGIN;
#define EASYCRYPT_MAKEKEY(key)		(~(key))
#define EASYCRYPT_GETKEY(key)		(~(key))


#pragma pack(pop)

#endif // __INCLUDE_CIPHER_H__
