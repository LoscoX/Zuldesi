/*
 * Bullet.hpp
 *
 *  Created on: 30 dic 2022
 *      Author: david
 */

#include <iostream>
#include <ncurses.h>
#include <ctime>
#include <cstring>
#include <cmath>
#include <cstdlib>


struct bullet{
	int xB; //x of the bullet
	int yB; //y of the bullet
	int dir; //direction of the bullet
	int cod; //how to identify one bullet
	bullet* next;

};

typedef bullet* bullt;

class Bullet{
public:
	Bullet();
	bullt blt; //list of bullet that you are using
	bullt head_insert(bullt h,int dir,int x,int y,int ind); //create new bullet and add it in the gun magazine
	bullt obj_remove(bullt h, int e,bool head); //destroy the first bullet and remove from the gun magazine. If head==true we clean the memory in the head, otherwise no
	void shoot(bullt h,bullt blt); //handle the dynamic of the bullet
};
