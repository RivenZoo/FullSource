//---------------------------------------------------------------------------
// Sword3 Engine (c) 1999-2000 by Kingsoft
//
// File:	KDebug.h
// Date:	2000.08.08
// Code:	WangWei(Daphnis)
// Desc:	Header File
//---------------------------------------------------------------------------
#ifndef _ENGINE_DEBUG_H_
#define _ENGINE_DEBUG_H_

C_ENGINE_API void g_DebugLog(const char* Fmt, ...);
C_ENGINE_API void g_MessageBox(const char* lpMsg, ...);
C_ENGINE_API void g_AssertFailed(const char* FileName, int LineNum);

#ifdef _DEBUG
	#define KASSERT(x)	if (!(x)) g_AssertFailed(__FILE__, __LINE__)
#else
	#define KASSERT(x)	0
#endif

#ifndef _ASSERT
	#define _ASSERT(f)	KASSERT(f)
#endif


/*class ENGINE_API KSG_LogFile
{
public:
    KSG_LogFile(const char cszFileName[]);
    virtual ~KSG_LogFile();

    KSG_LogFile();

    int Init(const char cszFileName[]);

    
    
    void printf(const char* pcszFmt, ...);
    void puts(const char* pcszString);
private:
    FILE *m_fpFile;
};*/

#endif //_ENGINE_DEBUG_H_
