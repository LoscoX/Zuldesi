/*
 * board.hpp
 *
 *  Created on: 11 dic 2022
 *      Author: david
 */

#include <iostream>
#include <ncurses.h>
#include <ctime>
#include <cstring>
#include <cmath>
#include <cstdlib>

const int len = 7;

struct platform{ //structure for a platform
	char graph[len];
	int xpos[len];
	int ypos[len];
};

struct wall{ //structure for a wall
	char graph[len];
	int xpos[len];
	int ypos[len];
};


class Board{
public:
	WINDOW *board_win;
	Board();
	Board(int height, int width);
	void addBorder();
	void clear();
	void refresh();
	void initialize();
	void addAt(int y,int x,char ch);
	char getInput();
	void initializeWall(int x,int y,int ind);
	void initializePlatform(int pivot,int h,int ind);
	platform plat[3]; //platforms
	wall wal[3]; //walls
protected:
	void construct(int height, int width);
};
