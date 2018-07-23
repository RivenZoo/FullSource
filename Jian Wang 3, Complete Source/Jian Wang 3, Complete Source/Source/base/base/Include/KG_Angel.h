////////////////////////////////////////////////////////////////////////////////
//
//  FileName    : KG_Angel.h
//  Version     : 1.0
//  Creater     : Wu Caizhong
//  Create Date : 2005-5-8 14:34:13
//  Comment     : 
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _INCLUDE_KG_ANGEL_H_
#define _INCLUDE_KG_ANGEL_H_

#include "KSUnknown.h"
#include "Common/KG_Memory.h"

// this define when check how to do when role data error
enum KG_ROLE_DATA_PROCESS_CODE
{
	KG_ROLE_DATA_OK,
    KG_ROLE_NOT_SAVE,
    KG_ROLE_SAVE_TO_EXCEPTION,
};

enum KG_STATISTIC_DATA_TYPE
{
    STATISTIC_BASE_INFO,
    STATISTIC_MOST_LEVEL_NAME_LIST,
    STATISTIC_VIRTUAL_CURRENCY
};

////////////////////////////////////////////////////////////////////////////////
class IKG_RoleInfo : public IUnknown
{
public:
    ////////////////////////////////////////////////////////////////////////////
    // @brief : Check role data.
    // @param uBufferSize   : [in] buffer size of pvRoleData point to 
    //                             maybe large than this function need.
    // @param pvRoleData    : [in] point to role's data
    // @param pErrorProcess : [out] specify how to process role data when 
    //                               function return failed. ignore it
    //                               when function return true.
    // @return : true if successful, false if failed.
    virtual int OnPackCheck(
        unsigned uBufferSize, 
        void *pvRoleData,
        KG_ROLE_DATA_PROCESS_CODE *pErrorProcess
    ) = 0;

    ////////////////////////////////////////////////////////////////////////////
    // @brief : Get name of role
    // @param uBufferSize    : [in] buffer size of pvRoleData point to.
    //                              maybe large than this function need.
    // @param pvRoleData     : [in] point to role data
    // @param puRoleNameSize : [out] role name size(include '\0')
    // @param ppvRoleName    : [out] point to role name
    // @return : true if successful, false if failed.
    virtual int GetRoleName(
        unsigned uBufferSize,   void *pvRoleData, 
        unsigned *puRoleNameSize, void **ppvRoleName
    ) = 0;
    
    ////////////////////////////////////////////////////////////////////////////
    // @brief : Get account name of role
    // @param uBufferSize       : [in] buffer size of pvRoleData point to 
    //                                  maybe large than this function need.
    // @param pvRoleData        : [in] point to role data 
    // @param puAccountNameSize : [out] account name size(include '\0') 
    // @param ppvAccountName    : [out] point to account name 
    // @return : true if successful, false if failed.
    virtual int GetAccountName(
        unsigned uBufferSize, void *pvRoleData, 
        unsigned *puAccountNameSize, void **ppvAccountName
    ) = 0;
    

    ////////////////////////////////////////////////////////////////////////////
    // @brief : Get ID of role
    // @param uBufferSize       : [in] buffer size of pvRoleData point to 
    //                                  maybe large than this function need.
    // @param pvRoleData        : [in] point to role data 
    // @param puRetRoleIDSize   : [out] Size of ID
    // @param pvRetRoleID       : [out] Pointer which point the ID position in pvRoleData
    // @return : true if successful, false if failed.
    virtual int GetRoleID(
        unsigned uBufferSize,
        void *pvRoleData,
        unsigned* puId
    ) = 0;

    ////////////////////////////////////////////////////////////////////////////
    // @brief : Get account's role list item's information
    // @param uBufferSize        : [in] buffer size of pvRoleData point to 
    //                                  maybe large than this function need.
    // @param pvRoleData         : [in] point to role data 
    // @param puRoleListItemSize : [in] buffer size of pvRoleListItem
    //                                  maybe large than this function need.
    //                             [out] bytes real store to buffer
    // @param pvRoleListItem     : [out] specify buffer to store result
    // @return : true if successful, false if failed.
    virtual int GetRoleListItem(
        unsigned uBufferSize, void *pvRoleData, 
        unsigned *puRoleListItemSize, void *pvRoleListItem
    ) = 0;  

    ////////////////////////////////////////////////////////////////////////////
    // @brief : Get max size of account's role list item
    virtual unsigned GetRoleListItemMaxSize() = 0;

