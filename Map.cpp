#include <iostream>
#include <cstring>
#include "Map.hpp"
#include "Primenumebers.hpp"

using namespace std;


Map::Map(int difficulty){

    //procedural generation
	int numSeg = 0;
    Segment seg = Segment("C:/Users/david/eclipse-workspace/Project/src/segments/Basic/segstart.txt");//fix before production
    segList = new segment_el;
    segList->id = numSeg++; //first segment (start)
    segList->next = NULL;
    segList->seg = seg;

    seg_list_ptr segtmp = segList;

    for(int i=0; i<5; i++){ //fixed number of segments
        seg_list_ptr tmp = new segment_el; //add new segment
        tmp->id = numSeg++;
        int x = rand()%82;//generate a random number between 0 and num_max of segments
        tmp->seg = Segment("C:/Users/david/eclipse-workspace/Project/src/segments/Segment_pieces/seg"+to_string(x)+".txt"); //map segments
        tmp->next = NULL;
        segtmp->next = tmp;
        segtmp = segtmp->next;
    }

	for(int i=0; i<4; i++){
        seg_list_ptr tmp = new segment_el; //add new segment
        tmp->id = numSeg++;
        tmp->seg = Segment("C:/Users/david/eclipse-workspace/Project/src/segments/Basic/segempty.txt"); //empty segments
        tmp->next = NULL;
        segtmp->next = tmp;
        segtmp = segtmp->next;
    }

	//wall at the end
	seg_list_ptr tmp = new segment_el; //add new segment
	tmp->id = numSeg++;
	tmp->seg = Segment("C:/Users/david/eclipse-workspace/Project/src/segments/Basic/segend.txt");
	tmp->next = NULL;
	segtmp->next = tmp;
	segtmp = segtmp->next;

	//Market
	for (int i=0; i<4; i++){
		seg_list_ptr tmp = new segment_el; //add new segment
		tmp->id = numSeg++;
		tmp->seg = Segment("C:/Users/david/eclipse-workspace/Project/src/segments/Market/segmarket"+to_string(i)+".txt"); //market segments
		tmp->next = NULL;
		segtmp->next = tmp;
		segtmp = segtmp->next;
	}

	//wall at the end
	tmp = new segment_el; //add new segment
	tmp->id = numSeg++;
	tmp->seg = Segment("C:/Users/david/eclipse-workspace/Project/src/segments/Basic/segend.txt");
	tmp->next = NULL;
	segtmp->next = tmp;
	segtmp = segtmp->next;

	for(int i=0; i<4; i++){
        seg_list_ptr tmp = new segment_el; //add new segment
        tmp->id = numSeg++;
        tmp->seg = Segment("C:/Users/david/eclipse-workspace/Project/src/segments/Basic/segempty.txt"); //empty segments
        tmp->next = NULL;
        segtmp->next = tmp;
        segtmp = segtmp->next;
    }


    //set variable for the segments
    dim_x = numSeg*25;
    dim_y = 25;
    trigger_start = 20; //to back to the previous map
    trigger_end = dim_x-300; //to end the map and pass to market
    trigger_market = dim_x-120; //to end market and start a new map

    //to generate coins and enemies
	int iniz_x = trigger_start+20;
	int fin_x = trigger_end-15;
	int iniz_y = 4;
	int fin_y = 21;
	gen_x = 0;gen_y = 0;

	coins = NULL; //initialize coins

	nc = 5; //number of coins

	for(int i=0;i<nc;i++){ //create coins with random position and add them to the list
		//avoid coins inside a structure
		int gen_x = iniz_x+rand()%(fin_x-iniz_x);
		int gen_y = iniz_y+rand()%(fin_y-iniz_y);
		while(isSolid(gen_x, gen_y)){
			gen_x = iniz_x+rand()%(fin_x-iniz_x);
			gen_y = iniz_y+rand()%(fin_y-iniz_y);
		}
		coins = head_insert_coin(coins,i,gen_x,gen_y);
	}

	//fall coins
	coins = FallCoins(coins);

	//Enemies
	enemies0 = NULL; //initialize the list
	enemies1 = NULL; //initialize the list
	enemies2 = NULL; //initialize the list
	enemies3 = NULL; //initialize the list
	enemies4 = NULL; //initialize the list
	enemies5 = NULL; //initialize the list
	enemies6 = NULL; //initialize the list //shoot
	enemies7 = NULL; //initialize the list
	enemies8 = NULL; //initialize the list
	enemies9 = NULL; //initialize the list

	int k = getPrime(difficulty); //handle the generation of enemies

    int* enemies_quantity = thelast10prime(k); // generate array to define quantity of enemies by type

    for (int i = 0; i<5; i++){
        int aux = enemies_quantity[9-i];
        enemies_quantity[9-i] = enemies_quantity[i];
        enemies_quantity[i] = aux;
    }

    for (int i = 0; i<9; i++){
        enemies_quantity[i] = ::rand() % enemies_quantity[i];
    }


	n0 = enemies_quantity[0]; //number of enemies of type 0
	for(int i=0;i<n0;i++){
		//avoid enemy type0 inside a structure
		generationRandom(iniz_x,iniz_y,fin_x,fin_y);
		Enemy0 e = Enemy0(gen_y, gen_x,'0',9); //create one enemy
		enemies0 = head_insert_enemy0(enemies0,e,i); //add the enemy into the list
	}


	n1 = enemies_quantity[1]; //number of enemies of type 1

	for(int i=0;i<n1;i++){
		//avoid enemy type1 inside a structure
		generationRandom(iniz_x,iniz_y,fin_x,fin_y);
		Enemy1 e = Enemy1(gen_y, gen_x,'1',9); //create one enemy
		enemies1 = head_insert_enemy1(enemies1,e,i); //add the enemy into the list
	}

	n2 = enemies_quantity[2];
	for(int i=0;i<n2;i++){
		//avoid enemy type2 inside a structure
		generationRandom(iniz_x,iniz_y,fin_x,fin_y);
		Enemy2 e = Enemy2(gen_y, gen_x,'2',15); //create one enemy
		enemies2 = head_insert_enemy2(enemies2,e,i); //add the enemy into the list
	}

	n3 = enemies_quantity[3]; //number of enemies of type 3
	for(int i=0;i<n3;i++){
		//avoid enemy type3 inside a structure
		generationRandom(iniz_x,iniz_y,fin_x,fin_y);
		Enemy3 e = Enemy3(gen_y, gen_x,'3',9); //create one enemy
		enemies3 = head_insert_enemy3(enemies3,e,i); //add the enemy into the list
	}


	n4 = enemies_quantity[4]; //number of enemies of type 4
	for(int i=0;i<n4;i++){
		//avoid enemy type4 inside a structure
		generationRandom(iniz_x,iniz_y,fin_x,fin_y);
		Enemy4 e = Enemy4(gen_y, gen_x,'4',7); //create one enemy
		enemies4 = head_insert_enemy4(enemies4,e,i); //add the enemy into the list
	}


	n5 = enemies_quantity[5]; //number of enemies of type 5
	for(int i=0;i<n5;i++){
		//avoid enemy type5 inside a structure
		generationRandom(iniz_x,iniz_y,fin_x,fin_y);
		Enemy5 e = Enemy5(gen_y, gen_x,'5',7); //create one enemy
		enemies5 = head_insert_enemy5(enemies5,e,i); //add the enemy into the list
	}


    n6 = enemies_quantity[6];
	for(int i=0;i<n6;i++){
		//avoid enemy type6 inside a structure
		generationRandom(iniz_x,iniz_y,fin_x,fin_y);
		Enemy6 e = Enemy6(gen_y, gen_x,'0',7); //create one enemy
		enemies6 = head_insert_enemy6(enemies6,e,i); //add the enemy into the list
	}


	n7= enemies_quantity[7];

	for(int i=0;i<n7;i++){
		//avoid enemy type7 inside a structure
		generationRandom(iniz_x,iniz_y,fin_x,fin_y);
		Enemy7 e = Enemy7(gen_y, gen_x,'5',7); //create one enemy
		enemies7 = head_insert_enemy7(enemies7,e,i); //add the enemy into the list
	}


    n8= enemies_quantity[8];
	for(int i=0;i<n8;i++){
		//avoid enemy type8 inside a structure
		generationRandom(iniz_x,iniz_y,fin_x,fin_y);
		Enemy8 e = Enemy8(gen_y, gen_x,'8',7); //create one enemy
		enemies8 = head_insert_enemy8(enemies8,e,i); //add the enemy into the list
	}


    n9= enemies_quantity[9];
	for(int i=0;i<n9;i++){
		//avoid enemy type9 inside a structure
		generationRandom(iniz_x,iniz_y,fin_x,fin_y);
		Enemy9 e = Enemy9(gen_y, gen_x,'2',7); //create one enemy
		enemies9 = head_insert_enemy9(enemies9,e,i); //add the enemy into the list
	}

    delete[] enemies_quantity; // delete array to clear dynamic memory
}

