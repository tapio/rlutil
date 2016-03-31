/**
 * File: test.cpp
 *
 * About: Description
 * This is a C++ example / test program for rlutil that can be
 * used for validating or showcasing the functionality.
 *
 * About: Copyright
 * (C) 2010 Tapio Vierros
 *
 * About: Licensing
 * See <License>
 */

#include "rlutil.h"
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <ctime>

#define waitkey rlutil::anykey("Press any key to continue...\n")

char chargen() {
	return rand() % (('~' - '!') + 1) + '!'; // I am really sorry for this
}

int main() {
	rlutil::saveDefaultColor();

	std::cout << "Welcome to rlutil test program." << std::endl;
	waitkey;

	std::cout << "\nTest 1: Colors" << std::endl;
	for (int i = 0; i < 16; i++) {
		rlutil::setColor(i);
		std::cout << i << " ";
	}
	rlutil::resetColor();
	std::cout << std::endl << "You should see numbers 0-15 in different colors." << std::endl;
	waitkey;

	std::cout << "\nTest 2: Background colors\n";
	for (int i = 0; i < 8; i++) {
		rlutil::setBackgroundColor(i);
		std::cout << i;
		rlutil::setBackgroundColor(0);
		std::cout << ' ';
	}
	rlutil::resetColor();
	std::cout << "\nYou should see numbers 0-7 in different-colored backgrounds.\n";
	waitkey;

	rlutil::cls();
	std::cout << "Test 3: Clear screen" << std::endl;
	std::cout << "The colors should now be gone." << std::endl;
	waitkey;

	std::cout << "\nTest 4: Cursor hiding" << std::endl;
	rlutil::hidecursor();
	std::cout << "The cursor should now be invisible." << std::endl;
	waitkey;

	std::cout << "\nTest 5: Cursor showing" << std::endl;
	rlutil::showcursor();
	std::cout << "The cursor should now be visible again." << std::endl;
	waitkey;

	rlutil::cls();
	std::cout << "Test 6: Cursor positioning" << std::endl;
	rlutil::locate(16,6); std::cout << "(16,6)";
	rlutil::locate(4,3); std::cout << "(4,3)";
	rlutil::locate(8,8); std::cout << "(8,8)";
	std::cout << std::endl << "You should see three coordinates in their specified locations." << std::endl;
	waitkey;

	// Test 7
	{	int x = 7; int y = 7; unsigned int cnt = 0;
		while (true) {
			rlutil::cls();
			std::cout << "Test 7: Blocking keyboard input" << std::endl;
			std::cout << "You should be able to move the '@' character with WASD keys." << std::endl;
			std::cout << "Hit Space to continue to the next test." << std::endl;
			std::cout << "Turn count: " << cnt << std::endl;
			rlutil::locate(x,y); std::cout << '@'; // Output player
			char k = getch(); // Get character
			if (k == 'a') --x;
			else if (k == 'd') ++x;
			else if (k == 'w') --y;
			else if (k == 's') ++y;
			else if (k == ' ') break;
			cnt++;
		}
	}

	// Test 8
	{	int x = 7; int y = 7; unsigned int cnt = 0;
		rlutil::hidecursor();
		rlutil::cls();
		std::cout << "Test 8: Non-blocking keyboard input" << std::endl;
		std::cout << "You should be able to move the '@' character with WASD keys." << std::endl;
		std::cout << "Hit Space to continue to the next test." << std::endl;
		std::cout << "Turn count: " << cnt << std::endl;
		rlutil::locate(x,y); std::cout << '@' << std::endl; // Output player
		while (true) {
			rlutil::locate(1,4); std::cout << "Turn count: " << cnt;
			if (kbhit()) {
				char k = getch(); // Get character
				rlutil::locate(x,y); std::cout << " "; // Erase player
				if (k == 'a') --x;
				else if (k == 'd') ++x;
				else if (k == 'w') --y;
				else if (k == 's') ++y;
				else if (k == ' ') break;
				rlutil::locate(x,y); std::cout << '@'; // Output player
			}
			cnt++;
			std::cout.flush();
		}
		rlutil::showcursor();
	}

	// Test 9
	{	int x = 7; int y = 7;
		rlutil::cls();
		rlutil::CursorHider curs;
		std::cout << "Test 9: Arrow keys" << std::endl;
		std::cout << "You should be able to move the '@' character with arrow keys." << std::endl;
		std::cout << "Hit Escape to continue to the next test." << std::endl;
		gotoxy(x,y); std::cout << '@' << std::endl; // Output player
		while (true) {
			if (kbhit()) {
				int k = rlutil::getkey(); // Get character
				gotoxy(x,y); std::cout << " "; // Erase player
				if (k == rlutil::KEY_LEFT) --x;
				else if (k == rlutil::KEY_RIGHT) ++x;
				else if (k == rlutil::KEY_UP) --y;
				else if (k == rlutil::KEY_DOWN) ++y;
				else if (k == rlutil::KEY_ESCAPE) break;
				gotoxy(x,y); std::cout << '@'; // Output player
				std::cout.flush();
			}
		}
	}

	rlutil::cls();
	std::cout << "Test 10: Delay" << std::endl;
	std::cout << "Next numbers should appear rapidly after each other (but not instantly)." << std::endl;
	rlutil::msleep(500);
	for (float t = 0; t <= 2; t += 0.25f) {
		std::cout << t << "s" << std::endl;
		rlutil::msleep(250);
	}
	waitkey;

	rlutil::cls();
	std::cout << "Test 11: Terminal Dimensions" << std::endl;
	std::cout << "You should see the size in character rows and columns of your terminal window." << std::endl;
	std::cout << rlutil::trows() << " Rows" << std::endl;
	std::cout << rlutil::tcols() << " Columns" << std::endl;
	waitkey;

	rlutil::cls();
	std::cout << "Test 12: Non-advancing character setting" << std::endl;
	std::cout << "Next ASCII characters should appear rapidly after each other in the same position." << std::endl;
	{
		rlutil::CursorHider hider;
		for(char c = '!'; c <= '~'; ++c) {
			rlutil::setChar(c);
			std::cout.flush();
			rlutil::msleep(75);
		}
	}
	waitkey;

	std::srand(std::time(0));
	rlutil::cls();
	std::cout << "Test 13: Non-advancing string setting" << std::endl;
	std::cout << "Next random character strings should appear rapidly after each other starting in the same position." << std::endl;
	{
		const rlutil::CursorHider hider;
		const unsigned int maxlen = rlutil::tcols() / 2;
		std::string buf(maxlen, '\0');
		for(unsigned int l = 1; l < maxlen; ++l) {
			std::generate(buf.begin(), buf.begin() + l, chargen);
			rlutil::setString(buf.c_str());
			std::cout.flush();
			rlutil::msleep(75);
		}
	}
	std::cout << std::endl;
	waitkey;

	rlutil::cls();
	std::cout << "Test 14: Terminal window title" << std::endl;
	{
		std::string title(14, '\0');
		std::generate(title.begin(), title.end(), chargen);
		rlutil::setConsoleTitle(title);
		std::cout << "Your terminal window should now be named \"" << title << "\"." << std::endl;
	}
	waitkey;

	std::cout << "All tests done. Bye!" << std::endl;
	return 0;
}
