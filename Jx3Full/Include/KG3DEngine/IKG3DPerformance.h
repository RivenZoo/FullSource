/*!
 * \file IKG3DPerformance.h
 * \date 2014/07/14 10:05
 * \author Gu Lu (gulu@kingsoft.com)
 *
 * \brief Definition of IKG3DPerformance 
*/

#pragma once

#include <tchar.h>


/* ----- 容器相关的操作 ----- */
// 判断是否在容器中（O(n)）
template <typename ELEM, typename CONT> bool KPerfIsInContainer(ELEM e, CONT c);


/* ----- 颜色相关的操作 ----- */
/*
    快速定义和使用标准颜色 

    这个宏能自动把变量名与颜色值(Color Value)和颜色名(Color Name)挂钩，
    提高了使用颜色的代码的可读性。

    用法：
    KG_COLOR(White)         返回白色的值:     0xffffffff
    KG_COLOR_NAME(White)    返回白色的颜色名:  _T("White")
*/

// 尽量仅在本头文件内集中定义
#define KG_DEFINE_COLOR(c, v) \
    const int               KG_COLOR_##c = v; \
    const TCHAR* const      KG_COLOR_NAME_##c = _T(#c);
// 取颜色值
#define KG_COLOR(c)         KG_COLOR_##c  
// 取颜色名字符串
#define KG_COLOR_NAME(c)    KG_COLOR_NAME_##c  

/* ----- 常用颜色定义 ----- */
KG_DEFINE_COLOR(Black,          0xff000000);
KG_DEFINE_COLOR(White,          0xffffffff);
KG_DEFINE_COLOR(Red,            0xffff0000);
KG_DEFINE_COLOR(Green,          0xff00ff00);
KG_DEFINE_COLOR(Blue,           0xff0000ff);
KG_DEFINE_COLOR(Yellow,         0xffffff00);
KG_DEFINE_COLOR(BrightYellow,   0xffffffc0);
KG_DEFINE_COLOR(Purple,         0xffff00ff);
KG_DEFINE_COLOR(Indigo,         0xff00ffff);
KG_DEFINE_COLOR(Gray,           0xff808080);
KG_DEFINE_COLOR(TransWhite,     0x80ffffff);
KG_DEFINE_COLOR(TransGray,      0x80404040);
KG_DEFINE_COLOR(MoreTransGray,  0x40202020);
KG_DEFINE_COLOR(LessTransGray,  0xc0202020);


/* ----- Math - 迷你数学库 ----- */
const float KPERF_Epsilon = 0.00001f;
template <typename T> T KPerfEqual(T v1, T v2);
template <typename T> T KPerfClamp(T val, T minV, T maxV);
template <typename T> T KPerfLerp(T val, T minV, T maxV);


/* ----- 性能等级定义 ----- */
enum ePerfLevel
{
    PLV_None,
    PLV_Smooth,        // average ~ 60
    PLV_Tolerable,     // 30-60
    PLV_Critical,      // less than 30
    PLV_Num,        
};

const char* const g_perfLevelInfo[] = 
{
    "None",
    "Smooth",
    "Tolerable",
    "Critical",
};

/* ----- 独立优化选项（可单独开关） ----- */
enum ePerfOptFeatrues
{
    POF_None            = 0,
    POF_FilterPlayers   = 1,
    POF_FilterEntities  = 1 << 1,
    POF_PostCull        = 1 << 2,
    POF_All             = 0xffffffff,
};

enum ePerfStatsType
{
    PST_TotalCount,
    PST_CulledCount,
    PST_AffectedCount,
    PST_Num,
};

/*
 *	接口类 - 性能事件处理对象 （其他的子系统可以通过继承自这个类，响应性能事件）
 */
interface IPerfEventHandler
{
    // 主要性能事件
    virtual void OnPerfLevelChanged(ePerfLevel newLevel, ePerfLevel oldLevel) = 0;
    virtual void OnPerfLevelWarning(ePerfLevel newLevel, double fTime) = 0;

    // 次要接口（可选）
    virtual void Refresh(double fTime, const D3DXVECTOR3& vPlayerPos) {}
    virtual std::map<ePerfStatsType, DWORD> GetStats() { return std::map<ePerfStatsType, DWORD>(); }   
};

interface IPerfEventHandlerSet
{
    virtual void Register(IPerfEventHandler* peh) = 0;
    virtual IPerfEventHandler* GetPlayerHandler() = 0;
};

interface IKG3DPerformanceTweaker
{
    virtual unsigned int GetEngineFPS() = 0;
    virtual void RenderDebugInfo() = 0;

    virtual void SetEnable(bool bEnable) = 0;
    virtual bool IsEnabled() = 0;

    virtual void ExecuteCommand(const char* szCommnd) = 0;
    virtual void RegisterHandlerSet(IPerfEventHandlerSet* handerSet) = 0;

    virtual bool IsOptFeatureEnabled(ePerfOptFeatrues pof) = 0;
	virtual void PrintLaptopTag() = 0;

    virtual void SetAllPlayersVisible(bool visible) = 0;
};


//-----------------------------------------------------------------------------
/* ----- 以下为实现细节 ----- */

template <typename ELEM, typename CONT>
bool KPerfIsInContainer(ELEM e, CONT c) 
{
    return std::find(c.begin(), c.end(), e) != c.end(); 
}

template <typename T> T KPerfEqual(T v1, T v2)
{ 
    return abs(v1 - v2) < (T)(KPERF_Epsilon); 
}
template <typename T> T KPerfClamp(T val, T minV, T maxV) 
{ 
    if (minV > maxV)
    {
        return KPerfClamp(val, maxV, minV);
    }
    else
    {
        return val < minV ? minV : (val > maxV ? maxV : val); 
    }
}
template <typename T> T KPerfLerp(T val, T minV, T maxV)
{
    if (minV > maxV)
    {
        return KPerfLerp(val, maxV, minV);
    } 
    else if (KPerfEqual(maxV, minV))
    {
        return (val >= minV) ? 1.0f : 0.0f;
    } 
    else
    {
        return (KPerfClamp(val, minV, maxV) - minV) / (maxV - minV); 
    }
}
