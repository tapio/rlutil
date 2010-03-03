/**
 * File: rlutil.h
 *
 * About: Description
 * This file provides some useful utilities for console mode
 * roguelike game development with C and C++. It is aimed to
 * be cross-platform (at least Windows and Linux).
 *
 * About: Copyright
 * (C) 2010 Tapio Vierros
 *
 * About: Licensing
 * See <License>
 */


/// Define: RLUTIL_USE_ANSI
/// Define this to use ANSI escape sequences also on Windows
/// (defaults to using WinAPI instead).
#if 0
#define RLUTIL_USE_ANSI
#endif

/// Define: RLUTIL_STRING_T
/// Define/typedef this to your preference to override rlutil's string type.
///
/// Defaults to std::string with C++ and char* with C.
#if 0
#define RLUTIL_STRING_T char*
#endif

#ifdef __cplusplus
	/// Common C++ headers
	#include <iostream>
	#include <string>
#endif // __cplusplus

#ifdef WIN32
	#include <windows.h>  // for color()
	#include <conio.h>    // for getch() and kbhit()
#else
	#ifdef __cplusplus
		#include <cstdio> // for getch()
	#else // __cplusplus
		#include <stdio.h> // for getch()
	#endif // __cplusplus
	#include <termios.h>  // for getch()
	#include <unistd.h>   // for getch()

/// Function: getch
/// Get character without requiring pressing Enter.
/// Windows has this in conio.h
int getch() {
	struct termios oldt, newt;
	int ch;
	tcgetattr( STDIN_FILENO, &oldt );
	newt = oldt;
	newt.c_lflag &= ~( ICANON | ECHO );
	tcsetattr( STDIN_FILENO, TCSANOW, &newt );
	ch = getchar();
	tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
	return ch;
}

/// Function: kbhit
/// Determines if keyboard has been hit. Dummy for Linux (in conio.h on Windows).
int kbhit() {
	//TODO: Dummy implementation
	return !0;
}
#endif // WIN32

#ifdef __cplusplus
/// Namespace: rlutil
/// In C++ all functions except getch() and kbhit() are arranged under namespace rlutil.
/// That is because they are found in conio.h on Windows.
namespace rlutil {
#endif

/**
 * Defs: Internal typedefs and macros
 * RLUTIL_STRING_T - String type depending on which one of C or C++ is used
 * RLUTIL_PRINT(str) - Printing macro independent of C/C++
 */

#ifdef __cplusplus
	#include <iostream>
	#include <string>
	#ifndef RLUTIL_STRING_T
		typedef std::string RLUTIL_STRING_T;
	#endif // RLUTIL_STRING_T
	void inline RLUTIL_PRINT(RLUTIL_STRING_T st) { std::cout << st; }
#else // __cplusplus
	#ifndef RLUTIL_STRING_T
		typedef char* RLUTIL_STRING_T;
	#endif // RLUTIL_STRING_T
	#define RLUTIL_PRINT(st) printf("%s", st)
#endif // __cplusplus

/**
 * Consts: ANSI color strings
 *
 * ANSI_CLS - Clears screen
 * ANSI_BLACK - Black
 * ANSI_RED - Red
 * ANSI_GREEN - Green
 * ANSI_BROWN - Brown / dark yellow
 * ANSI_BLUE - Blue
 * ANSI_MAGENTA - Magenta / purple
 * ANSI_CYAN - Cyan
 * ANSI_GREY - Grey / dark white
 * ANSI_DARKGREY - Dark Grey / light black
 * ANSI_LIGHTRED - Light red
 * ANSI_LIGHTGREEN - Light green
 * ANSI_YELLOW - Yellow (bright)
 * ANSI_LIGHTBLUE - Light blue
 * ANSI_LIGHTMAGENTA - Light magenta / light purple
 * ANSI_LIGHTCYAN - Light cyan
 * ANSI_WHITE - White (bright)
 **/
const RLUTIL_STRING_T ANSI_CLS = "\033[2J";
const RLUTIL_STRING_T ANSI_BLACK = "\033[22;30m";
const RLUTIL_STRING_T ANSI_RED = "\033[22;31m";
const RLUTIL_STRING_T ANSI_GREEN = "\033[22;32m";
const RLUTIL_STRING_T ANSI_BROWN = "\033[22;33m";
const RLUTIL_STRING_T ANSI_BLUE = "\033[22;34m";
const RLUTIL_STRING_T ANSI_MAGENTA = "\033[22;35m";
const RLUTIL_STRING_T ANSI_CYAN = "\033[22;36m";
const RLUTIL_STRING_T ANSI_GREY = "\033[22;37m";
const RLUTIL_STRING_T ANSI_DARKGREY = "\033[01;30m";
const RLUTIL_STRING_T ANSI_LIGHTRED = "\033[01;31m";
const RLUTIL_STRING_T ANSI_LIGHTGREEN = "\033[01;32m";
const RLUTIL_STRING_T ANSI_YELLOW = "\033[01;33m";
const RLUTIL_STRING_T ANSI_LIGHTBLUE = "\033[01;34m";
const RLUTIL_STRING_T ANSI_LIGHTMAGENTA = "\033[01;35m";
const RLUTIL_STRING_T ANSI_LIGHTCYAN = "\033[01;36m";
const RLUTIL_STRING_T ANSI_WHITE = "\033[01;37m";

/// Function: getANSIColor
/// Return ANSI color escape sequence for specified number.
///
/// See <Color Codes>
RLUTIL_STRING_T getANSIColor(const int c) {
	switch (c) {
		case 0 : return ANSI_BLACK;
		case 1 : return ANSI_BLUE; // non-ANSI
		case 2 : return ANSI_GREEN;
		case 3 : return ANSI_CYAN; // non-ANSI
		case 4 : return ANSI_RED; // non-ANSI
		case 5 : return ANSI_MAGENTA;
		case 6 : return ANSI_BROWN;
		case 7 : return ANSI_GREY;
		case 8 : return ANSI_DARKGREY;
		case 9 : return ANSI_LIGHTBLUE; // non-ANSI
		case 10: return ANSI_LIGHTGREEN;
		case 11: return ANSI_LIGHTCYAN; // non-ANSI;
		case 12: return ANSI_LIGHTRED; // non-ANSI;
		case 13: return ANSI_LIGHTMAGENTA;
		case 14: return ANSI_YELLOW; // non-ANSI
		case 15: return ANSI_WHITE;
		default: return "";
	}
}

/// Function: setColor
/// Change color specified by number (Windows / QBasic colors).
///
/// See <Color Codes>
void setColor(int c) {
#if defined(WIN32) && !defined(RLUTIL_USE_ANSI)
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, c);
#else
	RLUTIL_PRINT(getANSIColor(c));
#endif
}

/// Function: cls
/// Clears screen.
void cls() {
#if defined(WIN32) && !defined(RLUTIL_USE_ANSI)
	system("cls");
#else
	RLUTIL_PRINT("\033[2J");
#endif
}

#ifdef __cplusplus
} // namespace rlutil
#endif
