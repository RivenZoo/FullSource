#ifndef _KMENTOR_DEF_H_
#define _KMENTOR_DEF_H_

#define HIGH_DWORD_IN_UINT64(_KEY) ((DWORD)((_KEY) >> 32))
#define LOW_DWORD_IN_UINT64(_KEY)  ((DWORD)((_KEY) & 0x00000000FFFFFFFF))

#define MAX_SYNC_MENTOR_RECORD_COUNT 100

#define LOWEST_LEVEL_AS_MENTOR      50

#define MENTOR_APPLY_TIMEOUT_TIME    (5 * 60)

#define MIN_APPRENTICE_NUM           4
#define MAX_APPRENTICE_NUM           10
#define MAX_MENTOR_NUM               3

#define MENTOR_NORMAL_TIMEOUT        (60 * 60 * 24 * 30 * 3)
#define MENTOR_MBREAK_TIMEOUT        (60 * 60 * 24 * 3)
#define MENTOR_ABREAK_TIMEOUT        (60 * 60 * 24 * 3)
#define MENTOR_BROKEN_TIMEOUT        (60 * 60 * 24 * 30 * 3)
#define MENTOR_GRATUATING_TIMEOUT    (60 * 60 * 24 * 30 * 3)
#define MENTOR_GRATUATED_TIMEOUT     (60 * 60 * 24 * 30 * 3)

#define EVIL_BREAK_OFFLINE_TIME      (60 * 60 * 24 * 7)

#define MBREAK_MENTOR_VALUE_RATE        0.5
#define ABREAK_MENTOR_VALUE_RATE        0.5
#define EVIL_MBREAK_MENTOR_VALUE_RATE   0
#define EVIL_ABREAK_MENTOR_VALUE_RATE   0.6

#define LOWEST_ALEVEL_ACCQUIRE_MENTOR_VALUE 20

#define MENTOR_DATA_VERSION 1

#pragma pack(1)
struct KMentorRecordDBHead
{
    int nVersion;
};

struct KMentorRecordDB : KMentorRecordDBHead
{
    time_t  nCreateTime;        // 拜师时间
    int     nMentorValue;       // 师徒值
    time_t  nEndTime;           // 状态的截止时间
    BYTE    byState;            // 关系解除发起方
    BYTE    byOriginalALevel;   // 拜师时徒弟的等级
    BYTE    byReserved[18];
};
#pragma pack()

enum KMentorRecordState
{
    emrsInvalid = 0,

    emrsNormal,      // 正常的师徒关系
    emrsMBreak,      // 被师傅解除的待删除的师徒关系
    emrsABreak,      // ..徒弟......
    emrsBroken,      // 解除后等待师傅取走师徒值
    emrsGraduating,  // 徒弟和其它师傅做了出师任务，当前师傅要加已毕业徒弟数
    emrsGraduated,   // 徒弟出师后等待师傅取走师徒值

    emrsTotal
};

struct KMentorRecordBase
{
    int  nMentorValue;
    BYTE byState;
};

#pragma pack(1)
// 用于GC向GS做初始同步的
struct KMentorSyncInfo
{
    DWORD dwMentor;
    DWORD dwApprentice;
    int   nValue;
    BYTE  byState;
};
#pragma pack()

#endif // _KMENTOR_DEF_H_


