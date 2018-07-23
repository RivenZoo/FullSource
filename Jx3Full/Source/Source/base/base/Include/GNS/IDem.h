//--------------------------------------------------------------
//	月影传说网络版	DataExchangeMechanism(DEM)
//	版权所有:			2010 金山软件(Kingsoft)
//	创建日期与作者:	2010-4-2 Golton Gao
//--------------------------------------------------------------
#ifndef __I_DATA_EXCHANGE_MECHANISM_H__
#define __I_DATA_EXCHANGE_MECHANISM_H__
/*--------------------------------------------------------------
	[说明]：
		1、此工程参考了JsonCpp，感谢Baptiste Lepilleur。
		2、引入Base64算法，方便二进制数据和文本之间的变换。
	[例子]：
		请参考DemDemo工程
	[概念]：
		DO(DataObject)：		数据对象，由原子类型、数组(ARRAY）、结构(STRUCT)等类型的数据嵌套组成的对象。
								数据对象有两种存在形式:DVO和DSO。
		DVO(DataValueObject)：	数据值对象，以树状结构存在，用于运行时进行值/字段/元素的存取
		DSO(DataS11nObj):		数据序列化对象，以字节流形式存在的，用于网络传输或者持久化
		注：S11n = Serialization
---------------------------------------------------------------*/

// === DVO相关 ===//

// == DVO的类型 ==//
enum DVO_TYPE
{
	// == 原子类型 ==//
	DVO_TYPE_NULL = 0,	// NULL类型
	DVO_TYPE_BOOL,		// 布尔类型
	DVO_TYPE_LONGLONG,	// 整数类型(统一为64位)
	DVO_TYPE_DOUBLE,	// 浮点类型(统一为64位)

	// == 复合类型 ==//
	DVO_TYPE_STRING,	// 字符串类型
	DVO_TYPE_ARRAY,		// 数组类型
	DVO_TYPE_STRUCT,	// 结构类型
};

// 判断是否为合法的DO类型
static inline bool IS_VALID_DVO_TYPE(int nType)
{
	return (nType >= DVO_TYPE_NULL && nType <= DVO_TYPE_STRUCT);
}

// == DVO字段名 ==//
#define DVO_FIELD_NAME_MAX_LEN	32							// 字段名的最大长度为32个字符（不包括'\0')
typedef	char DVO_FIELD_NAME[DVO_FIELD_NAME_MAX_LEN + 1];	// 字段名类型定义


// == 数据值对象 ==//
// 数据值对象是一种“元对象”，它可以是多种类型（参见DEM_DO_TYPE）的，具体类型只能在运行时决定
// 针对不同的类型，有不同的接口，在使用时务必对其类型做到心中有数
struct IDataValueObject
{
	// === 生命期管理 ===//

	// 创建数据值对象
	// DataValueObjectCreate
	// DataValueObjectCreate创建出的DVO是NULL类型的


	// === 针对所有类型的接口 ===//

	// 获取Object的类型
	// 返回值：DVO的类型，参见DEM_DO_TYPE
	virtual int	 GetType() = 0;



	// === 针对NULL类型的接口 ===//
	// DataValueObjectCreate只能创建出NULL类型的DVO，其它类型的DVO只能通过NULL类型的转换接口实现


	// 将对象转化为BOOL类型
	// 前置条件：对象类型为NULL
	virtual bool ToBool(bool bBool) = 0;	

	// 将对象转化为LONGLONG类型
	// 前置条件：对象类型为NULL
	virtual bool ToLongLong(long long llLongLong) = 0;

	// 将对象转化为DOUBLE类型
	// 前置条件：对象类型为NULL
	virtual bool ToDouble(double dDouble) = 0;

	// 将对象转化为STRING类型
	// 前置条件：对象类型为NULL
	virtual bool ToString(const char* szStr) = 0;

	// 将对象转化为ARRAY类型
	// 前置条件：对象类型为NULL
	virtual bool ToArray() = 0;

	// 将对象转化为STRUCT类型
	// 前置条件：对象类型为NULL
	virtual bool ToStruct() = 0;



	// === 针对BOOL类型的接口 ===//

	// 获取bool值
	// 前置条件：对象类型为BOOL
	virtual bool GetBool() = 0;

	// 设置bool值
	// 前置条件：对象类型为BOOL
	virtual bool SetBool(bool bBool) = 0;



	// === 针对longlong类型的接口 ===//
	// 获取longlong值
	// 前置条件：对象类型为LONGLONG
	virtual long long GetLongLong() = 0;

	// 设置longlong值
	// 前置条件：对象类型为LONGLONG
	virtual bool SetLongLong(long long llLongLong) = 0;



