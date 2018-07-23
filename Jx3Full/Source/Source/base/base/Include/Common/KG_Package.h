//////////////////////////////////////////////////////////////////////////////////////
//
//  FileName    :   KG_Package.h
//  Version     :   1.0
//  Creater     :   zhuchuanjing, Freeway Chen
//  Date        :   2004-11-4 10:09:50
//  Comment     :   
//
//////////////////////////////////////////////////////////////////////////////////////

#ifndef _KG_PACKAGE_H_
#define _KG_PACKAGE_H_  1

#include <stdlib.h>
#include "KGPublic.h"


#define MAX_CID		256
#define MAX_PACKAGE (65536 - 32)

class KG_Packager 
{
public:

    // Process Recv Data
	char *PackUp(const void *data, int& size);

	// Send
	char *GetHeadPack(unsigned char cID, size_t& actualLength,          size_t packLength = 512);
	char *GetNextPack(unsigned char cID, size_t& actualLength);
	
	void AddData(unsigned char cID, const char * const pData,           size_t dataLength, unsigned long lnUserData = 0);
	void AddData(unsigned char cID, const unsigned char * const pData,  size_t dataLength, unsigned long lnUserData = 0)
	{
		AddData(cID, reinterpret_cast<const char *>(pData), dataLength, lnUserData);
	}

	void DelData(unsigned char cID);


	KG_Packager() 
	{
		memset(&data_ptr[0],        0, MAX_CID * sizeof(char *));
		memset(data_size,           0, MAX_CID * sizeof(int));
		memset(&send_data_ptr[0],   0, MAX_CID * sizeof(char *));
		memset(&pack_data_ptr[0],   0, MAX_CID * sizeof(char *));
		memset(split_pos,           0, MAX_CID * sizeof(int));
		memset(pack_len,            0, MAX_CID * sizeof(int));
		memset(send_data_size,      0, MAX_CID * sizeof(int));
		memset(pack_data_size,      0, MAX_CID * sizeof(int));
	}
	~KG_Packager() 
	{
		int index;
		for (index = 0; index < MAX_CID; index++) 
		{
			if (data_ptr[index]) 
			    delete[] data_ptr[index];
		}
		for (index = 0; index < MAX_CID; index++) 
		{
			if (send_data_ptr[index]) 
			    delete[] send_data_ptr[index];
		}
		for(index = 0; index < MAX_CID; index++) 
		{
			if (pack_data_ptr[index]) 
			    delete[] pack_data_ptr[index];
		}
	}
	
private:
	char *_getpackdata(unsigned char cID);
	

private:
	char           *data_ptr      [MAX_CID];
	unsigned        data_size     [MAX_CID];

	char           *send_data_ptr [MAX_CID];
	char           *pack_data_ptr [MAX_CID];
	unsigned        send_data_size[MAX_CID];
	unsigned        split_pos     [MAX_CID];
	unsigned        pack_len      [MAX_CID];
	unsigned        pack_data_size[MAX_CID];
	unsigned long   user_data     [MAX_CID];
};

int KG_Package_SendBuffer(KG_Packager *pPackager, IKG_SocketStream *piSocketStream, IKG_Buffer *piBuffer);
int KG_Package_RecvBuffer(KG_Packager *pPackager, IKG_SocketStream *piSocketStream, IKG_Buffer **ppiBuffer);


class KG_Packer
{
public:
    int Send(
        IKG_SocketStream *piSocketStream, 
        unsigned uBufferSize, const unsigned char cbyBuffer[]
    );
    int FlushSend(IKG_SocketStream *piSocketStream);
    
    int Reset();

    KG_Packer(unsigned uPackSize) : 
        m_uPackSize(uPackSize), 
        m_piBuffer(NULL),
        m_piBufferReSize(NULL),
        m_pbyBufferBegin(NULL), m_pbyBufferPos(NULL), m_pbyBufferEnd(NULL) 
    { 
        ASSERT(uPackSize > 0);
    }
    ~KG_Packer() 
    { 
        KG_COM_RELEASE(m_piBufferReSize);
        KG_COM_RELEASE(m_piBuffer);
        m_pbyBufferBegin = m_pbyBufferPos = m_pbyBufferEnd = NULL;
    }

private:
    unsigned                 m_uPackSize;

    IKG_Buffer              *m_piBuffer;
    IKG_Buffer_ReSize       *m_piBufferReSize;

    unsigned char           *m_pbyBufferBegin;
    unsigned char           *m_pbyBufferPos;
    unsigned char           *m_pbyBufferEnd;
};
#endif
