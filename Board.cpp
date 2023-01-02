/*
 * Board.cpp
 *
 *  Created on: 11 dic 2022
 *      Author: david
 */

#include "Board.hpp"

Board::Board(){ //default construct
	construct(0,0);
}

Board::Board(int height,int width){
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

void Board::initialize(){
	clear();
	addBorder();
	refresh();
}


char Board::getInput(){
	return wgetch(board_win);
}

void Board::addBorder(){
	box(board_win, 0, 0);
}

void Board::clear(){
	wclear(board_win);
}

void Board::refresh(){
	wrefresh(board_win);
}

void Board::initializePlatform(int pivot,int h,int ind){ //pivot = first point of the platform,ind = index of the platform,h = height
	for(int i=0;i<len;i++){
		plat[ind].graph[i] = '_';
		plat[ind].xpos[i] = pivot + i;
		plat[ind].ypos[i] = h;
		mvwaddch(board_win,plat[ind].ypos[i],plat[ind].xpos[i],plat[ind].graph[i]);
	}
}

void Board::initializeWall(int pivotx,int pivoty,int ind){ //pivot = first point of the wall,ind = index of the wall
	for(int i=0;i<len;i++){
		wal[ind].graph[i] = 'O';
		wal[ind].xpos[i] = pivotx;
		wal[ind].ypos[i] = pivoty-i;
		mvwaddch(board_win,wal[ind].ypos[i],wal[ind].xpos[i],wal[ind].graph[i]);
	}
}

