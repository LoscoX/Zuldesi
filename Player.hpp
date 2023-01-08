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
	char character[4]; //icon of the player
	WINDOW * curwin;
	int life; //life
	int cash; //money
	int xLoc,yLoc; //coordinates of the player
	int xMax,yMax; //coordinates of the box
	int dir; //save the direction of the movement
	int points; //points of the player
	int jump_height;
	void mvleft();
	void mvright();
public:
	bool activejump; //if it is true, you are jumping
	int conta;
	bool onplatform; //if the player is on a platform
	int segno;
	//powerup
	Powerup gun; //type of gun
	Powerup shield; //shield
	Powerup hp; //life
	Powerup armor; //armor
	Powerup teleportation; //teleport
	Powerup bullets; //bullets
	Powerup jumping; //jump
	Powerup fly; //fly
	Powerup explo_bullets; //explosive bullets
	int ARMOR_DURATION[3]; //duration of the armor
	int TELEPORT_DISTANCE[3]; //distance of teleport
	bool ACTIVE_ARMOR; //you active or not armor
	int ARMOR_ACTIVE_DURATION; //time duration of actived armor
	int NUM_BULLETS; //number of bullets
	int NUM_EXPLO_BULLETS; //number of explosive bullets
	int FLY_DURATION; //duration of the fly
	int FLY_ACTIVE_DURATION; //time duration of actived fly
	bool ACTIVE_FLY; //you activd or not fly

	Player();
	Player(WINDOW * win, int y, int x);

	int getmv(); //movement
	void jump(); //jump
	int airshoot(); //shoot during the jump movement or the down movement
	void godown(); //fall
	void teleport(); //teleport
	void goup(); //go up

	Bullet bullet; //bullets magazine
	Bullet explo_bullet; //explosive bullets magazine
	int ind; //index for the list of bullets
	int ind2; //index for the list of explosive bullets

	void display(); //see the player
	void initialize(); //start the player

	void injury(); //damage

	int getx(); //x coordinate of the player
	int gety(); //y coordinate of the player
	int getCoins(); //return coins of player
	int getDir(); //return dir of player
	int getPoints(); //points of the player
	int getLife(); //life of player

	void SetJump(); //restart the variable of jump

	void updatePoints(int points); //when you kill one enemy you take points
	void updateCash(int money); //update your wallet
	void updateCoordinates(int x,int y); //Update your x and y when you went in a not-possible place
	void setDir(int dir); //change direction
	void setLife(int val); //change life
};
