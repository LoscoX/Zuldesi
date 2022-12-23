/*
 * Enemy.cpp
 *
 *  Created on: 8 dic 2022
 *      Author: david
 */

#include "Enemy.hpp"

Enemy::Enemy(WINDOW * win, int y, int x, char c, int mv,int col){
	curwin = win;
	yLoc = y;
	xLoc = x;
	getmaxyx(curwin,yMax,xMax);
	keypad(curwin,true);
	character = c;
	life = 10;
	xpern = x;
	ypern = y;
	cost = mv;
	color = col;
}

Enemy::Enemy(){
	curwin = newwin(0,0,0,0);
	yLoc = 0;
	xLoc = 0;
	getmaxyx(curwin,yMax,xMax);
	keypad(curwin,true);
	character = '0';
	life = 10;
	xpern = 0;
	ypern = 0;
	cost = 0;
	color = 0;
}

void Enemy::initialize(){
	display();
}

void Enemy::display(){ //display the character
	wattron(curwin,COLOR_PAIR(Enemy::color));
	mvwaddch(curwin,yLoc,xLoc,character);
	wattroff(curwin,COLOR_PAIR(Enemy::color));
}

void Enemy::movement(int cost){
	mvwaddch(curwin, yLoc, xLoc, ' '); //Delete previous character
	xLoc = xLoc + segno; //implement the movement
	if(xLoc > xMax - 2){ //reach the max
		xLoc = xMax - 2;
		segno = segno * (-1); //change the direction of the movement
	}
	else if(xLoc < 1){ //reach the minimum
		xLoc = 1;
		segno = segno * (-1);
	}
	else if(xLoc > xpern + cost){
		xLoc = xpern + cost;
		segno = segno * (-1);
	}
	else if(xLoc < xpern - cost){
		xLoc = xpern - cost;
		segno = segno * (-1);
	}
}

int Enemy::getx(){
	return xLoc;
}

int Enemy::gety(){
	return yLoc;
}

void Enemy::injury(){ //Injury
	life = life - 1;
}

bool Enemy::death(){
	if(life<=0) return true;
	else return false;
}
/*
EnemyBis::EnemyBis(WINDOW * win, int y, int x, char c) : Enemy(win,y,x,c){
	life = 12;
}

EnemyBis::EnemyBis() : Enemy(){
	character = '1';
	life = 10;
}
*/