    ////////////////////////////////////////////////////////////////////////////
    // @brief : Get role list information from a set of role list item
    // @param uBufferSize     : [in] specify buffer size of pvRoleListItems 
    // @param pvRoleListItems : [in] a buffer contain role list information set.
    // @param puBufferSize    : [in] buffer size of pvRoleList 
    //                          [out] bytes store to buffer pvRoleList
    // @param pvRoleList      : [out] specify buffer to contain result.
    // @return : true if successful, false if failed.
    // @remark : buffer format of pvRoleListItems point to:
    //      unsigned uItemCount
    //      unsigned uRoleListItem1Size
    //      unsigned char aRoleListItem1[uRoleListItem1Size]
    //      unsigned uRoleListItem2Size
    //      unsigned char aRoleListItem2[uRoleListItem2Size]
    //      ....
    virtual int GetRoleList(
        unsigned uBufferSize, void *pvRoleListItems,
        unsigned *puRoleListBufferSize, void *pvRoleList        
    ) = 0;    

    ////////////////////////////////////////////////////////////////////////////////
    // @brief : Get max buffer size for account info
    virtual unsigned GetRoleListMaxSize() = 0;
    
    ////////////////////////////////////////////////////////////////////////////
    // @brief : Get role data size
    // @param uBufferSize    : [in] buffer size of pvRoleData point to 
    //                               maybe large than this function need. 
    // @param pvRoleData     : [in] point to role data
    // @param puRoleDataSize : [out] point to role data
    // @return : true if successful, false if failed.
    virtual int GetRoleDataSize(
        unsigned uBufferSize, void *pvRoleData, unsigned *puRoleDataSize
    ) = 0;

    ////////////////////////////////////////////////////////////////////////////
    // @brief : Copy name of role to a buffer 
    // @param uBufferSize         : [in] buffer size of pvRoleData point to.
    //                                   maybe large than this function need.
    // @param pvRoleData          : [in] point to role data
    // @param uRoleNameBufferSize : [in] buffer size of pszRoleName point to, 
    //                                   should above 1 bytes.
    // @param pszRoleName         : [out] a buffer to store role name, role name
    //                                    is terminal with '\0'.
    // @return : true if successful, false if failed.
    virtual int CopyRoleName(
        unsigned uBufferSize, void *pvRoleData, 
        unsigned uRoleNameBufferSize, char *pszRoleName
    ) = 0;

    ////////////////////////////////////////////////////////////////////////////
    // @brief : Copy account name of role to a buffer 
    // @param uBufferSize            : [in] buffer size of pvRoleData point to.
    //                                      maybe large than this function need.
    // @param pvRoleData             : [in] point to role data
    // @param uAccountNameBufferSize : [in] buffer size of pszAccount point to, 
    //                                      should above 1 bytes.
    // @param pszAccountName         : [out] a buffer to store account, 
    //                                       is terminal with '\0'.
    // @return : true if successful, false if failed.
    virtual int CopyAccountName(
        unsigned uBufferSize, void *pvRoleData, 
        unsigned uAccountNameBufferSize, char *pszAccountName
    ) = 0;

    ////////////////////////////////////////////////////////////////////////////
    // @param uBufferSize : [in] buffer size of pvRoleData point to.
    //                           maybe large than this function need.
    // @param pvRoleData  : [in] point to role data
    // @param cszNewName  : [in] new role name
    // @return : true if successful, false if failed.
    virtual int SetRoleName(
        unsigned uBufferSize, void *pvRoleData, const char cszNewName[]
    ) = 0;

    ////////////////////////////////////////////////////////////////////////////
    // @param uBufferSize : [in] buffer size of pvRoleData point to.
    //                           maybe large than this function need.
    // @param pvRoleData  : [in] point to role data
    // @param cszNewName  : [in] new account name
    // @return : true if successful, false if failed.
    virtual int SetAccountName(
        unsigned uBufferSize, void *pvRoleData, const char cszNewName[]
    ) = 0;

    ////////////////////////////////////////////////////////////////////////////
    // @brief : Get ID of role
    // @param uBufferSize       : [in] buffer size of pvRoleData point to 
    //                                  maybe large than this function need.
    // @param pvRoleData        : [in/out] point to role data 
    // @param uRoleID          : [in] This ID is just a propositional value,
    //                                function can use another value as ID perhaps;
    //                                If you want know the actual ID,
    //                                you should invoke GetRoleID() after this function. 
    // @return : true if successful, false if failed.
    virtual int SetRoleID(unsigned uBufferSize, void *pvRoleData, unsigned uRoleID) = 0;

    ////////////////////////////////////////////////////////////////////////////
    // @brief : Modify role data
    // @param uOrgRoleDataSize       : [in]
    // @param pvOrgRoleData          : [in]
    // @param uNewRoleDataBufferSize : [in]
    // @param puNewRoleDataSize      : [out]
    // @param pvNewRoleData          : [out]
    // @param nModifiedFlag          : [out] if set to true, means role data has
    //                                       been modified. if set to false.the
    //                                       caller should ignore 
    //                                       puNewRoleDataSize and pvNewRoleData
    // @return : true if successful, false if failed.
    virtual int ModifyRoleData(
        unsigned uOrgRoleDataSize, void *pvOrgRoleData,
        unsigned uNewRoleDataBufferSize, 
        unsigned *puNewRoleDataSize, void *pvNewRoleData,
        int *nModifiedFlag
    ) = 0;

