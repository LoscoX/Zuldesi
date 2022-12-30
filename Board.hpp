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
protected:
	void construct(int height, int width);
};
