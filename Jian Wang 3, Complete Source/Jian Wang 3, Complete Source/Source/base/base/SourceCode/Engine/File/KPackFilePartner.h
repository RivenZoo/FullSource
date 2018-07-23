/*****************************************************************************************
//	包文件的伴侣文件
//	Copyright : Kingsoft 2005
//	Author	:   Wooy(Wu yue)
//	CreateTime:	2005-3-23
------------------------------------------------------------------------------------------
用与纪录打包文件中各子文件的文件名之类的相关信息
*****************************************************************************************/
#ifndef _ENGINE_PACK_FILE_PARTNER_H_
#define _ENGINE_PACK_FILE_PARTNER_H_

#include "IPackFileShell.h"

class KPackFilePartner
{
public:
	struct PACKPARTNER_ELEM_INFO
	{
		int				nElemIndex;					//在包中的第几个子文件
		unsigned int	uId;						//子文件ID
		unsigned int	uSize;						//子文件原始大小
		unsigned int	uStoreSizeAndCompressFlag;	//子文件在包中的存储大小与子文件的压缩标记,与XPackIndexInfo::uCompressSizeFlag相同
		unsigned int	uTime;						//子文件的时间
		unsigned int	uCRC;						//校验和
		char			szFileName[128];			//子文件的文件名（相对于游戏根目录）
	};
public:
	KPackFilePartner();
	~KPackFilePartner();
	//初始化
	bool	Init();
	//清空数据
	void	Clear();
	//加载打包文件信息
	bool	Load(const char* pFileName);
	//保存打包文件信息
	bool	Save(const char* pFileName, unsigned int uPackTime, unsigned int uPackCRC);
	//检查打包信息文件是否匹配特定信息
	bool	IsPartnerMatch(int nElemCount, unsigned int uPackTime, unsigned int uCRC);
	//往打包文件中添加一个子文件
	bool	AddElem(PACKPARTNER_ELEM_INFO& ElemInfo);
	//删除打包文件中的一个子文件
	bool	DeleteElemInPak(unsigned int uElemID);
	//获取子文件信息
	bool	GetElemInfo(unsigned int uElemId, PACKPARTNER_ELEM_INFO& info);
	//扫描整个包文件集合，对于每个子文件给出进行一次回调函数操作
	//参数pFileNamePrefix表示遍历到的子文件名的前缀必须与此给定的字符串完全一致（不区分大小写），前缀不符的子文件将被略过，传入空指针表示无前缀限制。
	//返回值表示多少个满足条件的子文件被扫描到
	//int		ScanAllPack(IPackFileShell::fnScanPackCallback pCallback, const char* pFileNamePrefix = NULL);

private:
	//查找子文件项
    bool    FindElem(unsigned int uElemId, unsigned int& uIndex);
private:
	PACKPARTNER_ELEM_INFO*		m_pElemInfoList;

	int							m_nElemCount;		//子文件数目
	unsigned int				m_uPackTime;		//打包文件制作时的时间，秒为单位time()
	unsigned int				m_uCRC;				//校验和

	IPackFileShell::fnAddFolderToPakCallback	m_pScanCallback;
};

#endif //_ENGINE_PACK_FILE_PARTNER_H_