Map::Map(){} //deafult constructor

int Map::get_trigger_start(){
	return trigger_start;
}

int Map::get_trigger_end(){
	return trigger_end;
}

int Map::get_trigger_market(){
	return trigger_market;
}

void Map::generationRandom(int iniz_x,int iniz_y,int fin_x,int fin_y){
	gen_x = iniz_x+rand()%(fin_x-iniz_x);
	gen_y = iniz_y+rand()%(fin_y-iniz_y);
	while(isSolid(gen_x, gen_y)){
		gen_x = iniz_x+rand()%(fin_x-iniz_x);
		gen_y = iniz_y+rand()%(fin_y-iniz_y);
	}
}

bool Map::isSolid(int x, int y){ //check if the block is solid
    int target = (int)x/MATRIX_SIZE_X; //choose the right segment

    //see all segments
    seg_list_ptr tmp = segList;
    for(int i=0; i<target && tmp!=NULL; i++){
        tmp = tmp->next;
    }

    //save the symbol correspond to the given coordinates
    char symbol = tmp->seg.getMatrix()[y][x%MATRIX_SIZE_X];

    //check this symbol corresponds to a solid block
    if(symbol != '#' && symbol != '-' && symbol != '^' && symbol!= '|'){
        return false;
    }
    return true;
}

