#include <iostream>
#include <cstring>
#include "Map.hpp"

using namespace std;

Map::Map(int difficulty){

    //procedural generation
    Segment seg = Segment("C:/Users/david/eclipse-workspace/Project/src/segments/seg0.txt");//fix before production
    segList = new segment_el;
    segList->id = 0; //first segment (start)
    segList->next = NULL;
    segList->seg = seg;

    seg_list_ptr segtmp = segList;

    for(int i=1; i<difficulty; i++){
        seg_list_ptr tmp = new segment_el; //add new segment
        tmp->id = i;
        tmp->seg = Segment("C:/Users/david/eclipse-workspace/Project/src/segments/seg"+to_string(i)+".txt");
        tmp->next = NULL;
        segtmp->next = tmp;
        segtmp = segtmp->next;
    }

    //set variable for the segments
    dim_x = difficulty*25;
    dim_y = 25;
    trigger_start = 0;
    trigger_end = 0;

	coins = NULL; //initialize coins

	nc = 10; //number of coins

	for(int i=0;i<nc;i++){ //create coins with random position and add them to the list
		coins = head_insert_coin(coins,i,(2 + rand()%(dim_x-92)),(2+rand()%(dim_y-4)));
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
	enemies6 = NULL; //initialize the list
	enemies7 = NULL; //initialize the list
	enemies8 = NULL; //initialize the list
	enemies9 = NULL; //initialize the list

	int k = 4; //max number of enemies

	n0 = rand()%k; //number of enemies of type 0
	for(int i=0;i<n0;i++){
		Enemy0 e = Enemy0((2+rand()%(dim_y-4)),(2 + rand()%(dim_x-92)),'0',9,1); //create one enemy
		enemies0 = head_insert_enemy0(enemies0,e,i); //add the enemy into the list
	}

	n1 = rand()%k; //number of enemies of type 1
	for(int i=0;i<n1;i++){
		Enemy1 e = Enemy1((2+rand()%(dim_y-4)),(2 + rand()%(dim_x-92)),'1',9,2); //create one enemy
		enemies1 = head_insert_enemy1(enemies1,e,i); //add the enemy into the list
	}

	n2 = rand()%k; //number of enemies of type 2
	for(int i=0;i<n2;i++){
		Enemy2 e = Enemy2((2+rand()%(dim_y-4)),(2 + rand()%(dim_x-92)),'2',15,3); //create one enemy
		enemies2 = head_insert_enemy2(enemies2,e,i); //add the enemy into the list
	}

	n3 = rand()%k; //number of enemies of type 3
	for(int i=0;i<n3;i++){
		Enemy3 e = Enemy3((2+rand()%(dim_y-4)),(2 + rand()%(dim_x-92)),'3',9,4); //create one enemy
		enemies3 = head_insert_enemy3(enemies3,e,i); //add the enemy into the list
	}

	n4 = rand()%k; //number of enemies of type 4
	for(int i=0;i<n4;i++){
		Enemy4 e = Enemy4((2+rand()%(dim_y-4)),(2 + rand()%(dim_x-92)),'4',7,5); //create one enemy
		enemies4 = head_insert_enemy4(enemies4,e,i); //add the enemy into the list
	}

	n5 = rand()%k; //number of enemies of type 5
	for(int i=0;i<n5;i++){
		Enemy5 e = Enemy5((2+rand()%(dim_y-4)),(2 + rand()%(dim_x-92)),'5',7,6); //create one enemy
		enemies5 = head_insert_enemy5(enemies5,e,i); //add the enemy into the list
	}

	n6 = rand()%k; //number of enemies of type 6
	for(int i=0;i<n6;i++){
		Enemy6 e = Enemy6((2+rand()%(dim_y-4)),(2 + rand()%(dim_x-92)),'0',7,1); //create one enemy
		enemies6 = head_insert_enemy6(enemies6,e,i); //add the enemy into the list
	}

	n7 = rand()%k; //number of enemies of type 7
	for(int i=0;i<n7;i++){
		Enemy7 e = Enemy7((2+rand()%(dim_y-4)),(2 + rand()%(dim_x-92)),'5',7,6); //create one enemy
		enemies7 = head_insert_enemy7(enemies7,e,i); //add the enemy into the list
	}

	n8 = rand()%k; //number of enemies of type 8
	for(int i=0;i<n8;i++){
		Enemy8 e = Enemy8((2+rand()%(dim_y-4)),(2 + rand()%(dim_x-92)),'8',7,7); //create one enemy
		enemies8 = head_insert_enemy8(enemies8,e,i); //add the enemy into the list
	}

	n9 = rand()%k; //number of enemies of type 9
	for(int i=0;i<n9;i++){
		Enemy9 e = Enemy9((2+rand()%(dim_y-4)),(2 + rand()%(dim_x-92)),'2',7,3); //create one enemy
		enemies9 = head_insert_enemy9(enemies9,e,i); //add the enemy into the list
	}

}

Map::Map(){} //deafult constructor

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

    return mat;
}

int Map::getDim_x(){
	return dim_x;
}

int Map::getDim_y(){
	return dim_y;
}


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

//list of function for enemies

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


