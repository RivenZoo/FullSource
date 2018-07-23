//--------------------------------------------------------------
//	月影传说网络版	DataCube
//	版权所有:			2010 金山软件(Kingsoft)
//	创建日期与作者:	2010-4-28 Golton Gao
//--------------------------------------------------------------
#ifndef __DATA_CUBE_DEF_H__
#define __DATA_CUBE_DEF_H__

#define GNE_TYPE_DATA_CUBE "DataCube"

// === 约束常量定义 ===//
#define DATA_CUBE_TABLE_MAX_NUM			20	// 一次请求最多同时操作20张表
#define DATA_CUBE_TABLE_NAME_MAX_LEN	20	// DataCube表格名最大长度为20字节
#define DATA_CUBE_TABLE_FIELD_MAX_NUM	50	// DataCube表格最多有50个字段
#define DATA_CUBE_TABLE_FILTER_MAX_NUM	50	// DataCube表格最多有50个过滤条件
#define DATA_CUBE_TABLE_RECORD_MAX_NUM  50	

typedef char DATA_CUBE_TABLE_NAME[DATA_CUBE_TABLE_NAME_MAX_LEN + 1];

// === 分表模式 ===//
enum DATA_CUBE_TABLE_DIVIDE_MODE
{
	DATA_CUBE_TABLE_DIVIDE_MODE_NONE		= 0,	// 不分表
	DATA_CUBE_TABLE_DIVIDE_MODE_BY_MONTH,			// 按月分表
};

static inline bool IS_VALID_DATA_CUBE_TABLE_DIVIDE_MODE(int DivideMode)
{
	return DivideMode >= DATA_CUBE_TABLE_DIVIDE_MODE_NONE && DivideMode <= DATA_CUBE_TABLE_DIVIDE_MODE_BY_MONTH;
}

#define DATA_CUBE_KEY_TABLE_NAME			"TableName"
#define DATA_CUBE_KEY_WRITE_IF_NOT_EXIST	"WriteIfNotExist"
#define DATA_CUBE_KEY_DIVIDE_MODE			"DivideMode"
#define DATA_CUBE_KEY_FIELD_ARRAY			"FieldArray"
#define DATA_CUBE_KEY_FILTER_ARRAY			"FilterArray"
#define DATA_CUBE_KEY_TABLE_OFFSET			"TableOffset"
#define DATA_CUBE_KEY_START_OFFSET			"StartOffset"
#define DATA_CUBE_KEY_EXPECT_NUM			"ExpectNum"
#define DATA_CUBE_KEY_HAS_MORE				"HasMore"
#define DATA_CUBE_KEY_FIELD_NAME			"FieldName"
#define DATA_CUBE_KEY_GNE_PATH				"GnePath"
#define DATA_CUBE_KEY_DATA_TYPE				"DataType"
#define DATA_CUBE_KEY_FIELD_VALUE			"FieldValue"
#define DATA_CUBE_KEY_UPDATE_MODE			"UpdateMode"
#define DATA_CUBE_KEY_AFFECTED_ROWS			"AffectedRows"
#define DATA_CUBE_KEY_FILTER_OPERATOR		"FilterOperator"
#define DATA_CUBE_KEY_FILTER_CONJUNCTION	"FilterConjunction"
#define DATA_CUBE_KEY_RECORD_ARRAY			"RecordArray"
#define DATA_CUBE_KEY_MAX_SIZE				"MaxSize"
#define DATA_CUBE_KEY_FIELD_FLAG			"FieldFlag"
#define DATA_CUBE_KEY_HAS_READ_PRIVILEGE	"HasReadPrivilege"
#define DATA_CUBE_KEY_HAS_WRITE_PRIVILEGE	"HasWritePrivilege"
#define DATA_CUBE_KEY_HAS_MODIFY_PRIVILEGE	"HasModifyPrivilege"
#define DATA_CUBE_KEY_READ_MODE				"ReadMode"
#define DATA_CUBE_KEY_FORBID_INC			"ForbidInc"
#define DATA_CUBE_KEY_FORBID_DEC			"ForbidDec"
#define DATA_CUBE_KEY_LIMIT_MAX				"LimitMax"
#define DATA_CUBE_KEY_LIMIT_MIN				"LimitMin"
#define DATA_CUBE_KEY_MAX_VALUE				"MaxValue"
#define DATA_CUBE_KEY_MIN_VALUE				"MinValue"

#define DATA_CUBE_KEY_RES_PATH				"ResPath"
#define DATA_CUBE_KEY_LOAD_DATA				"LoadData"

// == DataCube资源路径（DataCube所提供的服务）==//
#define DATA_CUBE_RES_PATH_ADD_TABLE			"AddTable"
#define DATA_CUBE_RES_PATH_DEL_TABLE			"DelTable"

#define DATA_CUBE_RES_PATH_ADD_FIELD			"AddField"
#define DATA_CUBE_RES_PATH_DEL_FIELD			"DelField"

#define DATA_CUBE_RES_PATH_ADD_PRIVILEGE		"AddPrivilege"
#define DATA_CUBE_RES_PATH_DEL_PRIVILEGE		"DelPrivilege"
#define DATA_CUBE_RES_PATH_GET_PRIVILEGE		"GetPrivilege"

#define DATA_CUBE_RES_PATH_READ_TABLE			"ReadTable"
#define DATA_CUBE_RES_PATH_WRITE_TABLE			"WriteTable"
#define DATA_CUBE_RES_PATH_MODIFY_TABLE			"ModifyTable"

#endif // #ifndef __DATA_CUBE_DEF_H__
