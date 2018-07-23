//---------------------------------------------------------------------------
// 剑侠情缘网络版2 GameMasterCentral 互联互通
// 版权所有:       2006-2007 金山软件(Kingsoft)
// 创建日期与作者: 2007-1-3 越子(wooy)
//---------------------------------------------------------------------------
// GameMasterCentral与游戏世界之外的各个应用系统之间连接的协议接口。
// 这些协议都是以文本数据包形式发送，数据包的最后一个字节都是字符串结尾符'\0'。
// 这些连接分为两类，一类是明文传输原协议数据包文本，一类是把文本进行加密转换
// 后再传输。
// GmWeb2.0用的是旧GmWeb接口协议，与此协议不通，此两组协议之间互相不兼容。
//---------------------------------------------------------------------------
#ifndef __GAME_MASTER_CENTRAL_GMCENTRAL_DOOR_PROTOCOL_H__
#define __GAME_MASTER_CENTRAL_GMCENTRAL_DOOR_PROTOCOL_H__

struct GMCENTRAL_DOOR_PROTOCOL_PARAM
{
	//该文本协议中各字段的分隔符（以空格为分隔符）
	#define FIELD_SEPARATOR			' '
	//字段中字段内容与字段前缀标识的分隔符（以冒号分隔）
	#define FIELD_PREFIX_SEPARATOR	':'
	//协议的第一个字段为分类关键字，它们都为固定长度:8个字节（不含字符串结尾符）
	#define	OF_KEYWORD_LEN			8
	//协议的第二个字段为操作关键字，它们的长度最长为11个字节，加上字符串结尾符占12字节
	#define OPER_KEYWORD_MAX_LEN	12
};

//=====协议的分类关键字=====
struct OF_KEYWORD
{
	#define	OF_KEYWORD_LEN	8		//这些关键字都为固定长度:8个字节
	#define OFKW_SYSTEM		"_SYSTEM_"	//服务系统互联
	#define OFKW_RET		"_RETURN_"	//反馈消息(操作结果数据包)
	#define OFKW_SINFO		"SYS_INFO"	//系统信息监视
	#define OFKW_SNCTRL		"S_N_CTRL"	//服务系统一般控制	
	#define OFKW_SSCTRL		"S_S_CTRL"	//服务系统特殊控制	
	#define OFKW_ANCTRL		"A_N_CTRL"	//帐号一般控制
	#define OFKW_RNCTRL		"R_N_CTRL"	//角色一般控制
	#define OFKW_RSCTRL		"R_S_CTRL"	//角色特殊控制
	#define OFKW_RINFO		"ROL_INFO"	//角色信息查询
	#define OFKW_GSINFO		"GAM_INFO"	//获取游戏世界信息
	#define OFKW_GSCTRL		"GAM_CTRL"	//游戏世界信息控制	
	#define OFKW_GMCTRL		"G_M_CTRL"	//GM帐号角色控制
	#define OFKW_ASTINFO	"AST_INFO"	//辅助信息
};

//-------------------------------------
//		服务系统互联的操作
//-------------------------------------
struct GMC_SYSTEM_OPERATION
{
	//用于告诉GMC该连接的基本相关信息。
	#define GMC_SO_CONNECT_INFO	"CONN_INFO"
		//GMC将可能根据这个连接是什么连接，而确定支持在该连接上进行哪些操作。
		//与GMC建立后的第一个消息就该发这个消息，因为目前还兼容旧GMWeb2.0，所以GMC
		//如果第一个消息如果收到的不是这个消息，则GMC把该连接判定为旧GMWeb2.0连接，
		//并对收到的消息只以旧GMWeb2.0发出的格式来处理。
		//该消息的格式如下：
		//_SYSTEM_ CONN_INFO SN:0-0 NAME:连接名 IDENT:识别号
		//格式参数说明：
		//连接名:	连接名最长为31个字节长，GMC根据连接名来标识和确定这是条什么连接。
		//			GMC将可能根据连接名来配置该连接上许可的操作。多条连接为同样一个
		//			连接名。
		//识别号:	为10进制表示的非0正整数。当连接名相同时，将根据识别号，区分不同
		//			的同名连接。连接名相同的连接，识别号不可相同。不同的连接名，识别
		//			号可以相同。
};

