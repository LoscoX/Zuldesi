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
#include "Player.hpp"
#include "Enemy.hpp"

using namespace std;

int main(int argc, char ** argv) {
	srand(time(0));
	//initialize the screen
	//sets up the memory and clears the screen
	initscr();
	cbreak();
	noecho();

	int height = 25; int width = 90;

	WINDOW * playwin = newwin(height,width,0,30);  //creates the window
	box(playwin,0,0);
	refresh();
	wrefresh(playwin);

	Player * p = new Player(playwin,height-2 , 1, '@'); //creates the player
	Enemy * e = new Enemy(playwin,height-2, width-10, '0');
	do{
		p->display(); //See the player
		e->display();
		wrefresh(playwin);
		e->movement();
		if(e->xLoc == p->xLoc && e->yLoc == p->yLoc){
			p->injury();
		}
	}while(p->getmv() != 'x' && p->getmv() != 'X');

	getch(); //whats for user input, returns int value for that key

	endwin(); //deallocates memory and ends ncurses
}
