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
	character[2] = '|';
	character[3] = '-';
	life = 250;
	cash = 0;
	dir = 1; //initial direction
	bullet = Bullet(); //initialize the bullet
	ind = 0; //no bullet
	//jump
	activejump = false; //start without jump
	segno = -1; //segno for parabola
	conta = 1;
	jump_height = 5; //max height of the jump
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
	fly = Powerup("Fly","You can fly",0,1,1); //you cannot fly when you start
	ARMOR_DURATION[0] = 500; ARMOR_DURATION[1] = 1000; ARMOR_DURATION[2] = 5000; //different type of Armor duration
	TELEPORT_DISTANCE[0] = dir*20; TELEPORT_DISTANCE[1] = dir*30; TELEPORT_DISTANCE[2] = dir*40; //different teleport distance
	ACTIVE_ARMOR = false; //no armor when you start
	ARMOR_ACTIVE_DURATION = 0; //no armor when you start
	FLY_ACTIVE_DURATION = 0; //no fly when you start
	FLY_DURATION = 5000; //duration of the fly
	ACTIVE_FLY = false; //no fly when you start
};

Player::Player(){} //default constructor

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
	if(armor.getQnt()>0) mvwaddch(curwin,yLoc-1,xLoc,' '); //Delete armor
	if(shield.getQnt()>0) mvwaddch(curwin,yLoc,xLoc-getDir(),' '); //delete shield
	if(shield.getQnt()==0) mvwaddch(curwin,yLoc,xLoc-getDir(),' '); //delete old gun
	if(gun.getName()!="none") mvwaddch(curwin,yLoc,xLoc+getDir(),' '); //delete gun
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
	mvwaddch(curwin, yLoc, xLoc,' '); //delete character
	if(armor.getQnt()>0) mvwaddch(curwin,yLoc-1,xLoc,' '); //Delete armor
	if(shield.getQnt()>0) mvwaddch(curwin,yLoc,xLoc-getDir(),' '); //delete shield
	if(shield.getQnt()==0) mvwaddch(curwin,yLoc,xLoc-getDir(),' '); //old gun
	if(gun.getName()!="none") mvwaddch(curwin,yLoc,xLoc+getDir(),' '); //delete gun
	yLoc = yLoc + 1; //you are falling
}

void Player::goup(){ //go up
	mvwaddch(curwin, yLoc, xLoc,' '); //delete character
	if(armor.getQnt()>0) mvwaddch(curwin,yLoc-1,xLoc,' '); //Delete armor
	if(shield.getQnt()>0) mvwaddch(curwin,yLoc,xLoc-getDir(),' '); //delete shield
	if(shield.getQnt()==0) mvwaddch(curwin,yLoc,xLoc-getDir(),' '); //old gun
	if(gun.getName()!="none") mvwaddch(curwin,yLoc,xLoc+getDir(),' '); //delete gun
	yLoc = yLoc - 1; //you are liftfing
	if(yLoc<1) yLoc = 1;
}

void Player::teleport(){
	mvwaddch(curwin, yLoc, xLoc,' '); //delete character
	if(armor.getQnt()>0) mvwaddch(curwin,yLoc-1,xLoc,' '); //delete armor
	if(shield.getQnt()>0) mvwaddch(curwin,yLoc,xLoc-getDir(),' '); //delete shield
	if(shield.getQnt()==0) mvwaddch(curwin,yLoc,xLoc-getDir(),' '); //delete old gun
	if(gun.getName()!="none") mvwaddch(curwin,yLoc,xLoc+getDir(),' '); //delete gun
	yLoc = yMax - 2; //ground floor
	xLoc = xLoc + TELEPORT_DISTANCE[teleportation.getQnt()-1]; //teleport the character
	if(xLoc > xMax-2) xLoc = xMax - 2; //you reach the wall
}

int Player::getmv(){ //move the character with gun by user
	if(ACTIVE_ARMOR){ //check if you have actived your armor
		if(ARMOR_ACTIVE_DURATION>0)ARMOR_ACTIVE_DURATION--; //if you have the armor actived, you have to decrement the time life of armor
		else ACTIVE_ARMOR = false; //Your armor finishes its life
	}
	if(ACTIVE_FLY){ //check if you have actived your fly
		if(FLY_ACTIVE_DURATION>0)FLY_ACTIVE_DURATION--; //if you have fly actived, you have to decrement the time life of fly
		else ACTIVE_FLY = false; //Your fly finishes its life
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
				ARMOR_ACTIVE_DURATION = ARMOR_DURATION[armor.getQnt()-1]; //thanks to the quantity you get the armor duration. For example if you have two pieces of armor, you have 1000 time duration
				armor.setQnt(0); //no armor anymore (you lose all piecies)
				ACTIVE_ARMOR = true;
			}
			break;
		case 'f': //activate the fly (time_life of fly starts)
			if(fly.getQnt()>0){ //you have the fly
				FLY_ACTIVE_DURATION = FLY_DURATION; //thanks to the quantity you get the fly duration.
				fly.setQnt(0); //no fly anymore
				ACTIVE_FLY = true;
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
		mvwaddch(curwin,yLoc,xLoc,character[0]); //see the player
		if(ACTIVE_ARMOR==true){
			mvwaddch(curwin,yLoc,xLoc,'O'); //see armor
		}
		if(shield.getQnt()>0) mvwaddch(curwin,yLoc,xLoc-getDir(),character[2]); //see the shield
		if(shield.getQnt()==0) mvwaddch(curwin,yLoc,xLoc-getDir(),' '); //delete old gun
		if(gun.getName()!="none") mvwaddch(curwin,yLoc,xLoc+getDir(),character[3]); //see the gun
	}
	else{ //if you have one life, you become red
		wattron(curwin,COLOR_PAIR(1)); //color
		mvwaddch(curwin,yLoc,xLoc,character[0]); //see the player
		if(ACTIVE_ARMOR==true){
			mvwaddch(curwin,yLoc,xLoc,'O'); //see armor
		}
		if(shield.getQnt()>0) mvwaddch(curwin,yLoc,xLoc-getDir(),character[2]); //see the shield
		if(shield.getQnt()==0) mvwaddch(curwin,yLoc,xLoc-getDir(),' '); //delete old gun
		if(gun.getName()!="none") mvwaddch(curwin,yLoc,xLoc+getDir(),character[3]); //see the gun
		wattroff(curwin,COLOR_PAIR(1));
	}
}


void Player::injury(){ //Injury
	if(shield.getQnt() == 0 && !ACTIVE_ARMOR){ //check if the player has the shield and the armor
		//mvwaddch(curwin,yLoc,xLoc,' ');
		//xLoc = 20; //back to beginning
		//yLoc = yMax - 2; //back to beginning
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
