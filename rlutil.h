/** rlutil.h
 * Copyright (C) 2010 Tapio Vierros
 *
 * This file provides some useful utilities for console mode
 * roguelike game development with C++. It is aimed to be
 * cross-platform (at least Windows and Linux).
 *
 * *** LICENSE ***
 *
 *            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 *                    Version 2, December 2004
 *
 * Copyright (C) 2004 Sam Hocevar <sam@hocevar.net>
 *
 * Everyone is permitted to copy and distribute verbatim or modified
 * copies of this license document, and changing it is allowed as long
 * as the name is changed.

 *            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
 *   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION
 *
 *  0. You just DO WHAT THE FUCK YOU WANT TO.
*/

/// Define RLUTIL_USE_ANSI to use ANSI escape sequences also on Windows
//#define RLUTIL_USE_ANSI

#include <iostream>
#include <string>

#ifdef WIN32
#include <windows.h>  // for color()
#include <conio.h>    // for getch() and kbhit()
#else
#include <cstdio>     // for gethch()
#include <termios.h>  // for gethch()
#include <unistd.h>   // for gethch()

/// Get character without requiring pressing Enter
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

/// Somewhat useless function? (In conio.h on Windows)
//TODO: If this always returns true, does it have side effects?
bool kbhit() {
	return true;
}
#endif

const std::string ANSI_CLS("\033[2J");
const std::string ANSI_BLACK("\033[22;30m");
const std::string ANSI_RED("\033[22;31m");
const std::string ANSI_GREEN("\033[22;32m");
const std::string ANSI_BROWN("\033[22;33m");
const std::string ANSI_BLUE("\033[22;34m");
const std::string ANSI_MAGENTA("\033[22;35m");
const std::string ANSI_CYAN("\033[22;36m");
const std::string ANSI_GRAY("\033[22;37m");
const std::string ANSI_DARKGREY("\033[01;30m");
const std::string ANSI_LIGHTRED("\033[01;31m");
const std::string ANSI_LIGHTGREEN("\033[01;32m");
const std::string ANSI_YELLOW("\033[01;33m");
const std::string ANSI_LIGHTBLUE("\033[01;34m");
const std::string ANSI_LIGHTMAGENTA("\033[01;35m");
const std::string ANSI_LIGHTCYAN("\033[01;36m");
const std::string ANSI_WHITE("\033[01;37m");

/// Return ANSI color escape sequence for speficied number
std::string getANSIColor(const int c) {
	switch (c) {
		case 0 : return ANSI_BLACK;
		case 1 : return ANSI_BLUE; // non-ANSI
		case 2 : return ANSI_GREEN;
		case 3 : return ANSI_CYAN; // non-ANSI
		case 4 : return ANSI_RED; // non-ANSI
		case 5 : return ANSI_MAGENTA;
		case 6 : return ANSI_BROWN;
		case 7 : return ANSI_GRAY;
		case 8 : return ANSI_DARKGREY;
		case 9 : return ANSI_LIGHTBLUE; // non-ANSI
		case 10: return ANSI_LIGHTGREEN;
		case 11: return ANSI_LIGHTCYAN; // non-ANSI;
		case 12: return ANSI_LIGHTRED; // non-ANSI;
		case 13: return ANSI_LIGHTMAGENTA;
		case 14: return ANSI_YELLOW; // non-ANSI
		case 15: return ANSI_WHITE;
		default: return std::string("");
	}
}

/// Change color specified by number (Windows / QBasic colors)
void color(int c) {
#if defined(WIN32) && !defined(RLUTIL_USE_ANSI)
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, c);
#else
	std::cout << getANSIColor(c);
#endif
}

/// Clear screen
void cls() {
#if defined(WIN32) && !defined(RLUTIL_USE_ANSI)
	system("cls");
#else
	std::cout << "\033[2J";
#endif
}

