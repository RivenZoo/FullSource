#include "Precompile.h"
#include <vector>
#ifdef WIN32
#include <IPHlpApi.h>
#endif
#include "Engine/KGLog.h"
#include "Engine/md5.h"
#include "Engine/KG_MachineID.h"

#ifdef WIN32

// VERSION value must between 0 and 15
// If change algorithm, should increase VERSION
const unsigned char VERSION = 0;

int KG_GetMachineID(unsigned char byRetMachineID[16])
{
    int nResult  = false;
    int nRetCode = false;
    BYTE *pbyBuffer = NULL;
    PIP_ADAPTER_INFO pAdapterInfo = NULL;
    DWORD dwSize = 0;
    std::vector<unsigned char> byMacAddr;
    md5_state_t md5_state;

    // Make an initial call to GetAdaptersInfo to get the
    // necessary size into the dwSize variable
	nRetCode = GetAdaptersInfo(NULL, &dwSize);
	KGLOG_PROCESS_ERROR(nRetCode == ERROR_BUFFER_OVERFLOW);

    pbyBuffer = (BYTE *)malloc(dwSize);
    KGLOG_PROCESS_ERROR(pbyBuffer);

    pAdapterInfo = (PIP_ADAPTER_INFO)pbyBuffer;

    nRetCode = GetAdaptersInfo(pAdapterInfo, &dwSize);
    KGLOG_PROCESS_ERROR(nRetCode == ERROR_SUCCESS);

    while (pAdapterInfo)
    {
		for (DWORD i = 0; i < pAdapterInfo->AddressLength; ++i)
		{
			byMacAddr.push_back(pAdapterInfo->Address[i]);
		}
		pAdapterInfo = pAdapterInfo->Next;
    }
    KGLOG_PROCESS_ERROR(!byMacAddr.empty());

    md5_init(&md5_state);

    md5_append(&md5_state, (unsigned char *)&(byMacAddr[0]), byMacAddr.size());

    md5_finish(&md5_state, byRetMachineID);

    ASSERT(VERSION <= 0x0F);

    byRetMachineID[0] = (byRetMachineID[0] & 0x0F) + (VERSION << 4);

    nResult = true;
Exit0:
    if (pbyBuffer)
    {
        free(pbyBuffer);
        pbyBuffer = NULL;
    }

    return nResult;
}


#endif
