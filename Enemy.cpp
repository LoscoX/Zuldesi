/*
 * Enemy.cpp
 *
 *  Created on: 8 dic 2022
 *      Author: david
 */

#include "Enemy.hpp"


/*List of enemies
No gun type
	0- sin movement (life = 5). There is a costant (mv) which determines the radius of the oscillation
	1- sin movement with lift (life = 7). There is a constant (mv) which determines the height for the lifting
	2- fixed lift (life = 7). There is a constant (mv) which determines the max height for the lifting
	3- No fixed jump (life = 2). There is a constant (mv) which determines the height of the jump but the jump is dinamic
	4- random movement (life = 3). Random movement in a constant neighborhood (mv)
	5- smart movement (life = 2). It follows the player when it is sufficiently near to the enemy
Gun type (If you touch them, nothing happens)
	6- It's the enemy type0 but with gun
	7- It's the enemy type5 but with gun
	8- Enemy can't move but he can shoot, when the player reaches a specific place
	9- Is's the enemy type2 but with two guns
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
	segno = -1;
}

Enemy0::Enemy0(){ //default constructor
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
	segno = -1;
}

//Enemy0::~Enemy0(){};

void Enemy0::initialize(){
	display();
}

void Enemy0::display(){ //display the character
	wattron(curwin,COLOR_PAIR(Enemy0::color)); //color
	mvwaddch(curwin,yLoc,xLoc,character);
	wattroff(curwin,COLOR_PAIR(Enemy0::color));
}

void Enemy0::movement(){
	mvwaddch(curwin, yLoc, xLoc, ' '); //Delete previous character
	Enemy0::updateCoordinates(segno,0); //implement the movement
	/*if(xLoc > xMax - 2){ //reach the max
		xLoc = xMax - 2;
		Enemy0::setSign(); //change the direction of the movement
	}
	else if(xLoc < 1){ //reach the minimum
		xLoc = 1;
		Enemy0::setSign(); //change the direction of the movement
	}
	else*/ if(xLoc > xpern + cost){ //reach the max of radius
		xLoc = xpern + cost;
		Enemy0::setSign(); //change the direction of the movement
	}
	else if(xLoc < xpern - cost){ //reach the min of radius
		xLoc = xpern - cost;
		Enemy0::setSign(); //change the direction of the movement
	}
}

void Enemy0::EnemyGoDown(){ //go down
	mvwaddch(curwin, yLoc, xLoc,' ');
	yLoc = yLoc + 1; //Enemy is falling
}

int Enemy0::getx(){ //Take x
	return xLoc;
}

int Enemy0::gety(){
	return yLoc;
}

void Enemy0::injury(){ //Injury
	life = life - 1;
}

int Enemy0::getLife(){
	return life;
}

int Enemy0::getSign(){
	return segno;
}

void Enemy0::setSign(){
	segno = segno * (-1); //change sign
}
int Enemy0::getXpern()
{
	return xpern;
}

void Enemy0::setXpern(int x)
{
	xpern=x;
}



void Enemy0::updateCoordinates(int x,int y){ //update coordinates
	xLoc = xLoc+x;
	yLoc = yLoc+y;
}

//Enemy type 1

Enemy1::Enemy1(WINDOW * win, int y, int x, char c,int mv, int col) : Enemy0(win,y,x,c,mv,col){
	life = 7;
	up = -1;
}

Enemy1::Enemy1() : Enemy0(){ //default constructor
	character = '1';
	life = 7;
	color = 2;
	up = -1;
}

