/*
 * Enemy.cpp
 *
 *  Created on: 8 dic 2022
 *      Author: david
 */

#include "Enemy.hpp"


/*List of enemies
Every enemy, when it dies, it gives to player a number of points proportional to number of life of enemy
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
	8- Enemy can't move but he can shoot, when the player reaches a specific place (life 5)
	9- Is's the enemy type2 but with two guns
*/

//Enemy type 0

Enemy0::Enemy0(int y, int x, char c, int mv){
	yLoc = y;
	xLoc = x;
	character = c;
	life = 5;
	xpern = x; //save coordinates
	ypern = y; //save coordinates
	cost = mv;
	segno = -1;
}

Enemy0::Enemy0(){ //default constructor
}


void Enemy0::movement(){
	Enemy0::updateCoordinates(segno,0); //implement the movement
	if(xLoc > xpern + cost){ //reach the max of radius
		xLoc = xpern + cost;
		Enemy0::setSign(); //change the direction of the movement
	}
	else if(xLoc < xpern - cost){ //reach the min of radius
		xLoc = xpern - cost;
		Enemy0::setSign(); //change the direction of the movement
	}
}

void Enemy0::EnemyGoDown(){ //go down
	yLoc = yLoc + 1; //Enemy is falling
}

int Enemy0::getx(){ //Take x
	return xLoc;
}

int Enemy0::gety(){
	return yLoc;
}

