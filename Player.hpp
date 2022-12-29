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
	int val; //powerup code
	char c; //powerup graphic symbol
	powerup* next;
};

struct bullet{
	int xB; //x of the bullet
	int yB; //y of the bullet
	int dir; //direction of the bullet
	int cod; //how to identify one bullet
	bullet* next;

};

typedef bullet* bullt;
typedef powerup* powup;

class Player{
private:
	int xMax,yMax; //coordinates of the box
	char character[2]; //icon of the player
	WINDOW * curwin;
	int life; //life
	int cash; //money
	void mvleft();
	void mvright();
public:
	int xLoc,yLoc; //coordinates of the player
	int dir; //save the direction of the movement
	bool activejump; //if it is true, you are jumping
	int xpern,ypern; //pivot for jumping
	int conta;
	bool gun; //activate gun or not

	Player();
	Player(WINDOW * win, int y, int x);

	int getmv(); //movement

	void updatepivot(); //update pivotvariables
	void jump();
	int jumpandshoot(); //shoot during the jump

	bullt blt; //list of bullet that you are using
	int ind; //index for the list of bullet
	bullt head_insert(bullt h,int dir); //create new bullet and add it in the gun magazine
	bullt obj_remove(bullt h, int e); //destroy the first bullet and remove from the gun magazine
	void shoot(bullt h); //handle the dynamic of the bullet

	void display(); //see the player
	void initialize(); //start the player

	void injury(); //damage

	int getx(); //x coordinate of the player
	int gety(); //y coordinate of the player
	int getlife(); //return life of player
	int getcoins(); //return coins of player

	void updatecash(); //update your wallet

	powup pwup; //power-up

	powup addpwup(powup h,int e,char icon); //add powerup
	powup removepwup(powup h, int e); //remove powerup
};