void Enemy1::movement(){
	mvwaddch(curwin, yLoc, xLoc, ' '); //Delete previous character
	Enemy0::updateCoordinates(segno,0); //update coordinates
	/*if(xLoc > xMax - 2){ //reach the max
		xLoc = xMax - 2;
		Enemy0::setSign(); //change the direction of the movement
	}
	else if(xLoc < 1){ //reach the minimum
		xLoc = 1;
		Enemy0::setSign(); //change the direction of the movement
	}
	else*/ if(xLoc > xpern + cost){ //reach the max of radius
		yLoc = yLoc + up; //go up
		xLoc = xpern + cost;
		Enemy0::setSign(); //change the direction of the movement
	}
	else if(xLoc < xpern - cost){ //reach the min of radius
		yLoc = yLoc + up; //go up
		xLoc = xpern - cost;
		Enemy0::setSign(); //change the direction of the movement
	}
	if(yLoc < yMax - 2 - cost){ //lifting depends from cost
		yLoc = yMax - 2 - cost;
		Enemy1::setUp(); //change the direction of the lifting
	}
	else if(yLoc > yMax - 2){
		yLoc = yMax - 2;
		Enemy1::setUp(); //change the direction of the lifting
	}
}

void Enemy1::setUp(){
	up = up * (-1);
}

int Enemy1::getUp(){
	return up;
}

bool Enemy1::ReachAngles(){
	if(xLoc == xpern + cost || xLoc == xpern - cost) return true;
	else return false;
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
	Enemy0::updateCoordinates(0,segno);
	if(yLoc < yMax - 2 - cost){ //lifting depends from cost
		yLoc = yMax - 2 - cost;
		Enemy0::setSign(); //change the direction of the lifting
	}
	else if(yLoc > yMax - 2){
		yLoc = yMax - 2;
		Enemy0::setSign(); //change the direction of the lifting
	}
}

//Enemy type 3

Enemy3::Enemy3(WINDOW * win, int y, int x, char c,int mv, int col) : Enemy0(win,y,x,c,mv,col){
	life = 2;
	conta = 1;
	up = -1;
}

Enemy3::Enemy3() : Enemy0(){
	character = '3';
	life = 2;
	color = 4;
	conta = 1;
	up = -1;
}

void Enemy3::movement(){
	mvwaddch(curwin, yLoc, xLoc,' '); //Delete previous character
	if(conta<=16){
		if(conta == 9)up = 1; //go down
		yLoc = yLoc + up;
		if(conta%2==0)xLoc = xLoc + segno; //go to the next point
		conta++;
		/*if(xLoc>xMax-2){ //if you reach the wall
			Enemy0::setSign(); //you have to change direction
			Enemy3::SetJump(); //Set to zero variable of the jump
			xLoc = xMax-2; //fix the x
			while(yLoc>yMax-2)EnemyGoDown(); //go down
		}
		else if(xLoc<1){ //if you reach the wall
			Enemy0::setSign(); //you have to change direction
			Enemy3::SetJump(); //Set to zero variable of the jump
			xLoc = 1; //fix the x
			while(yLoc>yMax-2)EnemyGoDown(); //go down
		}
		else*/ if(yLoc<1){
			yLoc = 1;
			while(yLoc>yMax-2)EnemyGoDown(); //go down
		}
	}
	else Enemy3::SetJump(); //Set to zero variable of the jump
}

void Enemy3::SetJump(){
	conta = 0;
	up = -1;
}

int Enemy3::GetConta(){
	return conta;
}

//Enemy type 4

Enemy4::Enemy4(WINDOW * win, int y, int x, char c,int mv, int col) : Enemy0(win,y,x,c,mv,col){
	life = 3;
	conta = 0; //handle delay of the movement
}

Enemy4::Enemy4() : Enemy0(){
	character = '4';
	life = 3;
	color = 5;
	conta = 0; //handle delay of the movement
}

