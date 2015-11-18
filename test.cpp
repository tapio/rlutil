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
#include <cstdio>

#define waitkey rlutil::anykey("Press any key to continue...\n\n")

int main() {
	std::cout << "Welcome to rlutil test program.\n";
	waitkey;

	std::cout << "Test 1: Colors";
	for (int i = 0; i < 16; i++) {
		rlutil::setColor(i);
		std::cout << i << " ";
	}
	std::cout << "\n"
	             "You should see numbers 0-15 in different colors.\n";
	waitkey;

	rlutil::cls();
	std::cout << "Test 2: Clear screen\n"
	             "The colors should now be gone.\n";
	waitkey;

	std::cout << "Test 3: Cursor hiding\n";
	rlutil::hidecursor();
	std::cout << "The cursor should now be invisible.\n";
	waitkey;

	std::cout << "Test 4: Cursor showing\n";
	rlutil::showcursor();
	std::cout << "The cursor should now be visible again.\n";
	waitkey;

	rlutil::cls();
	std::cout << "Test 5: Cursor positioning\n";
	rlutil::locate(16,6); std::cout << "(16,6)";
	rlutil::locate(4,3); std::cout << "(4,3)";
	rlutil::locate(8,8); std::cout << "(8,8)";
	std::cout << "\n"
	             "You should see three coordinates in their specified locations.\n";
	waitkey;

	// Test 6
	{	int x = 7; int y = 7; unsigned int cnt = 0;
		while (true) {
			rlutil::cls();
			std::cout << "Test 6: Blocking keyboard input\n"
			             "You should be able to move the '@' character with WASD keys.\n"
			             "Hit Space to continue to the next test.\n"
			             "Turn count: " << cnt << '\n';
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

	// Test 7
	{	int x = 7; int y = 7; unsigned int cnt = 0;
		rlutil::hidecursor();
		rlutil::cls();
		std::cout << "Test 7: Non-blocking keyboard input\n"
		             "You should be able to move the '@' character with WASD keys.\n"
		             "Hit Space to continue to the next test.\n"
		             "Turn count: " << cnt << '\n';
		rlutil::locate(x,y); std::cout << '@' << std::endl; // Output player
		while (true) {
			rlutil::locate(1,4); std::cout << "Turn count: " << cnt;
			if (kbhit()) {
				char k = getch(); // Get character
				rlutil::locate(x,y); std::cout << ' '; // Erase player
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

	// Test 8
	{	int x = 7; int y = 7;
		rlutil::cls();
		rlutil::CursorHider curs;
		std::cout << "Test 8: Arrow keys\n"
		             "You should be able to move the '@' character with arrow keys.\n"
		             "Hit Escape to continue to the next test.\n";
		gotoxy(x,y); std::cout << '@' << std::endl; // Output player
		while (true) {
			if (kbhit()) {
				int k = rlutil::getkey(); // Get character
				gotoxy(x,y); std::cout << ' '; // Erase player
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
	std::cout << "Test 9: Delay\n"
	             "Next numbers should appear rapidly after each other (but not instantly)." << std::endl;
	rlutil::msleep(500);
	for (float t = 0; t < 5; t += 0.33333333f) {
		std::cout << t << "s" << std::endl;
		rlutil::msleep(333);
	}
	waitkey;

	rlutil::cls();
	std::cout << "Test 10: Terminal Dimensions\n"
	             "You should see the size in character rows and columns of your terminal window.\n"
	          << rlutil::trows() << " Rows\n"
	          << rlutil::tcols() << " Columns\n";
	waitkey;

	std::cout << "All tests done. Bye!\n";
	return 0;
}
