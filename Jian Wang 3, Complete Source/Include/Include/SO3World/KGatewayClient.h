/************************************************************************/
/* Gateway client   					                                */
/* Copyright : Kingsoft 2008										    */
/* Author	 : Zhao chunfeng, Yan rui						            */
/* History	 :															*/
/*		2008.07.22	Create												*/
/************************************************************************/
#ifndef _KGATEWAYCLIENT_H_
#define _KGATEWAYCLIENT_H_

#ifdef _CLIENT

#include "GatewayDef.h"

// 该系列枚举用于BishopClient将登陆流程相关事件通知UI模块
typedef enum
{
    LPUM_UNABLE_TO_CONNECT_SERVER,              // "无法连接服务器"
    LPUM_MISS_CONNECTION,                       // "服务器连接丢失"
    LPUM_SYSTEM_MAINTENANCE,                    // "系统维护"
    LPUM_UNMATCHED_PROTOCOL_VERSION,            // "协议版本不匹配，请更新"

    LPUM_HANDSHAKE_SUCCESS,                     // "握手成功"
    LPUM_HANDSHAKE_ACCOUNT_SYSTEM_LOST,         // "帐号系统在维护"

    LPUM_LOGIN_VERIFY_ALREADY_IN_GATEWAY,       // "该账号正在使用: 正在本组服务器的Bishop上验证呢!"
    LPUM_LOGIN_VERIFY_IN_GATEWAY_BLACK_LIST,    // "账号因为使用非法客户端而被锁入黑名单了"
    LPUM_LOGIN_VERIFY_SUCCESS,                  // "验证通过,一切顺利"
    LPUM_LOGIN_NEED_MATRIX_PASSWORD,            // "验证通过,但是矩阵卡密保用户 需要密保密码"
    LPUM_LOGIN_NEED_TOKEN_PASSWORD,             // "验证通过,但是令牌密保用户 需要密保密码"
    LPUM_LOGIN_MIBAO_SYSTEM,                    // "密保系统错误"
    LPUM_LOGIN_MATRIX_FAILED,                   // "矩阵卡验证失败"
    LPUM_LOGIN_MATRIX_CARDINVALID,              // "矩阵卡无效"
    LPUM_LOGIN_MATRIX_NOTFOUND,                 // "矩阵卡未找到"
    LPUM_LOGIN_VERIFY_IN_GAME,                  // "账号正在游戏中，稍后重试(自动踢号)"
    LPUM_LOGIN_VERIFY_ACC_PSW_ERROR,            // "账号或者密码错误"
    LPUM_LOGIN_VERIFY_NO_MONEY,                 // "没钱了"
    LPUM_LOGIN_VERIFY_NOT_ACTIVE,               // "账号没有激活"
    LPUM_LOGIN_VERIFY_ACTIVATE_CODE_ERR,        // "激活码错误，不存在或已经被使用过了"
    LPUM_LOGIN_VERIFY_IN_OTHER_GROUP,           // "该账号已经在其他区服登录"
    LPUM_LOGIN_VERIFY_ACC_FREEZED,              // "账号被冻结了"
    LPUM_LOGIN_VERIFY_PAYSYS_BLACK_LIST,        // "多次密码错误,账号被Paysys锁进黑名单了"
    LPUM_LOGIN_VERIFY_LIMIT_ACCOUNT,            // "访沉迷用户，不能登入"
    LPUM_LOGIN_VERIFY_ACC_SMS_LOCK,             // "账号被用户短信锁定"
    LPUM_LOGIN_VERIFY_UNKNOWN_ERROR,            // "未知错误"

    LPUM_GET_ROLE_LIST_SUCCESS,                 // 获得角色列表OK
    LPUM_GET_ALL_ROLE_LIST_SUCCESS,             // 获得全部角色列表完成
    LPUM_UPDATE_HOMETOWN_LIST,                  // 更新新手村列表数据

    LPUM_CREATE_ROLE_SUCCESS,                   // "创建角色OK"
    LPUM_CREATE_ROLE_NAME_EXIST,                // "创建失败,角色名已存在"
    LPUM_CREATE_ROLE_INVALID_NAME,              // "创建失败,角色名非法"
    LPUM_CREATE_ROLE_NAME_TOO_LONG,             // "创建失败,角色名太长"
    LPUM_CREATE_ROLE_NAME_TOO_SHORT,            // "创建失败,角色名太短"
    LPUM_CREATE_ROLE_UNABLE_TO_CREATE,          // "创建失败,无法创建角色"

    LPUM_REQUEST_LOGIN_GAME_SUCCESS,            // 已经取得游戏世界登陆信息，正在连接服务器
    LPUM_REQUEST_LOGIN_GAME_OVERLOAD,           // "游戏世界人数已满,稍后再来"
    LPUM_REQUEST_LOGIN_GAME_MAINTENANCE,        // "服务器正在维护"
    LPUM_REQUEST_LOGIN_GAME_ROLEFREEZE,         // "该角色已冻结"
    LPUM_REQUEST_LOGIN_GAME_UNKNOWN_ERROR,      //  未知错误

    LPUM_DELETE_ROLE_SUCCESS,                   // 删除成功
    LPUM_DELETE_ROLE_DELAY,                     // 进入延时删除队列
    LPUM_DELETE_ROLE_TONG_MASTER,               // 帮主不允许删除
    LPUM_DELETE_ROLE_FREEZE_ROLE,               // 冻结角色不允许删除
    LPUM_DELETE_ROLE_UNKNOWN_ERROR,             // 不晓得什么原因，反正失败了:)

    LPUM_GIVEUP_QUEUE_SUCCESS,                  // 成功放弃排队
    LPUM_GIVEUP_QUEUE_ERROR,                    // 放弃排队出错

    LPUM_RENAME_SUCCESS,                        // 改名成功
    LPUM_RENAME_NAME_ALREADY_EXIST,             // 更改的名字已存在了
    LPUM_RENAME_NAME_TOO_LONG,                  // 更改的名字太长了
    LPUM_RENAME_NAME_TOO_SHORT,                 // 更改的名字太短了
    LPUM_RENAME_NEW_NAME_ERROR,                 // 改的名字仍不符合命名规范
    LPUM_RENAME_ERROR,                          // 改名其他错误

    LPUM_SNDA_VERIFY_SUCCESS,                   // 盛大验证成功
    LPUM_SNDA_VERIFY_FAILED,                    // 盛大验证失败(一般验证错误信息盛大圈圈会提供 走到这里可能是技术原因)

} LOGIN_PROCESS_UI_MESSAGE;

