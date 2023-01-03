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
	life = 3;
	cash = 0;
	dir = 1; //initial direction
	bullet = Bullet(curwin); //initialize the bullet
	ind = 0; //no bullet
	//jump
	activejump = false; //start without jump
	segno = -1; //segno for parabola
	conta = 1;
	down_arrive = true; //you are not falling
	onplatform = false; //you are not on a platform
	//powerup
	gun = Powerup("None", "No gun", 1, 0, 0); //no gun when you start
	shield = Powerup("Shield", "A shield that blocks damage one time", 0, 1, 1); //no shield when you start
	hp = Powerup("HP", "Get back on your feet one more time", life, 1, 1);
	armor = Powerup("Armor", "Become invincible for a limited time", 0, 1, 1); //no armor when you start
	teleportation = Powerup("Teleport", "Teleport a short distance", 0, 1, 1); //you cannot teleport when you start
	ARMOR_DURATION[0] = 50; ARMOR_DURATION[1] = 100; ARMOR_DURATION[2] = 500; //different type of Armor duration
	TELEPORT_DISTANCE[0] = 20; TELEPORT_DISTANCE[1] = 30; TELEPORT_DISTANCE[2] = 40; //different teleport distance
	ACTIVE_ARMOR = false; //no Armor when you start
	ARMOR_ACTIVE_DURATION = 0; //no armor when you start
	num_bullet = 9; //number of bullets
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
	down_arrive = true; //you are not falling
	onplatform = false; //you are not on a platform
	//powerup
	gun = Powerup("None", "No gun", 1, 0, 0); //no gun when you start
	shield = Powerup("Shield", "A shield that blocks damage one time", 0, 1, 1); //no shield when you start
	hp = Powerup("HP", "Get back on your feet one more time", life, 1, 1);
	armor = Powerup("Armor", "Become invincible for a limited time", 0, 1, 1); //no armor when you start
	teleportation = Powerup("Teleport", "Teleport a short distance", 0, 1, 1); //you cannot teleport when you start
	ARMOR_DURATION[0] = 50; ARMOR_DURATION[1] = 100; ARMOR_DURATION[2] = 500; //different type of Armor duration
	TELEPORT_DISTANCE[0] = 20; TELEPORT_DISTANCE[1] = 30; TELEPORT_DISTANCE[2] = 40; //different teleport distance
	ACTIVE_ARMOR = false; //no Armor when you start
	ARMOR_ACTIVE_DURATION = 0; //no armor when you start
	num_bullet = 9; //number of bullets
}

void Player::initialize(){
	display();
}

void Player::SetJump(){ //Rearrange jump variables
	conta = 1; //ready for the next jump
	segno = -1; //ready for the next jump
	activejump = false; //you reach the ground floor
}

