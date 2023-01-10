/*
 * Drawable.cpp
 *
 *  Created on: 11 dic 2022
 *      Author: david
 */

#include "Drawable.hpp"


Drawable::Drawable(){
	y = x = 0;
	icon = ' ';
}

Drawable::Drawable(int y, int x, char ch){
	this->y = y;
	this->x = x;
	this->icon = ch;
}

int Drawable::getX(){
	return x;
}

int Drawable::getY(){
	return y;
}

char Drawable::geticon(){
	return icon;
}



