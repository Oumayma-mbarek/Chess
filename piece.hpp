#ifndef PIECE_HPP
#define PIECE_HPP

#include <iostream> 
#include <vector>
#include <string>

#include "couleur.hpp"
#include "spot.hpp"



class Piece{
    protected: 
        Couleur couleur; //couleur
        string symbole; // symbole de la piece en emoji (utf-8)
        int id; //identifiant unique
        Spot pos; //position actuelle 
        bool firstmove; /**< Indicates whether the piece has moved yet (only useful for the king, the rooks, and the pawns). */


    public: 
        Piece(Couleur C,string sym, int i ,Spot s,bool firstmove=true); //constructeur 

        void set_pos(Spot s); // permet de placer la piece a la position s 
        
        Spot get_pos(); //renvoie la position d'une piece 
        string get_symbole()const;
        Couleur get_color() const;
        bool get_firstmove() const;
        void setFirstMove(bool t) ;

        virtual bool possible_move(Spot orig, Spot dest)=0  ;// true si le deplacement est valide 

        void display();
};

class King : public Piece {
    public: 
        King(Couleur c,string sym,int i, Spot s);
        bool possible_move(Spot orig, Spot dest)  override; 
};
class Queen : public Piece {
    public:
        Queen(Couleur c,string sym,int i, Spot s);
        bool possible_move(Spot orig, Spot dest) override;
};
class Pawn : public Piece {
    public:
        Pawn (Couleur c,string sym,int i, Spot s);
        bool possible_move(Spot orig, Spot dest) override;
};
class Knight : public Piece {
    public:
        Knight(Couleur c,string sym,int i, Spot s);
        bool possible_move(Spot orig, Spot dest ) override;
};
class Bishop : public Piece {
    public:
        Bishop (Couleur c,string sym,int i, Spot s);
        bool possible_move(Spot orig, Spot dest) override;
};
class Rook : public Piece {
    public:
        Rook(Couleur c,string sym,int i, Spot s);
        bool possible_move(Spot orig,Spot dest ) override;
};


#endif // PIECE_HPP