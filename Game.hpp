/*
 * Game.hpp
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
#include "Board.hpp"
#include "Player.hpp"
#include "Enemy.hpp"

const int len = 3; //max number of enemies

class Game{
public:
	int n0,n1,n2,n3,n4; //number of enemies
	Game(int height,int width);
	void updateState(); //Main game
	void redraw(); //
	bool isOver(); //Game is over
	void interaction1(int i,Enemy0 e); //Game interaction between Enemy without gun and Player
	void displaylife(); //Display life
protected:
	Board board;
	Player player;
	Enemy0 enemy0[len];
	Enemy1 enemy1[len];
	Enemy2 enemy2[len];
	Enemy3 enemy3[len];
	Enemy4 enemy4[len];
	bool game_over;
};

