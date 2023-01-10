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

const int len = 7; //length of one structure

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

const int num_ogg = 30; //number of one type of objects

class Board{
public:
	WINDOW *board_win;
	Board();
	Board(int height, int width);
	void addBorder(int x,int y);
	void clear();
	void refresh();
	void initialize(int x,int y);
	void addAt(int y,int x,char ch);
	char getInput();
	int getHeight();
	int getWidth();
protected:
	void construct(int height, int width);
	int height,width; //height and width of the board
};