	//////////////////////////////////////////////////////////////////////////
	virtual int GetCreateRoleMaxBufferSize() = 0;

	//////////////////////////////////////////////////////////////////////////
	virtual int GetMultiRolesPackMaxSize() = 0;

	//////////////////////////////////////////////////////////////////////////
	virtual int GetFamilyNodeFromPack(
		void* Pack,
		unsigned& uNodeSize,	void* prFamilyNode) = 0;

	//////////////////////////////////////////////////////////////////////////
	virtual int	GetRoleNodeFromPack(
		void* Pack,				unsigned uIdx,
		unsigned& uNodeSize,	void* prRoleNode) = 0;
	
	//////////////////////////////////////////////////////////////////////////
	virtual int GetRoleIdFromNode(
		void* Node,				unsigned long long& ullRoleId) = 0;

	//////////////////////////////////////////////////////////////////////////
	virtual int GetRoleNameFromNode(
		void* Node,
		unsigned* puNameSize,	char** ppName) = 0;

	//////////////////////////////////////////////////////////////////////////
	virtual int GetPairNameFromCreateParam(
		void* Param,			unsigned uParamSize,
		char** ppFamily,		char** ppRole) = 0;

	//////////////////////////////////////////////////////////////////////////
	virtual int	PackRoleData(
		void* Pack,				unsigned& uPakcSize,
		void* pvNode,			unsigned uNodeSize,
		DWORD dwFlag) = 0;

	//////////////////////////////////////////////////////////////////////////
	virtual	void WatchePackData(void* Pack) = 0;

	//////////////////////////////////////////////////////////////////////////
	virtual int AnalyzeRoleOperPack(
		void* OperPack,			int& eOper,
		unsigned& uFamilyId,		char* szFamilyName,
		unsigned long long& ullRoleId,
		char* szRoleName,		void* pvData,
		int& uRoleDataSize) = 0;

	//////////////////////////////////////////////////////////////////////////
	virtual int ModifyRoleData(
		void* RoleData,			int& nSize,
		unsigned long long* ullRoleId, const char* szName) = 0;

	//////////////////////////////////////////////////////////////////////////
	virtual int FetchRoleRestoreData(void* RoleData, void* pvData) = 0;

	//////////////////////////////////////////////////////////////////////////
	virtual void CreateRoleOperReply(
		void* OperPack,			void* pvReply,
		int& nReplySize,
		void* pvBuff,			int nSize) = 0;
};

////////////////////////////////////////////////////////////////////////////////
class IKG_RoleProcessor : public IUnknown
{
public:
    virtual int Init(void *pvContent) = 0;

    virtual int UnInit(void *pvContent) = 0;

    virtual int SetStatisticData(
        KG_STATISTIC_DATA_TYPE eDataType, IKG_Buffer *pStatistic
    ) = 0;

    ////////////////////////////////////////////////////////////////////////////
    // @param pnContinueFlag  : [out] return false to prevent load
    //                                invalid if function return false.
    virtual int OnRoleLoadFromDatabase(
        unsigned uRoleDataSize, void *pvRoleData, int *pnContinueFlag
    ) = 0;

    // @param pnContinueFlag  : [out] return false to prevent save
    //                                invalid if function return false.
    virtual int OnRoleSaveToDatabase(
        unsigned uRoleDataSize, void *pvRoleData, int *pnContinueFlag
    ) = 0;

	//////////////////////////////////////////////////////////////////////////
	virtual int OnPackCheck(void* Pack, unsigned uSize) = 0;

    ////////////////////////////////////////////////////////////////////////////
    // @brief : Create a new role
    // @return : true if successful, false if failed.
    // @remark : must call LoadCreateRoleConfig() first.
	virtual int CreateRole(
		unsigned	uCreateParamSize,	void* pvCreateParam,
		unsigned	uFamilyId,			unsigned long long ullRoleId,
		unsigned&	uPackSize,			void* Pack) = 0;
};

////////////////////////////////////////////////////////////////////////////////

class IKG_Statistic : public IUnknown
{
public:
    virtual int Begin(void *pvContext) = 0;

    virtual int OnceStatiticOperation(
        unsigned int uRoleDataSize, const void *pvRoleData
    ) = 0;

    virtual int End(void *pvContext) = 0;    

    virtual int GetStatisticData(
        KG_STATISTIC_DATA_TYPE eDataType, IKG_Buffer **ppStatistic
    ) = 0;

};



