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
protected:
    /**
     * Player's icon.
     */
	char character[4]{};
	WINDOW * curwin{};
    /**
     * Lifepoints.
     */
	int life{};
    /**
     * Money.
     */
	int cash{};
    /**
     * Player coordinates position.
     */
	int xLoc{},yLoc{};
    /**
     * Coordinates of the box.
     */
	int xMax{},yMax{};
    /**
     * Save the direction of the movement.
     */
	int dir{};
    /**
     * Points of the player.
     */
	int points{};
	int jump_height{};
    /**
     * If it is true, you are jumping.
     */
	bool activejump{};
	int conta{};
	int segno{};
    /**
     * If you want to buy something.
     */
	bool buy{};

    /**
     * Power-ups.
     */

    /**
     * Gun type power-up.
     */
	Powerup gun;
    /**
     * Shield power-up.
     */
	Powerup shield;
    /**
     * HP Power-up.
     */
	Powerup hp;
    /**
     * Armor Power-up.
     */
	Powerup armor;
    /**
     * Teleport power-up.
     */
	Powerup teleportation;
    /**
     * Bullets power-up.
     */
	Powerup bullets;
    /**
     * Jump power-up.
     */
	Powerup jumping;
    /**
     * Fly power-up.
     */
	Powerup fly;
    /**
     * Explosive bullets power-up.
     */
	Powerup explo_bullets;

    /**
     * Constant for power-ups.
     */

    /**
     * Duration of the armor.
     */
	int ARMOR_DURATION[3]{};
    /**
     * Teleport distance.
     */
	int TELEPORT_DISTANCE[3]{};
    /**
     * Check if armor is activated.
     */
	bool ACTIVE_ARMOR{};
    /**
     * Armor time duration.
     */
	int ARMOR_ACTIVE_DURATION{};
    /**
     *  Quantity of bullets.
     */
	int NUM_BULLETS{};
    /**
     * Explosive bullets.
     */
	int NUM_EXPLO_BULLETS{};
    /**
     * Flight duration.
     */
	int FLY_DURATION{};
    /**
     * Fly time duration remains.
     */
	int FLY_ACTIVE_DURATION{};
    /**
     * Check if fly power-up is activated.
     */
	bool ACTIVE_FLY{};

    /**
     * Gun magazine.
     */

    /**
     * Bullets magazine.
     */
	Bullet bullet;
    /**
     * Explosive bullets magazine.
     */
	Bullet explo_bullet;
    /**
     * Bullets list index.
     */
	int ind{};
    /**
     * Explosive bullets list index.
     */
	int ind2{};
public:
	Player();
	Player(WINDOW * win, int y, int x);
    /**
     * Movement.
     */
	int getmv();
    /**
     * Jump.
     */
	void jump();
    /**
     * Shoot during the jump movement or the down movement.
     * @return
     */
	int airshoot();
    /**
     * Fall.
     */
	void godown();
	void goup(); //go up

	void display(); //see the player
	void initialize(); //start the player

	void injury(); //damage

	int getx(); //x coordinate of the player
	int gety(); //y coordinate of the player
	int getCoins(); //return coins of player
	int getDir(); //return dir of player
	int getPoints(); //points of the player
	int getLife(); //life of player
	bool getBuy(); //take buy variable
	void setBuy(bool val); //set buy variable

	void SetJump(); //restart the variable of jump

	void updatePoints(int points); //when you kill one enemy you take points
	void updateCash(int money); //update your wallet
	void updateCoordinates(int x,int y); //Update your x and y when you went in a not-possible place
	void setDir(int dir); //change direction
	void setLife(int val); //change life

	//bullets
	Bullet getBullet(); //bullets
	bullt setBullet(bullt tmp,int cod);
	Bullet getExploBullet(); //explosive bullets
	bullt setExploBullet(bullt tmp,int cod);
	bullt shoot(bullt tmp);
	bullt explo_shoot(bullt tmp);

	//get Powerups
	Powerup getGun(); //gun
	Powerup getShield(); //shield
	Powerup getHP(); //HP
	Powerup getArmor(); //Armor
	Powerup getTeleportation(); //teleport
	Powerup getBullets(); //bullets
	Powerup getJumping(); //jump
	Powerup getFly(); //fly
	Powerup getExplo_Bullets(); //explosive bullets

	//set Powerups
	void setGun(string g); //gun
	void setShield(int s); //shield
	void setHP(int h); //HP
	void setArmor(int a); //Armor
	void setTeleportation(int t); //teleport
	void setBullets(int b); //bullets
	void setJumping(int j); //jump
	void setFly(int f); //fly
	void setExplo_Bullets(int e); //explosive bullets

	bool getActiveFly(); //take active fly variable
	bool getActiveJump(); //take active jump variable
	int getTELEPORT_DISTANCE(int i); //take the variable i of the vector TELEPORT_DISTANCE
};
