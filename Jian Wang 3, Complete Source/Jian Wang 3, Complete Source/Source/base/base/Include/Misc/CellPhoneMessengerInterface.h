//-------------------------------------------------------------------
//剑侠情缘网络版2	手机短讯发送组件
//版权所有：        2008 金山软件(Kingsoft)
//创建日期及作者：  2008-3-24	越子(Wooy)
/*-------------------------------------------------------------------
 能够通过采用HTTP GET方式向手机短讯ISP发出发送短讯的请求，并获得回馈。
 该模块不支持多线程，且未考虑Linux支持。
 请求URL样式：
 http://1.0.0.1/default.aspx?Acc=Jx2&Phone=13900000000&Message=HELLO
-------------------------------------------------------------------*/
#ifndef __CELL_PHONE_MESSENGER_INTERFACE_H__
#define __CELL_PHONE_MESSENGER_INTERFACE_H__

//用于设置该模块的工作环境的相关信息
struct CPM_WORK_ENVIRONMENT_INFO
{
	char	szRequestURLPrefix[512];	//请求URL前缀不含分隔参数用的"?"符号
	char	szAccountToken[16];			//帐号参数"="前的关键字
	char	szPhoneNumberToken[16];		//手机号码"="前的关键字
	char	szShortMessageToken[16];	//短讯内容"="前的关键字
	char	szAccountName[32];			//实际使用"的发送帐号
	char	szEncodeKey[32];			//加密私钥（在XmlRpc方式时用）
	char	szHandlerMethod[64];		//处理对象与方法名称（在XmlRpc方式时用）
};

//用于描述一条短讯的结构体
struct CPM_SHORT_MESSAGE_INFO
{
	//pPhoneNumber与pMessageContent指向两个字符串缓冲区，这两个字符串都可以没有字符串结尾符\0。
	const char*		pPhoneNumber;		//接收短讯的电话号码；如有多个号码，用";"隔开
	unsigned int	uPhoneNumberLen;	//pPhoneNumber所指内容的长度（如果内容中包含字符串结尾符\0，则该长度不含结尾符）
	const char*		pMessageContent;	//短讯文本内容
	unsigned int	uMessageContentLen;	//pMessageContent所指内容的长度（如果内容中包含字符串结尾符\0，则该长度不含结尾符）
};

//短讯发送操作的结果
enum	CPM_RESULT
{
	CPM_RESULT_OK = 0,						//正常发送，无错误
	CPM_RESULT_UNACCEPTABLE_PHONE_NUMBER = 1,//无效的手机号码
	CPM_RESULT_SERVER_EXCEPTION = 7,		//服务器出现未知异常
	CPM_RESULT_CONTENT_ACCEPT_DENY = 9,		//拒绝接收该短讯内容(信息含有非法关键字)
	CPM_RESULT_IO_EXCEPTION = 10000,		//发生有关网络的错误
	CPM_RESULT_FAIL = -1,					//未指明原因的其它错误
	//请参看该文件的末尾的附录，获知短讯ISP对返回信息的定义
};

enum CPM_MESSENGER_TYPE
{
	CPM_MESSENGER_TYPE_HTTPGET = 1,
	CPM_MESSENGER_TYPE_XMLRPC = 2,
};

//<<<<<<===---+++   接口函数   +++---===>>>>>>
#ifndef CELL_PHONE_MESSENGER_INTERNAL_SIGNATURE
	extern "C" bool			CPMessengerSetWorkEnvironment(const CPM_WORK_ENVIRONMENT_INFO& env, CPM_MESSENGER_TYPE eType);
	extern "C" CPM_RESULT	CPMessengerSendShortMessage(const CPM_SHORT_MESSAGE_INFO& msg);
	extern "C" void			CPMessengerCleanup();
	typedef bool		(*FUNC_CPM_SET_WORK_ENVIRONMENT)(const CPM_WORK_ENVIRONMENT_INFO& env, CPM_MESSENGER_TYPE eType);
	typedef CPM_RESULT	(*FUNC_CPM_SEND_SHORT_MESSAGE)(const CPM_SHORT_MESSAGE_INFO& msg);
	typedef void		(*FUNC_CPM_CLEANUP)();
	#define FUNC_NAME_CP_MESSENGER_SET_WORK_ENVIRONMENT	"CPMessengerSetWorkEnvironment"
	#define FUNC_NAME_CP_MESSENGER_SEND_SHORT_MESSAGE	"CPMessengerSendShortMessage"
	#define FUNC_NAME_CP_MESSENGER_CLEANUP				"CPMessengerCleanup"
#endif

#endif	//#ifndef __CELL_PHONE_MESSENGER_INTERFACE_H__

//==============================================================
//	附录：短讯ISP对返回信息的定义
//返回信息统一使用“错误代码-错误代码释义”的格式，具体定义如下：
// 错误代码	错误代码释义				说明	
//		0	OK							正常发送，无错误	
//		1	Must be China-Mobile user	“phone”参数传递的内容必须是中国移动的手机号码，中国移动的手机号码定义参见3.2	
//		2	undefined Command			“Command”参数传递的内容为未定义指令	
//		3	Need Command Paramater		Get请求中没有提供“Command”参数	
//		4	Need user Paramater			Get请求中没有提供“phone”参数	
//		5	Need Content Paramater		Get请求中没有提供“content”参数	
//		7	Server Exception			服务器出现未知异常	
//		9	Failed to filter message	信息含有非法关键字	
//
//  返回信息类似于以下列出的形式：
//		0-OK
//		1-Must be China-Mobile user
//		9-Failed to filter message
//==============================================================
