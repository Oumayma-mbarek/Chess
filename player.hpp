#ifndef PLAYER_HPP
#define PLAYER_HPP


#include <vector>
#include <iostream>
#include <string>

#include "couleur.hpp"
#include "board.hpp"

using namespace std; 

class Player{

    private: 
        string nom;
        Couleur couleur;

    public: 

        Player (string n, Couleur c);
        Couleur get_couleur() const ;
        string get_nom() const; 
        ~Player();
};

#endif // PLAYER_HPP