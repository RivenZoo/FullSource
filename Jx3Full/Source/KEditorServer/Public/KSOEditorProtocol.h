#ifndef _KSO_EDITOR_PROTOCOL_H_
#define _KSO_EDITOR_PROTOCOL_H_

#define  PROTOCOL_CURRENT_VERSION 1

#pragma pack(1)
enum PROTOCOL_PACKAGE_FLAG
{
    ppfSinglePackage    = 0,
    ppfPackageHeader    = 1,
    ppfPackageBody      = 2,
    ppfPackageTail      = 3
};

struct PROTOCOL_HEADER
{
    uint32_t    uProtocolID;
    uint32_t    uPakSize;
    uint8_t     uPakFlag;
};

enum EDITOR_TO_SERVER_PROTOCOL_ID
{
    editor_to_server_begin,

    editor_to_server_handshake_request,
    editor_to_server_send_message,
	editor_to_server_send_ping,
	editor_to_server_send_jsonfilechange,

    editor_to_server_end
};

struct EDITOR_TO_SERVER_HANDSHAKE_REQUEST : PROTOCOL_HEADER
{
    uint32_t    uVersion;
};

struct EDITOR_TO_SERVER_SEND_MESSAGE : PROTOCOL_HEADER
{
    char        szMessage[0];
};

struct EDITOR_TO_SERVER_SEND_PING : PROTOCOL_HEADER
{
	char        szMessage[0];
};

struct EDITOR_TO_SERVER_SEND_JSONFILECHANGE : PROTOCOL_HEADER
{
	char        szFileName[256];
	char        szJsonFile[0];
};

//////////////////////////////////////////////////////////////////////////

enum SERVER_TO_EDITOR_PROTOCOL_ID
{
    server_to_editor_begin,

	server_to_editor_send_message,
	server_to_editor_send_jsonfilechange,

    server_to_editor_end
};


struct SERVER_TO_EDITOR_SEND_MESSAGE : PROTOCOL_HEADER
{
    char    szMessage[0];
};

struct SERVER_TO_EDITOR_SEND_JSONFILECHANGE : PROTOCOL_HEADER
{
	char        szFileName[256];
	char        szJsonFile[0];
};
#pragma pack()

#endif // _KSO_EDITOR_PROTOCOL_H_