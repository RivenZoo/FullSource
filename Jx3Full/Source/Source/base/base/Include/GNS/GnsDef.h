//--------------------------------------------------------------
// 月影传说网络版  GmcNetworkSystem(GNS)
// 版权所有:        2010 金山软件(Kingsoft)
// 创建日期与作者: 2010-2-11 Golton Gao
//--------------------------------------------------------------
#ifndef __GMC_NETWORK_SYSTEM_DEF_H__
#define __GMC_NETWORK_SYSTEM_DEF_H__
/*--------------------------------------------------------------
[名词解释]
	GNS(GMC Network System)：GMC网络系统，由GMC和接入GMC的其它网络节点组成。
	GNE(GMC Network Entity)：GMC网络实体，GMC网络中的节点的抽象。
	GNM(GMC Network Message)：GMC网络消息，GNE交互通过消息交换实现。
/-------------------------------------------------------------*/
#include <assert.h>
#include <string.h>
#include <stdio.h>

#pragma pack(1)

// === GNE标识符 ===//
/*
	GNE的标识符有地址和路径两种，两者之间可以互相变换。
	1、GNE地址由两段(Segment)组成，第一段为GNE的类型，第二段位GNE的实例。
	2、GNE的类型标识GNE的性质，也就是所提供的服务，类型相同的GNE所提供的服务是相同的。
	3、GNE的实例标识相同类型GNE的不同运行实例。
	4、每个地址段都是一个字符串，只能取英文字符、数字和下划线。其中以下划线'_'开始的段是为内部保留的。
	5、GNE路径的组成方式为：类型/实例。中间用'/'分割。
*/

// == GNE地址 ==//
#define GNE_ADDR_SEGMENT_MAX_LEN	15
typedef char						GNE_ADDR_SEGMENT[GNE_ADDR_SEGMENT_MAX_LEN + 1];
#define GNE_ADDR_SEGMENT_ANY		"%"

struct GNE_ADDR
{
	GNE_ADDR_SEGMENT	Type;
	GNE_ADDR_SEGMENT	Inst;
};

// == GNE_PATH ==//
#define GNE_PATH_MAX_LEN	(GNE_ADDR_SEGMENT_MAX_LEN * 2 + 1)
typedef char				GNE_PATH[GNE_PATH_MAX_LEN + 1];		// 例子："DataCube/ForStat"

// === 服务标识符 ===//
/* 
	1、服务(Service)用路径(Path)来标识。
	2、路径由多级目录组成，每级之间用'/'作为分隔符。
	3、'/'不能作为路径的起始字符。
	4、路径分为本地路径(PathLocal)和全局路径(PathGlobal)两类。
	5、本地路径为相对于GNE自身的路径。
	6、全局路径为相对于GNS全局的路径。

	例子：
	游戏世界所提供的“移动玩家到指定位置”服务。
	本地路径："Player/Move/ToLocation"
	全局路径："GameSpace/Gateway00101/Player/Move/ToLocation"
*/

#define GNE_SERVICE_PATH_LOCAL_MAX_LEN	40
typedef char							GNE_SERVICE_PATH_LOCAL[GNE_SERVICE_PATH_LOCAL_MAX_LEN + 1];
#define GNE_SERVICE_PATH_GLOBAL_MAX_LEN (GNE_PATH_MAX_LEN + 1 + GNE_SERVICE_PATH_LOCAL_MAX_LEN)
typedef char							GNE_SERVICE_PATH_GLOBAL[GNE_SERVICE_PATH_GLOBAL_MAX_LEN + 1];


// === 消息交换模式 ===//
/*
	GNS中交互通过消息交换进行的。GNM是交互的基本单元。
	1、目前GNS支持两种消息交换模式：Reuqest-Reply模式和Request-NoReply模式。
	2、因此，消息也由两类：Request消息和Reply消息。
	3、对于Reply消息，提供返回码字段，用于表征结果。
	4、GNM分为头部HEAD（定长)和载荷LOAD两部分。
	5、载荷LOAD部分随应用不同而不同。
	6、载荷可以有不同的格式，用户可以自定义格式，只需要交互双方一致即可。
*/

// == GNM交换模式 ==//
enum GNM_EXCHANGE_PATTERN
{
	GNM_EXCHANGE_PATTERN_REQUEST_REPLY = 0,
	GNM_EXCHANGE_PATTERN_REQUEST_NO_REPLY
};

// == GNM类型 ==//
enum GNM_TYPE
{
	GNM_TYPE_REQUEST = 0,			// Request消息
	GNM_TYPE_REPLY,					// Reply消息
};

