//
// Created by LoscoX on 04/01/2023.
//

#include "Segment.hpp"

Segment::Segment() {
    data = nullptr;
    x = 0;
    y = 0;
    char c = ' ';
}

Segment::Segment(int x, int y, char c) {
    //assign parameters
    this->x = x;
    this->y = y;

    if (!data){ //creating Segment
        data = new char*[x];
        for (int i = 0; i<x; i++){
            data[i] = new char[y];
            for (int j = 0; j<y; j++){
                this->data[i][j] = c;
            }
        }
    }else{

        //deleting older Segment
        for (int i = 0; i<x; i++){
            delete[]data[i];
        }

        delete[] data;

        //creating Segment
        data = new char*[x];
        for (int i = 0; i<x; i++){
            data[i] = new char[y];
            for (int j = 0; j<y; j++){
                this->data[i][j] = c;
            }
        }

    }
}

Segment::~Segment() {
    if (data){

        //deleting Segment

        for (int i = 0; i<x; i++){
            delete[]data[i];
        }

        delete[] data;

        data = nullptr;
        x = 0;
        y = 0;
    }
}

int Segment::wide() const {
    return x;
}

int Segment::high() const {
    return y;
}