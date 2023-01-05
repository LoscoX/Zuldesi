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
struct listenemy6{ //list of enemies type6
	int val; //ID
	Enemy6 enemy; //enemy
	listenemy6* next;
};
struct listenemy7{ //list of enemies type7
	int val; //ID
	Enemy7 enemy; //enemy
	listenemy7* next;
};
struct listenemy8{ //list of enemies type8
	int val; //ID
	Enemy8 enemy; //enemy
	listenemy8* next;
};
struct listenemy9{ //list of enemies type8
	int val; //ID
	Enemy9 enemy; //enemy
	listenemy9* next;
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
typedef listenemy6* listenm6;
typedef listenemy7* listenm7;
typedef listenemy8* listenm8;
typedef listenemy9* listenm9;

typedef money* mony;

const int NUM_GUNS = 4; //max number of powerup type gun
const int NUM_BONUS = 3; //max number of powerup type bonus
const int NUM_ACTIVE = 3; //max number of powerup type activable

class Game{
public:
	int n0,n1,n2,n3,n4,n5,n6,n7,n8,n9; //number of enemies
	int nc; //number of coins
	int difficulty; //difficulty of the level. It depends on the number of powerup you have. It handles the generation of the map
	//powerup
	Powerup guns[NUM_GUNS]; //guns powerup
	Powerup bonus[NUM_BONUS]; //bouns powerup
	Powerup active[NUM_ACTIVE]; //activable powerup
	Game(int height,int width);

	void updateState(); //Main game
	void redraw(); //
	bool isOver(); //Game is over
	void drawPowerUp(Powerup pwp[]);

	void Structure(); //create structures

	void updatePowerup();
	void market(); //activate the market

	void interaction(Enemy0 e); //Game interaction between Enemy without gun and Player
	bool interactionBullet(bullt tmp); //Game interaction between Enemy with gun and Player
	void PlayerCanMove(int choice); //Game interaction between player and structure map
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

	int directionSmartEnemy5(Enemy5 e); //Handle the direction of the enemy based on the position of the player
	int directionSmartEnemy7(Enemy7 e); //Handle the direction of the enemy based on the position of the player
	int directionSmartEnemy8(Enemy8 e); //Handle the direction of the enemy based on the position of the player

	void displayLife(); //Display life
	void displayCoins(); //Display wallet
	void shooting(); //handle the shooting
	void enemyMovement(); //enemies movement

	void mapMovement(); //map movement
	void mapright(); //map right
	void mapleft(); //map left

	void StructureUpdate(); //update structure
	void PlayerDown(); //player goes down

	void UpdateBoard(); //redraw the board

	int time; //time of the game

	mony head_insert_coin(mony h,int val,int x,int y);

	listenm0 head_insert_enemy0(listenm0 h,Enemy0 e, int val); //add one enemy type0
	listenm1 head_insert_enemy1(listenm1 h,Enemy1 e, int val); //add one enemy type1
	listenm2 head_insert_enemy2(listenm2 h,Enemy2 e, int val); //add one enemy type2
	listenm3 head_insert_enemy3(listenm3 h,Enemy3 e, int val); //add one enemy type3
	listenm4 head_insert_enemy4(listenm4 h,Enemy4 e, int val); //add one enemy type4
	listenm5 head_insert_enemy5(listenm5 h,Enemy5 e, int val); //add one enemy type5
	listenm6 head_insert_enemy6(listenm6 h,Enemy6 e, int val); //add one enemy type6
	listenm7 head_insert_enemy7(listenm7 h,Enemy7 e, int val); //add one enemy type7
	listenm8 head_insert_enemy8(listenm8 h,Enemy8 e, int val); //add one enemy type8
	listenm9 head_insert_enemy9(listenm9 h,Enemy9 e, int val); //add one enemy type9

	listenm0 obj_remove_enemy0(listenm0 h,int cod,bool head); //delete one enemy type0 (head == true, clean memory when delete an element in the head, otherwise not)
	listenm1 obj_remove_enemy1(listenm1 h,int cod,bool head); //delete one enemy type1 (head == true, clean memory when delete an element in the head, otherwise not)
	listenm2 obj_remove_enemy2(listenm2 h,int cod,bool head); //delete one enemy type2 (head == true, clean memory when delete an element in the head, otherwise not)
	listenm3 obj_remove_enemy3(listenm3 h,int cod,bool head); //delete one enemy type3 (head == true, clean memory when delete an element in the head, otherwise not)
	listenm4 obj_remove_enemy4(listenm4 h,int cod,bool head); //delete one enemy type4 (head == true, clean memory when delete an element in the head, otherwise not)
	listenm5 obj_remove_enemy5(listenm5 h,int cod,bool head); //delete one enemy type5 (head == true, clean memory when delete an element in the head, otherwise not)
	listenm6 obj_remove_enemy6(listenm6 h,int cod,bool head); //delete one enemy type6 (head == true, clean memory when delete an element in the head, otherwise not)
	listenm7 obj_remove_enemy7(listenm7 h,int cod,bool head); //delete one enemy type7 (head == true, clean memory when delete an element in the head, otherwise not)
	listenm8 obj_remove_enemy8(listenm8 h,int cod,bool head); //delete one enemy type8 (head == true, clean memory when delete an element in the head, otherwise not)
	listenm9 obj_remove_enemy9(listenm9 h,int cod,bool head); //delete one enemy type9 (head == true, clean memory when delete an element in the head, otherwise not)

	void initializeCoins(); //spawn of coins
	void updateCoins(); //check if one coin has to be removed
	mony removeCoins(mony h,int cod); //remove one coin
	mony FallCoins(mony h); //avoid coins on the air

	void initializeEnemies(); //initalize enemies
	bool enemydeath(bullt tmp); //enemy death

	bullt deletePlayerBullets(bullt tmp); //delete bullets of the Player
	bullt deleteEnemy6Bullets(bullt tmp,listenm6 e); //delete bullets of Enemy6
	bullt deleteEnemy7Bullets(bullt tmp,listenm7 e); //delete bullets of Enemy7
	bullt deleteEnemy8Bullets(bullt tmp,listenm8 e); //delete bullets of Enemy8
	bullt deleteEnemy9Bullets(bullt tmp,listenm9 e); //delete bullets of Enemy9

protected:

	Board board; //board

	Player player; //player

	listenm0 enemies0; //list of enemies type 0
	listenm1 enemies1; //list of enemies type 1
	listenm2 enemies2; //list of enemies type 2
	listenm3 enemies3; //list of enemies type 3
	listenm4 enemies4; //list of enemies type 4
	listenm5 enemies5; //list of enemies type 5
	listenm6 enemies6; //list of enemies type 6
	listenm7 enemies7; //list of enemies type 7
	listenm8 enemies8; //list of enemies type 8
	listenm9 enemies9; //list of enemies type 8

	mony coins;
	bool game_over;
};
