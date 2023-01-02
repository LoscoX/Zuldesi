/*
 * Game.cpp
 *
 *  Created on: 11 dic 2022
 *      Author: david
 */

#include "Game.hpp"
#include <cstdlib>

Game::Game(int height,int width){

	start_color();
	init_pair(1,COLOR_RED, COLOR_BLACK); //color enemy type 0/6
	init_pair(2,COLOR_BLUE, COLOR_BLACK); //color enemy type 1
	init_pair(3,COLOR_YELLOW,COLOR_BLACK); //color enemy type 2
	init_pair(4,COLOR_GREEN,COLOR_BLACK); //color enemy type 3
	init_pair(5,COLOR_MAGENTA,COLOR_BLACK); //color enemy type 4
	init_pair(6,COLOR_CYAN,COLOR_BLACK); //color enemy type 5/7
	init_pair(7,COLOR_WHITE,COLOR_BLACK); //color enemy type 8

	difficulty = 0; //diffcult = 0 when you start the game

	//Initialize Powerups (quantity of the guns is fixed to 1-->you can have just one gun)
    guns[0] = Powerup("Pistol", "you shoot one bullet", 1, 1, 1);
	guns[1] = Powerup("Rifle", "you shoot two bullets", 1, 1, 1);
	guns[2] = Powerup("Machinegun", "you shoot three bullets", 1, 1, 1);
	guns[3] = Powerup("Doublegun", "you shoot two bullets, one dx direction and one sx direction", 1, 1, 1);

    bonus[0] = Powerup("HP", "Additional life", 1, 1, 1); //quantity corresponds to the number of lives which you have bought
	bonus[1] = Powerup("Shield", "A shield that blocks damage one time", 1, 1, 1);//quantity corresponds to the number of protection you have (max 2)

	active[0] = Powerup("Armor", "Become invincible for a limited time", 1, 1, 1); //quantity corresponds to the number of protection you have (max 3)
	active[1] = Powerup("Teleport", "Teleport a short distance", 1, 1, 1); //quantity correspons to the number of possibility of teleportation you have

	board = Board(height,width); //create the board
	board.initialize(); //initialize the board
	WINDOW* win = board.board_win;

	player = Player(win,height-2,1); //create the player
	player.initialize(); //initialize the player

	//board.initializePlatform(50,17,0); //create the first platform
	//board.initializePlatform(60,13,1); //create the second platform
	//board.initializePlatform(70,10,2); //create the third platform

	board.initializeWall(40,height-2,0);
	board.initializeWall(60,height-2,1);
	board.initializeWall(80,height-2,2);

	time = 0;

	enemies0 = NULL; //initialize the list
	enemies1 = NULL; //initialize the list
	enemies2 = NULL; //initialize the list
	enemies3 = NULL; //initialize the list
	enemies4 = NULL; //initialize the list
	enemies5 = NULL; //initialize the list
	enemies6 = NULL; //initialize the list
	enemies7 = NULL; //initialize the list
	enemies8 = NULL; //initialize the list
	enemies9 = NULL; //initialize the list

	coins = NULL; //initialize coins

	nc = rand()%10; //number of coins

	for(int i=0;i<nc;i++){ //create coins with random position and add them to the list
		coins = Game::head_insert_coin(coins,i,(1+rand()%(width-2)),height-2);
	}
	Game::initializeCoins(); //initialize coins

	int k = 1; //max number of enemies

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

	n6 = rand()%k; //number of enemies of type 6
	for(int i=0;i<n6;i++){
		Enemy6 e = Enemy6(win,height-2,(2 + rand()%(width-3)),'0',7,1); //create one enemy
		enemies6 = Game::head_insert_enemy6(enemies6,e,i); //add the enemy into the list
	}

	n7 = rand()%k; //number of enemies of type 7
	for(int i=0;i<n7;i++){
		Enemy7 e = Enemy7(win,height-2,(2 + rand()%(width-3)),'5',7,6); //create one enemy
		enemies7 = Game::head_insert_enemy7(enemies7,e,i); //add the enemy into the list
	}

	n8 = rand()%k; //number of enemies of type 8
	for(int i=0;i<n8;i++){
		Enemy8 e = Enemy8(win,height-2,(2 + rand()%(width-3)),'8',7,7); //create one enemy
		enemies8 = Game::head_insert_enemy8(enemies8,e,i); //add the enemy into the list
	}

	n9 = rand()%k; //number of enemies of type 9
	for(int i=0;i<n9;i++){
		Enemy9 e = Enemy9(win,height-2,(2 + rand()%(width-3)),'2',7,3); //create one enemy
		enemies9 = Game::head_insert_enemy9(enemies9,e,i); //add the enemy into the list
	}

	//onplatform = false; //initialize the platform bool variable

	//Game::market(); //starts market

	//try powerups
	//player.gun.name = guns[0].getName();
	player.gun.name = guns[1].getName();
	//player.gun.name = guns[2].getName();
	//player.gun.name = guns[3].getName();

	//player.shield.qnt = player.shield.qnt + bonus[1].getQnt();
	player.hp.qnt = player.hp.qnt + bonus[0].getQnt();
	player.updateLife();

	//player.armor.qnt = player.armor.qnt + active[0].getQnt();
	player.teleportation.qnt = player.teleportation.qnt + active[1].getQnt();

	//initialize the enemies
	Game::initializeEnemies();

	game_over = false;
}

