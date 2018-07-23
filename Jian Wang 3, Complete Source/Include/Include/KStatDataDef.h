#ifndef _KSTAT_DATA_DEF_H_
#define _KSTAT_DATA_DEF_H_

// 统计数据名称长度
#define STAT_DATA_NAME_LEN      128
#define MAX_UPDATE_STAT_COUNT   8000

#pragma pack(1)
// Server批量发给Center的统计数据结构
struct KSTAT_DATA_MODIFY
{
    int     nID;
    int64_t nValue;
};
#pragma pack()

#endif
