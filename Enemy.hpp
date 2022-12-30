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
public:
	int xMax,yMax; //coordinates of the box
	WINDOW * curwin;
	int segno; //change the movement
	int xLoc,yLoc; //coordinates of the enemy
	int color; //color for the enemy
	char character; //icon for the enemy
	int xpern,ypern; //coordinates for the movement of the enemy
	int cost; //radius of the movement
	int life; //life
	Enemy0(WINDOW * win, int y, int x, char c,int mv,int col);
	Enemy0();
	void initialize(); //start enemy
	void movement(); //movement
	void display(); //see the enemy
	int getx(); //x coordinate of the enemy
	int gety(); //y coordinate of the enemy
	void injury();
	int getlife();
};

class Enemy1 : public Enemy0{
public:
	int conta; //time for the jump
	int step; //traslation of the vertex of parabola
	int xv; //xvertex of parabola
	int yv; //yvertex of parabola
	int a; //coefficients of degree 2 of parabola
	Enemy1(WINDOW * win, int y, int x, char c, int mv, int col);
	Enemy1();
	void movement(); //modify the movement
};

class Enemy2 : public Enemy0{
public:
	Enemy2(WINDOW * win, int y, int x, char c, int mv, int col);
	Enemy2();
	void movement(); //modify the movement
};


class Enemy3 : public Enemy0{
public:
	int conta; //time for the jump
	int step;
	Enemy3(WINDOW * win, int y, int x, char c, int mv, int col);
	Enemy3();
	void movement(); //modify the movement
};

class Enemy4 : public Enemy0{
public:
	int conta;
	Enemy4(WINDOW * win, int y, int x, char c, int mv, int col);
	Enemy4();
	void movement(); //modify the movement
};

class Enemy5 : public Enemy0{
public:
	Enemy5(WINDOW * win, int y, int x, char c, int mv, int col);
	Enemy5();
	void movement(int direction); //modify the movement
};

class Enemy6 : public Enemy0{
public:
	int conta; //time for one shot
	char gun; //character for the gun
	Enemy6(WINDOW * win, int y, int x, char c, int mv, int col);
	Enemy6();
	void movement(); //modify the movement
	void display(); //modify display for the gun
	Bullet bullet; //list of bullet that you are using
	int ind; //index for the list of bullet
};

class Enemy7 : public Enemy6{
public:
	Enemy7(WINDOW * win, int y, int x, char c, int mv, int col);
	Enemy7();
	void movement(int direction); //modify the movement
};

class Enemy8 : public Enemy6{
public:
	Enemy8(WINDOW * win, int y, int x, char c, int mv, int col);
	Enemy8();
	void movement(int direction); //modify the movement
};
