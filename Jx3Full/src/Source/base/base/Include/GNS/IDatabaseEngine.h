//--------------------------------------------------------------
// 月影传说网络版  DatabaseEngine
// 版权所有:        2010 金山软件(Kingsoft)
// 创建日期与作者: 2010-4-28 Golton Gao
//--------------------------------------------------------------
#ifndef __I_DATABASE_ENGINE_H__
#define __I_DATABASE_ENGINE_H__

struct IDatabaseEngine;
struct IStatement;
struct IResultSet;

// 数据库引擎配置信息
struct DATABASE_ENGINE_CONFIG
{
	char	DbIP[16];								// 数据库IP
	int		DbPort;									// 数据库端口
	char	DbName[31];								// 数据库名
	char	DbUser[21];								// 数据库用户名
	char	DbPwd[21];								// 数据库密码
};

struct IDatabaseEngine
{
	// 销毁接口对象
	virtual void Release() = 0;

	// 初始化数据库引擎（连接数据库）
	virtual bool Initialize(const DATABASE_ENGINE_CONFIG& Config) = 0;

	// 反初始化数据库引擎（断开数据库）
	virtual void Terminate() = 0;

	// === DDL操作接口 ===//
	// 增加表格
	virtual bool AddTable(
		const TABLE_NAME	TableName,				// 表名
		const FIELD_TYPE	FieldType[],			// 表格字段类型信息
		unsigned int		uFieldNum,				// 表格字段数量
		bool				bIfNotExists = false	// 是否只在表格不存在时创建
		) = 0;

	// 删除表格
	virtual bool DelTable(
		const TABLE_NAME	TableName				// 表名
		) = 0;
	
	// 增加字段
	virtual bool AddField(
		const TABLE_NAME	TableName,				// 表名
		const FIELD_TYPE	FieldType[],			// 字段类型信息
		unsigned int		uFieldNum				// 字段数量
		) = 0;
	
	// 增加字段
	virtual bool DelField(
		const TABLE_NAME	TableName,				// 表名
		const FIELD_TYPE	FieldType[],			// 字段类型信息
		unsigned int		uFieldNum				// 字段数量
		) = 0;

	// === DML操作接口在IStatement中提供 ===//
	virtual IStatement*	CreateStatement() = 0;	// 创建Statememt

	// 获取错误消息
	virtual const char* GetErrorStr() = 0;

	// 获取错误码
	virtual unsigned int GetErrorCode() = 0;
};

struct IStatement
{
	// 销毁接口对象
	virtual void Release() = 0;

	// 准备Insert操作
	virtual bool PrepareInsert(
		const TABLE_NAME	TableName,			// 表名
		const FIELD_TYPE	FieldType[],		// 需要插入的字段的类型信息
		unsigned int		uFieldNum			// 需要插入的字段数量
		) = 0;

	// 准备Select操作
	virtual bool PrepareSelect(
		const TABLE_NAME	TableName,			// 表名
		const FIELD_TYPE	FieldType[],		// 需要选择的字段的类型信息 
		unsigned int		uFieldNum,			// 需要选择的字段数量
		const FIELD_FILTER	FieldFilter[],		// 字段值过滤条件
		unsigned int		uFilterNum,			// 字段值过滤条件数
		unsigned int		uOffset,			// 起始偏移量
		int					nExpectNum			// 选择的记录条数
		) = 0;

	// 准备Update操作
	virtual bool PrepareUpdate(
		const char*			TableName,			// 表格名
		const FIELD_TYPE	FieldType[],		// 需要更新的目标字段的类型信息
		unsigned int		uFieldNum,			// 需要更新的字段的数量
		const FIELD_FILTER	FieldFilter[],		// 字段值过滤条件
		unsigned int		uFilterNum			// 字段值过滤条件数
		) = 0;

