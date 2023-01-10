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
	life = 10;
	cash = 0;
	points = 0; //no points when you start
	dir = 1; //initial direction
	bullet = Bullet(); //initialize the bullet
	ind = 0; //no bullet
	ind2 = 0; //explosive bullet
	buy = false; //nothing to build when you start
	//jump
	activejump = false; //start without jump
	segno = -1; //segno for parabola
	conta = 1;
	jump_height = 5; //max height of the jump
	NUM_BULLETS = 0; //number of bullets
	NUM_EXPLO_BULLETS = 0; //number of exploding bullets
	//power-up
	gun = Powerup("None", "GUNS", 1, 10, 1); //no gun when you start
	shield = Powerup("Shield", "A shield that blocks damage one time", 0, 15, 1); //no shield when you start
	hp = Powerup("HP", "Get back on your feet one more time", life, 3, 1);
	armor = Powerup("Armor", "Become invincible for a limited time", 0, 10, 1); //no armor when you start
	teleportation = Powerup("Teleport", "Teleport a short distance", 0, 10, 1); //you cannot teleport when you start
	bullets = Powerup("Bullets","Charge of bullets",NUM_BULLETS,5,1); //no bullets when you start
	explo_bullets = Powerup("Explo-Bullets","Charge of explosive bullets",NUM_EXPLO_BULLETS,20,1); //no bullets when you start
	jumping = Powerup("Jump","Change the height of the jump",jump_height,7,1); //basic jump when you start
	fly = Powerup("Fly","You can fly",0,20,1); //you cannot fly when you start
	ARMOR_DURATION[0] = 100; ARMOR_DURATION[1] = 200; ARMOR_DURATION[2] = 500; //different type of Armor duration
	TELEPORT_DISTANCE[0] = dir*20; TELEPORT_DISTANCE[1] = dir*30; TELEPORT_DISTANCE[2] = dir*40; //different teleport distance
	ACTIVE_ARMOR = false; //no armor when you start
	ARMOR_ACTIVE_DURATION = 0; //no armor when you start
	FLY_ACTIVE_DURATION = 0; //no fly when you start
	FLY_DURATION = 500; //duration of the fly
	ACTIVE_FLY = false; //no fly when you start
}

Player::Player()= default; //default constructor

void Player::initialize(){
	display();
}

