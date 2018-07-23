/* -------------------------------------------------------------------------
//	文件名		：	kgc/signcode_linklib.h
//	创建者		：	lailigao
//	创建时间	：	2004-10-11 0:11:03
//	功能描述	：	
//
// -----------------------------------------------------------------------*/
#ifndef __KGC_SIGNCODE_LINKLIB_H__
#define __KGC_SIGNCODE_LINKLIB_H__

// -------------------------------------------------------------------------
#define LINKLIB "SignCodeScan.lib"

#if !defined(__Linked_kgcsigncode)
#define __Linked_kgcsigncode
#pragma message("\t程序将自动链接模块 - " LINKLIB)
#pragma linklib(LINKLIB)
#endif

#undef LINKLIB
// -------------------------------------------------------------------------

#endif /* __KGC_SIGNCODE_LINKLIB_H__ */