class IKG_BishopProcessor : public IUnknown
{
public:
    ////////////////////////////////////////////////////////////////////////////
    // @brief : Check role data.
    // @param uBufferSize   : [in] buffer size of pvRoleData point to 
    //                             maybe large than this function need.
    // @param pvRoleData    : [in] point to role's data
    // @return : true if successful, false if failed.
    virtual int CheckRoleDataCRC(unsigned uBufferSize, void *pvRoleData) = 0;
	virtual int OnPackCheck(void* Pack, unsigned uSize) = 0;

    ////////////////////////////////////////////////////////////////////////////
    // @brief : Get role name from role data .
    // @param uBufferSize  : [in] buffer size of pvRoleData point to.
    //                            maybe large than this function need.
    // @param pvRoleData   : [in] point to role data
    // @param ppszRoleName : [out] point to role name
    // @return : role name
    virtual char *GetRoleNameFromPackData(unsigned uBufferSize,  void *Pack) = 0;
   

    virtual int GetNormalRoleCountFromList(unsigned uBufferSize, void *pvRoleListData) = 0;
    virtual int GetFreezedRoleCountFromList(unsigned uBufferSize, void *pvRoleListData) = 0;

    virtual int GetNormalRoleNameFromList(
        unsigned uBufferSize, 
        void *pvRoleListData, 
        int nIndex, 
        char szRoleName[], 
        int nNameBufferSize
    ) = 0;

    virtual int GetFreezedRoleNameFromList(
        unsigned uBufferSize, 
        void *pvRoleListData, 
        int nIndex, 
        char szRoleName[], 
        int nNameBufferSize
    ) = 0;

    virtual int GetRoleNameFromPlayerCreateRoleParam(
        unsigned uParamSize, 
        void *pvCreateRoleParam,
        char szRoleName[],
        int nNameBufferSize
    ) = 0;

    virtual int GetGoddessCreateRoleParamSize() = 0;

    virtual int GetGoddessCreateRoleParam(
        unsigned uGoddessParamSize, void *pvGoddessParam, // output
        unsigned uPlayerParamSize, void *pvPlayerCreateRoleParam, // input
        const char cszAccountName[]
    ) = 0;
    

    ////////////////////////////////////////////////////////////////////////////
    // @brief : Call back function, be call when role list will be send to client.
    // @param uBufferSize : [in] specify buffer size of pvRoleList 
    // @param pvRoleList  : [in] buffer contain role list
    // @return : true if successful, false if failed.
    virtual int OnSendRoleList(unsigned uBufferSize, void *pvRoleList, unsigned uPackSize, void* pvPackData) = 0;

    ////////////////////////////////////////////////////////////////////////////
    // @brief : Call back function
    // @param uBufferSize   : [in] packet size of pvQueryPacket
    // @param pvQueryPacket : [in] buffer contain whole packet from player
    // @return : true if successful, false if failed.
    virtual int OnEnterGameRequest(unsigned uBufferSize, void *pvQueryPacket) = 0;    

    virtual int GetRoleDataFlag(
        unsigned uRoleDataBufferSize, void *Pack,
        int *pnEnterGameID 
    ) = 0;

    // cFightMode, reset CRC. 
    virtual int SetRoleDataFlag(   
        unsigned uRoleDataBufferSize, void *Pack,
        char cFightMode 
    ) = 0;
};


extern "C" 
{

////////////////////////////////////////////////////////////////////////////////
// @brief : Initialize interface.
// @param pvContext : [in] reserved
// @return : true if successful, false if failed.
int __stdcall KG_AngelInit(void *pvContext);

////////////////////////////////////////////////////////////////////////////////
// @param puMainVersion : [out] 1: sword1, 2: sword2, 3: sword3
// @param puSubVersion  : [out] version number of each product
int __stdcall KG_GetAngelVersion(
    unsigned *puMainVersion, unsigned *puSubVersion
);

////////////////////////////////////////////////////////////////////////////////
// @brief : Get a interface of role information
// @return : interface point, if failed, is NULL
// @remark :1. must call KG_AngelInit() first
//          2. call IKG_RoleInfo::Release() to release resource.
IKG_RoleInfo *__stdcall KG_CreateRoleInfo();

////////////////////////////////////////////////////////////////////////////
// @berief : Get a interface of statistic.
// @return : Interface pointer, if failed, is NULL.
// @remark :
IKG_Statistic *__stdcall KG_CreateStatistic();

IKG_RoleProcessor *__stdcall KG_CreateRoleProcessor();

IKG_BishopProcessor *__stdcall KG_CreateBishopProcessor();

////////////////////////////////////////////////////////////////////////////////
// @brief : Uninitialized interface.
// @param pvContext : [in] reserved
// @return : true if successful, false if failed.
int __stdcall KG_AngelUnInit(void *pvContext);

}//extern "C" 


#endif //_INCLUDE_KG_ANGEL_H_
