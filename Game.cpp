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
	init_pair(5,COLOR_MAGENTA,COLOR_BLACK); //color enemy type 4
	init_pair(6,COLOR_CYAN,COLOR_BLACK); //color enemy type 5


	board = Board(height,width); //create the board
	board.initialize(); //initialize the board
	WINDOW* win = board.board_win;

	player = Player(win,height-2,1); //create the player
	player.initialize(); //initialize the player

	time = 0;

	enemies0 = NULL; //initialize the list
	enemies1 = NULL; //initialize the list
	enemies2 = NULL; //initialize the list
	enemies3 = NULL; //initialize the list
	enemies4 = NULL; //initialize the list
	enemies5 = NULL; //initialize the list

	coins = NULL; //initialize coins

	nc = rand()%10; //number of coins

	for(int i=0;i<nc;i++){ //create coins with random position and add them to the list
		coins = Game::head_insert_coin(coins,i,(1+rand()%(width-2)),height-2);
	}
	Game::initializeCoins(); //initialize coins

	int k = 2; //max number of enemies

	n0 = rand()%k; //number of enemies of type 0
	for(int i=0;i<n0;i++){
		Enemy0 e = Enemy0(win,height-2,(1 + rand()%(width-2)),'0',7,1); //create one enemy
		enemies0 = Game::head_insert_enemy0(enemies0,e,i); //add the enemy into the list
	}

	n1 = rand()%k; //number of enemies of type 1
	for(int i=0;i<n1;i++){
		Enemy1 e = Enemy1(win,height-2,(1 + rand()%(width-2)),'1',9,2); //create one enemy
		enemies1 = Game::head_insert_enemy1(enemies1,e,i); //add the enemy into the list
	}

	n2 = rand()%k; //number of enemies of type 2
	for(int i=0;i<n2;i++){
		Enemy2 e = Enemy2(win,height-2,(1 + rand()%(width-2)),'2',9,3); //create one enemy
		enemies2 = Game::head_insert_enemy2(enemies2,e,i); //add the enemy into the list
	}

	n3 = rand()%k; //number of enemies of type 3
	for(int i=0;i<n3;i++){
		Enemy3 e = Enemy3(win,height-2,(1 + rand()%(width-2)),'3',9,4); //create one enemy
		enemies3 = Game::head_insert_enemy3(enemies3,e,i); //add the enemy into the list
	}

	n4 = rand()%k; //number of enemies of type 4
	for(int i=0;i<n4;i++){
		Enemy4 e = Enemy4(win,height-2,(1 + rand()%(width-2)),'4',7,5); //create one enemy
		enemies4 = Game::head_insert_enemy4(enemies4,e,i); //add the enemy into the list
	}

	n5 = rand()%k; //number of enemies of type 5
	for(int i=0;i<n5;i++){
		Enemy5 e = Enemy5(win,height-2,(1 + rand()%(width-2)),'5',7,6); //create one enemy
		enemies5 = Game::head_insert_enemy5(enemies5,e,i); //add the enemy into the list
	}

	//initialize the enemies
	Game::initializeEnemies();

	game_over = false;
}

void Game::initializeEnemies(){ //initialize enemies
	listenm0 tmp = enemies0; //enemies is global!!
	while(tmp!=NULL){
		tmp->enemy.initialize();
		tmp = tmp->next;
	}

	listenm1 tmp1 = enemies1; //enemies is global!!
	while(tmp1!=NULL){
		tmp1->enemy.initialize();
		tmp1 = tmp1->next;
	}

	listenm2 tmp2 = enemies2; //enemies is global!!
	while(tmp2!=NULL){
		tmp2->enemy.initialize();
		tmp2 = tmp2->next;
	}

	listenm3 tmp3 = enemies3; //enemies is global!!
	while(tmp3!=NULL){
		tmp3->enemy.initialize();
		tmp3 = tmp3->next;
	}

	listenm4 tmp4 = enemies4; //enemies is global!!
	while(tmp4!=NULL){
		tmp4->enemy.initialize();
		tmp4 = tmp4->next;
	}

	listenm5 tmp5 = enemies5; //enemies is global!!
	while(tmp5!=NULL){
		tmp5->enemy.initialize();
		tmp5 = tmp5->next;
	}
}

void Game::updateState(){

	//display life
	Game::displaylife();
	//display coins
	Game::displaycoins();

	//player movement
	Game::playermovement();

	//Update coins
	Game::updateCoins();

	//handle shooting
	Game::shooting();

	//enemy movement
	if(time%5 == 0) Game::enemymovement(); //you want to slow down enemies

	time++;

	if(player.getlife() == 0) game_over = true; //Player death
}

