/*
 * Game.cpp
 *
 *  Created on: 11 dic 2022
 *      Author: david
 */

#include "Game.hpp"
#include <fstream>

Game::Game(int height,int width){

	start_color();
	init_pair(1,COLOR_RED, COLOR_BLACK);
	init_pair(2,COLOR_GREEN,COLOR_BLACK);
	init_pair(3,COLOR_YELLOW,COLOR_BLACK);
	init_pair(4,COLOR_BLUE,COLOR_BLACK);


	//Initialize Power-ups
	initializePowerUp();

	board = Board(height,width); //create the board
	board.initialize(0,0); //initialize the board in 0,0
	WINDOW* win = board.board_win;

	HEIGHT_MARKET = 15; //height of powerups
	draw_cost1 = 213;
	draw_cost2 = 185;
	draw_cost3 = 150;
	Market_Active = false; //you are not in the market when you start
	Market_Build = false;
	//bought nothing
	bought1 = false;
	bought2 = false;
	bought3 = false;

	//start the map
	difficulty = 0;
	mapList = NULL;
	nextMap(1, difficulty);

	xMin = 5; //start camera

	//print all map
	Game::PrintMap();

	player = Player(win,height-6,20); //create the player
	player.initialize(); //initialize the player

	time = 0; //time for the game

	game_over = false;
}

void Game::updateState(){

	//display title
	handleDisplay();

	//Map movement
	if(time%200 == 0)mapMovement(); //We move the map on horizontal direction and the player only on vertical direction

	//coins
	handleCoins();

	//handle shooting
	shooting();

	//enemy movement
	if(time%400 == 0)enemyMovement(); //you want to slow down enemies
	time++;

	//maps and market
	handleMaps();

	//Update board
	Game::UpdateBoard();

	//end of the game
	if(player.getHP().getQnt() <= 0) game_over = true; //Player death

}

void Game::handleCoins(){
	//check if you take one coin
	if(mapList->map.updateCoins(xMin+player.getx(), player.gety())){
		matrix[player.gety()][xMin+player.getx()] = ' '; //update the map removing coin
		player.updateCash(1); //increment cashes of player
	}

	//redraw all coins (avoid they disappear due to enemies movement)
	mony m = mapList->map.getCoins();
	while(m != NULL){
		matrix[m->y][m->x] = '$';
		m = m->next;
	}
}

void Game::handleMaps(){
	//next map (you finish market level)
	if(player.getx()+xMin == mapList->map.get_trigger_market()){ //go to the next map
		Market_Active = false; //you leave the market
		//raise all descriptions
		deleteDescription(0);
		deleteDescription(1);
		deleteDescription(2);
		//delete powerups
		deletePowerup(spawn_powerup); //you have to raise powerups from the matrix
		//update bought variables
		bought1 = false;
		bought2 = false;
		bought3 = false;
		updateDifficulty();
		nextMap(1, difficulty);
	}
	else if(player.getx()+xMin == mapList->map.get_trigger_end()){ 	//go to market
		//teleport player to market
		Market_Active = true; //you are in the market
		Market_Build = true; //you have to build the market

		xMin = xMin + 85;
		PrintMap();
	}
	else if(player.getx()+xMin == mapList->map.get_trigger_start()){
		nextMap(0,0);
	}


	if(Market_Build){ //check if the market is built
		market_build();
		Market_Build = false; //you have built the market
	}
	else if(Market_Active){ //check the position of the player in the market
		market();
	}
	else{
		player.setBuy(false); //you can't
	}
}

