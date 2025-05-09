
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
    int enpassantw[8]; /**< Array to track en passant moves for white pieces. */
    int enpassantb[8]; /**< Array to track en passant moves for black pieces. */
    int nocapture; /**< Number of moves since the last capture. */

public:
    // Constructeur
    Board(); 


    string to_string(int x); //transforme un entier en char : 1->'1' 

    void pose_piece(Piece* p, Spot pos);  // place une pièce dans board[x][y]. //ne fait pas la verification du deplacement
                                          //ni de la disponibilite de la position demande 
    bool deplace(Spot orig, Spot dest, Couleur turn,bool actualmove, bool checktest=false); // déplace une pièce d’une case à une autre.

    bool checkmate(Couleur turn);
    bool stalemate(Couleur turn);
    int getnocapture() const;
    void setnocapture(int nc);

    bool is_empty(Spot s); //renvoie true si la case est vide 

    Piece* get_piece(int x,int y); //renvoie la piece a la position (x,y)

    bool pathisclear(Spot orig, Spot dest);

    char askwhichpiecewanted();
    bool incheck(Couleur turn);
    bool willputincheck(Spot orig, Spot dest,Couleur turn);

    bool little_castle(Couleur turn);
    bool big_castle(Couleur turn);
   
    // Affichage
    void display() const ;
    void canonicallyprintboard(string score);
    
    

};

#endif //BOARD_HPP