listenm0 Game::head_insert_enemy0(listenm0 h,Enemy0 e, int val){ //add one enemy type0 to the list
	listenm0 tmp = new listenemy0;
	tmp->val = val;
	tmp->enemy = e;
	tmp->next = h;
	return tmp;
}

listenm1 Game::head_insert_enemy1(listenm1 h,Enemy1 e, int val){ //add one enemy type1 to the list
	listenm1 tmp = new listenemy1;
	tmp->val = val;
	tmp->enemy = e;
	tmp->next = h;
	return tmp;
}

listenm2 Game::head_insert_enemy2(listenm2 h,Enemy2 e, int val){ //add one enemy type2 to the list
	listenm2 tmp = new listenemy2;
	tmp->val = val;
	tmp->enemy = e;
	tmp->next = h;
	return tmp;
}

listenm3 Game::head_insert_enemy3(listenm3 h,Enemy3 e, int val){ //add one enemy type3 to the list
	listenm3 tmp = new listenemy3;
	tmp->val = val;
	tmp->enemy = e;
	tmp->next = h;
	return tmp;
}

listenm4 Game::head_insert_enemy4(listenm4 h,Enemy4 e, int val){ //add one enemy type4 to the list
	listenm4 tmp = new listenemy4;
	tmp->val = val;
	tmp->enemy = e;
	tmp->next = h;
	return tmp;
}

listenm5 Game::head_insert_enemy5(listenm5 h,Enemy5 e, int val){ //add one enemy type5 to the list
	listenm5 tmp = new listenemy5;
	tmp->val = val;
	tmp->enemy = e;
	tmp->next = h;
	return tmp;
}

listenm0 Game::obj_remove_enemy0(listenm0 h,int cod){ //remove the enemy type0 with this cod
	if (h==NULL) return h;
	else if(h->val == cod){ //if the enemy is in the top of the list
		//problem with the memory
		h = h->next;
	}
	else{
		listenm0 tmp = h;
		bool found = false;
		while(tmp->next!=NULL && !found){
			if(tmp->next->val == cod){ //enemy in the middle of the list (ok also for the tail)
				listenm0 tmp2 = tmp->next;
				tmp->next = tmp2->next;
				delete tmp2; //clean memory
				tmp2 = NULL;
				found = true;
			}
			else tmp = tmp->next;
		}
	}
	return h;
}

listenm1 Game::obj_remove_enemy1(listenm1 h,int cod){ //remove the enemy type1 with this cod
	if (h==NULL) return h;
	else if(h->val == cod){ //if the enemy is in the top of the list
		//problem with the memory
		h = h->next;
	}
	else{
		listenm1 tmp = h;
		bool found = false;
		while(tmp->next!=NULL && !found){
			if(tmp->next->val == cod){ //enemy in the middle of the list (ok also for the tail)
				listenm1 tmp2 = tmp->next;
				tmp->next = tmp2->next;
				delete tmp2; //clean memory
				tmp2 = NULL;
				found = true;
			}
			else tmp = tmp->next;
		}
	}
	return h;
}

listenm2 Game::obj_remove_enemy2(listenm2 h,int cod){ //remove the enemy type2 with this cod
	if (h==NULL) return h;
	else if(h->val == cod){ //if the enemy is in the top of the list
		//problem with the memory
		h = h->next;
	}
	else{
		listenm2 tmp = h;
		bool found = false;
		while(tmp->next!=NULL && !found){
			if(tmp->next->val == cod){ //enemy in the middle of the list (ok also for the tail)
				listenm2 tmp2 = tmp->next;
				tmp->next = tmp2->next;
				delete tmp2; //clean memory
				tmp2 = NULL;
				found = true;
			}
			else tmp = tmp->next;
		}
	}
	return h;
}

listenm3 Game::obj_remove_enemy3(listenm3 h,int cod){ //remove the enemy type3 with this cod
	if (h==NULL) return h;
	else if(h->val == cod){ //if the enemy is in the top of the list
		//problem with the memory
		h = h->next;
	}
	else{
		listenm3 tmp = h;
		bool found = false;
		while(tmp->next!=NULL && !found){
			if(tmp->next->val == cod){ //enemy in the middle of the list (ok also for the tail)
				listenm3 tmp2 = tmp->next;
				tmp->next = tmp2->next;
				delete tmp2; //clean memory
				tmp2 = NULL;
				found = true;
			}
			else tmp = tmp->next;
		}
	}
	return h;
}

