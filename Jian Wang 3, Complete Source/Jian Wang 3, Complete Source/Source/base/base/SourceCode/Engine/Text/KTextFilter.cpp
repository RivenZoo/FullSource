#include "Precompile.h"
#include <wctype.h>
#include <stdlib.h>
#include <wchar.h>
#include <set>
#include <string>
#include "KG_InterlockedVariable.h"
#include "KSUnknown.h"
#include "KGPublic.h"
#include "KGLog.h"
#include "KTextFilter.h"
#include "File.h"

using namespace std;

#define MAX_TEXT_LEN  1024

class KTextFilter : public ITextFilter
{
public:
    KTextFilter();

    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppvObject);
    ULONG STDMETHODCALLTYPE AddRef(void);
    ULONG STDMETHODCALLTYPE Release(void);

    BOOL LoadFilterFile(const char cszFilterFile[]);

    BOOL AddFilterText(const char cszFilterText[]);

    void ClearAll()
    {
        m_FilterList.clear();
    }

    BOOL Check(char* pszTextAnsi);

    BOOL Replace(char* pszTextAnsi);

private:
    BOOL PreProcessText(const char* pszTextAnsi, int nAnsiLen);

    BOOL MatchOne(wchar_t* pszText, const wchar_t* pszFilter);
    BOOL MatchSub(wchar_t* pszText, const wchar_t* pszFilter);

private:    
    typedef std::set<std::wstring> KFILTER_TABLE;
    KFILTER_TABLE m_FilterList;

    wchar_t         m_szWCharTextRaw[MAX_TEXT_LEN];
    wchar_t         m_szWCharTextTmp[MAX_TEXT_LEN];
    wchar_t         m_cReplaceChar;
    int             m_nReplaceCount;
    ULONG           m_ulRefCount;
};

KTextFilter::KTextFilter()
{
    m_cReplaceChar  = '\0';
    m_nReplaceCount = 0;
    m_ulRefCount    = 1;
}

HRESULT STDMETHODCALLTYPE KTextFilter::QueryInterface(REFIID riid, void** ppvObject)
{
    KG_USE_ARGUMENT(riid);
    KG_USE_ARGUMENT(ppvObject);
    return KG_E_FAIL;
}

ULONG STDMETHODCALLTYPE KTextFilter::AddRef(void)
{
    return (ULONG)KG_InterlockedIncrement((long*)&m_ulRefCount);
}

ULONG STDMETHODCALLTYPE KTextFilter::Release(void)
{
    ULONG ulCount = KG_InterlockedDecrement((long*)&m_ulRefCount);
    if (ulCount == 0)
    {
        delete this;
    }
    return ulCount;
}

BOOL KTextFilter::LoadFilterFile(const char cszFilterFile[])
{
    BOOL    bResult                 = false;
    BOOL    bRetCode                = false;
    IFile*  piFile                  = NULL;
    size_t  uFileSize               = 0;
    size_t  uReadSize               = 0;
    char*   pszBuffer               = NULL;
    char*   pszFilterText           = NULL;
    char*   pszPos                  = NULL;
    int     nLine                   = 0;

    assert(cszFilterFile);

    piFile = g_OpenFile(cszFilterFile);
    KGLOG_PROCESS_ERROR(piFile);

    uFileSize = piFile->Size();
    KGLOG_PROCESS_ERROR(uFileSize > 0);

    pszBuffer = new char[uFileSize + 1];
    KGLOG_PROCESS_ERROR(pszBuffer);

    uReadSize = piFile->Read(pszBuffer, uFileSize);
    KGLOG_PROCESS_ERROR(uReadSize == uFileSize);

    pszBuffer[uFileSize] = '\n';

    pszFilterText = pszBuffer;
    pszPos        = pszBuffer;

    while (true)
    {
        if (*pszPos == '\n')
        {
            *pszPos = '\0';

            nLine++;

            bRetCode = AddFilterText(pszFilterText);
            if (!bRetCode)
            {
                KGLogPrintf(KGLOG_ERR, "Text filter error(%s : %d)\n", cszFilterFile, nLine);
            }

            pszFilterText = pszPos + 1;
        }

        if (pszPos == pszBuffer + uFileSize)
        {
            break;
        }

        pszPos++;
    }

    bResult = true;
Exit0:
    KG_DELETE_ARRAY(pszBuffer);
    KG_COM_RELEASE(piFile);
    return bResult;
}

