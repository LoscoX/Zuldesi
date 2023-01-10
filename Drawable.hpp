/*
 * Drawable.hpp
 *
 *  Created on: 11 dic 2022
 *      Author: david
 */

#include <iostream>
#include <ncurses.h>
#include <ctime>
#include <cstring>
#include <cmath>
#include <cstdlib>

class Drawable{
public:
	Drawable();
	Drawable(int y, int x, char ch);
	int getX();
	int getY();
	char geticon();
protected:
	int y,x;
	char icon;
};
