
#include <iostream>
#include <vector>
#include <regex>
#include <string>

#include "game.hpp"
#include "board.hpp"
#include "couleur.hpp"


using namespace std;

Game::Game() : board(Board()), player1(Player("white Player",White)), player2(Player("black Player",Black)){}

//--------------------------------------------------------------
//--------------------------------------------------------------


bool Game::is_valid_input(string const & cmd) {
    regex mouvmtpattern("[a-h][1-8][a-h][1-8]");
    cout << "valid input" << endl;
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
    
        cout << "Player " << (white_turn ? "White" : "Black") << ", enter your move: ";
        cin >> input ;
        cout << "your move is " << input << endl;;
         
        

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
        
         // Execute the move
        bool moved = false;
        if (is_valid_input(input)) {
            Spot origin( input[1] - '1',input[0] - 'a');
            Spot dest(input[3] - '1',input[2]-'a');
            moved = board.deplace(origin, dest, (white_turn ? White : Black),true);
        }   
        else if(is_valid_input_short_castling(input)){
            moved=board.little_castle(white_turn ? White : Black);
        }    
        else if(is_valid_input_long_castling(input)){
            moved=board.big_castle(white_turn ? White : Black);
        }
        if(!moved){
            cout << "invalid move" << endl;
            continue;
        }

        //check for stalemate and checkmate
        if (board.stalemate((white_turn ? Black : White))) {
            board.display();
            cout << "Game ended in stalemate. Score: 1/2 - 1/2" << endl;
            score = "1/2-1/2";
            break;
        }
        if (board.checkmate((white_turn ? Black: White))) {
            board.display();
            cout << "Player " << (white_turn ? "White" : "Black") << " wins by checkmate! Score: ";
            score = (white_turn ? "1-0" : "0-1");
            cout << score << endl;
            break;
        }
        cout << "current board"<< endl;
        board.display();
    
        // Switch to the next player
        white_turn = !white_turn;
        // Check if no captures have been done in the last 100 moves
        if (board.getnocapture() >= 100) {
            cout << "Game ended in a draw due to 100-moves rule. Score: 1/2 - 1/2" << endl;
            score = "1/2-1/2";
            break;
        }
    }
    board.canonicallyprintboard(score);
}