	// === 针对DOUBLE类型的接口 ===//

	// 获取double值
	// 前置条件：对象类型为DOUBLE
	virtual double GetDouble() = 0;

	// 设置double值
	// 前置条件：对象类型为DOUBLE
	virtual bool SetDouble(double dDouble) = 0;



	// === 针对STRING类型的接口 ===//

	// 获取string值
	// 前置条件：对象类型为STRING
	virtual const char* GetString() = 0;

	// 设置string值
	// 前置条件：对象类型为STRING
	virtual bool SetString(const char* szStr) = 0;



	// === 针对ARRAY类型的接口 ===//
	// ARRAY类型可以看作是同种类型的多个DVO元素(Element)的集合
	// ARRAY类型的接口就是针对Element进行CRUD(增删改查)的操作


	// == ARRAY增加操作(Add操作)的接口 ==//

	// 增加一个NULL类型的元素
	// 返回值：	NULL	--	增加元素失败
	//				非NULL	--	增加元素成功，返回的为增加元素的对象的指针
	// 前置条件：对象类型为ARRAY
	virtual IDataValueObject* AddElemNull() = 0;

	// 增加一个BOOL类型的元素
	// 返回值：	NULL	--	增加元素失败
	//				非NULL	--	增加元素成功，返回的为增加元素的对象的指针
	// 前置条件：对象类型为ARRAY
	virtual IDataValueObject* AddElemBool(bool bBool) = 0;

	// 增加一个LONGLONG类型的元素
	// 返回值：	NULL	--	增加元素失败
	//				非NULL	--	增加元素成功，返回的为增加元素的对象的指针
	// 前置条件：对象类型为ARRAY
	virtual IDataValueObject* AddElemLongLong(long long llLongLong) = 0;

	// 增加一个DOUBLE类型的元素
	// 返回值：	NULL	--	增加元素失败
	//				非NULL	--	增加元素成功，返回的为增加元素的对象的指针
	// 前置条件：对象类型为ARRAY
	virtual IDataValueObject* AddElemDouble(double dDouble) = 0;

	// 增加一个STRING类型的元素
	// 返回值：	NULL	--	增加元素失败
	//				非NULL	--	增加元素成功，返回的为增加元素的对象的指针
	// 前置条件：对象类型为ARRAY
	virtual IDataValueObject* AddElemString(const char* szStr) = 0;

	// 增加一个不含任何元素的ARRAY类型的元素
	// 返回值：	NULL	--	增加元素失败
	//				非NULL	--	增加元素成功，返回的为增加元素的对象的指针
	// 前置条件：对象类型为ARRAY
	virtual IDataValueObject* AddElemArray() = 0;

	// 增加一个不含任何字段的STRUCT类型的元素
	// 返回值：	NULL	--	增加元素失败
	//				非NULL	--	增加元素成功，返回的为增加元素的对象的指针
	// 前置条件：对象类型为ARRAY
	virtual IDataValueObject* AddElemStruct() = 0;


	// == ARRAY删除操作(Del操作)的接口 ==//

	// 删除ARRAY中的一个元素
	// 前置条件：对象类型为ARRAY且元素索引合法
	virtual void DelElem(unsigned int uElemIndex) = 0;


	// == ARRAY修改操作(Set操作)的接口 ==//

	// 设置BOOL类型的元素的值
	// 前置条件：对象类型为ARRAY且元素索引合法且元素类型为BOOL
	virtual bool SetElemBool(unsigned int uElemIndex, bool bBool) = 0;

	// 设置LONGLONG类型的元素的值
	// 前置条件：对象类型为ARRAY且uIndex合法且元素类型为LONGLONG
	virtual bool SetElemLongLong(unsigned int uIndex, long long llLongLong) = 0;

	// 设置DOUBLE类型的元素的值
	// 前置条件：对象类型为ARRAY且uIndex合法且元素类型为DOUBLE
	virtual bool SetElemDouble(unsigned int uIndex, double dDouble) = 0;

	// 设置STRING类型的元素的值
	// 前置条件：对象类型为ARRAY且uIndex合法且元素类型为STRING
	virtual bool SetElemString(unsigned int uIndex, const char* szStr) = 0;


	// == ARRAY查询操作(Get操作)的接口 ==//

	// 遍历ARRAY
	/*
		例子：
		IDataValueObject* pArray;
		unsigned int uElemNum = pArray->GetElemNum();
		for (unsigned int i = 0; i < uElemNum; i++)
		{
			switch(pElem->GetElemType(i))
			{
				case DVO_TYPE_STRING:
					printf("FieldValue:%s\n", pArray->GetElemValue(i)->GetString());
				break;
				//...
			}
		}
	*/

