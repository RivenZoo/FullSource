#ifndef __LOCALIZATION_H__
#define __LOCALIZATION_H__
//======================================================
//====				本地化处理工程					====
//======================================================


enum LOCALIZATION_CHARACTER_SET
{
	LOCALIZATION_CHARACTER_SET_GBK		= 0,	//GBK编码
	LOCALIZATION_CHARACTER_SET_BIG5		= 1,	//BIG5编码
	LOCALIZATION_CHARACTER_SET_ENGLISH	= 2,	//英文编码
	LOCALIZATION_CHARACTER_SET_VIETNAM	= 3,	//越南文编码
};

#ifndef LOCALIZATION_INTERNAL_SIGNAL
//------接口函数的原型定义----------
typedef int (*fnLOC_IsCharacterNotAllowAtLineHead)(const char* pCharacter);
typedef int (*fnLOC_GetCharacterWide)(const char* pCharacter);
//------接口函数的函数名字符串----------
#define	FN_IS_CHARACTER_NOT_ALLOW_AT_LINE_END		"LOC_IsCharacterNotAllowAtLineHead"
#define FN_GET_CHARACTER_WIDE						"LOC_GetCharacterWide"

extern "C"
{
	//获取该本地化版本的语言集
	LOCALIZATION_CHARACTER_SET LOC_GetLocalizationCharacterSet(LOCALIZATION_CHARACTER_SET);
	//检测某个字符是否为不许放置行首的字符，不是限制字符则返回0，否则返回字符占的子节数
	int LOC_IsCharacterNotAllowAtLineHead(const char* pCharacter);
	//得到一个字符的宽度（占几个字节）
	int LOC_GetCharacterWide(const char* pCharacter);
}

#endif //LOCALIZATION_INTERNAL_SIGNAL

#endif //__LOCALIZATION_H__

