////////////////////////////////////////////////////////////////////////////////
//  FileName    : KGD_Interface.h
//  Version     : 1.0
//  Creater     : Wu Caizhong
//  Create Date : 2005-01-17 19:58:08
//  Comment     : define database client interface 
//                This interface in not thread safe, 
//                not use one interface in multithread.
////////////////////////////////////////////////////////////////////////////////

#ifndef _INCLUDE_KGD_INTERFACE_H_
#define _INCLUDE_KGD_INTERFACE_H_

#include "KSUnknown.h"

////////////////////////////////////////////////////////////////////////////////
// buffer size store database, table, field name,
const unsigned KGD_NAME_BUFFER_MAX_SIZE     = 32;  

// one Table contain max field count
const unsigned KGD_MAX_FIELD_COUNT          = 64;

// max data size of type KGD_TYPE_CHAR, KGD_TYPE_VARCHAR, 
// KGD_TYPE_BINARY,KGD_TYPE_VARBINARY
const unsigned KGD_TINY_FIELD_MAX_DATA_SIZE     = 255;

// max size of type KGD_TYPE_TEXT, KGD_TYPE_BLOB
const unsigned KGD_MEDIUM_FIELD_MAX_DATA_SIZE   = 65535; 

const unsigned KGD_BLOB_OR_TEXT_INDEX_PREFIX_MAX_NUM = 255;

const unsigned KGD_DATETIME_SIZE        = sizeof("2005-01-01 12:00:00");
const unsigned KGD_INT32_SIZE           = sizeof(int);
const unsigned KGD_UNSIGNED_INT32_SIZE  = sizeof(unsigned);
const unsigned KGD_INT64_SIZE           = sizeof(long long);
const unsigned KGD_UNSIGNED_INT64_SIZE  = sizeof(unsigned long long);

////////////////////////////////////////////////////////////////////////////////
// field data type define
// NOTE: for compatible with old version, 
//       do not change element value, do not reuse deleted element's value
enum KGD_FIELD_TYPE
{
    KGD_TYPE_INT32              = 0x00, // 32 bit integer,  size = KGD_INT32_SIZE
    KGD_TYPE_UNSIGNED_INT32     = 0x01, // 32 bit unsigned integer, size = KGD_UNSIGNED_INT32_SIZE
    KGD_TYPE_INT64              = 0x02, // 64 bit integer,  size = KGD_INT64_SIZE
    KGD_TYPE_UNSIGNED_INT64     = 0x03, // 64 bit unsigned integer, size = KGD_UNSIGNED_INT64_SIZE
    KGD_TYPE_CHAR               = 0x04, // max size <= KGD_TINY_FIELD_MAX_DATA_SIZE
    KGD_TYPE_VARCHAR            = 0x05, // max size <= KGD_TINY_FIELD_MAX_DATA_SIZE
    KGD_TYPE_TEXT               = 0x06, // max size <= KGD_MEDIUM_FIELD_MAX_DATA_SIZE
    //KGD_TYPE_BINARY           = 0x07, // max size <= KGD_TINY_FIELD_MAX_DATA_SIZE
    //KGD_TYPE_VARBINARY        = 0x08, // max size <= KGD_TINY_FIELD_MAX_DATA_SIZE
    KGD_TYPE_BLOB               = 0x09, // max size <= KGD_MEDIUM_FIELD_MAX_DATA_SIZE
    KGD_TYPE_DATETIME           = 0x0A, // size = KGD_DATETIME_SIZE
};

// NOTE: for compatible with old version, 
//       do not change element value, do not reuse deleted element's value
enum KGD_FIELD_FLAG
{
    KGD_FIELD_NORMAL         = 0x00,  // normal field
    KGD_FIELD_INDEX          = 0x01,  // bit 0 set to 1, create index for field.
                                      // can't set with KGD_FIELD_UNIQUE_INDEX,
                                      // KGD_FIELD_PRIMARY_KEY and
                                      // KGD_FIELD_AUTO_INCREMENT

    KGD_FIELD_UNIQUE_INDEX   = 0x02,  // bit 1 set to 1, field value is unique
                                      // can't set with KGD_FIELD_INDEX,
                                      // KGD_FIELD_PRIMARY_KEY and
                                      // KGD_FIELD_AUTO_INCREMENT

    KGD_FIELD_PRIMARY_KEY    = 0x04,  // bit 2 set to 1, field is primary key.
                                      // only one field can set this flag.
                                      // can't set with KGD_FIELD_INDEX,
                                      // KGD_FIELD_UNIQUE_INDEX and
                                      // KGD_FIELD_AUTO_INCREMENT


