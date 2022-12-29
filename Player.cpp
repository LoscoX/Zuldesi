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
	pwup = NULL;//powerup
	dir = 1; //initial direction
	blt = NULL; //gun magazine
	ind = 0; //no bullet
	//jump
	activejump = false; //start without jump
	xpern = xLoc; //save medium point for the jump
	ypern = yLoc; //save medium point for the jump
	conta = 0;
	gun = true; //you start without the gun
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
	pwup = NULL;
	dir = 1;
	blt = NULL; //gun magazine
	ind = 0; //no bullet
	//jump
	activejump = false;
	xpern = 0;
	ypern = 0;
	conta = 0;
	gun = false;
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

bullt Player::head_insert(bullt h,int dir){ //add the bullet
	bullt tmp = new bullet;
	tmp->xB = xLoc + dir; //bullet starts where is the player
	tmp->yB = yLoc;
	tmp->dir = dir; //direction of the bullet
	tmp->cod = ind; //ID --> It's unic
	tmp->next = h;
	return tmp;
}

bullt Player::obj_remove(bullt h,int e){ //remove the e bullet
	if (h==NULL) return h;
	else if(h->cod == e){ //if the bullet is in the head of the list
		//problem with the memory
		//bullt tmp = h;
		h = h->next;  //ok also if h has one element
		//delete tmp;
		//tmp = NULL;
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

void Player::shoot(bullt blt2){ //describes the movement of the bullet
	if(blt2->xB >= 1 && blt2->xB <= xMax - 2) mvwaddch(curwin,blt2->yB,blt2->xB,' ');
	blt2->xB = blt2->xB + blt2->dir; //update the x of the bullet
	if(blt2->xB < 1 || blt2->xB > xMax-2){ //if the bullet reach the walls
		int codice = blt2->cod;
		blt2 = obj_remove(blt2,blt2->cod); //remove from the list
		blt = obj_remove(blt,codice); //remove from the main list
	}
	else mvwaddch(curwin,blt2->yB,blt2->xB,'-'); //draw the bullet
}

int Player::getmv(){ //move the character with gun by user
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
			if(gun == true){
				blt = head_insert(blt,dir); //add the bullet
				ind = ind + 1; //we want different indexes for the different bullets
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
			blt = head_insert(blt,dir); //add the bullet
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
	mvwaddch(curwin,yLoc,xLoc,' ');
	mvwaddch(curwin, yLoc-1, xLoc,' ');
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

int Player::getcoins(){
	return cash;
}

void Player::updatecash(){ //update cash
	cash = cash + 1;
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
		h = h->next;
	}
	powup tmp = h;
	bool found = false;
	while(tmp->next!=NULL && !found){
		if(tmp->next->val == e){ //you find powerup in the list
			powup tmp2 = tmp->next;
			tmp->next = tmp2->next;
			delete tmp2;
			tmp2 = NULL;
			found = true;
		}
		else tmp = tmp->next; //nothing
	}
	return h; //no powerups
}
