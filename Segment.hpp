#include <string>

using namespace std;

//dimension of one segment
const int MATRIX_SIZE_X=25; //x of the segment
const int MATRIX_SIZE_Y=25; //y of the segment

class Segment{
    private:
        string matrix[MATRIX_SIZE_X]; //matrix of segments
    public:
        Segment();
        Segment(string path);
        string* getMatrix(); //return the matrix of segments
};