void Enemy4::movement(){
	conta++;
	if(conta == 8){ //delay (bigger-->easier)
		mvwaddch(curwin, yLoc, xLoc,' '); //Delete previous character
		xLoc = (xpern - cost) + rand()%(2*cost+1); //generate a random number between xpen-cost and xpern+cost
		//if (xLoc < 1) xLoc = 1; //avoid spawn out of the map
		//if (xLoc > xMax - 2) xLoc = xMax - 2; //avoid spawn out of the map
		conta = 0; //time starts again
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
	mvwaddch(curwin, yLoc, xLoc,' ');
	Enemy0::updateCoordinates(direction, 0); //Delete previous character//direction = 1-->dx   direction = -1-->sx
}

//Enemy type 6

Enemy6::Enemy6(WINDOW * win, int y, int x, char c,int mv, int col) : Enemy0(win,y,x,c,mv,col){
	life = 5;
	bullet = Bullet(curwin); //initialize the bullet
	ind = 0; //no bullet
	conta = 0; //no shots
	gun = '-'; //gun
}

Enemy6::Enemy6() : Enemy0(){
	character = '0';
	color = 1;
	life = 5;
	bullet = Bullet(curwin); //initialize the bullet
	ind = 0; //no bullet
	conta = 0; //no shots
	gun = '-';
}

void Enemy6::display(){
	wattron(curwin,COLOR_PAIR(Enemy6::color)); //color
	mvwaddch(curwin,yLoc,xLoc,character);
	if(segno == 1) mvwaddch(curwin,yLoc,xLoc+1,gun); //create the gun, dx when enemy goes to dx
	else mvwaddch(curwin,yLoc,xLoc-1,gun); //create the gun, sx when enemy goes to sx
	wattroff(curwin,COLOR_PAIR(Enemy6::color));
}

void Enemy6::movement(){
	conta++; //increment time for the shot
	mvwaddch(curwin, yLoc, xLoc, ' '); //Delete previous character
	if(segno == 1) mvwaddch(curwin,yLoc,xLoc+1,' '); //delete the gun, dx when enemy goes to dx
	else mvwaddch(curwin,yLoc,xLoc-1,' '); //delete the gun, sx when enemy goes to sx
	Enemy0::updateCoordinates(segno,0); //implement the movement
	/*if(xLoc > xMax - 3){ //reach the max (Pay attention,there is the gun)
		xLoc = xMax - 3;
		Enemy0::setSign(); //change the direction of the movement
	}
	else if(xLoc < 2){ //reach the minimum (Pay attention,there is the gun)
		xLoc = 2;
		Enemy0::setSign();
	}
	else*/ if(xLoc > xpern + cost){ //reach the max of radius
		xLoc = xpern + cost;
		Enemy0::setSign();
	}
	else if(xLoc < xpern - cost){ //reach the min of radius
		xLoc = xpern - cost;
		Enemy0::setSign();
	}
	if(conta==10){ //every 10 seconds, the enemy fires
		bullet.blt = bullet.head_insert(bullet.blt,segno,xLoc,yLoc,ind); //add the bullet
		ind = ind + 1; //we want different indexes for the different bullets
		conta = 0;
	}
}

//Enemy type7

Enemy7::Enemy7(WINDOW * win, int y, int x, char c,int mv, int col) : Enemy6(win,y,x,c,mv,col){
	life = 5;
	bullet = Bullet(curwin); //initialize the bullet
	ind = 0; //no bullet
	conta = 0; //no shots
	gun = '-'; //gun
}

Enemy7::Enemy7() : Enemy6(){
	character = '5'; //It's the enemy type5 but with the gun
	life = 5;
	bullet = Bullet(curwin); //initialize the bullet
	ind = 0; //no bullet
	conta = 0; //no shots
	gun = '-';
}

void Enemy7::movement(int direction){
	conta++; //increment time for the shot
	mvwaddch(curwin, yLoc, xLoc,' '); //Delete previous character
	if(segno == 1) mvwaddch(curwin,yLoc,xLoc+1,' '); //delete the gun, dx when enemy goes to dx
	else mvwaddch(curwin,yLoc,xLoc-1,' '); //delete the gun, sx when enemy goes to sx
	segno = direction; //update direction of enemy
	Enemy0::updateCoordinates(segno,0); //direction = 1-->dx   direction = -1-->sx
	if(conta==10){ //every 10 seconds, the enemy fires
		bullet.blt = bullet.head_insert(bullet.blt,segno,xLoc,yLoc,ind); //add the bullet
		ind = ind + 1; //we want different indexes for the different bullets
		conta = 0;
	}
}

//Enemy type8

Enemy8::Enemy8(WINDOW * win, int y, int x, char c,int mv, int col) : Enemy6(win,y,x,c,mv,col){
	life = 5;
	bullet = Bullet(curwin); //initialize the bullet
	ind = 0; //no bullet
	conta = 0; //no shots
	gun = '-'; //gun
}

Enemy8::Enemy8() : Enemy6(){
	character = '7';
	life = 5;
	bullet = Bullet(curwin); //initialize the bullet
	ind = 0; //no bullet
	conta = 0; //no shots
	gun = '-';
}

void Enemy8::movement(int direction){
	conta++; //increment time for the shot
	mvwaddch(curwin, yLoc, xLoc,' '); //Delete previous character
	if(segno == 1) mvwaddch(curwin,yLoc,xLoc+1,' '); //delete the gun, dx when enemy goes to dx
	else mvwaddch(curwin,yLoc,xLoc-1,' '); //delete the gun, sx when enemy goes to sx
	segno = direction; //update direction of enemy
	if(conta==5){ //every 5 seconds, the enemy fires
		bullet.blt = bullet.head_insert(bullet.blt,segno,xLoc,yLoc,ind); //add the bullet
		ind = ind + 1; //we want different indexes for the different bullets
		conta = 0;
	}
}

//Enemy type9

Enemy9::Enemy9(WINDOW * win, int y, int x, char c,int mv, int col) : Enemy6(win,y,x,c,mv,col){
	life = 5;
	bullet = Bullet(curwin); //initialize the bullet
	ind = 0; //no bullet
	conta = 0; //no shots
	gun = '-'; //gun
}

Enemy9::Enemy9() : Enemy6(){
	character = '2'; //It's the enemy type2 but with two guns
	life = 5;
	bullet = Bullet(curwin); //initialize the bullet
	ind = 0; //no bullet
	conta = 0; //no shots
	gun = '-';
}

void Enemy9::movement(){
	conta++; //increment time for the shot
	mvwaddch(curwin, yLoc, xLoc,' '); //Delete previous character
	mvwaddch(curwin, yLoc, xLoc+1,' '); //Delete the first gun
	mvwaddch(curwin, yLoc, xLoc-1,' '); //Delete the second gun
	Enemy0::updateCoordinates(0,segno);
	if(yLoc < yMax - 2 - cost){ //lifting depends from cost
		yLoc = yMax - 2 - cost;
		Enemy0::setSign(); //change the direction of the lifting
	}
	else if(yLoc > yMax - 2){
		yLoc = yMax - 2;
		Enemy0::setSign(); //change the direction of the lifting
	}
	if(conta==5){ //every 5 seconds, the enemy fires two bullets in opposite directions
		bullet.blt = bullet.head_insert(bullet.blt,segno,xLoc,yLoc,ind); //add the bullet
		ind = ind + 1; //we want different indexes for the different bullets
		bullet.blt = bullet.head_insert(bullet.blt,-segno,xLoc,yLoc,ind); //add the bullet
		ind = ind + 1;
		conta = 0;
	}
}

void Enemy9::display(){
	wattron(curwin,COLOR_PAIR(Enemy6::color)); //color
	mvwaddch(curwin,yLoc,xLoc,character);
	mvwaddch(curwin,yLoc,xLoc+1,gun); //create the dx gun
	mvwaddch(curwin,yLoc,xLoc-1,gun); //create the sx gun
	wattroff(curwin,COLOR_PAIR(Enemy6::color));
}