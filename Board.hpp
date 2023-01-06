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
	void initializeWall(int x,int y,int ind); //build the walls
	void deleteWall(int x,int y,int ind);
	void initializePlatform(int pivot,int h,int ind); //build the structures
	void deletePlatform(int pivot,int h,int ind);
	platform plat[num_ogg]; //platforms
	wall wal[num_ogg]; //walls
	bool IsThereStructure(int x,int y); //check if one character collides with a structure
	int height,width; //height and width of the board
protected:
	void construct(int height, int width);
};
