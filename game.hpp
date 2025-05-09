#ifndef GAME_HPP
#define GAME_HPP


#include <iostream>
#include <vector>
#include <string>

#include "board.hpp"
#include "player.hpp"


using namespace std;

/**
 * @brief this class represents the game 
 * 
 * it manages the game and switching the players
 */
class Game{
    private: 

        Board board;/**<the chess board for the game*/
        Player player1;/**<the first player */
        Player player2;/**<the second player */

    public:
        /**
         * @brief Constructs a new Game object.
         * 
         * Initializes the game with an empty board.
        */
        Game (); 

        /** 
         * @brief this method starts the game and handles the turns, player moves and determines the outcome
        */
        void play();
        /**
     * @brief Checks if the input command is valid.
     * 
     * @param cmd The input command to check.
     * @return True if the command is valid, false otherwise.
     */
    bool is_valid_input(string const &cmd);

    /**
     * @brief Checks if the input command represents a valid short castling move.
     * 
     * @param cmd The input command to check.
     * @return True if the command represents a valid short castling move, false otherwise.
     */
    bool is_valid_input_short_castling(string const &cmd);

    /**
     * @brief Checks if the input command represents a valid long castling move.
     * 
     * @param cmd The input command to check.
     * @return True if the command represents a valid long castling move, false otherwise.
     */
    bool is_valid_input_long_castling(string const &cmd);
};

#endif // GAME_HPP