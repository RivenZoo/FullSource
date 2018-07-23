/********************************************************************
	created:	2003/05/02
	file base:	Console
	file ext:	h
	author:		liupeng
	
	purpose:	
*********************************************************************/
#ifndef __INCLUDE_CONSOLE_H__
#define __INCLUDE_CONSOLE_H__

#ifdef _WIN32

#if defined (_MSC_VER) && (_MSC_VER >= 1020)
	#pragma once
#endif

#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>

enum enumConsoleColor
{
	enumWhiteonBlack,
	enumRedonBlack,
	enumGreenonBlack,
	enumYellowonBlack,
	enumBlueonBlack,
	enumMagentaonBlack,
	enumCyanonBlack,
	enumBlackonGray,
	enumBlackonWhite,
	enumRedonWhite,
	enumGreenonWhite,
	enumYellowonWhite,
	enumBlueonWhite,
	enumMagentaonWhite,
	enumCyanonWhite,
	enumWhiteonWhite,

	enumDefault

};

/*
 * namespace OnlineGameLib::Win32::Console
 */

namespace OnlineGameLib {
	namespace Win32 {
		namespace Console {

		void clrscr();
		void gotoxy( int x, int y );
		void getxy( int &x, int &y );
		void setcolor( int color );

		} // End of namespace Console
	} // End of namespace Win32
} // End of namespace OnlineGameLib

#endif

#endif // __INCLUDE_CONSOLE_H__

