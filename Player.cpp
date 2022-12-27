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
}

void Player::initialize(){
	display();
}

void Player::jump(int segno){ //jump dx,sx
	int x = xLoc; //save xstart of jump
	int y = yLoc; //save ystart of jump
	int xv = x+3*segno; //xvertex of parabola
	int yv = y - 9; //yvertex of parabola
	int a = (y-yv)/((x-xv)*(x-xv));
	for (int i=0;i<7;i++){ //7 = 2*3 + 1
		mvwaddch(curwin, yLoc, xLoc,' '); //Delete previous character
		xLoc = x + segno*i;
		yLoc = a * (xLoc-xv) * (xLoc-xv) + yv; //parabola equation
		if(xLoc < 1) xLoc = 1; //reach minimum
		if(xLoc > xMax-2) xLoc = xMax - 2; //reach maximum
		display();
		wrefresh(curwin);
        napms(40); //delay 40ms --> we can see the jump
	}
}

void Player::mvupright(){  //move up
	jump(1);
}

void Player::mvupleft(){ //move down
	jump(-1);
}
void Player::mvleft(){ //move left
	mvwaddch(curwin, yLoc, xLoc,' ');
	xLoc = xLoc - 1;
	if (xLoc < 1) xLoc = 1;
}
void Player::mvright(){ //move right
	mvwaddch(curwin, yLoc, xLoc,' ');
	xLoc = xLoc + 1;
	if (xLoc > xMax-2) xLoc = xMax - 2;
}
int Player::getmv(){ //move the character by user
	int choice = wgetch(curwin);
	switch (choice){
		case KEY_UP:
			mvupright();
			break;
		case KEY_DOWN:
			mvupleft();
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
