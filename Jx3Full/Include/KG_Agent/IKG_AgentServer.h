////////////////////////////////////////////////////////////////////////////////
//
//  FileName    : IKG_AgentServer.h
//  Version     : 1.0
//  Creator     : tongxuehu
//  Create Date : 01/12/2007
//  Comment     : 
//  
//  Copyright (C) 2007 - All Rights Reserved
////////////////////////////////////////////////////////////////////////////////

#ifndef _IKG_AGENT_SERVER_H_
#define _IKG_AGENT_SERVER_H_ 1

#ifndef interface
#define interface struct
#endif

interface IKG_AgentServer 
{
    virtual int SendRequest(  
        const char  cszAgentServerName[],  
        KG_AGENT_PROTOCOL *pAgentProtocol 
    ) = 0;

    virtual int SendResponse(
        KG_AGENT_PROTOCOL *pAgentProtocol
    ) = 0;
};

#endif // _IKG_AGENT_SERVER_H_