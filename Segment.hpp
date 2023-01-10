#include <string>

using namespace std;

/**
 * Dimension of one segment.
 */
/**
 * x of the segment
 */
const int MATRIX_SIZE_X=25;
/**
 * y of the segment
 */
const int MATRIX_SIZE_Y=25;

class Segment{
    private:
        /**
         * Matrix of segments.
         */
        string matrix[MATRIX_SIZE_X];
    public:
        Segment();
        Segment(string path);
        /**
         *
         * @return Matrix segments.
         */
        string* getMatrix();
};
