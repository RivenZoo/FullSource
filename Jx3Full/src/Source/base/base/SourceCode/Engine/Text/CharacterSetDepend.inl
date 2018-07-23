//---------------------------------------------------------------------------
//	文字串处理
//	Copyright : Kingsoft 2007
//	CreateTime:	2007-8
//---------------------------------------------------------------------------
//文字串处理中根据不同的编码情况，有不同实现的处理函数/代码，汇集在此源文件中。
//---------------------------------------------------------------------------


//=============================================================================================================
//>>  西文 LOCALIZATION_CHARACTER_SET_ENGLISH 相关代码 开始
//=============================================================================================================
//检测某个字符是否为不许放置行首的字符
#define	ENGLISh_NUM_CHARACTER_IN_00	7
unsigned char	s_ENGLISH_NotAllowAtLineHead00Characters[ENGLISh_NUM_CHARACTER_IN_00] =
{
	//!),.:;>?
	0x21, 0x29, 0x2c, /*0x2e,*/ 0x3a, 0x3b, 0x3e, 0x3f
};

//检测某个字符是否为不许放置行首的字符，不是限制字符则返回0，否则返回字符占的子节数
int ENGLISH_IsCharacterNotAlowAtLineHead(const char *pCharacter)
{
	for (int i = 0; i < ENGLISh_NUM_CHARACTER_IN_00; ++i)
		if ((unsigned char)(*pCharacter) == s_ENGLISH_NotAllowAtLineHead00Characters[i])
			return 1;
	return false;
}
//=============================================================================================================
//  西文 LOCALIZATION_CHARACTER_SET_ENGLISH 相关代码 结束
//=============================================================================================================



//=============================================================================================================
//>> 简体中文 LOCALIZATION_CHARACTER_SET_GBK 相关代码 开始
//=============================================================================================================
//检测某个字符是否为不许放置行首的字符
#define	GBK_NUM_CHARACTER_IN_A1	11
unsigned char	s_GBK_NotAllowAtLineHeadA1Characters[GBK_NUM_CHARACTER_IN_A1] = 
{
	//、。’〕〉》」』〗】
	0xa2, 0xa3, 0xaf, 0xb1, 0xb3, 0xb5, 0xb7, 0xb9, 0xbb, 0xbd, 0xbf
};
#define	GBK_NUM_CHARACTER_IN_A3	10
unsigned char	s_GBK_NotAllowAtLineHeadA3Characters[GBK_NUM_CHARACTER_IN_A3] = 
{
	//！   ）    ，   ．     ：    ；   ＞    ？    ］    ｝
	0xa1, 0xa9, 0xac, 0xae, 0xba, 0xbb, 0xbe, 0xbf, 0xdd, 0xfd
};
// 包括西文的不许放置行首的字符

//检测GBK编码的某个字符是否为不许放置行首的字符，不是限制字符则返回0，否则返回字符占的子节数
int GBK_IsCharacterNotAlowAtLineHead(const char *pCharacter)
{
	int				i;
	unsigned char	cChar;
	cChar = (unsigned char)(*pCharacter);

	if (cChar == 0xa3)
	{
		cChar = (unsigned char)pCharacter[1];
		if (cChar >= 0xa1 && cChar <= 0xfd)
		{
			for (i = 0; i < GBK_NUM_CHARACTER_IN_A3; i++)
				if (s_GBK_NotAllowAtLineHeadA3Characters[i] == cChar)
					return 2;
		}
	}
	else if (cChar == 0xa1)
	{
		cChar = (unsigned char)pCharacter[1];
		if (cChar >= 0xa2 && cChar <= 0xbf)
		{
			for (i = 0; i < GBK_NUM_CHARACTER_IN_A1; i++)
				if (s_GBK_NotAllowAtLineHeadA1Characters[i] == cChar)
					return 2;
		}
	}
	else 
		return ENGLISH_IsCharacterNotAlowAtLineHead(pCharacter);

	return false;
}
//=============================================================================================================
//  简体中文 LOCALIZATION_CHARACTER_SET_GBK 相关代码 结束
//=============================================================================================================



//=============================================================================================================
//>> 繁体中文 LOCALIZATION_CHARACTER_SET_BIG5 相关代码 开始
//=============================================================================================================
//检测某个字符是否为不许放置行首的字符
#define BIG5_NUM_CHARACTER_IN_A1 36
unsigned char s_BIG5_NotAllowAtLineHeadA3Characters[BIG5_NUM_CHARACTER_IN_A1] = 
{
	//，   、    。    ．    ?    ；    ：    ？    ！    ︰    …    ‥    ﹐    ﹑    ﹒
	0x41, 0x42, 0x43, 0x44 ,0x45 ,0x46 ,0x47 ,0x48 ,0x49 ,0x4A ,0x4B, 0x4C, 0x4D, 0x4E ,0x4F ,
	//·   ﹔   ﹕    ﹖    ﹗     ）
	0x50 ,0x51 ,0x52 ,0x53 ,0x54 ,0x5E ,
	//｝   〕    】    》
	0x62 ,0x66 ,0x6A ,0x6E ,
	//〉   」    』    ﹚
	0x72 ,0x76 ,0x7A ,0x7E ,
	//﹜   ﹞    ’    ”     〞    ′
	0xA2 ,0xA4 ,0xA6 ,0xA8 ,0xAA ,0xAC ,
	//﹥
	0xE1 ,
};
//跟西文的规则相同

//检测BIG5编码的某个字符是否为不许放置行首的字符，不是限制字符则返回0，否则返回字符占的子节数
int BIG5_IsCharacterNotAlowAtLineHead(const char *pCharacter)
{
	if ((unsigned char)(*pCharacter) == 0xa1)
	{
		for (int i = 0; i < BIG5_NUM_CHARACTER_IN_A1; ++i)
			if ((unsigned char)(pCharacter[1]) == s_BIG5_NotAllowAtLineHeadA3Characters[i])
				return 2;
	}
	else 
		return ENGLISH_IsCharacterNotAlowAtLineHead(pCharacter);

	return false;
}
//=============================================================================================================
//  繁体中文 LOCALIZATION_CHARACTER_SET_BIG5 相关代码 结束
//=============================================================================================================



//=============================================================================================================
//>> 越南文 LOCALIZATION_CHARACTER_SET_VIETNAM 相关代码 开始
//=============================================================================================================
//检测某个字符是否为不许放置行首的字符
//越南文的规则跟西文的相同

//=============================================================================================================
//  越南 LOCALIZATION_CHARACTER_SET_VIETNAM 相关代码 结束
//=============================================================================================================

