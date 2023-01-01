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
#include "Bullet.hpp"

class Player{
private:
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
	int xMax,yMax; //coordinates of the box
	//powerup
	char typeofgun[20]; //type of gun (it depends from you powerup)
	bool shield; //shield
	int shield_life; //shield resistance
	bool teleportation; //you can or cannot teleport
	int time_life_armor; //time duration of armor
	bool active_armor; //you active or not armor
	bool have_armor; //you have or have not armor

	Player();
	Player(WINDOW * win, int y, int x);

	int getmv(); //movement

	void updatepivot(); //update pivotvariables
	void jump();
	int jumpandshoot(); //shoot during the jump
	bool godown(); //fall from one platform
	void teleport();

	Bullet bullet; //gun magazine
	int ind; //index for the list of bullet

	void display(); //see the player
	void initialize(); //start the player

	void injury(); //damage

	int getx(); //x coordinate of the player
	int gety(); //y coordinate of the player
	int getlife(); //return life of player
	int getcoins(); //return coins of player

	void updatecash(); //update your wallet
};