// == 响应类型的GNM的返回码 ==//
enum GNM_RET_CODE
{
	// GNS通用返回码，通用规则：0表示成功；非0表示成功以外的情形
	GRC_SUCCESS					= 0,	// 服务成功
	GRC_FAILED					= 1,	// 服务失败
	GRC_TIMEOUT					= 2,	// 服务超时
	GRC_SERVICE_UNAVAILABLE		= 3,	// 当前服务不可用
	GRC_NOT_SUPPORT				= 4,	// 服务不支持
	GRC_NOT_RECOGNIZED			= 5,	// 服务请求无法识别（格式错误）
	GRC_UNKOWN					= 6,	// 服务结果未知

	// GNS中枢进行消息路由时产生的返回码
	GRC_CENTER_INTERNAL_ERROR	= 100,
	GRC_CENTER_MSG_FILTERED		= 101,	// 消息被中枢过滤（没有权限）
	GRC_CENTER_DEST_OFFLINE		= 102,	// 消息路由的目的地不在线
	GRC_CENTER_TRANSFER_FAILED	= 103,	// 消息路由转发失败

	GRC_USER					= 1000,	// >= GPC_USER的为用户自定义的返回码
};

// == GNM消息中参数的格式 ==//
enum GNM_LOAD_FORMAT
{
	// == 文本格式 ==//
	GNM_LOAD_FORMAT_TEXT_PLAIN	= 0,	// 普通文本格式
	GNM_LOAD_FORMAT_TEXT_JSON	= 1,	// JSON文本格式
	GNM_LOAD_FORMAT_TEXT_XML	= 2,	// XML文本格式

	// == 二进制格式 ==//
	GNM_LOAD_FORMAT_BIN_PLAIN	= 50,	// 普通二进制格式

	// == 自定义格式 ==//
	GNM_LOAD_FORMAT_USER		= 100,	// 从GNM_LOAD_FORMAT_USER开始的格式编号表示是用户自定义的格式
};

// == GNM消息的头部的定义 ==//
struct GNM_HEAD
{
	unsigned char			ExchangePattern;		// 消息交换类型，参考：GNM_EXCHANGE_PATTERN
	unsigned char			Type;					// 消息类型，参考：GNM_TYPE
	unsigned short			RetCode;				// 返回码，仅仅对Reply消息有意义。参考：GNM_RET_CODE
	GNE_ADDR				Src;					// 消息来源地
	GNE_ADDR				Dest;					// 消息目的地
	GNE_SERVICE_PATH_LOCAL	ServicePath;			// 服务路径，消息交换涉及的是哪个服务。
	unsigned int			Sn;						// 消息序列号，一次消息交换过程唯一标识符。
	unsigned char			LoadFormat;				// 消息载荷的格式，参考：GNM_LOAD_FORMAT
};

// == GNM消息的载荷的定义 ==//
#define GNM_LOAD_MAX_LEN	(1024 * 40)				// GNM消息载荷的的最大长度为40K

#pragma pack()

// === 常用辅助函数 ===//
// 普通GNE_ADDR_SEGMENT中的字符的取值范围
static inline bool IS_NORMAL_GNE_ADDR_SEGMENT_CHAR(char ch)
{
	return ((ch >= 'a' && ch <= 'z') || 
		(ch >= 'A' && ch <= 'Z') || 
		(ch >= '0' && ch <= '9') ||
		(ch == '_'));
}

// 判断是否为普通GNE_ADDR_SEGMENT
static inline bool IS_NORMAL_GNE_ADDR_SEGMENT(const char* szSegment)
{
	char* pChar = (char*)szSegment;
	while(*pChar)
	{
		if (pChar - szSegment + 1 > GNE_ADDR_SEGMENT_MAX_LEN)
			return false;
		else if (!IS_NORMAL_GNE_ADDR_SEGMENT_CHAR(*pChar))
			return false;
		else
		{
			pChar++;
			continue;
		}
	}
	return true;
}

// 判断是否为通配GNE_ADDR_SEGMENT
static inline bool IS_ANY_GNE_ADDR_SEGMENT(const char* szSegment)
{
	return strcmp(szSegment, GNE_ADDR_SEGMENT_ANY) == 0;
}

// 判断GNE_TYPE是否相等
static inline bool IS_GNE_ADDR_SEGMENT_EQUAL(const char* szSegment1, const char* szSegment2)
{
	return strcmp(szSegment1, szSegment2) == 0;
}

// 判断是否为一个合法的GNE_ADDR
static inline bool IS_VALID_GNE_ADDR(const GNE_ADDR& GneAddr)
{
	if (IS_NORMAL_GNE_ADDR_SEGMENT(GneAddr.Type))			// 普通GNE_TYPE + 普通GNE_INST = 单播地址，合法
	{														// 普通GNE_TYPE + 广播GNE_INST = 组播地址，合法
		return true;								
	}
	else if (IS_ANY_GNE_ADDR_SEGMENT(GneAddr.Type))			// 广播GNE_TYPE + 广播GNE_INST = 广播地址，合法
	{
		return IS_ANY_GNE_ADDR_SEGMENT(GneAddr.Inst);
	}
	else													// 其它情况，非法
		return false;
}