    //KGD_FIELD_AUTO_INCREMENT = 0x08   // bit 3 set to 1,  Auto increment,
    //                                  // only set with type: KGD_TYPE_INT32 and
    //                                  // KGD_TYPE_INT64, this filed automatic
    //                                  // become a primary key.    
    //                                  // can't set with KGD_FIELD_INDEX,
    //                                  // KGD_FIELD_UNIQUE_INDEX and 
    //                                  // and KGD_FIELD_PRIMARY_KEY
};

// NOTE: for compatible with old version, 
//       do not change element value, do not reuse be deleted element's value
enum KGD_CREATE_FLAG
{
    KGD_CREATE_IF_NOT_EXIST = 0x01  // bit0 set, if not exist, create a new one.
                                    // if exist, do nothing and return true.
};

// NOTE: for compatible with old version, 
//       do not change element value, do not reuse be deleted element's value
enum KGD_RESULT_FLAG
{
    KGD_RESULT_STORE    = 0x01,     // bit0 set, cache all query result to 
                                    // memory. you must insure you has enough
                                    // memory to store the result set.
                                    // need more memory, bu quick then
                                    // KGD_RESULT_USE
                                    // ** if you use this flag, you can keep more
                                    // then one result set.                                  

    KGD_RESULT_USE      = 0x02      // bit1 set, do not cache all query result.
                                    // need less memory, but slower then 
                                    // KGD_RESULT_STORE
                                    // ** if you use this flag, means that you
                                    // just can keep one result set
};

// NOTE: for compatible with old version, 
//       do not change element value, do not reuse deleted element's value
enum KGD_OPERATOR
{
    KGD_OPERATOR_NONE        = 0x00,   // none operator
    KGD_OPERATOR_LESS        = 0x01,   //  .. <  .. 
    KGD_OPERATOR_LESS_EQUAL  = 0x02,   //  .. <= .. 
    KGD_OPERATOR_EQUAL       = 0x03,   //  .. =  .. 
    KGD_OPERATOR_NOT_EQUAL   = 0x04,   //  .. != .. 
    KGD_OPERATOR_ABOVE       = 0x05,   //  .. >  .. 
    KGD_OPERATOR_ABOVE_EQUAL = 0x06    //  .. >= .. 
};

// NOTE: for compatible with old version, 
//       do not change element value, do not reuse be deleted element's value
enum KGD_ENGINE_TYPE
{
    KGD_ENGINE_DEFAULT  = 0x00    // use default database engine
    //KGD_ENGINE_MYSQL    = 0x01     // use MySQL as database engine
};

// NOTE: for compatible with old version, 
//       do not change element value, do not reuse deleted element's value
enum KGD_ERROR_CODE
{
    KGD_ERROR_SUCCESS               = 0x00,
    KGD_ERROR_UNKNOW                = 0x01, 

    KGD_ERROR_NULL_POINTER          = 0x02,
    KGD_ERROR_EMPTY_STRING          = 0x03,
    KGD_ERROR_TABLE_NOT_EXIST       = 0x04,
    KGD_ERROR_FIELD_NOT_EXIST       = 0x05,
    KGD_ERROR_FIELD_COUNT_IS_ZERO   = 0x06,
    KGD_ERROR_TOO_MANY_FIELD        = 0x07,
    KGD_ERROR_NAME_TOO_LONG         = 0x08, 
    KGD_ERROR_DATA_TOO_LONG         = 0x09, 
    KGD_ERROR_MAX_DATA_TOO_LONG     = 0x0A,

    KGD_ERROR_INVALID_TYPE          = 0x0B, 
    KGD_ERROR_INVALID_OPERATOR      = 0x0C, 
    KGD_ERROR_INVALID_FLAG          = 0x0D, 
    KGD_ERROR_INVALID_INDEX         = 0x0E,
    KGD_ERROR_NOT_SUPPORT           = 0x0F,
  
    KGD_ERROR_RESOURCE_NOT_RELEASE  = 0x10,
    KGD_ERROR_CAN_NOT_CALL_THIS_NOW = 0x11, 
    KGD_ERROR_CONNECT_LOST          = 0x12,
    KGD_ERROR_NO_MORE_ROW           = 0x13,
    KGD_ERROR_NOT_ENOUGH_MEMORY     = 0x14,
    KGD_ERROR_DATABASE_ENGINE_ERROR = 0x15 
};

