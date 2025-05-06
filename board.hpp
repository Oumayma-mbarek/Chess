
#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <vector>
#include <string>

#include "piece.hpp"
#include "spot.hpp"
#include "couleur.hpp"


using namespace std ;




class Board {
private:
    Piece * board[8][8]; //tableau de 8x8 pointeurs vers pieces
    vector<Piece*> pieces[2]; //0=white 1=Black

public:
    // Constructeur
    Board(); 


    string to_string(int x); //transforme un entier en char : 1->'1' 

    void pose_piece(Piece* p, Spot pos);  // place une pièce dans board[x][y]. //ne fait pas la verification du deplacement
                                          //ni de la disponibilite de la position demande 
    bool deplace(Spot orig, Spot dest, Couleur turn,bool actualmove, bool checktest=false); // déplace une pièce d’une case à une autre.


    bool is_empty(Spot s); //renvoie true si la case est vide 

    Piece* get_piece(int x,int y); //renvoie la piece a la position (x,y)

    char askwhichpiecewanted();
    bool incheck(Couleur turn);
    bool willputincheck(Spot orig, Spot dest,Couleur turn);

    bool isBishopMoveBlocked(Spot orig, Spot dest);
    bool isRookMoveBlocked(Spot orig, Spot dest);
    bool isQueenMoveBlocked(Spot orig, Spot dest);
   
    // Affichage
    void display() const ;
    void canonicallyprintboard(string score);
    
    

};

#endif //BOARD_HPP