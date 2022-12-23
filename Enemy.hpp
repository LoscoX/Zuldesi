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


class Enemy{
private:
	int xMax,yMax; //coordinates of the box
	int segno = -1; //change the movement
	WINDOW * curwin;
public:
	int xLoc,yLoc; //coordinates of the enemy
	int color; //color for the enemy
	char character; //icon for the enemy
	int xpern,ypern; //coordinates for the movement of the enemy
	int cost; //radius of the movement
	int life; //life
	Enemy(WINDOW * win, int y, int x, char c,int mv,int col);
	Enemy();
	void initialize(); //start enemy
	void movement(int cost); //movement
	void display(); //see the enemy
	int getx(); //x coordinate of the enemy
	int gety(); //y coordinate of the enemy
	void injury();
	bool death();
};

/*
class EnemyBis : public Enemy{
public:
	EnemyBis(WINDOW * win, int y, int x, char c);
	EnemyBis();
	void movement();
};
*/