#define	GMC_GROUP_NAME_ALL		"__ALL__"

//GM服务协议的基本字段
//对于协议中的基本字段，在格式上我们都在字段的最前面加上特定的前缀关键字，方便系统对内容进行快速的
//无歧异和统一的识别。前缀关键字都用英文符号表示，区分大小写。前缀关键字与字段内容间都以冒号:作为间隔号。
//前缀关键字最长为7个字符。下面定义了一些基本字段的前缀关键字。
struct GMC_COMMON_FIELD_NAME
{
	//协议的流水号，用它标记唯一的标记区分每条协议，方便各系统定位请求来源与处理。
	#define GMC_CF_SERIAL_NO	"SN"
		//格式：SN:数值1-数值2
		//说明：数值1和数值2都是十六进制正整数，每个正整数的最大值为FFFFFFFF，即32bit表示的最大数。
		//数值1为GMC生成，各挂接GMC的系统不解析该数值的含义。数值2位由各挂接GMC的系统在生成请求消息
		//时自行生成，用于表示该系统中产生的消息的流水号，方便系统作请求与结果之间的匹配等。

	//表示操作的目标区服，或者信息来源的源区服
	#define GMC_CF_SVR_GROUP	"GROUP"
		//格式：GROUP:区整数-服整数
		//说明：区整数和服整数都是十进制非负数。当区整数为0时表示，任意区；当服整数为0时表示任意服。
		//如GROUP:3-2表示3区2服；GROUP:2-1表示2区1服；GROUP:15-0表示15区全区；GROUP:0-0表示全区全服。

	//用字符串名称表示操作的目标区服
	#define GMC_CF_SVR_GROUP_NAME	"GROUPN"
	//格式：GROUPN:区服名称
	//说明：区服名称字符串长度少于等于31字节，如果名称为GMC_GROUP_NAME_ALL，表示全区服

	//玩家帐号名，须为游戏系统支持的合法帐号名
	#define GMC_CF_ACCOUNT		"ACC"
		//格式：ACC:帐号名字符串
		//说明：帐号名字符串不需要加引号，最长不超过规定32个字节，最短不少于4个字节。

	//玩家角色名，须为游戏世界中规定的合法角色名
	#define GMC_CF_ROLE			"ROLE"
		//格式：ROLE:角色名字符串
		//说明：角色名字符串不需要加引号，具体长度和各个游戏的命名长度限制有关。

	//进行GM操作的操作员的帐号名
	#define GMC_CF_OPERATOR		"OPER"
		//格式：OPER:操作员操作帐号名字符串
		//说明：有些操作GM需要授权，需要在请求上指出进行GM操作的操作员帐号。

	//GM角色名
	#define GMC_CF_GM_ROLE		"GM"
		//格式：GM:角色名字符串
		//说明：角色名字符串不需要加引号，具体长度和各个游戏的命名长度限制有关

	//选项开关
	#define GMC_CF_OPT			"OPT"
		//格式：OPT:ON 或 OPT:OFF

	//用于表述文本信息的信息内容，如聊天语句、公告内容等
	#define GMC_CF_TEXT_DATA	"T_DATA"
		//格式：T_DATA:文本信息长度-文本信息内容
		//说明：文本信息长度为一个十进制正整数，为后面所跟的文本信息内容以字节计的长度。
		//信息文本串可包含空格、引号等符号。文本信息长度值与内容之间有减号分隔符-。

	//用于表述二进制信息的信息数据内容
	#define GMC_CF_BIN_DATA		"B_DATA"
		//格式：B_DATA:信息长度信息内容
		//说明：信息长度为两个字节长度(unsigned short)正整数，为后面所跟的信息内容数据块，
		//数据块的(以字节计)长度即为前面信息长度的值。信息长度与信息内容之间无间隔符。
		//例如对于一块3个字节长度的信息，则该字段的总长度为11个字节。

	//请求的处理结果（成功或失败）
	#define GMC_CF_RESULT		"RESULT"
		//格式：RESULT:SUCCESS 或 RESULT:FAIL
};


#endif// #ifndef __GAME_MASTER_CENTRAL_GMCENTRAL_DOOR_PROTOCOL_H__
