/*
 * Enemy.cpp
 *
 *  Created on: 8 dic 2022
 *      Author: david
 */

#include "Enemy.hpp"


/*List of enemies
First type
0- sin movement (life = 5). There is a costant (mv) which determines the radius of the oscillation
1- fixed jump (life = 7). There is a constant (mv) which determines the height of the jump
2- fixed lift (life = 7). There is a constant (mv) which determines the max height for the lifting
3- No fixed jump (life = 2). There is a constant (mv) which determines the height of the jump but the jump is dinamic
4- random movement (life = 3). Random movement in a constant neighborhood (mv)
5- smart movement (life = 2). It follows the player
*/

//Enemy type 0

Enemy0::Enemy0(WINDOW * win, int y, int x, char c, int mv,int col){
	curwin = win;
	yLoc = y;
	xLoc = x;
	getmaxyx(curwin,yMax,xMax);
	keypad(curwin,true);
	character = c;
	life = 5;
	xpern = x; //save coordinates
	ypern = y; //save coordinates
	cost = mv;
	color = col;
}

Enemy0::Enemy0(){
	curwin = newwin(0,0,0,0);
	yLoc = 0;
	xLoc = 0;
	getmaxyx(curwin,yMax,xMax);
	keypad(curwin,true);
	character = '0'; //graphic icon
	life = 5;
	xpern = 0;
	ypern = 0;
	cost = 0;
	color = 1;
}

void Enemy0::initialize(){
	display();
}

void Enemy0::display(){ //display the character
	wattron(curwin,COLOR_PAIR(Enemy0::color)); //color
	mvwaddch(curwin,yLoc,xLoc,character);
	wattroff(curwin,COLOR_PAIR(Enemy0::color));
	napms(4); //It is the number of milliseconds to sleep. (increments the speed of characters) 4 It's a good comromise
}

void Enemy0::movement(){
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
	else if(xLoc > xpern + cost){ //reach the max of radius
		xLoc = xpern + cost;
		segno = segno * (-1);
	}
	else if(xLoc < xpern - cost){ //reach the min of radius
		xLoc = xpern - cost;
		segno = segno * (-1);
	}
}

int Enemy0::getx(){
	return xLoc;
}

int Enemy0::gety(){
	return yLoc;
}

void Enemy0::injury(){ //Injury
	life = life - 1;
}

bool Enemy0::death(){ //Death Enemy
	if(life<=0) return true;
	else return false;
}

//Enemy type 1

Enemy1::Enemy1(WINDOW * win, int y, int x, char c,int mv, int col) : Enemy0(win,y,x,c,mv,col){
	life = 7;
	conta = 0;
	step = int(sqrt(cost));
	xv = xpern - step; //xvertex of parabola
	yv = ypern - cost; //yvertex of parabola
	a = (ypern-yv)/((xpern-xv)*(xpern-xv)); //coefficients of degree 2 of parabola
}

Enemy1::Enemy1() : Enemy0(){
	character = '1';
	life = 7;
	color = 2;
	conta = 0;
	step = 0;
	xv = 0; //xvertex of parabola
	yv = 0; //yvertex of parabola
	a = 1; //coefficients of degree 2 of parabola
}

void Enemy1::movement(){
	if(conta < 2*step + 1){ //if you want to do all parabola
		mvwaddch(curwin, yLoc, xLoc,' '); //Delete previous character
		xLoc = xpern - conta;
		conta = conta + 1;
		yLoc = a * (xLoc-xv) * (xLoc-xv) + yv; //parabola equation
		if(xLoc > xpern || xLoc < xpern) xLoc = xpern; //fix the x
	}
	else conta = 0;
}

//Enemy type 2

Enemy2::Enemy2(WINDOW * win, int y, int x, char c,int mv, int col) : Enemy0(win,y,x,c,mv,col){
	life = 7;
}

Enemy2::Enemy2() : Enemy0(){
	character = '2';
	life = 7;
	color = 3;
}

void Enemy2::movement(){
	mvwaddch(curwin, yLoc, xLoc,' '); //Delete previous character
	yLoc = yLoc + segno;
	if(yLoc < yMax - 2 - cost){
		yLoc = yMax - 2 - cost;
		segno = segno * (-1);
	}
	else if(yLoc > yMax - 2){
		yLoc = yMax - 2;
		segno = segno * (-1);
	}
}

//Enemy type 3

Enemy3::Enemy3(WINDOW * win, int y, int x, char c,int mv, int col) : Enemy0(win,y,x,c,mv,col){
	life = 2;
	step = int(sqrt(cost));
	conta = 0;
}

Enemy3::Enemy3() : Enemy0(){
	character = '3';
	life = 2;
	color = 4;
	step = 0;
	conta = 0;
}

void Enemy3::movement(){ //remember that
	mvwaddch(curwin, yLoc, xLoc,' '); //Delete previous character
	if(xLoc == xMax - 2 && yLoc == yMax-2){
		segno = segno*(-1); //you have to change the direction
		xpern = xMax - 2;
	}
	else if(xLoc == 1 && yLoc == yMax-2){
		segno = segno*(-1); //you have to change the direction
		xpern = 1;
	}
	int xv = xpern + step*segno; //xvertex of parabola
	int yv = ypern - cost; //yvertex of parabola
	int a = (ypern-yv)/((xpern-xv)*(xpern-xv)); //coefficients of degree 2 of parabola
	if(conta < 2*step + 1){ //if you want to do the whole jump
		xLoc = xpern + segno * conta;
		conta = conta + 1;
		yLoc = a * (xLoc-xv) * (xLoc-xv) + yv; //parabola equation
		if(xLoc < 1){
			xLoc = 1; //reach minimum
		}
		if(xLoc > xMax-2){
			xLoc = xMax - 2; //reach maximum
		}
	}
	else{
		conta = 0;
		xpern = xpern + 2*step * segno;//we have to move data of parabola (simulate dinamic jump)
	}
}


//Enemy type 4

Enemy4::Enemy4(WINDOW * win, int y, int x, char c,int mv, int col) : Enemy0(win,y,x,c,mv,col){
	life = 3;
	conta = 0; //handle the delay of the movement
}

Enemy4::Enemy4() : Enemy0(){
	character = '4';
	life = 3;
	color = 5;
	conta = 0; //handle the delay of the movement
}

void Enemy4::movement(){
	conta++;
	if(conta == 8){ //delay (bigger-->easier)
		mvwaddch(curwin, yLoc, xLoc,' '); //Delete previous character
		xLoc = (xpern - cost) + rand()%(2*cost+1); //generate a random number between xpen-cost and xpern+cost
		if (xLoc < 1) xLoc = 1; //avoid spawn out of the map
		if (xLoc > xMax - 2) xLoc = xMax - 2; //avoid spawn out of the map
		conta = 0;
	}
}

//Enemy type 5

Enemy5::Enemy5(WINDOW * win, int y, int x, char c,int mv, int col) : Enemy0(win,y,x,c,mv,col){
	life = 2;
}

Enemy5::Enemy5() : Enemy0(){
	character = '5';
	life = 2;
	color = 6;
}

void Enemy5::movement(int direction){
	mvwaddch(curwin, yLoc, xLoc,' '); //Delete previous character
	xLoc = xLoc + direction; //direction = 1-->dx   direction = -1-->sx
}