BOOL KTextFilter::AddFilterText(const char cszFilterTextAnsi[])
{
    BOOL    bResult         = false;
    BOOL    bRetCode        = false;
    int     nFilterTextLen  = 0;

    assert(cszFilterTextAnsi);

    nFilterTextLen = (int)strlen(cszFilterTextAnsi);
    KGLOG_PROCESS_ERROR(nFilterTextLen >= 0);
    KGLOG_PROCESS_ERROR(nFilterTextLen < MAX_TEXT_LEN);

    bRetCode = PreProcessText(cszFilterTextAnsi, nFilterTextLen);
    KGLOG_PROCESS_ERROR(bRetCode);

    for (int i = 0; m_szWCharTextTmp[i] != '\0'; i++)
    {
        if (m_szWCharTextTmp[i] == '\r' || m_szWCharTextTmp[i] == '\n')
        {
            m_szWCharTextTmp[i] = '\0';
            break;
        }
    }

    if (m_szWCharTextTmp[0] != '\0')
    {
        m_FilterList.insert(std::wstring(m_szWCharTextTmp));
    }

    bResult = true;
Exit0:
    return bResult;
}

BOOL KTextFilter::Check(char* pszTextAnsi)
{
    BOOL                    bResult       = false;
    BOOL                    bRetCode      = false;
    int                     nAnsiLen      = 0;

    assert(pszTextAnsi);

    nAnsiLen = (int)strlen(pszTextAnsi);
    KGLOG_PROCESS_ERROR(nAnsiLen >= 0);
    KGLOG_PROCESS_ERROR(nAnsiLen < MAX_TEXT_LEN);

    bRetCode = PreProcessText(pszTextAnsi, nAnsiLen);
    KGLOG_PROCESS_ERROR(bRetCode);    

    m_cReplaceChar = '\0';

    for (KFILTER_TABLE::iterator it = m_FilterList.begin(); it != m_FilterList.end(); ++it)
    {
        bRetCode = MatchOne(m_szWCharTextTmp, it->c_str());
        if (bRetCode)
        {
            goto Exit0;
        }
    }

    bResult = true;
Exit0:
    return bResult;
}

BOOL KTextFilter::Replace(char* pszTextAnsi)
{
    BOOL                    bResult       = false;
    BOOL                    bRetCode      = false;
    int                     nAnsiLen      = 0;
    size_t                  uConvertCount = 0;

    assert(pszTextAnsi);

    if (pszTextAnsi[0] == '\0')
    {
        goto Exit1;
    }

    nAnsiLen = (int)strlen(pszTextAnsi);
    KGLOG_PROCESS_ERROR(nAnsiLen >= 0);
    KGLOG_PROCESS_ERROR(nAnsiLen < MAX_TEXT_LEN);

    bRetCode = PreProcessText(pszTextAnsi, nAnsiLen);
    KGLOG_PROCESS_ERROR(bRetCode);
 
    m_cReplaceChar = '*';

    for (KFILTER_TABLE::iterator it = m_FilterList.begin(); it != m_FilterList.end(); ++it)
    {
        do 
        {
            m_nReplaceCount = 0;

            MatchOne(m_szWCharTextTmp, it->c_str());

        } while (m_nReplaceCount > 0);
    }

    for (int i = 0; m_szWCharTextTmp[i] != '\0'; i++)
    {
        if (m_szWCharTextTmp[i] != m_cReplaceChar)
        {
            m_szWCharTextTmp[i] = m_szWCharTextRaw[i];
        }
    }

#ifdef WIN32
    uConvertCount = (size_t)::WideCharToMultiByte(
        CP_ACP,
        0,
        m_szWCharTextTmp, -1,
        pszTextAnsi, nAnsiLen + 1,
        NULL, NULL
    );
    if (uConvertCount == 0)
    {
        KGLogPrintf(KGLOG_ERR, "::WideCharToMultiByte failed! Error code : %d\n", GetLastError());
        goto Exit0;
    }
#else
    uConvertCount = wcstombs(pszTextAnsi, m_szWCharTextTmp, nAnsiLen + 1);
    KGLOG_PROCESS_ERROR(uConvertCount != (size_t)-1);
#endif

Exit1:
    bResult = true;
Exit0:
    return bResult;
}