void Game::handleDisplay(){
	if(!Market_Active)displayGame();
	else displayMarket();
	//display life
	displayLife();
	//display coins
	displayCoins();
	//display points
	displayPoints();
	//display bullets
	displayBullets();
	//display Powerup
	displayPowerup();
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

//dir decides the direction, 1 = right (generate next map/go to the next map already existing)
//0 = go the the previous map
void Game::nextMap(int dir, int difficulty = 0){//we call this when the player reaches a trigger
	if(mapList == NULL){//first map generation (you dont' have map
		mapList = new map_el;
		mapList->id=0;
		mapList->prev=NULL;
		mapList->next=NULL;
		mapList->map = Map(difficulty);
		matrix = mapList->map.toString();
	}
	else{
		if(dir == 1){//right
			if(mapList->next == NULL){//generate next map //new map
				
				mapList->next = new map_el;
				mapList->next->prev = mapList;
				mapList=mapList->next;

				mapList->id=mapList->prev->id+1; //change the id of the map
				mapList->next=NULL;
				mapList->map = Map(difficulty);
				matrix = mapList->map.toString();
			}
			else{//just move pointer to the next map (you have already visited)
				mapList = mapList->next;
				matrix = mapList->map.toString();
			}
			//restart also the variables of the game
			xMin = 5;
			time = 0;
		}
		else if(dir == 0){//left
			if(mapList->prev != NULL){//if this is not the first map
				mapList = mapList->prev;
				xMin = mapList->map.get_trigger_end()-(player.getx()+3);
				time = 0;
				matrix = mapList->map.toString();
			}
		}
	}
}

void Game::PrintMap(){ //print your map
	for(int i=0;i<mapList->map.getDim_y();i++){
		for(int j=xMin;j<mapList->map.getDim_x()&&j<xMin+110;j++){
			mvwaddch(board.board_win,i,j-xMin,matrix[i][j]);
		}
	}
}

void Game::market(){
	drawPowerUp(spawn_powerup); //draw powerups

	//check if the player buy some powerups
	//first powerup
	if(player.getx()+xMin>=mapList->map.getDim_x()-draw_cost1 && player.getx()+xMin<=mapList->map.getDim_x()-(draw_cost1-10)){
		//draw description
		drawDescription(0);
		deleteDescription(1);
		deleteDescription(2);
		if(player.getCoins()-spawn_powerup[0].price>=0 && !bought1  && player.getBuy()){ //you have enough money and it's the first powerup that you buy
			if(strcmp(player.getGun().name.c_str(),spawn_powerup[0].getName().c_str())!=0){ //you don't already have this gun
				player.updateCash(-spawn_powerup[0].price); //update cash of player
				player.setGun(spawn_powerup[0].getName()); //update powerups of player
				bought1 = true;
				player.setBuy(false); //you can buy another powerup
			}
		}
	}
	//second powerup
	if(player.getx()+xMin>=mapList->map.getDim_x()-draw_cost2 && player.getx()+xMin<=mapList->map.getDim_x()-(draw_cost2-10)){
		//draw description
		drawDescription(1);
		deleteDescription(0);
		deleteDescription(2);
		if(player.getCoins()-spawn_powerup[1].price>=0 && !bought2  && player.getBuy()){ //you have enough money and it's the first powerup that you buy
			//update powerups of player
			if(strcmp(spawn_powerup[1].getName().c_str(),"HP") == 0){ //HP
				player.updateCash(-spawn_powerup[1].price); //update cash of player
				bought2 = true;
				player.setBuy(false); //you can buy another powerup
				player.setHP(player.getHP().getQnt() + spawn_powerup[1].getQnt());
			}
			else if(strcmp(spawn_powerup[1].getName().c_str(),"Shield") == 0){ //Shield
				player.updateCash(-spawn_powerup[1].price); //update cash of player
				bought2 = true;
				player.setBuy(false); //you can buy another powerup
				player.setShield(player.getShield().getQnt() + spawn_powerup[1].getQnt());
			}
			else if(strcmp(spawn_powerup[1].getName().c_str(),"Jump") == 0  && player.getJumping().getQnt()<3){ //Jump
				player.updateCash(-spawn_powerup[1].price); //update cash of player
				bought2 = true;
				player.setBuy(false); //you can buy another powerup
				player.setJumping(player.getJumping().getQnt() + spawn_powerup[1].getQnt());
			}
			else if(strcmp(spawn_powerup[1].getName().c_str(),"Bullets") == 0){ //Bullets
				player.updateCash(-spawn_powerup[1].price); //update cash of player
				bought2 = true;
				player.setBuy(false); //you can buy another powerup
				player.setBullets(player.getBullets().getQnt() + spawn_powerup[1].getQnt());
			}
			else if(strcmp(spawn_powerup[1].getName().c_str(),"Explo_Bullets") == 0){ //Explosive bullets
				player.updateCash(-spawn_powerup[1].price); //update cash of player
				bought2 = true;
				player.setBuy(false); //you can buy another powerup
				player.setExplo_Bullets(player.getExplo_Bullets().getQnt() + spawn_powerup[1].getQnt());
			}
		}
	}
	//third powerup
	if(player.getx()+xMin>=mapList->map.getDim_x()-(draw_cost3) && player.getx()+xMin<=mapList->map.getDim_x()-(draw_cost3-10)){
		//draw description
		drawDescription(2);
		deleteDescription(0);
		deleteDescription(1);
		if(player.getCoins()-spawn_powerup[2].price>=0 && !bought3  && player.getBuy()){ ////you have enough money and it's the first powerup that you buy
			//update powerups of player
			if(strcmp(spawn_powerup[2].getName().c_str(),"Teleport") == 0 && player.getTeleportation().getQnt()<3){ //Teleport
				player.updateCash(-spawn_powerup[1].price); //update cash of player
				bought3 = true;
				player.setBuy(false); //you can buy another powerup
				player.setTeleportation(player.getTeleportation().getQnt() + spawn_powerup[2].getQnt());
			}
			else if(strcmp(spawn_powerup[2].getName().c_str(),"Armor") == 0 && player.getArmor().getQnt()<3){ //Armor
				player.updateCash(-spawn_powerup[1].price); //update cash of player
				bought3 = true;
				player.setBuy(false); //you can buy another powerup
				player.setArmor(player.getArmor().getQnt() + spawn_powerup[2].getQnt());
			}
			else if(strcmp(spawn_powerup[2].getName().c_str(),"Fly") == 0){ //Fly
				player.updateCash(-spawn_powerup[1].price); //update cash of player
				bought3 = true;
				player.setBuy(false); //you can buy another powerup
				player.setFly(player.getFly().getQnt() + spawn_powerup[2].getQnt());
			}
		}
	}
}

void Game::market_build(){ //build the market
	//Generate randomly 3 power-ups
	int a = rand()%NUM_GUNS;
	int b = rand()%NUM_BONUS;
	int c = rand()%NUM_ACTIVE;
	//update spawned powerups vector
	spawn_powerup[0] = guns[a];
	spawn_powerup[1] = bonus[b];
	spawn_powerup[2] = active[c];
}

void Game::drawDescription(int j){
	//show the description of powerup
	int s0 = strlen(spawn_powerup[j].getName().c_str());
	for(int i=0;i<s0;i++){
		if(j==0)matrix[5][mapList->map.getDim_x()-draw_cost1+i] = spawn_powerup[j].getName().c_str()[i]; //draw name of power up
		if(j==1)matrix[6][mapList->map.getDim_x()-draw_cost2+i] = spawn_powerup[j].getName().c_str()[i]; //draw name of power up
		if(j==2)matrix[7][mapList->map.getDim_x()-draw_cost3+i] = spawn_powerup[j].getName().c_str()[i]; //draw name of power up
	}
	int s1 = strlen(spawn_powerup[j].getDescription().c_str());
	for(int i=s0;i<s1+s0;i++){
		if(j==0)matrix[5][mapList->map.getDim_x()-draw_cost1+i] = spawn_powerup[j].getDescription().c_str()[i-s0]; //draw description of power up
		if(j==1)matrix[6][mapList->map.getDim_x()-draw_cost2+i] = spawn_powerup[j].getDescription().c_str()[i-s0]; //draw description of power up
		if(j==2)matrix[7][mapList->map.getDim_x()-draw_cost3+i] = spawn_powerup[j].getDescription().c_str()[i-s0]; //draw description of power up
	};
}
void Game::deleteDescription(int j){
	//show the description of powerup
	int s0 = strlen(spawn_powerup[j].getName().c_str());
	for(int i=0;i<s0;i++){
		if(j==0)matrix[5][mapList->map.getDim_x()-draw_cost1+i] = ' '; //delete name of power up
		if(j==1)matrix[6][mapList->map.getDim_x()-draw_cost2+i] = ' '; //delete name of power up
		if(j==2)matrix[7][mapList->map.getDim_x()-draw_cost3+i] = ' '; //delete name of power up
	}
	int s1 = strlen(spawn_powerup[j].getDescription().c_str());
	for(int i=s0;i<s1+s0;i++){
		if(j==0)matrix[5][mapList->map.getDim_x()-draw_cost1+i] = ' '; //delete description of power up
		if(j==1)matrix[6][mapList->map.getDim_x()-draw_cost2+i] = ' '; //delete description of power up
		if(j==2)matrix[7][mapList->map.getDim_x()-draw_cost3+i] = ' '; //delete description of power up
	};
}

void Game::initializePowerUp(){
	//(quantity of the guns is fixed to 1-->you can have just one gun)
	guns[0] = Powerup("Pistol", ": You can shoot one bullet", 1, 5, 1);
	guns[1] = Powerup("Rifle", ": You can shoot two bullets", 1, 10, 1);
	guns[2] = Powerup("Machinegun", ": You can shoot three bullets", 1, 15, 1);
	guns[3] = Powerup("Doublegun", ": You can shoot two bullets, one to dx direction and one to sx direction", 1, 15, 1);

    bonus[0] = Powerup("HP", ": Additional life (+1)", 1, 1, 1); //quantity corresponds to the number of lives which you have bought
	bonus[1] = Powerup("Shield", ": It blocks damage one time", 1, 5, 1);//quantity corresponds to the number of protection you have (max 2)
	bonus[2] = Powerup("Jump",": Change the height of the jump (+2)  (max 3)",2,5,1); //quantity corresponds to max (plus with respect to basic jump) height of the jump
	bonus[3] = Powerup("Bullets",": Charge of bullets",100,5,1); //quantity corresponds to the number of bullets
	bonus[4] = Powerup("Explo_Bullets",": Charge of explosive bullets",1,20,1); //quantity corresponds to the number of explosive bullets

	active[0] = Powerup("Armor", ": Become invincible for a limited time (max 3)", 1, 10, 1); //quantity corresponds to the number of protection you have (max 3)
	active[1] = Powerup("Teleport", ": Teleport a short distance (max 3)", 1, 10, 1); //quantity corresponds to the number of possibility of teleportation you have
	active[2] = Powerup("Fly",": You can fly for a limited time",1,20,1); //quantity corresponds to the number of fly you can do it (max 1)
}

void Game::drawPowerUp(Powerup pwp[]){ //Draw power-ups which are spawned
	//FIRST powerup
	int s0 = strlen(pwp[0].getName().c_str());
	for(int i=0;i<s0;i++){
		matrix[HEIGHT_MARKET][mapList->map.getDim_x()-draw_cost1+i] = pwp[0].getName().c_str()[i];
	}
	//SECOND powerup
	int s1 = strlen(pwp[1].getName().c_str());
	for(int i=0;i<s1;i++){
		matrix[HEIGHT_MARKET][mapList->map.getDim_x()-draw_cost2+i] = pwp[1].getName().c_str()[i];
	}
	//THIRD powerup
	int s2 = strlen(pwp[2].getName().c_str());
	for(int i=0;i<s2;i++){
		matrix[HEIGHT_MARKET][mapList->map.getDim_x()-draw_cost3+i] = pwp[2].getName().c_str()[i];
	}

	//print description of powerup
}

void Game::deletePowerup(Powerup pwp[]){
	//FIRST powerup
	int s0 = strlen(pwp[0].getName().c_str());
	for(int i=0;i<s0;i++){
		matrix[HEIGHT_MARKET][mapList->map.getDim_x()-draw_cost1+i] = ' ';
	}
	//SECOND powerup
	int s1 = strlen(pwp[1].getName().c_str());
	for(int i=0;i<s1;i++){
		matrix[HEIGHT_MARKET][mapList->map.getDim_x()-draw_cost2+i] = ' ';
	}
	//THIRD powerup
	int s2 = strlen(pwp[2].getName().c_str());
	for(int i=0;i<s2;i++){
		matrix[HEIGHT_MARKET][mapList->map.getDim_x()-draw_cost3+i] = ' ';
	}
}

void Game::updateDifficulty(){
	//once we exit the market level we update difficulty based on power-ups
	int diff = player.getGun().getDifficulty();
	diff += (player.getHP().getQnt()-player.getLife()) * player.getHP().getDifficulty(); //you start with a life
	diff += player.getShield().getQnt() * player.getShield().getDifficulty();
	diff += ((player.getJumping().getQnt()-5)/2)* player.getJumping().getDifficulty(); //you buy 2 jumping each time and your height at the beginning is 5
	diff += player.getArmor().getQnt() * player.getArmor().getDifficulty();
	diff += player.getTeleportation().getQnt() * player.getTeleportation().getDifficulty();
	diff += player.getFly().getQnt() * player.getFly().getDifficulty();
	diff += player.getBullets().getQnt()/100 * player.getBullets().getDifficulty(); //you buy 100 bullets each time
	diff += player.getExplo_Bullets().getQnt() * player.getExplo_Bullets().getDifficulty();
	difficulty = diff;
}

void Game::displayGame(){
	wattron(board.board_win,COLOR_PAIR(3)); //color
	mvwprintw(board.board_win,1,39,"WELCOME TO THIS NEW FANTASTIC GAME");
	wattroff(board.board_win,COLOR_PAIR(3)); //color
}

void Game::displayMarket(){
	wattron(board.board_win,COLOR_PAIR(3)); //color
	mvwprintw(board.board_win,1,45,"WELCOME TO MARKET LEVEL");
	wattroff(board.board_win,COLOR_PAIR(3)); //color
}

void Game::displayLife(){ //display life and bullets
	wattron(board.board_win,COLOR_PAIR(1)); //color
	mvwprintw(board.board_win,25,1,"Life: ");
	wattroff(board.board_win,COLOR_PAIR(1)); //color

	wattron(board.board_win,COLOR_PAIR(2)); //color
	mvwprintw(board.board_win,25,6,"%d",player.getHP().getQnt());
	if(player.getHP().getQnt()<100) mvwprintw(board.board_win,25,8," ");
	if(player.getHP().getQnt()<10) mvwprintw(board.board_win,25,7," ");
	wattroff(board.board_win,COLOR_PAIR(2)); //color
	mvwprintw(board.board_win,25,13,"%d",player.getBuy());
}

void Game::displayPowerup(){
	//powerups
	wattron(board.board_win,COLOR_PAIR(4)); //color
	mvwprintw(board.board_win,26,30,"--------------- LIST OF POWER-UP ---------------");
	wattroff(board.board_win,COLOR_PAIR(4)); //color

	//gun
	wattron(board.board_win,COLOR_PAIR(1)); //color
	mvwprintw(board.board_win,27,1,"Gun: ");
	wattroff(board.board_win,COLOR_PAIR(1)); //color

	wattron(board.board_win,COLOR_PAIR(2)); //color
	mvwprintw(board.board_win,27,5,player.getGun().getName().c_str());
	wattroff(board.board_win,COLOR_PAIR(2)); //color

	//armor
	wattron(board.board_win,COLOR_PAIR(1)); //color
	mvwprintw(board.board_win,27,17,"Armor: ");
	wattroff(board.board_win,COLOR_PAIR(1)); //color

	wattron(board.board_win,COLOR_PAIR(2)); //color
	mvwprintw(board.board_win,27,23,"%d",player.getArmor().getQnt());
	wattroff(board.board_win,COLOR_PAIR(2)); //color

	//shield
	wattron(board.board_win,COLOR_PAIR(1)); //color
	mvwprintw(board.board_win,27,30,"Shield: ");
	wattroff(board.board_win,COLOR_PAIR(1)); //color

	wattron(board.board_win,COLOR_PAIR(2)); //color
	mvwprintw(board.board_win,27,37,"%d",player.getShield().getQnt());
	wattroff(board.board_win,COLOR_PAIR(2)); //color

	//teleportation
	wattron(board.board_win,COLOR_PAIR(1)); //color
	mvwprintw(board.board_win,27,45,"Teleport: ");
	wattroff(board.board_win,COLOR_PAIR(1)); //color

	wattron(board.board_win,COLOR_PAIR(2)); //color
	mvwprintw(board.board_win,27,54,"%d",player.getTeleportation().getQnt());
	wattroff(board.board_win,COLOR_PAIR(2)); //color

	//fly
	wattron(board.board_win,COLOR_PAIR(1)); //color
	mvwprintw(board.board_win,27,63,"Fly: ");
	wattroff(board.board_win,COLOR_PAIR(1)); //color

	wattron(board.board_win,COLOR_PAIR(2)); //color
	mvwprintw(board.board_win,27,67,"%d",player.getFly().getQnt());
	wattroff(board.board_win,COLOR_PAIR(2)); //color

	//jumping
	wattron(board.board_win,COLOR_PAIR(1)); //color
	mvwprintw(board.board_win,27,75,"Jumping: ");
	wattroff(board.board_win,COLOR_PAIR(1)); //color

	wattron(board.board_win,COLOR_PAIR(2)); //color
	mvwprintw(board.board_win,27,83,"+");
	mvwprintw(board.board_win,27,84,"%d",(player.getJumping().getQnt() - 5)/2);
	wattroff(board.board_win,COLOR_PAIR(2)); //color

	//explosive bullets
	wattron(board.board_win,COLOR_PAIR(1)); //color
	mvwprintw(board.board_win,27,91,"Explode Bullets: ");
	wattroff(board.board_win,COLOR_PAIR(1)); //color

	wattron(board.board_win,COLOR_PAIR(2)); //color
	mvwprintw(board.board_win,27,107,"%d",player.getExplo_Bullets().getQnt());
	wattroff(board.board_win,COLOR_PAIR(2)); //color
}

void Game::displayBullets(){
	wattron(board.board_win,COLOR_PAIR(1)); //color
	mvwprintw(board.board_win,25,30,"Number of Bullets: ");
	wattroff(board.board_win,COLOR_PAIR(1)); //color

	wattron(board.board_win,COLOR_PAIR(2)); //color
	mvwprintw(board.board_win,25,48,"%d",player.getBullets().getQnt());
	if(player.getBullets().getQnt()<100) mvwprintw(board.board_win,25,50," ");
	if(player.getBullets().getQnt()<10) mvwprintw(board.board_win,25,49," ");
	wattroff(board.board_win,COLOR_PAIR(2)); //color
}

void Game::displayPoints(){
	wattron(board.board_win,COLOR_PAIR(1)); //color
	mvwprintw(board.board_win,25,72,"Points: ");
	wattroff(board.board_win,COLOR_PAIR(1)); //color

	wattron(board.board_win,COLOR_PAIR(2)); //color
	mvwprintw(board.board_win,25,79,"%d",player.getPoints());
	wattroff(board.board_win,COLOR_PAIR(2)); //color
}

void Game::displayCoins(){ //display coins
	wattron(board.board_win,COLOR_PAIR(1)); //color
	mvwprintw(board.board_win,25,99,"Money: ");
	wattroff(board.board_win,COLOR_PAIR(1));

	wattron(board.board_win,COLOR_PAIR(2)); //color
	mvwprintw(board.board_win,25,105,"%d",player.getCoins());
	if(player.getCoins()<100)mvwprintw(board.board_win,25,107," ");
	if(player.getCoins()<10)mvwprintw(board.board_win,25,106," ");
	wattroff(board.board_win,COLOR_PAIR(2));
}

bullt Game::deletePlayerBullets(bullt tmp){ //delete Player's bullets
	int codice = tmp->cod; //save the code of the bullet
	tmp = player.setBullet(tmp,codice); //delete bullets
	return tmp;
}

bullt Game::deletePlayerExplosiveBullets(bullt tmp){ //delete Player's bullets
	int codice = tmp->cod; //save the code of the bullet
	tmp = player.setExploBullet(tmp,codice); //delete bullets
	return tmp;
}

bullt Game::deleteEnemy6Bullets(bullt tmp,listenm6 e){ //delete Enemy6's bullets
	int codice = tmp->cod; //save the code of the bullet
	tmp = e->enemy.setBullet(tmp,codice); //delete bullets;
	return tmp;
}

bullt Game::deleteEnemy7Bullets(bullt tmp,listenm7 e){ //delete Enemy7's bullets
	int codice = tmp->cod; //save the code of the bullet
	tmp = e->enemy.setBullet(tmp,codice); //delete bullets;
	return tmp;
}

bullt Game::deleteEnemy8Bullets(bullt tmp,listenm8 e){ //delete Enemy8's bullets
	int codice = tmp->cod; //save the code of the bullet
	tmp = e->enemy.setBullet(tmp,codice); //delete bullets;
	return tmp;
}

bullt Game::deleteEnemy9Bullets(bullt tmp,listenm9 e){ //delete Enemy9's bullets
	int codice = tmp->cod; //save the code of the bullet
	tmp = e->enemy.setBullet(tmp,codice); //delete bullets;
	return tmp;
}

void Game::interaction(Enemy0 e){ //interaction between enemies and player
	if(abs(player.getx()+xMin - e.getx())<=1 && (player.gety() - e.gety())<=1 && (player.gety() - e.gety())>=0){
		player.injury(); //if you are in a neighborhood of the enemy, you lose one life

	}
}

bool Game::interactionBullet(bullt tmp){ //interaction between bullet shot by enemies and player
	if(abs(player.getx()+xMin - tmp->xB) <=1 && abs(player.gety() - tmp->yB)<=1){
		player.injury(); //if you are in a neighborhood of the bullet, you lose one life
		return true;
	}
	else return false;
}

void Game::shooting(){
	bullt tmp;
	if(time%400==0){ //slow down also the speed of bullets
		//Bullets player
		tmp = player.getBullet().blt;
		while(tmp!=NULL){ //you have to move all the bullets
			mvwaddch(board.board_win,tmp->yB,tmp->xB,' '); //delete graphically the bullet
			tmp = player.shoot(tmp);
			if(tmp->xB+xMin>(mapList->map.getDim_x()-5) || tmp->xB+xMin<5){ //check if it has reached the walls
				tmp = Game::deletePlayerBullets(tmp); //delete bullet
			}
			else if(mapList->map.isSolid(tmp->xB+xMin,tmp->yB) || mapList->map.isSolid(tmp->xB+1+xMin,tmp->yB) || mapList->map.isSolid(tmp->xB-1+xMin,tmp->yB)){ //you have had a collision with a structure (the range avoids the collision next to the wall)
				mvwaddch(board.board_win,tmp->yB,tmp->xB,' '); //delete graphically the bullet
				tmp = Game::deletePlayerBullets(tmp); //delete bullet
			}
			else if(Game::enemydeath(tmp)){
				mvwaddch(board.board_win,tmp->yB,tmp->xB,' '); //delete graphically the bullet
				tmp = Game::deletePlayerBullets(tmp); //delete bullet
			}
			else{
				mvwaddch(board.board_win,tmp->yB,tmp->xB,'*'); //draw bullet
				tmp = tmp->next;
			}
		}

		//Explosive bullets player
		tmp = player.getExploBullet().blt;
		while(tmp!=NULL){ //you have to move all the bullets
			mvwaddch(board.board_win,tmp->yB,tmp->xB,' '); //delete graphically the bullet
			tmp = player.explo_shoot(tmp);
			if(tmp->xB+xMin>(mapList->map.getDim_x()-5) || tmp->xB+xMin<5){ //check if it has reached the walls
				tmp = Game::deletePlayerExplosiveBullets(tmp); //delete bullet
			}
			else if(mapList->map.isSolid(tmp->xB+xMin,tmp->yB) || mapList->map.isSolid(tmp->xB+1+xMin,tmp->yB) || mapList->map.isSolid(tmp->xB-1+xMin,tmp->yB)){ //you have had a collision with a structure (the range avoids the collision next to the wall)
				mvwaddch(board.board_win,tmp->yB,tmp->xB,' '); //delete graphically the bullet
				tmp = Game::deletePlayerExplosiveBullets(tmp); //delete bullet
			}
			else if(Game::enemydeath2(tmp)){
				mvwaddch(board.board_win,tmp->yB,tmp->xB,' '); //delete graphically the bullet
				tmp = Game::deletePlayerExplosiveBullets(tmp); //delete bullet
			}
			else{
				mvwaddch(board.board_win,tmp->yB,tmp->xB,'*'); //draw bullet
				tmp = tmp->next;
			}
		}

		//gun enemy type6
		listenm6 cont = mapList->map.getEnemies6();
		while(cont!=NULL){ //There are more enemies type6 than one
			tmp = cont->enemy.getBullet().blt;
			while(tmp!=NULL){ //you have to move all the bullets
				mvwaddch(board.board_win,tmp->yB,tmp->xB-xMin,' '); //delete graphically the bullet
				tmp = cont->enemy.Enemyshoot(tmp); //shoot
				if(tmp->xB>(mapList->map.getDim_x()-5) || tmp->xB<5){ //check if reaches the wall
					mvwaddch(board.board_win,tmp->yB,tmp->xB-xMin,' '); //delete graphically the bullet
					tmp = deleteEnemy6Bullets(tmp,cont); //delete bullet
				}
				else if(mapList->map.isSolid(tmp->xB,tmp->yB)|| mapList->map.isSolid(tmp->xB+cont->enemy.getSign(),tmp->yB)){ //you have had a collision with a structure (the range avoids the collision next to the wall)
					mvwaddch(board.board_win,tmp->yB,tmp->xB-xMin,' '); //delete graphically the bullet
					tmp = deleteEnemy6Bullets(tmp,cont); //delete bullet
				}
				else if(Game::interactionBullet(tmp)){
					mvwaddch(board.board_win,tmp->yB,tmp->xB-xMin,' '); //delete graphically the bullet
					tmp = deleteEnemy6Bullets(tmp,cont); //delete bullet
				}
				else{
					mvwaddch(board.board_win,tmp->yB,tmp->xB-xMin,'*'); //draw bullet
					tmp = tmp->next;
				}
			}
			cont = cont->next; //change enemy
		}

		//gun enemy type7
		listenm7 cont2 = mapList->map.getEnemies7();
		while(cont2!=NULL){ //There are more enemies type7 than one
			Bullet bullet = cont2->enemy.getBullet();
			tmp = bullet.blt;
			while(tmp!=NULL){ //you have to move all the bullets
				mvwaddch(board.board_win,tmp->yB,tmp->xB-xMin,' '); //delete graphically the bullet
				tmp = cont2->enemy.Enemyshoot(tmp); //shoot
				if(tmp->xB>(mapList->map.getDim_x()-5) || tmp->xB<5){//check if it reaches the wall
					mvwaddch(board.board_win,tmp->yB,tmp->xB-xMin,' '); //delete graphically the bullet
					tmp = deleteEnemy7Bullets(tmp,cont2); //delete bullet
				}
				else if(mapList->map.isSolid(tmp->xB,tmp->yB) || mapList->map.isSolid(tmp->xB+cont2->enemy.getSign(),tmp->yB)){ //you have had a collision with a structure (the range avoids the collision next to the wall)
					mvwaddch(board.board_win,tmp->yB,tmp->xB-xMin,' '); //delete graphically the bullet
					tmp = deleteEnemy7Bullets(tmp,cont2); //delete bullet
				}
				else if(Game::interactionBullet(tmp)){
					mvwaddch(board.board_win,tmp->yB,tmp->xB-xMin,' '); //delete graphically the bullet
					tmp = deleteEnemy7Bullets(tmp,cont2); //delete bullet
				}
				else{
					mvwaddch(board.board_win,tmp->yB,tmp->xB-xMin,'*'); //draw bullet
					tmp = tmp->next;
				}
			}
			cont2 = cont2->next; //change enemy
		}

		//gun enemy type8
		listenm8 cont3 = mapList->map.getEnemies8();
		while(cont3!=NULL){ //There are more enemies type8 than one
			tmp = cont3->enemy.getBullet().blt;
			while(tmp!=NULL){ //you have to move all the bullets
				mvwaddch(board.board_win,tmp->yB,tmp->xB-xMin,' '); //delete graphically the bullet
				tmp = cont3->enemy.Enemyshoot(tmp); //shoot
				if(tmp->xB>(mapList->map.getDim_x()-5) || tmp->xB<5){ //check if it reaches the
					mvwaddch(board.board_win,tmp->yB,tmp->xB-xMin,' '); //delete graphically the bullet
					tmp = deleteEnemy8Bullets(tmp,cont3); //delete bullet
				}
				else if(mapList->map.isSolid(tmp->xB,tmp->yB) || mapList->map.isSolid(tmp->xB+cont3->enemy.getSign(),tmp->yB)){ //you have had a collision with a structure (the range avoids the collision next to the wall)
					mvwaddch(board.board_win,tmp->yB,tmp->xB-xMin,' '); //delete graphically the bullet
					tmp = deleteEnemy8Bullets(tmp,cont3); //delete bullet
				}
				else if(Game::interactionBullet(tmp)){
					mvwaddch(board.board_win,tmp->yB,tmp->xB-xMin,' '); //delete graphically the bullet
					tmp = deleteEnemy8Bullets(tmp,cont3); //delete bullet
				}
				else{
					mvwaddch(board.board_win,tmp->yB,tmp->xB-xMin,'*'); //draw bullet
					tmp = tmp->next;
				}
			}
			cont3 = cont3->next; //change enemy
		}

		//gun enemy type9
		listenm9 cont4 = mapList->map.getEnemies9();
		while(cont4!=NULL){ //There are more enemies type9 than one
			tmp = cont4->enemy.getBullet().blt;
			while(tmp!=NULL){ //you have to move all the bullets
				mvwaddch(board.board_win,tmp->yB,tmp->xB-xMin,' '); //delete graphically the bullet
				tmp = cont4->enemy.Enemyshoot(tmp); //shoot
				if(tmp->xB>(mapList->map.getDim_x()-5) || tmp->xB<5){ //check if it reaches the wall
					mvwaddch(board.board_win,tmp->yB,tmp->xB-xMin,' '); //delete graphically the bullet
					tmp = deleteEnemy9Bullets(tmp,cont4); //delete bullet
				}
				else if(mapList->map.isSolid(tmp->xB,tmp->yB)|| mapList->map.isSolid(tmp->xB+cont4->enemy.getSign(),tmp->yB)){ //you have had a collision with a structure (the range avoids the collision next to the wall)
					mvwaddch(board.board_win,tmp->yB,tmp->xB-xMin,' '); //delete graphically the bullet
					tmp = deleteEnemy9Bullets(tmp,cont4); //delete bullet
				}
				else if(Game::interactionBullet(tmp)){
					mvwaddch(board.board_win,tmp->yB,tmp->xB-xMin,' '); //delete graphically the bullet
					tmp = deleteEnemy9Bullets(tmp,cont4); //delete bullet
				}
				else{
					mvwaddch(board.board_win,tmp->yB,tmp->xB-xMin,'*'); //draw bullet
					tmp = tmp->next;
				}
			}
			cont4 = cont4->next; //change enemy
		}
	}
}


bool Game::enemydeath(bullt tmp){ //check if one bullet touch one of the enemy
	//check enemy0
	listenm0 tmp0 = mapList->map.getEnemies0();
	bool found = false;
	int codice; //variable where we can save the code of one enemy
	while(tmp0!=NULL && !found){
		if(abs(tmp->xB+xMin - tmp0->enemy.getx())<=1 && abs(tmp->yB - tmp0->enemy.gety())<=1){ //check if the bullet and the enemy are in the same place (the same approach used in interaction1)
			tmp0->enemy.injury(); //injury for the enemy
			found = true; //you have removed this bullet, so you can stop the cycle
			if(tmp0->enemy.getLife() <= 0){ //Enemy life = 0
				player.updatePoints(5); //take points
				matrix[tmp0->enemy.gety()][tmp0->enemy.getx()] = ' '; //delete graphically the enemy
				codice = tmp0->val; //save the code of the enemy
				tmp0 = mapList->map.setEnemies0(tmp0,codice); //update list
			}
			else tmp0 = tmp0->next;
		}
		else tmp0 = tmp0->next;
	}

	//check enemy1
	listenm1 tmp1 = mapList->map.getEnemies1();
	while(tmp1!=NULL && !found){
		if(abs(tmp->xB+xMin - tmp1->enemy.getx())<=1 && abs(tmp->yB - tmp1->enemy.gety())<=1){ //check if the bullet and the enemy are in the same place (the same approach used in interaction1)
			tmp1->enemy.injury(); //injury for the enemy
			found = true; //you have removed this bullet, so you can stop the cycle
			if(tmp1->enemy.getLife() <= 0){ //Enemy life = 0
				player.updatePoints(7); //take points
				matrix[tmp1->enemy.gety()][tmp1->enemy.getx()] = ' '; //delete graphically the enemy
				codice = tmp1->val; //save the code of the enemy
				tmp1 = mapList->map.setEnemies1(tmp1,codice); //update list
			}
			else tmp1 = tmp1->next;
		}
		else tmp1 = tmp1->next;
	}

	//check enemy2
	listenm2 tmp2 = mapList->map.getEnemies2();
	while(tmp2!=NULL && !found){
		if(abs(tmp->xB+xMin - tmp2->enemy.getx())<=1 && abs(tmp->yB - tmp2->enemy.gety())<=1){ //check if the bullet and the enemy are in the same place (the same approach used in interaction1)
			tmp2->enemy.injury(); //injury for the enemy
			found = true; //you have removed this bullet, so you can stop the cycle
			if(tmp2->enemy.getLife() <= 0){ //Enemy life = 0
				player.updatePoints(7); //take points
				matrix[tmp2->enemy.gety()][tmp2->enemy.getx()] = ' '; //delete graphically the enemy
				codice = tmp2->val; //save the code of the enemy
				tmp2 = mapList->map.setEnemies2(tmp2,codice); //update list
			}
			else tmp2 = tmp2->next;
		}
		else tmp2 = tmp2->next;
	}

	//check enemy3
	listenm3 tmp3 = mapList->map.getEnemies3();
	while(tmp3!=NULL && !found){
		if(abs(tmp->xB+xMin - tmp3->enemy.getx())<=1 && abs(tmp->yB - tmp3->enemy.gety())<=1){ //check if the bullet and the enemy are in the same place (the same approach used in interaction1)
			tmp3->enemy.injury(); //injury for the enemy
			found = true; //you have removed this bullet, so you can stop the cycle
			if(tmp3->enemy.getLife() <= 0){ //Enemy life = 0
				player.updatePoints(2); //take points
				matrix[tmp3->enemy.gety()][tmp3->enemy.getx()] = ' '; //delete graphically the enemy
				codice = tmp3->val; //save the code of the enemy
				tmp3 = mapList->map.setEnemies3(tmp3,codice); //update list
			}
			else tmp3 = tmp3->next;
		}
		else tmp3 = tmp3->next;
	}

	//check enemy4
	listenm4 tmp4 = mapList->map.getEnemies4();
	while(tmp4!=NULL && !found){
		if(abs(tmp->xB+xMin - tmp4->enemy.getx())<=1 && abs(tmp->yB - tmp4->enemy.gety())<=1){ //check if the bullet and the enemy are in the same place (the same approach used in interaction1)
			tmp4->enemy.injury(); //injury for the enemy
			found = true; //you have removed this bullet, so you can stop the cycle
			if(tmp4->enemy.getLife() <= 0){ //Enemy life = 0
				player.updatePoints(3); //take points
				matrix[tmp4->enemy.gety()][tmp4->enemy.getx()] = ' '; //delete graphically the enemy
				codice = tmp4->val; //save the code of the enemy
				tmp4 = mapList->map.setEnemies4(tmp4,codice); //update list
			}
			else tmp4 = tmp4->next;
		}
		else tmp4 = tmp4->next;
	}

	//check enemy5
	listenm5 tmp5 = mapList->map.getEnemies5();
	while(tmp5!=NULL && !found){
		if(abs(tmp->xB+xMin - tmp5->enemy.getx())<=1 && abs(tmp->yB - tmp5->enemy.gety())<=1){ //check if the bullet and the enemy are in the same place (the same approach used in interaction1)
			tmp5->enemy.injury(); //injury for the enemy
			found = true; //you have removed this bullet, so you can stop the cycle
			if(tmp5->enemy.getLife() <= 0){ //Enemy life = 0
				player.updatePoints(2); //take points
				matrix[tmp5->enemy.gety()][tmp5->enemy.getx()] = ' '; //delete graphically the enemy
				codice = tmp5->val; //save the code of the enemy
				tmp5 = mapList->map.setEnemies5(tmp5,codice); //update list
			}
			else tmp5 = tmp5->next;
		}
		else tmp5 = tmp5->next;
	}

	bullt temp; //we need it to raise all remaining bullets
	//check enemy6
	listenm6 tmp6 = mapList->map.getEnemies6();
	while(tmp6!=NULL && !found){
		if(abs(tmp->xB+xMin - tmp6->enemy.getx())<=1 && abs(tmp->yB - tmp6->enemy.gety())<=1){ //check if the bullet and the enemy are in the same place (the same approach used in interaction1)
			tmp6->enemy.injury(); //injury for the enemy
			found = true; //you have removed this bullet, so you can stop the cycle
			if(tmp6->enemy.getLife() <= 0){ //Enemy life = 0
				player.updatePoints(5); //take points
				matrix[tmp6->enemy.gety()][tmp6->enemy.getx()] = ' '; //delete graphically the enemy
				//delete graphically the gun
				if(tmp6->enemy.getSign()==1)matrix[tmp6->enemy.gety()][tmp6->enemy.getx()+1] = ' ';
				else matrix[tmp6->enemy.gety()][tmp6->enemy.getx()-1] = ' '; //delete graphically the enemy
				//delete all remaining bullets
				temp = tmp6->enemy.getBullet().blt;
				while(temp!=NULL){
					mvwaddch(board.board_win,temp->yB,temp->xB,' '); //delete graphically the bullet
					temp = deleteEnemy6Bullets(temp,tmp6); //delete bullet
				}
				codice = tmp6->val; //save the code of the enemy
				tmp6 = mapList->map.setEnemies6(tmp6,codice); //update list
			}
			else tmp6 = tmp6->next;
		}
		else tmp6 = tmp6->next;
	}

	//check enemy7
	listenm7 tmp7 = mapList->map.getEnemies7();
	while(tmp7!=NULL && !found){
		if(abs(tmp->xB+xMin - tmp7->enemy.getx())<=1 && abs(tmp->yB - tmp7->enemy.gety())<=1){ //check if the bullet and the enemy are in the same place (the same approach used in interaction1)
			tmp7->enemy.injury(); //injury for the enemy
			found = true; //you have removed this bullet, so you can stop the cycle
			if(tmp7->enemy.getLife() <= 0){ //Enemy life = 0
				player.updatePoints(2); //take points
				matrix[tmp7->enemy.gety()][tmp7->enemy.getx()] = ' '; //delete graphically the enemy
				//delete graphically the gun
				if(tmp7->enemy.getSign()==1)matrix[tmp7->enemy.gety()][tmp7->enemy.getx()+1] = ' ';
				else matrix[tmp7->enemy.gety()][tmp7->enemy.getx()-1] = ' ';
				//delete all remaining bullets
				temp = tmp7->enemy.getBullet().blt;
				while(temp!=NULL){
					mvwaddch(board.board_win,temp->yB,temp->xB,' '); //delete graphically the bullet
					temp = deleteEnemy7Bullets(temp,tmp7); //delete bullet
				}
				codice = tmp7->val; //save the code of the enemy
				tmp7 = mapList->map.setEnemies7(tmp7,codice); //update list
			}
			else tmp7 = tmp7->next;
		}
		else tmp7 = tmp7->next;
	}

	//check enemy8
	listenm8 tmp8 = mapList->map.getEnemies8();
	while(tmp8!=NULL && !found){
		if(abs(tmp->xB+xMin - tmp8->enemy.getx())<=1 && abs(tmp->yB - tmp8->enemy.gety())<=1){ //check if the bullet and the enemy are in the same place (the same approach used in interaction1)
			tmp8->enemy.injury(); //injury for the enemy
			found = true; //you have removed this bullet, so you can stop the cycle
			if(tmp8->enemy.getLife() <= 0){ //Enemy life = 0
				player.updatePoints(5); //take points
				matrix[tmp8->enemy.gety()][tmp8->enemy.getx()] = ' '; //delete graphically the enemy
				//delete graphically the gun
				if(tmp8->enemy.getSign()==1)matrix[tmp8->enemy.gety()][tmp8->enemy.getx()+1] = ' ';
				else matrix[tmp8->enemy.gety()][tmp8->enemy.getx()-1] = ' ';
				//delete all remaining bullets
				temp = tmp8->enemy.getBullet().blt;
				while(temp!=NULL){
					mvwaddch(board.board_win,temp->yB,temp->xB,' '); //delete graphically the bullet
					temp = deleteEnemy8Bullets(temp,tmp8); //delete bullet
				}
				codice = tmp8->val; //save the code of the enemy
				tmp8 = mapList->map.setEnemies8(tmp8,codice); //update list
			}
			else tmp8 = tmp8->next;
		}
		else tmp8 = tmp8->next;
	}

	//check enemy9
	listenm9 tmp9 = mapList->map.getEnemies9();
	while(tmp9!=NULL && !found){
		if(abs(tmp->xB+xMin - tmp9->enemy.getx())<=1 && abs(tmp->yB - tmp9->enemy.gety())<=1){ //check if the bullet and the enemy are in the same place (the same approach used in interaction1)
			tmp9->enemy.injury(); //injury for the enemy
			found = true; //you have removed this bullet, so you can stop the cycle
			if(tmp9->enemy.getLife() <= 0){ //Enemy life = 0
				player.updatePoints(7); //take points
				matrix[tmp9->enemy.gety()][tmp9->enemy.getx()] = ' '; //delete graphically the enemy
				//delete graphically the two guns
				matrix[tmp9->enemy.gety()][tmp9->enemy.getx()+1] = ' ';
				matrix[tmp9->enemy.gety()][tmp9->enemy.getx()-1] = ' ';
				//delete all remaining bullets
				temp = tmp9->enemy.getBullet().blt;
				while(temp!=NULL){
					mvwaddch(board.board_win,temp->yB,temp->xB,' '); //delete graphically the bullet
					temp = deleteEnemy9Bullets(temp,tmp9); //delete bullet
				}
				codice = tmp9->val; //save the code of the enemy
				tmp9 = mapList->map.setEnemies9(tmp9,codice); //update list
			}
			else tmp9 = tmp9->next;
		}
		else tmp9 = tmp9->next;
	}

	return found;
}

bool Game::enemydeath2(bullt tmp){ //check if one explosive bullet touch one of the enemy
	//check enemy0
	listenm0 tmp0 = mapList->map.getEnemies0();
	bool found = false;
	int codice; //variable where we can save the code of one enemy
	while(tmp0!=NULL && !found){
		if(abs(tmp->xB+xMin - tmp0->enemy.getx())<=1 && abs(tmp->yB - tmp0->enemy.gety())<=1){ //check if the bullet and the enemy are in the same place (the same approach used in interaction1)
			tmp0->enemy.setLife(0); //death for the enemy
			found = true; //you have removed this bullet, so you can stop the cycle
			player.updatePoints(5); //take points
			matrix[tmp0->enemy.gety()][tmp0->enemy.getx()] = ' '; //delete graphically the enemy
			codice = tmp0->val; //save the code of the enemy
			tmp0 = mapList->map.setEnemies0(tmp0,codice); //update list
		}
		else tmp0 = tmp0->next;
	}

	//check enemy1
	listenm1 tmp1 = mapList->map.getEnemies1();
	while(tmp1!=NULL && !found){
		if(abs(tmp->xB+xMin - tmp1->enemy.getx())<=1 && abs(tmp->yB - tmp1->enemy.gety())<=1){ //check if the bullet and the enemy are in the same place (the same approach used in interaction1)
			tmp1->enemy.setLife(0); //death for the enemy
			found = true; //you have removed this bullet, so you can stop the cycle
			player.updatePoints(7); //take points
			matrix[tmp1->enemy.gety()][tmp1->enemy.getx()] = ' '; //delete graphically the enemy
			codice = tmp1->val; //save the code of the enemy
			tmp1 = mapList->map.setEnemies1(tmp1,codice); //update list
		}
		else tmp1 = tmp1->next;
	}

	//check enemy2
	listenm2 tmp2 = mapList->map.getEnemies2();
	while(tmp2!=NULL && !found){
		if(abs(tmp->xB+xMin - tmp2->enemy.getx())<=1 && abs(tmp->yB - tmp2->enemy.gety())<=1){ //check if the bullet and the enemy are in the same place (the same approach used in interaction1)
			tmp2->enemy.setLife(0); //death for the enemy
			found = true; //you have removed this bullet, so you can stop the cycle
			player.updatePoints(7); //take points
			matrix[tmp2->enemy.gety()][tmp2->enemy.getx()] = ' '; //delete graphically the enemy
			codice = tmp2->val; //save the code of the enemy
			tmp2 = mapList->map.setEnemies2(tmp2,codice); //update list
		}
		else tmp2 = tmp2->next;
	}

	//check enemy3
	listenm3 tmp3 = mapList->map.getEnemies3();
	while(tmp3!=NULL && !found){
		if(abs(tmp->xB+xMin - tmp3->enemy.getx())<=1 && abs(tmp->yB - tmp3->enemy.gety())<=1){ //check if the bullet and the enemy are in the same place (the same approach used in interaction1)
			tmp3->enemy.setLife(0); //death for the enemy
			found = true; //you have removed this bullet, so you can stop the cycle
			player.updatePoints(2); //take points
			matrix[tmp3->enemy.gety()][tmp3->enemy.getx()] = ' '; //delete graphically the enemy
			codice = tmp3->val; //save the code of the enemy
			tmp3 = mapList->map.setEnemies3(tmp3,codice); //update list
		}
		else tmp3 = tmp3->next;
	}

	//check enemy4
	listenm4 tmp4 = mapList->map.getEnemies4();
	while(tmp4!=NULL && !found){
		if(abs(tmp->xB+xMin - tmp4->enemy.getx())<=1 && abs(tmp->yB - tmp4->enemy.gety())<=1){ //check if the bullet and the enemy are in the same place (the same approach used in interaction1)
			tmp4->enemy.setLife(0); //death for the enemy
			found = true; //you have removed this bullet, so you can stop the cycle
			player.updatePoints(3); //take points
			matrix[tmp4->enemy.gety()][tmp4->enemy.getx()] = ' '; //delete graphically the enemy
			codice = tmp4->val; //save the code of the enemy
			tmp4 = mapList->map.setEnemies4(tmp4,codice); //update list
		}
		else tmp4 = tmp4->next;
	}

	//check enemy5
	listenm5 tmp5 = mapList->map.getEnemies5();
	while(tmp5!=NULL && !found){
		if(abs(tmp->xB+xMin - tmp5->enemy.getx())<=1 && abs(tmp->yB - tmp5->enemy.gety())<=1){ //check if the bullet and the enemy are in the same place (the same approach used in interaction1)
			tmp5->enemy.setLife(0); //death for the enemy
			found = true; //you have removed this bullet, so you can stop the cycle
			player.updatePoints(2); //take points
			matrix[tmp5->enemy.gety()][tmp5->enemy.getx()] = ' '; //delete graphically the enemy
			codice = tmp5->val; //save the code of the enemy
			tmp5 = mapList->map.setEnemies5(tmp5,codice); //update list
		}
		else tmp5 = tmp5->next;
	}

	bullt temp; //we need it to raise all remaining bullets
	//check enemy6
	listenm6 tmp6 = mapList->map.getEnemies6();
	while(tmp6!=NULL && !found){
		if(abs(tmp->xB+xMin - tmp6->enemy.getx())<=1 && abs(tmp->yB - tmp6->enemy.gety())<=1){ //check if the bullet and the enemy are in the same place (the same approach used in interaction1)
			tmp6->enemy.setLife(0); //death for the enemy
			found = true; //you have removed this bullet, so you can stop the cycle
			player.updatePoints(5); //take points
			matrix[tmp6->enemy.gety()][tmp6->enemy.getx()] = ' '; //delete graphically the enemy
			//delete graphically the gun
			if(tmp6->enemy.getSign()==1)matrix[tmp6->enemy.gety()][tmp6->enemy.getx()+1] = ' ';
			else matrix[tmp6->enemy.gety()][tmp6->enemy.getx()-1] = ' '; //delete graphically the enemy
			//delete all remaining bullets
			temp = tmp6->enemy.getBullet().blt;
			while(temp!=NULL){
				mvwaddch(board.board_win,temp->yB,temp->xB,' '); //delete graphically the bullet
				temp = deleteEnemy6Bullets(temp,tmp6); //delete bullet
			}
			codice = tmp6->val; //save the code of the enemy
			tmp6 = mapList->map.setEnemies6(tmp6,codice); //update list
		}
		else tmp6 = tmp6->next;
	}

	//check enemy7
	listenm7 tmp7 = mapList->map.getEnemies7();
	while(tmp7!=NULL && !found){
		if(abs(tmp->xB+xMin - tmp7->enemy.getx())<=1 && abs(tmp->yB - tmp7->enemy.gety())<=1){ //check if the bullet and the enemy are in the same place (the same approach used in interaction1)
			tmp7->enemy.setLife(0); //death for the enemy
			found = true; //you have removed this bullet, so you can stop the cycle
			player.updatePoints(2); //take points
			matrix[tmp7->enemy.gety()][tmp7->enemy.getx()] = ' '; //delete graphically the enemy
			//delete graphically the gun
			if(tmp7->enemy.getSign()==1)matrix[tmp7->enemy.gety()][tmp7->enemy.getx()+1] = ' ';
			else matrix[tmp7->enemy.gety()][tmp7->enemy.getx()-1] = ' ';
			//delete all remaining bullets
			temp = tmp7->enemy.getBullet().blt;
			while(temp!=NULL){
				mvwaddch(board.board_win,temp->yB,temp->xB,' '); //delete graphically the bullet
				temp = deleteEnemy7Bullets(temp,tmp7); //delete bullet
			}
			codice = tmp7->val; //save the code of the enemy
			tmp7 = mapList->map.setEnemies7(tmp7,codice); //update list
		}
		else tmp7 = tmp7->next;
	}

	//check enemy8
	listenm8 tmp8 = mapList->map.getEnemies8();
	while(tmp8!=NULL && !found){
		if(abs(tmp->xB+xMin - tmp8->enemy.getx())<=1 && abs(tmp->yB - tmp8->enemy.gety())<=1){ //check if the bullet and the enemy are in the same place (the same approach used in interaction1)
			tmp8->enemy.setLife(0); //death for the enemy
			found = true; //you have removed this bullet, so you can stop the cycle
			player.updatePoints(5); //take points
			matrix[tmp8->enemy.gety()][tmp8->enemy.getx()] = ' '; //delete graphically the enemy
			//delete graphically the gun
			if(tmp8->enemy.getSign()==1)matrix[tmp8->enemy.gety()][tmp8->enemy.getx()+1] = ' ';
			else matrix[tmp8->enemy.gety()][tmp8->enemy.getx()-1] = ' ';
			//delete all remaining bullets
			temp = tmp8->enemy.getBullet().blt;
			while(temp!=NULL){
				mvwaddch(board.board_win,temp->yB,temp->xB,' '); //delete graphically the bullet
				temp = deleteEnemy8Bullets(temp,tmp8); //delete bullet
			}
			codice = tmp8->val; //save the code of the enemy
			tmp8 = mapList->map.setEnemies8(tmp8,codice); //update list
		}
		else tmp8 = tmp8->next;
	}

	//check enemy9
	listenm9 tmp9 = mapList->map.getEnemies9();
	while(tmp9!=NULL && !found){
		if(abs(tmp->xB+xMin - tmp9->enemy.getx())<=1 && abs(tmp->yB - tmp9->enemy.gety())<=1){ //check if the bullet and the enemy are in the same place (the same approach used in interaction1)
			tmp9->enemy.setLife(0); //death for the enemy
			found = true; //you have removed this bullet, so you can stop the cycle
			player.updatePoints(7); //take points
			matrix[tmp9->enemy.gety()][tmp9->enemy.getx()] = ' '; //delete graphically the enemy
			//delete graphically the two guns
			matrix[tmp9->enemy.gety()][tmp9->enemy.getx()+1] = ' ';
			matrix[tmp9->enemy.gety()][tmp9->enemy.getx()-1] = ' ';
			//delete all remaining bullets
			temp = tmp9->enemy.getBullet().blt;
			while(temp!=NULL){
				mvwaddch(board.board_win,temp->yB,temp->xB,' '); //delete graphically the bullet
				temp = deleteEnemy9Bullets(temp,tmp9); //delete bullet
			}
			codice = tmp9->val; //save the code of the enemy
			tmp9 = mapList->map.setEnemies9(tmp9,codice); //update list
		}
		else tmp9 = tmp9->next;
	}

	return found;
}

//Movement

int Game::directionSmartEnemy5(Enemy5 e){ //handle the direction of the smart enemy
	if(player.getx()+xMin - e.getx() > 0) return 1; //positive direction
	else if(player.getx()+xMin - e.getx() < 0) return -1; //negative direction
	else return 0;
}

int Game::directionSmartEnemy7(Enemy7 e){ //handle the direction of the smart enemy
	if(player.getx()+xMin - e.getx() > 0) return 1; //positive direction
	else if(player.getx()+xMin - e.getx() < 0) return -1; //negative direction
	else return 0;
}

int Game::directionSmartEnemy8(Enemy8 e){ //handle the direction of the smart enemy
	if(player.getx()+xMin - e.getx() > 0) return 1; //positive direction
	else if(player.getx()+xMin - e.getx() < 0) return -1; //negative direction
	else return 0;
}

void Game::mapMovement(){
	int choice;
	choice = player.getmv(); //save the movement
	if(!player.getActiveFly()){
		if(!player.getActiveJump()){ //you are not jumping
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
					if(xMin>mapList->map.getDim_x()-90) xMin--; //avoid exit
					break;
				case KEY_UP:
					if(player.getDir()==1){ //the jump depends on previous player direction
						xMin++; //increment the variable
						if(xMin>mapList->map.getDim_x()-90) xMin--; //avoid exit
					}
					else{
						xMin--; //decrement the variable
						if(xMin<0) xMin = 0; //avoid exit
					}
					break;
				case 't': //teleport
					if(player.getTeleportation().getQnt()>0){ //check if the player has teleport
						if(player.getDir()==1) //the jump depends on previous player direction
							for(int i=0;i<player.getTELEPORT_DISTANCE(player.getTeleportation().getQnt()-1);i++){
								xMin++; //increment the variable
								if(xMin>mapList->map.getDim_x()-90) xMin--; //avoid exit
							}
						else
							for(int i=0;i<player.getTELEPORT_DISTANCE(player.getTeleportation().getQnt()-1);i++){
								xMin--; //decrement the variable
								if(xMin<0) xMin = 0; //avoid exit
							}
						player.getTeleportation().setQnt(0); //delete teleports you have
					}
					break;
				default:
					break;
			}
			Game::PlayerCanMove(choice); //check if you can move
		}
		else{
			player.jump();
			if(player.getDir()==1){ //the jump depends on previous player direction
				xMin++;
				if(xMin>mapList->map.getDim_x()-90) xMin--; //avoid exit
			}
			else{
				xMin--;
				if(xMin<0) xMin = 0; //avoid exit
				}
			Game::PlayerCanMove(KEY_UP); //check if you can move (you are jumping)
			player.display();
			player.airshoot(); //if you want shoot you have to press h
		}
	}
	else{
		switch(choice){
			case KEY_LEFT:
				player.setDir(-1);  //direction of the player
				xMin--; //decrement the variable
				if(xMin<0) xMin = 0; //avoid exit
				break;
			case KEY_RIGHT:
				player.setDir(1); //direction of the player
				xMin++; //increment the variable
				if(xMin>mapList->map.getDim_x()-90) xMin--; //avoid exit
				break;
			default:
				break;
		}
		Game::PlayerCanFly(choice); //check if you can fly
	}
	if(mapList->map.isDanger(player.getx()+xMin,player.gety()+1)){//check if there are spikes
		player.injury();
	}
	PrintMap(); //map movement
	//see player
	player.display();
}

