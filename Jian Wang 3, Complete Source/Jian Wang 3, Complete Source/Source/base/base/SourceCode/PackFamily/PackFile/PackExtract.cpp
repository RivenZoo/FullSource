#include "PackFile.h"


bool UnpackOperation()
{
	g_nPackIndex = g_PackFileShell->CreatePack(g_StringTable[OPER_EXTRACT_PACKFILE_NAME], true, false);
	if (g_nPackIndex < 0)
	{
		printf("ERROR : Open package [%s] failed!\n", g_StringTable[OPER_EXTRACT_PACKFILE_NAME]);
		return false;
	}

	bool bOk = false;
	if (g_StringTable[OPER_EXTRACT_FILE_TO_EXTRACT][0])
	{
		if (g_PackFileShell->UnpackElem(g_nPackIndex, g_StringTable[OPER_EXTRACT_FILE_TO_EXTRACT], g_StringTable[OPER_EXTRACT_DEST_FILE_NAME]))
		{
			printf("SUCCESS : Unpak file [%s] from package [%s ].\n", g_StringTable[OPER_EXTRACT_FILE_TO_EXTRACT], g_StringTable[OPER_EXTRACT_PACKFILE_NAME]);
			bOk = true;
		}
		else
		{
			printf("ERROR : Unpak file [%s] from package [%s ] failed!\n", g_StringTable[OPER_EXTRACT_FILE_TO_EXTRACT], g_StringTable[OPER_EXTRACT_PACKFILE_NAME]);
		}
	}
	else
	{
		int nUnpackCount = 0;
		if (g_PackFileShell->UnpackAll(g_nPackIndex, nUnpackCount, g_StringTable[OPER_EXTRACT_ELEM_ROOT_PATH]))
		{
			printf("SUCCESS : Unpak %d files from package [%s ].\n", nUnpackCount, g_StringTable[OPER_EXTRACT_PACKFILE_NAME]);
			bOk = true;
		}
		else
		{
			printf("ERROR : Unpak %d files from package [%s ]. failed!\n", nUnpackCount, g_StringTable[OPER_EXTRACT_PACKFILE_NAME]);
		}
	}

	g_PackFileShell->ClosePack(g_nPackIndex);
	g_nPackIndex = -1;
	return bOk;
}
