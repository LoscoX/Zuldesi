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
	segno = -1; //segno for parabola
	conta = 1;
	jump_height = 9; //max height of the jump
	onplatform = false; //you are not on a platform
	NUM_BULLETS = 100; //number of bullets
	//powerup
	gun = Powerup("None", "No gun", 1, 0, 0); //no gun when you start
	shield = Powerup("Shield", "A shield that blocks damage one time", 0, 1, 1); //no shield when you start
	hp = Powerup("HP", "Get back on your feet one more time", life, 1, 1);
	armor = Powerup("Armor", "Become invincible for a limited time", 0, 1, 1); //no armor when you start
	teleportation = Powerup("Teleport", "Teleport a short distance", 0, 1, 1); //you cannot teleport when you start
	bullets = Powerup("Bullets","Charge of bullets",NUM_BULLETS,1,1); //no bullets when you start
	jumping = Powerup("Jump","Change the height of the jump",jump_height,1,1); //basic jump when you start
	ARMOR_DURATION[0] = 50; ARMOR_DURATION[1] = 100; ARMOR_DURATION[2] = 500; //different type of Armor duration
	TELEPORT_DISTANCE[0] = dir*20; TELEPORT_DISTANCE[1] = dir*30; TELEPORT_DISTANCE[2] = dir*40; //different teleport distance
	ACTIVE_ARMOR = false; //no Armor when you start
	ARMOR_ACTIVE_DURATION = 0; //no armor when you start
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
	segno = -1; //segno for parabola
	conta = 1;
	onplatform = false; //you are not on a platform
	jump_height = 9; //max height of the jump
	NUM_BULLETS = 100; //number of bullets
	//powerup
	gun = Powerup("None", "No gun", 1, 0, 0); //no gun when you start
	shield = Powerup("Shield", "A shield that blocks damage one time", 0, 1, 1); //no shield when you start
	hp = Powerup("HP", "Get back on your feet one more time", life, 1, 1);
	armor = Powerup("Armor", "Become invincible for a limited time", 0, 1, 1); //no armor when you start
	teleportation = Powerup("Teleport", "Teleport a short distance", 0, 1, 1); //you cannot teleport when you start
	bullets = Powerup("Bullets","Charge of bullets",NUM_BULLETS,1,1); //no bullets when you start
	jumping = Powerup("Jump","Change the height of the jump",jump_height,1,1); //basic jump when you start
	ARMOR_DURATION[0] = 50; ARMOR_DURATION[1] = 100; ARMOR_DURATION[2] = 500; //different type of Armor duration
	TELEPORT_DISTANCE[0] = 20; TELEPORT_DISTANCE[1] = 30; TELEPORT_DISTANCE[2] = 40; //different teleport distance
	ACTIVE_ARMOR = false; //no Armor when you start
	ARMOR_ACTIVE_DURATION = 0; //no armor when you start
}

void Player::initialize(){
	display();
}

void Player::SetJump(){ //Rearrange jump variables
	conta = 1; //ready for the next jump
	segno = -1; //ready for the next jump
	activejump = false; //you reach the ground floor
}

void Player::jump(){ //not move the x
	mvwaddch(curwin, yLoc, xLoc,' '); //Delete previous character
	mvwaddch(curwin, yLoc-1, xLoc,' '); //Delete previous character
	if(conta<=2*(jumping.getQnt()-1)){
		if(conta == jumping.getQnt())segno = 1; //go down
		yLoc = yLoc + segno;
		conta++;
		if(xLoc>xMax-2){ //if you reach the wall
			SetJump(); //ready for a new jump
			xLoc = xMax-2; //fix the x
			while(yLoc>yMax-2)godown(); //go down
		}
		else if(xLoc<1){ //if you reach the wall
			SetJump(); //ready for a new jump
			xLoc = 1; //fix the x
			while(yLoc>yMax-2)godown(); //go down
		}
		else if(yLoc<1){ //if you reach the roof
			SetJump(); //ready for a new jump
			while(yLoc>yMax-2)godown(); //godown
		}
	}
	else{
		SetJump(); //ready for a new jump
	}
}

