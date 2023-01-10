/*
 * board.hpp
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

/**
 * Length of one structure.
 */
const int len = 7;

/**
 * Structure for a platform.
 */
struct platform{
	char graph[len];
	int xpos[len];
	int ypos[len];
};


/**
 * Structure for a wall.
 */
struct wall{
	char graph[len];
	int xpos[len];
	int ypos[len];
};

/**
 * Number of one type of objects.
 */
const int num_ogg = 30;

/**
 * Manage game borders.
 */
class Board{
public:
	WINDOW *board_win;
    /**
     * Default constructor.
     */
	Board();
    /**
     * Constructor with size parameters.
     * @param height
     * @param width
     */
	Board(int height, int width);
    /**
     * create a border in the input coordinate.
     * @param x
     * @param y
     */
	void addBorder(int x,int y);
    /**
     * Clear the borders window.
     */
	void clear();
    /**
     * Refresh the borders window.
     */
	void refresh();
    /**
     * Initialize the window getting in inputs its width and high.
     * @param x Width of the window.
     * @param y Height of the window.
     */
	void initialize(int x,int y);
    /**
     *
     * @return Height of the window.
     */
	int getHeight();
    /**
     *
     * @return Width of the window.
     */
	int getWidth();
protected:
    /**
     * Make the board with size parameters.
     * @param height
     * @param width
     */
	void construct(int height, int width);
    /**
     * Height and width of the board.
     */
	int height,width;
};