	// 获取ARRAY中元素的数量
	// 前置条件：对象类型为ARRAY
	virtual unsigned int GetElemNum() = 0;

	// 获取元素类型
	// 前置条件：对象类型为ARRAY且元素索引值合法
	virtual int GetElemType(unsigned int uElemIndex) = 0;

	// 获取元素值
	// 前置条件：对象类型为ARRAY且元素索引值合法
	virtual IDataValueObject* GetElemValue(unsigned int uElemIndex) = 0;



	// === 针对STRUCT类型的接口 ===//
	// STRUCT类型可以看作是不种类型的多个DVO字段(Field)的集合
	// 每个字段(Field)包括字段名(FieldName)和字段值(FieldValue)
	// 字段名的长度(不包括'\0')必须<=DVO_FIELD_NAME_MAX_LEN
	// STRUCT类型的接口就是针对Field进行CRUD(增删改查)的操作


	// == STRUCT增加操作(Add操作)的接口 ==//

	// 增加一个NULL类型的字段
	// 返回值：	NULL	--	增加字段失败
	//				非NULL	--	增加字段成功，返回的为增加字段的对象的指针
	// 前置条件：对象类型为STRUCT
	virtual IDataValueObject* AddFieldNull(const DVO_FIELD_NAME FieldName) = 0;

	// 增加一个BOOL类型的字段
	// 返回值：	NULL	--	增加字段失败
	//				非NULL	--	增加字段成功，返回的为增加字段的对象的指针
	// 前置条件：对象类型为STRUCT
	virtual IDataValueObject* AddFieldBool(const DVO_FIELD_NAME FieldName, bool bBool) = 0;

	// 增加一个LONGLONG类型的字段
	// 返回值：	NULL	--	增加字段失败
	//				非NULL	--	增加字段成功，返回的为增加字段的对象的指针
	// 前置条件：对象类型为STRUCT
	virtual IDataValueObject* AddFieldLongLong(const DVO_FIELD_NAME FieldName, long long llLongLong) = 0;

	// 增加一个DOUBLE类型的字段
	// 返回值：	NULL	--	增加字段失败
	//				非NULL	--	增加字段成功，返回的为增加字段的对象的指针
	// 前置条件：对象类型为STRUCT
	virtual IDataValueObject* AddFieldDouble(const DVO_FIELD_NAME FieldName, double dDouble) = 0;

	// 增加一个STRING类型的字段
	// 返回值：	NULL	--	增加字段失败
	//				非NULL	--	增加字段成功，返回的为增加字段的对象的指针
	// 前置条件：对象类型为STRUCT
	virtual IDataValueObject* AddFieldString(const DVO_FIELD_NAME FieldName, const char* szStr) = 0;

	// 增加一个不含任何元素的ARRAY类型的字段
	// 返回值：	NULL	--	增加字段失败
	//				非NULL	--	增加字段成功，返回的为增加字段的对象的指针
	// 前置条件：对象类型为STRUCT
	virtual IDataValueObject* AddFieldArray(const DVO_FIELD_NAME FieldName) = 0;

	// 增加一个不含任何字段的STRUCT类型的字段
	// 返回值：	NULL	--	增加字段失败
	//				非NULL	--	增加字段成功，返回的为增加字段的对象的指针
	// 前置条件：对象类型为STRUCT
	virtual IDataValueObject* AddFieldStruct(const DVO_FIELD_NAME FieldName) = 0;


	// == STRUCT删除操作的接口 ==//

	// 删除字段
	// 前置条件：对象类型为STRUCT且字段名合法(字段名所指的字段存在）
	virtual void DelField(const DVO_FIELD_NAME FieldName) = 0;


	// == STRUCT修改操作(Set操作)的接口 ==//

	// 设置BOOL类型的字段的值
	// 前置条件：对象类型为STRUCT且字段名所指的字段存在且字段类型为BOOL
	virtual bool SetFieldBool(const DVO_FIELD_NAME FieldName, bool bBool) = 0;

	// 设置LONGLONG类型的字段的值
	// 前置条件：对象类型为STRUCT且字段名所指的字段存在且字段类型为LONGLONG
	virtual bool SetFieldLongLong(const DVO_FIELD_NAME FieldName, long long llLongLong) = 0;

	// 设置DOUBLE类型的字段的值
	// 前置条件：对象类型为STRUCT且字段名所指的字段存在且字段类型为DOUBLE
	virtual bool SetFieldDouble(const DVO_FIELD_NAME FieldName, double dDouble) = 0;

