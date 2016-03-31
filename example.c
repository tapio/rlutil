#include "rlutil.h"
#include <stdlib.h> // for srand() / rand()
#include <stdio.h>
#include "math.h"

#ifndef min
#define min(a,b) (((a)<(b))?(a):(b))
#endif // min

/// Tiles
#define FLOOR 0
#define WALL 1
#define COIN (1 << 1)
#define STAIRS_DOWN (1 << 2)
#define TORCH (1 << 4)

#define MAPSIZE 15

/// Globals
int x, y;
int coins = 0, moves = 0, torch = 30, level = 1;
int lvl[MAPSIZE][MAPSIZE];

/// Generates the dungeon map
void gen(int seed) {
	srand(seed);
	int i, j;
	for (j = 0; j < MAPSIZE; j++) {
		for (i = 0; i < MAPSIZE; i++) {
			if (i == 0 || i == MAPSIZE-1 || j == 0 || j == MAPSIZE-1 ||
			  rand() % 10 == 0) lvl[i][j] = 1;
			else if (rand() % 20 == 0) lvl[i][j] = COIN;
			else if (rand() % 100 == 0) lvl[i][j] = TORCH;
			else lvl[i][j] = 0;
		}
	}
	#define randcoord (1+rand()%(MAPSIZE-2))
	x = randcoord;
	y = randcoord;
	lvl[randcoord][randcoord] = STAIRS_DOWN;
	#undef randcoord
}

/// Draws the screen
void draw() {
	cls();
	locate(1, MAPSIZE + 1);
	setColor(YELLOW);
	printf("Coins: %d\n", coins);
	setColor(RED);
	printf("Torch: %d\n", torch);
	setColor(MAGENTA);
	printf("Moves: %d\n", moves);
	setColor(GREEN);
	printf("Level: %d\n", level);
	locate(1, 1);
	int i, j;
	for (j = 0; j < MAPSIZE; j++) {
		for (i = 0; i < MAPSIZE; i++) {
			if (0); //(i == x && j == y) printf("@");
			else if (abs(x-i)+abs(y-j)>min(10,torch/2)) printf(" ");
			else if (lvl[i][j] == 0) { setColor(BLUE); printf("."); }
			else if (lvl[i][j] & WALL) { setColor(CYAN); printf("#"); }
			else if (lvl[i][j] & COIN) { setColor(YELLOW); printf("o"); }
			else if (lvl[i][j] & STAIRS_DOWN) { setColor(GREEN); printf("<"); }
			else if (lvl[i][j] & TORCH) { setColor(RED); printf("f"); }
		}
		printf("\n");
	}
	locate(x+1, y+1);
	setColor(WHITE);
	printf("@");
	fflush(stdout);
}

/// Main loop and input handling
int main() {
	hidecursor();
	saveDefaultColor();
	gen(level);
	setColor(2);
	printf("Welcome! Use WASD to move, ESC to quit.\n");
	setColor(6);
	anykey("Hit any key to start.\n");
	draw();
	while (1) {
		// Input
		if (kbhit()) {
			char k = getkey();

			int oldx = x, oldy = y;
			if (k == 'a') { --x; ++moves; }
			else if (k == 'd') { ++x; ++moves; }
			else if (k == 'w') { --y; ++moves; }
			else if (k == 's') { ++y; ++moves; }
			else if (k == KEY_ESCAPE) break;
			// Collisions
			if (lvl[x][y] & WALL) { x = oldx; y = oldy; }
			else if (lvl[x][y] & COIN) { coins++; lvl[x][y] ^= COIN; }
			else if (lvl[x][y] & TORCH) { torch+=20; lvl[x][y] ^= TORCH; }
			else if (lvl[x][y] & STAIRS_DOWN) gen(++level);
			// Drawing
			draw();
			// Die
			if (--torch <= 0) break;
		}
	}

	cls();
	resetColor();
	showcursor();

	return 0;
}
