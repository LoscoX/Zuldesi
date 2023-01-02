/*
 * Player.cpp
 *
 *  Created on: 8 dic 2022
 *      Author: david
 */

#include "Player.hpp"

Player::Player(WINDOW * win, int y, int x){
	yLoc = y;
	xLoc = x;
	curwin = win;
	getmaxyx(curwin,yMax,xMax);
	keypad(curwin,true);
	character[0] = '@';
	character[1] = '^';
	life = 99;
	cash = 0;
	dir = 1; //initial direction
	bullet = Bullet(curwin); //initialize the bullet
	ind = 0; //no bullet
	//jump
	activejump = false; //start without jump
	xpern = xLoc; //save medium point for the jump
	ypern = yLoc; //save medium point for the jump
	conta = 0;
	//powerup
	strcpy(typeofgun,"none"); //no gun when you start
	shield = false; //no shield when you start
	shield_life = 0;
	teleportation = false; //you cannot teleport when you start
	time_life_armor = 0; //life of the armor (0 becasuse you don't have the armor when you start)
	active_armor = false; //no armor when you start
	have_armor = false; //no armor when you start
};

Player::Player(){ //default constructor
	yLoc = 0;
	xLoc = 0;
	curwin = newwin(0,0,0,0);
	getmaxyx(curwin,yMax,xMax);
	keypad(curwin,true);
	character[0] = '@';
	character[1] = '^';
	life = 99;
	cash = 0;
	dir = 1;
	bullet = Bullet(curwin); //initialize the bullet
	ind = 0; //no bullet
	//jump
	activejump = false;
	xpern = 0;
	ypern = 0;
	conta = 0;
	strcpy(typeofgun,"none"); //no gun when you start
	shield = false; //no shield when you start
	shield_life = 0;
	teleportation = false; //you cannot teleport when you start
	time_life_armor = 0; //life of the armor (0 becasuse you don't have the armor when you start)
	active_armor = false; //no armor when you start
	have_armor = false; //no armor when you start
}

void Player::initialize(){
	display();
}

void Player::updatepivot(){ //update pivot coordinates
	xpern = xLoc;
	ypern = yLoc;
}

void Player::jump(){ //jump dx,sx
	mvwaddch(curwin, yLoc, xLoc,' '); //Delete previous character
	mvwaddch(curwin, yLoc-1, xLoc,' '); //Delete previous character
	int xv = xpern + 3*dir; //xvertex of parabola
	int yv = ypern - 9; //yvertex of parabola
	int a = (ypern-yv)/((xpern-xv)*(xpern-xv)); //coefficients of degree 2 of parabola
	if(conta < 7){ //if you want to do the whole jump also from the platform, you have to take the max of conta very large
		int x = xpern + dir * conta;
		yLoc = a * (x-xv) * (x-xv) + yv; //parabola equation
		if(x < 1) xLoc = 1; //reach minimum
		else if(x > xMax-2) xLoc = xMax - 2; //reach maximum
		else if(yLoc < 1) yLoc = 1; //reach minimum
		else if(yLoc > yMax-2) yLoc = yMax-2; //reach maximum
		else xLoc = xpern + dir * conta;
		conta = conta + 1;
	}
	else{
		conta = 0; //ready for the next jump
		activejump = false; //you reach the ground floor
	}
}

void Player::mvleft(){ //move left
	dir = -1; //update direction
	mvwaddch(curwin, yLoc, xLoc,' ');
	mvwaddch(curwin, yLoc-1, xLoc,' ');
	xLoc = xLoc - 1;
	if (xLoc < 1) xLoc = 1;
}

void Player::mvright(){ //move right
	dir = 1; //update direction
	mvwaddch(curwin, yLoc, xLoc,' ');
	mvwaddch(curwin, yLoc-1, xLoc,' ');
	xLoc = xLoc + 1;
	if (xLoc > xMax-2) xLoc = xMax - 2;
}

bool Player::godown(){
	mvwaddch(curwin, yLoc, xLoc,' ');
	mvwaddch(curwin, yLoc-1, xLoc,' ');
	bool arrive = false;
	if(yLoc<yMax-2) yLoc = yLoc + 1;
	else{
		yLoc = yMax-2;
		arrive = true;
	}
	return arrive;
}

