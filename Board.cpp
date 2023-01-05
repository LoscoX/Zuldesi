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

void Board::initializePlatform(int pivot,int h,int ind){ //pivot = first point of the platform,ind = index of the platform,h = height
	for(int i=0;i<len;i++){
		plat[ind].graph[i] = '-'; //symbol of the platform
		plat[ind].xpos[i] = pivot + i;
		plat[ind].ypos[i] = h; //height
		mvwaddch(board_win,plat[ind].ypos[i],plat[ind].xpos[i],plat[ind].graph[i]); //graph
	}
}

void Board::initializeWall(int pivotx,int pivoty,int ind){ //pivot = first point of the wall,ind = index of the wall
	for(int i=0;i<len;i++){
		wal[ind].graph[i] = 'O'; //symbol of the wall
		wal[ind].xpos[i] = pivotx;
		wal[ind].ypos[i] = pivoty-i;
		mvwaddch(board_win,wal[ind].ypos[i],wal[ind].xpos[i],wal[ind].graph[i]); //graph
	}
}

void Board::deleteWall(int pivotx,int pivoty,int ind){
	for(int i=0;i<len;i++){
		wal[ind].graph[i] = ' '; //symbol of the wall
		mvwaddch(board_win,wal[ind].ypos[i],wal[ind].xpos[i],wal[ind].graph[i]); //graph
	}
}

void Board::deletePlatform(int pivot,int h,int ind){ //pivot = first point of the platform,ind = index of the platform,h = height
	for(int i=0;i<len;i++){
		plat[ind].graph[i] = ' '; //symbol of the platform
		mvwaddch(board_win,plat[ind].ypos[i],plat[ind].xpos[i],plat[ind].graph[i]); //graph
	}
}

bool Board::IsThereStructure(int x,int y){ //check if one character collides with one of the structure in the map
	int i;
	int j = 0;
	bool found = false;
	while(j<num_ogg && !found){
		i = 0;
		while(i<len && !found){
			if(x == wal[j].xpos[i] && y == wal[j].ypos[i]) found = true; //collision
 			if(x == plat[j].xpos[i] && y == plat[j].ypos[i]) found = true; //collision
			i++; //change the piece
		}
		j++; //change the structure
	}
	return found;
}