void Game::PlayerDown(){
	player.godown(); //go down
	player.display(); //see the player
	player.airshoot(); //you can shoot
}

void Game::PlayerCanFly(int choice){ //Player can or cannot fly
	switch(choice){
		case KEY_LEFT: //you went to sx
			if(strcmp(player.getGun().getName().c_str(),"None")==0){ //no gun
				if(mapList->map.isSolid(player.getx()+xMin,player.gety())){ //check it there has been collision
					xMin++; //increment the variable
					PrintMap(); //see map movement
				}
			}
			else{ //gun
				if(mapList->map.isSolid(player.getx()+xMin+player.getDir(),player.gety())){ //check it there has been collision
					xMin++; //increment the variable
					PrintMap(); //see map movement
				}
			}
			break;
		case KEY_RIGHT: //you went to dx
			if(strcmp(player.getGun().getName().c_str(),"None")==0){ //no gun
				if(mapList->map.isSolid(player.getx()+xMin,player.gety())){ //check it there has been collision
					xMin--; //increment the variable
					PrintMap(); //see map movement
				}
			}
			else{ //gun
				if(mapList->map.isSolid(player.getx()+xMin+player.getDir(),player.gety())){ //check it there has been collision
					xMin--; //increment the variable
					PrintMap(); //see map movement
				}
			}
			break;
		case KEY_UP: //you went to up
			if(mapList->map.isSolid(player.getx()+xMin,player.gety())){ //check it there has been collision
				player.godown(); //move player
			}
			break;
		case KEY_DOWN: //you went to down
			if(mapList->map.isSolid(player.getx()+xMin,player.gety())){ //check it there has been collision
				player.goup(); //move player
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
		if(strcmp(player.getGun().getName().c_str(),"None")==0){ //no gun
			if(mapList->map.isSolid(player.getx()+xMin,player.gety())){ //check it there has been collision
				xMin++; //increment the variable
				PrintMap(); //see map movement
			}
			else{
				while(!mapList->map.isSolid(player.getx()+xMin,player.gety()+1)){ //check if you have something under your feet
					Game::PlayerDown(); //go down
				}
			}
		}
		else{ //gun
			if(mapList->map.isSolid(player.getx()+xMin+player.getDir(),player.gety())){ //check it there has been collision
				xMin++; //increment the variable
				PrintMap(); // see map movement
			}
			else{
				while(!mapList->map.isSolid(player.getx()+xMin,player.gety()+1)){ //check if you have something under your feet
					Game::PlayerDown(); //go down
				}
			}
		}
		break;
	case KEY_RIGHT: //you went to dx
		if(strcmp(player.getGun().getName().c_str(),"None")==0){ //no gun
			if(mapList->map.isSolid(player.getx()+xMin,player.gety())){ //check it there has been collision
				xMin--;
				PrintMap(); //see map movement
			}
			else{
				while(!mapList->map.isSolid(player.getx()+xMin,player.gety()+1)){ //check if you have something under your feet
					Game::PlayerDown(); //go down
				}
			}
		}
		else{ //gun
			if(mapList->map.isSolid(player.getx()+xMin+player.getDir(),player.gety())){ //check it there has been collision
				xMin--;
				PrintMap(); // see map movement
			}
			else{
				while(!mapList->map.isSolid(player.getx()+xMin,player.gety()+1)){ //check if you have something under your feet
					Game::PlayerDown(); //go down
				}
			}
		}
		break;
	case KEY_UP: //you went up
		if(strcmp(player.getGun().getName().c_str(),"None")==0){ //no gun
			if(mapList->map.isSolid(player.getx()+xMin,player.gety())){ //check if you reach one piece of one structure
				if(player.getDir()==1){ //you have to go where you went(it depends on the direction)
					xMin--;
					PrintMap(); //see map movement
				}
				else{
					xMin++; //increment the variable
					PrintMap(); //see map movement
				}
				player.SetJump(); //for the next jump
				while(!mapList->map.isSolid(player.getx()+xMin,player.gety()+1)){ //check if you have something under your feet
					Game::PlayerDown(); //go down
				}
			}
			else if(mapList->map.isSolid(player.getx()+xMin,player.gety()-1) || mapList->map.isSolid(player.getx()+xMin,player.gety()+1)){ //check if you have something under your feet or over you head
				player.SetJump(); //for the next jump
				while(!mapList->map.isSolid(player.getx()+xMin,player.gety()+1)){ //check if you have something under your feet
					Game::PlayerDown(); //go down
				}
			}
			else if(player.getActiveJump() == false){
				while(!mapList->map.isSolid(player.getx()+xMin,player.gety()+1)){ //check if you have something under your feet
					Game::PlayerDown(); //go down
				}
			}
		}
		else{ //gun
			if(mapList->map.isSolid(player.getx()+xMin+player.getDir(),player.gety())){ //check if the gun reaches one piece of one structure
				if(player.getDir()==1){ //you have to go where you went(it depends on the direction)
					xMin--;
					PrintMap(); //see map movement
				}
				else{
					xMin++; //increment the variable
					PrintMap(); //see -map movement
				}
				player.SetJump(); //for the next jump
				while(!mapList->map.isSolid(player.getx()+xMin,player.gety()+1)){ //check if you have something under your feet
					Game::PlayerDown(); //go down
				}
			}
			else if(mapList->map.isSolid(player.getx()+xMin,player.gety()-1) || mapList->map.isSolid(player.getx()+xMin,player.gety()+1)){ //check if you have something under your feet or over you head
				player.SetJump(); //for the next jump
				while(!mapList->map.isSolid(player.getx()+xMin,player.gety()+1)){ //check if you have something under your feet
					Game::PlayerDown(); //go down
				}
			}
			else if(player.getActiveJump() == false){
				while(!mapList->map.isSolid(player.getx()+xMin,player.gety()+1)){ //check if you have something under your feet
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
	if(mapList->map.isSolid(h->enemy.getx(),h->enemy.gety())){ //check it there has been collision
		h->enemy.updateCoordinates(-h->enemy.getSign(),0); //you have to go from you went
		h->enemy.setSign(); //change the direction
	}
	else{
		while(!mapList->map.isSolid(h->enemy.getx(),h->enemy.gety()+1)){ //check if you have something under your feet
			h->enemy.EnemyGoDown(); //go down
		}
	}
}

void Game::Enemy1CanMove(listenm1 h){ //Enemies can or cannot move
	if(mapList->map.isSolid(h->enemy.getx(),h->enemy.gety())){ //check it there has been collision
		if(h->enemy.ReachAngles()){ //vertical collision
			h->enemy.updateCoordinates(0,-h->enemy.getUp()); //you have to go from you went
			h->enemy.setUp(); //change the vertical direction
		}
		else{ //horizontal collision
			h->enemy.updateCoordinates(-h->enemy.getSign(),0); //you have to go from you went
			h->enemy.setSign(); //change the horizontal direction
		}
	}
}

void Game::Enemy2CanMove(listenm2 h){ //Enemies can or cannot move
	if(mapList->map.isSolid(h->enemy.getx(),h->enemy.gety())){ //check if you have something under your feet or over you head
		h->enemy.updateCoordinates(0,-h->enemy.getSign()); //you have to go from you went
		h->enemy.setSign(); //change the vertical direction
	}
}

void Game::Enemy3CanMove(listenm3 h){ //Enemies can or cannot move
	if(mapList->map.isSolid(h->enemy.getx(),h->enemy.gety())){ //check if reach one piece of one structure
		h->enemy.updateCoordinates(-h->enemy.getSign(),-1); //you have to go where you went(it depends on the direction)
		h->enemy.SetJump(); //for the next jump
		while(!mapList->map.isSolid(h->enemy.getx(),h->enemy.gety()+1)){ //check if you have something under your feet
			h->enemy.EnemyGoDown(); //go down
		}
	}
	else if(mapList->map.isSolid(h->enemy.getx(),h->enemy.gety()-1) || mapList->map.isSolid(h->enemy.getx(),h->enemy.gety()+1)){ //check if you have something under your feet or over you head
		h->enemy.SetJump(); //for the next jump
		while(!mapList->map.isSolid(h->enemy.getx(),h->enemy.gety()+1)){ //check if you have something under your feet
			h->enemy.EnemyGoDown(); //go down
		}
	}
	else if(h->enemy.GetConta()==0 && !mapList->map.isSolid(h->enemy.getx(),h->enemy.gety()+1)){
		h->enemy.SetJump(); //for the next jump
		while(!mapList->map.isSolid(h->enemy.getx(),h->enemy.gety()+1)){ //check if you have something under your feet
			h->enemy.EnemyGoDown(); //go down
		}
	}
}

void Game::Enemy4CanMove(listenm4 h){ //Enemies can or cannot move
	if(mapList->map.isSolid(h->enemy.getx(),h->enemy.gety())){ //check it there has been collision
		while(mapList->map.isSolid(h->enemy.getx(),h->enemy.gety())){ //until your teleport is ok you have to change the position
			h->enemy.movement();
		}
	}
	else{
		while(!mapList->map.isSolid(h->enemy.getx(),h->enemy.gety()+1)){ //check if you have something under your feet

			h->enemy.EnemyGoDown(); //go down
		}
	}
}

void Game::Enemy5CanMove(listenm5 h){ //Enemies can or cannot move
	if(mapList->map.isSolid(h->enemy.getx(),h->enemy.gety())){ //check it there has been collision
		h->enemy.updateCoordinates(-(h->enemy.getSign()),0); //you have to go from you went
		//stay there
	}
	else{
		while(!mapList->map.isSolid(h->enemy.getx(),h->enemy.gety()+1)){ //check if you have something under your feet
			h->enemy.EnemyGoDown(); //go down
		}
	}
}

void Game::Enemy6CanMove(listenm6 h){ //Enemies can or cannot move
	if(mapList->map.isSolid(h->enemy.getx()+h->enemy.getSign(),h->enemy.gety())){ //check it there has been collision
		h->enemy.updateCoordinates(-(h->enemy.getSign()),0); //you have to go from you went
		h->enemy.setSign(); //change the direction
	}
	else{
		while(!mapList->map.isSolid(h->enemy.getx(),h->enemy.gety()+1)){ //check if you have something under your feet
			h->enemy.EnemyGoDown(); //go down
		}
	}
}

void Game::Enemy7CanMove(listenm7 h){ //Enemies can or cannot move
	if(mapList->map.isSolid(h->enemy.getx()+h->enemy.getSign(),h->enemy.gety())){ //check it there has been collision
		h->enemy.updateCoordinates(-(h->enemy.getSign()),0); //you have to go from you went
		//stay there
	}
	else{
		while(!mapList->map.isSolid(h->enemy.getx(),h->enemy.gety()+1)){ //check if you have something under your feet
			h->enemy.EnemyGoDown(); //go down
		}
	}
}

void Game::Enemy8CanMove(listenm8 h){ //Enemies can or cannot move
	while(!mapList->map.isSolid(h->enemy.getx(),h->enemy.gety()+1)){ //check if you have something under your feet
		h->enemy.EnemyGoDown(); //go down
	}
}

void Game::Enemy9CanMove(listenm9 h){ //Enemies can or cannot move
	if(mapList->map.isSolid(h->enemy.getx(),h->enemy.gety())){ //check if you have something under your feet or over you head
		h->enemy.updateCoordinates(0,-(h->enemy.getSign())); //you have to go from you went
		h->enemy.setSign(); //change the vertical direction
	}
}

void Game::enemyMovement(){	//Enemies movement
	listenm0 tmp = mapList->map.getEnemies0(); //type0
	while(tmp!=NULL){
		matrix[tmp->enemy.gety()][tmp->enemy.getx()] = ' '; //delete enemy
		tmp->enemy.movement(); //move one enemy
		Game::Enemy0CanMove(tmp); //interaction with the structure
		matrix[tmp->enemy.gety()][tmp->enemy.getx()] = tmp->enemy.getChar(); //print enemy again
		Game::interaction(tmp->enemy); //check the interaction between one enemy and the player
		tmp = tmp->next; //go to the next enemy
	}
	listenm1 tmp1 = mapList->map.getEnemies1(); //type1
	while(tmp1!=NULL){
		matrix[tmp1->enemy.gety()][tmp1->enemy.getx()] = ' '; //delete enemy
		tmp1->enemy.movement(); //move one enemy
		Game::Enemy1CanMove(tmp1); //interaction with the structure
		matrix[tmp1->enemy.gety()][tmp1->enemy.getx()] = tmp1->enemy.getChar(); //print enemy again
		Game::interaction(tmp1->enemy); //check the interaction between one enemy and the player
		tmp1 = tmp1->next; //go to the next enemy
	}

	listenm2 tmp2 = mapList->map.getEnemies2(); //type2
	while(tmp2!=NULL){
		matrix[tmp2->enemy.gety()][tmp2->enemy.getx()] = ' '; //delete enemy
		tmp2->enemy.movement(); //move one enemy
		Game::Enemy2CanMove(tmp2); //interaction with the structure
		matrix[tmp2->enemy.gety()][tmp2->enemy.getx()] = tmp2->enemy.getChar(); //print enemy again
		Game::interaction(tmp2->enemy); //check the interaction between one enemy and the player
		tmp2 = tmp2->next; //go to the next enemy
	}

	listenm3 tmp3 = mapList->map.getEnemies3(); //type3
	while(tmp3!=NULL){
		matrix[tmp3->enemy.gety()][tmp3->enemy.getx()] = ' '; //delete enemy
		tmp3->enemy.movement(); //move one enemy
		Game::Enemy3CanMove(tmp3); //interaction with the structure
		matrix[tmp3->enemy.gety()][tmp3->enemy.getx()] = tmp3->enemy.getChar(); //print enemy again
		Game::interaction(tmp3->enemy); //check the interaction between one enemy and the player
		tmp3 = tmp3->next; //go to the next enemy
	}

	listenm4 tmp4 = mapList->map.getEnemies4(); //type4
	while(tmp4!=NULL){
		matrix[tmp4->enemy.gety()][tmp4->enemy.getx()] = ' '; //delete enemy
		tmp4->enemy.movement(); //move one enemy
		Game::Enemy4CanMove(tmp4); //interaction with the structure
		matrix[tmp4->enemy.gety()][tmp4->enemy.getx()] = tmp4->enemy.getChar(); //print enemy again
		Game::interaction(tmp4->enemy); //check the interaction between one enemy and the player
		tmp4 = tmp4->next; //go to the next enemy
	}

	int dir;
	listenm5 tmp5 = mapList->map.getEnemies5(); //type5
	while(tmp5!=NULL){
		matrix[tmp5->enemy.gety()][tmp5->enemy.getx()] = ' '; //delete enemy
		dir = Game::directionSmartEnemy5(tmp5->enemy);
		if(abs(player.getx()+xMin - tmp5->enemy.getx()) <= 20){ //player is sufficiently near to enemy type5
			tmp5->enemy.movement(dir); //move one enemy
		}
		Game::Enemy5CanMove(tmp5); //interaction with the structure
		matrix[tmp5->enemy.gety()][tmp5->enemy.getx()] = tmp5->enemy.getChar(); //print enemy again
		Game::interaction(tmp5->enemy); //check the interaction between one enemy and the player
		tmp5 = tmp5->next; //go to the next enemy
	}

	listenm6 tmp6 = mapList->map.getEnemies6();  //type6
	while(tmp6!=NULL){
		matrix[tmp6->enemy.gety()][tmp6->enemy.getx()] = ' '; //delete enemy
		matrix[tmp6->enemy.gety()][tmp6->enemy.getx()+tmp6->enemy.getSign()] = ' '; //delete gun
		tmp6->enemy.movement(); //move one enemy
		Game::Enemy6CanMove(tmp6); //interaction with the structure
		matrix[tmp6->enemy.gety()][tmp6->enemy.getx()] = tmp6->enemy.getChar(); //print enemy again
		matrix[tmp6->enemy.gety()][tmp6->enemy.getx()+tmp6->enemy.getSign()] = '-'; //print gun again
		Game::interaction(tmp6->enemy);
		tmp6 = tmp6->next; //go to the next enemy
	}

	listenm7 tmp7 = mapList->map.getEnemies7();  //type7
	while(tmp7!=NULL){
		matrix[tmp7->enemy.gety()][tmp7->enemy.getx()] = ' '; //delete enemy
		matrix[tmp7->enemy.gety()][tmp7->enemy.getx()+tmp7->enemy.getSign()] = ' '; //delete gun
		dir = Game::directionSmartEnemy7(tmp7->enemy);
		if((abs(player.getx()+xMin - tmp7->enemy.getx()) <= 20) && (player.gety() == tmp7->enemy.gety())){ //player is sufficiently near to enemy type7
			tmp7->enemy.movement(dir); //move one enemy
		}
		Game::Enemy7CanMove(tmp7);
		matrix[tmp7->enemy.gety()][tmp7->enemy.getx()] = tmp7->enemy.getChar(); //print enemy again
		matrix[tmp7->enemy.gety()][tmp7->enemy.getx()+tmp7->enemy.getSign()] = '-'; //print gun again
		Game::interaction(tmp7->enemy);
		tmp7 = tmp7->next; //go to the next enemy
	}

	listenm8 tmp8 = mapList->map.getEnemies8();  //type8
	while(tmp8!=NULL){
		matrix[tmp8->enemy.gety()][tmp8->enemy.getx()] = ' '; //delete enemy
		matrix[tmp8->enemy.gety()][tmp8->enemy.getx()+tmp8->enemy.getSign()] = ' '; //delete gun
		dir = Game::directionSmartEnemy8(tmp8->enemy);
		if((abs(player.getx()+xMin - tmp8->enemy.getx()) <= 20) && (player.gety() == tmp8->enemy.gety())){ //player is sufficiently near to enemy type8
			tmp8->enemy.movement(dir); //move one enemy
		}
		Game::Enemy8CanMove(tmp8);
		matrix[tmp8->enemy.gety()][tmp8->enemy.getx()] = tmp8->enemy.getChar(); //print enemy again
		matrix[tmp8->enemy.gety()][tmp8->enemy.getx()+tmp8->enemy.getSign()] = '-'; //print gun again
		Game::interaction(tmp8->enemy);
		tmp8 = tmp8->next; //go to the next enemy
	}

	listenm9 tmp9 = mapList->map.getEnemies9();  //type9
	while(tmp9!=NULL){
		matrix[tmp9->enemy.gety()][tmp9->enemy.getx()] = ' '; //delete enemy
		matrix[tmp9->enemy.gety()][tmp9->enemy.getx()+1] = ' '; //delete gun
		matrix[tmp9->enemy.gety()][tmp9->enemy.getx()-1] = ' '; //delete gun
		tmp9->enemy.movement(); //move one enemy
		Game::Enemy9CanMove(tmp9); //interaction with the structure
		matrix[tmp9->enemy.gety()][tmp9->enemy.getx()] = tmp9->enemy.getChar(); //print enemy again
		matrix[tmp9->enemy.gety()][tmp9->enemy.getx()+1] = '-'; //print gun again
		matrix[tmp9->enemy.gety()][tmp9->enemy.getx()-1] = '-'; //print gun again
		Game::interaction(tmp9->enemy);
		tmp9 = tmp9->next; //go to the next enemy
	}

}