void Game::market(){
	//Generate randomally 3 powerups
	int a = rand()%NUM_GUNS;
	int b = rand()%NUM_BONUS;
	int c = rand()%NUM_ACTIVE;
	Powerup pu_market[3] = {guns[a], bonus[b], active[c]};
	//call graphic lib to load market level passing the 3 powerups selected for sale
	Game::drawPowerUp(pu_market);

	//Game::updatePowerup(Powerup pwp);

	//once we exit the market level
	//update difficulty based on powerups
	int diff = player.gun.getDifficulty();
	diff += player.hp.getQnt() * player.hp.getDifficulty();
	diff += player.shield.getQnt() * player.shield.getDifficulty();
	diff += player.armor.getQnt() * player.armor.getDifficulty();
	diff += player.teleportation.getQnt() * player.teleportation.getDifficulty();
	difficulty = diff;

	//call map generation function
}

//void Game::updatePowerup(Powerup pwp){

//}

void Game::drawPowerUp(Powerup pwp[]){ //Draw powerups which are spawned
	mvwprintw(board.board_win,20,28,pwp[0].getName().c_str());
	mvwprintw(board.board_win,20,52,pwp[1].getName().c_str());
	mvwprintw(board.board_win,20,80,pwp[2].getName().c_str());
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

	listenm6 tmp6 = enemies6; //enemies is global!!
	while(tmp6!=NULL){
		tmp6->enemy.initialize();
		tmp6 = tmp6->next;
	}

	listenm7 tmp7 = enemies7; //enemies is global!!
	while(tmp7!=NULL){
		tmp7->enemy.initialize();
		tmp7 = tmp7->next;
	}

	listenm8 tmp8 = enemies8; //enemies is global!!
	while(tmp8!=NULL){
		tmp8->enemy.initialize();
		tmp8 = tmp8->next;
	}

	listenm9 tmp9 = enemies9; //enemies is global!!
	while(tmp9!=NULL){
		tmp9->enemy.initialize();
		tmp9 = tmp9->next;
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

listenm6 Game::head_insert_enemy6(listenm6 h,Enemy6 e, int val){ //add one enemy type6 to the list
	listenm6 tmp = new listenemy6;
	tmp->val = val;
	tmp->enemy = e;
	tmp->next = h;
	return tmp;
}

listenm7 Game::head_insert_enemy7(listenm7 h,Enemy7 e, int val){ //add one enemy type7 to the list
	listenm7 tmp = new listenemy7;
	tmp->val = val;
	tmp->enemy = e;
	tmp->next = h;
	return tmp;
}

listenm8 Game::head_insert_enemy8(listenm8 h,Enemy8 e, int val){ //add one enemy type8 to the list
	listenm8 tmp = new listenemy8;
	tmp->val = val;
	tmp->enemy = e;
	tmp->next = h;
	return tmp;
}

listenm9 Game::head_insert_enemy9(listenm9 h,Enemy9 e, int val){ //add one enemy type9 to the list
	listenm9 tmp = new listenemy9;
	tmp->val = val;
	tmp->enemy = e;
	tmp->next = h;
	return tmp;
}

listenm0 Game::obj_remove_enemy0(listenm0 h,int cod,bool head){ //remove the enemy type0 with this cod
	if (h==NULL) return h;
	else if(h->val == cod){ //if the enemy is in the top of the list
		if(head == true){ //we need because we have a problem if we delete the list and use again the element pointed by the list
			listenm0 tmp = h;
			h = h->next;  //ok also if h has one element
			delete tmp;
			tmp = NULL;
		}
		else h = h->next;
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

listenm1 Game::obj_remove_enemy1(listenm1 h,int cod,bool head){ //remove the enemy type1 with this cod
	if (h==NULL) return h;
	else if(h->val == cod){ //if the enemy is in the top of the list
		if(head == true){ //we need because we have a problem if we delete the list and use again the element pointed by the list
			listenm1 tmp = h;
			h = h->next;  //ok also if h has one element
			delete tmp;
			tmp = NULL;
		}
		else h = h->next;
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

listenm2 Game::obj_remove_enemy2(listenm2 h,int cod,bool head){ //remove the enemy type2 with this cod
	if (h==NULL) return h;
	else if(h->val == cod){ //if the enemy is in the top of the list
		if(head == true){ //we need because we have a problem if we delete the list and use again the element pointed by the list
			listenm2 tmp = h;
			h = h->next;  //ok also if h has one element
			delete tmp;
			tmp = NULL;
		}
		else h = h->next;
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

listenm3 Game::obj_remove_enemy3(listenm3 h,int cod,bool head){ //remove the enemy type3 with this cod
	if (h==NULL) return h;
	else if(h->val == cod){ //if the enemy is in the top of the list
		if(head == true){ //we need because we have a problem if we delete the list and use again the element pointed by the list
			listenm3 tmp = h;
			h = h->next;  //ok also if h has one element
			delete tmp;
			tmp = NULL;
		}
		else h = h->next;
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

listenm4 Game::obj_remove_enemy4(listenm4 h,int cod,bool head){ //remove the enemy type4 with this cod
	if (h==NULL) return h;
	else if(h->val == cod){ //if the enemy is in the top of the list
		if(head == true){ //we need because we have a problem if we delete the list and use again the element pointed by the list
			listenm4 tmp = h;
			h = h->next;  //ok also if h has one element
			delete tmp;
			tmp = NULL;
		}
		else h = h->next;
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

listenm5 Game::obj_remove_enemy5(listenm5 h,int cod,bool head){ //remove the enemy type5 with this cod
	if (h==NULL) return h;
	else if(h->val == cod){ //if the enemy is in the top of the list
		if(head == true){ //we need because we have a problem if we delete the list and use again the element pointed by the list
			listenm5 tmp = h;
			h = h->next;  //ok also if h has one element
			delete tmp;
			tmp = NULL;
		}
		else h = h->next;
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

listenm6 Game::obj_remove_enemy6(listenm6 h,int cod,bool head){ //remove the enemy type6 with this cod
	if (h==NULL) return h;
	else if(h->val == cod){ //if the enemy is in the top of the list
		if(head == true){ //we need because we have a problem if we delete the list and use again the element pointed by the list
			listenm6 tmp = h;
			h = h->next;  //ok also if h has one element
			delete tmp;
			tmp = NULL;
		}
		else h = h->next;
	}
	else{
		listenm6 tmp = h;
		bool found = false;
		while(tmp->next!=NULL && !found){
			if(tmp->next->val == cod){ //enemy in the middle of the list (ok also for the tail)
				listenm6 tmp2 = tmp->next;
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

listenm7 Game::obj_remove_enemy7(listenm7 h,int cod,bool head){ //remove the enemy type7 with this cod
	if (h==NULL) return h;
	else if(h->val == cod){ //if the enemy is in the top of the list
		if(head == true){ //we need because we have a problem if we delete the list and use again the element pointed by the list
			listenm7 tmp = h;
			h = h->next;  //ok also if h has one element
			delete tmp;
			tmp = NULL;
		}
		else h = h->next;
	}
	else{
		listenm7 tmp = h;
		bool found = false;
		while(tmp->next!=NULL && !found){
			if(tmp->next->val == cod){ //enemy in the middle of the list (ok also for the tail)
				listenm7 tmp2 = tmp->next;
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

listenm8 Game::obj_remove_enemy8(listenm8 h,int cod,bool head){ //remove the enemy type7 with this cod
	if (h==NULL) return h;
	else if(h->val == cod){ //if the enemy is in the top of the list
		if(head == true){ //we need because we have a problem if we delete the list and use again the element pointed by the list
			listenm8 tmp = h;
			h = h->next;  //ok also if h has one element
			delete tmp;
			tmp = NULL;
		}
		else h = h->next;
	}
	else{
		listenm8 tmp = h;
		bool found = false;
		while(tmp->next!=NULL && !found){
			if(tmp->next->val == cod){ //enemy in the middle of the list (ok also for the tail)
				listenm8 tmp2 = tmp->next;
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

listenm9 Game::obj_remove_enemy9(listenm9 h,int cod,bool head){ //remove the enemy type7 with this cod
	if (h==NULL) return h;
	else if(h->val == cod){ //if the enemy is in the top of the list
		if(head == true){ //we need because we have a problem if we delete the list and use again the element pointed by the list
			listenm9 tmp = h;
			h = h->next;  //ok also if h has one element
			delete tmp;
			tmp = NULL;
		}
		else h = h->next;
	}
	else{
		listenm9 tmp = h;
		bool found = false;
		while(tmp->next!=NULL && !found){
			if(tmp->next->val == cod){ //enemy in the middle of the list (ok also for the tail)
				listenm9 tmp2 = tmp->next;
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

bool Game::interactionBullet(bullt tmp){ //interaction between bullet shot by enemies and player
	if(abs(player.getx() - tmp->xB) <=1 && abs(player.gety() - tmp->yB)<=1){
		player.injury(); //if you are in a neighborhood of the bullet, you lose one life
		return true;
	}
	else return false;
}

int Game::directionSmartEnemy5(Enemy5 e){ //handle the direction of the smart enemy
	if(player.getx() - e.getx() > 0) return 1; //positive direction
	else if(player.getx() - e.getx() < 0) return -1; //negative direction
	else return 0;
}

int Game::directionSmartEnemy7(Enemy7 e){ //handle the direction of the smart enemy
	if(player.getx() - e.getx() > 0) return 1; //positive direction
	else if(player.getx() - e.getx() < 0) return -1; //negative direction
	else return 0;
}

int Game::directionSmartEnemy8(Enemy8 e){ //handle the direction of the smart enemy
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
	mvwprintw(board.board_win,0,56,"%d",player.activejump);
	mvwprintw(board.board_win,0,80,"%d",player.down_arrive);
}

void Game::shooting(){
	//gun player
	bullt tmp = player.bullet.blt;
	int codice;
	if(time%2==0){ //slow down also the speed of bullets
		while(tmp!=NULL){ //you have to move all the bullets
			if(player.bullet.shoot(tmp,player.bullet.blt) == true){ //move the bullet if it exists
				codice = tmp->cod; //save the code of the bullet
				tmp = player.bullet.obj_remove(tmp,codice,false); //remove from the list (don't clean the memory)
				player.bullet.blt = player.bullet.obj_remove(player.bullet.blt,codice,true); //remove from the main list (clean the memory);
			}
			else if(Game::enemydeath(tmp) == true){
				mvwaddch(board.board_win,tmp->yB,tmp->xB,' '); //delete graphically the bullet
				codice = tmp->cod; //save the code of the bullet
				tmp = player.bullet.obj_remove(tmp,codice,false); //delete the bullet (not clean the memory)
				player.bullet.blt = player.bullet.obj_remove(player.bullet.blt,codice,true); //delete the bullet from the main list (clean the memory)
			}
			else tmp = tmp->next;
		}

		//gun enemy type6
		listenm6 cont = enemies6;
		while(cont!=NULL){ //There are more enemies type6 than one
			tmp = cont->enemy.bullet.blt;
			while(tmp!=NULL){ //you have to move all the bullets
				if(cont->enemy.bullet.shoot(tmp,cont->enemy.bullet.blt) == true){ //move the bullet if it exists and check if reaches the wall
					codice = tmp->cod; //save the code of the bullet
					tmp = cont->enemy.bullet.obj_remove(tmp,codice,false); //remove from the list (don't clean the memory)
					cont->enemy.bullet.blt = cont->enemy.bullet.obj_remove(cont->enemy.bullet.blt,codice,true); //remove from the main list (clean the memory);
				}
				else if(Game::interactionBullet(tmp) == true){
					mvwaddch(board.board_win,tmp->yB,tmp->xB,' '); //delete graphically the bullet
					codice = tmp->cod; //save the code of the bullet
					tmp = cont->enemy.bullet.obj_remove(tmp,codice,false); //delete the bullet (not clean the memory)
					cont->enemy.bullet.blt = cont->enemy.bullet.obj_remove(cont->enemy.bullet.blt,codice,true); //delete the bullet from the main list (clean the memory)
				}
				else tmp = tmp->next;
			}
			cont = cont->next; //change enemy
		}

		//gun enemy type7
		listenm7 cont2 = enemies7;
		while(cont2!=NULL){ //There are more enemies type7 than one
			tmp = cont2->enemy.bullet.blt;
			while(tmp!=NULL){ //you have to move all the bullets
				if(cont2->enemy.bullet.shoot(tmp,cont2->enemy.bullet.blt)==true){ //move the bullet if it exists and check if it reaches the wall
					codice = tmp->cod; //save the code of the bullet
					tmp = cont2->enemy.bullet.obj_remove(tmp,codice,false); //remove from the list (don't clean the memory)
					cont2->enemy.bullet.blt = cont2->enemy.bullet.obj_remove(cont2->enemy.bullet.blt,codice,true); //remove from the main list (clean the memory);
				}
				else if(Game::interactionBullet(tmp) == true){
					mvwaddch(board.board_win,tmp->yB,tmp->xB,' '); //delete graphically the bullet
					codice = tmp->cod; //save the code of the bullet
					tmp = cont2->enemy.bullet.obj_remove(tmp,codice,false); //delete the bullet (not clean the memory)
					cont2->enemy.bullet.blt = cont2->enemy.bullet.obj_remove(cont2->enemy.bullet.blt,codice,true); //delete the bullet from the main list (clean the memory)
				}
				else tmp = tmp->next;
			}
			cont2 = cont2->next; //change enemy
		}

		//gun enemy type8
		listenm8 cont3 = enemies8;
		while(cont3!=NULL){ //There are more enemies type8 than one
			tmp = cont3->enemy.bullet.blt;
			while(tmp!=NULL){ //you have to move all the bullets
				if(cont3->enemy.bullet.shoot(tmp,cont3->enemy.bullet.blt) == true){ //move the bullet if it exists and check if it reaches the wall
					codice = tmp->cod; //save the code of the bullet
					tmp = cont3->enemy.bullet.obj_remove(tmp,codice,false); //remove from the list (don't clean the memory)
					cont3->enemy.bullet.blt = cont3->enemy.bullet.obj_remove(cont3->enemy.bullet.blt,codice,true); //remove from the main list (clean the memory);
				}
				else if(Game::interactionBullet(tmp) == true){
					mvwaddch(board.board_win,tmp->yB,tmp->xB,' '); //delete graphically the bullet
					codice = tmp->cod; //save the code of the bullet
					tmp = cont3->enemy.bullet.obj_remove(tmp,codice,false); //delete the bullet (not clean the memory)
					cont3->enemy.bullet.blt = cont3->enemy.bullet.obj_remove(cont3->enemy.bullet.blt,codice,true); //delete the bullet from the main list (clean the memory)
				}
				else tmp = tmp->next;
			}
			cont3 = cont3->next; //change enemy
		}

		//gun enemy type9
		listenm9 cont4 = enemies9;
		while(cont4!=NULL){ //There are more enemies type9 than one
			tmp = cont4->enemy.bullet.blt;
			while(tmp!=NULL){ //you have to move all the bullets
				if(cont4->enemy.bullet.shoot(tmp,cont4->enemy.bullet.blt) == true){ //move the bullet if it exists and check if it reaches the wall
					codice = tmp->cod; //save the code of the bullet
					tmp = cont4->enemy.bullet.obj_remove(tmp,codice,false); //remove from the list (don't clean the memory)
					cont4->enemy.bullet.blt = cont4->enemy.bullet.obj_remove(cont4->enemy.bullet.blt,codice,true); //remove from the main list (clean the memory);
				}
				else if(Game::interactionBullet(tmp) == true){
					mvwaddch(board.board_win,tmp->yB,tmp->xB,' '); //delete graphically the bullet
					codice = tmp->cod; //save the code of the bullet
					tmp = cont4->enemy.bullet.obj_remove(tmp,codice,false); //delete the bullet (not clean the memory)
					cont4->enemy.bullet.blt = cont4->enemy.bullet.obj_remove(cont4->enemy.bullet.blt,codice,true); //delete the bullet from the main list (clean the memory)
				}
				else tmp = tmp->next;
			}
			cont4 = cont4->next; //change enemy
		}
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
				tmp0 = Game::obj_remove_enemy0(tmp0, codice,false); //if it is died, you have to remove from the list
				enemies0 = Game::obj_remove_enemy0(enemies0, codice,true); //if it is died, you have to remove from the main list
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
				tmp1 = Game::obj_remove_enemy1(tmp1, codice,false); //if it is died, you have to remove from the list
				enemies1 = Game::obj_remove_enemy1(enemies1, codice,true); //if it is died, you have to remove from the main list
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
				tmp2 = Game::obj_remove_enemy2(tmp2, codice,false); //if it is died, you have to remove from the list
				enemies2 = Game::obj_remove_enemy2(enemies2, codice,true); //if it is died, you have to remove from the main list
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
				tmp3 = Game::obj_remove_enemy3(tmp3, codice,false); //if it is died, you have to remove from the list
				enemies3 = Game::obj_remove_enemy3(enemies3, codice,true); //if it is died, you have to remove from the main list
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
				tmp4 = Game::obj_remove_enemy4(tmp4, codice,false); //if it is died, you have to remove from the list
				enemies4 = Game::obj_remove_enemy4(enemies4, codice,true); //if it is died, you have to remove from the main list
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
				tmp5 = Game::obj_remove_enemy5(tmp5, codice,false); //if it is died, you have to remove from the list
				enemies5 = Game::obj_remove_enemy5(enemies5, codice,true); //if it is died, you have to remove from the main list
			}
			else tmp5 = tmp5->next;
		}
		else tmp5 = tmp5->next;
	}

	bullt temp; //we need it to raise all remaining bullets
	//check enemy6
	listenm6 tmp6 = enemies6;
	while(tmp6!=NULL && !found){
		if(abs(tmp->xB - tmp6->enemy.getx())<=1 && abs(tmp->yB - tmp6->enemy.gety())<=1){ //check if the bullet and the enemy are in the same place (the same approach used in interaction1)
			tmp6->enemy.injury(); //injury for the enemy
			found = true; //you have removed this bullet, so you can stop the cycle
			if(tmp6->enemy.getlife() <= 0){ //Enemy life = 0
				mvwaddch(board.board_win,tmp6->enemy.gety(),tmp6->enemy.getx(),' '); //delete graphically the enemy
				//delete graphically the gun
				if(tmp6->enemy.segno==1)mvwaddch(board.board_win,tmp6->enemy.gety(),tmp6->enemy.getx()+1,' ');
				else mvwaddch(board.board_win,tmp6->enemy.gety(),tmp6->enemy.getx()-1,' ');
				//delete all remaining bullets
				temp = tmp6->enemy.bullet.blt;
				while(temp!=NULL){
					mvwaddch(board.board_win,temp->yB,temp->xB,' '); //delete graphically the bullet
					codice = temp->cod; //save the code of the bullet
					tmp = tmp6->enemy.bullet.obj_remove(temp,codice,false); //delete the bullet (not clean the memory)
					tmp6->enemy.bullet.blt = tmp6->enemy.bullet.obj_remove(tmp6->enemy.bullet.blt,codice,true); //delete the bullet from the main list (clean the memory)
					temp = temp->next;
				}
				codice = tmp6->val; //save the code of the enemy
				tmp6 = Game::obj_remove_enemy6(tmp6, codice,false); //if it is died, you have to remove from the list
				enemies6 = Game::obj_remove_enemy6(enemies6, codice,true); //if it is died, you have to remove from the main list
			}
			else tmp6 = tmp6->next;
		}
		else tmp6 = tmp6->next;
	}

	//check enemy7
	listenm7 tmp7 = enemies7;
	while(tmp7!=NULL && !found){
		if(abs(tmp->xB - tmp7->enemy.getx())<=1 && abs(tmp->yB - tmp7->enemy.gety())<=1){ //check if the bullet and the enemy are in the same place (the same approach used in interaction1)
			tmp7->enemy.injury(); //injury for the enemy
			found = true; //you have removed this bullet, so you can stop the cycle
			if(tmp7->enemy.getlife() <= 0){ //Enemy life = 0
				mvwaddch(board.board_win,tmp7->enemy.gety(),tmp7->enemy.getx(),' '); //delete graphically the enemy
				//delete graphically the gun
				if(tmp7->enemy.segno==1)mvwaddch(board.board_win,tmp7->enemy.gety(),tmp7->enemy.getx()+1,' ');
				else mvwaddch(board.board_win,tmp7->enemy.gety(),tmp7->enemy.getx()-1,' ');
				//delete all remaining bullets
				temp = tmp7->enemy.bullet.blt;
				while(temp!=NULL){
					mvwaddch(board.board_win,temp->yB,temp->xB,' '); //delete graphically the bullet
					codice = temp->cod; //save the code of the bullet
					tmp = tmp7->enemy.bullet.obj_remove(temp,codice,false); //delete the bullet (not clean the memory)
					tmp7->enemy.bullet.blt = tmp7->enemy.bullet.obj_remove(tmp7->enemy.bullet.blt,codice,true); //delete the bullet from the main list (clean the memory)
					temp = temp->next;
				}
				codice = tmp7->val; //save the code of the enemy
				tmp7 = Game::obj_remove_enemy7(tmp7, codice,false); //if it is died, you have to remove from the list
				enemies7 = Game::obj_remove_enemy7(enemies7, codice,true); //if it is died, you have to remove from the main list
			}
			else tmp7 = tmp7->next;
		}
		else tmp7 = tmp7->next;
	}

	//check enemy8
	listenm8 tmp8 = enemies8;
	while(tmp8!=NULL && !found){
		if(abs(tmp->xB - tmp8->enemy.getx())<=1 && abs(tmp->yB - tmp8->enemy.gety())<=1){ //check if the bullet and the enemy are in the same place (the same approach used in interaction1)
			tmp8->enemy.injury(); //injury for the enemy
			found = true; //you have removed this bullet, so you can stop the cycle
			if(tmp8->enemy.getlife() <= 0){ //Enemy life = 0
				mvwaddch(board.board_win,tmp8->enemy.gety(),tmp8->enemy.getx(),' '); //delete graphically the enemy
				//delete graphically the gun
				if(tmp8->enemy.segno==1)mvwaddch(board.board_win,tmp8->enemy.gety(),tmp8->enemy.getx()+1,' ');
				else mvwaddch(board.board_win,tmp8->enemy.gety(),tmp8->enemy.getx()-1,' ');
				//delete all remaining bullets
				temp = tmp8->enemy.bullet.blt;
				while(temp!=NULL){
					mvwaddch(board.board_win,temp->yB,temp->xB,' '); //delete graphically the bullet
					codice = temp->cod; //save the code of the bullet
					tmp = tmp8->enemy.bullet.obj_remove(temp,codice,false); //delete the bullet (not clean the memory)
					tmp8->enemy.bullet.blt = tmp8->enemy.bullet.obj_remove(tmp8->enemy.bullet.blt,codice,true); //delete the bullet from the main list (clean the memory)
					temp = temp->next;
				}
				codice = tmp8->val; //save the code of the enemy
				tmp8 = Game::obj_remove_enemy8(tmp8, codice,false); //if it is died, you have to remove from the list
				enemies8 = Game::obj_remove_enemy8(enemies8, codice,true); //if it is died, you have to remove from the main list
			}
			else tmp8 = tmp8->next;
		}
		else tmp8 = tmp8->next;
	}

	//check enemy9
	listenm9 tmp9 = enemies9;
	while(tmp9!=NULL && !found){
		if(abs(tmp->xB - tmp9->enemy.getx())<=1 && abs(tmp->yB - tmp9->enemy.gety())<=1){ //check if the bullet and the enemy are in the same place (the same approach used in interaction1)
			tmp9->enemy.injury(); //injury for the enemy
			found = true; //you have removed this bullet, so you can stop the cycle
			if(tmp9->enemy.getlife() <= 0){ //Enemy life = 0
				mvwaddch(board.board_win,tmp9->enemy.gety(),tmp9->enemy.getx(),' '); //delete graphically the enemy
				//delete graphically the two guns
				mvwaddch(board.board_win,tmp9->enemy.gety(),tmp9->enemy.getx()+1,' ');
				mvwaddch(board.board_win,tmp9->enemy.gety(),tmp9->enemy.getx()-1,' ');
				//delete all remaining bullets
				temp = tmp9->enemy.bullet.blt;
				while(temp!=NULL){
					mvwaddch(board.board_win,temp->yB,temp->xB,' '); //delete graphically the bullet
					codice = temp->cod; //save the code of the bullet
					tmp = tmp9->enemy.bullet.obj_remove(temp,codice,false); //delete the bullet (not clean the memory)
					tmp9->enemy.bullet.blt = tmp9->enemy.bullet.obj_remove(tmp9->enemy.bullet.blt,codice,true); //delete the bullet from the main list (clean the memory)
					temp = temp->next;
				}
				codice = tmp9->val; //save the code of the enemy
				tmp9 = Game::obj_remove_enemy9(tmp9, codice,false); //if it is died, you have to remove from the list
				enemies9 = Game::obj_remove_enemy9(enemies9, codice,true); //if it is died, you have to remove from the main list
			}
			else tmp9 = tmp9->next;
		}
		else tmp9 = tmp9->next;
	}

	return found;
}

void Game::playermovement(){
	//if you are jumping you cannot move
	//bool arrive = true;
	/*if(arrive){ //check if you are not going down
		if(!player.activejump){ //you are not jumping
			int choice = player.getmv(); //save the movement
			//player.getmv();
			//bool down = Game::interactionPlatform(choice); //interaction with the platforms
			//if (down == true) arrive = player.godown();
			Game::interactionWall(choice); //interaction with the walls
		}
		else{
			player.jump();
			//Game::interactionPlatform(KEY_UP); //you are jumping
			player.display(); //show the jump
			player.jumpandshoot(); //if you want shoot you have to press h
		}
	//}
	//else player.godown(); //go down
	//see player
	player.display();
	 */
	//if you are jumping you cannot move
	bool down;
	if(player.down_arrive){ //check if you are not going down
		if(!player.activejump){ //you are not jumping
			int choice = player.getmv(); //save the movement
			down = Game::interactionWall(choice); //interaction with the walls
		}
		else{
			player.jump();
			down = Game::interactionWall(KEY_UP); //you are jumping
		}
		//check if you have had a collision
		if(!down && player.activejump){
			player.display(); //show the jump
			player.jumpandshoot(); //if you want shoot you have to press h
		}
		else if(player.activejump){
			player.display(); //see the player
			player.activejump = false; //stop jumping
			player.godown(); //If there has been collisions, you have to go down
		}
	}
	else player.godown(); //go down
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
	listenm5 tmp5 = enemies5; //type5
	while(tmp5!=NULL){
		dir = Game::directionSmartEnemy5(tmp5->enemy);
		if((abs(player.getx() - tmp5->enemy.getx()) <= 20) && (player.gety() == tmp5->enemy.gety())){ //player is sufficiently near to enemy type5
			tmp5->enemy.movement(dir); //move one enemy
		}
		tmp5->enemy.display(); //see one enemy
		Game::interaction(tmp5->enemy); //check the interaction between one enemy and the player
		tmp5 = tmp5->next; //go to the next enemy
	}

	listenm6 tmp6 = enemies6;  //type6
	while(tmp6!=NULL){
		tmp6->enemy.movement(); //move one enemy
		tmp6->enemy.display(); //see one enemy
		//no damage when player touches enemies type6
		tmp6 = tmp6->next; //go to the next enemy
	}

	listenm7 tmp7 = enemies7;  //type7
	while(tmp7!=NULL){
		dir = Game::directionSmartEnemy7(tmp7->enemy);
		if((abs(player.getx() - tmp7->enemy.getx()) <= 20) && (player.gety() == tmp7->enemy.gety())){ //player is sufficiently near to enemy type7
			tmp7->enemy.movement(dir); //move one enemy
		}
		tmp7->enemy.display(); //see one enemy
		//no damage when player touches enemies type7
		tmp7 = tmp7->next; //go to the next enemy
	}

	listenm8 tmp8 = enemies8;  //type8
	while(tmp8!=NULL){
		dir = Game::directionSmartEnemy8(tmp8->enemy);
		if((abs(player.getx() - tmp8->enemy.getx()) <= 10) && (player.gety() == tmp8->enemy.gety())){ //player is sufficiently near to enemy type8
			tmp8->enemy.movement(dir); //move one enemy
		}
		tmp8->enemy.display(); //see one enemy
		//no damage when player touches enemies type8
		tmp8 = tmp8->next; //go to the next enemy
	}

	listenm9 tmp9 = enemies9;  //type9
	while(tmp9!=NULL){
		tmp9->enemy.movement(); //move one enemy
		tmp9->enemy.display(); //see one enemy
		//no damage when player touches enemies type9
		tmp9 = tmp9->next; //go to the next enemy
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
			player.updatecash(1); //update wallet
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
/*
bool Game::interactionPlatform(int choice){
	bool down = false; //you are not falling
	if (onplatform == false){ //you are not on the platform
		for(int i=0;i<3;i++){
			switch(choice){
				case KEY_UP: //you are jumping
					if(player.getx() >= board.plat[i].xpos[0] && player.getx() <= board.plat[i].xpos[len-1] && player.gety() == board.plat[i].ypos[0]){ //you reach the platform with a jump
						player.activejump = false; //stop tu jump
						onplatform = true; //now you are on platform
					}
					else if (player.getx() >= board.plat[i].xpos[0] && player.getx() <= board.plat[i].xpos[len-1] && (player.gety() - board.plat[i].ypos[0])<=3){ //you are under the platform and you can't reach it
						mvwaddch(board.board_win,player.gety()-1,player.getx(),'_');
						player.activejump = false; //stop to jump
						onplatform = true; //you simulate that you are on platform
					}
					break;
				default:
					break;
			}
		}
	}
	else{
		for(int i=0;i<3;i++){
			if((player.getx() < board.plat[i].xpos[0] || player.getx() > board.plat[i].xpos[len-1])){ //you reach the end of the platform
				if(player.gety() == player.yMax-2) onplatform = false; //you reach the ground floor
				down = true; //you are going down
			}
			else if(player.gety() == board.plat[i].ypos[0]){ //you are on the platform
				switch(choice){
					case KEY_UP:
						break;
					case KEY_RIGHT:
						mvwaddch(board.board_win,player.gety(),player.getx()-1,'_'); //rewrite the character
						break;
					case KEY_LEFT:
						mvwaddch(board.board_win,player.gety(),player.getx()+1,'_'); //rewrite the character
						break;
				}
			}
			else{ //this is for the jump under the platform
				if(player.gety() == player.yMax-2) onplatform = false; //you reach the ground floor
				down = true;
			}
		}
	}
	return down;
}
*/

bool Game::interactionWall(int choice){
	int j = 0;
	int i;
	bool found_wall = false;
	bool down = false;
	while(j<3 && !found_wall){ //all walls!
		i = 0;
		while(i<len && !found_wall){ //check the position of the player with respect all pieces of the wall
				switch(choice){
					case KEY_RIGHT: //when player went to dx
						if(player.getx() == board.wal[j].xpos[0] && player.gety() == board.wal[j].ypos[i]){
							found_wall = true; //collision
							player.updateCoordinates(-1,0); //come back from where you went
						}
						break;
					case KEY_LEFT: //when player went to sx
						if(player.getx() == board.wal[j].xpos[0] && player.gety() == board.wal[j].ypos[i]){
							found_wall = true; //collision
							player.updateCoordinates(1,0); //come back from where you went
						}
					case KEY_UP: //when player jumped
						if(player.getx() == board.wal[j].xpos[0] && player.gety() == board.wal[j].ypos[i]){ //range of collision between a jump of player and the sx (or dx) part of wall (remember the dynamic of jump!)
							found_wall = true; //collision
							player.updateCoordinates(-player.getdir(),0); //come back from where you went
							down = true; //you have to go down
						}
						break;
					default:

						break;
				}
			i++; //change piece of wall
		}
		j++; //change wall
	}
	return down;
}
