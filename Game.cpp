/*
 * Game.cpp
 *
 *  Created on: 11 dic 2022
 *      Author: david
 */

#include "Game.hpp"

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
	bonus[2] = Powerup("Jump","Change the height of the jump",2,1,1); //quantity corresponds to max (plus with respect to basi jump) height of the jump

	active[0] = Powerup("Armor", "Become invincible for a limited time", 1, 1, 1); //quantity corresponds to the number of protection you have (max 3)
	active[1] = Powerup("Teleport", "Teleport a short distance", 1, 1, 1); //quantity corresponds to the number of possibility of teleportation you have
	active[2] = Powerup("Bullets","Charge of bullets",100,1,1); //quantity corresponds to the number of bullets
	active[3] = Powerup("Fly","You can fly",1,1,1); //quantity corresponds to the number of fly you can do it (max 1)

	board = Board(height,width); //create the board
	board.initialize(0,0); //initialize the board in 0,0
	WINDOW* win = board.board_win;

	map = Map(10); //create the map

	matrix = map.toString(); //create the matrix of char for the map

	xMin = 0;
	//print all map
	Game::PrintMap();

	player = Player(win,height-4,20); //create the player
	player.initialize(); //initialize the player

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

	int k = 2; //max number of enemies

	int iniz = -300;
	int fin = 300;

	n0 = rand()%k; //number of enemies of type 0
	for(int i=0;i<n0;i++){
		Enemy0 e = Enemy0(win,(1 + rand()%(height-2)),(rand()%(fin)+iniz),'0',9,1); //create one enemy
		enemies0 = Game::head_insert_enemy0(enemies0,e,i); //add the enemy into the list
	}

	n1 = rand()%k; //number of enemies of type 1
	for(int i=0;i<n1;i++){
		Enemy1 e = Enemy1(win,(1 + rand()%(height-2)),(rand()%(fin)+iniz),'1',9,2); //create one enemy
		enemies1 = Game::head_insert_enemy1(enemies1,e,i); //add the enemy into the list
	}

	n2 = rand()%k; //number of enemies of type 2
	for(int i=0;i<n2;i++){
		Enemy2 e = Enemy2(win,(1 + rand()%(height-2)),(rand()%(fin)+iniz),'2',15,3); //create one enemy
		enemies2 = Game::head_insert_enemy2(enemies2,e,i); //add the enemy into the list
	}

	n3 = rand()%k; //number of enemies of type 3
	for(int i=0;i<n3;i++){
		Enemy3 e = Enemy3(win,(1 + rand()%(height-2)),(rand()%(fin)+iniz),'3',9,4); //create one enemy
		enemies3 = Game::head_insert_enemy3(enemies3,e,i); //add the enemy into the list
	}

	n4 = rand()%k; //number of enemies of type 4
	for(int i=0;i<n4;i++){
		Enemy4 e = Enemy4(win,(1 + rand()%(height-2)),(rand()%(fin)+iniz),'4',7,5); //create one enemy
		enemies4 = Game::head_insert_enemy4(enemies4,e,i); //add the enemy into the list
	}

	n5 = rand()%k; //number of enemies of type 5
	for(int i=0;i<n5;i++){
		Enemy5 e = Enemy5(win,(1 + rand()%(height-2)),(rand()%(fin)+iniz),'5',7,6); //create one enemy
		enemies5 = Game::head_insert_enemy5(enemies5,e,i); //add the enemy into the list
	}

	n6 = rand()%k; //number of enemies of type 6
	for(int i=0;i<n6;i++){
		Enemy6 e = Enemy6(win,(1 + rand()%(height-2)),(rand()%(fin)+iniz),'0',7,1); //create one enemy
		enemies6 = Game::head_insert_enemy6(enemies6,e,i); //add the enemy into the list
	}

	n7 = rand()%k; //number of enemies of type 7
	for(int i=0;i<n7;i++){
		Enemy7 e = Enemy7(win,(1 + rand()%(height-2)),(rand()%(fin)+iniz),'5',7,6); //create one enemy
		enemies7 = Game::head_insert_enemy7(enemies7,e,i); //add the enemy into the list
	}

	n8 = rand()%k; //number of enemies of type 8
	for(int i=0;i<n8;i++){
		Enemy8 e = Enemy8(win,(1 + rand()%(height-2)),(rand()%(fin)+iniz),'8',7,7); //create one enemy
		enemies8 = Game::head_insert_enemy8(enemies8,e,i); //add the enemy into the list
	}

	n9 = rand()%k; //number of enemies of type 9
	for(int i=0;i<n9;i++){
		Enemy9 e = Enemy9(win,(1 + rand()%(height-2)),(rand()%(fin)+iniz),'2',7,3); //create one enemy
		enemies9 = Game::head_insert_enemy9(enemies9,e,i); //add the enemy into the list
	}

	//Game::market(); //starts market

	//try powerups
	player.gun.name = guns[0].getName();
	//player.gun.name = guns[1].getName();
	//player.gun.name = guns[2].getName();
	//player.gun.name = guns[3].getName();

	player.shield.setQnt(player.shield.getQnt() + bonus[1].getQnt());
	player.hp.setQnt(player.hp.getQnt() + bonus[0].getQnt());
	//player.jumping.setQnt(player.jumping.getQnt()+ bonus[2].getQnt());

	player.armor.setQnt(player.armor.getQnt() + active[0].getQnt());
	player.teleportation.setQnt(player.teleportation.getQnt() + active[1].getQnt());
	//player.bullets.setQnt(player.bullets.getQnt() + active[2].getQnt());
	//player.fly.setQnt(player.fly.getQnt() + active[3].getQnt());

	//initialize the enemies
	Game::initializeEnemies();

	game_over = false;
}

void Game::PrintMap(){
	for(int i=0;i<map.getDim_y();i++){
		for(int j=xMin;j<map.getDim_x()&&j<xMin+110;j++){
			mvwaddch(board.board_win,i,j-xMin,matrix[i][j]);
		}
	}
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
	Game::displayLife();
	//display coins
	Game::displayCoins();

	//Map movement
	if(time%600 == 0)Game::mapMovement(); //We move the map on orrizzontal directionand the player only on vertical direction

	if(map.updateCoins(xMin+player.getx(), player.gety())){
		matrix = map.toString(); //update the map removing coin
		player.updateCash(1);
	}

	//handle shooting
	Game::shooting();

	//enemy movement
	if(time%1200 == 0) Game::enemyMovement(); //you want to slow down enemies
	time++;

	if(player.hp.getQnt() == 0) game_over = true; //Player death

	//Update board
	Game::UpdateBoard();

}