BOOL KTextFilter::PreProcessText(const char* pszTextAnsi, int nAnsiLen)
{
    BOOL                    bResult       = false;
    size_t                  uConvertCount = 0;
    int                     nIndex        = 0;

#ifdef WIN32
    uConvertCount = (size_t)::MultiByteToWideChar(
        CP_ACP,
        MB_PRECOMPOSED | MB_ERR_INVALID_CHARS | MB_USEGLYPHCHARS,
        pszTextAnsi, nAnsiLen + 1,
        m_szWCharTextRaw, MAX_TEXT_LEN
    );
    if (uConvertCount == 0)
    {
        KGLogPrintf(KGLOG_ERR, "::MultiByteToWideChar failed! Error code : %d\n", GetLastError());
        goto Exit0;
    }
#else
    uConvertCount = mbstowcs(m_szWCharTextRaw, pszTextAnsi, MAX_TEXT_LEN);
    KGLOG_PROCESS_ERROR(uConvertCount != (size_t)-1);
#endif

    do
    {
        m_szWCharTextTmp[nIndex] = towlower(m_szWCharTextRaw[nIndex]);
    } while (m_szWCharTextRaw[nIndex++] != '\0');

    bResult = true;
Exit0:
    return bResult;
}

BOOL KTextFilter::MatchOne(wchar_t* pszText, const wchar_t* pszFilter)
{
    assert(pszText);
    assert(pszFilter);

    if (*pszFilter == '\0')
    {
        return true;
    }

    if (*pszFilter == '?')
    {
        if (MatchSub(pszText, pszFilter + 1))
        {
            return true;
        }

        return MatchSub(pszText + 1, pszFilter + 1);
    }

    if (*pszFilter == '*')
    {
        do 
        {
            if (MatchOne(pszText, pszFilter + 1))
            {
                return true;
            }
        } while (*pszText++ != '\0');

        return false;
    }

    if (*pszFilter == *pszText)
    {
        BOOL bMatch = MatchSub(pszText + 1, pszFilter + 1);

        if (bMatch && m_cReplaceChar != '\0')
        {
            *pszText = m_cReplaceChar;
            m_nReplaceCount++;
        }

        return bMatch;
    }

    return false;
}

BOOL KTextFilter::MatchSub(wchar_t* pszText, const wchar_t* pszFilter)
{
    assert(pszText);
    assert(pszFilter);

    if (*pszFilter == '?')
    {
        if (MatchSub(pszText, pszFilter + 1))
        {
            return true;
        }

        return MatchSub(pszText + 1, pszFilter + 1);
    }

    if (*pszFilter == '*')
    {
        do 
        {
            if (MatchOne(pszText, pszFilter + 1))
            {
                return true;
            }
        } while (*pszText++ != '\0');

        return false;
    }

    if (*pszFilter == *pszText)
    {
        if (*pszFilter == '\0')
        {
            return true;
        }

        BOOL bMatch = MatchSub(pszText + 1, pszFilter + 1);

        if (bMatch && m_cReplaceChar != '\0')
        {
            *pszText = m_cReplaceChar;
            m_nReplaceCount++;
        }

        return bMatch;
    }

    return false;
}

ITextFilter* CreateTextFilterInterface()
{
    return new KTextFilter;
}
