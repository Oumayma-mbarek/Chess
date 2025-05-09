
#ifndef BOARD_HPP
#define BOARD_HPP

#include <iostream>
#include <vector>
#include <string>

#include "piece.hpp"
#include "spot.hpp"
#include "couleur.hpp"


using namespace std ;


/**
 * @brief Represents a Chess board .This class stores white and black pieces as well as the chess board at each iteration.
 */

class Board {
private:
    Piece * board[8][8]; //tableau de 8x8 pointeurs vers pieces
    vector<Piece*> pieces[2]; /**< two vectors to store black and white pieces, 0=white 1=Black */
    int enpassantw[8]; /**< Array to track en passant moves for white pieces. */
    int enpassantb[8]; /**< Array to track en passant moves for black pieces. */
    int nocapture; /**< Number of moves since the last capture. */

public:
     /**
     * @brief Constructs a Board.
     */
    Board(); 

    /**
     * @brief displays the board with the pieces as emojis
     */
    void display() const ;

    /**
     * @brief prints the output of the board canonically followed by the score
     *
     *  @param score the score to display with the canonical position of the board
     */
    void canonicallyprintboard(string score);

     /**
     * @brief transform an integer to a string.
     *
     *  @param x the integer to be transformed
     */
    string to_string(int x); //transforme un entier en char : 1->'1' 

    /**
     * @brief checks if a spot on the board has a piece inside or not
     *
     *  @param s the spot to check
     * 
     * @return true if the spot is empty, false otherwise
     */
    bool is_empty(Spot s);

    /**
     * @brief searches for the piece in the spot of row x and col y
     *
     *  @param x the row 
     * 
     * @param y the column
     * 
     * @return a pointer to the piece on board[x][y] 
     */
    Piece* get_piece(int x,int y);


     /**
     * @brief puts a piece on the specified spot on the board, does not check wheather the move is legal
     *
     *  @param p a pointer to the piece to be put on the board 
     * 
     * @param pos the position on the board where to put the piece
     */
    void pose_piece(Piece* p, Spot pos); 
    
    /**
     * @brief getter of the attribute nocapture
     */
    int getnocapture() const;

    /**
     * @brief setter of the attribute nocapture
     * 
     * @param nc the new value of the nocapture attribute
     */
    void setnocapture(int nc);

    /**
     * @brief asks which piece the player wants to promote the pawn to
     *
     *  @return the caracter representing the chosen piece
     */
    char askwhichpiecewanted();

    /**
     * @brief checks if the path is clear between the origin spot and destination spot, concerns all pieces except for the knight
     * @param orig the origin spot 
     * @param dest the destination spot
     */
    bool pathisclear(Spot orig, Spot dest);

    /**
     * @brief checks if the king of the current players is in check or not
     *
     *  @param turn the color of the current player
     * 
     * @return true if the king is in check , false otherwise
     */
    bool incheck(Couleur turn);

    /**
     * @brief Checks if making a move from the origin square to the destination square puts the player in check. (based on incheck method)
     * 
     *
     *  @param origin The origin square of the move.
     * 
     * @param dest The destination square of the move.
     * 
     * @param turn The color of the player making the move.
     * 
     * @return True if the move puts the player in check, false otherwise.
     */
    bool willputincheck(Spot orig, Spot dest,Couleur turn);

    /**
     * @brief implementation of the little castle move
     * @param turn the color of the current player
     * @return true if the move is possible or false otherwise 
     */
    bool little_castle(Couleur turn);

    /**
     * @brief implementaiton of the big castle move
     *
     *  @param turn the color of the current player
     * 
     * @return true if the move is successful or false otherwise 
     */
    bool big_castle(Couleur turn);

    /**
     * @brief specifies if the current player is in checkmate. Implementation : iterates over all the pieces of the player and checks if there is a move that can be made.
     *
     *  @param turn the color of the current player
     * 
     * @return true if the player is in checkmate position, false otherwise
     */
    bool checkmate(Couleur turn);

    /**
     * @brief specifies if the current player is in stalemate. 
     *
     *  @param turn the color of the current player
     * 
     * @return true if the player is in stalemate position, false otherwise 
     */
    bool stalemate(Couleur turn);
     /**
     * @brief checks if a move from origin square to destination square is legal or not and changes the board accordingly
     *
     *  @param orig the origin spot of the piece
     * 
     * @param dest the destination spot of the piece
     * 
     * @param turn the color of the current player
     * 
     * @param actualmove a bool representing if the move is real of just for simulation
     * 
     * @param checktest Whether this move is for checking if the player is in check (to avoid recursion with willputincheck).
     * 
     * @return true if the move is legal and successful, false otherwise 
     */
    bool deplace(Spot orig, Spot dest, Couleur turn,bool actualmove, bool checktest=false); // déplace une pièce d’une case à une autre.
};

#endif //BOARD_HPP