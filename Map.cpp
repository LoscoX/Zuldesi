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

    for(int i=1; i<=difficulty; i++){
        seg_list_ptr tmp = new segment_el; //add new segment
        tmp->id = i;
        tmp->seg = Segment("C:/Users/david/eclipse-workspace/Project/src/segments/seg"+to_string(i)+".txt");
        tmp->next = NULL;
        segtmp->next = tmp;
        segtmp = segtmp->next;
    }

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

}

Map::Map(){
}

bool Map::isSolid(int x, int y){
    int target = (int)x/MATRIX_SIZE_X;

    seg_list_ptr tmp = segList;
    for(int i=0; i<target && tmp!=NULL; i++){
        tmp = tmp->next;
    }

    char symbol = tmp->seg.getMatrix()[y][x%MATRIX_SIZE_X];

    if(symbol != '#' && symbol != '-' && symbol != '^' && symbol!= '|'){
        return false;
    }
    return true;
}

string* Map::toString(){ //build matrix
    string* mat;

    seg_list_ptr tmp = segList;
    mat = tmp->seg.getMatrix();
    tmp = tmp->next;

    while(tmp!=NULL){
        string* segment_str = tmp->seg.getMatrix();
        for(int i=0; i<MATRIX_SIZE_X; i++){
        	mat[i] += segment_str[i];
            //strcat(mat[i].c_str(),segment_str[i].c_str());
        }
        tmp = tmp->next;
    }

    //create money
    mony tmp2 = coins;
    while(tmp2!=NULL){
    	mat[tmp2->y][tmp2->x] = '$';
    	tmp2 = tmp2->next;
    }


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
			//player.updateCash(1); //update wallet //da spostare
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