	// 准备Delete操作
	virtual bool PrepareDelete(
		const TABLE_NAME	TableName,			// 表名
		const FIELD_FILTER	FieldFilter[],		// 字段值过滤条件
		unsigned int		uFilterNum			// 字段值过滤条件数
		) = 0;

	// 绑定FieldValue参数
	virtual bool BindFieldPara(
		const FIELD_TYPE	FieldType[],		// 字段类型信息
		const FIELD_VALUE	FieldValue[],		// 字段值
		unsigned int		uFieldNum			// 字段数量
		) = 0;

	// 绑定FieldFilter参数
	virtual bool BindFilterPara(
		const FIELD_FILTER	FieldFilter[],		// 字段值过滤条件
		unsigned int		uFilterNum			// 字段值过滤条件数
		) = 0;

	// 绑定FieldValue和FieldFilter参数
	virtual bool BindFieldAndFilterPara(
		const FIELD_TYPE	FieldType[],		// 字段类型信息		
		const FIELD_VALUE	FieldValue[],		// 字段值
		unsigned int		uFieldNum,			// 字段数量
		const FIELD_FILTER	FieldFilter[],		// 字段值过滤条件
		unsigned int		uFilterNum			// 字段值过滤条件数
		) = 0;

	// 执行
	virtual bool Execute() = 0;

	// 提交
	virtual bool Commit() = 0;

	// 回滚
	virtual bool Rollback() = 0;

	// 获取DQL操作(SELECT)的结果集
	// 返回值：NULL	-- 获取失败
	//			非NULL	-- 获取成功，返回结果集的指针
	// 注意：使用完结果集后务必释放之
	virtual IResultSet* GetResultSet() = 0;

	// 获取DML操作(INSERT, UPDATE, DELETE)所影响的记录数
	// 返回值：-1	-- 获取失败
	//			>=0	-- 获取成功，返回操作所影响的记录数
	virtual int	GetAffectedRows() = 0;

	// 获取错误消息
	virtual const char* GetErrorStr() = 0;

	// 获取错误码
	virtual unsigned int GetErrorCode() = 0;
};

struct IResultSet
{
	// 销毁接口对象
	virtual void Release() = 0;

	// 读取下一条记录
	// 返回值：true	-- 读取下一条记录成功
	//			false	-- 读取下一条记录失败或者不存在下一条记录
	virtual bool Next() = 0;

	// 获取记录的字段数量
	virtual unsigned int GetFieldCount() = 0;

	// 获取当前记录的字段类型
	// 返回值：字段类型，参见FIELD_DATA_TYPE
	virtual int GetFieldType(
		unsigned int	uColumnIndex	// 列序号，从0开始
		) = 0;

	// 判断当前记录的字段是否为NULL值
	virtual bool IsNull(
		unsigned int uColumnIndex		// 序列号，从0开始
		)= 0;

	// 获取当前记录的字段值
	// 返回值：true	-- 获取字段值成功
	//			false	-- 获取字段值失败，缓存过小
	virtual bool GetFieldValue(
		unsigned int	uColumnIndex,	// 列序号，从0开始 
		void*			pValueBuffer,	// 值缓存
		unsigned int	uBufferLen,		// 缓存长度
		unsigned int&	uRealLen		// 输出参数，实际值占有缓存长度
		) = 0;

	// 获取错误消息
	virtual const char* GetErrorStr() = 0;

	// 获取错误码
	virtual unsigned int GetErrorCode() = 0;
};

//=== 外部引用该头文件时，给出接口声明 ===//
#ifndef  DATABASE_ENGINE_INTERNAL_SIGNATURE 

extern "C" IDatabaseEngine* DatabaseEngineCreate();
#define FUNC_NAME_DATABASE_ENGINE_CREATE "DatabaseEngineCreate"
typedef IDatabaseEngine* (*FUNC_DATABASE_ENGINE_CREATE)();

#endif // #ifndef  DATABASE_ENGINE_INTERNAL_SIGNATURE 

#endif // #ifndef __DATABASE_ENGINE_H__