////////////////////////////////////////////////////////////////////////////////
// Contain filed information
// zero fill this struct when first use, then set information need
typedef struct KGD_FIELD
{
    // ----------------- information ------------------ 
    char szName[KGD_NAME_BUFFER_MAX_SIZE];  // Filed name, NULL terminal string.

    KGD_FIELD_TYPE  Type;                   // Data type that field contain.

    unsigned        uMaxDataSize;           // max size of uDataSize member
                                            // this value is limited by filed
                                            // type. see more information at the
                                            // define of KGD_FIELD_TYPE 

    int             nFlag;                  // another information about filed.
                                            // set one of more value of type 
                                            // KGD_FIELD_FLAG
    // -------------------- value  -------------------- 
    unsigned        uDataSize;              // byte of pvData point to. 
                                            // if point to string, 
                                            // include the terminal '\0'.

    void            *pvData;                // point to data buffer
                                            // for NULL field, set to NULL
} KGD_FIELD;


////////////////////////////////////////////////////////////////////////////////
// IKGD_Result manage the memory of returned result set.
class IKGD_Result : public IUnknown
{
public:

    ////////////////////////////////////////////////////////////////////////////
    // @brief : Retrieves the next row of a result set.
    // @return : true  when success move to next row.
    //           false when there are no more rows to retrieve 
    //           or an error occurred.
    virtual int NextRow() = 0;
    
    ////////////////////////////////////////////////////////////////////////////
    // @brief : Returns the value describe for the specify field of current row
    // @param uIndex    : [in] Field index, start from zero. The order of fields
    //                         is same as user specify in query function.
    // @param pRetField : [out] will set uDataSize and pvData member.
    // @return : true if successful, false if failed.
    // @remark : Before call this, you should make a success call of NextRow(),
    //           and call NextRow() after this to access next row.
    virtual int GetCurrentRowField(unsigned uIndex, KGD_FIELD *pRetField)= 0;

    ////////////////////////////////////////////////////////////////////////////
    // @return : Returns the number of rows. 
    // @remark : when is create by KGD_RESULT_USE, this function does not 
    //           return the correct value until all the rows in the result set 
    //           have been retrieved(will return -1).
    virtual int GetRowCount() = 0;

    ////////////////////////////////////////////////////////////////////////////
    // @return : The count of filed in result set.
    virtual unsigned GetFieldCount() = 0;

    ////////////////////////////////////////////////////////////////////////////
    // @return : Last error code. see more at define of KGD_ERROR_CODE
    virtual int GetLastErrorCode() = 0;
};

////////////////////////////////////////////////////////////////////////////
class IKGD_Database : public IUnknown
{
public:    
    ////////////////////////////////////////////////////////////////////////////
    // @brief :  Create new database.
    // @param cszDatabaseName : [in] Null terminal string, specify database name
    // @param nCreateFlag     : [in] See more in define of KGD_CREATE_FLAG.
    // @return : true if successful, false if failed.
    virtual int CreateDatabase(
        const char cszDatabaseName[KGD_NAME_BUFFER_MAX_SIZE], 
        int nCreateFlag
    ) = 0;
    
    ////////////////////////////////////////////////////////////////////////////
    // @brief : Remove an exist database.
    // @param cszDatabaseName : [in] Null terminal string, specify database name
    // @return : true if successful, false if failed.
    virtual int RemoveDatabase(
        const char cszDatabaseName[KGD_NAME_BUFFER_MAX_SIZE]
    ) = 0;    
    
    ////////////////////////////////////////////////////////////////////////////
    // @brief : Set current database,
    // @param cszDatabaseName : [in] Null terminal string, specify database name
    // @return : true if successful, false if failed.
    virtual int SetCurrentDatabase(
        const char cszDatabaseName[KGD_NAME_BUFFER_MAX_SIZE]
    ) = 0;        
    
    ////////////////////////////////////////////////////////////////////////////
    // @brief : Create a new table in current database
    // @param cszTableName : [in] Null terminal string, specify table name.
    // @param uFieldCount  : [in] Element count in param caFields.
    // @param caFields     : [in] An array specify initial field in table.
    //                            should set szName, Type, uMaxDataSize, nFlag
    // @param nCreateFlag  : [in] see more in define of KGD_CREATE_FLAG.
    // @return : true if successful, false if failed.
    virtual int CreateTable(
        const char cszTableName[KGD_NAME_BUFFER_MAX_SIZE],
        unsigned uFieldCount,
        const KGD_FIELD caFields[],
        int nCreateFlag
    ) = 0;
    
    ////////////////////////////////////////////////////////////////////////////
    // @brief : Remove table from current database
    // @param cszTableName : [in] Null terminal string, specify table name.
    // @return : true if successful, false if failed.
    virtual int RemoveTable(
        const char cszTableName[KGD_NAME_BUFFER_MAX_SIZE]
    ) = 0;

