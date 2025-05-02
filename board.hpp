
#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <vector>
#include <string>

#include "piece.hpp"
#include "couleur.hpp"
#include "spot.hpp"

using namespace std ;




class Board {
private:
    Piece *** board; //tableau de 8x8 pointeurs vers pieces
    vector<Piece*> pieces[2]; //0=white 1=Black

public:
    // Constructeur
    Board(); 


    void alloc_mem_echiquier(); // alloue de la memoire ; une matrice contenant type Piece* mais initialise avec des nullptr 
    string pgn_piece_name(string const name, bool view_pawn, bool view_color) const ; // transforme notation utf-8 en lettre (R/K/Q/N)
    string canonical_position() const; //renvoie position finale du jeu sous forme canonique
    string to_string(int x); //transforme un entier en char : 1->'1' 

    void pose_piece(Piece* p, Spot pos);  // place une pièce dans board[x][y]. //ne fait pas la verification du deplacement
                                          //ni de la disponibilite de la position demande 
    bool deplace(Spot orig, Spot dest, Couleur turn); // déplace une pièce d’une case à une autre.

    // Stratégies
    size_t strat_alea(Couleur c);
    size_t strat_defense(Couleur c);

    vector<Piece*> get_pieces(Couleur c) const; //renvoie toutes les pieces de couleur c 
    bool is_empty(Spot s); //renvoie true si la case est vide 

    Piece* get_piece(int x,int y); //renvoie la piece a la position (x,y)

    char askwhichpiecewanted();
    bool incheck(Couleur turn);

    bool isBishopMoveBlocked(Spot orig, Spot dest);
    bool isRookMoveBlocked(Spot orig, Spot dest);
    bool isQueenMoveBlocked(Spot orig, Spot dest);
   
    // Affichage
    void display() const ;
    void canonicallyprintboard(string score);
    
    

};

#endif