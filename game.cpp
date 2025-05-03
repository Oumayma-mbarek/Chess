
#include <iostream>
#include <vector>
#include <regex>
#include <string>

#include "game.hpp"
#include "board.hpp"
#include "couleur.hpp"


using namespace std;

Game::Game() : board(Board()), player1(Player("white Player",White)), player2(Player("black Player",Black)){}
Game::~Game() {}

//--------------------------------------------------------------
//--------------------------------------------------------------


bool Game::is_valid_input(string const & cmd) {
    regex mouvmtpattern("[a-h][1-8][a-h][1-8]");
    return regex_match(cmd,mouvmtpattern);

}
//--------------------------------------------------------------
//--------------------------------------------------------------

bool Game::is_valid_input_short_castling(string const & cmd) {
    regex mouvmtpattern("(O|o|0)-(O|o|0)");
    return regex_match(cmd,mouvmtpattern);
}
//--------------------------------------------------------------
//--------------------------------------------------------------

bool Game::is_valid_input_long_castling(string const & cmd){
    regex mouvmtpattern("(O|o|0)-(O|o|0)-(O|o|0)");
    return regex_match(cmd,mouvmtpattern);
}

//--------------------------------------------------------------
//--------------------------------------------------------------

void Game::play(){
    string input;
    bool white_turn = true;
    string score;

    while (true) {
        // Display the board
        board.display();
        //if(board.incheck(white_turn ? Couleur::White : Couleur::Black)){
        //    cout << "Check" << endl;
        //}
        // Display the current player
        cout << "Player " << (white_turn ? "White" : "Black") << ", enter your move: ";
        cin >> input;

        // Check for special commands
        if (input == "/quit") {
            cout << "Game abandoned by " << (white_turn ? "White" : "Black") << " player. Score: ?-?" << endl;
            score = "?-?";
            break;
        } 
        else if (input == "/resign") {
            cout << "Game ended by " << (white_turn ? "White" : "Black") << " player's resignation. Score: ";
            score = (white_turn ? "0-1" : "1-0");
            cout << score << endl;
            break;
        } 
        else if (input == "/draw") {
            cout << "Game ended by mutual agreement for a draw. Score: 1/2 - 1/2" << endl;
            score = "1/2-1/2";
            break;
        } 
        else if (!is_valid_input(input) && !is_valid_input_short_castling(input) && !is_valid_input_long_castling(input)) {
            cout << "Invalid input. Please enter a valid move." << endl;
            continue;
        }

        // Switch to the next player
        white_turn = !white_turn;

        board.canonicallyprintboard(score);

    }
}