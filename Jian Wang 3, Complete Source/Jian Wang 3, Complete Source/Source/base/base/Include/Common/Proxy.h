#ifndef _PROXY_H_
#define _PROXY_H_



#pragma	pack(push, 1)

struct Socks5ProxyCheckAuthenticationMethod // 协议握手请求
{ 
	char cVersion; 
	char cMethodCount; 
	char cMethods[255]; 
}; 

struct Socks5ProxyAuthenticationMethodRespond //协议握手应答
{ 
	char cVersion; 
	char cMethod; 
}; 

struct Socks5ProxyAuthenticationInfo // 登陆代理服务器的用户信息
{
	char cVersion; 
    char cAuthenticationData[512]; // (char)UserNameLength + UserName + (char)PasswordLength + Password
};

struct Socks5ProxyAuthenticationRespond // 用户登录信息的校验结果
{ 
	char cVersion; 
	char cStatus; 
}; 


struct Socks5ProxyCommand // 连接请求，即一些关于目标server的基本信息
{ 
	char cVersion; 
	char cCommand; 
	char cReserved; 
	char cAddressType; 
    char szHostInfo[260]; // address, port
}; 

struct Socks5ProxyRespon 
{ 
	char cVersion; 
	char cReplyCode; 
	char cReserved; 
	char cAddressType; // == 1
	unsigned uBoundAddress; // no use now
    unsigned short usBoundPort; // no use now
}; 

/*
o  Socks5ProxyRespon::cReplyCode field:
        o  X'00' succeeded
        o  X'01' general SOCKS server failure
        o  X'02' connection not allowed by ruleset
        o  X'03' Network unreachable
        o  X'04' Host unreachable
        o  X'05' Connection refused
        o  X'06' TTL expired
        o  X'07' Command not supported
        o  X'08' Address type not supported
        o  X'09' to X'FF' unassigned
*/


struct Socks4ProxyCommand // 连接请求，即一些关于目标server的基本信息
{ 
	char cVersion; 
	char cCommand; 
    unsigned short usDestPort;
    unsigned uDestIPAddress;
    char szOther[260]; //
}; 

struct Socks4ProxyRespon 
{ 
	char cVersion; 
	char cReplyCode; 
    unsigned short usDestPort;
    unsigned uDestIP;
}; 
/*
Socks4ProxyRespon::cReplyCode
	90: request granted
	91: request rejected or failed
	92: request rejected becasue SOCKS server cannot connect to
	    identd on the client
	93: request rejected because the client program and identd
	    report different user-ids
*/

typedef enum _AUTHENTICATION_METHOD
{
    authentication_method_none = 0x00,
    authentication_method_gssapi = 0x01,
    authentication_method_password = 0x02,
    authentication_method_iana_assigned = 0x03, // up to 0x7f 
    authentication_method_reserved = 0x80,      // up to 0xfe
    authentication_method_no_acceptable_methods = 0xff
} AUTHENTICATION_METHOD;
  


typedef enum _ADDRESS_TYPE
{
    address_type_ipv4 = 0x01,
    address_type_domain_name = 0x03, 
    address_type_ipv6 = 0x04 // not support now !
} ADDRESS_TYPE;

typedef enum _PROXY_CMD
{
    proxy_cmd_tcp_connect = 0x01,
    proxy_cmd_tcp_bind = 0x02, // not support now !
    proxy_cmd_udp_associate = 0x03 // not support now !
} PROXY_CMD;

typedef enum _PROXY_TYPE
{
	PROXY_TYPE_SOCK4, 
	PROXY_TYPE_SOCK5,
	PROXY_TYPE_HTTP
} PROXY_TYPE;

typedef enum _PROXY_ERROR
{
    proxy_all_ok = 1, //no error
    proxy_connection_failed, // can't connect to the proxy server
    proxy_network_error, // IO error ! disconnected ! timeout !
    proxy_authentication_error,     // e.g password error !
    proxy_destination_error, // e.g host unreachable, refused !
    proxy_not_supported, 
    proxy_unknown_error
} PROXY_ERROR;

#define PROXY_MAX_STRING_LENGTH 64

typedef struct _PROXY_INFO
{
	char            szProxyAddr[PROXY_MAX_STRING_LENGTH];
    unsigned short  usProxyPort;
    char            szUserName[PROXY_MAX_STRING_LENGTH]; // if not use, set to "", 
	char            szPassword[PROXY_MAX_STRING_LENGTH]; // if not use, set to "" 
	PROXY_TYPE      ProxyType;
    timeval         ProxyInitTimeout;

	char            szHostAddress[PROXY_MAX_STRING_LENGTH]; // e.g "192.168.27.25" 
	unsigned short  usHostPort;   // e.g 80 !
} PROXY_INFO;

#pragma pack(pop)





#endif // _PROXY_H_
