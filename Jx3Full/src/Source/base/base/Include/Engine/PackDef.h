//---------------------------------------------------------------------------
// (c) 2005 by Kingsoft
// Date:	2005.2.28
// Code:	wooy
//---------------------------------------------------------------------------
#ifndef __ENGINE_PAK_DEF_H_
#define __ENGINE_PAK_DEF_H_

//------------------------------------------------------------------
//----				打包文件存储结构定义					--------
//------------------------------------------------------------------
#define	XPACKFILE_SIGNATURE_FLAG		0x4b434150	//'PACK'

//一个Pack文件具有的头结构:
struct XPackFileHeader
{
	unsigned char	cSignature[4];		//四个字节的文件的头标志，固定为字符串'PACK'
	unsigned int	uCount;				//数据的条目数
	unsigned int	uIndexTableOffset;	//索引的偏移量
	unsigned int	uDataOffset;		//数据的偏移量
	unsigned int	uCrc32;				//校验和(根据索引表内容数据求得)
	unsigned int	uPakTime;			//打包文件制作时的时间，秒为单位time()
	unsigned char	cReserved[8];		//保留的字节
};

//Pack中对应每个子文件的索引信息项
struct XPackIndexInfo
{
	unsigned int	uId;				//子文件id
	unsigned int	uOffset;			//子文件在包中的偏移位置
	unsigned int	uSize;				//子文件的原始大小
	unsigned int	uCompressSizeFlag;	//子文件压缩后的大小和压缩方法
	//最高字节表示压缩方法，见XPACK_METHOD与XPAK_FLAG
	//低的三个字节表示子文件压缩后的大小；对于分块压缩的文件，包含该文件全部分块数据，头信息数据，分块信息表等加起来的全部大小。
};

//分块压缩的文件的文件数据存储区存储的内容与顺序一般为：
// [XPackFileFragmentElemHeader] + [第一块数据] + [第二块数据] + .. + [第n块数据] + [n个XPackFileFragmentInfo的数组]

//分块压缩的文件在该文件数据存储区起始位置的头数据结构
struct XPackFileFragmentElemHeader
{
	int				nNumFragment;		//分块的数目
	int				nFragmentInfoOffest;//分块信息表的偏移位置,相对于XPackFileFragmentElemHeader开始位置的偏移
};

//分块压缩文件的分块信息
struct XPackFileFragmentInfo
{
	unsigned int	uOffset;			//此分块数据的起始处在子文件数据区中的偏移位置,相对于XPackFileFragmentElemHeader开始位置的偏移
	unsigned int	uSize;				//此分块的原始大小
	unsigned int	uCompressSizeFlag;	//此分块压缩后的大小和压缩方法，类似与XPackIndexInfo结构中的uCompressSizeFlag
};


//包文件的压缩方式
enum XPACK_METHOD_AND_FLAG
{
	XPACK_METHOD_NONE				= 0x00000000,	//没有压缩
//	XPACK_METHOD_UCL_OLD			= 0x01000000,	//UCL压缩
//	XPACK_METHOD_FILTER_OLD			= 0x0f000000,	//过滤标记
//	XPACK_COMPRESS_SIZE_FILTER_OLD	= 0x00ffffff,	//压缩后大小过滤标记

	XPACK_METHOD_UCL				= 0x20000000,	//UCL压缩
	XPACK_METHOD_FILTER				= 0xf0000000,	//过滤标记

	XPACK_FLAG_FRAGMENT				= 0x10000000,	//子文件分块压缩
	XPACK_COMPRESS_SIZE_FILTER		= 0x07ffffff,	//压缩后大小过滤标记,最大支持128M
	XPACK_COMPRESS_SIZE_BIT			= 27,
};


//------------------------------------------------------------------
//----			打包信息文件存储结构定义					--------
//	打包信息文件记录了与每一个打包文件一一对应，记录了包中每个子文件
//的相关信息。打包文件配合打包信息文件，就可以轻松的解出包中的全部子
//文件。 如打包文件文件名为image.pak则对应的打包信息文件文件名为
//image.pak.txt。
//------------------------------------------------------------------
//  打包信息文件为文本格式每行中各数据域以\t分隔。
//  第一行格式示例：
//		TotalFile:220	PakTime:2005-3-20 18:00:00	PakTimeSave:4239E52B	CRC:02FE0701
//		第一个组数字“220”为包中子文件的数目
//		第二组数字“2005-3-20 18:00:00”为易于阅读的包文件的制作时间，与XPackFileHeader::uPakTime为对应一致的时间。
//		第三组数字“4239E52B”(16进制)表示包文件的制作时间，与XPackFileHeader::uPakTime为对应一致的时间。
//		第四组数字“02FE0701”(16进制)为包文件的CRC校验数。
//	第二行为表示第三行开始的内容对应的格式符串，固定如下：
//		Index	ID	Time	FileName	Size	InPakSize	ComprFlag	CRC	
//		分别表示含义如下：
//			Index		子文件在包中的索引
//			ID			子文件的ID
//			Time		子文件的时间（对于取自库中的文件为Checkin操作时间，对于复制于共享目录的文件为文件的最后修改时间）
//			FileName	子文件的文件名（相对于游戏根目录）
//			Size		子文件的原始大小（单位：字节）
//			InPakSize	子文件在包中的存储大小（单位：字节）
//			ComprFlag	子文件的压缩标记(16进制数)，其值为(XPackIndexInfo::uCompressSizeFlag >> 24)
//			CRC			子文件的CRC校验数，根据子文件压缩前完整内容数据求得。
//  后面的每一行表示一个包中子文件的信息，按照Index递增顺序排列，示例如下：
//		0	769629AC	2005-3-19 18:50:00	\settings\serverlist.ini	741		741	0	04657F80
//		1	6FCAA162	2005-3-18 19:00:00	\ui\setting.ini	1519	624	1	2D332871

#endif //#ifndef __ENGINE_PAK_DEF_H_