void Player::godown(){ //go down
	mvwaddch(curwin, yLoc, xLoc,' ');
	mvwaddch(curwin, yLoc-1, xLoc,' ');
	yLoc = yLoc + 1; //you are falling
}

void Player::teleport(){
	mvwaddch(curwin, yLoc, xLoc,' ');
	mvwaddch(curwin, yLoc-1, xLoc,' ');
	yLoc = yMax - 2; //ground floor
	xLoc = xLoc + TELEPORT_DISTANCE[teleportation.getQnt()-1]; //teleport the character
	if(xLoc > xMax-2) xLoc = xMax - 2; //you reach the wall
}

int Player::getmv(){ //move the character with gun by user
	if(ACTIVE_ARMOR){ //check if you have actived your armor
		if(ARMOR_ACTIVE_DURATION>0)ARMOR_ACTIVE_DURATION--; //if you have the armor actived, you have to decrement the time life of armor
		else ACTIVE_ARMOR = false; //Your armor finishes its life
	}
	int choice = wgetch(curwin);
	switch (choice){
		case KEY_UP: //just go up
			activejump = true; //active jump
			jump();
		break;
		case 'h': //activate the gun
			if(bullets.getQnt()>0 && strcmp(gun.getName().c_str(),"Pistol") == 0){ //you shoot one bullet
				bullet.blt = bullet.head_insert(bullet.blt,dir,xLoc,yLoc,ind); //add the bullet
				ind = ind + 1; //we want different indexes for the different bullets
				bullets.setQnt(bullets.getQnt()-1); //decrement bullets
			}
			else if(bullets.getQnt()>1 && strcmp(gun.getName().c_str(),"Rifle") == 0){ //you shoot two bullets
				for(int i=0;i<2;i++){
					bullet.blt = bullet.head_insert(bullet.blt,dir,xLoc+i*dir,yLoc,ind); //add the bullet
					ind = ind + 1; //we want different indexes for the different bullets
					bullets.setQnt(bullets.getQnt()-1); //decrement bullets
				}
			}
			else if(bullets.getQnt()>2 && strcmp(gun.getName().c_str(),"Machinegun") == 0){ //you shoot three bullets
				for(int i=0;i<3;i++){
					bullet.blt = bullet.head_insert(bullet.blt,dir,xLoc+i*dir,yLoc,ind); //add the bullet
					ind = ind + 1; //we want different indexes for the different bullets
					bullets.setQnt(bullets.getQnt()-1); //decrement bullets
				}
			}
			else if(bullets.getQnt()>1 && strcmp(gun.getName().c_str(), "Doublegun") == 0){//you shoot two bullets in opposite directions
				bullet.blt = bullet.head_insert(bullet.blt,dir,xLoc,yLoc,ind); //add the bullet
				ind = ind + 1; //we want different indexes for the different bullets
				bullets.setQnt(bullets.getQnt()-1); //decrement bullets
				bullet.blt = bullet.head_insert(bullet.blt,-dir,xLoc,yLoc,ind); //add the bullet
				ind = ind + 1;
				bullets.setQnt(bullets.getQnt()-1); //decrement bullets
			}
			break;
		case 'a': //activate the armor (time_life of armor starts)
			if(armor.getQnt()>0){ //you have at least on piece of armor
				ARMOR_ACTIVE_DURATION = ARMOR_DURATION[armor.getQnt()-1]; //thanks to the quantity you get the armor duration. For example if you have two pieces of armor, you have 5000 time duration
				armor.setQnt(0); //no armor anymore (you lose all piecies)
				ACTIVE_ARMOR = true;
			}
			break;
		default:
			break;
	}
	return choice;
}

