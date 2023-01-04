//
// Created by LoscoX on 04/01/2023.
//

#include "data_matrix.hpp"

data_matrix::data_matrix() {
    data = nullptr;
    x = 0;
    y = 0;
    char c = ' ';
}

data_matrix::data_matrix(int x, int y, char c) {
    //assign parameters
    this->x = x;
    this->y = y;

    if (!data){ //creating data_matrix
        data = new char*[x];
        for (int i = 0; i<x; i++){
            data[i] = new char[y];
            for (int j = 0; j<y; j++){
                this->data[i][j] = c;
            }
        }
    }else{

        //deleting older data_matrix
        for (int i = 0; i<x; i++){
            delete[]data[i];
        }

        delete[] data;

        //creating data_matrix
        data = new char*[x];
        for (int i = 0; i<x; i++){
            data[i] = new char[y];
            for (int j = 0; j<y; j++){
                this->data[i][j] = c;
            }
        }

    }
}

data_matrix::~data_matrix() {
    if (data){

        //deleting data_matrix

        for (int i = 0; i<x; i++){
            delete[]data[i];
        }

        delete[] data;

        data = nullptr;
        x = 0;
        y = 0;
    }
}

int data_matrix::wide() const {
    return x;
}

int data_matrix::high() const {
    return y;
}