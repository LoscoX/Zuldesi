#include <iostream>
#include <string>
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
}

Map::Map(){

}

bool Map::isSolid(int y, int x){
    int target = (int)x/MATRIX_SIZE_X;

    seg_list_ptr tmp = segList;
    for(int i=0; i<target && tmp!=NULL; i++){
        tmp = tmp->next;
    }
    char symbol = tmp->seg.getMatrix()[x%MATRIX_SIZE_X][y];

    if(symbol != '#' && symbol != '-' && symbol != '^'){
        return false;
    }
    return true;
}

string* Map::toString(){
    string* mat;

    seg_list_ptr tmp = segList;
    mat = tmp->seg.getMatrix();
    tmp = tmp->next;

    while(tmp!=NULL){
        string* segment_str = tmp->seg.getMatrix();
        for(int i=0; i<MATRIX_SIZE_X; i++){
            mat[i] += segment_str[i];
            std::cout << segment_str[i];
        }
        tmp = tmp->next;
    }

    return mat;
}

int Map::getDim_x(){
	return dim_x;
}

int Map::getDim_y(){
	return dim_y;
}