    ////////////////////////////////////////////////////////////////////////////
    // @brief : Add new fields to the table of current database.
    // @param cszTableName : [in] Null terminal string, specify table name.
    // @param uFieldCount  : [in] element count of array caFields
    // @param caFields     : [in] an array, describe fields information.
    //                            should set szName, Type, uMaxDataSize, nFlag
    // @return : true if successful, false if failed.
    virtual int AddField(
        const char cszTableName[KGD_NAME_BUFFER_MAX_SIZE], 
        unsigned uFieldCount,
        const KGD_FIELD caFields[] 
    ) = 0;

    ////////////////////////////////////////////////////////////////////////////
    // @brief : Remove fields from table of current database.
    // @param cszTableName : [in] Null terminal string, specify table name.
    // @param uFieldCount  : [in] element count of array caFields
    // @param caFields     : [in] should set element's szName member.
    // @return : true if successful, false if failed.
    virtual int RemoveField(
        const char cszTableName[KGD_NAME_BUFFER_MAX_SIZE], 
        unsigned uFieldCount,
        const KGD_FIELD caFields[] 
    ) = 0;

    ////////////////////////////////////////////////////////////////////////////
    // @brief : Query record from table of current database
    //     SELECT (caResultFields[0].szName[, caResultFields[1].szName, ...])
    //     FROM cszTableName
    //     [WHERE pcMatchField1.szName Operator1 *pcMatchField1.pvData 
    //        [AND pcMatchField2.szName Operator2 *pcMatchField2.pvData]
    //     ]
    // @param cszTableName      : [in] Null terminal string, specify table name
    // @param uResultFieldCount : [in] Element count of caResultFields.
    // @param caResultFields    : [in] should set element's szName member 
    // @param pcMatchField1     : [in] if not NULL, set szName,uDataSize, pvData
    // @param Operator1         : [in] be ignore if pcMatchField1 is NULL
    // @param pcMatchField2     : [in] if not NULL, set szName,uDataSize, pvData
    // @param Operator2         : [in] be ignore if pcMatchField2 is NULL
    // @return : true if successful, false if failed.
    // @remark : if you make a success call of this function,
    //           you "must" call GetQueryResult() to access result.
    virtual int Query(
        const char cszTableName[KGD_NAME_BUFFER_MAX_SIZE], 
        unsigned uResultFieldCount,
        const KGD_FIELD caResultFields[], 
        const KGD_FIELD *pcMatchField1, 
        KGD_OPERATOR Operator1,
        const KGD_FIELD *pcMatchField2, 
        KGD_OPERATOR Operator2
    ) = 0;

    ////////////////////////////////////////////////////////////////////////////
    // @brief : Get query result of success call of Query()
    // @param Flag : [in] specify how to process result set. 
    //                    see more at define of KGD_RESULT_FLAG
    // @return : if success, return a interface of IKGD_Result to access result. 
    //           if failed, return NULL.
    // @remark : 1.only can and must be call after success call of Query() 
    //           2.call IKGD_Result->Release to free result.
    virtual IKGD_Result *GetQueryResult(KGD_RESULT_FLAG Flag) = 0;

    ////////////////////////////////////////////////////////////////////////////
    // @brief : Update record for specify table of current database
    //     UPDATE cszTableName
    //     SET caBeUpdateFields[0].szName = *caBeUpdateFields[0].pvData
    //         [, caBeUpdateFields[1].szName = *caBeUpdateFields[1].pvData, ...]
    //     [WHERE pcMatchField1.szName Operator1 *pcMatchField1.pvData 
    //        [AND pcMatchField2.szName Operator2 *pcMatchField2.pvData]
    //     ]
    // @param cszTableName     : [in] Null terminal string, specify table name
    // @param uFieldCount      : [in] Element count in param caBeUpdateFields.
    // @param caBeUpdateFields : [in] set element's szName, uDataSize, pvData
    // @param pcMatchField1    : [in] if not NULL, set szName, uDataSize, pvData
    // @param Operator1        : [in] be ignore if pcMatchField1 is NULL
    // @param pcMatchField2    : [in] if not NULL, set szName, uDataSize, pvData
    // @param Operator2        : [in] be ignore if pcMatchField2 is NULL
    // @return : true if successful, false if failed.
    virtual int Update(
        const char cszTableName[KGD_NAME_BUFFER_MAX_SIZE], 
        unsigned uFieldCount,
        const KGD_FIELD caBeUpdateFields[],
        const KGD_FIELD *pcMatchField1, 
        KGD_OPERATOR Operator1,
        const KGD_FIELD *pcMatchField2, 
        KGD_OPERATOR Operator2
    ) = 0;

