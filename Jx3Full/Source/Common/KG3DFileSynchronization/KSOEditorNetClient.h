#pragma once

struct IKConnector;
struct KG3DJsonFileHelper;


class KSOEditorNetClient
{
public:
	DWORD m_dwLastPingTime;

	IKConnector* m_piConnector;

	KSOEditorNetClient(void);
	virtual ~KSOEditorNetClient(void);

	HRESULT Init(); 
	
	HRESULT SendFileChange(const char szMessage[]);
	HRESULT SendJsonFileChange(KG3DJsonFileHelper* pHelper);

	HRESULT Activate();
	HRESULT Uninit();

};

