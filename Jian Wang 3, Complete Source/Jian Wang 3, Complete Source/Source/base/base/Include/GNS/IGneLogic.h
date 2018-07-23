//---------------------------------------------------------------------------
// 月影传说网络版     GneLauncher(GL)
// 版权所有           2010 金山软件(Kingsoft)
// 创建日期与作者     2010-7-29 Golton Gao
//---------------------------------------------------------------------------
#ifndef __I_GNE_LOGIC_H__
#define __I_GNE_LOGIC_H__
/*---------------------------------------------------------------------------
   [说明]: GneLogic所应该实现的接口
---------------------------------------------------------------------------*/

// === 监控流 ===//
struct IGneMonitorStream
{
	// == 向监控流中写入错误信息 ==//
	virtual void		WriteError(const char* pFormat, ...) = 0;

	// == 向监控流中写入常规信息 ==//
	virtual void		WriteInfo(const char* pFormat, ...) = 0;
	
	// == 向监控流中写入调试信息 ==//
	virtual void		WriteDebug(const char* pFormat, ...) = 0;
};

// === 命令流 ===//
struct IGneCommandStream
{
	// === 向命令流中写入命令执行结果 ===//
	virtual void		Write(const char* pFormat, ...) = 0;
};

struct IGneLogic
{
	// == Life Cycle ==//
	virtual void		Release() = 0;
	virtual bool		Initialize() = 0;
	virtual void		Terminate() = 0;

	// == Dependency Injection ==//
	virtual void		SetMonitorStream(IGneMonitorStream* pMonitorStream) = 0;
	virtual void		SetCommandStream(IGneCommandStream* pCommandStream) = 0;

	// == Schedule ==//
	virtual void		Tick() = 0;

	// == Data Access ==//
	virtual const char* GetVersion() = 0;
	virtual const char* GetStatus() = 0;

	// == Manipulation ==//
	virtual void		ExecCommand(const char* szCommand) = 0;
};

// == GneLogic的对外接口 ==//

// == 在GNE_LOGIC工程内部 ==//
// (1)预定义GNE_LOGIC_INTER_FLAG宏
// (2)实现GneLogicCreate()接口

#ifndef GNE_LOGIC_INTER_FLAG

extern "C" IGneLogic* GneLogicCreate();
#define FUNC_NAME_GNE_LOGIC_CREATE "GneLogicCreate"
typedef IGneLogic* (*FUNC_GNE_LOGIC_CREATE)();

#endif // #ifndef GNE_LOGIC_INTER_FLAG

#endif // #ifndef __I_GNE_APP_H__