bool Map::isDanger(int x,int y){ //check if there are spikes
    int target = (int)x/MATRIX_SIZE_X; //choose the right segment

    //see all segments
    seg_list_ptr tmp = segList;
    for(int i=0; i<target && tmp!=NULL; i++){
        tmp = tmp->next;
    }

    //save the symbol correspond to the given coordinates
    char symbol = tmp->seg.getMatrix()[y][x%MATRIX_SIZE_X];

    //check this symbol corresponds to a solid block
    if(symbol != '^'){
        return false;
    }
    return true;
}

string* Map::toString(){ //build matrix
    string* mat;

    seg_list_ptr tmp = segList;
    mat = tmp->seg.getMatrix();
    tmp = tmp->next;

    //create matrix
    while(tmp!=NULL){
        string* segment_str = tmp->seg.getMatrix();
        for(int i=0; i<MATRIX_SIZE_X; i++){
        	mat[i] += segment_str[i];
        }
        tmp = tmp->next;
    }

    //create money
    mony tmpc = coins;
    while(tmpc!=NULL){
    	mat[tmpc->y][tmpc->x] = '$'; //put money in the matrix
    	tmpc = tmpc->next; //change money
    }

    //create enemies
    mat = initializeEnemies(mat);

    //symbol for teleport points
	mat[22][trigger_end] = 'X';
	mat[22][trigger_start] = 'X';
	mat[22][trigger_market] = 'X';

    return mat;
}

int Map::getDim_x(){
	return dim_x;
}

int Map::getDim_y(){
	return dim_y;
}

//coins

mony Map::head_insert_coin(mony h,int val,int x,int y){
	mony tmp = new money;
	tmp->val = val;
	tmp->x = x;
	tmp->y = y;
	tmp->next = h;
	return tmp;
}

bool Map::updateCoins(int x,int y){
	mony tmp = coins;
	bool found = false;
	int codice; //save cod
	while(tmp!=NULL && !found){
		if(x == tmp->x && y == tmp->y){ //if the player and the coin are in the same place, you have to remove it and delete from the list
			found = true;
			codice = tmp->val;
			tmp = removeCoins(tmp,codice); //remove coin from the list
			coins = removeCoins(coins,codice); //remove coin from the main list
		}
		else{
			tmp = tmp->next;
		}
	}
	return found;
}


