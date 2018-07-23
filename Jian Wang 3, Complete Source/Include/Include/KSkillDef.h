#ifndef _KSKILL_DEF_
#define _KSKILL_DEF_

#pragma pack(1)
struct KDB_SKILL_DATA
{
    DWORD       dwMountKungfuID;
    DWORD       dwMountKungfuLevel;
    int         nSkillCount;
    struct KDB_SKILL_ITEM
    {
        WORD	wSkillID;
        BYTE	byMaxLevel;
        DWORD	dwExp;
    } SkillItems[0];
};
#pragma pack()

#endif // _KSKILL_DEF_
