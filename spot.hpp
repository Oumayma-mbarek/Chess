#ifndef SPOT_HPP
#define SPOT_HPP

#include <iostream> 
#include <vector>
#include <string>

#include "couleur.hpp"

using namespace std;

/**
 * @brief this class represents a squre on the chess board
 */
class Spot{
    private: 
        int x; /**< row */
        int y; /**< column */ 
    public: 

        /**
         * @brief constructor of a spot
         * @param row the corresponding row of the spot
         * @param col the corresponding column of the spot
         */
        Spot( int row, int col); 
        
        /**
         * @brief getter of the column: y attribute
         * @return column y attribute
         */
        int get_col() const ;

        /**
         * @brief getter of the row : x attribute
         * @return row x attribute
         */
        int get_row() const ; 

        /**
         * @brief setter of the y attribute
         * @param col the new value of y
         */
        void set_col(int col); 

        /**
         * @brief setter of the x attribute
         * @param row the new value of x
         */
        void set_row(int row);

        /**
         * @brief convetts position of type spot to coordinates
         * @return coordinates of the spot
         */
        string to_string(); 

        /**
         * @brief surcharge of == operator of type spot 
         */
        bool operator==(const Spot& other) const;

        /**
         * @brief checks if a spot is valid: exists on the chess board
         * @return true if a spot is valid, false otherwise
         */
        bool validspot() const;

};

#endif // SPOT_HPP