//
// Created by LoscoX on 04/01/2023.
//

#ifndef ZULDESI_Segment_HPP
#define ZULDESI_Segment_HPP

#endif //ZULDESI_Segment_HPP

class Segment{
private:

    char** data = nullptr;

    int x = 0; // number of rows
    int y = 0; // number of columns

public:

    /**
     * Class constructor
     *
     * Parameter-less class constructor
     */
    Segment();

    /**
     * Class constructor
     *
     * Creates a new matrix of size x*y initialized at value c
     *
     * @param x
     * @param y
     * @param c
     */
    Segment(int x, int y, char c = ' ');

    /**
     * Class distructor
     *
     * Cleanup the data when deallocated
     */
    ~Segment();

    /**
     * Constant Initialization
     *
     * Perform the initialization of the segment to a value c
     *
     * @param x
     * @param y
     * @param c
     */
    void init(int x, int y, char c=' ');


    /**
     *
     * @return the wide value
     */
    int wide()const;

    /**
     *
     * @return the high value
     */
    int high()const;


};