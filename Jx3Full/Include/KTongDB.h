#ifndef _KTONGDB_H_
#define _KTONGDB_H_

// 帮会数据库存盘数据结构定义

#define TONG_DB_VERSION     2
#define MAX_TONG_DATA_LEN   (1024 * 1024)

enum KTongDataSection
{
    eTongDataBegin,
    eTongBaseInfo,
    eTongSchema,
    eTongRoster,
    eTongAnnouncement,
    eTongOnlineMessage,
    eTongIntroduction,
    eTongRules,
    eTongMemorabilia,
    eTongRepertory,
    eTongDevelopmentInfo,
    eTongHistory,
    eTongDataEnd
};

#pragma pack(1)
struct KTONG_DB_HEADER
{
    int nVersion;
};

struct KTONG_DB_SECTION
{
    int     nType;
    size_t  uDataLen;
    BYTE    byData[0];
};

struct KTONG_DB_BASEINFO
{
    char    szName[_NAME_LEN];
    DWORD   dwMaster;           // 帮主
    int     nLevel;
    WORD    wMaxMemberCount;    // 成员上限
    BYTE    byTongState;
    time_t  nStateTimer;
    BYTE    byCamp;             // 阵营
    
};

// --- KTONG_DB_BASEINFO 版本兼容 ---
struct KTONG_DB_BASEINFO_VERSION1
{
    char    szName[_NAME_LEN];
    DWORD   dwMaster;           // 帮主
    int     nFund;              // 资金(银币)
    int     nLevel;
    int     nDevelopmentPoint;  // 发展点
    WORD    wMaxMemberCount;    // 成员上限
    BYTE    byTongState;
    time_t  nStateTimer;
    BYTE    byCamp;             // 阵营
};
// ---------------------------------

struct KTONG_DB_SCHEMA
{
    KTongSchemaData Schema;
};

struct KTONG_DB_ROSTER
{
    int     nMemberCount;
    BYTE    byData[0];
};

struct KTONG_DB_MEMORABILIA
{
    time_t  nTime;
    BYTE    byDataLen;
    BYTE    byData[0];
};

struct KTONG_DB_MEMBER_DATA
{
    DWORD   dwID;
    int     nGroupID;                           // 所属成员组
	time_t  nJoinTime;                          // 加入时间
    char    szRemark[TONG_MEMBER_REMARK_LEN];   // 备注
    time_t  nLastOfflineTime;                   // 最后在线时间
    int     nSalary;                            // 工资储蓄(银币)
};

// --- KTONG_DB_MEMBER_DATA 版本兼容 ---
struct KTONG_DB_MEMBER_DATA_VERSION1
{
    DWORD   dwID;
    int     nGroupID;                           // 所属成员组
	time_t  nJoinTime;                          // 加入时间
    char    szRemark[TONG_MEMBER_REMARK_LEN];   // 备注
    time_t  nLastOfflineTime;                   // 最后在线时间
};
// -------------------------------------

struct KTONG_DB_DEVELOPMENT_DATA
{
    int     nFund;              // 资金(银币)
    int     nMaxWageRate;
    int     nDevelopmentPoint;  // 发展点
    int     nUsedDevelopmentPoint;
    BYTE    byTechTree[MAX_TONG_TECHTREE_NODE_NUM];
};

struct KTONG_REPERTORY_DB_PAGE
{
    BYTE byPageIndex;
    BYTE byCount;
};

struct KTONG_REPERTORY_DB_ITEM
{
    BYTE byPos;
    BYTE bySize;
    BYTE byData[0];
};

struct KTONG_DB_HISTORY_CATEGORY
{
    BYTE byType;
    WORD wRecordCount;
};
#pragma pack()

#endif