listenm4 Game::obj_remove_enemy4(listenm4 h,int cod){ //remove the enemy type 4 with this cod
	if (h==NULL) return h;
	else if(h->val == cod){ //if the enemy is in the top of the list
		//problem with the memory
		h = h->next;
	}
	else{
		listenm4 tmp = h;
		bool found = false;
		while(tmp->next!=NULL && !found){
			if(tmp->next->val == cod){ //enemy in the middle of the list (ok also for the tail)
				listenm4 tmp2 = tmp->next;
				tmp->next = tmp2->next;
				delete tmp2; //clean memory
				tmp2 = NULL;
				found = true;
			}
			else tmp = tmp->next;
		}
	}
	return h;
}

listenm5 Game::obj_remove_enemy5(listenm5 h,int cod){ //remove the enemy type5 with this cod
	if (h==NULL) return h;
	else if(h->val == cod){ //if the enemy is in the top of the list
		//problem with the memory
		h = h->next;
	}
	else{
		listenm5 tmp = h;
		bool found = false;
		while(tmp->next!=NULL && !found){
			if(tmp->next->val == cod){ //enemy in the middle of the list (ok also for the tail)
				listenm5 tmp2 = tmp->next;
				tmp->next = tmp2->next;
				delete tmp2; //clean memory
				tmp2 = NULL;
				found = true;
			}
			else tmp = tmp->next;
		}
	}
	return h;
}

void Game::interaction(Enemy0 e){ //interaction between enemies and player
	if(abs(player.getx() - e.getx()) <=1 && abs(player.gety() - e.gety())<=1) player.injury(); //if you are in a neighborhood of the enemy, you lose one life
}

int Game::directionSmartEnemy(Enemy5 e){ //handle the direction of the smart enemy
	if(player.getx() - e.getx() > 0) return 1; //positive direction
	else if(player.getx() - e.getx() < 0) return -1; //negative direction
	else return 0;
}

void Game::redraw(){
	board.refresh();
}

bool Game::isOver(){
	return game_over;
}

void Game::displaylife(){ //display life
	mvwprintw(board.board_win,0,0,"Life: ");
	mvwprintw(board.board_win,0,5,"%d",player.getlife());
}

void Game::displaycoins(){ //display coins
	mvwprintw(board.board_win,0,103,"Money: ");
	mvwprintw(board.board_win,0,109,"%d",player.getcoins());
}

void Game::shooting(){
	bullt tmp = player.blt;
	int codice;
	while(tmp!=NULL){ //you have to move all the bullets
		player.shoot(tmp); //move the bullet if it exists
		if(Game::enemydeath(tmp) == true){
			mvwaddch(board.board_win,tmp->yB,tmp->xB,' '); //delete graphically the bullet
			codice = tmp->cod; //save the code of the bullet
			tmp = player.obj_remove(tmp, codice); //delete the bullet
			player.blt = player.obj_remove(player.blt, codice); //delete the bullet from the main list
		}
		else tmp = tmp->next;
	}
}

