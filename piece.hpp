#ifndef PIECE_HPP
#define PIECE_HPP

#include <iostream> 
#include <vector>
#include <string>

#include "couleur.hpp"
#include "spot.hpp"

/**
 * @brief this class represents the pieces of the game 
 */

class Piece{
    protected: 
        Couleur couleur; /**< the colour of the piece */
        string symbole;  /**< The name of the piece (represented by its emoji). */
        int id; /**< a unique identifier for the piece  */
        Spot pos; /**<the position of the piece on the chess board */ 
        bool firstmove; /**< Indicates whether the piece has moved yet (only useful for the king, the rooks, and the pawns). */


    public: 
        /**
         * @brief Constructor for the Piece class.
         * @param name The name of the piece.
         * @param colour The color of the piece.
         * @param alive Indicates whether the piece is alive (default is true).
         * @param firstmove Indicates whether the piece has moved yet (default is true).
         */
        Piece(Couleur C,string sym, int i ,Spot s,bool firstmove=true);

        /**
         * @brief setter of the postion of a piece
         * 
         * @param s the new position of the piece
         */
        void set_pos(Spot s); //permet de changer la position d'une piece( aucune influence sur le board) 
        
        /**
         * @brief getter of the position of the piece
         * 
         * @return the current position of the piece
         */
        Spot get_pos(); //renvoie la position d'une piece 

        /**
         * @brief getter of the name of the piece
         * 
         * @return the name of the piece
         */
        string get_symbole()const;

        /**
         * @brief getter of the color of the piece
         * 
         * @return the color of the piece
         */
        Couleur get_color() const;

        /**
         * @brief getter of the identifier of the piece
         * 
         * @return the id of the piece
         */
        int get_id() const;

        /**
         * @brief getter of the firstmove attribute
         * 
         * @return firstmove attribute
         */
        bool get_firstmove() const;

        /**
         * @brief setter of the firstmove attribute
         * 
         * @param t the new value of firstmove
         */
        void setFirstMove(bool t) ;

        /**
         * @brief checks if a move is possible from origin spot to destination spot
         * 
         * @param orig the origin spot
         * 
         * @param dest the destination spot
         * 
         * @return true if the move is possible, false otherwise
         */
        virtual bool possible_move(Spot orig, Spot dest)=0  ;// true si le deplacement est valide 

        /**
         * @brief display the piece
         */
        void display();
};

/**
 * @brief represents a king piece
 */
class King : public Piece {
    public: 

        /**
         * @brief a constructor for the king pieces
         * @param c the colour of the king piece
         * @param sym the name of the king piece
         * @param i the identifier of the king piece 
         * @param s the current position of the king piece
         */
        King(Couleur c,string sym,int i, Spot s);

        /**
         * @brief check if a move from origin spot to destination spot is legal
         * @param orig the origin square where the king currently is
         * @param dest the destination square where the king want to go
         * @return true if the move is possible 
         */
        bool possible_move(Spot orig, Spot dest)  override; 
};

/**
 * @brief represents a Queen piece
 */
class Queen : public Piece {
    public:

        /**
         * @brief a constructor for the Queen 
         * @param c the colour of the Queen 
         * @param sym the name of the Queen 
         * @param i the identifier of the Queen 
         * @param s the current position of the Queen 
         */
        Queen(Couleur c,string sym,int i, Spot s);

        /**
         * @brief check if a move from origin spot to destination spot is legal
         * @param orig the origing square where the queen currently is
         * @param dest the destination spot where the queen want to go
         * @return true if the move is possible, false otherwise
         */
        bool possible_move(Spot orig, Spot dest) override;
};

/**
 * @brief represents a Pawn piece
 */
class Pawn : public Piece {
    public:

        /**
         * @brief constructor for the Pawn
         * @param c colour of the pawn
         * @param sym name of the Pawn
         * @param i identifier of the pawn
         * @param s current position of the pawn 
         */
        Pawn (Couleur c,string sym,int i, Spot s);

        /**
         * @brief check if a move from origin spot to destination spot is legal
         * @param orig the origin spot where the pawn currently is
         * @param dest the destination spot where the pawn wants to go
         * @return true if the move is possible, false otherwise
         */
        bool possible_move(Spot orig, Spot dest) override;
};

/**
 * @brief represents a Knight piece
 */
class Knight : public Piece {
    public:

        /**
         * @brief constructor of the Knight
         * @param c colour of the knight
         * @param sym name of the knight
         * @param i identifier of the knight
         * @param s current position of the knight
         */
        Knight(Couleur c,string sym,int i, Spot s);

        /**
         * @brief checks if a knight move from origin spot to destination spot is legal
         * @param orig origin spot where the knight currently is 
         * @param dest destination spot where the knight wants to go 
         * @return true if the move is legal, false otherwise
         */
        bool possible_move(Spot orig, Spot dest ) override;
};

/**
 * @brief represents a Bishop piece
 */
class Bishop : public Piece {
    public:

        /** 
         * @brief constructor of the bishop
         * @param c colour of the bishop
         * @param sym name of the bishop
         * @param i identifier of the bishoop
         * @param s current spot of the bishop
        */
        Bishop (Couleur c,string sym,int i, Spot s);

        /**
         * @brief checks if the bishop move from orig to dest is legal
         * @param orig origin spot where the bishop currently is 
         * @param dest destination spot where the bishop wants to go
         * @return true if the bishop move is legal, false otherwise
         */
        bool possible_move(Spot orig, Spot dest) override;
};

/**
 * @brief represents a Rook piece
 */
class Rook : public Piece {
    public:

        /**
         * @brief constructor for the rook
         * @param c colour of the rook
         * @param sym name of the rook
         * @param i identifier of the rook
         * @param s current position of the rook
         */
        Rook(Couleur c,string sym,int i, Spot s);

        /**
         * @brief check if the rook can go from orig to dest
         * @param orig origin spot where the rook currently is
         * @param dest destination spot where the rook attempts to go
         * @return true if the move is legal, false otherwise
         */
        bool possible_move(Spot orig,Spot dest ) override;
};


#endif // PIECE_HPP