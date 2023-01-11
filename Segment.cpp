#include <iostream>
#include <fstream>
#include "Segment.hpp"

using namespace std;

Segment::Segment(){}

Segment::Segment(string path){ //create the segment
    ifstream src(path);
    string mat[MATRIX_SIZE_X];
    for(int i=0; i<MATRIX_SIZE_X; i++) {
        getline(src, mat[i]);
    }
    src.close();

    for (int i=0; i<MATRIX_SIZE_X; i++){
        this->matrix[i] = mat[i].c_str();
    }
}

string* Segment::getMatrix(){
    return matrix;
}