bool Game::enemydeath(bullt tmp){ //check if one bullet touch one of the enemy
	//check enemy0
	listenm0 tmp0 = enemies0;
	bool found = false;
	int codice; //variable where we can save the code of one enemy
	while(tmp0!=NULL && !found){
		if(abs(tmp->xB - tmp0->enemy.getx())<=1 && abs(tmp->yB - tmp0->enemy.gety())<=1){ //check if the bullet and the enemy are in the same place (the same approach used in interaction1)
			tmp0->enemy.injury(); //injury for the enemy
			found = true; //you have removed this bullet, so you can stop the cycle
			if(tmp0->enemy.getlife() <= 0){ //Enemy life = 0
				mvwaddch(board.board_win,tmp0->enemy.gety(),tmp0->enemy.getx(),' '); //delete graphically the enemy
				codice = tmp0->val; //save the code of the enemy
				tmp0 = Game::obj_remove_enemy0(tmp0, codice); //if it is died, you have to remove from the list
				enemies0 = Game::obj_remove_enemy0(enemies0, codice); //if it is died, you have to remove from the main list
			}
			else tmp0 = tmp0->next;
		}
		else tmp0 = tmp0->next;
	}

	//check enemy1
	listenm1 tmp1 = enemies1;
	while(tmp1!=NULL && !found){
		if(abs(tmp->xB - tmp1->enemy.getx())<=1 && abs(tmp->yB - tmp1->enemy.gety())<=1){ //check if the bullet and the enemy are in the same place (the same approach used in interaction1)
			tmp1->enemy.injury(); //injury for the enemy
			found = true; //you have removed this bullet, so you can stop the cycle
			if(tmp1->enemy.getlife() <= 0){ //Enemy life = 0
				mvwaddch(board.board_win,tmp1->enemy.gety(),tmp1->enemy.getx(),' '); //delete graphically the enemy
				codice = tmp1->val; //save the code of the enemy
				tmp1 = Game::obj_remove_enemy1(tmp1, codice); //if it is died, you have to remove from the list
				enemies1 = Game::obj_remove_enemy1(enemies1, codice); //if it is died, you have to remove from the main list
			}
			else tmp1 = tmp1->next;
		}
		else tmp1 = tmp1->next;
	}

	//check enemy2
	listenm2 tmp2 = enemies2;
	while(tmp2!=NULL && !found){
		if(abs(tmp->xB - tmp2->enemy.getx())<=1 && abs(tmp->yB - tmp2->enemy.gety())<=1){ //check if the bullet and the enemy are in the same place (the same approach used in interaction1)
			tmp2->enemy.injury(); //injury for the enemy
			found = true; //you have removed this bullet, so you can stop the cycle
			if(tmp2->enemy.getlife() <= 0){ //Enemy life = 0
				mvwaddch(board.board_win,tmp2->enemy.gety(),tmp2->enemy.getx(),' '); //delete graphically the enemy
				codice = tmp2->val; //save the code of the enemy
				tmp2 = Game::obj_remove_enemy2(tmp2, codice); //if it is died, you have to remove from the list
				enemies2 = Game::obj_remove_enemy2(enemies2, codice); //if it is died, you have to remove from the main list
			}
			else tmp2 = tmp2->next;
		}
		else tmp2 = tmp2->next;
	}

	//check enemy3
	listenm3 tmp3 = enemies3;
	while(tmp3!=NULL && !found){
		if(abs(tmp->xB - tmp3->enemy.getx())<=1 && abs(tmp->yB - tmp3->enemy.gety())<=1){ //check if the bullet and the enemy are in the same place (the same approach used in interaction1)
			tmp3->enemy.injury(); //injury for the enemy
			found = true; //you have removed this bullet, so you can stop the cycle
			if(tmp3->enemy.getlife() <= 0){ //Enemy life = 0
				mvwaddch(board.board_win,tmp3->enemy.gety(),tmp3->enemy.getx(),' '); //delete graphically the enemy
				codice = tmp3->val; //save the code of the enemy
				tmp3 = Game::obj_remove_enemy3(tmp3, codice); //if it is died, you have to remove from the list
				enemies3 = Game::obj_remove_enemy3(enemies3, codice); //if it is died, you have to remove from the main list
			}
			else tmp3 = tmp3->next;
		}
		else tmp3 = tmp3->next;
	}

	//check enemy4
	listenm4 tmp4 = enemies4;
	while(tmp4!=NULL && !found){
		if(abs(tmp->xB - tmp4->enemy.getx())<=1 && abs(tmp->yB - tmp4->enemy.gety())<=1){ //check if the bullet and the enemy are in the same place (the same approach used in interaction1)
			tmp4->enemy.injury(); //injury for the enemy
			found = true; //you have removed this bullet, so you can stop the cycle
			if(tmp4->enemy.getlife() <= 0){ //Enemy life = 0
				mvwaddch(board.board_win,tmp4->enemy.gety(),tmp4->enemy.getx(),' '); //delete graphically the enemy
				codice = tmp4->val; //save the code of the enemy
				tmp4 = Game::obj_remove_enemy4(tmp4, codice); //if it is died, you have to remove from the list
				enemies4 = Game::obj_remove_enemy4(enemies4, codice); //if it is died, you have to remove from the main list
			}
			else tmp4 = tmp4->next;
		}
		else tmp4 = tmp4->next;
	}

	//check enemy5
	listenm5 tmp5 = enemies5;
	while(tmp5!=NULL && !found){
		if(abs(tmp->xB - tmp5->enemy.getx())<=1 && abs(tmp->yB - tmp5->enemy.gety())<=1){ //check if the bullet and the enemy are in the same place (the same approach used in interaction1)
			tmp5->enemy.injury(); //injury for the enemy
			found = true; //you have removed this bullet, so you can stop the cycle
			if(tmp5->enemy.getlife() <= 0){ //Enemy life = 0
				mvwaddch(board.board_win,tmp5->enemy.gety(),tmp5->enemy.getx(),' '); //delete graphically the enemy
				codice = tmp5->val; //save the code of the enemy
				tmp5 = Game::obj_remove_enemy5(tmp5, codice); //if it is died, you have to remove from the list
				enemies5 = Game::obj_remove_enemy5(enemies5, codice); //if it is died, you have to remove from the main list
			}
			else tmp5 = tmp5->next;
		}
		else tmp5 = tmp5->next;
	}
	return found;
}

