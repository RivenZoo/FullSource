#ifndef _KDESIGNATION_LIST_H_
#define _KDESIGNATION_LIST_H_

#include <map>

struct KPrefixInfo
{
    BYTE byAnnounceType;
};

struct KPostfixInfo
{
    BYTE byAnnounceType;
};

class KDesignationList
{
public:
    BOOL Init();
    void UnInit();

    KPrefixInfo* GetPrefixInfo(int nPrefix);
    KPostfixInfo* GetPostfixInfo(int nPostfix);

private:
    BOOL LoadPrefixInfo();
    BOOL LoadPostfixInfo();

private:
    typedef std::map<int, KPrefixInfo> KPREFIX_MAP;
    KPREFIX_MAP m_PrefixList;

    typedef std::map<int, KPostfixInfo> KPOSTFIX_MAP;
    KPOSTFIX_MAP m_PostfixList;
};

#endif  //_KDESIGNATION_LIST_H_

