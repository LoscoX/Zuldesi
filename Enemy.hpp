/*
 * Enemy.hpp
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

#include "Player.hpp" //take information about bullets and player

class Enemy0{
protected:
    /**
     * Change the movement.
     */
	int segno;
    /**
     * Coordinates of the enemy.
     */
	int xLoc,yLoc;
    /**
     * Life.
     */
	int life;
    /**
     * Icon for the enemy.
     */
	char character;
    /**
     * Coordinates for the movement of the enemy.
     */
	int xpern,ypern;
    /**
     * Radius of the movement.
     */
	int cost;
public:

    /**
     * Constructor with coordinates.
     * @param y
     * @param x
     * @param c
     * @param mv
     */
	Enemy0(int y, int x, char c,int mv);
    /**
     * Default constractor.
     */
	Enemy0();

    virtual /**
     * Manage enemy movement.
     */
	void movement();
    /**
     * Manage enemy's gravity.
     */
	void EnemyGoDown();
    /**
     *
     * @return x coordinate of the enemy.
     */
	int getx();
    /**
     *
     * @return y coordinate of the enemy.
     */
	int gety();
    /**
     *
     * @return Enemy life.
     */
	int getLife();
    /**
     *
     * @return Enemy's sign.
     */
	int getSign();

    /**
     *
     * @return Enemy's graphic displayed symbol.
     */
	char getChar();
    /**
     * Change enemy's sign.
     */
	void setSign();
    /**
     * Update coordinates of the enemy.
     * @param x
     * @param y
     */
	void updateCoordinates(int x,int y);
    /**
     *  Change life value.
     * @param life
     */
	void setLife(int life);
    /**
     * give damage to the enemy.
     */
	void injury();
};

class Enemy1 : public Enemy0{
protected:
    /**
     * Direction of the lifting.
     */
	int up;
public:
    /**
     * Constructor with coordinates.
     * @param y
     * @param x
     * @param c
     * @param mv
     */
	Enemy1(int y, int x, char c, int mv);
    /**
     * Default constructor.
     */
	Enemy1();
    /**
     * Edit the movement.
     */
	void movement() override;
    /**
     * Change the direction of the lifting.
     */
	void setUp();
    /**
     *
     * @return Lifting's direction.
     */
	int getUp();
    /**
     * Reach one of the two limits of the sin movement, you must go up (or down).
     * @return
     */
	bool ReachAngles();
};

class Enemy2 : public Enemy0{
public:
	Enemy2(int y, int x, char c, int mv);
	Enemy2();
	void movement() override; //modify the movement
};


class Enemy3 : public Enemy0{
protected:
	int conta; //time for the jump
	int up; //direction of the parabola
public:
	Enemy3(int y, int x, char c, int mv);
	Enemy3();
	void SetJump(); //starts the jump
	void movement() override; //modify the movement
	int GetConta(); //take conta
};

class Enemy4 : public Enemy0{
protected:
	int conta;
public:
	Enemy4(int y, int x, char c, int mv);
	Enemy4();
	void movement() override; //modify the movement
};

class Enemy5 : public Enemy0{
public:
	Enemy5(int y, int x, char c, int mv);
	Enemy5();
	void movement(int direction); //modify the movement
};

class Enemy6 : public Enemy0{
protected:
	int conta; //time for one shot
	char gun; //character for the gun
	Bullet bullet; //list of bullet that you are using
	int ind; //index for the list of bullet
public:
	Enemy6(int y, int x, char c, int mv);
	Enemy6();
	void movement() override; //modify the movement
	Bullet getBullet(); //take bullet
	bullt setBullet(bullt tmp,int cod); //set bullet(remove one bullet)
	bullt Enemyshoot(bullt tmp); //shooting
};

class Enemy7 : public Enemy6{
public:
	Enemy7(int y, int x, char c, int mv);
	Enemy7();
	void movement(int direction); //modify the movement
};

class Enemy8 : public Enemy6{
public:
	Enemy8(int y, int x, char c, int mv);
	Enemy8();
	void movement(int direction); //modify the movement
};

class Enemy9 : public Enemy6{
public:
	Enemy9(int y, int x, char c, int mv);
	Enemy9();
	void movement() override; //modify the movement
};