struct UI_ROLE_LIST_ITEM
{
    char    szAccountName[_NAME_LEN];
    char    szRoleName[_NAME_LEN];
    DWORD   dwRoleID;
    int     nRoleType;
    int     nLevel;
    DWORD   dwMapID;
    int	    nMapCopyIndex;
	time_t	nLastSaveTime;
    time_t  nTotalGameTime;
    time_t  nFreezeTime;
    time_t  nDeleteTime;
    WORD    wRepresentID[perRepresentCount];
    BOOL    bCanRename;
};

struct UI_ROLE_CREATE_PARAM
{
    char    szRoleName[_NAME_LEN];
    int     nRoleType; 
    DWORD   dwMapID;
    int     nMapCopyIndex;
    WORD	wRepresentId[perRepresentCount];
};

struct KUI_HOMETOWN_COPY_INFO 
{
    DWORD dwCopyIndex;
    int   nLoadFactor;
};

typedef std::vector<KUI_HOMETOWN_COPY_INFO> KUI_HOMETOWN_LOAD_REFACT_TABLE;

struct KUI_HOMETOWN_MAP_INFO
{
    DWORD dwMapID;
    KUI_HOMETOWN_LOAD_REFACT_TABLE LoadFactorTable;
};

typedef std::vector<KUI_HOMETOWN_MAP_INFO> KUI_HOMETOWN_MAP_TABLE;

struct KROLE_LIST_INFO;

class KGatewayClient
{
public:
	KGatewayClient(void);
	~KGatewayClient(void);

    void    Activate();
    void    ProcessConnectGateway();
    void    ProcessPackage();
    
    int     SetGatewayAddress(const char cszLoginIP[], unsigned short usLoginPort);
    int     SetAccountPassword(const char cszAccountName[], const char cszPasswordMD5[], const char cszActiveCode[]);
    int     SetSndaIDToken(const char cszSndaID[], const char cszSndaToken[]);
    int     AccountVerify();
    int     SndaTokenVerify();
    int     GetRoleListItem(UI_ROLE_LIST_ITEM *pRoleListItem, int nRoleIndex); // nRoleIndex 从0开始
    int     QueryHometownList();
    int     RoleLogin(const char cszRoleName[]);
    int     DeleteRole(const char cszRoleName[], const char cszSecPasswordMD5[]);    
    int     CreateRole(const UI_ROLE_CREATE_PARAM &crRoleCreateParam);
    int     GetRoleCount();
    time_t  GetLastLoginTime();
    DWORD   GetLastLoginIP();
    void    Reset();
    void    MibaoVerify(const char* pszPassword);

