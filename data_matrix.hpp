//
// Created by LoscoX on 04/01/2023.
//

#ifndef ZULDESI_DATA_MATRIX_HPP
#define ZULDESI_DATA_MATRIX_HPP

#endif //ZULDESI_DATA_MATRIX_HPP

class data_matrix{
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
    data_matrix();

    /**
     * Class constructor
     *
     * Creates a new matrix of size x*y initialized at value c
     *
     * @param x
     * @param y
     * @param c
     */
    data_matrix(int x, int y, char c = ' ');

    /**
     * Class distructor
     *
     * Cleanup the data when deallocated
     */
    ~data_matrix();

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