void Game::playermovement(){
	//if you are jumping you cannot move
	if(!player.activejump) player.getmv();
	else{
		player.jump();
		player.display(); //show the jump
		player.jumpandshoot(); //if you want shoot you have to press h
	}
	//see player
	player.display();
}

void Game::enemymovement(){	//Enemies movement
	listenm0 tmp = enemies0; //type0
	while(tmp!=NULL){
		tmp->enemy.movement(); //move one enemy
		tmp->enemy.display(); //see one enemy
		Game::interaction(tmp->enemy); //check the interaction between one enemy and the player
		tmp = tmp->next; //go to the next enemy
	}

	listenm1 tmp1 = enemies1; //type1
	while(tmp1!=NULL){
		tmp1->enemy.movement(); //move one enemy
		tmp1->enemy.display(); //see one enemy
		Game::interaction(tmp1->enemy); //check the interaction between one enemy and the player
		tmp1 = tmp1->next; //go to the next enemy
	}

	listenm2 tmp2 = enemies2; //type2
	while(tmp2!=NULL){
		tmp2->enemy.movement(); //move one enemy
		tmp2->enemy.display(); //see one enemy
		Game::interaction(tmp2->enemy); //check the interaction between one enemy and the player
		tmp2 = tmp2->next; //go to the next enemy
	}

	listenm3 tmp3 = enemies3; //type3
	while(tmp3!=NULL){
		tmp3->enemy.movement(); //move one enemy
		tmp3->enemy.display(); //see one enemy
		Game::interaction(tmp3->enemy); //check the interaction between one enemy and the player
		tmp3 = tmp3->next; //go to the next enemy
	}

	listenm4 tmp4 = enemies4; //type4
	while(tmp4!=NULL){
		tmp4->enemy.movement(); //move one enemy
		tmp4->enemy.display(); //see one enemy
		Game::interaction(tmp4->enemy); //check the interaction between one enemy and the player
		tmp4 = tmp4->next; //go to the next enemy
	}

	int dir;
	listenm5 tmp5 = enemies5;
	while(tmp5!=NULL){
		dir = Game::directionSmartEnemy(tmp5->enemy);
		tmp5->enemy.movement(dir); //move one enemy
		tmp5->enemy.display(); //see one enemy
		Game::interaction(tmp5->enemy); //check the interaction between one enemy and the player
		tmp5 = tmp5->next; //go to the next enemy
	}
}

mony Game::head_insert_coin(mony h,int val,int x,int y){
	mony tmp = new money;
	tmp->val = val;
	tmp->x = x;
	tmp->y = y;
	tmp->next = h;
	return tmp;
}

void Game::initializeCoins(){
	mony tmp = coins;
	while(tmp!=NULL){
		mvwaddch(board.board_win,tmp->y,tmp->x,'$');
		tmp = tmp->next;
	}
}

void Game::updateCoins(){
	mony tmp = coins;
	int codice; //save cod
	while(tmp!=NULL){
		if(player.getx() == tmp->x && player.gety() == tmp->y){ //if the player and the coin are in the same place, you have to remove it and delete from the list
			player.updatecash(); //update wallet
			codice = tmp->val;
			tmp = Game::removeCoins(tmp,codice); //remove coin from the list
			coins = Game::removeCoins(coins,codice); //remove coin from the main list
		}
		else{
			mvwaddch(board.board_win,tmp->y,tmp->x,'$'); //avoid that enemies or bullets delete our coins
			tmp = tmp->next;
		}
	}
}

mony Game::removeCoins(mony h,int cod){ //remove the coin with this cod
	if (h==NULL) return h;
	else if(h->val == cod){ //if the coin is in the top of the list
		//problem with the memory
		h = h->next;
	}
	else{
		mony tmp = h;
		bool found = false;
		while(tmp->next!=NULL && !found){
			if(tmp->next->val == cod){ //coin in the middle of the list (ok also for the tail)
				mony tmp2 = tmp->next;
				tmp->next = tmp2->next;
				delete tmp2; //clean memory
				tmp2 = NULL;
				found = true;
			}
			else tmp = tmp->next;
		}
	}
	return h;
}


