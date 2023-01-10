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
    /**
     * Go up.
     */
	void goup();
    /**
     * See the player.
     */
	void display();
    /**
     * Start the player.
     */
	void initialize();

    /**
     * Damage.
     */
	void injury();
    /**
     * X coordinate of the player.
     * @return
     */
	int getx();
    /**
     * y coordinate of the player.
     * @return
     */
	int gety();
    /**
     *
     * @return coins of player.
     */
	int getCoins();
    /**
     *
     * @return dir of player.
     */
	int getDir();
    /**
     * Points of the player.
     * @return
     */
	int getPoints();
    /**
     * Life of player.
     * @return
     */
	int getLife();
    /**
     * Take buy variable.
     * @return
     */
	bool getBuy();
    /**
     * Set buy variable.
     * @param val
     */
	void setBuy(bool val);

    /**
     * Reset jump variable.
     */
	void SetJump();

    /**
     * When you kill one enemy you take points.
     * @param points
     */
	void updatePoints(int points);
    /**
     * Update your wallet.
     * @param money
     */
	void updateCash(int money);
    /**
     * Update your x and y when you went in a not-possible place.
     * @param x
     * @param y
     */
	void updateCoordinates(int x,int y);
    /**
     * Change direction.
     * @param dir
     */
	void setDir(int dir);

    /**
     * bullets.
     */
    /**
     *
     * @return bullets.
     */
	Bullet getBullet();
    /**
     * Set bullets.
     * @param tmp
     * @param cod
     * @return
     */
	bullt setBullet(bullt tmp,int cod);
    /**
     *
     * @return explosive bullets.
     */
	Bullet getExploBullet();
    /**
     *
     * @param tmp
     * @param cod
     * @return
     */
	bullt setExploBullet(bullt tmp,int cod);
	bullt shoot(bullt tmp);
    /**
     *
     * @param tmp
     * @return
     */
	bullt explo_shoot(bullt tmp);

    /**
     * Get power-ups.
     */

    /**
     *
     * @return Gun.
     */
	Powerup getGun();
    /**
     *
     * @return Shield.
     */
	Powerup getShield();
    /**
     *
     * @return HP.
     */
	Powerup getHP();
    /**
     *
     * @return Armor.
     */
	Powerup getArmor();
    /**
     *
     * @return Teleport.
     */
	Powerup getTeleportation();
    /**
     *
     * @return Bullets.
     */
	Powerup getBullets();
    /**
     *
     * @return Jump.
     */
	Powerup getJumping();
    /**
     *
     * @return Fly.
     */
	Powerup getFly();
    /**
     *
     * @return explosive bullets.
     */
	Powerup getExplo_Bullets();


    /**
     * Set power-ups.
     */

    /**
     * Set Gun.
     * @param g
     */
	void setGun(string g);
    /**
     * Set Shield.
     * @param s
     */
	void setShield(int s);
    /**
     * Set HP.
     * @param h
     */
	void setHP(int h);
    /**
     * Set armor.
     * @param a
     */
	void setArmor(int a);
    /**
     * Set teleport.
     * @param t
     */
	void setTeleportation(int t);
    /**
     * Set bullets.
     * @param b
     */
	void setBullets(int b);
    /**
     * Set jump.
     * @param j
     */
	void setJumping(int j);
    /**
     * Set fly.
     * @param f
     */
	void setFly(int f);
    /**
     * Set explosive bullets.
     * @param e
     */
	void setExplo_Bullets(int e);

    /**
     * Take active fly variable.
     * @return
     */
	bool getActiveFly();
    /**
     * Set active fly variable.
     * @param val
     */
	void setActiveFly(bool val);
    /**
     * Take active jump variable.
     * @return
     */
	bool getActiveJump();
    /**
     * take the input parameter of the vector TELEPORT_DISTANCE
     * @param i
     * @return
     */
	int getTELEPORT_DISTANCE(int i);
    /**
     * Take fly duration.
     * @return
     */
	int getFlyActiveDuration();
    /**
     * Set fly duration.
     * @param val
     */
	void setFlyActiveDuration(int val);
};
