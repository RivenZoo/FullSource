////////////////////////////////////////////////////////////////////////////////
//
//  FileName    : IKG_AgentGateway.h
//  Version     : 1.0
//  Creator     : tongxuehu, zoukewei
//  Create Date : 01/18/2007
//  Comment     : 
//  
//  Copyright (C) 2007 - All Rights Reserved
////////////////////////////////////////////////////////////////////////////////

#ifndef _IKG_AGENT_GATEWAY_H_
#define _IKG_AGENT_GATEWAY_H_ 1

#include "KG_AgentProtocol.h"

class IKG_AgentGateway
{
public:
    virtual int SendToClient(KG_AGENT_PROTOCOL *pAgentProtocol) = 0;
    virtual int SendToServer(KG_AGENT_PROTOCOL *pAgentProtocol) = 0;

public:
    virtual int GetNextSequenceID(int *pnSequenceID) = 0;
};

#endif // _IKG_AGENT_GATEWAY_H_
