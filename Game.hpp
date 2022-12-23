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

const int len = 3;

class Game{
public:
	Game(int height,int width);
	void updateState();
	void redraw();
	bool isOver();
	void interaction(int i);
	void displaylife();
protected:
	Board board;
	Player player;
	Enemy enemy[len];
	bool game_over;
};

