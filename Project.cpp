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

#include <fstream>


#include "Game.hpp"


using namespace std;

int main(int argc, char ** argv) {

	srand(time(0));

	//initialize the screen
	//sets up the memory and clears the screen
	initscr();
	refresh();

	noecho();


	Game game(29,110);
	curs_set(0); //delete the cursor


	while(!game.isOver()){
		game.updateState();
		game.redraw();
	}


	//update save file
	ofstream save;
	save.open("C:/Users/david/eclipse-workspace/Project/src/save.txt");
	save << "-";
	save.close();


	endwin(); //deallocates memory and ends ncurses
	return 0;
}