    const KUI_HOMETOWN_MAP_TABLE& GetHometownList() { return m_HometownList; };
    char* GetAccountName() { return m_szAccountName; }

public:
    char                    m_szLoginIP[32];
    unsigned short          m_usLoginPort;
    IKG_SocketStream*       m_piSocketStream;
    BOOL                    m_bSendErrorFlag;

    char                    m_szAccountName[_NAME_LEN];
    KSG_PASSWORD            m_Password;    
    char                    m_szActivateCode[_NAME_LEN];
    char                    m_szMibaoPassword[10];
    char                    m_szSndaToken[SNDA_TOKEN_LEN];

    time_t                  m_nLastPingTime;

    BOOL                    m_bZoneChargeFlag;
    BOOL                    m_bChargeFlag;
    time_t                  m_nEndOfDayTime;
    DWORD                   m_dwLeftTimeOfPoint;
    DWORD                   m_dwLeftTimeOfDay;
    time_t                  m_nEndTimeOfFee;
    time_t                  m_nLoginTime;
    time_t                  m_nLastLoginTime;
    DWORD                   m_dwLastLoginIP;

	typedef std::vector<UI_ROLE_LIST_ITEM>  ROLE_LIST;
    ROLE_LIST               m_RoleList;

    KUI_HOMETOWN_MAP_TABLE  m_HometownList;
    
    BOOL    AddRoleToRoleList(KROLE_LIST_INFO* pRoleListInfo);
    DWORD   GetRoleID(const char* cszRoleName);
    BOOL    ConnectGateway();

    BOOL    Send(IKG_Buffer* piSendBuffer);

public:
    BOOL DoPingSignal();
    BOOL DoHandshakeRequest();
    BOOL DoAccountVerifyRequest();
    BOOL DoSndaTokenVerifyRequest();
    BOOL DoMibaoVerifyRequest();
    BOOL DoCreateRoleRequest(const UI_ROLE_CREATE_PARAM &crRoleCreateParam);
    BOOL DoDeleteRoleRequest(DWORD dwRoleID);
    BOOL DoLoginGameRequest(DWORD dwRoleID);
    BOOL DoQueryHometownListRequest();
    BOOL DoGiveupQueueRequest();
    BOOL DoRenameRequest(char szOldName[], char szNewName[]);
    BOOL DoCancelRename();

private:
    typedef void (KGatewayClient::*PROTOCOL_FUNCTION)(BYTE* pbyData, size_t uDataLen);

    PROTOCOL_FUNCTION m_ProtocolFunctions[UCHAR_MAX + 1];
    size_t            m_uPakSize[UCHAR_MAX + 1];
    
    enum CONNECT_STATE
    {
        csInvalid,
        csWaitingConnectOK
    };
    CONNECT_STATE m_ConnectState;

    void OnPingRespond(BYTE* pbyData, size_t uDataLen);
    void OnHandshakeRespond(BYTE* pbyData, size_t uDataLen);
    void OnAccountLockedNotify(BYTE* pbyData, size_t uDataLen);
    void OnAccountVerifyRespond(BYTE* pbyData, size_t uDataLen);
    void OnMibaoVerifyRespond(BYTE* pbyData, size_t uDataLen);
    void OnKickAccountNotify(BYTE* pbyData, size_t uDataLen);
    void OnSyncRoleList(BYTE* pbyData, size_t uDataLen);
    void OnSyncNewbieMaps(BYTE* pbyData, size_t uDataLen);
    void OnCreateRoleRespond(BYTE* pbyData, size_t uDataLen);
    void OnDeleteRoleRespond(BYTE* pbyData, size_t uDataLen);
    void OnGameLoginPrepare(BYTE* pbyData, size_t uDataLen);
    void OnSyncLoginKey(BYTE* pbyData, size_t uDataLen);
    void OnSyncQueueState(BYTE* pbyData, size_t uDataLen);
    void OnGiveupQueueRespond(BYTE* pbyData, size_t uDataLen);
    void OnRenameRespond(BYTE* pbyData, size_t uDataLen);
    void OnSndaVerifyRespond(BYTE* pbyData, size_t uDataLen);
};


extern KGatewayClient g_GatewayClient;

#endif  // _CLIENT

#endif  // _KGATEWAYCLIENT_H_
