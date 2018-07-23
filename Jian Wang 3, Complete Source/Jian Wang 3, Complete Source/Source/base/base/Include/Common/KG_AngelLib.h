////////////////////////////////////////////////////////////////////////////////
//
//  FileName    : KG_AngelLib.h
//  Version     : 1.0
//  Creater     : Wu Caizhong
//  Create Date : 2005-5-12 17:40:17
//  Comment     : 
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _INCLUDE_KG_ANGELLIB_H_
#define _INCLUDE_KG_ANGELLIB_H_

#include "KG_Angel.h"
#include "KGPublic.h"

////////////////////////////////////////////////////////////////////////////////
class KG_AngelLib
{
public:
    KG_AngelLib(void);
    ~KG_AngelLib(void);
    ////////////////////////////////////////////////////////////////////////////////
    // @brief : Initialize interface.
    // @param pvContext : [in] reserved
    // @return : true if successful, false if failed.
    static int Init(void *pvContext);

    ////////////////////////////////////////////////////////////////////////////////
    // @brief : Uninitialized interface.
    // @param pvContext : [in] reserved
    // @return : true if successful, false if failed.
    static int UnInit(void *pvContext);

    static int GetVersion(unsigned *puMainVersion, unsigned *puSubVersion)
    {
        ASSERT(ms_pfnGetAngelVerson);
        return ms_pfnGetAngelVerson(puMainVersion, puSubVersion);
    }
    ////////////////////////////////////////////////////////////////////////////////
    // @brief : Get a interface of role information
    // @return : interface point, if failed, is NULL
    // @remark :1. must call KG_AngelInit() first
    //          2. call IKG_RoleInfo::Release() to release resource.
    static IKG_RoleInfo *CreateRoleInfo()
    {
        ASSERT(ms_pfnCreateRoleInfo);
        return ms_pfnCreateRoleInfo();
    }

    ////////////////////////////////////////////////////////////////////////////
    // @berief : Get a interface of statistic.
    // @return : Interface pointer, if failed, is NULL.
    // @remark :
    static IKG_Statistic *CreateStatistic()
    {
        ASSERT(ms_pfnCreateStatistic);
        return ms_pfnCreateStatistic();
    }

    static IKG_RoleProcessor *CreateRoleProcessor()
    {
        ASSERT(ms_pfnCreateRoleProcessor);
        return ms_pfnCreateRoleProcessor();
    }

    static IKG_BishopProcessor *CreateBishopProcessor()
    {
        ASSERT(ms_pfnCreateBishopProcessor);
        return ms_pfnCreateBishopProcessor();
    }

private:
    typedef int (__stdcall *KG_PFN_VOIDPTRPARAM)(void *pvContext);
    typedef int (__stdcall *KG_PFN_GET_ANGEL_VERSION)(
        unsigned *puMainVersion, unsigned *puSubVerson
    );
    typedef IKG_RoleInfo *(__stdcall *KG_PFN_CREATE_ROLE_INFO)();
    typedef IKG_Statistic *(__stdcall *KG_PFN_CREATE_STATISTIC)();
    typedef IKG_RoleProcessor *(__stdcall *KG_PFN_CREATE_ROLE_PROCESSOR)();
    typedef IKG_BishopProcessor *(__stdcall *KG_PFN_CREATEBISHOPPROCESSOR)();

    static KG_PFN_VOIDPTRPARAM          ms_pfnAngelInit;
    static KG_PFN_VOIDPTRPARAM          ms_pfnAngelUnInit;
    static KG_PFN_GET_ANGEL_VERSION     ms_pfnGetAngelVerson;
    static KG_PFN_CREATE_ROLE_INFO      ms_pfnCreateRoleInfo;
    static KG_PFN_CREATE_STATISTIC      ms_pfnCreateStatistic;
    static KG_PFN_CREATE_ROLE_PROCESSOR ms_pfnCreateRoleProcessor;
    static KG_PFN_CREATEBISHOPPROCESSOR ms_pfnCreateBishopProcessor;

#ifdef WIN32
    static HMODULE ms_hAngelModule;
#else
    static void* ms_hAngelModule;
#endif   
};


#endif //_INCLUDE_KG_ANGELLIB_H_
