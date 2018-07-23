#ifndef __CACHE_H__
#define __CACHE_H__

class CCache
{
public:
	CCache();
	CCache(int nBufLen);
	~CCache();
	void Init(int nBufLen);
	void PushMessage(char *pMsg, unsigned int nMsgLen);
	char *PopMessage(unsigned int &nMsgLen);
	bool IsEmpty();
private:
	char *buff;
	char *data;
	char *free;
	char *tail;
};

#endif //__CACHE_H__
