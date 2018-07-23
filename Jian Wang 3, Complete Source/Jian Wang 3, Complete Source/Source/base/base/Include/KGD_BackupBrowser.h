////////////////////////////////////////////////////////////////////////////////
//  Copyright(c) Kingsoft
//
//  FileName    : KGD_BackupBrowser.h
//  Version     : 1.0
//  Creator     : Hu Hao
//  Create Date : 2009-3-2 19:43:52
//  Comment     : Used to get information from backup file.
//                NOT thread safe, do not use one interface in multi-thread.
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _KGD_BACKUP_BROWSER_H_
#define _KGD_BACKUP_BROWSER_H_

#include "KSUnknown.h"

enum KGD_FETCH_RESULT
{
    KGD_FETCH_SUCCESS           = 0x00,
    KGD_FETCH_NO_MORE_RECORD    = 0X01,
    KGD_FETCH_CORRUPT_RECORD    = 0x02
};

////////////////////////////////////////////////////////////////////////////////
class IKGD_TableBrowser : public IUnknown
{
public:
    virtual int GetFieldCount(unsigned *puRetFieldCount) = 0;

    virtual int GetFieldName(
        unsigned uFieldIndex, const char **ppcszRetFieldName
    ) = 0;

    virtual int GetRecordCount(unsigned *puRetRecordCount) = 0;

    // @brief : Fetch the next record as current record, get the record data via
    //          GetCurrentRecordField() only if peRetFecthResult return
    //          KGD_FETCH_SUCCESS.
    virtual int FetchNextRecord(KGD_FETCH_RESULT *peRetFecthResult) = 0;

    virtual int GetCurrentRecordField(
        unsigned uFieldIndex, 
        unsigned *puRetFieldDataSize,
        const void **ppcvFieldData
    ) = 0;
};

////////////////////////////////////////////////////////////////////////////////
// @brief  : Initialize runtime environment for browser backup file.
// @remark : Each process just need call once.
int KGD_InitBackupBrowserEnvironment(void *pvContext);

////////////////////////////////////////////////////////////////////////////////
// @brief  : Free the resource initialized in KGD_InitBackupBrowserEnvironment().
int KGD_UnInitBackupBrowserEnvironment(void *pvContext);

////////////////////////////////////////////////////////////////////////////////
// @brief  : Open the table backup file and get table information.
// @param cszTableName      : The target table name.
// @param cszBackupFilePath : The table backup file path, not including file name.
// @remark : 1. Call KGD_InitBackupBrowserEnvironment() firstly.
//           2. Call IKGD_TableBrowser->Release() to free resource.
IKGD_TableBrowser *KGD_OpenTableBackupFile(
    const char cszTableName[], const char cszBackupFilePath[]
);

#endif  // _KGD_BACKUP_BROWSER_H_