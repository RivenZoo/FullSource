////////////////////////////////////////////////////////////////////////////////
//  FileName    : KG_IniFile.h
//  Version     : 1.0
//  Creator     : Hu Hao
//  Create Date : 2008-6-4    16:36:08
//  Comment     : Use the IIniFile as interface
////////////////////////////////////////////////////////////////////////////////

#ifndef __KG_INI_FILE_H__
#define __KG_INI_FILE_H__

#include "Engine/FileType.h"
#include <map>
#include <string>

////////////////////////////////////////////////////////////////////////////////
// Used to identify the arguments including ini data
#define KG_INI_ARGUMENT_PREFIX "--"

////////////////////////////////////////////////////////////////////////////////
// Mapping the key name with its value
typedef std::map<std::string, std::string> KG_Ini_KeyMap;

////////////////////////////////////////////////////////////////////////////////
// Mapping the section name with corresponding KG_Ini_KeyMap
typedef std::map<std::string, KG_Ini_KeyMap> KG_Ini_SectionMap;

class KG_IniFile : public IIniFile
{
public:
    KG_IniFile()
    {
    }

    ~KG_IniFile()
    {
    }

    ////////////////////////////////////////////////////////////////////////////
    int Init(const KG_Ini_SectionMap &rcSectionMap, void *pvContext);
    int UnInit(void *pvContext);

    //-------------- Supporting interface functions as below -------------------
    virtual void Clear()
    {
        m_SectionMap.clear();
        return;
    }
    virtual void Release()
    {
        UnInit(NULL);
        delete this;
    }

    virtual int GetNextSection(const char *pSection, char *pNextSection);
    virtual int GetNextKey(const char *pSection, const char *pKey, char *pNextKey);
    virtual int GetSectionCount();
    virtual int IsSectionExist(const char *lpSection);

    virtual int GetString(
        const char  *lpSection,
        const char  *lpKeyName,
        const char  *lpDefault,
        char        *lpRString,
        unsigned int dwSize
    );
    virtual int GetInteger(
        const char *lpSection,
        const char *lpKeyName,
        int         nDefault,
        int        *pnValue
    );
    virtual int GetInteger2(
        const char *lpSection,
        const char *lpKeyName,
        int        *pnValue1,
        int        *pnValue2
    );
    virtual int GetMultiInteger(
        const char *lpSection,
        const char *lpKeyName,
        int        *pValues,
        int         nCount
    );
    virtual int GetMultiLong(
        const char *lpSection,
        const char *lpKeyName,
        long       *pValues,
        int         nCount
    );
    virtual int GetFloat(
        const char *lpSection,
        const char *lpKeyName,
        float       fDefault,
        float      *pfValue
    );
    virtual int GetFloat2(
        const char *lpSection,
        const char *lpKeyName,
        float      *pfValue1,
        float      *pfValue2
    );
    virtual int GetMultiFloat(
        const char *lpSection,
        const char *lpKeyName,
        float      *pValues,
        int         nCount
    );
    virtual int GetStruct(
        const char  *lpSection,
        const char  *lpKeyName,
        void        *lpStruct,
        unsigned int dwSize
    );
    virtual int GetBool(
        const char *lpSection,
        const char *lpKeyName,
        int        *pBool
    );

    //--------------- NOT support interface functions as below -----------------
    // So return false

    virtual int Save(const char *FileName)
    {
        return false;
    }
    virtual void EraseSection(const char *lpSection)
    {
        return;
    }
    virtual void EraseKey(const char *lpSection, const char *lpKey)
    {
        return;
    }
    virtual int WriteString(
        const char *lpSection,
        const char *lpKeyName,
        const char *lpString
    )
    {
        return false;
    }
    virtual int WriteInteger(
        const char *lpSection,
        const char *lpKeyName,
        int         Value
    )
    {
        return false;
    }
    virtual int WriteInteger2(
        const char *lpSection,
        const char *lpKeyName,
        int         Value1,
        int         Value2
    )
    {
        return false;
    }
    virtual int WriteMultiInteger(
        const char *lpSection,
        const char *lpKeyName,
        int        *pValues,
        int         nCount
    )
    {
        return false;
    }
    virtual int WriteMultiLong(
        const char *lpSection,
        const char *lpKeyName,
        long       *pValues,
        int         nCount
    )
    {
        return false;
    }
    virtual int WriteFloat(
        const char *lpSection,
        const char *lpKeyName,
        float       fValue
    )
    {
        return false;
    }
    virtual int WriteFloat2(
        const char *lpSection,
        const char *lpKeyName,
        float       fValue1,
        float       fValue2
    )
    {
        return false;
    }
    virtual int WriteMultiFloat(
        const char *lpSection,
        const char *lpKeyName,
        float      *pValues,
        int         nCount
    )
    {
        return false;
    }
    virtual int WriteStruct(
        const char  *lpSection,
        const char  *lpKeyName,
        void        *lpStruct,
        unsigned int dwSize
    )
    {
        return false;
    }

private:
    KG_Ini_SectionMap m_SectionMap;
};
#endif  // #ifndef __KG_INI_FILE_H__
