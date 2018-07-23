#ifndef _GATEWAYDEF_H_ 
#define _GATEWAYDEF_H_ 

#define GATEWAY_VERSION     15
#define INVALID_QUEUE_ID    0

// 本文件定义有些Gateway相关的常量定义,本文件会被游戏世界,客户端引用

enum KGATEWAY_HANDSHAKE_CODE
{
    ghcHandshakeSucceed,        // 握手成功
    ghcGatewayVersionError,     // 网关版本不匹配,请更新客户端
    ghcGameWorldMaintenance,    // 系统正在维护
    ghcAccountSystemLost,       // 帐号系统连接丢失
    ghcGameWorldVersionError,   // 游戏世界版本不匹配,请更新客户端
};

enum KCREATE_ROLE_RESPOND_CODE
{
    eCreateRoleSucceed,             // 成功
    eCreateRoleNameAlreadyExist,    // 名字已经存在
    eCreateRoleInvalidRoleName,     // 角色名非法
    eCreateRoleNameTooLong,         // 角色名太长
    eCreateRoleNameTooShort,        // 角色名太短
    eCreateRoleUnableToCreate,      // 其他原因,反正无法创建角色
};

enum KDELETE_ROLE_RESPOND_CODE
{
    eDeleteRoleSucceed,         // 成功
    eDeleteRoleDelay,           // 删除角色延时中
    eDeleteRoleTongMaster,      // 帮主不能删除
    eDeleteRoleFreezeRole,      // 冻结角色不能删除
    eDeleteRoleUnknownError,    // 未知错误
};

enum KGAME_LOGIN_RESPOND_CODE
{
    eGameLoginSucceed,                // 成功
    eGameLoginSystemMaintenance,      // 系统维护
    eGameLoginQueueWait,              // 人数已满,需要排队
    eGameLoginOverload,               // 系统过载
    eGameLoginRoleFreeze,             // 角色已冻结
    eGameLoginUnknownError,           // 未知错误
};

enum KRENAME_RESPOND_CODE
{
    eRenameSucceed,                 // 成功
    eRenameNameAlreadyExist,        // 更改的名字已存在
    eRenameNewNameError,            // 新的名字依然不合法
    eRenameNewNameTooLong,          // 新的名字太长了
    eRenameNewNameTooShort,         // 新的名字太短了
    eRenameUnknownError,            // 未知的错误
};

#pragma	pack(1)
struct KNEWBIE_MAP_COPY_INFO 
{
    int     nCopyIndex;
    int     nLoadFactor;
};
#pragma pack()

#define SNDA_ID_LEN     32
#define SNDA_TOKEN_LEN  384
#define ID_CARD_LEN     32

#endif
