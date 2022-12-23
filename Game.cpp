/*
 * Game.cpp
 *
 *  Created on: 11 dic 2022
 *      Author: david
 */

#include "Game.hpp"

Game::Game(int height,int width){


	start_color();
	init_pair(1,COLOR_RED, COLOR_BLACK);


	board = Board(height,width);
	board.initialize();
	WINDOW* win = board.board_win;
	player = Player(win,height-2,1,'@');
	player.initialize();
	enemy[0] = Enemy(win,height-2,width-10,'0',3,1);
	enemy[0].initialize();
	enemy[1] = Enemy(win,height-2,width-25,'0',5,1);
	enemy[1].initialize();
	enemy[2] = Enemy(win,height-2,width-40,'0',7,1);
	enemy[2].initialize();
	game_over = false;
}

void Game::interaction(int i){
	if(player.getx() == enemy[i].getx() && player.gety() == enemy[i].gety()) player.injury();
}

void Game::updateState(){
	Game::displaylife();
	player.getmv();
	player.display();
	//if(enemy.death() == false){
	for(int i=0;i<len;i++){
		enemy[i].movement(enemy[i].cost);
		enemy[i].display();
		Game::interaction(i);
	}
	//}
	if(player.getlife() == 0) game_over = true;
}

void Game::redraw(){
	board.refresh();
}

bool Game::isOver(){
	return game_over;
}

void Game::displaylife(){ //display life
	mvwaddch(board.board_win, 0, 0,' ');
	mvwaddch(board.board_win, 1, 0,' ');
	mvwprintw(board.board_win,0,0,"%d",player.getlife());
}