void Enemy0::injury(){ //Injury
	setLife(getLife()-1);
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

char Enemy0::getChar(){
	return character;
}

void Enemy0::setLife(int life){
	this->life = life;
}

void Enemy0::setXpern(int x)
{
	xpern = x;
}

void Enemy0::updateCoordinates(int x,int y){ //update coordinates
	xLoc = xLoc+x;
	yLoc = yLoc+y;
}

//Enemy type 1

Enemy1::Enemy1(int y, int x, char c,int mv) : Enemy0(y,x,c,mv){
	life = 7;
	up = -1;
}

Enemy1::Enemy1() : Enemy0(){ //default constructor
}

void Enemy1::movement(){
	Enemy0::updateCoordinates(segno,0); //update coordinates
	if(xLoc > xpern + cost){ //reach the max of radius
		yLoc = yLoc + up; //go up
		xLoc = xpern + cost;
		Enemy0::setSign(); //change the direction of the movement
	}
	else if(xLoc < xpern - cost){ //reach the min of radius
		yLoc = yLoc + up; //go up
		xLoc = xpern - cost;
		Enemy0::setSign(); //change the direction of the movement
	}
	else if(yLoc < 25 - 2 - cost){ //lifting depends from cost
		yLoc = 25 - 2 - cost;
		Enemy1::setUp(); //change the direction of the lifting
	}
	else if(yLoc > 25 - 2){
		yLoc = 25 - 2;
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

Enemy2::Enemy2(int y, int x, char c,int mv) : Enemy0(y,x,c,mv){
	life = 7;
}

Enemy2::Enemy2() : Enemy0(){
}

void Enemy2::movement(){
	Enemy0::updateCoordinates(0,segno);
	if(yLoc < 25 - 2 - cost){ //lifting depends from cost
		yLoc = 25 - 2 - cost;
		Enemy0::setSign(); //change the direction of the lifting
	}
	else if(yLoc > 25 - 2){
		yLoc = 25 - 2;
		Enemy0::setSign(); //change the direction of the lifting
	}
}

//Enemy type 3

Enemy3::Enemy3(int y, int x, char c,int mv) : Enemy0(y,x,c,mv){
	life = 2;
	conta = 1;
	up = -1;
}

Enemy3::Enemy3() : Enemy0(){
}

void Enemy3::movement(){
	if(conta<=16){
		if(conta == 9)up = 1; //go down
		yLoc = yLoc + up;
		if(conta%2==0)xLoc = xLoc + segno; //go to the next point
		conta++;
		if(yLoc<1){
			yLoc = 1;
			while(yLoc>25-3)EnemyGoDown(); //go down
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

Enemy4::Enemy4(int y, int x, char c,int mv) : Enemy0(y,x,c,mv){
	life = 3;
	conta = 0; //handle delay of the movement
}

Enemy4::Enemy4() : Enemy0(){
}

void Enemy4::movement(){
	conta++;
	if(conta == 8){ //delay (bigger-->easier)
		xLoc = (xpern - cost) + rand()%(2*cost+1); //generate a random number between xpen-cost and xpern+cost
		conta = 0; //time starts again
	}
}

//Enemy type 5

Enemy5::Enemy5(int y, int x, char c,int mv) : Enemy0(y,x,c,mv){
	life = 2;
}

Enemy5::Enemy5() : Enemy0(){
}

void Enemy5::movement(int direction){
	segno = direction;
	Enemy0::updateCoordinates(direction, 0); //Delete previous character//direction = 1-->dx   direction = -1-->sx
}

//Enemy type 6

Enemy6::Enemy6(int y, int x, char c,int mv) : Enemy0(y,x,c,mv){
	life = 5;
	bullet = Bullet(); //initialize the bullet
	ind = 0; //no bullet
	conta = 0; //no shots
	gun = '-'; //gun
}

Enemy6::Enemy6() : Enemy0(){
}

void Enemy6::movement(){
	conta++; //increment time for the shot
	Enemy0::updateCoordinates(segno,0); //implement the movement
	if(xLoc >= xpern + cost){ //reach the max of radius
		xLoc = xpern + cost;
		Enemy0::setSign();
	}
	else if(xLoc <= xpern - cost){ //reach the min of radius
		xLoc = xpern - cost;
		Enemy0::setSign();
	}
	if(conta==10){ //every 10 milliseconds, the enemy fires
		bullet.blt = bullet.head_insert(bullet.blt,segno,xLoc,yLoc,ind); //add the bullet
		ind = ind + 1; //we want different indexes for the different bullets
		conta = 0;
	}
}

Bullet Enemy6::getBullet(){
	return bullet;
}

bullt Enemy6::setBullet(bullt tmp,int cod){
	tmp = bullet.obj_remove(tmp,cod,false); //remove from the list (don't clean the memory)
	bullet.blt = bullet.obj_remove(bullet.blt,cod,true); //remove from the main list (clean the memory);
	return tmp;
}

bullt Enemy6::Enemyshoot(bullt tmp){
	tmp = bullet.shoot(tmp,bullet.blt);
	return tmp;
}


//Enemy type7

Enemy7::Enemy7(int y, int x, char c,int mv) : Enemy6(y,x,c,mv){
	life = 5;
	bullet = Bullet(); //initialize the bullet
	ind = 0; //no bullet
	conta = 0; //no shots
	gun = '-'; //gun
}

Enemy7::Enemy7() : Enemy6(){
}

void Enemy7::movement(int direction){
	conta++; //increment time for the shot
	segno = direction; //update direction of enemy
	Enemy0::updateCoordinates(segno,0); //direction = 1-->dx   direction = -1-->sx
	if(conta==10){ //every 10 milliseconds, the enemy fires
		bullet.blt = bullet.head_insert(bullet.blt,segno,xLoc,yLoc,ind); //add the bullet
		ind = ind + 1; //we want different indexes for the different bullets
		conta = 0;
	}
}

//Enemy type8

Enemy8::Enemy8(int y, int x, char c,int mv) : Enemy6(y,x,c,mv){
	life = 5;
	bullet = Bullet(); //initialize the bullet
	ind = 0; //no bullet
	conta = 0; //no shots
	gun = '-'; //gun
}

Enemy8::Enemy8() : Enemy6(){
}

void Enemy8::movement(int direction){
	conta++; //increment time for the shot
	segno = direction; //update direction of enemy
	if(conta==5){ //every 5 milliseconds, the enemy fires
		bullet.blt = bullet.head_insert(bullet.blt,segno,xLoc,yLoc,ind); //add the bullet
		ind = ind + 1; //we want different indexes for the different bullets
		conta = 0;
	}
}

//Enemy type9

Enemy9::Enemy9(int y, int x, char c,int mv) : Enemy6(y,x,c,mv){
	life = 5;
	bullet = Bullet(); //initialize the bullet
	ind = 0; //no bullet
	conta = 0; //no shots
	gun = '-'; //gun
}

Enemy9::Enemy9() : Enemy6(){
}

void Enemy9::movement(){
	conta++; //increment time for the shot
	Enemy0::updateCoordinates(0,segno);
	if(yLoc < 25 - 2 - cost){ //lifting depends from cost
		yLoc = 25 - 2 - cost;
		Enemy0::setSign(); //change the direction of the lifting
	}
	else if(yLoc > 25 - 2){
		yLoc = 25 - 2;
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
