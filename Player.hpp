/*
 * Player.hpp
 *
 *  Created on: 8 dic 2022
 *      Author: david
 */

#include <iostream>
#include <ncurses.h>
#include <ctime>
#include <cstring>
#include <cmath>
#include <cstdlib>

struct powerup{
	int val;
	char c;
	powerup* next;
};

typedef powerup* powup;

class Player{
private:
	int xMax,yMax; //coordinates of the box
	char character; //icon of the player
	WINDOW * curwin;
	int life; //life
	powup pwup; //power-up
	int cash; //moneys
	void jump(int segno);
	void mvupright();  //movement
	void mvupleft();
	void mvleft();
	void mvright();
public:
	int xLoc,yLoc; //coordinates of the player
	Player();
	Player(WINDOW * win, int y, int x, char c);
	int getmv(); //movement
	void display(); //see the player
	void initialize(); //start the player
	void injury(); //damage
	int getx(); //x coordinate of the player
	int gety(); //y coordinate of the player
	int getlife(); //return life of player
	void updatecash(int cash);
	powup addpwup(powup h,int e,char icon);
};
