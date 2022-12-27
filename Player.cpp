/*
 * Player.cpp
 *
 *  Created on: 8 dic 2022
 *      Author: david
 */

#include "Player.hpp"

Player::Player(WINDOW * win, int y, int x, char c){
	yLoc = y;
	xLoc = x;
	curwin = win;
	getmaxyx(curwin,yMax,xMax);
	keypad(curwin,true);
	character = c;
	life = 99;
	cash = 0;
	pwup = NULL;
	dir = 1; //initial direction
	blt = NULL; //gun magazine
	ind = 0; //no bullet
	//jump
	activejump = false; //start without jump
	xpern = xLoc; //save medium point for the jump
	ypern = yLoc; //save medium point for the jump
	conta = 0;
};

Player::Player(){
	yLoc = 0;
	xLoc = 0;
	curwin = newwin(0,0,0,0);
	getmaxyx(curwin,yMax,xMax);
	keypad(curwin,true);
	character = '@';
	life = 99;
	cash = 0;
	pwup = NULL;
	dir = 1;
	blt = NULL; //gun magazine
	ind = 0; //no bullet
	//jump
	activejump = false;
	xpern = 0;
	ypern = 0;
	conta = 0;
}

void Player::initialize(){
	display();
}

void Player::updatepern(){
	xpern = xLoc;
	ypern = yLoc;
}

void Player::jump(){ //jump dx,sx
	mvwaddch(curwin, yLoc, xLoc,' '); //Delete previous character
	int xv = xpern + 3*dir; //xvertex of parabola
	int yv = ypern - 9; //yvertex of parabola
	int a = (ypern-yv)/((xpern-xv)*(xpern-xv)); //coefficients of degree 2 of parabola
	if(conta < 2*3 + 1){ //if you want to do the whole jump (2 times of 3 + 1)
		xLoc = xpern + dir * conta;
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
		conta = 0; //ready for the next jump
		activejump = false; //you reach the ground floor
	}

}


void Player::mvleft(){ //move left
	dir = -1; //update direction
	mvwaddch(curwin, yLoc, xLoc,' ');
	xLoc = xLoc - 1;
	if (xLoc < 1) xLoc = 1;
}

void Player::mvright(){ //move right
	dir = 1; //update direction
	mvwaddch(curwin, yLoc, xLoc,' ');
	xLoc = xLoc + 1;
	if (xLoc > xMax-2) xLoc = xMax - 2;
}

int Player::getmv(){ //move the character by user
	int choice = wgetch(curwin);
	switch (choice){
		case KEY_UP:
			activejump = true; //active jump
			updatepern();
			jump();
			break;
		case KEY_LEFT:
			mvleft();
			break;
		case KEY_RIGHT:
			mvright();
			break;
		default:
			break;
	}
	return choice;
}

bullt Player::head_insert(bullt h,int dir){ //add the bullet
	bullt tmp = new bullet;
	tmp->xB = xLoc + dir; //bullet starts where is the player
	tmp->yB = yLoc;
	tmp->dir = dir; //direction of the bullet
	tmp->cod = ind; //ID
	tmp->next = h;
	return tmp;
}

bullt Player::tail_remove(bullt h,int e){ //remove the e bullet
	if (h==NULL) return h;
	else if(h->next == NULL){ //if there is just one bullet
		//problem with the memory
		h = NULL;
	}
	else{
		bullt tmp = h;
		bool found = false;
		while(tmp->next!=NULL && !found){
			if(tmp->next->cod == e){ //bullet in the middle of the list (ok also for the tail)
				bullt tmp2 = tmp->next;
				tmp->next = tmp2->next;
				delete tmp2; //clean memory
				tmp2 = NULL;
				found = true;
			}
			else tmp = tmp->next;
		}
	}
	return h;
}

void Player::shoot(bullt blt){ //describes the movement of the bullet
	if(blt->xB >= 1 && blt->xB <= xMax - 2) mvwaddch(curwin,blt->yB,blt->xB,' ');
	blt->xB = blt->xB + blt->dir; //update the x of the bullet
	if(blt->xB < 1 || blt->xB > xMax-2){ //if the bullet reach the walls
		blt = tail_remove(blt,blt->cod); //remove from the list
	}
	else mvwaddch(curwin,blt->yB,blt->xB,'-'); //draw the bullet
}

int Player::getmvgun(){ //move the character with gun by user
	int choice = wgetch(curwin);
	switch (choice){
		case KEY_UP:
			activejump = true; //active jump
			updatepern();
			jump();
		break;
		case KEY_LEFT:
			mvleft();
			break;
		case KEY_RIGHT:
			mvright();
			break;
		case 'h': //activate the gun
			blt = head_insert(blt,dir); //add the bullet
			ind = ind + 1;
			break;
		default:
			break;
	}
	return choice;
}

int Player::jumpandshoot(){
	int choice = wgetch(curwin);
	switch(choice){
		case 'h':
			blt = head_insert(blt,dir); //add the bullet
			ind = ind + 1;
			break;
		default:
			break;
	}
	return choice;
}

void Player::display(){ //display the character
	mvwaddch(curwin,yLoc,xLoc,character);
}


void Player::injury(){ //Injury
	xLoc = 1; //back to beginning
	yLoc = yMax - 2; //back to beginning
	life = life - 1; // one point
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

void Player::updatecash(int cash){ //update cash
	this->cash = this->cash + cash;
}

powup Player::addpwup(powup h,int e,char icon){ //add powerup
	powup tmp = new powerup;
	tmp->val = e;
	tmp->c = icon;
	tmp->next = h;
	return tmp;
}

powup Player::removepwup(powup h,int e){ //remove powerup
	if(h==NULL) return h;
	if(h->val == e){ //you find powerup on the head of list
		powup tmp2 = h;
		h = h->next;
		delete tmp2;
		tmp2 = NULL;
		return h;
	}
	powup tmp = h;
	while(tmp->next!=NULL){
		if(tmp->next->val == e){ //you find powerup in the list
			powup tmp2 = tmp->next;
			tmp->next = tmp2->next;
			delete tmp2;
			tmp2 = NULL;
			return h;
		}
		else tmp = tmp->next; //nothing
	}
	return h; //no powerups
}
