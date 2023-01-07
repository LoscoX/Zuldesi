/*
 * Board.cpp
 *
 *  Created on: 11 dic 2022
 *      Author: david
 */

#include "Board.hpp"

Board::Board(){ //default construct
	this->height = 0;
	this->width = 0;
	construct(0,0);
}

Board::Board(int height,int width){
	this->height = height;
	this->width = width;
	construct(height,width);
}

void Board::construct(int height,int width){
	int xMax,yMax;
	getmaxyx(stdscr,yMax,xMax);
	board_win = newwin(height,width, (yMax / 2) - (height / 2), (xMax / 2) - (width / 2));
	wtimeout(board_win,10); //need this command for the movement of ALL characters
	//the second term is the number of milliseconds to block or wait for input.
	keypad(board_win,true);
}

void Board::initialize(int x,int y){
	clear();
	addBorder(x,y);
	refresh();
}


char Board::getInput(){
	return wgetch(board_win);
}

void Board::addBorder(int x,int y){
	box(board_win, x, y);
}

void Board::clear(){
	wclear(board_win);
}

void Board::refresh(){
	wrefresh(board_win);
}