void Game::interaction(Enemy0 e){ //interaction between enemies and player
	if(abs(player.getx() - e.getx())<=1 && (player.gety() - e.gety())<=1 && (player.gety() - e.gety())>=0){
		player.injury(); //if you are in a neighborhood of the enemy, you lose one life
	}
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

void Game::UpdateBoard(){
	board.addBorder(0,0);
}

bool Game::isOver(){
	return game_over;
}

void Game::displayLife(){ //display life and bullets
	mvwprintw(board.board_win,24,1,"Life: ");
	mvwprintw(board.board_win,24,6,"%d",player.hp.getQnt());
	if(player.hp.getQnt()<100) mvwprintw(board.board_win,24,8," ");
	if(player.hp.getQnt()<10) mvwprintw(board.board_win,24,7," ");
	mvwprintw(board.board_win,24,45,"Number of Bullets: ");
	mvwprintw(board.board_win,24,63,"%d",player.bullets.getQnt());
	if(player.bullets.getQnt()<100) mvwprintw(board.board_win,24,65," ");
	if(player.bullets.getQnt()<10) mvwprintw(board.board_win,24,64," ");
}

void Game::displayCoins(){ //display coins
	mvwprintw(board.board_win,24,101,"Money: ");
	mvwprintw(board.board_win,24,107,"%d",player.getCoins());
}

void Game::Structure(){ //create structures
	for(int i=0;i<num_ogg;i++){
		board.initializePlatform((rand()%(300)-100),(4 + rand()%(board.height-6)),i); //platform
		board.initializeWall((rand()%(300)-100),(8 + rand()%(board.height-10)),i); //platform
	}
}

void Game::StructureUpdate(){ //update structures
	for(int i=0;i<num_ogg;i++){
		board.initializePlatform(board.plat[i].xpos[0],board.plat[i].ypos[0],i); //platform
		board.initializeWall(board.wal[i].xpos[0],board.wal[i].ypos[0],i); //platform
	}
}

bullt Game::deletePlayerBullets(bullt tmp){ //delete Player's bullets
	int codice = tmp->cod; //save the code of the bullet
	tmp = player.bullet.obj_remove(tmp,codice,false); //remove from the list (don't clean the memory)
	player.bullet.blt = player.bullet.obj_remove(player.bullet.blt,codice,true); //remove from the main list (clean the memory);
	return tmp;
}

bullt Game::deleteEnemy6Bullets(bullt tmp,listenm6 e){ //delete Enemy6's bullets
	int codice = tmp->cod; //save the code of the bullet
	tmp = e->enemy.bullet.obj_remove(tmp,codice,false); //remove from the list (don't clean the memory)
	e->enemy.bullet.blt = e->enemy.bullet.obj_remove(e->enemy.bullet.blt,codice,true); //remove from the main list (clean the memory);
	return tmp;
}

bullt Game::deleteEnemy7Bullets(bullt tmp,listenm7 e){ //delete Enemy7's bullets
	int codice = tmp->cod; //save the code of the bullet
	tmp = e->enemy.bullet.obj_remove(tmp,codice,false); //remove from the list (don't clean the memory)
	e->enemy.bullet.blt = e->enemy.bullet.obj_remove(e->enemy.bullet.blt,codice,true); //remove from the main list (clean the memory);
	return tmp;
}

bullt Game::deleteEnemy8Bullets(bullt tmp,listenm8 e){ //delete Enemy8's bullets
	int codice = tmp->cod; //save the code of the bullet
	tmp = e->enemy.bullet.obj_remove(tmp,codice,false); //remove from the list (don't clean the memory)
	e->enemy.bullet.blt = e->enemy.bullet.obj_remove(e->enemy.bullet.blt,codice,true); //remove from the main list (clean the memory);
	return tmp;
}

bullt Game::deleteEnemy9Bullets(bullt tmp,listenm9 e){ //delete Enemy9's bullets
	int codice = tmp->cod; //save the code of the bullet
	tmp = e->enemy.bullet.obj_remove(tmp,codice,false); //remove from the list (don't clean the memory)
	e->enemy.bullet.blt = e->enemy.bullet.obj_remove(e->enemy.bullet.blt,codice,true); //remove from the main list (clean the memory);
	return tmp;
}

void Game::shooting(){
	//gun player
	bullt tmp = player.bullet.blt;
	if(time%500==0){ //slow down also the speed of bullets
		while(tmp!=NULL){ //you have to move all the bullets
			if(player.bullet.shoot(tmp,player.bullet.blt) == true){ //move the bullet if it exists (in this case you reached the walls)
				tmp = Game::deletePlayerBullets(tmp); //delete bullet
			}
			else if(board.IsThereStructure(tmp->xB,tmp->yB) == true || board.IsThereStructure(tmp->xB+1,tmp->yB) || board.IsThereStructure(tmp->xB-1,tmp->yB)){ //you have had a collision with a structure (the range avoids the collision next to the wall)
				mvwaddch(board.board_win,tmp->yB,tmp->xB,' '); //delete graphically the bullet
				tmp = Game::deletePlayerBullets(tmp); //delete bullet
			}
			else if(Game::enemydeath(tmp) == true){
				mvwaddch(board.board_win,tmp->yB,tmp->xB,' '); //delete graphically the bullet
				tmp = Game::deletePlayerBullets(tmp); //delete bullet
			}
			else tmp = tmp->next;
		}
		//gun enemy type6
		listenm6 cont = enemies6;
		while(cont!=NULL){ //There are more enemies type6 than one
			tmp = cont->enemy.bullet.blt;
			while(tmp!=NULL){ //you have to move all the bullets
				if(cont->enemy.bullet.shoot(tmp,cont->enemy.bullet.blt) == true){ //move the bullet if it exists and check if reaches the wall
					tmp = deleteEnemy6Bullets(tmp,cont); //delete bullet
				}
				else if(board.IsThereStructure(tmp->xB,tmp->yB) == true || board.IsThereStructure(tmp->xB+1,tmp->yB) || board.IsThereStructure(tmp->xB-1,tmp->yB)){ //you have had a collision with a structure (the range avoids the collision next to the wall)
					mvwaddch(board.board_win,tmp->yB,tmp->xB,' '); //delete graphically the bullet
					tmp = deleteEnemy6Bullets(tmp,cont); //delete bullet
				}
				else if(Game::interactionBullet(tmp) == true){
					mvwaddch(board.board_win,tmp->yB,tmp->xB,' '); //delete graphically the bullet
					tmp = deleteEnemy6Bullets(tmp,cont); //delete bullet
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
					tmp = deleteEnemy7Bullets(tmp,cont2); //delete bullet
				}
				else if(board.IsThereStructure(tmp->xB,tmp->yB) == true || board.IsThereStructure(tmp->xB+1,tmp->yB) || board.IsThereStructure(tmp->xB-1,tmp->yB)){ //you have had a collision with a structure (the range avoids the collision next to the wall)
					mvwaddch(board.board_win,tmp->yB,tmp->xB,' '); //delete graphically the bullet
					tmp = deleteEnemy7Bullets(tmp,cont2); //delete bullet
				}
				else if(Game::interactionBullet(tmp) == true){
					mvwaddch(board.board_win,tmp->yB,tmp->xB,' '); //delete graphically the bullet
					tmp = deleteEnemy7Bullets(tmp,cont2); //delete bullet
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
					tmp = deleteEnemy8Bullets(tmp,cont3); //delete bullet
				}
				else if(board.IsThereStructure(tmp->xB,tmp->yB) == true || board.IsThereStructure(tmp->xB+1,tmp->yB) || board.IsThereStructure(tmp->xB-1,tmp->yB)){ //you have had a collision with a structure (the range avoids the collision next to the wall)
					mvwaddch(board.board_win,tmp->yB,tmp->xB,' '); //delete graphically the bullet
					tmp = deleteEnemy8Bullets(tmp,cont3); //delete bullet
				}
				else if(Game::interactionBullet(tmp) == true){
					mvwaddch(board.board_win,tmp->yB,tmp->xB,' '); //delete graphically the bullet
					tmp = deleteEnemy8Bullets(tmp,cont3); //delete bullet
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
					tmp = deleteEnemy9Bullets(tmp,cont4); //delete bullet
				}
				else if(board.IsThereStructure(tmp->xB,tmp->yB) == true || board.IsThereStructure(tmp->xB+1,tmp->yB) || board.IsThereStructure(tmp->xB-1,tmp->yB)){ //you have had a collision with a structure (the range avoids the collision next to the wall)
					mvwaddch(board.board_win,tmp->yB,tmp->xB,' '); //delete graphically the bullet
					tmp = deleteEnemy9Bullets(tmp,cont4); //delete bullet
				}
				else if(Game::interactionBullet(tmp) == true){
					mvwaddch(board.board_win,tmp->yB,tmp->xB,' '); //delete graphically the bullet
					tmp = deleteEnemy9Bullets(tmp,cont4); //delete bullet
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
			if(tmp0->enemy.getLife() <= 0){ //Enemy life = 0
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
			if(tmp1->enemy.getLife() <= 0){ //Enemy life = 0
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
			if(tmp2->enemy.getLife() <= 0){ //Enemy life = 0
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
			if(tmp3->enemy.getLife() <= 0){ //Enemy life = 0
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
			if(tmp4->enemy.getLife() <= 0){ //Enemy life = 0
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
			if(tmp5->enemy.getLife() <= 0){ //Enemy life = 0
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
			if(tmp6->enemy.getLife() <= 0){ //Enemy life = 0
				mvwaddch(board.board_win,tmp6->enemy.gety(),tmp6->enemy.getx(),' '); //delete graphically the enemy
				//delete graphically the gun
				if(tmp6->enemy.getSign()==1)mvwaddch(board.board_win,tmp6->enemy.gety(),tmp6->enemy.getx()+1,' ');
				else mvwaddch(board.board_win,tmp6->enemy.gety(),tmp6->enemy.getx()-1,' ');
				//delete all remaining bullets
				temp = tmp6->enemy.bullet.blt;
				while(temp!=NULL){
					mvwaddch(board.board_win,temp->yB,temp->xB,' '); //delete graphically the bullet
					temp = deleteEnemy6Bullets(temp,tmp6); //delete bullet
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
			if(tmp7->enemy.getLife() <= 0){ //Enemy life = 0
				mvwaddch(board.board_win,tmp7->enemy.gety(),tmp7->enemy.getx(),' '); //delete graphically the enemy
				//delete graphically the gun
				if(tmp7->enemy.getSign()==1)mvwaddch(board.board_win,tmp7->enemy.gety(),tmp7->enemy.getx()+1,' ');
				else mvwaddch(board.board_win,tmp7->enemy.gety(),tmp7->enemy.getx()-1,' ');
				//delete all remaining bullets
				temp = tmp7->enemy.bullet.blt;
				while(temp!=NULL){
					mvwaddch(board.board_win,temp->yB,temp->xB,' '); //delete graphically the bullet
					temp = deleteEnemy7Bullets(temp,tmp7); //delete bullet
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
			if(tmp8->enemy.getLife() <= 0){ //Enemy life = 0
				mvwaddch(board.board_win,tmp8->enemy.gety(),tmp8->enemy.getx(),' '); //delete graphically the enemy
				//delete graphically the gun
				if(tmp8->enemy.getSign()==1)mvwaddch(board.board_win,tmp8->enemy.gety(),tmp8->enemy.getx()+1,' ');
				else mvwaddch(board.board_win,tmp8->enemy.gety(),tmp8->enemy.getx()-1,' ');
				//delete all remaining bullets
				temp = tmp8->enemy.bullet.blt;
				while(temp!=NULL){
					mvwaddch(board.board_win,temp->yB,temp->xB,' '); //delete graphically the bullet
					temp = deleteEnemy8Bullets(temp,tmp8); //delete bullet
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
			if(tmp9->enemy.getLife() <= 0){ //Enemy life = 0
				mvwaddch(board.board_win,tmp9->enemy.gety(),tmp9->enemy.getx(),' '); //delete graphically the enemy
				//delete graphically the two guns
				mvwaddch(board.board_win,tmp9->enemy.gety(),tmp9->enemy.getx()+1,' ');
				mvwaddch(board.board_win,tmp9->enemy.gety(),tmp9->enemy.getx()-1,' ');
				//delete all remaining bullets
				temp = tmp9->enemy.bullet.blt;
				while(temp!=NULL){
					mvwaddch(board.board_win,temp->yB,temp->xB,' '); //delete graphically the bullet
					temp = deleteEnemy9Bullets(temp,tmp9); //delete bullet
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

void Game::mapMovement(){
	int choice;
	choice = player.getmv(); //save the movement
	if(!player.ACTIVE_FLY){
		if(!player.activejump){ //you are not jumping
			switch (choice)
			{
				case KEY_LEFT:
					player.setDir(-1);  //direction of the player
					xMin--; //decrement the variable
					if(xMin<0) xMin = 0; //avoid exit
					break;
				case KEY_RIGHT:
					player.setDir(1); //direction of the player
					xMin++; //increment the variable
					if(xMin>map.getDim_x()-90) xMin--; //avoid exit
					break;
				case KEY_UP:
					if(player.getDir()==1){ //the jump depends on previous player direction
						xMin++; //increment the variable
						if(xMin>map.getDim_x()-90) xMin--; //avoid exit
					}
					else{
						xMin--; //decrement the variable
						if(xMin<0) xMin = 0; //avoid exit
					}
					break;
				case 't': //teleport
					if(player.teleportation.getQnt()>0){ //check if the player has teleport
						if(player.getDir()==1) //the jump depends on previous player direction
							for(int i=0;i<player.TELEPORT_DISTANCE[player.teleportation.getQnt()-1];i++){
								xMin++; //increment the variable
								if(xMin>map.getDim_x()-90) xMin--; //avoid exit
							}
						else
							for(int i=0;i<player.TELEPORT_DISTANCE[player.teleportation.getQnt()-1];i++){
								xMin--; //decrement the variable
								if(xMin<0) xMin = 0; //avoid exit
							}
						player.teleportation.setQnt(0); //delete teleports you have
					}
					break;
				default:
					break;
			}
			Game::PlayerCanMove(choice); //check if you can move
			//Game::StructureUpdate();;
		}
		else{
			player.jump();
			if(player.getDir()==1){ //the jump depends on previous player direction
				xMin++;
				if(xMin>map.getDim_x()-90) xMin--; //avoid exit
			}
			else{
				xMin--;
				if(xMin<0) xMin = 0; //avoid exit
				}
			Game::PlayerCanMove(KEY_UP); //check if you can move (you are jumping)
			player.display();
			player.airshoot(); //if you want shoot you have to press h
			//Game::StructureUpdate();;
		}
	}
	else{
		switch(choice){
			case KEY_LEFT:
				player.setDir(-1);  //direction of the player
				mapright(); //map movement (opposite movement with respect to the player)
				break;
			case KEY_RIGHT:
				player.setDir(1); //direction of the player
				mapleft(); //map movement (opposite movement with respect to the player)
				break;
			case KEY_UP:
				player.goup(); //go up
				break;
			case KEY_DOWN:
				player.godown(); //go down
				break;
			default:
				break;
		}
		Game::PlayerCanFly(choice); //check if you can fly
		//Game::StructureUpdate();
	}
	PrintMap(); //map movement
	//see player
	player.display();
}

void Game::mapleft(){ //move left

	//move alle enemies
	listenm0 tmp0=enemies0;
	while(tmp0!=NULL)
	{
		mvwaddch(board.board_win,tmp0->enemy.gety(),tmp0->enemy.getx(),' '); //delete enemy
		tmp0->enemy.updateCoordinates(-1,0); //go left
		tmp0->enemy.setXpern(tmp0->enemy.getXpern()-1); //change pern block
		tmp0=tmp0->next; //change enemy
	}
	listenm1 tmp1=enemies1;
	while(tmp1!=NULL)
	{
		mvwaddch(board.board_win,tmp1->enemy.gety(),tmp1->enemy.getx(),' '); //delete enemy
		tmp1->enemy.updateCoordinates(-1,0); //go left
		tmp1->enemy.setXpern(tmp1->enemy.getXpern()-1);//change pern block
		tmp1=tmp1->next; //change enemy
	}
	listenm2 tmp2=enemies2;
	while(tmp2!=NULL)
	{
		mvwaddch(board.board_win,tmp2->enemy.gety(),tmp2->enemy.getx(),' '); //delete enemy
		tmp2->enemy.updateCoordinates(-1,0);//go left
		tmp2=tmp2->next; //change enemy
	}
	listenm3 tmp3=enemies3;
	while(tmp3!=NULL)
	{
		mvwaddch(board.board_win,tmp3->enemy.gety(),tmp3->enemy.getx(),' '); //delete enemy
		tmp3->enemy.updateCoordinates(-1,0);//go left
		tmp3->enemy.setXpern(tmp3->enemy.getXpern()-1);//change pern block
		tmp3=tmp3->next; //change enemy
	}
	listenm4 tmp4=enemies4;
	while(tmp4!=NULL)
	{
		mvwaddch(board.board_win,tmp4->enemy.gety(),tmp4->enemy.getx(),' '); //delete enemy
		tmp4->enemy.updateCoordinates(-1,0);//go left
		tmp4->enemy.setXpern(tmp4->enemy.getXpern()-1);//change pern block
		tmp4=tmp4->next; //change enemy
	}
	listenm5 tmp5=enemies5;
	while(tmp5!=NULL)
	{
		mvwaddch(board.board_win,tmp5->enemy.gety(),tmp5->enemy.getx(),' '); //delete enemy
		tmp5->enemy.updateCoordinates(-1,0);//go left
		tmp5=tmp5->next; //change enemy
	}
	listenm6 tmp6=enemies6;
	while(tmp6!=NULL)
	{
		mvwaddch(board.board_win,tmp6->enemy.gety(),tmp6->enemy.getx(),' '); //delete enemy
		mvwaddch(board.board_win,tmp6->enemy.gety(),tmp6->enemy.getx()+tmp6->enemy.getSign(),' '); //delete gun
		tmp6->enemy.updateCoordinates(-1,0);//go left
		tmp6->enemy.setXpern(tmp6->enemy.getXpern()-1);//change pern block
		tmp6=tmp6->next; //change enemy
	}
	listenm7 tmp7=enemies7;
	while(tmp7!=NULL)
	{
		mvwaddch(board.board_win,tmp7->enemy.gety(),tmp7->enemy.getx(),' '); //delete enemy
		mvwaddch(board.board_win,tmp7->enemy.gety(),tmp7->enemy.getx()+tmp7->enemy.getSign(),' '); //delete gun
		tmp7->enemy.updateCoordinates(-1,0);//go left
		tmp7=tmp7->next; //change enemy
	}
	listenm8 tmp8=enemies8;
	while(tmp8!=NULL)
	{
		mvwaddch(board.board_win,tmp8->enemy.gety(),tmp8->enemy.getx(),' '); //delete enemy
		mvwaddch(board.board_win,tmp8->enemy.gety(),tmp8->enemy.getx()+tmp8->enemy.getSign(),' '); //delete gun
		tmp8->enemy.updateCoordinates(-1,0);//go left
		tmp8=tmp8->next; //change enemy
	}
	listenm9 tmp9=enemies9;
	while(tmp9!=NULL)
	{
		mvwaddch(board.board_win,tmp9->enemy.gety(),tmp9->enemy.getx(),' '); //delete enemy
		mvwaddch(board.board_win,tmp9->enemy.gety(),tmp9->enemy.getx()+1,' '); //delete gun
		mvwaddch(board.board_win,tmp9->enemy.gety(),tmp9->enemy.getx()-1,' '); //delete gun
		tmp9->enemy.updateCoordinates(-1,0);//go left
		tmp9=tmp9->next; //change enemy
	}

	//move all bullets

	bullt blt = player.bullet.blt; //player bullets
	while(blt!=NULL){
		mvwaddch(board.board_win,blt->yB,blt->xB,' '); //delete bullet
		blt->xB--; //go left
		blt = blt->next; //change bullet
	}

	tmp6 = enemies6; //enemy type6
	while(tmp6!=NULL){ //all enemies
		blt = tmp6->enemy.bullet.blt; //all bullets
		while(blt!=NULL){
			mvwaddch(board.board_win,blt->yB,blt->xB,' '); //delete bullet
			blt->xB--; //go left
			blt = blt->next; //change bullet
		}
		tmp6 = tmp6->next;
	}

	tmp7 = enemies7; //enemy type7
	while(tmp7!=NULL){ //all enemies
		blt = tmp7->enemy.bullet.blt; //all bullets
		while(blt!=NULL){
			mvwaddch(board.board_win,blt->yB,blt->xB,' '); //delete bullet
			blt->xB--; //go left
			blt = blt->next; //change bullet
		}
		tmp7 = tmp7->next;
	}

	tmp8 = enemies8; //enemy type8
	while(tmp8!=NULL){ //all enemies
		blt = tmp8->enemy.bullet.blt; //all bullets
		while(blt!=NULL){
			mvwaddch(board.board_win,blt->yB,blt->xB,' '); //delete bullet
			blt->xB--; //go left
			blt = blt->next; //change bullet
		}
		tmp8 = tmp8->next;
	}

	tmp9 = enemies9; //enemy type9
	while(tmp9!=NULL){ //all enemies
		blt = tmp9->enemy.bullet.blt; //all bullets
		while(blt!=NULL){
			mvwaddch(board.board_win,blt->yB,blt->xB,' '); //delete bullet
			blt->xB--; //go left
			blt = blt->next; //change bullet
		}
		tmp9 = tmp9->next;
	}
}

void Game::mapright(){ //move right
	//move all enemies
	listenm0 tmp0=enemies0;
	while(tmp0!=NULL)
	{
		mvwaddch(board.board_win,tmp0->enemy.gety(),tmp0->enemy.getx(),' '); //delete enemy
		tmp0->enemy.updateCoordinates(1,0); //go right
		tmp0->enemy.setXpern(tmp0->enemy.getXpern()+1); //change pern block
		tmp0=tmp0->next; //change enemy
	}
	listenm1 tmp1=enemies1;
	while(tmp1!=NULL)
	{
		mvwaddch(board.board_win,tmp1->enemy.gety(),tmp1->enemy.getx(),' '); //delete enemy
		tmp1->enemy.updateCoordinates(1,0);//go right
		tmp1->enemy.setXpern(tmp1->enemy.getXpern()+1);//change pern block
		tmp1=tmp1->next; //change enemy
	}
	listenm2 tmp2=enemies2;
	while(tmp2!=NULL)
	{
		mvwaddch(board.board_win,tmp2->enemy.gety(),tmp2->enemy.getx(),' ');//delete enemy
		tmp2->enemy.updateCoordinates(1,0);//go right
		tmp2=tmp2->next; //change enemy
	}
	listenm3 tmp3=enemies3;
	while(tmp3!=NULL)
	{
		mvwaddch(board.board_win,tmp3->enemy.gety(),tmp3->enemy.getx(),' ');//delete enemy
		tmp3->enemy.updateCoordinates(1,0);//go right
		tmp3->enemy.setXpern(tmp3->enemy.getXpern()+1);//change pern block
		tmp3=tmp3->next; //change enemy
	}
	listenm4 tmp4=enemies4;
	while(tmp4!=NULL)
	{
		mvwaddch(board.board_win,tmp4->enemy.gety(),tmp4->enemy.getx(),' ');//delete enemy
		tmp4->enemy.updateCoordinates(1,0);//go right
		tmp4->enemy.setXpern(tmp4->enemy.getXpern()+1);//change pern block
		tmp4=tmp4->next; //change enemy
	}
	listenm5 tmp5=enemies5;
	while(tmp5!=NULL)
	{
		mvwaddch(board.board_win,tmp5->enemy.gety(),tmp5->enemy.getx(),' ');//delete enemy
		tmp5->enemy.updateCoordinates(1,0);//go right
		tmp5=tmp5->next; //change enemy
	}
	listenm6 tmp6=enemies6;
	while(tmp6!=NULL)
	{
		mvwaddch(board.board_win,tmp6->enemy.gety(),tmp6->enemy.getx(),' ');//delete enemy
		mvwaddch(board.board_win,tmp6->enemy.gety(),tmp6->enemy.getx()+tmp6->enemy.getSign(),' '); //delete gun
		tmp6->enemy.updateCoordinates(1,0);//go right
		tmp6->enemy.setXpern(tmp6->enemy.getXpern()+1);//change pern block
		tmp6=tmp6->next; //change enemy
	}
	listenm7 tmp7=enemies7;
	while(tmp7!=NULL)
	{
		mvwaddch(board.board_win,tmp7->enemy.gety(),tmp7->enemy.getx(),' ');//delete enemy
		mvwaddch(board.board_win,tmp7->enemy.gety(),tmp7->enemy.getx()+tmp7->enemy.getSign(),' ');//delete gun
		tmp7->enemy.updateCoordinates(1,0);//go right
		tmp7=tmp7->next; //change enemy
	}
	listenm8 tmp8=enemies8;
	while(tmp8!=NULL)
	{
		mvwaddch(board.board_win,tmp8->enemy.gety(),tmp8->enemy.getx(),' ');//delete enemy
		mvwaddch(board.board_win,tmp8->enemy.gety(),tmp8->enemy.getx()+tmp8->enemy.getSign(),' ');//delete gun
		tmp8->enemy.updateCoordinates(1,0);//go right
		tmp8=tmp8->next; //change enemy
	}
	listenm9 tmp9=enemies9;
	while(tmp9!=NULL)
	{
		mvwaddch(board.board_win,tmp9->enemy.gety(),tmp9->enemy.getx(),' ');//delete enemy
		mvwaddch(board.board_win,tmp9->enemy.gety(),tmp9->enemy.getx()+1,' ');//delete gun
		mvwaddch(board.board_win,tmp9->enemy.gety(),tmp9->enemy.getx()-1,' ');//delete gun
		tmp9->enemy.updateCoordinates(1,0);//go right
		tmp9=tmp9->next; //change enemy
	}

	//move all bullets

	bullt blt = player.bullet.blt; //player bullets

	while(blt!=NULL){
		mvwaddch(board.board_win,blt->yB,blt->xB,' '); //delete bullet
		blt->xB++; //go right
		blt = blt->next; //change bullet
	}

	tmp6 = enemies6; //enemy type6
	while(tmp6!=NULL){ //all enemies
		blt = tmp6->enemy.bullet.blt; //all bullets
		while(blt!=NULL){
			mvwaddch(board.board_win,blt->yB,blt->xB,' '); //delete bullet
			blt->xB++; //go right
			blt = blt->next; //change bullet
		}
		tmp6 = tmp6->next;
	}

	tmp7 = enemies7; //enemy type7
	while(tmp7!=NULL){ //all enemies
		blt = tmp7->enemy.bullet.blt; //all bullets
		while(blt!=NULL){
			mvwaddch(board.board_win,blt->yB,blt->xB,' '); //delete bullet
			blt->xB++; //go right
			blt = blt->next; //change bullet
		}
		tmp7 = tmp7->next;
	}

	tmp8 = enemies8; //enemy type8
	while(tmp8!=NULL){ //all enemies
		blt = tmp8->enemy.bullet.blt; //all bullets
		while(blt!=NULL){
			mvwaddch(board.board_win,blt->yB,blt->xB,' '); //delete bullet
			blt->xB++; //go right
			blt = blt->next; //change bullet
		}
		tmp8 = tmp8->next;
	}

	tmp9 = enemies9; //enemy type9
	while(tmp9!=NULL){ //all enemies
		blt = tmp9->enemy.bullet.blt; //all bullets
		while(blt!=NULL){
			mvwaddch(board.board_win,blt->yB,blt->xB,' '); //delete bullet
			blt->xB++; //go right
			blt = blt->next; //change bullet
		}
		tmp9 = tmp9->next;
	}
}

void Game::PlayerDown(){
	player.godown(); //go down
	player.display(); //see the player
	player.airshoot(); //you can shoot
}

void Game::PlayerCanFly(int choice){ //Player can or cannot fly
	switch(choice){
		case KEY_LEFT: //you went to sx
			if(player.gun.getName()=="none"){ //no gun
				if(board.IsThereStructure(player.getx(),player.gety())){ //check it there has been collision
					mapleft(); //move map
				}
			}
			else{ //gun
				if(board.IsThereStructure(player.getx()+player.getDir(),player.gety())){ //check it there has been collision
					mapleft(); //move map
				}
			}
			break;
		case KEY_RIGHT: //you went to dx
			if(player.gun.getName()=="none"){ //no gun
				if(board.IsThereStructure(player.getx(),player.gety())){ //check it there has been collision
					mapright(); //move map
				}
			}
			else{ //gun
				if(board.IsThereStructure(player.getx()+player.getDir(),player.gety())){ //check it there has been collision
					mapright(); //move map
				}
			}
			break;
		case KEY_UP: //you went to up
			if(board.IsThereStructure(player.getx(),player.gety())){ //check it there has been collision
				player.godown(); //move map
			}
			break;
		case KEY_DOWN: //you went to down
			if(board.IsThereStructure(player.getx(),player.gety())){ //check it there has been collision
				player.goup(); //move map
			}
			break;
		default:
			break;
	}
}

void Game::PlayerCanMove(int choice){ //Player can or cannot move
	//bool down;
	switch(choice){
	case KEY_LEFT: //you went to sx
		if(player.gun.getName()=="none"){ //no gun
			if(map.isSolid(player.getx()+xMin,player.gety())){ //check it there has been collision
				xMin++; //increment the variable
				PrintMap(); //map movement
			}
			else{
				while(!map.isSolid(player.getx()+xMin,player.gety()+1)){ //check if you have something under your feet
					Game::PlayerDown(); //go down
				}
			}
		}
		else{ //gun
			if(map.isSolid(player.getx()+xMin+player.getDir(),player.gety())){ //check it there has been collision
				xMin++; //increment the variable
				PrintMap(); //map movement
			}
			else{
				while(!map.isSolid(player.getx()+xMin,player.gety()+1)){ //check if you have something under your feet
					Game::PlayerDown(); //go down
				}
			}
		}
		break;
	case KEY_RIGHT: //you went to dx
		if(player.gun.getName()=="none"){ //no gun
			if(map.isSolid(player.getx()+xMin,player.gety())){ //check it there has been collision
				xMin--;
				PrintMap(); //map movement
			}
			else{
				while(!map.isSolid(player.getx()+xMin,player.gety()+1)){ //check if you have something under your feet
					Game::PlayerDown(); //go down
				}
			}
		}
		else{ //gun
			if(map.isSolid(player.getx()+xMin+player.getDir(),player.gety())){ //check it there has been collision
				xMin--;
				PrintMap(); //map movement
			}
			else{
				while(!map.isSolid(player.getx()+xMin,player.gety()+1)){ //check if you have something under your feet
					Game::PlayerDown(); //go down
				}
			}
		}
		break;
	case KEY_UP: //you went up
		if(player.gun.getName()=="none"){ //no gun
			if(map.isSolid(player.getx()+xMin,player.gety())){ //check if you reach one piece of one structure
				if(player.getDir()==1){ //you have to go where you went(it depends on the direction)
					xMin--;
					PrintMap(); //map movement
				}
				else{
					xMin++; //increment the variable
					PrintMap(); //map movement
				}
				player.SetJump(); //for the next jump
				while(!map.isSolid(player.getx()+xMin,player.gety()+1)){ //check if you have something under your feet
					Game::PlayerDown(); //go down
				}
			}
			else if(map.isSolid(player.getx()+xMin,player.gety()-1) || map.isSolid(player.getx()+xMin,player.gety()+1)){ //check if you have something under your feet or over you head
				player.SetJump(); //for the next jump
				while(!map.isSolid(player.getx()+xMin,player.gety()+1)){ //check if you have something under your feet
					Game::PlayerDown(); //go down
				}
			}
			else if(player.activejump == false){
				while(!map.isSolid(player.getx()+xMin,player.gety()+1)){ //check if you have something under your feet
					Game::PlayerDown(); //go down
				}
			}
		}
		else{ //gun
			if(map.isSolid(player.getx()+xMin+player.getDir(),player.gety())){ //check if the gun reaches one piece of one structure
				if(player.getDir()==1){ //you have to go where you went(it depends on the direction)
					xMin--;
					PrintMap(); //map movement
				}
				else{
					xMin++; //increment the variable
					PrintMap(); //map movement
				}
				player.SetJump(); //for the next jump
				while(!map.isSolid(player.getx()+xMin,player.gety()+1)){ //check if you have something under your feet
					Game::PlayerDown(); //go down
				}
			}
			else if(map.isSolid(player.getx()+xMin,player.gety()-1) || map.isSolid(player.getx()+xMin,player.gety()+1)){ //check if you have something under your feet or over you head
				player.SetJump(); //for the next jump
				while(!map.isSolid(player.getx()+xMin,player.gety()+1)){ //check if you have something under your feet
					Game::PlayerDown(); //go down
				}
			}
			else if(player.activejump == false){
				while(!map.isSolid(player.getx()+xMin,player.gety()+1)){ //check if you have something under your feet
					Game::PlayerDown(); //go down
				}
			}
		}
		break;
	default:
		break;
	}
}

void Game::Enemy0CanMove(listenm0 h){ //Enemies can or cannot move
	if(board.IsThereStructure(h->enemy.getx(),h->enemy.gety())){ //check it there has been collision
		h->enemy.updateCoordinates(-h->enemy.getSign(),0); //you have to go from you went
		h->enemy.setSign(); //change the direction
	}
	else{
		while(!board.IsThereStructure(h->enemy.getx(),h->enemy.gety()+1) && h->enemy.gety()!= board.height-2){ //check if you have something under your feet
			h->enemy.EnemyGoDown(); //go down
		}
	}
}

void Game::Enemy1CanMove(listenm1 h){ //Enemies can or cannot move
	if(board.IsThereStructure(h->enemy.getx(),h->enemy.gety())){ //check it there has been collision
		if(h->enemy.ReachAngles()){ //vertical collision
			h->enemy.updateCoordinates(0,-h->enemy.getUp()); //you have to go from you went
			h->enemy.setUp(); //change the vertical direction
		}
		else{ //orrizontal collision
			h->enemy.updateCoordinates(-h->enemy.getSign(),0); //you have to go from you went
			h->enemy.setSign(); //change the orrizontal direction
		}
	}
}

void Game::Enemy2CanMove(listenm2 h){ //Enemies can or cannot move
	if(board.IsThereStructure(h->enemy.getx(),h->enemy.gety())){ //check if you have something under your feet or over you head
		h->enemy.updateCoordinates(0,-h->enemy.getSign()); //you have to go from you went
		h->enemy.setSign(); //change the vertical direction
	}
}

void Game::Enemy3CanMove(listenm3 h){ //Enemies can or cannot move
	if(board.IsThereStructure(h->enemy.getx(),h->enemy.gety())){ //check if reach one piece of one structure
		h->enemy.updateCoordinates(-h->enemy.getSign(),-1); //you have to go where you went(it depends on the direction)
		h->enemy.SetJump(); //for the next jump
		while(!board.IsThereStructure(h->enemy.getx(),h->enemy.gety()+1) && h->enemy.gety()!= board.height-2){ //check if you have something under your feet
			h->enemy.EnemyGoDown(); //go down
			h->enemy.display(); //see enemy
		}
	}
	else if(board.IsThereStructure(h->enemy.getx(),h->enemy.gety()-1) || board.IsThereStructure(h->enemy.getx(),h->enemy.gety()+1)){ //check if you have something under your feet or over you head
		h->enemy.SetJump(); //for the next jump
		while(!board.IsThereStructure(h->enemy.getx(),h->enemy.gety()+1) && h->enemy.gety()!= board.height-2){ //check if you have something under your feet
			h->enemy.EnemyGoDown(); //go down
			h->enemy.display(); //see enemy
		}
	}
	else if(h->enemy.GetConta()==0 && !board.IsThereStructure(h->enemy.getx(),h->enemy.gety()+1)){
		h->enemy.SetJump(); //for the next jump
		while(!board.IsThereStructure(h->enemy.getx(),h->enemy.gety()+1) && h->enemy.gety()!= board.height-2){ //check if you have something under your feet
			h->enemy.EnemyGoDown(); //go down
			h->enemy.display(); //see enemy
		}
	}
}

void Game::Enemy4CanMove(listenm4 h){ //Enemies can or cannot move
	if(board.IsThereStructure(h->enemy.getx(),h->enemy.gety())){ //check it there has been collision
		while(board.IsThereStructure(h->enemy.getx(),h->enemy.gety())){ //until your teleport is ok you have to change the position
			h->enemy.movement();
		}
	}
	else{
		while(!board.IsThereStructure(h->enemy.getx(),h->enemy.gety()+1) && h->enemy.gety()!= board.height-2){ //check if you have something under your feet
			h->enemy.EnemyGoDown(); //go down
		}
	}
}

void Game::Enemy5CanMove(listenm5 h){ //Enemies can or cannot move
	if(board.IsThereStructure(h->enemy.getx(),h->enemy.gety())){ //check it there has been collision
		h->enemy.updateCoordinates(-h->enemy.getSign(),0); //you have to go from you went
		//stay there
	}
	else{
		while(!board.IsThereStructure(h->enemy.getx(),h->enemy.gety()+1) && h->enemy.gety()!= board.height-2){ //check if you have something under your feet
			h->enemy.EnemyGoDown(); //go down
		}
	}
}

void Game::Enemy6CanMove(listenm6 h){ //Enemies can or cannot move
	if(board.IsThereStructure(h->enemy.getx()+h->enemy.getSign(),h->enemy.gety())){ //check it there has been collision
		h->enemy.updateCoordinates(-h->enemy.getSign(),0); //you have to go from you went
		h->enemy.setSign(); //change the direction
	}
	else{
		while(!board.IsThereStructure(h->enemy.getx(),h->enemy.gety()+1) && h->enemy.gety()!= board.height-2){ //check if you have something under your feet
			h->enemy.EnemyGoDown(); //go down
		}
	}
}

void Game::Enemy7CanMove(listenm7 h){ //Enemies can or cannot move
	if(board.IsThereStructure(h->enemy.getx()+h->enemy.getSign(),h->enemy.gety())){ //check it there has been collision
		h->enemy.updateCoordinates(-h->enemy.getSign(),0); //you have to go from you went
		//stay there
	}
	else{
		while(!board.IsThereStructure(h->enemy.getx(),h->enemy.gety()+1) && h->enemy.gety()!= board.height-2){ //check if you have something under your feet
			h->enemy.EnemyGoDown(); //go down
		}
	}
}

void Game::Enemy8CanMove(listenm8 h){ //Enemies can or cannot move
	while(!board.IsThereStructure(h->enemy.getx(),h->enemy.gety()+1) && h->enemy.gety()!= board.height-2){ //check if you have something under your feet
		h->enemy.EnemyGoDown(); //go down
	}
}

void Game::Enemy9CanMove(listenm9 h){ //Enemies can or cannot move
	if(board.IsThereStructure(h->enemy.getx(),h->enemy.gety())){ //check if you have something under your feet or over you head
		h->enemy.updateCoordinates(0,-h->enemy.getSign()); //you have to go from you went
		h->enemy.setSign(); //change the vertical direction
	}
}

void Game::enemyMovement(){	//Enemies movement
	listenm0 tmp = enemies0; //type0
	while(tmp!=NULL){
		tmp->enemy.movement(); //move one enemy
		Game::Enemy0CanMove(tmp); //interaction with the structure
		tmp->enemy.display(); //see one enemy
		Game::interaction(tmp->enemy); //check the interaction between one enemy and the player
		tmp = tmp->next; //go to the next enemy
	}
	listenm1 tmp1 = enemies1; //type1
	while(tmp1!=NULL){
		tmp1->enemy.movement(); //move one enemy
		Game::Enemy1CanMove(tmp1); //interaction with the structure
		tmp1->enemy.display(); //see one enemy
		Game::interaction(tmp1->enemy); //check the interaction between one enemy and the player
		tmp1 = tmp1->next; //go to the next enemy
	}

	listenm2 tmp2 = enemies2; //type2
	while(tmp2!=NULL){
		tmp2->enemy.movement(); //move one enemy
		Game::Enemy2CanMove(tmp2); //interaction with the structure
		tmp2->enemy.display(); //see one enemy
		Game::interaction(tmp2->enemy); //check the interaction between one enemy and the player
		tmp2 = tmp2->next; //go to the next enemy
	}

	listenm3 tmp3 = enemies3; //type3
	while(tmp3!=NULL){
		tmp3->enemy.movement(); //move one enemy
		Game::Enemy3CanMove(tmp3); //interaction with the structure
		tmp3->enemy.display(); //see one enemy
		Game::interaction(tmp3->enemy); //check the interaction between one enemy and the player
		tmp3 = tmp3->next; //go to the next enemy
	}

	listenm4 tmp4 = enemies4; //type4
	while(tmp4!=NULL){
		tmp4->enemy.movement(); //move one enemy
		Game::Enemy4CanMove(tmp4); //interaction with the structure
		tmp4->enemy.display(); //see one enemy
		Game::interaction(tmp4->enemy); //check the interaction between one enemy and the player
		tmp4 = tmp4->next; //go to the next enemy
	}

	int dir;
	listenm5 tmp5 = enemies5; //type5
	while(tmp5!=NULL){
		dir = Game::directionSmartEnemy5(tmp5->enemy);
		if(abs(player.getx() - tmp5->enemy.getx()) <= 20){ //player is sufficiently near to enemy type5
			tmp5->enemy.movement(dir); //move one enemy
		}
		Game::Enemy5CanMove(tmp5); //interaction with the structure
		tmp5->enemy.display(); //see one enemy
		Game::interaction(tmp5->enemy); //check the interaction between one enemy and the player
		tmp5 = tmp5->next; //go to the next enemy
	}

	listenm6 tmp6 = enemies6;  //type6
	while(tmp6!=NULL){
		tmp6->enemy.movement(); //move one enemy
		Game::Enemy6CanMove(tmp6); //interaction with the structure
		tmp6->enemy.display(); //see one enemy
		Game::interaction(tmp6->enemy);
		tmp6 = tmp6->next; //go to the next enemy
	}

	listenm7 tmp7 = enemies7;  //type7
	while(tmp7!=NULL){
		dir = Game::directionSmartEnemy7(tmp7->enemy);
		if(abs(player.getx() - tmp7->enemy.getx()) <=30 && player.gety()==tmp7->enemy.gety()){ //player is sufficiently near to enemy type7
			tmp7->enemy.movement(dir); //move one enemy
		}
		Game::Enemy7CanMove(tmp7); //interaction with the structure
		tmp7->enemy.display(); //see one enemy
		tmp7 = tmp7->next; //go to the next enemy
	}

	listenm8 tmp8 = enemies8;  //type8
	while(tmp8!=NULL){
		dir = Game::directionSmartEnemy8(tmp8->enemy);
		if((abs(player.getx() - tmp8->enemy.getx()) <= 20) && (player.gety() == tmp8->enemy.gety())){ //player is sufficiently near to enemy type8
			tmp8->enemy.movement(dir); //move one enemy
		}
		Game::Enemy8CanMove(tmp8);
		tmp8->enemy.display(); //see one enemy
		Game::interaction(tmp8->enemy);
		tmp8 = tmp8->next; //go to the next enemy
	}

	listenm9 tmp9 = enemies9;  //type9
	while(tmp9!=NULL){
		tmp9->enemy.movement(); //move one enemy
		Game::Enemy9CanMove(tmp9); //interaction with the structure
		tmp9->enemy.display(); //see one enemy
		Game::interaction(tmp9->enemy);
		tmp9 = tmp9->next; //go to the next enemy
	}

}

//list of function for enemies

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
