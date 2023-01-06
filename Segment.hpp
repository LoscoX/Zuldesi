#include <string>

using namespace std;

const int MATRIX_SIZE_X=25;
const int MATRIX_SIZE_Y=25;

class Segment{
    private:
        string matrix[MATRIX_SIZE_X];
    public:
        Segment();
        Segment(string path);
        string* getMatrix();
};