mony Map::removeCoins(mony h,int cod){ //remove the coin with this cod
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

mony Map::FallCoins(mony h){ //avoid coins in the air
	mony tmp = h;
	while(tmp!=NULL){
		while(!isSolid(tmp->x,tmp->y+1)){
			tmp->y++;
		}
		tmp = tmp->next;
	}
	return h;
}


int Map::rand_segment_selection() {
    return rand()%40;

mony Map::getCoins(){
	return coins;

}

//list of function for enemies

listenm0 Map::getEnemies0(){
	return enemies0; //take list of enemies type 0
}
listenm1 Map::getEnemies1(){
	return enemies1; //take list of enemies type 1
}
listenm2 Map::getEnemies2(){
	return enemies2; //take list of enemies type 2
}
listenm3 Map::getEnemies3(){
	return enemies3; //take list of enemies type 3
}
listenm4 Map::getEnemies4(){
	return enemies4; //take list of enemies type 4
}
listenm5 Map::getEnemies5(){
	return enemies5; //take list of enemies type 5
}
listenm6 Map::getEnemies6(){
	return enemies6; //take list of enemies type 6
}
listenm7 Map::getEnemies7(){
	return enemies7; //take list of enemies type 7
}
listenm8 Map::getEnemies8(){
	return enemies8; //take list of enemies type 8
}
listenm9 Map::getEnemies9(){
	return enemies9; //take list of enemies type 9
}

listenm0 Map::setEnemies0(listenm0 tmp,int cod){ //take list of enemies type 0
	tmp = obj_remove_enemy0(tmp,cod,false); //if it is died, you have to remove from the list
	enemies0 = obj_remove_enemy0(enemies0, cod,true); //if it is died, you have to remove from the main list
	return tmp;
}
listenm1 Map::setEnemies1(listenm1 tmp,int cod){ //take list of enemies type 1
	tmp = obj_remove_enemy1(tmp,cod,false); //if it is died, you have to remove from the list
	enemies1 = obj_remove_enemy1(enemies1, cod,true); //if it is died, you have to remove from the main list
	return tmp;
}
listenm2 Map::setEnemies2(listenm2 tmp,int cod){ //take list of enemies type 2
	tmp = obj_remove_enemy2(tmp,cod,false); //if it is died, you have to remove from the list
	enemies2 = obj_remove_enemy2(enemies2, cod,true); //if it is died, you have to remove from the main list
	return tmp;
}
listenm3 Map::setEnemies3(listenm3 tmp,int cod){ //take list of enemies type 3
	tmp = obj_remove_enemy3(tmp,cod,false); //if it is died, you have to remove from the list
	enemies3 = obj_remove_enemy3(enemies3, cod,true); //if it is died, you have to remove from the main list
	return tmp;
}
listenm4 Map::setEnemies4(listenm4 tmp,int cod){ //take list of enemies type 4
	tmp = obj_remove_enemy4(tmp,cod,false); //if it is died, you have to remove from the list
	enemies4 = obj_remove_enemy4(enemies4, cod,true); //if it is died, you have to remove from the main list
	return tmp;
}
listenm5 Map::setEnemies5(listenm5 tmp,int cod){ //take list of enemies type 5
	tmp = obj_remove_enemy5(tmp,cod,false); //if it is died, you have to remove from the list
	enemies5 = obj_remove_enemy5(enemies5, cod,true); //if it is died, you have to remove from the main list
	return tmp;
}
listenm6 Map::setEnemies6(listenm6 tmp,int cod){ //take list of enemies type 6
	tmp = obj_remove_enemy6(tmp,cod,false); //if it is died, you have to remove from the list
	enemies6 = obj_remove_enemy6(enemies6, cod,true); //if it is died, you have to remove from the main list
	return tmp;
}
listenm7 Map::setEnemies7(listenm7 tmp,int cod){ //take list of enemies type 7
	tmp = obj_remove_enemy7(tmp,cod,false); //if it is died, you have to remove from the list
	enemies7 = obj_remove_enemy7(enemies7, cod,true); //if it is died, you have to remove from the main list
	return tmp;
}
listenm8 Map::setEnemies8(listenm8 tmp,int cod){ //take list of enemies type 8
	tmp = obj_remove_enemy8(tmp,cod,false); //if it is died, you have to remove from the list
	enemies8 = obj_remove_enemy8(enemies8, cod,true); //if it is died, you have to remove from the main list
	return tmp;
}
listenm9 Map::setEnemies9(listenm9 tmp,int cod){ //take list of enemies type 9
	tmp = obj_remove_enemy9(tmp,cod,false); //if it is died, you have to remove from the list
	enemies9 = obj_remove_enemy9(enemies9, cod,true); //if it is died, you have to remove from the main list
	return tmp;
}



listenm0 Map::head_insert_enemy0(listenm0 h,Enemy0 e, int val){ //add one enemy type0 to the list
	listenm0 tmp = new listenemy0;
	tmp->val = val;
	tmp->enemy = e;
	tmp->next = h;
	return tmp;
}

listenm1 Map::head_insert_enemy1(listenm1 h,Enemy1 e, int val){ //add one enemy type1 to the list
	listenm1 tmp = new listenemy1;
	tmp->val = val;
	tmp->enemy = e;
	tmp->next = h;
	return tmp;
}

listenm2 Map::head_insert_enemy2(listenm2 h,Enemy2 e, int val){ //add one enemy type2 to the list
	listenm2 tmp = new listenemy2;
	tmp->val = val;
	tmp->enemy = e;
	tmp->next = h;
	return tmp;
}

listenm3 Map::head_insert_enemy3(listenm3 h,Enemy3 e, int val){ //add one enemy type3 to the list
	listenm3 tmp = new listenemy3;
	tmp->val = val;
	tmp->enemy = e;
	tmp->next = h;
	return tmp;
}

listenm4 Map::head_insert_enemy4(listenm4 h,Enemy4 e, int val){ //add one enemy type4 to the list
	listenm4 tmp = new listenemy4;
	tmp->val = val;
	tmp->enemy = e;
	tmp->next = h;
	return tmp;
}

listenm5 Map::head_insert_enemy5(listenm5 h,Enemy5 e, int val){ //add one enemy type5 to the list
	listenm5 tmp = new listenemy5;
	tmp->val = val;
	tmp->enemy = e;
	tmp->next = h;
	return tmp;
}

listenm6 Map::head_insert_enemy6(listenm6 h,Enemy6 e, int val){ //add one enemy type6 to the list
	listenm6 tmp = new listenemy6;
	tmp->val = val;
	tmp->enemy = e;
	tmp->next = h;
	return tmp;
}

listenm7 Map::head_insert_enemy7(listenm7 h,Enemy7 e, int val){ //add one enemy type7 to the list
	listenm7 tmp = new listenemy7;
	tmp->val = val;
	tmp->enemy = e;
	tmp->next = h;
	return tmp;
}

listenm8 Map::head_insert_enemy8(listenm8 h,Enemy8 e, int val){ //add one enemy type8 to the list
	listenm8 tmp = new listenemy8;
	tmp->val = val;
	tmp->enemy = e;
	tmp->next = h;
	return tmp;
}

listenm9 Map::head_insert_enemy9(listenm9 h,Enemy9 e, int val){ //add one enemy type9 to the list
	listenm9 tmp = new listenemy9;
	tmp->val = val;
	tmp->enemy = e;
	tmp->next = h;
	return tmp;
}

listenm0 Map::obj_remove_enemy0(listenm0 h,int cod,bool head){ //remove the enemy type0 with this cod
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

listenm1 Map::obj_remove_enemy1(listenm1 h,int cod,bool head){ //remove the enemy type1 with this cod
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

listenm2 Map::obj_remove_enemy2(listenm2 h,int cod,bool head){ //remove the enemy type2 with this cod
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

listenm3 Map::obj_remove_enemy3(listenm3 h,int cod,bool head){ //remove the enemy type3 with this cod
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

listenm4 Map::obj_remove_enemy4(listenm4 h,int cod,bool head){ //remove the enemy type4 with this cod
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

listenm5 Map::obj_remove_enemy5(listenm5 h,int cod,bool head){ //remove the enemy type5 with this cod
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

listenm6 Map::obj_remove_enemy6(listenm6 h,int cod,bool head){ //remove the enemy type6 with this cod
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

listenm7 Map::obj_remove_enemy7(listenm7 h,int cod,bool head){ //remove the enemy type7 with this cod
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

listenm8 Map::obj_remove_enemy8(listenm8 h,int cod,bool head){ //remove the enemy type7 with this cod
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

listenm9 Map::obj_remove_enemy9(listenm9 h,int cod,bool head){ //remove the enemy type7 with this cod
	if (h==NULL) return h;
	else if(h->val == cod){ //if the enemy is in the top of the list
		if(head){ //we need because we have a problem if we delete the list and use again the element pointed by the list
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

string* Map::initializeEnemies(string* mat){
	//create enemies
	listenm0 tmp0 = enemies0;
	while(tmp0!=NULL){
		mat[tmp0->enemy.gety()][tmp0->enemy.getx()] = tmp0->enemy.getChar(); //put enemy type0 in the matrix
		tmp0 = tmp0->next; //change enemy
	}
	listenm1 tmp1 = enemies1;
	while(tmp1!=NULL){
		mat[tmp1->enemy.gety()][tmp1->enemy.getx()] = tmp1->enemy.getChar(); //put enemy type1 in the matrix
		tmp1 = tmp1->next; //change enemy
	}
	listenm2 tmp2 = enemies2;
	while(tmp2!=NULL){
		mat[tmp2->enemy.gety()][tmp2->enemy.getx()] = tmp2->enemy.getChar(); //put enemy type2 in the matrix
		tmp2 = tmp2->next; //change enemy
	}
	listenm3 tmp3 = enemies3;
	while(tmp3!=NULL){

		mat[tmp3->enemy.gety()][tmp3->enemy.getx()] = tmp3->enemy.getChar(); //put enemy type3 in the matrix
		tmp3 = tmp3->next; //change enemy
	}
	listenm4 tmp4 = enemies4;
	while(tmp4!=NULL){
		mat[tmp4->enemy.gety()][tmp4->enemy.getx()] = tmp4->enemy.getChar(); //put enemy type4 in the matrix
		tmp4 = tmp4->next; //change enemy
	}
	listenm5 tmp5 = enemies5;
	while(tmp5!=NULL){
		mat[tmp5->enemy.gety()][tmp5->enemy.getx()] = tmp5->enemy.getChar(); //put enemy type5 in the matrix
		tmp5 = tmp5->next; //change enemy
	}
	listenm6 tmp6 = enemies6;
	while(tmp6!=NULL){
		mat[tmp6->enemy.gety()][tmp6->enemy.getx()] = tmp6->enemy.getChar(); //put enemy type6 in the matrix
		mat[tmp6->enemy.gety()][tmp6->enemy.getx()+tmp6->enemy.getSign()] = '-'; //put the gun in the matrix
		tmp6 = tmp6->next; //change enemy
	}
	listenm7 tmp7 = enemies7;
	while(tmp7!=NULL){
		mat[tmp7->enemy.gety()][tmp7->enemy.getx()] = tmp7->enemy.getChar(); //put enemy type7 in the matrix
		mat[tmp7->enemy.gety()][tmp7->enemy.getx()+tmp7->enemy.getSign()] = '-'; //put the gun in the matrix
		tmp7 = tmp7->next; //change enemy
	}
	listenm8 tmp8 = enemies8;
	while(tmp8!=NULL){
		mat[tmp8->enemy.gety()][tmp8->enemy.getx()] = tmp8->enemy.getChar(); //put enemy type8 in the matrix
		mat[tmp8->enemy.gety()][tmp8->enemy.getx()+tmp8->enemy.getSign()] = '-'; //put the gun in the matrix
		tmp8 = tmp8->next; //change enemy
	}
	listenm9 tmp9 = enemies9;
	while(tmp9!=NULL){
		mat[tmp9->enemy.gety()][tmp9->enemy.getx()] = tmp9->enemy.getChar(); //put enemy type9 in the matrix
		mat[tmp9->enemy.gety()][tmp9->enemy.getx()+1] = '-'; //put the gun in the matrix
		mat[tmp9->enemy.gety()][tmp9->enemy.getx()-1] = '-'; //put the gun in the matrix
		tmp9 = tmp9->next; //change enemy
	}
	return mat;
}





void map_difficulty(){

}