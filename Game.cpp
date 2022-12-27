/*
 * Game.cpp
 *
 *  Created on: 11 dic 2022
 *      Author: david
 */

#include "Game.hpp"

Game::Game(int height,int width){

	start_color();
	init_pair(1,COLOR_RED, COLOR_BLACK); //color enemy type 0
	init_pair(2,COLOR_BLUE, COLOR_BLACK); //color enemy type 1
	init_pair(3,COLOR_YELLOW,COLOR_BLACK); //color enemy type 2
	init_pair(4,COLOR_GREEN,COLOR_BLACK); //color enemy type 3
	init_pair(5,COLOR_WHITE,COLOR_BLACK); //color enemy type 4


	board = Board(height,width); //create the board
	board.initialize(); //initialize the board
	WINDOW* win = board.board_win;

	player = Player(win,height-2,1,'@'); //create the player
	player.initialize(); //initialize the player

	int k = len; //max number of enemies of type i

	//type0
	n0 = 1 + rand()%k; //number of enemy of type 0
	for(int i=0;i<n0;i++){
		enemy0[i] = Enemy0(win,height-2,(1 + rand()%(width-2)),'0',7,1); //create the enemy
		enemy0[i].initialize(); //initialize the enemy
	}

	//type1
	n1 = 1 + rand()%k; //number of enemy of type 1
	for(int i=0;i<n1;i++){
		enemy1[i] = Enemy1(win,height-2,(1 + rand()%(width-2)),'1',9,2);
		enemy1[i].initialize();
	}

	//type2
	n2 = 1 + rand()%k; //number of enemy of type 2
	for(int i=0;i<n2;i++){
		enemy2[i] = Enemy2(win,height-2,(1 + rand()%(width-2)),'2',7,3);
		enemy2[i].initialize();
	}

	//type3
	n3 = 1 + rand()%k; //number of enemy of type 3
	for(int i=0;i<n3;i++){
		enemy3[i] = Enemy3(win,height-2,(1 + rand()%(width-2)),'3',9,4);
		enemy3[i].initialize();
	}

	//type4
	n4 = 1 + rand()%k; //number of enemy of type 4
	for(int i=0;i<n4;i++){
		enemy4[i] = Enemy4(win,height-2,(1 + rand()%(width-2)),'4',9,5);
		enemy4[i].initialize();
	}
	game_over = false;
}

void Game::interaction1(int i,Enemy0 e){
	if(player.getx() == e.getx() && player.gety() == e.gety()) player.injury();
}

void Game::updateState(){
	//display life
	Game::displaylife();
	//movement of the player
	player.getmv();
	player.display();
	//Enemies movement

	//Enemy type 0
	for(int i=0;i<n0;i++){
		enemy0[i].movement(enemy0[i].cost);
		enemy0[i].display();
		Game::interaction1(i,enemy0[i]);
	}
	//Enemy type 1
	for(int i=0;i<n1;i++){
		enemy1[i].movement(enemy1[i].cost);
		enemy1[i].display();
		Game::interaction1(i,enemy1[i]);
	}
	//Enemy type 2
	for(int i=0;i<n2;i++){
		enemy2[i].movement(enemy2[i].cost);
		enemy2[i].display();
		Game::interaction1(i,enemy2[i]);
	}
	//Enemy type 3
	for(int i=0;i<n3;i++){
		enemy3[i].movement(enemy3[i].cost);
		enemy3[i].display();
		Game::interaction1(i,enemy3[i]);
	}
	//Enemy type 4
	for(int i=0;i<n4;i++){
		enemy4[i].movement(enemy4[i].cost);
		enemy4[i].display();
		Game::interaction1(i,enemy4[i]);
	}

	if(player.getlife() == 0) game_over = true; //Player death
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


