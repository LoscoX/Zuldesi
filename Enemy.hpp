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

    /**
     * Constructor with parameters.
     * @param y
     * @param x
     * @param c
     * @param mv
     */
	Enemy2(int y, int x, char c, int mv);
    /**
     * Default constructor.
     */
	Enemy2();
    /**
     * Change the movement direction.
     */
	void movement() override;
};


class Enemy3 : public Enemy0{
protected:
    /**
     * Counter for the jump's time.
     */
	int conta;
    /**
     * Jump parabola's direction.
     */
	int up;
public:
    /**
     * Constructor with parameters.
     * @param y
     * @param x
     * @param c
     * @param mv
     */
	Enemy3(int y, int x, char c, int mv);
    /**
     * Default constructor.
     */
	Enemy3();
    /**
     * Starts the jump.
     */
	void SetJump();
    /**
     * Change the movement direction.
     */
	void movement() override;
    /**
     *
     * @return conta value.
     */
	int GetConta();
};

class Enemy4 : public Enemy0{
protected:
	int conta;
public:
    /**
     * Constructor with parameters.
     * @param y
     * @param x
     * @param c
     * @param mv
     */
	Enemy4(int y, int x, char c, int mv);
    /**
     * Default constructor.
     */
	Enemy4();
    /**
     * Change the movement direction.
     */
	void movement() override;
};

class Enemy5 : public Enemy0{
public:
    /**
     * Constructor with parameters.
     * @param y
     * @param x
     * @param c
     * @param mv
     */
	Enemy5(int y, int x, char c, int mv);
    /**
     * Default constructor.
     */
	Enemy5();
    /**
     * Change the movement direction.
     * @param direction
     */
	void movement(int direction);
};

class Enemy6 : public Enemy0{
protected:
    /**
     *  Counter for one shot time.
     */
	int conta{};
    /**
     * List of bullet that you are using.
     */
	Bullet bullet;
    /**
     * Index for the list of bullet.
     */
	int ind{};
public:
    /**
     * Constructor with parameters.
     * @param y
     * @param x
     * @param c
     * @param mv
     */
	Enemy6(int y, int x, char c, int mv);
    /**
     * Default constructor.
     */
	Enemy6();
    /**
     * Change the movement direction.
     */
	void movement() override;
    /**
     * Take the bullet.
     * @return
     */
	Bullet getBullet();
    /**
     * Set bullet (remove one bullet).
     * @param tmp
     * @param cod
     * @return
     */
	bullt setBullet(bullt tmp,int cod);
    /**
     * Shooting.
     * @param tmp
     * @return
     */
	bullt Enemyshoot(bullt tmp);
};

class Enemy7 : public Enemy6{
public:
    /**
     * Constructor with parameters.
     * @param y
     * @param x
     * @param c
     * @param mv
     */
	Enemy7(int y, int x, char c, int mv);
    /**
     * Default constructor.
     */
	Enemy7();
    /**
     * Change the movement direction.
     * @param direction
     */
	void movement(int direction);
};

class Enemy8 : public Enemy6{
public:
    /**
     * Constructor with parameters.
     * @param y
     * @param x
     * @param c
     * @param mv
     */
	Enemy8(int y, int x, char c, int mv);
    /**
     * Default constructor.
     */
	Enemy8();
    /**
     * Change the movement direction.
     * @param direction
     */
	void movement(int direction);
};

class Enemy9 : public Enemy6{
public:
    /**
     * Constructor with parameters.
     * @param y
     * @param x
     * @param c
     * @param mv
     */
	Enemy9(int y, int x, char c, int mv);
    /**
     * Default constructor.
     */
	Enemy9();
    /**
     * Change the movement direction.
     */
	void movement() override;
};

