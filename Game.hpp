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
#include <typeinfo>
#include "Board.hpp"
#include "Map.hpp"

const int NUM_GUNS = 4; //max number of powerup type gun
const int NUM_BONUS = 5; //max number of powerup type bonus
const int NUM_ACTIVE = 3; //max number of powerup type activable

struct map_el{
	int id;
	Map map;
	map_el* next;
	map_el* prev;
};

typedef map_el* map_list;

class Game{
public:

	Game(int height,int width); //Constructor

	//Function for the map
	void restartMap(int difficulty);
	void nextMap(int dir, int difficulty);
	void PrintMap(); //Print map

	//Main functions
	void updateState(); //Main game
	void redraw(); //
	bool isOver(); //Game is over

	//Market function
	void initializePowerUp(); //initialize powerup
	void drawPowerUp(Powerup pwp[]); //draw powerup
	void deletePowerup(Powerup pwp[]); //delete powerup
	void updatePowerup();
	void market(); //activate the market
	void market_build(); //build the market
	void drawDescription(int i); //draw description of power up
	void deleteDescription(int i); //draw description of power up

	//Function for the movement
	void PlayerCanMove(int choice); //Game interaction between player and structure map
	void PlayerCanFly(int choice); //Game interaction between player and structure map when you fly
	void Enemy0CanMove(listenm0 h); //Game interaction between enemy0 and structure map
	void Enemy1CanMove(listenm1 h); //Game interaction between enemy1 and structure map
	void Enemy2CanMove(listenm2 h); //Game interaction between enemy2 and structure map
	void Enemy3CanMove(listenm3 h); //Game interaction between enemy3 and structure map
	void Enemy4CanMove(listenm4 h); //Game interaction between enemy4 and structure map
	void Enemy5CanMove(listenm5 h); //Game interaction between enemy5 and structure map
	void Enemy6CanMove(listenm6 h); //Game interaction between enemy6 and structure map
	void Enemy7CanMove(listenm7 h); //Game interaction between enemy7 and structure map
	void Enemy8CanMove(listenm8 h);
	void Enemy9CanMove(listenm9 h); //Game interaction between enemy9 and structure map
	void mapMovement(); //map movement
	void enemyMovement(); //enemies movement
	void PlayerDown(); //player goes down
	int directionSmartEnemy5(Enemy5 e); //Handle the direction of the enemy based on the position of the player
	int directionSmartEnemy7(Enemy7 e); //Handle the direction of the enemy based on the position of the player
	int directionSmartEnemy8(Enemy8 e); //Handle the direction of the enemy based on the position of the player

	//graphic function
	void displayLife(); //Display life
	void displayCoins(); //Display wallet
	void displayGame(); //Display Title
	void displayBullets(); //Display bullets
	void displayPoints(); //Display points
	void displayMarket(); //Display market
	void displayPowerup(); //Display powerup

	//function for collision
	void interaction(Enemy0 e); //Game interaction between Enemy without gun and Player
	bool enemydeath(bullt tmp); //enemy death for bullets
	bool enemydeath2(bullt tmp); //enemy death for explosive bullets
	//function for bullets collision
	bool interactionBullet(bullt tmp); //Game interaction between Enemy with gun and Player
	void shooting(); //handle the shooting
	bullt deletePlayerBullets(bullt tmp); //delete bullets of the Player
	bullt deletePlayerExplosiveBullets(bullt tmp); //delete explosive bullets of the Player
	bullt deleteEnemy6Bullets(bullt tmp,listenm6 e); //delete bullets of Enemy6
	bullt deleteEnemy7Bullets(bullt tmp,listenm7 e); //delete bullets of Enemy7
	bullt deleteEnemy8Bullets(bullt tmp,listenm8 e); //delete bullets of Enemy8
	bullt deleteEnemy9Bullets(bullt tmp,listenm9 e); //delete bullets of Enemy9

	//function coins
	void handleCoins(); //handle coins part
	//function maps
	void handleMaps(); //handle maps part, market part
	//function display
	void handleDisplay(); //handle displayment

	//Update function
	void UpdateBoard(); //redraw the board
	void updateDifficulty();

protected:

	Powerup spawn_powerup[3]; //power up spawned in the market

	//powerup
	Powerup guns[NUM_GUNS]; //guns powerup
	Powerup bonus[NUM_BONUS]; //bouns powerup
	Powerup active[NUM_ACTIVE]; //activable powerup

	int xMin; //variable for the position of camera

	int HEIGHT_MARKET; //height of market powerups
	//costants for drawing
	int draw_cost1;
	int draw_cost2;
	int draw_cost3;

	bool Market_Active; //you are in the market
	bool Market_Build; //you have to build the market
	bool bought1,bought2,bought3; //tell us if you have bought one powerup

	int time; //time of the game

	int difficulty; //difficulty of the level. It depends on the number of powerup you have. It handles the generation of the map

	Board board; //board

	Player player; //player

	Map map; //map

	string* matrix; //matrix for the map

	bool game_over;

	map_list mapList; //list of maps

};