	// 设置STRING类型的字段的值
	// 前置条件：对象类型为STRUCT且字段名所指的字段存在且字段类型为STRING
	virtual bool SetFieldString(const DVO_FIELD_NAME FieldName, const char* szStr) = 0;


	// == STRUCT查询操作(Get操作)的接口 ==//

	// = 遍历STRUCT的字段 =//
	/*
		例子：
		IDataValueObject* pStruct;
		unsigned int uFieldNum = pStruct->GetFieldNum();
		for (unsigned int i = 0; i < uFieldNum; i++)
		{
			printf("FieldName:%s\n", pStruct->GetFieldName());
			switch(pStruct->GetFieldType(i))
			{
				case DVO_TYPE_STRING:
					printf("FieldValue:%s\n", pStruct->GetFieldValue(i)->GetString());
				break;
				//...
			}
		}
	*/

	// 判定是否为结构的一个合法的字段名
	// 在操作一个字段之前，需要确定该字段是存在的，特别是当对象已经经过网络传输或者磁盘IO等
	// 前置条件：对象类型为STRUCT
	virtual bool IsValidFieldName(const DVO_FIELD_NAME FieldName) = 0;

	// 判定是否为结构的一个合法的Field(字段名所指的字段存在且类型匹配)
	// 在操作一个字段之前，需要确定该字段是存在的，特别是当对象已经经过网络传输或者磁盘IO等
	// 前置条件：对象类型为STRUCT
	virtual bool IsValidField(const DVO_FIELD_NAME FieldName, int nType) = 0;

	// 获取字段数
	// 前置条件：对象类型为STRUCT
	virtual unsigned int GetFieldNum() = 0;

	// 获取字段类型
	// 前置条件：对象类型为STRUCT且字段索引值合法
	virtual int	GetFieldType(unsigned int uFieldIndex) = 0;
	
	// 获取字段名
	// 前置条件：对象类型为STRUCT且字段索引值合法
	virtual const char* GetFieldName(unsigned int uFieldIndex) = 0;

	// 获取字段值
	// 前置条件：对象类型为STRUCT且字段索引值合法
	virtual IDataValueObject* GetFieldValue(unsigned int uFieldIndex) = 0;

	// 获取字段类型
	// 前置条件：对象类型为STRUCT且字段名合法
	virtual int	GetFieldType(const DVO_FIELD_NAME FieldName) = 0;

	// 获取字段值
	// 前置条件：对象类型为STRUCT且字段名合法
	virtual IDataValueObject* GetFieldValue(const DVO_FIELD_NAME FieldName) = 0;
};


// == DVO二进制数据支持相关 ==//
// DVO不直接支持二进制数据类型，但是可以通过将二进制数据编码成C字符串来间接支持
// IBinaryEncoderDecoder负责二进制数据与字符串之间的编解码

// 根据二进制块长度计算编码后字符串的最大长度（不包括'\0')
// 用于提前预估需要多大的编码缓存
// 例子：
/*
	#define BIN_DATA_MAX_LEN				20
	#define BIN_DATA_ENCODED_MAX_LEN		(BIN_ENCODED_MAX_LEN(BIN_DATA_MAX_LEN))
	char BinEncodeBuffer[BIN_DATA_ENCODED_MAX_LEN + 1];
*/
#define BIN_ENCODED_MAX_LEN(nBinLen)	(((nBinLen) + 2) / 3 * 4)

// 根据字符串长度（不包括'\0'）计算解码后的二进制块的最大长度
// 用于提前预估需要多大的解码缓存
// 例子：
/*
	#define STR_DATA_MAX_LEN				20
	#define STR_DATA_DECODED_MAX_LEN		(STR_DECODED_MAX_LEN(STR_DATA_MAX_LEN))
	char StrDecodeBuffer[STR_DATA_DECODED_MAX_LEN];
*/
#define STR_DECODED_MAX_LEN(nStrLen)	((((nStrLen) + 3) / 4) * 3)


// === DSO相关 ===//

// == DSO的格式 ==//
enum DSO_FORMAT
{
	DSO_FORMAT_JSON = 0,	// JSON文本，目前只支持该形式
};

// === 内存分配器 ===//
struct IDemAllocator
{
	virtual void* Malloc(size_t size)  = 0;
	virtual void  Free(void* memblock) = 0;
};

struct IDem
{
	// == Life Cycle  ==//
	virtual void Release() = 0;

	virtual bool Initialize() = 0;
	virtual void Terminate() = 0;

	// == Dependency Injection ==//
	// 设置依赖的内存分配器
	// DEM默认采用CRT的内存分配器
	// 如果调用了该接口，则DEM使用所设置的内存分配器
	// 该接口请在Initialize之前调用
	virtual void SetAllocator(IDemAllocator* pAllocator) = 0;