    ////////////////////////////////////////////////////////////////////////////
    // @brief : Delete record from specify table of current database
    //     DELETE FROM cszTableName 
    //     [WHERE pcMatchField1.szName Operator1 *pcMatchField1.pvData 
    //        [AND pcMatchField2.szName Operator2 *pcMatchField2.pvData]
    //     ]
    // @param cszTableName  : [in] Null terminal string, specify table name
    // @param pcMatchField1 : [in] if not NULL, set szName, uDataSize, pvData
    // @param Operator1     : [in] be ignore if pcMatchField1 is NULL
    // @param pcMatchField2 : [in] if not NULL, set szName, uDataSize, pvData
    // @param Operator2     : [in] be ignore if pcMatchField2 is NULL
    // @return : true if successful, false if failed.
    virtual int Delete(
        const char cszTableName[KGD_NAME_BUFFER_MAX_SIZE], 
        const KGD_FIELD *pcMatchField1, 
        KGD_OPERATOR Operator1,
        const KGD_FIELD *pcMatchField2, 
        KGD_OPERATOR Operator2
    ) = 0;

    ////////////////////////////////////////////////////////////////////////////
    // @brief : Insert new record into specify table of current database
    //   INSERT INTO cszTableName(caFields[0].szName[, caFields[1].szName, ...])
    //   VALUES(*caFields[0].pvData[, *caFields[1].pvData, ...])
    // @param cszTableName : [in] Null terminal string, specify table name
    // @param uFieldCount  : [in] Element count in param caFields.
    // @param caFields     : [in] should set element's szName, uDataSize, pvData
    // @return : true if successful, false if failed.
    virtual int Insert(
        const char cszTableName[KGD_NAME_BUFFER_MAX_SIZE], 
        unsigned uFieldCount, 
        const KGD_FIELD caFields[]
    ) = 0;

    ////////////////////////////////////////////////////////////////////////////
    // @brief : Returns the affected row number by last call of Insert(), 
    //           Delete() or Update()
    // @return : >= 0 indicates the number of rows affected or retrieved
    //           -1   indicates that an error
    // @remark : 1.May be called immediately after Insert(),Delete() or Update()
    //           2. for Query(), call IKDG_Result::GetRowCount() to get count
    virtual int GetAffectedRow() = 0;

    ////////////////////////////////////////////////////////////////////////////
    // @return : Last error code. see more at define of KGD_ERROR_CODE
    virtual int GetLastErrorCode() = 0;

	//////////////////////////////////////////////////////////////////////////
	// @brief:	some time we have strong requirement for more...
	//			such as limit m,n group by field...
	//			param szSql[] of ExecSQL should be escape first use EscapeData
	virtual	int EscapeData(char* szEscaped, const char* szSrc, int nLength) = 0;
	virtual int ExecSQL(const char szSql[], unsigned int uLength) = 0;
};


////////////////////////////////////////////////////////////////////////////////
// @brief : initialize runtime environment 
// @param pvContext : [in] reserve, should set to NULL
// @return : true if successful, false if failed.
// @remark : each process just need call once
int KGD_Init(void *pvContext);

////////////////////////////////////////////////////////////////////////////////
// @brief : 
// @param pvContext : [in] reserve, should set to NULL
// @return : true if successful, false if failed.
// @remark : call to release resource
int KGD_Uninit(void *pvContext);

////////////////////////////////////////////////////////////////////////////////
// @brief : Connect to database server
// @param EngineType          : [in] specify engine type.
// @param cszServerName       : [in] specify database server name or ip.
// @param usPort              : [in] Specify database server listen port.
// @param cszUserName         : [in] specify user name to connect to database
// @param cszPassword         : [in] specify password.
// @param pcszCurrentDatabase : [in] Null terminal string, max buffer size is 
//                                   KGD_NAME_BUFFER_MAX_SIZE, specify current
//                                   database after connected. 
//                                   Can be NULL, if set to NULL, you should
//                                   call IKGD_Database::SetCurrentDatabase()
//                                   before do anything relate to a table.
// @return : If success, return a Point to IKGD_Database, else return NULL.
// @remark : 1. call KGD_Init() first
//           2. call IKGD_Database->Release to free resource.
IKGD_Database *KGD_Connect(
    KGD_ENGINE_TYPE EngineType,
    const char cszServerName[], 
    unsigned short usPort, 
    const char cszUserName[], 
    const char cszPassword[],
    const char *pcszCurrentDatabase
);

#endif //_INCLUDE_KGD_INTERFACE_H_
