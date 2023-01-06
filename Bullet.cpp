/*
 * Bullet.cpp
 *
 *  Created on: 30 dic 2022
 *      Author: david
 */

#include "Bullet.hpp"

Bullet::Bullet(WINDOW * win){
	blt = NULL;
	curwin = win;
	getmaxyx(curwin,yMax,xMax);
}

Bullet::Bullet(){
	blt = NULL;
	curwin = newwin(0,0,0,0);
	getmaxyx(curwin,yMax,xMax);
}

bullt Bullet::head_insert(bullt h,int dir,int x,int y,int ind){ //add the bullet
	bullt tmp = new bullet;
	tmp->xB = x + dir; //bullet starts where is the player and it depends on his direction
	tmp->yB = y;
	tmp->dir = dir; //direction of the bullet
	tmp->cod = ind; //ID --> It's unic
	tmp->next = h;
	return tmp;
}

bullt Bullet::obj_remove(bullt h,int e,bool head){ //remove the e bullet
	if (h==NULL) return h;
	else if(h->cod == e){ //if the bullet is in the head of the list
		if(head == true){ //we need because we have a problem if we delete the list and use again the element pointed by the list
			bullt tmp = h;
			h = h->next;  //ok also if h has one element
			delete tmp;
			tmp = NULL;
		}
		else h = h->next;
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

bool Bullet::shoot(bullt blt2,bullt blt){ //describes the movement of the bullet
	bool found = false;
	if(blt2->xB >= 1 && blt2->xB <= xMax - 2) mvwaddch(curwin,blt2->yB,blt2->xB,' ');
	blt2->xB = blt2->xB + blt2->dir; //update the x of the bullet
	if(blt2->xB < 1 || blt2->xB > xMax-2) found = true; //you reach the wall
	else mvwaddch(curwin,blt2->yB,blt2->xB,'*'); //draw the bullet
	return found;
}
