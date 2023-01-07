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
	int segno; //change the movement
	int xLoc,yLoc; //coordinates of the enemy
	int life; //life
	int color; //color for the enemy
	char character; //icon for the enemy
	int xpern,ypern; //coordinates for the movement of the enemy
	int cost; //radius of the movement
public:
	Enemy0(int y, int x, char c,int mv,int col);
	Enemy0();
	void movement(); //movement
	void EnemyGoDown(); //fall
	int getx(); //x coordinate of the enemy
	int gety(); //y coordinate of the enemy
	int getLife(); //enemy life
	int getSign(); //enemy segn
	char getChar(); //enemy symbol
	int getColor(); //color of enemy
	void setSign(); //change enemy sign
	void updateCoordinates(int x,int y); //update coordinates of enemy
	int getXpern(); //take xpern
	void setXpern(int x); //change xpern
	void setLife(int life); //change life
	void injury(); //damage
};

class Enemy1 : public Enemy0{
protected:
	int up; //direction of the lifting
public:
	Enemy1(int y, int x, char c, int mv, int col);
	Enemy1();
	void movement(); //modify the movement
	void setUp(); //change the direction of the lifting
	int getUp(); //take the direction of the lifting
	bool ReachAngles(); //reach one of the two limits of the sin movement, you must go up (or down)
};

class Enemy2 : public Enemy0{
public:
	Enemy2(int y, int x, char c, int mv, int col);
	Enemy2();
	void movement(); //modify the movement
};


class Enemy3 : public Enemy0{
protected:
	int conta; //time for the jump
	int up; //direction of the parabola
public:
	Enemy3(int y, int x, char c, int mv, int col);
	Enemy3();
	void SetJump(); //starts the jump
	void movement(); //modify the movement
	int GetConta(); //take conta
};

class Enemy4 : public Enemy0{
protected:
	int conta;
public:
	Enemy4(int y, int x, char c, int mv, int col);
	Enemy4();
	void movement(); //modify the movement
};

class Enemy5 : public Enemy0{
public:
	Enemy5(int y, int x, char c, int mv, int col);
	Enemy5();
	void movement(int direction); //modify the movement
};

class Enemy6 : public Enemy0{
protected:
	int conta; //time for one shot
	char gun; //character for the gun
public:
	Enemy6(int y, int x, char c, int mv, int col);
	Enemy6();
	void movement(); //modify the movement
	Bullet bullet; //list of bullet that you are using
	int ind; //index for the list of bullet
};

class Enemy7 : public Enemy6{
public:
	Enemy7(int y, int x, char c, int mv, int col);
	Enemy7();
	void movement(int direction); //modify the movement
};

class Enemy8 : public Enemy6{
public:
	Enemy8(int y, int x, char c, int mv, int col);
	Enemy8();
	void movement(int direction); //modify the movement
};

class Enemy9 : public Enemy6{
public:
	Enemy9(int y, int x, char c, int mv, int col);
	Enemy9();
	void movement(); //modify the movement
};