	// == Data Access ==//
	// 获取错误信息
	virtual const char*	GetError() = 0;

	// == Manipulation ==//
	
	// 创建一个NULL类型的DVO对象
	// 返回值：	非NULL		--	创建对象成功，返回的是对象指针
	//				NULL		--	创建对象失败
	virtual IDataValueObject* CreateDVO() = 0;

	// 销毁DVO对象
	virtual void DestroyDVO(IDataValueObject* pDvo) = 0;

	// 编码二进制数据块为字符串
	// 输入参数：	pBinData	--	需要编码的二进制数据块指针
	//				nDataLen	--	需要编码的二进制数据块长度
	//				pStrBuf		--	存放编码后字符串的缓存
	//				nBufLen		--	存放编码后字符串的缓存的大小
	// 输出参数：	nCodedLen	--	实际编码后的字符串长度
	// 返回值：	true		--	编码成功
	//				false		--	编码失败，存放编码结果的缓存过小
	virtual bool Code(void* pBinData, int nDataLen, char* pStrBuf, int nBufLen, int& nCodedLen) = 0;

	// 解码字符串为二进制数据库
	// 输入参数：	pStr		--	需要解码的字符串指针
	//				nStrLen		--	字符串长度
	//				pBinBuf		--	存放解码后二进制块的缓存
	//				nBufLen		--	存放解码后二进制块的缓存的大小
	// 输出参数:	nDecodedLen	--	实际解码后的二进制块的长度
	// 返回值：	true		--	解码成功
	//				false		--	解码失败，存放解码后二进制块的缓存的大小过小或者有非法字符
	virtual bool Decode(const char* pStr, int nStrLen, void* pBinBuf, int nBufLen, int& nDecodedLen) = 0;
	// 将DVO转换为DSO
	// 输入参数：	pDvo		--	需要被转换DVO对象的指针
	//				nDsoFormat	--	转换后的DSO的格式，参考DSO_FORMAT
	//				pDsoDataBuf	--	存放转换后的DSO的缓存指针
	//				uDataBufLen	--	存放转换后的DSO的缓存大小
	// 输出参数：	uRealLen	--	转换后的DSO的实际大小
	// 返回值：	true		--	转换成功
	//				false		--	转换失败，调用GetErrorString查看失败原因
	// 例子：
	/*
		IDataObjectConvertor* pConvertor;
		char DsoBuffer[100];
		unsigned int uRealLen;
		if (pConvertor->DVO2DSO(pDvo, DSO_FORMAT_JSON, DsoBuffer, sizeof(DsoBuffer), uRealLen))
		{
			printf("DSO:%s\n", DsoBuffer);
		}
		else
		{
			printf("Failed for %s\n", pConvertor->GetErrorStr());
		}
	*/
	virtual bool DVO2DSO(IDataValueObject* pDvo, int nDsoFormat, char* pDsoDataBuf, unsigned int uDataBufLen, unsigned int& uRealLen) = 0;

	// 将DSO转换为DVO
	// 输入参数：	nDsoFormat	--	DSO的格式，参考DSO_FORMAT
	//				pDsoData	--	DSO数据块指针
	//				uDsoSize	--	DSO数据块大小
	// 输出参数：	pDvo		--	转换后DVO的指针
	// 返回值：	true		--	转换成功
	//				false		--	转换失败
	// 注意：		pDvo所指的对象在Convertor内部创建，使用后需要释放
	// 例子：
	/*
		IDataValueObject* pDvo;
		IDataObjectConvertor* pConvertor;
		char DsoData[] = "{1234}";
		if (pConvertor->DSO2DVO(DDF_JSON, DsoData, (unsigned int)strlen(DsoData), pDvo)
		{
			printf("%d\n", pDvo->GetLongLong());
			pDvo->Release();
		}
		else
		{
			printf("Convert failed for %s\n", pConvertor->GetErrorStr());
		}
	*/
	virtual bool DSO2DVO(int nDsoFormat, const char* pDsoData, unsigned int uDsoSize, IDataValueObject*& pDvo) = 0;

	
};

//=== 外部引用该头文件时，给出接口声明 ===//
#ifndef  DEM_INTERNAL_SIGNATURE 

extern "C" IDem*					DemCreate();
#define FUNC_NAME_DEM_CREATE		"DemCreate"
typedef IDem*						(*FUNC_DEM_CREATE)();

#endif // #ifndef  DEM_INTERNAL_SIGNATURE 

#endif // #ifndef __I_DATA_EXCHANGE_MECHANISM_H__