void Player::teleport(){
	mvwaddch(curwin, yLoc, xLoc,' ');
	mvwaddch(curwin, yLoc-1, xLoc,' ');
	yLoc = yMax - 2; //ground floor
	xLoc = xLoc + 30;
	if(xLoc > xMax-2) xLoc = xMax - 2; //you reach the wall
}

int Player::getmv(){ //move the character with gun by user
	if(active_armor){ //check if you have actived your armor (when you do a movement, you lose one life of your armor)
		if(time_life_armor>0)time_life_armor--; //if you have the armor actived, you have to decrement the time life of armor
		else active_armor = false; //Your armor finishes its life
	}
	int choice = wgetch(curwin);
	switch (choice){
		case KEY_UP:
			activejump = true; //active jump
			updatepivot();
			jump();
		break;
		case KEY_LEFT:
			mvleft();
			break;
		case KEY_RIGHT:
			mvright();
			break;
		case 'h': //activate the gun
			if(strcmp(typeofgun,"pistol") == 0){ //you shoot one bullet
				bullet.blt = bullet.head_insert(bullet.blt,dir,xLoc,yLoc,ind); //add the bullet
				ind = ind + 1; //we want different indexes for the different bullets
			}
			else if(strcmp(typeofgun,"rifle") == 0){ //you shoot two bullets
				for(int i=0;i<2;i++){
					bullet.blt = bullet.head_insert(bullet.blt,dir,xLoc+i*dir,yLoc,ind); //add the bullet
					ind = ind + 1; //we want different indexes for the different bullets
				}
			}
			else if(strcmp(typeofgun,"machinegun") == 0){ //you shoot three bullets
				for(int i=0;i<3;i++){
					bullet.blt = bullet.head_insert(bullet.blt,dir,xLoc+i*dir,yLoc,ind); //add the bullet
					ind = ind + 1; //we want different indexes for the different bullets
				}
			}
			else if(strcmp(typeofgun,"doublegun") == 0){//you shoot two bullets in opposite directions
				bullet.blt = bullet.head_insert(bullet.blt,dir,xLoc,yLoc,ind); //add the bullet
				ind = ind + 1; //we want different indexes for the different bullets
				bullet.blt = bullet.head_insert(bullet.blt,-dir,xLoc,yLoc,ind); //add the bullet
				ind = ind + 1;
			}
			break;
		case 't': //activate the teleport
			if(teleportation) Player::teleport();
			break;
		case 'a': //activate the armor (time_life of armor starts)
			if(have_armor){
				have_armor = false; //no armor anymore
				active_armor = true;
			}
			break;
		default:
			break;
	}
	return choice;
}

int Player::jumpandshoot(){ //during the jump you can just shooting
	int choice = wgetch(curwin);
	switch(choice){
		case 'h':
			bullet.blt = bullet.head_insert(bullet.blt,dir,xLoc,yLoc,ind); //add the bullet
			ind = ind + 1;
			break;
		default:
			break;
	}
	return choice;
}

void Player::display(){ //display the character
	mvwaddch(curwin,yLoc,xLoc,character[0]);
	mvwaddch(curwin,yLoc-1,xLoc,character[1]);
}


void Player::injury(){ //Injury
	if(!shield && !active_armor){ //check if the player has the shield and the armor
		mvwaddch(curwin,yLoc,xLoc,' ');
		mvwaddch(curwin, yLoc-1, xLoc,' ');
		xLoc = 1; //back to beginning
		yLoc = yMax - 2; //back to beginning
		life = life - 1; // one point
	}
	else if(shield){ //check if the player has the shield
		if(shield_life == 0) shield = false; //no shield anymore
		else shield_life = shield_life - 1;
	}
}

int Player::getx(){
	return xLoc;
}

int Player::gety(){
	return yLoc;
}

int Player::getlife(){
	return life;
}

int Player::getcoins(){
	return cash;
}

void Player::updatecash(){ //update cash
	cash = cash + 1;
}
