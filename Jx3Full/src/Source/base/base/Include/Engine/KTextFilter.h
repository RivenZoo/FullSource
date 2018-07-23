// 文字过滤的通配符版本: Zhao chunfeng, yanrui
// 1. 所有过滤不区分大小写
// 2. 通配符'?'表示匹配0个或1个任意字符
// 3. 通配符'*'表示匹配0个或多个任意字符
// 4. 过滤规则,每条最多32字节(含结尾的'\0')
// 5. 过滤处理的文字,一次最多1024字节(含结尾的'\0')
// 6. 过滤规则式,被过滤的文本,均假设为Ansi编码

#ifndef _KTEXTFILTER_H_
#define _KTEXTFILTER_H_

#include "EngineBase.h"
#include "KSUnknown.h"

struct ITextFilter : IUnknown
{
    virtual BOOL LoadFilterFile(const char cszFilterFile[]) = 0;

    virtual BOOL AddFilterText(const char cszFilterText[]) = 0;

    virtual void ClearAll() = 0;

    // Check 返回值:
    // true  - 字符串是OK的
    // false - 字符串无法识别，或者太长无法处理，或者包含了非法词汇
    virtual BOOL Check(char* pszTextAnsi) = 0;

    // Replace 返回值:
    // true  - 字符串替换成功，或者无需替换
    // false - 字符串无法识别，或者太长无法处理
    virtual BOOL Replace(char* pszTextAnsi) = 0;
};

ENGINE_API ITextFilter* CreateTextFilterInterface();

#endif
