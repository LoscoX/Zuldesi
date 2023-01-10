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
    /**
     * Default constructor.
     */
	Bullet();
    /**
     * List of bullet that you are using.
     */
	bullt blt;
    /**
     * Create new bullet and add it in the gun magazine.
     * @param h
     * @param dir
     * @param x
     * @param y
     * @param ind
     * @return
     */
	bullt head_insert(bullt h,int dir,int x,int y,int ind);
    /**
     * Destroy the first bullet and remove from the gun magazine. Just if head is equal to true, memory will be cleaned.
     * @param h
     * @param e
     * @param head
     * @return
     */
	bullt obj_remove(bullt h, int e,bool head);
    /**
     * Handle the dynamic of the bullet.
     * @param h
     * @param blt
     * @return
     */
	bullt shoot(bullt h,bullt blt);
};
