////////////////////////////////////////////////////////////////////////////////
//
//  FileName    : KGD_Sequence.h
//  Version     : 1.0
//  Creator     : Xia Yong
//  Create Date : 2006-7-27 16:59:03
//  Comment     : 
//
////////////////////////////////////////////////////////////////////////////////

#ifndef _INCLUDE_KGD_SEQUENCE_H_
#define _INCLUDE_KGD_SEQUENCE_H_

////////////////////////////////////////////////////////////////////////////////

#include "KSUnknown.h"

class IKGD_Sequence : public IUnknown
{
public:
    ////////////////////////////////////////////////////////////////////////////
    // @brief : Fetch a set of ID
    // @param ullIDCount      : [in] The Total number of ID want to get  
    // @param pullRetStartID  : [out] The first ID
    // @return : true if successful, false if failed.
    // @remark : example, set ullIDCount = 3 and return *pullRetStartID = 7
    //           means get a list of ID 7, 8, 9
    virtual int GetID(
        unsigned long long ullIDCount, unsigned long long *pullRetStartID
    ) = 0;
};

////////////////////////////////////////////////////////////////////////////
// @brief : 
// @param pvContext :[in] reserve, should set to NULL 
// @return : true if successful, false if failed.
// @remark :
int KGD_Sequence_Init(void *pvContext);

////////////////////////////////////////////////////////////////////////////
// @brief : 
// @param pvContext : [in] reserve, should set to NULL
// @return : true if successful, false if failed.
// @remark :
int KGD_Sequence_UnInit(void *pvContext);

////////////////////////////////////////////////////////////////////////////////
// @brief : Create a interface of IKG_Sequence
// @param szSequenceName    : [in] The Sequence name 
// @param ullStartID        : [in] The start ID of the sequence
// @param ullMaxID          : [in] The maximal ID of the sequence
// @param cszGroupName      : [in] The group of the sequence
// @param cszServer         : [in] The server of the database(IP or machine name)
// @param cszDatabase       : [in] The database on the server
// @param cszUserName       : [in] The user name of the database
// @param cszPassword       : [in] The password of the user
// @return : If success, return a Point to IKG_Sequence, else return NULL
IKGD_Sequence *KGD_CreateSequence(
    const char cszServer[],
    const char cszDatabase[],
    const char cszUserName[], 
    const char cszPassword[],
    const char cszGroupName[],    
    const char szSequenceName[], 
    unsigned long long ullStartID,
    unsigned long long ullMaxID
);


#endif //_INCLUDE_KGD_SEQUENCE_H_