int Player::airshoot(){ //during jump movement or down movement, you can just shooting
	int choice = wgetch(curwin);
	switch(choice){
		case 'h': //activate the gun
			if(bullets.getQnt()>0 && strcmp(gun.getName().c_str(),"Pistol") == 0){ //you shoot one bullet
				bullet.blt = bullet.head_insert(bullet.blt,dir,xLoc,yLoc,ind); //add the bullet
				ind = ind + 1; //we want different indexes for the different bullets
				bullets.setQnt(bullets.getQnt()-1); //decrement bullets
			}
			else if(bullets.getQnt()>1 && strcmp(gun.getName().c_str(),"Rifle") == 0){ //you shoot two bullets
				for(int i=0;i<2;i++){
					bullet.blt = bullet.head_insert(bullet.blt,dir,xLoc+i*dir,yLoc,ind); //add the bullet
					ind = ind + 1; //we want different indexes for the different bullets
					bullets.setQnt(bullets.getQnt()-1); //decrement bullets
				}
			}
			else if(bullets.getQnt()>2 && strcmp(gun.getName().c_str(),"Machinegun") == 0){ //you shoot three bullets
				for(int i=0;i<3;i++){
					bullet.blt = bullet.head_insert(bullet.blt,dir,xLoc+i*dir,yLoc,ind); //add the bullet
					ind = ind + 1; //we want different indexes for the different bullets
					bullets.setQnt(bullets.getQnt()-1); //decrement bullets
				}
			}
			else if(bullets.getQnt()>1 && strcmp(gun.getName().c_str(), "Doublegun") == 0){//you shoot two bullets in opposite directions
				bullet.blt = bullet.head_insert(bullet.blt,dir,xLoc,yLoc,ind); //add the bullet
				ind = ind + 1; //we want different indexes for the different bullets
				bullets.setQnt(bullets.getQnt()-1); //decrement bullets
				bullet.blt = bullet.head_insert(bullet.blt,-dir,xLoc,yLoc,ind); //add the bullet
				ind = ind + 1;
				bullets.setQnt(bullets.getQnt()-1); //decrement bullets
			}
			break;
		default:
			break;
	}
	return choice;
}

void Player::display(){ //display the character
	if(hp.getQnt()>1){
		mvwaddch(curwin,yLoc,xLoc,character[0]);
		mvwaddch(curwin,yLoc-1,xLoc,character[1]);
	}
	else{ //if you have one life, you become red
		wattron(curwin,COLOR_PAIR(1)); //color
		mvwaddch(curwin,yLoc,xLoc,character[0]);
		mvwaddch(curwin,yLoc-1,xLoc,character[1]);
		wattroff(curwin,COLOR_PAIR(1));
	}
}


void Player::injury(){ //Injury
	if(shield.getQnt() == 0 && !ACTIVE_ARMOR){ //check if the player has the shield and the armor
		mvwaddch(curwin,yLoc,xLoc,' ');
		mvwaddch(curwin, yLoc-1, xLoc,' ');
		xLoc = 20; //back to beginning
		yLoc = yMax - 2; //back to beginning
		hp.setQnt(hp.getQnt()-1); // one point
	}
	else if(shield.getQnt() > 0 && !ACTIVE_ARMOR){ //check if the player has the shield but not the armor
		shield.setQnt(shield.getQnt()-1); //you lose one piece of shield
	}
	//if you have the armor, you are invicible
}

int Player::getx(){
	return xLoc;
}

int Player::gety(){
	return yLoc;
}

int Player::getCoins(){
	return cash;
}

int Player::getDir(){
	return dir;
}

void Player::updateCash(int money){ //update cash
	cash = cash + money;
}

void Player::updateCoordinates(int x,int y){ //update coordinates
	xLoc = xLoc+x;
	yLoc = yLoc+y;
}

void Player::setDir(int dir)
{
	this->dir=dir;
}

void Player::setLife(int life){
	this->life = life;
}
