//---------------------------------------------------------------------------
// Sword3 Engine (c) 1999-2004 by Kingsoft
// Date:	2000.08.08
// Code:	WangWei(Daphnis)
// Desc:	Header File
//---------------------------------------------------------------------------
#ifndef _ENGINE_RANDOM_H_
#define _ENGINE_RANDOM_H_

C_ENGINE_API unsigned int	g_Random(unsigned int nMax);
C_ENGINE_API void			g_RandomSeed(unsigned int nSeed);
C_ENGINE_API unsigned int	g_GetRandomSeed();

#endif	//_ENGINE_RANDOM_H_

