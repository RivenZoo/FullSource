//---------------------------------------------------------------------------
// 剑侠情缘网络版2 TextParamAnalyse 文本参数解析
// 版权所有:       2007 金山软件(Kingsoft)
// 创建日期与作者: 越子(wooy)
//---------------------------------------------------------------------------
#ifndef __TEXT_PARAM_ANALYSE_H__
#define __TEXT_PARAM_ANALYSE_H__

#ifndef WIN32     // linux
	#define		C_TPA_API extern "C"
#else               //WIN32
	#ifdef TEXT_PARAM_ANALYSE_INTERNAL
		#define C_TPA_API extern "C" __declspec(dllexport)
	#else
		#define C_TPA_API extern "C" __declspec(dllimport)
	#endif
#endif

//-----------------------------------------------------------------------
// 注意：这些接口函数，对各种各种指针传入参数，在这些函数的实现代码中，统
// 一不做是否为空指针的检查，其它也都调用的模块需要自行保证该指针不为空！
// KTextParamAnalyseInfo::pString也不例外。！！！！！！！！！！！！！！！
//-----------------------------------------------------------------------
namespace KTextParamAnalyse
{
	struct KTextParamAnalyseInfo
	{
		const char*		pString;		//指向存有文本参数数据的缓冲区，不需要以0结尾
		int				nStringMaxLen;	//文本参数数据的缓冲区中的内容的长度（字节数）
		int				nStartPos;		//当前分析到的位置（从pString开始算的(字节长度)偏移量）
	};
	enum STANDARD_RESULT
	{
		SR_OK = 0,			//搞定
		SR_FAIL,			//失败
		SR_TIMEOUT,			//超时
		SR_DISPATCH_FAIL,	//发送失败
		SR_CMD_ERR,			//命令错误
		SR_NOT_ALLOW,		//操作不被允许，超过授权许可
		SR_NONE,			//无对应结果，（查询的）指定对象不存在
		STANDARD_RESULT_COUNT, 
	};
	enum
	{
		MAX_FIELD_PREFIX_LEN = 15, //字段前缀的最长允许长度，不含冒号和字符串结尾符0
	};
	//从开始解析位置获取一个字符串，nMaxLen表示字符串的最大长度(包含结尾符)。
	//若传入的pString缓冲区不足够大，则该函数返回false，且维持数据处理位置不变。
	C_TPA_API bool	AnalyseString(KTextParamAnalyseInfo& info, char* pString, int nMaxLen);
	//从开始解析位置获取一个字符串字段，pFieldPrefix为字段前缀标识，nMaxLen表示字符串的最大长度(包含结尾符)；
	//如果字符串超长，则返回失败，如果字符串长度为0，也返回成功。返回成功时pString内已存好一个以0结尾的字符串。
	//传入的pFieldPrefix参数字符串不需要带:分隔符。bMatch为传出参数，表示解析的内容是否为指定的字段（字段前缀是否已匹配上了）。
	//若传入的pString缓冲区不足够大，则该函数返回false，且维持数据处理位置不变。
	C_TPA_API bool	AnalyseFieldString(KTextParamAnalyseInfo& info, const char* pFieldPrefix, char* pString, int nMaxLen, bool& bMatch);
	//从开始解析位置获取一个整数字段，pFieldPrefix为字段前缀标识
	C_TPA_API bool	AnalyseFieldInteger(KTextParamAnalyseInfo& info, const char* pFieldPrefix, int& nValue, bool& bMatch);
	//从开始解析位置获取一个16进制整数字段，pFieldPrefix为字段前缀标识
	C_TPA_API bool	AnalyseFieldInteger16(KTextParamAnalyseInfo& info, const char* pFieldPrefix, unsigned int& uValue, bool& bMatch);
	//判断是否为指定的字段
	C_TPA_API bool	AnalyseIsField(const KTextParamAnalyseInfo& info, const char* pFieldPrefix);
	//判断是否为指定的字段，并根据判断结果，决定是否要跳过该字段。该函数执行每一次只处理最前面的一个字段，不会主动连续处理。
	//参数说明：bJumpIfMath 为真值时表示如果为指定字段则跳过，为零值时表示如果不是指定字段则跳过
	//参数说明：bEncounterErr 为传出参数，表示解析时是否遇到错误。如果遭遇，则一定不会掉过字段，返回值一定是false。
	//返回值表示：是否因为符合条件而跳过了最前面的一个字段
	C_TPA_API bool	AnalyseIsFieldThenJump(KTextParamAnalyseInfo& info, const char* pFieldPrefix, bool bJumpIfMatch, bool& bEncounterErr);
	//获取首个字段的前缀名称，pFieldPrefix指向的缓冲区长度不小于MAX_FIELD_PREFIX_LEN+1个字节，返回的字段前缀不含冒号和字符串结尾符0
	C_TPA_API bool	AnalyseGetFirstFieldPrefix(const KTextParamAnalyseInfo& info, char* pFieldPrefix);
//====常用基本字段分析，分析之后会掉过后续如果存在的间隔符号=====
	//分析序列号字段
	C_TPA_API bool	AnalyseFieldSn(KTextParamAnalyseInfo& info, unsigned int& uSn0, unsigned int& uSn1);
	//分析区服索引字段，返回值表示是否成功取得了所想要的值。传出参数bMatch表示正在分析的字段是否是GROUP字段
	C_TPA_API bool	AnalyseFieldGroup(KTextParamAnalyseInfo& info, int& nArea, int& nGroup, bool& bMatch);
	//分析区服名称字段，返回值表示是否成功取得了所想要的值。传出参数bMatch表示正在分析的字段是否是GROUPN字段
	//若传入的pGroupName缓冲区不足够大，则该函数返回false，且维持数据处理位置不变。
	C_TPA_API bool	AnalyseFieldGroupN(KTextParamAnalyseInfo& info, char* pGroupName, int nMaxLen, bool& bMatch);
	//分析帐号名字段
	//若传入的pAccount缓冲区不足够大，则该函数返回false，且维持数据处理位置不变。
	C_TPA_API bool	AnalyseFieldAcc(KTextParamAnalyseInfo& info, char* pAccount, int nMaxLen, bool& bMatch);
	//分析角色名字段
	//若传入的pRole缓冲区不足够大，则该函数返回false，且维持数据处理位置不变。
	C_TPA_API bool	AnalyseFieldRole(KTextParamAnalyseInfo& info, char* pRole, int nMaxLen, bool& bMatch);
	//分析对象名字段
	//若传入的pObj缓冲区不足够大，则该函数返回false，且维持数据处理位置不变。
	C_TPA_API bool	AnalyseFieldObj(KTextParamAnalyseInfo& info, char* pObj, int nMaxLen, bool& bMatch);
	//传入的nSize为pData可接受的字符串的最大长度(含结束符),传出的nSize为实际取得的字符串的长度(含结束符)
	//若传入的pData缓冲区不足够大，则该函数返回false，且维持数据处理位置不变。
	C_TPA_API bool	AnalyseSizeFieldText(KTextParamAnalyseInfo& info, const char* pFieldPrefix, char* pData, int& nSize, bool& bMatch);
	//判断是否为T_????段，如果是其数据长度为多少
	C_TPA_API bool	AnalyseSizeFieldTextSize(const KTextParamAnalyseInfo& info, const char* pFieldPrefix, int& nSize, int& nDataOffset);
	//传入的nSize为pData可接受的字符串的最大长度,传出的nSize为实际取得的字符串的长度
	//若传入的pData缓冲区不足够大，则该函数返回false，且维持数据处理位置不变。
	C_TPA_API bool	AnalyseSizeFieldBin(KTextParamAnalyseInfo& info, const char* pFieldPrefix, void* pData, int& nSize, bool& bMatch);
	//判断是否为B_????段，如果是其数据长度为多少
	C_TPA_API bool	AnalyseSizeFieldBinSize(const KTextParamAnalyseInfo& info, const char* pFieldPrefix, int& nSize, int& nDataOffset);

//====基本字段构造=====
	//获取'请求的处理结果'字段的标准字符串
	C_TPA_API const char*	GetStandardResultFieldString(STANDARD_RESULT eResult);

	//从一个字符串缓冲区的头部读取一个以16进制表示的数值
	//参数pString为缓冲区头部的开始指针，参数nStringMaxLen为缓冲区的长度
	//转换过程以处理到缓冲区结尾或第一个非'0~9'且非'A-F'的字符为止，参数nConvertLen传出经过转换处理的字符的数目。
	//返回值为读取到的数值，如果未读取到数值，则返回0，此时nConvertLen也传出0。
	C_TPA_API bool ConvertString16ToInteger(const char* pString, int nStringMaxLen, int& nConvertedLen, unsigned int& uValue);

	//从一个字符串缓冲区的头部读取一个以10进制表示的数值
	//参数pString为缓冲区头部的开始指针，参数nStringMaxLen为缓冲区的长度
	//转换过程以处理到缓冲区结尾或第一个非'0~9'的字符为止，参数nConvertLen传出经过转换处理的字符的数目。
	//返回值为读取到的数值，如果未读取到数值，则返回0，此时nConvertLen也传出0。
	//可以处理负数。
	C_TPA_API bool ConvertString10ToInteger(const char* pString, int nStringMaxLen, int& nConvertedLen, int& nValue);
};

#endif //__TEXT_PARAM_ANALYSE_H__
