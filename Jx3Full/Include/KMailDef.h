#ifndef _KMAIL_DEF_H_
#define _KMAIL_DEF_H_

#include "ProtocolBasic.h"

#define MAILSYS_VERSION      5

#define KMAIL_MAX_ITEM_COUNT 8
#define MAIL_TITLE_LEN       64
#define MAX_MAIL_TEXT_LEN    400

enum KMAIL_TYPE
{
    eMailType_Player = 0,
    eMailType_System,
    eMailType_Auction,
    eMailType_GmMessage,
    eMailType_PlayerMessage,
    eMailType_Total
};

enum KMAIL_RESULT_CODE
{
    mrcSucceed,
    mrcFailed,

    mrcSystemBusy,
    mrcDstNotExist,
    mrcNotEnoughMoney,
    mrcItemAmountLimit,
    mrcNotEnoughRoom,
    mrcMoneyLimit,
    mrcMailNotFound,
    mrcMailBoxFull,
    mrcReturnMailFailed,
    mrcItemBeBind,
    mrcTimeLimitItem,
    mrcItemNotInPackage,
    mrcDstNotSelf,
    mrcDeleteRefused,
    mrcSelfMailBoxFull,
    mrcTooFarAway,

    mrcTotal
};

#pragma pack(1)
struct KMailItemDesc 
{  
    bool   bAcquired;   // true 表示已经分发给玩家了 
    BYTE   byDataLen;
    int    nPrice;      // 货到付款的道具价格
};

struct KMail
{
    DWORD           dwMailID;
    BYTE            byType;
    bool            bRead;
    DWORD           dwSenderID;
    char            szSenderName[ROLE_NAME_LEN];
    char            szTitle[MAIL_TITLE_LEN];
    time_t          nSendTime;
    time_t          nRecvTime;
    time_t          nLockTime;
    int             nMoney;
    WORD            wTextLen;
    KMailItemDesc   ItemDesc[KMAIL_MAX_ITEM_COUNT];
    BYTE            byData[0];
};

struct KMailContent
{
    int             nMoney;
    WORD            wTextLen;
    KMailItemDesc   ItemDesc[KMAIL_MAX_ITEM_COUNT];
    BYTE            byData[0];
};

struct KMailListInfo
{
    BYTE        byType;
    DWORD       dwMailID;
    char        szSender[ROLE_NAME_LEN];
    char        szTitle[MAIL_TITLE_LEN];
    time_t      nSendTime;
    time_t      nRecvTime;
    bool        bReadFlag;
    bool        bMoneyFlag;
    bool        bItemFlag;
};
#pragma pack()

#endif //_KMAIL_DEF_H_
