//============================================================================
// Name        : Project.cpp
// Author      : Davide Giannerini
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <ncurses.h>
#include <ctime>
#include <cstring>

#include "Game.hpp"


using namespace std;

int main(int argc, char ** argv) {
	srand(time(0));
	//initialize the screen
	//sets up the memory and clears the screen
	initscr();
	refresh();

	noecho();

	Game game(25,110);

	while(!game.isOver()){
		game.updateState();
		game.redraw();
	}

	//getch(); //whats for user input, returns int value for that key

	endwin(); //deallocates memory and ends ncurses
	return 0;
}
