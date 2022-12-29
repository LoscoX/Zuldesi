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

struct listenemy0{ //list of enemies type 0
	int val; //ID
	Enemy0 enemy; //enemy
	listenemy0* next;
};
struct listenemy1{ //list of enemies type1
	int val; //ID
	Enemy1 enemy; //enemy
	listenemy1* next;
};
struct listenemy2{ //list of enemies type2
	int val; //ID
	Enemy2 enemy; //enemy
	listenemy2* next;
};
struct listenemy3{ //list of enemies type3
	int val; //ID
	Enemy3 enemy; //enemy
	listenemy3* next;
};
struct listenemy4{ //list of enemies type4
	int val; //ID
	Enemy4 enemy; //enemy
	listenemy4* next;
};
struct listenemy5{ //list of enemies type5
	int val; //ID
	Enemy5 enemy; //enemy
	listenemy5* next;
};


struct money{
	int val; //ID
	int x; //x position of coin
	int y; //y position of coin
	money* next;
};


typedef listenemy0* listenm0;
typedef listenemy1* listenm1;
typedef listenemy2* listenm2;
typedef listenemy3* listenm3;
typedef listenemy4* listenm4;
typedef listenemy5* listenm5;

typedef money* mony;


class Game{
public:
	int n0,n1,n2,n3,n4,n5; //number of enemies
	int nc; //number of coins
	Game(int height,int width);
	void updateState(); //Main game
	void redraw(); //
	bool isOver(); //Game is over
	void interaction(Enemy0 e); //Game interaction between Enemy without gun and Player
	int directionSmartEnemy(Enemy5 e); //Handle the direction of the enemy based on the position of the player
	void displaylife(); //Display life
	void displaycoins(); //Display wallet
	void shooting(); //handle the shooting
	void enemymovement(); //enemies movement
	void playermovement(); //player movement
	int time; //time of the game

	mony head_insert_coin(mony h,int val,int x,int y);

	listenm0 head_insert_enemy0(listenm0 h,Enemy0 e, int val); //add one enemy type0
	listenm1 head_insert_enemy1(listenm1 h,Enemy1 e, int val); //add one enemy type1
	listenm2 head_insert_enemy2(listenm2 h,Enemy2 e, int val); //add one enemy type2
	listenm3 head_insert_enemy3(listenm3 h,Enemy3 e, int val); //add one enemy type3
	listenm4 head_insert_enemy4(listenm4 h,Enemy4 e, int val); //add one enemy type4
	listenm5 head_insert_enemy5(listenm5 h,Enemy5 e, int val); //add one enemy type5

	listenm0 obj_remove_enemy0(listenm0 h,int cod); //delete one enemy type0
	listenm1 obj_remove_enemy1(listenm1 h,int cod); //delete one enemy type1
	listenm2 obj_remove_enemy2(listenm2 h,int cod); //delete one enemy type2
	listenm3 obj_remove_enemy3(listenm3 h,int cod); //delete one enemy type3
	listenm4 obj_remove_enemy4(listenm4 h,int cod); //delete one enemy type4
	listenm5 obj_remove_enemy5(listenm5 h,int cod); //delete one enemy type1

	void initializeCoins(); //spawn of coins
	void updateCoins(); //check if one coin has to be removed
	mony removeCoins(mony h,int cod); //remove one coin

	void initializeEnemies(); //initalize enemies
	bool enemydeath(bullt tmp);
protected:
	Board board;
	Player player;
	listenm0 enemies0; //list of enemies type 0
	listenm1 enemies1; //list of enemies type 1
	listenm2 enemies2; //list of enemies type 2
	listenm3 enemies3; //list of enemies type 3
	listenm4 enemies4; //list of enemies type 4
	listenm5 enemies5; //list of enemies type 5

	mony coins;
	bool game_over;
};