// 判断是否为一个单播地址
// 前置条件：GneAddr是一个合法的GNE_ADDR
static inline bool IS_UNICAST_ADDR(const GNE_ADDR& GneAddr)
{
	return !IS_ANY_GNE_ADDR_SEGMENT(GneAddr.Type) && !IS_ANY_GNE_ADDR_SEGMENT(GneAddr.Inst);
}

// 判断是否为一个多播地址
// 前置条件：GneAddr是一个合法的GNE_ADDR
static inline bool IS_MULTICAST_ADDR(const GNE_ADDR& GneAddr)
{
	return !IS_ANY_GNE_ADDR_SEGMENT(GneAddr.Type) && IS_ANY_GNE_ADDR_SEGMENT(GneAddr.Inst);
}

// 判断是否为一个广播地址
// 前置条件：GneAddr是一个合法的GNE_ADDR
static inline bool IS_BROADCASE_ADDR(const GNE_ADDR& GneAddr)
{
	return IS_ANY_GNE_ADDR_SEGMENT(GneAddr.Type) && IS_ANY_GNE_ADDR_SEGMENT(GneAddr.Inst);
}

// 判断两个GneAddr是否相等
static inline bool IS_GNE_ADDR_EQUAL(const GNE_ADDR& Addr1, const GNE_ADDR& Addr2)
{
	return (IS_GNE_ADDR_SEGMENT_EQUAL(Addr1.Type, Addr2.Type) && IS_GNE_ADDR_SEGMENT_EQUAL(Addr1.Inst, Addr2.Inst));
}

// 将GNE_ADDR转换为GNE_PATH
static inline void GNE_ADDR_TO_GNE_PATH(const GNE_ADDR& Addr, GNE_PATH& Path)
{
	sprintf(Path, "%s/%s", Addr.Type, Addr.Inst);
}

// 获取当前路径的顶级目录
// 输入参数：	szPath:		--	路径字符串
// 输出参数：	szTopDir	--	当前路径的顶级目录，请确保szTopDir有足够的空间，建议：char szTopDir[GNE_RES_GLOBAL_PATH_MAX_LEN + 1];
// 返回值：	去掉顶级目录以及与该目录相关的分隔符'/'后剩余的路径字符串
//				NULL	--	说明已经没有下一级目录
//				非NULL	-- 说明还有下一级目录
// 例子：
/* 
	char szTopDir[GNE_SERVICE_PATH_GLOBAL_MAX_LEN + 1];
	const char* szPathLeft = "GMC/ForMoon/Control/AddGne";
	while(szPathLeft)
	{
		szPathLeft = GET_TOP_DIR(szPathLeft, szTopDir);
		printf("Current directory:%s\n", szTopDir);
	}
*/

static inline const char* GET_TOP_DIR(const char* szPath, char* szTopDir)
{
	assert(szPath && szPath[0] != '/');
	assert(szTopDir);

	while(!(*szPath == '/' || *szPath == '\0'))
		*szTopDir++ = *szPath++;
	*szTopDir = '\0';
	if (*szPath == '/')
		szPath++;
	if (*szPath == '\0')
		return NULL;
	else
		return szPath;
}

// 判断是否为合法的消息交换模式
static inline bool IS_VALID_GNM_EXCHANGE_PATTERN(unsigned char GnmExchangePattern)
{
	return (GnmExchangePattern == GNM_EXCHANGE_PATTERN_REQUEST_REPLY) || (GnmExchangePattern = GNM_EXCHANGE_PATTERN_REQUEST_NO_REPLY);
}

// 判断是否为合法的GNM_TYPE
static inline bool IS_VALID_GNM_TYPE(unsigned char GnmType)
{
	return (GnmType == GNM_TYPE_REQUEST ||  GnmType == GNM_TYPE_REPLY);
};

static inline bool IS_VALID_IP_ADDRESS(const char* szIPAddress)
{
	int nValue[4];
	int nRet = sscanf(szIPAddress, "%d.%d.%d.%d", &nValue[0], &nValue[1], &nValue[2], &nValue[3]);
	if (nRet == 4 &&
		nValue[0] >= 0 && nValue[0] < 256 &&
		nValue[1] >= 0 && nValue[1] < 256 &&
		nValue[2] >= 0 && nValue[2] < 256 &&
		nValue[3] >= 0 && nValue[3] < 256)
	{
		return true;
	}
	return false;
}

#endif // #ifndef __GMC_NETWORK_SYSTEM_DEF_H__
