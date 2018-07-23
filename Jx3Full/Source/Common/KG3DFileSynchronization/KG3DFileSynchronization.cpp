// KG3DFileSynchronization.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "IKG3DFileSynchronization.h"
#include "KG3DFileSynchronizationCient.h"

KG3DFileSynchronizationCient* g_lpFileSync = NULL;

IKG3DFileSynchronization* CreateFileSync()
{
	if(g_lpFileSync==NULL)
	{
		g_lpFileSync = new KG3DFileSynchronizationCient();
	}

	return g_lpFileSync;
}