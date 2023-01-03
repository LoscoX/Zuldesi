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
#include "Powerup.hpp"

class Player{
private:
	char character[2]; //icon of the player
	WINDOW * curwin;
	int life; //life
	int cash; //money
	int xLoc,yLoc; //coordinates of the player
	int xMax,yMax; //coordinates of the box
	int dir; //save the direction of the movement
	void mvleft();
	void mvright();
public:
	bool activejump; //if it is true, you are jumping
	int xpern,ypern; //pivot for jumping
	int conta;
	bool down_arrive; //if the player has finished its fall
	//powerup
	Powerup gun; //type of gun
	Powerup shield; //shield
	Powerup hp; //life
	Powerup armor; //armor
	Powerup teleportation; //teleport
	int ARMOR_DURATION[3]; //duration of the armor
	int TELEPORT_DISTANCE[3]; //distance of teleport
	bool ACTIVE_ARMOR; //you active or not armor
	int ARMOR_ACTIVE_DURATION; //time duration of actived armor

	Player();
	Player(WINDOW * win, int y, int x);

	int getmv(); //movement

	void updatepivot(); //update pivotvariables
	void jump();
	int jumpandshoot(); //shoot during the jump
	void godown(); //fall from one platform
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
	int getdir(); //return dir of player

	void updatecash(int money); //update your wallet
	void updateLife(); //Update life if you finish a level
	void updateCoordinates(int x,int y); //Update your x and y when you went in a not-possible place
};
