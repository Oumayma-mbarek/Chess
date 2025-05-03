#ifndef GAME_HPP
#define GAME_HPP


#include <iostream>
#include <vector>
#include <string>

#include "player.hpp"
#include "board.hpp"

using namespace std;


class Game{
    private: 

        Board board;
        Player player1;
        Player player2;

    public:

        Game (); //default constructor 
        ~Game();

        void play(); //starts the game, handles player moves and determines outcome
        bool is_valid_input(string const & cmd);
        bool is_valid_input_short_castling(string const & cmd);
        bool is_valid_input_long_castling(string const & cmd);
        
};

#endif // GAME_HPP