void Player::jump(){
	mvwaddch(curwin, yLoc, xLoc,' '); //Delete previous character
	mvwaddch(curwin, yLoc-1, xLoc,' '); //Delete previous character
	if(conta<=16){
		if(conta == 9)segno = 1; //go down
		yLoc = yLoc + segno;
		if(conta%2==0)xLoc = xLoc + dir; //go to the next point
		conta++;
		if(xLoc>xMax-2){ //if you reach the wall
			Player::SetJump(); //ready for a new jump
			xLoc = xMax-2; //fix the x
			while(yLoc>yMax-2)godown(); //go down
		}
		else if(xLoc<1){ //if you reach the wall
			Player::SetJump(); //ready for a new jump
			xLoc = 1; //fix the x
			while(yLoc>yMax-2)godown(); //go down
		}
	}
	else{
		Player::SetJump(); //ready for a new jump
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
		case KEY_UP:
			activejump = true; //active jump
			jump();
		break;
		case KEY_LEFT:
			mvleft();
			break;
		case KEY_RIGHT:
			mvright();
			break;
		case 'h': //activate the gun
			if(num_bullet>0){
				if(strcmp(gun.getName().c_str(),"Pistol") == 0){ //you shoot one bullet
					bullet.blt = bullet.head_insert(bullet.blt,dir,xLoc,yLoc,ind); //add the bullet
					ind = ind + 1; //we want different indexes for the different bullets
					num_bullet--; //decrement bullets
				}
				else if(strcmp(gun.getName().c_str(),"Rifle") == 0){ //you shoot two bullets
					for(int i=0;i<2;i++){
						bullet.blt = bullet.head_insert(bullet.blt,dir,xLoc+i*dir,yLoc,ind); //add the bullet
						ind = ind + 1; //we want different indexes for the different bullets
						num_bullet--; //decrement bullets
					}
				}
				else if(strcmp(gun.getName().c_str(),"Machinegun") == 0){ //you shoot three bullets
					for(int i=0;i<3;i++){
						bullet.blt = bullet.head_insert(bullet.blt,dir,xLoc+i*dir,yLoc,ind); //add the bullet
						ind = ind + 1; //we want different indexes for the different bullets
						num_bullet--; //decrement bullets
					}
				}
				else if(strcmp(gun.getName().c_str(), "Doublegun") == 0){//you shoot two bullets in opposite directions
					bullet.blt = bullet.head_insert(bullet.blt,dir,xLoc,yLoc,ind); //add the bullet
					ind = ind + 1; //we want different indexes for the different bullets
					num_bullet--; //decrement bullets
					bullet.blt = bullet.head_insert(bullet.blt,-dir,xLoc,yLoc,ind); //add the bullet
					ind = ind + 1;
					num_bullet--; //decrement bullets
				}
			}
			break;
		case 't': //activate the teleport
			if(teleportation.getQnt()>0){
				Player::teleport(); //check if you have the teleportation powerup
				teleportation.setQnt(teleportation.getQnt()-1); //delete one teleport which you have
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
			if(strcmp(gun.getName().c_str(),"Pistol") == 0){ //you shoot one bullet
				bullet.blt = bullet.head_insert(bullet.blt,dir,xLoc,yLoc,ind); //add the bullet
				ind = ind + 1; //we want different indexes for the different bullets
				num_bullet--; //decrement bullets
			}
			else if(strcmp(gun.getName().c_str(),"Rifle") == 0){ //you shoot two bullets
				for(int i=0;i<2;i++){
					bullet.blt = bullet.head_insert(bullet.blt,dir,xLoc+i*dir,yLoc,ind); //add the bullet
					ind = ind + 1; //we want different indexes for the different bullets
					num_bullet--; //decrement bullets
				}
			}
			else if(strcmp(gun.getName().c_str(),"Machinegun") == 0){ //you shoot three bullets
				for(int i=0;i<3;i++){
					bullet.blt = bullet.head_insert(bullet.blt,dir,xLoc+i*dir,yLoc,ind); //add the bullet
					ind = ind + 1; //we want different indexes for the different bullets
					num_bullet--; //decrement bullets
				}
			}
			else if(strcmp(gun.getName().c_str(), "Doublegun") == 0){//you shoot two bullets in opposite directions
				bullet.blt = bullet.head_insert(bullet.blt,dir,xLoc,yLoc,ind); //add the bullet
				ind = ind + 1; //we want different indexes for the different bullets
				num_bullet--; //decrement bullets
				bullet.blt = bullet.head_insert(bullet.blt,-dir,xLoc,yLoc,ind); //add the bullet
				ind = ind + 1;
				num_bullet--; //decrement bullets
			}
			break;
		default:
			break;
	}
	return choice;
}

void Player::display(){ //display the character
	if(life>1){
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
		xLoc = 1; //back to beginning
		yLoc = yMax - 2; //back to beginning
		life = life - 1; // one point
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

int Player::getlife(){
	return life;
}

int Player::getcoins(){
	return cash;
}

int Player::getdir(){
	return dir;
}

int Player::getnumblt(){
	return num_bullet;
}

void Player::updatecash(int money){ //update cash
	cash = cash + money;
}

void Player::updateLife(){ //update life
	life = hp.qnt;
}

void Player::updateCoordinates(int x,int y){ //update coordinates
	xLoc = xLoc+x;
	yLoc = yLoc+y;
}


