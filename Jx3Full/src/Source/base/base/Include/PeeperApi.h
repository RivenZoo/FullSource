/*****************************************************************************************
                    ┏━━━━━━━━━━━━━━━━━━━━━━━━━┓
                    ┃　　　　　　　Ｐｅｅｐｅｒ　ＡＰＩ　　　　　　　　┃
                    ┗━━━━━━━━━━━━━━━━━━━━━━━━━┛
Copyright : Kingsoft 2001-2002
Author	:   Wooy(Wu yue)
CreateTime:	2001-11-9
------------------------------------------------------------------------------------------
	(基于Peeper作插件开发，包含此头文件)
*****************************************************************************************/
#ifndef __PEEPER_API_H__
#define __PEEPER_API_H__


//字符串缓冲区长度定义
#define	STRING_MINI		32
#define	STRING_SHORT	80
#define	STRING_NORMAL	128
#define	STRING_LONG		256

#include "peeper/PeeperCommData.h"		//定义了Peeper常用数据结构等，如资源类型、对资源的操作
#include "peeper/PeeperCommInterface.h"	//定义了Peeper常用接口
#include "peeper/PeeperShell.h"			//定义了外部访问Peepr的接口。
#include "peeper/FPluginShell.h"		//定义了Peeper功能模块插件的规范。

#endif //__PEEPER_API_H__
