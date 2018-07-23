#ifndef _KGAME_CARD_DEF_H_
#define _KGAME_CARD_DEF_H_

enum KGAME_CARD_TYPE
{
    gctInvalid,
    gctMonthCard    = 1,
    gctPointCard    = 2,
    gctDayCard      = 3
};

enum KGAME_CARD_OPERATION_RESULT
{
    gorSucceed,
    gorFreezeCoinFailed,
    gorExchangeFailed,
    gorUnFreezeCoinFailed,
    gorSystemError,

    gorUnknownError
};

enum KGAME_CARD_ORDER_TYPE
{
    gotByGameTime,
    gotByEndTime,
    gotByPrice,

    gotTotal
};

#define MAX_SYNC_GAME_CARD_COUNT 50

#pragma pack(1)
struct KGAME_CARD 
{
    DWORD   dwID;
    DWORD   dwSellerID;
    char    szSellerName[ROLE_NAME_LEN];
    int     nGameTime;
    BYTE    byType;
    int     nLeftTime;
    int     nPrice;
};
#pragma pack()

#endif
