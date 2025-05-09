#ifndef PLAYER_HPP
#define PLAYER_HPP


#include <vector>
#include <iostream>
#include <string>

#include "couleur.hpp"
#include "board.hpp"

using namespace std; 

/**
 * @brief class that represents a player
 */
class Player{

    private: 
        string nom;/**< name of the player */
        Couleur couleur; /**< color of the player */

    public: 
        /**
         * @brief constructor of the player class
         * @param n name of the player
         * @param c colour of the player
         */
        Player (string n, Couleur c);

        /**
         * @brief getter of the colour of the player
         * @return colour of the player
         */
        Couleur get_couleur() const ;

        /**
         * @brief getter of the name of the player
         * @return name of the player
         */
        string get_nom() const; 
        
};

#endif // PLAYER_HPP