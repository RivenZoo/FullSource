//--------------------------------------------------------------
//	月影传说网络版	DatabaseEngine
//	版权所有:			2010 金山软件(Kingsoft)
//	创建日期与作者:	2010-4-28 Golton Gao
//--------------------------------------------------------------
#ifndef __DATABASE_ENGINE_DEF_H__
#define __DATABASE_ENGINE_DEF_H__

#include <assert.h>
#include <string.h>

#define FIELD_DATA_TYPE_STRING_MAX_LEN	1024		// 字符串最大长度为1KB
#define FIELD_DATA_TYPE_BLOB_MAX_LEN	65536		// 二进制块最大长度为64KB

#define TABLE_NAME_MAX_LEN			30				// 表名的最大长度
#define FIELD_NAME_MAX_LEN			30				// 字段名最大长度为30字节

#define TABLE_FIELD_MAX_NUM			100				// 一张表的最大字段数为1000
#define TABLE_RECORD_MAX_NUM		100				// 一次最多读100条记录
#define TABLE_FILTER_MAX_NUM		100				// 一个表格中最多设置100个过滤条件

typedef char TABLE_NAME[TABLE_NAME_MAX_LEN + 1];	// 表名
typedef char FIELD_NAME[FIELD_NAME_MAX_LEN + 1];	// 字段名

// === 数据类型定义 ===//
enum FIELD_DATA_TYPE
{
	FIELD_DATA_TYPE_CHAR = 0,
	FIELD_DATA_TYPE_SHORT,
	FIELD_DATA_TYPE_INT,
	FIELD_DATA_TYPE_LONGLONG,
	FIELD_DATA_TYPE_FLOAT,
	FIELD_DATA_TYPE_DOUBLE,
	FIELD_DATA_TYPE_STRING,
	FIELD_DATA_TYPE_BLOB
};

static inline bool IS_VALID_FIELD_DATA_TYPE(int DataType)
{
	return DataType >= FIELD_DATA_TYPE_CHAR && DataType <= FIELD_DATA_TYPE_BLOB;
}

static inline bool IS_LEN_FIXED_FIELD_DATA_TYPE(int DataType)
{
	assert(IS_VALID_FIELD_DATA_TYPE(DataType));
	return !(DataType == FIELD_DATA_TYPE_STRING || DataType == FIELD_DATA_TYPE_BLOB);
}

static inline bool IS_VALID_FIELD_DATA_TYPE_LEN(int DataType, unsigned int uLen)
{
	switch(DataType)
	{
	case FIELD_DATA_TYPE_CHAR:
	case FIELD_DATA_TYPE_SHORT:
	case FIELD_DATA_TYPE_INT:
	case FIELD_DATA_TYPE_LONGLONG:
	case FIELD_DATA_TYPE_FLOAT:
	case FIELD_DATA_TYPE_DOUBLE:
		return uLen == 0;
	case FIELD_DATA_TYPE_STRING:
		return uLen <= FIELD_DATA_TYPE_STRING_MAX_LEN;
	case FIELD_DATA_TYPE_BLOB:
		return uLen <= FIELD_DATA_TYPE_BLOB_MAX_LEN;
	default:
		assert(0 && "Invalid FieldDataType!");
		return false;
	}
}

// === 字段更新模式 ===//
enum FIELD_UPDATE_MODE
{
	FIELD_UPDATE_MODE_OVERWRITE = 0,	// 更新模式为覆盖，即新值为当前值
	FIELD_UPDATE_MODE_INC,				// 更新模式为增加，即新值为旧值加上当前值，减小可以通过加上负值实现
};

static inline bool IS_VALID_FIELD_UPDATE_MODE(int FieldUpdateMode)
{
	return FieldUpdateMode >= FIELD_UPDATE_MODE_OVERWRITE && FieldUpdateMode <= FIELD_UPDATE_MODE_INC;
}

// === 字段标识 ===//
enum FIELD_FLAG
{
	FIELD_FLAG_NORMAL						= 0x00,	// normal field
	FIELD_FLAG_NOT_NULL						= 0x01,	// not null
	FIELD_FLAG_PRIMARY_KEY					= 0X02,	// primary key
	FIELD_FLAG_UNIQUE						= 0X04,	// unique
	FIELD_FLAG_AUTO_INCREMENT				= 0x08,	// auto_increment
};

// === 字段类型信息===//
struct FIELD_TYPE
{
	FIELD_NAME		FieldName;							// 字段名
	char			DataType;							// 字段数据类型

	unsigned int	MaxSize;							// 字段最大长度
	int				FieldFlag;							// 字段标志（是否有特定属性)，只在创建表的时候用到
	char			UpdateMode;							// 更新模式（覆盖或者增加)，只在更新表的时候用到
};

// === 字段值信息 ===//
struct FIELD_VALUE
{
	unsigned int		uValueSize;	// 数据长度, 0表示NULL, 非0表示非NULL
	union
	{
		// == 指向任何数据类型的指针 ==//
		void*			pValue;

		// == 指向具体数据类型的指针 ==//
		char*			pCharValue;
		short*			pShortValue;
		int*			pIntValue;
		long long*		pLongLongValue;
		float*			pFloatValue;
		double*			pDoubleValue;
	};
};

// === 过滤条件操作符 ===//
enum FILTER_OPERATOR
{
	FILTER_OPERATOR_LESS = 0,		//  <
	FILTER_OPERATOR_LESS_EQUAL,		//  <=
	FILTER_OPERATOR_EQUAL,			//  = 
	FILTER_OPERATOR_NOT_EQUAL,		//  != 
	FILTER_OPERATOR_ABOVE,			//  > 
	FILTER_OPERATOR_ABOVE_EQUAL,	//  >= 
	FILTER_OPERATOR_LIKE,			//  like 
	FILTER_OPERATOR_INVERTED_LIKE,
};

