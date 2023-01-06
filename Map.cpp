#include <iostream>
#include <string>
#include "Map.hpp"

using namespace std;

Map::Map(int difficulty){

    //procedural generation
    Segment seg = Segment("../segments/seg0.txt");//fix before production
    segList = new segment_el;
    segList->id = 0; //first segment (start)
    segList->next = NULL;
    segList->seg = seg;

    seg_list_ptr segtmp = segList;

    for(int i=1; i<=difficulty; i++){
        seg_list_ptr tmp = new segment_el; //add new segment
        tmp->id = i;
        tmp->seg = Segment("../segments/seg"+to_string(i)+".txt");
        tmp->next = NULL;
        segtmp->next = tmp;
        segtmp = segtmp->next;
    }

}

bool Map::isSolid(int y, int x){
    int target = (int)x/MATRIX_SIZE_X;
    cout<<"target"<<target<<endl;
    seg_list_ptr tmp = segList;
    for(int i=0; i<target && tmp!=NULL; i++){
        tmp = tmp->next;
    }
    char symbol = tmp->seg.getMatrix()[x%MATRIX_SIZE_X][y];
    cout<<"symbol:"<<symbol<<endl;
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
        }
        tmp = tmp->next;
    }

    return mat;
}

/*int main(){
    Map map = Map(2);
    string* mat;
    mat = map.toString();
    for(int i=0; i<MATRIX_SIZE_X; i++){
        cout<<mat[i]<<endl;
    }
    map.isSolid(25, 1);
    return 0;
}*/