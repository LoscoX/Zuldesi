/*
 * Board.cpp
 *
 *  Created on: 11 dic 2022
 *      Author: david
 */

#include "Board.hpp"

Board::Board(){
	construct(0,0);
}

Board::Board(int height,int width){
	construct(height-1,width);
}

void Board::construct(int height,int width){
	int xMax,yMax;
	getmaxyx(stdscr,yMax,xMax);
	board_win = newwin(height,width, (yMax / 2) - (height / 2), (xMax / 2) - (width / 2));
	wtimeout(board_win,50); //need this command for the movement of ALL characters (number of delay)
	keypad(board_win,true);
}

void Board::initialize(){
	clear();
	addBorder();
	refresh();
}

//void Board::addAt(int y, int x, char ch){
	//mvwaddch(board_win,y,x,ch);
//}

char Board::getInput(){
	return wgetch(board_win);
}

void Board::addBorder(){
	box(board_win, 0, 0);
}

//void Board::add(Drawable drawable){
	//addAt(drawable.getY(),drawable.getX(),drawable.geticon());
//}

void Board::clear(){
	wclear(board_win);
}

void Board::refresh(){
	wrefresh(board_win);
}

