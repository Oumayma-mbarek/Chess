#ifndef SPOT_HPP
#define SPOT_HPP

#include <iostream> 
#include <vector>
#include <string>

#include "couleur.hpp"

using namespace std;

class Spot{
    private: 
        int x; //colonne
        int y; //ligne 
    public: 
        Spot( int col, int row); //constructeur 
        ~Spot(); //destructeur
        int get_col() const ; //gtter qui renvoie la colonne 
        int get_row() const ; //getter qui renvoie la ligne 
        void set_col(int col); //setter qui modifie la valeur de la colonne
        void set_row(int row);
        string to_string(); // 00 ->a1 transforme une position de type Spot en coordonnees 
        bool operator==(const Spot& other) const;//surcharge de == pour spot
        bool validspot() const;

};

#endif // SPOT_HPP