static inline bool IS_VALID_FILTER_OPERATOR(int FilterOperator)
{
	return (FilterOperator >= FILTER_OPERATOR_LESS && FilterOperator <= FILTER_OPERATOR_INVERTED_LIKE);
}

// === 过滤条件连接词 ===//
enum FILTER_CONJUNCTION
{
	FILTER_CONJUNCTION_AND = 0,		// and
	FILTER_CONJUNCTION_OR,			// or
};

static inline bool IS_VALID_FILTER_CONJUNCTION(int FilterConjunction)
{
	return (FilterConjunction == FILTER_CONJUNCTION_AND) || (FilterConjunction == FILTER_CONJUNCTION_OR);
}

//=== 字段过滤条件 ===//
struct FIELD_FILTER : public FIELD_TYPE, public FIELD_VALUE
{
	FILTER_OPERATOR		FilterOperator;
	FILTER_CONJUNCTION	FilterConjunction;
};

static inline void SET_FIELD_TYPE_ADD(FIELD_TYPE& FieldType, const FIELD_NAME FieldName, int DataType, unsigned int MaxSize = 0, int FieldFlag = FIELD_FLAG_NORMAL)
{
	assert(FieldName && FieldName[0] != '\0' && strlen(FieldName) <= FIELD_NAME_MAX_LEN);
	assert(IS_VALID_FIELD_DATA_TYPE(DataType));
	assert( (DataType == FIELD_DATA_TYPE_STRING && MaxSize <= FIELD_DATA_TYPE_STRING_MAX_LEN ) || 
			(DataType == FIELD_DATA_TYPE_BLOB && MaxSize <= FIELD_DATA_TYPE_BLOB_MAX_LEN) ||
			(DataType != FIELD_DATA_TYPE_STRING && DataType != FIELD_DATA_TYPE_BLOB && MaxSize == 0));
	strcpy(FieldType.FieldName, FieldName);
	FieldType.DataType	= DataType;
	FieldType.MaxSize	= MaxSize;
	FieldType.FieldFlag = FieldFlag;
}

static inline void SET_FIELD_TYPE_DEL(FIELD_TYPE& FieldType, const FIELD_NAME FieldName)
{
	assert(FieldName && FieldName[0] != '\0' && strlen(FieldName) <= FIELD_NAME_MAX_LEN);
	strcpy(FieldType.FieldName, FieldName);
}

static inline void SET_FIELD_TYPE_INSERT(FIELD_TYPE& FieldType, const FIELD_NAME FieldName, int DataType)
{
	assert(FieldName && FieldName[0] != '\0' && strlen(FieldName) <= FIELD_NAME_MAX_LEN);
	assert(IS_VALID_FIELD_DATA_TYPE(DataType));
	strcpy(FieldType.FieldName, FieldName);
	FieldType.DataType = (FIELD_DATA_TYPE)DataType;
}

static inline void SET_FIELD_TYPE_SELECT(FIELD_TYPE& FieldType, const FIELD_NAME FieldName)
{
	assert(FieldName && FieldName[0] != '\0' && strlen(FieldName) <= FIELD_NAME_MAX_LEN);
	strcpy(FieldType.FieldName, FieldName);
}

static inline void SET_FIELD_TYPE_UPDATE(FIELD_TYPE& FieldType, const FIELD_NAME FieldName, int DataType, int UpdateMode)
{
	assert(FieldName && FieldName[0] != '\0' && strlen(FieldName) <= FIELD_NAME_MAX_LEN);
	assert(IS_VALID_FIELD_DATA_TYPE(DataType));
	assert(IS_VALID_FIELD_UPDATE_MODE(UpdateMode));
	strcpy(FieldType.FieldName, FieldName);
	FieldType.DataType		= (FIELD_DATA_TYPE)DataType;
	FieldType.UpdateMode	= (FIELD_UPDATE_MODE)UpdateMode;
}

static inline void SET_FIELD_VALUE(FIELD_VALUE& FieldValue, void* pValue, unsigned int uValueSize)
{
	assert(uValueSize == 0 || (uValueSize > 0 && pValue));
	FieldValue.pValue = pValue;
	FieldValue.uValueSize = uValueSize;
}

static inline void SET_FIELD_FILTER(FIELD_FILTER& FieldFilter, const FIELD_NAME FieldName, int DataType, void* pValue, 
									unsigned int uValueSize, int FilterOperator, int FilterConjunction)
{
	assert(FieldName && FieldName[0] != '\0' && strlen(FieldName) <= FIELD_NAME_MAX_LEN);
	assert(IS_VALID_FIELD_DATA_TYPE(DataType));
	assert(uValueSize == 0 || (uValueSize > 0 && pValue));
	assert(IS_VALID_FILTER_OPERATOR(FilterOperator));
	assert(IS_VALID_FILTER_CONJUNCTION(FilterConjunction));

	strcpy(FieldFilter.FieldName, FieldName);
	FieldFilter.DataType = DataType;
	FieldFilter.pValue = pValue;
	FieldFilter.uValueSize = uValueSize;
	FieldFilter.FilterOperator = (FILTER_OPERATOR)FilterOperator;
	FieldFilter.FilterConjunction = (FILTER_CONJUNCTION)FilterConjunction;
}

#endif // #ifndef __DATABASE_ENGINE_DEF_H__
