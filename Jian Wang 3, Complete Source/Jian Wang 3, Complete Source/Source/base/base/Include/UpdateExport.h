//////////////////////////////////////////////////////////////////////////////////////
//
//  FileName    :   UpdateExport.h
//  Version     :   1.0
//  Creater     :   Cheng bitao
//  Date        :   2002-11-28 17:24:39
//  Comment     :   
//
//////////////////////////////////////////////////////////////////////////////////////

#ifndef	 _UPDATE_EXPORT_H_
#define  _UPDATE_EXPORT_H_

#define defUPDATE_RESULT_INIT_FAILED				0x00
#define defUPDATE_RESULT_INIT_SUCCESS				0x01
#define defUPDATE_RESULT_DOWNLOAD_INDEX_FAILED		0x02	
#define defUPDATE_RESULT_DOWNLOAD_INDEX_SUCCESS  	0x03
#define defUPDATE_RESULT_PROCESS_INDEX_FAILED		0x04
#define defUPDATE_RESULT_PROCESS_INDEX_SUCCESS		0x05
#define defUPDATE_RESULT_NOT_UPDATE_FILE			0x06
#define defUPDATE_RESULT_DOWNLOAD_FAILED			0x07
#define defUPDATE_RESULT_DOWNLOAD_SUCCESS			0x08
#define defUPDATE_RESULT_UPDATE_FAILED				0x09
#define defUPDATE_RESULT_UPDATE_SUCCESS				0x0A
#define defUPDATE_RESULT_UPDATE_SUCCESS_NEED_REBOOT 0x0B
#define defUPDATE_RESULT_LOAD_SOCKET_ERROR			0x0C				
#define defUPDATE_RESULT_USER_VERIFY_FAILED         0x0D
#define defUPDATE_RESULT_USER_VERIFY_SUCCESS        0x0E
#define defUPDATE_RESULT_INVALIDSN                  0x0F
#define defUPDATE_RESULT_PIRATICSN                  0x10
#define defUPDATE_RESULT_INHIBITIVESN               0x11
#define defUPDATE_RESULT_CONNECT_SERVER_FAILED      0x12
#define defUPDATE_RESULT_ERRORSN                    0x13
#define defUPDATE_RESULT_CANCEL                     0x14
#define defUPDATE_RESULT_UPDATESELF_SUCCESS			0x15
#define defUPDATE_RESULT_VERSION_NOT_ENOUGH         0x16
#define defUPDATE_RESULT_VERSION_MORE				0x17
#define defUPDATE_RESULT_VERSION_LATEST				0x18	//Modified by Fellow, 2003.11.13

//Modified by Fellow, 2003.12.9
//启动前和启动后运行程序的标志
#define defUPDATE_RESULT_RUNBEFORE					0x19
#define defUPDATE_RESULT_RUNAFTER					0x20

#define defUPDATE_STATUS_INITIALIZING               0x01
#define defUPDATE_STATUS_VERIFING                   0x02
#define defUPDATE_STATUS_PROCESSING_INDEX           0x03
#define defUPDATE_STATUS_DOWNLOADING                0x04
#define defUPDATE_STATUS_DOWNLOADING_FILE           0x05
#define defUPDATE_STATUS_UPDATING                   0x06
      

#define PROXY_METHOD_DIRECT                 0
#define PROXY_METHOD_USEIE                  1
#define PROXY_METHOD_CUSTOM                 2



// define proxy data 
#define PROXY_VAR_LEN			            100


typedef int _stdcall FN_UPDATE_CALLBACK(int nCurrentStatus, long lParam);

typedef struct _tagDownloadFileStatus
{
	char	strFileName[MAX_PATH];		// 文件名
	DWORD	dwFileSize;					// 文件大小
	DWORD	dwFileDownloadedSize;		// 已经下载大小
} DOWNLOADFILESTATUS,*LPDOWNLOADFILESTATUS;

#pragma pack(push, 1)   

typedef struct tagKPROXY_SETTING
{
    int  nProxyMethod;              //DIRECT/USEIE/CUSTOM
    int  nProxyMode;                //PROXY_MODE_... when PROXY_METHOD_CUSTOM
    
    char szHostAddr[PROXY_VAR_LEN];
    int  nHostPort;
    
    BOOL bUpdateAuth;
    char szUserName[PROXY_VAR_LEN];
    char szPassword[PROXY_VAR_LEN];

} KPROXY_SETTING;

typedef struct tagKUPDATE_SETTING
{
	int		nVersion;
    int     nUpdateMode;                // 0: Internet  1: LAN
    
    ULONG   ulTryTimes;                 // Times of try when download failed
    CHAR    szUpdateSite[MAX_PATH];          // Download host URL 
        
    BOOL    bAutoTryNextHost;              // Flag of try use next faster host when failed
    BOOL    bUseFastestHost;               // Flag use the fastest host
    
    BOOL    bUseVerify;
    CHAR    szVerifyInfo[MAX_PATH];

    CHAR    szDownloadPath[MAX_PATH];   // Download destination path
    CHAR    szUpdatePath[MAX_PATH];     // Update destination path
	CHAR    szMainExecute[MAX_PATH];     // main program

    FN_UPDATE_CALLBACK *pfnCallBackProc; 

    KPROXY_SETTING ProxySetting;
    
	BOOL	bLog;

} KUPDATE_SETTING;


#pragma pack(pop)


int __stdcall Update_Init(KUPDATE_SETTING UpdateSetting);
int __stdcall Update_UnInit();
int __stdcall Update_Start();
int __stdcall Update_Cancel();

#endif	//_UPDATE_IMPORT_H_