void Player::SetJump(){ //Rearrange jump variables
	conta = 1; //ready for the next jump
	segno = -1; //ready for the next jump
	activejump = false; //you reach the first floor
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
		if(yLoc<1){ //if you reach the roof
			SetJump(); //ready for a new jump
			while(yLoc<yMax-6)godown(); //godown
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
	if(strcmp(gun.getName().c_str(),"None")!=0) mvwaddch(curwin,yLoc,xLoc+getDir(),' '); //delete gun
	if(strcmp(gun.getName().c_str(),"Doublegun")==0) mvwaddch(curwin,yLoc,xLoc-getDir(),' '); //see gun
	yLoc = yLoc + 1; //you are falling
	if (yLoc>yMax-6) yLoc = yMax-6; //ground floor
}

void Player::goup(){ //go up
	mvwaddch(curwin, yLoc, xLoc,' '); //delete character
	if(armor.getQnt()>0) mvwaddch(curwin,yLoc-1,xLoc,' '); //Delete armor
	if(shield.getQnt()>0) mvwaddch(curwin,yLoc,xLoc-getDir(),' '); //delete shield
	if(shield.getQnt()==0) mvwaddch(curwin,yLoc,xLoc-getDir(),' '); //old gun
	if(strcmp(gun.getName().c_str(),"None")!=0) mvwaddch(curwin,yLoc,xLoc+getDir(),' '); //delete gun
	if(strcmp(gun.getName().c_str(),"Doublegun")==0) mvwaddch(curwin,yLoc,xLoc-getDir(),' '); //see gun
	yLoc = yLoc - 1; //you are lifting
	if(yLoc<1) yLoc = 1;
}

int Player::getmv(){ //move the character with gun by user
	if(ACTIVE_ARMOR){ //check if you have active your armor
		if(ARMOR_ACTIVE_DURATION>0)ARMOR_ACTIVE_DURATION--; //if you have the armor active, you have to decrement the time life of armor
		else ACTIVE_ARMOR = false; //Your armor finishes its life
	}
	int choice = wgetch(curwin);
	switch (choice){
		case KEY_UP: //just go up
			if(FLY_ACTIVE_DURATION>0){ //if you are flying
				goup();
			}
			else{ //if you are not flying
				activejump = true; //active jump
			}
			break;
		case KEY_DOWN: //just go down
			if(FLY_ACTIVE_DURATION>0){ //if you are flying
				godown();
			}
			break;
		case 'h': //activate the gun
			if(bullets.getQnt()>0 && strcmp(gun.getName().c_str(),"Pistol") == 0){ //you shoot one bullet
				bullet.blt = bullet.head_insert(bullet.blt,dir,xLoc,yLoc,ind); //add the bullet
				ind = ind + 1; //we want different indexes for the different bullets
				bullets.setQnt(bullets.getQnt()-1); //decrement bullets
			}
			else if(bullets.getQnt()>0 && strcmp(gun.getName().c_str(),"Rifle") == 0){ //you shoot two bullets
				for(int i=0;i<2;i++){
					bullet.blt = bullet.head_insert(bullet.blt,dir,xLoc+i*dir,yLoc,ind); //add the bullet
					ind = ind + 1; //we want different indexes for the different bullets
				}
				bullets.setQnt(bullets.getQnt()-1); //decrement bullets
			}
			else if(bullets.getQnt()>0 && strcmp(gun.getName().c_str(),"Machinegun") == 0){ //you shoot three bullets
				for(int i=0;i<3;i++){
					bullet.blt = bullet.head_insert(bullet.blt,dir,xLoc+i*dir,yLoc,ind); //add the bullet
					ind = ind + 1; //we want different indexes for the different bullets
				}
				bullets.setQnt(bullets.getQnt()-1); //decrement bullets
			}
			else if(bullets.getQnt()>0 && strcmp(gun.getName().c_str(), "Doublegun") == 0){//you shoot two bullets in opposite directions
				bullet.blt = bullet.head_insert(bullet.blt,dir,xLoc,yLoc,ind); //add the bullet
				ind = ind + 1; //we want different indexes for the different bullets
				bullets.setQnt(bullets.getQnt()-1); //decrement bullets
				bullet.blt = bullet.head_insert(bullet.blt,-dir,xLoc,yLoc,ind); //add the bullet
				ind = ind + 1;
			}
			break;
		case 'a': //activate the armor (time_life of armor starts)
			if(armor.getQnt()>0){ //you have at least on piece of armor
				ARMOR_ACTIVE_DURATION = ARMOR_DURATION[armor.getQnt()-1]; //thanks to the quantity you get the armor duration. For example if you have two pieces of armor, you have 1000 time duration
				armor.setQnt(0); //no armor anymore (you lose all pieces)
				ACTIVE_ARMOR = true;
			}
			break;
		case 'f': //activate the fly (time_life of fly starts)
			if(fly.getQnt()>0){ //you have the fly
				FLY_ACTIVE_DURATION = FLY_DURATION; //thanks to the quantity you get the fly duration.
				fly.setQnt(fly.getQnt()-1); //no fly anymore
				ACTIVE_FLY = true;
			}
			break;
		case 'e': //explosive bullets
			if(explo_bullets.getQnt()>0 && strcmp(gun.getName().c_str(),"None") != 0){ //you shoot one bullet
				explo_bullet.blt = bullet.head_insert(explo_bullet.blt,dir,xLoc,yLoc,ind2); //add the bullet
				ind2 = ind2 + 1; //we want different indexes for the different bullets
				explo_bullets.setQnt(explo_bullets.getQnt()-1); //decrement bullets
			}
			break;
		case 'b': //buy something in the market
			buy = true;
			break;
		default:
			break;
	}
	return choice;
}

int Player::airshoot(){ //during jump movement or down movement, you can just shoot
	int choice = wgetch(curwin);
	switch(choice){
		case 'h': //activate the gun
			if(bullets.getQnt()>0 && strcmp(gun.getName().c_str(),"Pistol") == 0){ //you shoot one bullet
				bullet.blt = bullet.head_insert(bullet.blt,dir,xLoc,yLoc,ind); //add the bullet
				ind = ind + 1; //we want different indexes for the different bullets
				bullets.setQnt(bullets.getQnt()-1); //decrement bullets
			}
			else if(bullets.getQnt()>0 && strcmp(gun.getName().c_str(),"Rifle") == 0){ //you shoot two bullets
				for(int i=0;i<2;i++){
					bullet.blt = bullet.head_insert(bullet.blt,dir,xLoc+i*dir,yLoc,ind); //add the bullet
					ind = ind + 1; //we want different indexes for the different bullets
				}
				bullets.setQnt(bullets.getQnt()-1); //decrement bullets
			}
			else if(bullets.getQnt()>0 && strcmp(gun.getName().c_str(),"Machinegun") == 0){ //you shoot three bullets
				for(int i=0;i<3;i++){
					bullet.blt = bullet.head_insert(bullet.blt,dir,xLoc+i*dir,yLoc,ind); //add the bullet
					ind = ind + 1; //we want different indexes for the different bullets
				}
				bullets.setQnt(bullets.getQnt()-1); //decrement bullets
			}
			else if(bullets.getQnt()>0 && strcmp(gun.getName().c_str(), "Doublegun") == 0){//you shoot two bullets in opposite directions
				bullet.blt = bullet.head_insert(bullet.blt,dir,xLoc,yLoc,ind); //add the bullet
				ind = ind + 1; //we want different indexes for the different bullets
				bullets.setQnt(bullets.getQnt()-1); //decrement bullets
				bullet.blt = bullet.head_insert(bullet.blt,-dir,xLoc,yLoc,ind); //add the bullet
				ind = ind + 1;
			}
			break;
		case 'a': //activate the armor (time_life of armor starts)
			if(armor.getQnt()>0){ //you have at least on piece of armor
				ARMOR_ACTIVE_DURATION = ARMOR_DURATION[armor.getQnt()-1]; //thanks to the quantity you get the armor duration. For example if you have two pieces of armor, you have 1000 time duration
				armor.setQnt(0); //no armor anymore (you lose all pieces)
				ACTIVE_ARMOR = true;
			}
			break;
		case 'e': //explosive bullets
			if(explo_bullets.getQnt()>0 && strcmp(gun.getName().c_str(),"None") != 0){ //you shoot one bullet
				explo_bullet.blt = bullet.head_insert(explo_bullet.blt,dir,xLoc,yLoc,ind2); //add the bullet
				ind2 = ind2 + 1; //we want different indexes for the different bullets
				explo_bullets.setQnt(explo_bullets.getQnt()-1); //decrement bullets
			}
			break;
		default:
			break;
	}
	return choice;
}

void Player::display(){ //display the character
	if(hp.getQnt()>1){
		wattron(curwin,COLOR_PAIR(3)); //color
		mvwaddch(curwin,yLoc,xLoc,character[0]); //see the player
		if(ACTIVE_ARMOR){
			mvwaddch(curwin,yLoc,xLoc,'O'); //see armor
		}
		if(shield.getQnt()>0) mvwaddch(curwin,yLoc,xLoc-getDir(),character[2]); //see the shield
		if(strcmp(gun.getName().c_str(),"None")!=0) mvwaddch(curwin,yLoc,xLoc+getDir(),character[3]); //see the gun
		if(strcmp(gun.getName().c_str(),"Doublegun")==0) mvwaddch(curwin,yLoc,xLoc-getDir(),character[3]); //see the gun
		wattroff(curwin,COLOR_PAIR(3)); //color
	}
	else{ //if you have one life, you become red
		wattron(curwin,COLOR_PAIR(1)); //color
		mvwaddch(curwin,yLoc,xLoc,character[0]); //see the player
		if(ACTIVE_ARMOR){
			mvwaddch(curwin,yLoc,xLoc,'O'); //see armor
		}
		if(shield.getQnt()>0) mvwaddch(curwin,yLoc,xLoc-getDir(),character[2]); //see the shield
		if(strcmp(gun.getName().c_str(),"None")!=0) mvwaddch(curwin,yLoc,xLoc+getDir(),character[3]); //see the gun
		if(strcmp(gun.getName().c_str(),"Doublegun")==0) mvwaddch(curwin,yLoc,xLoc-getDir(),character[3]); //see the gun
		wattroff(curwin,COLOR_PAIR(1));
	}
}


void Player::injury(){ //Injury
	if(shield.getQnt() == 0 && !ACTIVE_ARMOR){ //check if the player has the shield and the armor
		hp.setQnt(hp.getQnt()-1); // one point
	}
	else if(shield.getQnt() > 0 && !ACTIVE_ARMOR){ //check if the player has the shield but not the armor
		shield.setQnt(shield.getQnt()-1); //you lose one piece of shield
	}
	//if you have the armor, you are invincible
}

int Player::getx(){
	return xLoc;
}

int Player::gety(){
	return yLoc;
}

int Player::getLife(){
	return life;
}

int Player::getCoins(){
	return cash;
}

int Player::getDir(){
	return dir;
}

int Player::getPoints(){
	return points;
}

bool Player::getBuy(){
	return buy;
}

void Player::setBuy(bool val){
	this->buy = val;
}

void Player::updateCash(int money){ //update cash
	cash = cash + money;
}

void Player::updatePoints(int points){ 	//update money
	this->points = this->points + points;
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

Bullet Player::getBullet(){
	return bullet;; //bullets
}

bullt Player::setBullet(bullt tmp,int cod){
	tmp = bullet.obj_remove(tmp,cod,false); //remove from the list (don't clean the memory)
	bullet.blt = bullet.obj_remove(bullet.blt,cod,true); //remove from the main list (clean the memory);
	return tmp;
}

Bullet Player::getExploBullet(){
	return explo_bullet; //explosive bullets
}

bullt Player::setExploBullet(bullt tmp,int cod){
	tmp = explo_bullet.obj_remove(tmp,cod,false); //remove from the list (don't clean the memory)
	explo_bullet.blt = explo_bullet.obj_remove(explo_bullet.blt,cod,true); //remove from the main list (clean the memory);
	return tmp;
}

bullt Player::shoot(bullt tmp){ //move bullets
	tmp = bullet.shoot(tmp,bullet.blt); //move bullets
	return tmp;
}

bullt Player::explo_shoot(bullt tmp){ //move explosive bullets
	tmp = bullet.shoot(tmp,explo_bullet.blt); //move explosive bullets
	return tmp;
}

bool Player::getActiveFly(){
	return ACTIVE_FLY; //take active fly variable
}
void Player::setActiveFly(bool val){
	ACTIVE_FLY = val; //set active fly variable
}
bool Player::getActiveJump(){
	return activejump; //take active jump variable
}
int Player::getTELEPORT_DISTANCE(int i){
	return TELEPORT_DISTANCE[i];
}
int Player::getFlyActiveDuration(){
	return FLY_ACTIVE_DURATION; //take fly duration
}
void Player::setFlyActiveDuration(int val){
	FLY_ACTIVE_DURATION = val; //set fly duration
}

//Power up

//get Power-ups
Powerup Player::getGun(){
	return gun;
}
Powerup Player::getShield(){
	return shield;
}
Powerup Player::getHP(){
	return hp;
}
Powerup Player::getArmor(){
	return armor;
}
Powerup Player::getTeleportation(){
	return teleportation; //teleport
}
Powerup Player::getBullets(){
	return bullets; //bullets
}
Powerup Player::getJumping(){
	return jumping; //jump
}
Powerup Player::getFly(){
	return fly; //fly
}
Powerup Player::getExplo_Bullets(){
	return explo_bullets; //explosive bullets
}

//set Power-ups
void Player::setGun(string g){
	gun.setName(g); //gun
}

void Player::setShield(int s){
	shield.setQnt(s); //Shield
}
void Player::setHP(int h){
	hp.setQnt(h); //HP
}
void Player::setArmor(int a){
	armor.setQnt(a); //armor
}
void Player::setTeleportation(int t){
	teleportation.setQnt(t); //teleport
}
void Player::setBullets(int b){
	bullets.setQnt(b); //bullets
}
void Player::setJumping(int j){
	jumping.setQnt(j); //jump
}
void Player::setFly(int f){
	fly.setQnt(f); //fly
}
void Player::setExplo_Bullets(int e){
	explo_bullets.setQnt(e); //explosive bullets
}

