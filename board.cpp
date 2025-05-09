
#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>

#include "board.hpp"
#include "piece.hpp"
#include "spot.hpp"
#include "couleur.hpp"

using namespace std;


//--------------------------------------------------------------
//--------------------------------------------------------------


// constructeur
Board::Board () 
{
   // allocation des pieces                  
   // Constructeur (Couleur, nom_affiché, id, case)
   //pieces[White] et pieces[Black] sont deux vectuers (piece[2]) 
    for (int row =0; row<8;row++){
        for(int col=0;col<8;col++){
            board[row][col]= nullptr; 
        }
    }



   pieces[White] = { 
        new Rook    (White,"\u2656",  0, Spot(0,0)),
        new Knight(White,"\u2658",  1, Spot(1,0)),
        new Bishop     (White,"\u2657",  2, Spot(2,0)),
        new Queen    (White,"\u2655",  3, Spot(3,0)),
        new King     (White,"\u2654",  4, Spot(4,0)),
        new Bishop     (White,"\u2657",  5, Spot(5,0)),
        new Knight(White,"\u2658",  6, Spot(6,0)),
        new Rook    (White,"\u2656",  7, Spot(7,0)) 
   };     
   pieces[Black] = {
        new Rook    (Black, "\u265C",  8, Spot(0,7)),
        new Knight(Black, "\u265E",  9, Spot(1,7)),
        new Bishop     (Black, "\u265D", 10, Spot(2,7)),
        new Queen    (Black, "\u265B", 11, Spot(3,7)),
        new King     (Black, "\u265A", 12, Spot(4,7)),
        new Bishop     (Black, "\u265D", 13, Spot(5,7)),
        new Knight(Black, "\u265E", 14, Spot(6,7)),
        new Rook    (Black, "\u265C", 15, Spot(7,7))
   };
   // alloc pawns
   for (int i=0;i<8;i++) {
    pieces[White].push_back(new Pawn(White, "\u2659", 16+i, Spot(1,i)));
    pieces[Black].push_back(new Pawn(Black,   "\u265F", 24+i, Spot(6,i)));
    }
    // Place the pieces on the board
    for(int i = 0; i < 8; i++){
        board[0][i] = pieces[0][i];
        board[1][i] = pieces[0][i + 8];
        board[6][i] = pieces[1][i + 8];
        board[7][i] = pieces[1][i];
    }

}


//--------------------------------------------------------------
//--------------------------------------------------------------

void Board::pose_piece(Piece* p, Spot s){
    int col=s.get_col();
    int row=s.get_row();
    p->get_pos().set_col(col);
    p->get_pos().set_row(row);
}

int Board::getnocapture() const {
    return nocapture;
}
void Board::setnocapture(int nc) {
    this->nocapture = nc;
}

//--------------------------------------------------------------
//--------------------------------------------------------------


void Board::display () const {
    int NBCOL=8;
    string space5 = string(5,' ');
    cout << endl;
    cout << "     a     b     c     d     e     f     g     h    "<< endl;
    cout << "  +-----+-----+-----+-----+-----+-----+-----+-----+" << endl;
    for (int i(NBCOL-1);i>=0;i--) {
            cout << i+1 << " "; // numérotation ligne dans affichage
            for (int j(0);j<NBCOL;j++) {
                    cout << "|" ;
                    if (board[i][j]) { 
                      cout << "\u0020\u0020";  //U+0020 est un esapce utf-8 taille police
                      board[i][j]->display();
                      cout << "\u0020" << " ";
                    }
                    else 
                            cout << space5;  // 2 ascii spaces
            }
            cout << "|\n  +-----+-----+-----+-----+-----+-----+-----+-----+";
            cout << endl;
    }
}




//--------------------------------------------------------------
//--------------------------------------------------------------

bool Board::is_empty(Spot s){
    if (board[s.get_row()][s.get_col()]== nullptr){
        cout << "the spot "<< s.get_row()<<s.get_col() << " is empty" << endl;
        return true;
    }
    
    return false;
}

//--------------------------------------------------------------
//--------------------------------------------------------------

Piece* Board::get_piece(int row,int col){
    return board[row][col];
}

//--------------------------------------------------------------
//--------------------------------------------------------------

char Board::askwhichpiecewanted() {
    char piecewanted;
    cout << "Other side reached ! Which piece do you want ?" << endl;
    cout << "Q. Queen" << endl;
    cout << "R. Rook" << endl;
    cout << "B. Bishop" << endl;
    cout << "N. Knight" << endl;
    cin >> piecewanted;
    while(piecewanted != 'Q' && piecewanted != 'R' && piecewanted != 'B' && piecewanted != 'N') {
        cout << "Invalid input, please enter a valid input" << endl;
        cin >> piecewanted;
    }
    return piecewanted;
}




//--------------------------------------------------------------
//--------------------------------------------------------------


bool Board::checkmate(Couleur turn){
    // Iterate over all the pieces of the player and check if a move is possible
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if (board[i][j] != nullptr && board[i][j]->get_color() == turn){
                for (int k = 0; k < 8; k++){
                    for (int l = 0; l < 8; l++){
                        if (deplace(Spot(i, j), Spot(k, l), turn, false)){
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}




//--------------------------------------------------------------
//--------------------------------------------------------------
bool Board::stalemate(Couleur turn) {
    // If no move possible and not in check : pat
    if(!incheck(turn) && checkmate(turn)){
        return true;
    }
    // If no moves possible for both players : pat
    if(checkmate(turn) && checkmate((turn == White ? Black : White))){
        return true;
    }
    return false;
}

//--------------------------------------------------------------
//--------------------------------------------------------------

bool Board::deplace(Spot orig, Spot dest,Couleur turn,bool actualmove, bool checktest){

    if(!orig.validspot() || !dest.validspot()){
        if(actualmove) cout <<" please insert a valid spot" << endl;
        return false;
    }

    Piece* p_orig= get_piece(orig.get_row(), orig.get_col());
    Piece* p_dest=get_piece(dest.get_row(), dest.get_col());

    //make sure start square has a piece inside it
    if (p_orig==nullptr){
        if(actualmove) cout << "no piece in origin square" << endl;
        return false;
    }
    if(actualmove) cout << "origin square has a piece inside" << endl;
    //make sure dest is not origin
    if(dest==orig){
        if(actualmove) cout << "you must move the piece" << endl;
        return false;
    }
    if(actualmove) cout << "dest is different from orig" << endl;
    //make sure that the player is moving his own piece 

    if(p_orig->get_color()!= turn){
        if(actualmove) cout << "choose a piece of your own" << endl;
        return false;
    }
    if(actualmove) cout << "player is moving his own piece" << endl;
    //make sure that the move is possible 
    if(p_orig->possible_move(orig,dest) == false){
        if(actualmove) cout << "Invalid move board deplace possible_move 5ra piece  " << endl;
        return false;
    }

    if(actualmove) cout << "the move is possible according to possible_move"<< endl;
    //make sure that dest is either empty or has a piece of another color
    if( p_dest != nullptr && p_orig->get_color() == p_dest->get_color() ){
        if(actualmove) cout << "destination square has a piece of your own" << endl;
        return false;
    }

    if(actualmove) cout << "destination square is empty or has a piece of another color"<< endl;
    //make sure that pawn is not capturing a piece in front of it 
    if((p_orig->get_symbole()== "\u2659" || p_orig->get_symbole()=="\u265F" )    && abs(orig.get_row() - dest.get_row()) >= 1 && orig.get_col() == dest.get_col() && p_dest != nullptr){
        if(actualmove) cout << "Pawns can't capture a piece in front of them" << endl;
        return false;
    }
    if(actualmove) cout << "Pawn is not capturing a piece in front of it "<< endl;

    //make sure that pawn moves diagonally only to caputre another piece 
    if((p_orig->get_symbole()== "\u2659" || p_orig->get_symbole()=="\u265F" )    && p_dest == nullptr &&  !(turn == White ? enpassantb[dest.get_col()] == 1 && dest.get_row() == 5 : enpassantw[dest.get_col()] == 1 && dest.get_row() == 2)){
        if(p_orig->get_color()==White){
            //mouvement diagonal vers la droite
            if (dest.get_col()== orig.get_col()+1  &&  dest.get_row()==orig.get_row()+1 ){
                if(actualmove) cout << "Pawns can only move diagonally to capture a piece" << endl;
                return false;
            }
            //mouvement diagonal vers la gauche 
            else if(dest.get_col()== orig.get_col()-1  &&  dest.get_row()==orig.get_row()+1){
                if(actualmove) cout << "Pawns can only move diagonally to capture a piece" << endl;
                return false;
            }
        }
        if(p_orig->get_color()==Black){
            //mouvement diagonal vers la droite
            if (dest.get_col()== orig.get_col()-1  &&  dest.get_row()==orig.get_row()-1 ){
                if(actualmove) cout << "Pawns can only move diagonally to capture a piece" << endl;
                return false;
            }
            //mouvement diagonal vers la gauche 
            if(dest.get_col()== orig.get_col()+1  &&  dest.get_row()==orig.get_row()-1){
                if(actualmove) cout << "Pawns can only move diagonally to capture a piece" << endl;
                return false;
            }
        }
    }
    //Check for en passant and delete the pawn that was captured 
  

   
    if(p_orig->get_symbole()=="\u2659" && orig.get_col()!= dest.get_col() && board[dest.get_row()][dest.get_col()]== nullptr){
        if(turn == White && enpassantb[dest.get_col()] == 1 && dest.get_row() == 5){
            if(actualmove){
                cout << "En passant !" << endl;
                cout << "Piece captured: " << board[dest.get_row()-1][dest.get_col()]->get_symbole() << endl;
                nocapture = 0;
                board[dest.get_row()-1][dest.get_col()] = nullptr;
                cout << "piece caputred en passant" << endl;
            }
        }
        if(turn == Black && enpassantw[dest.get_col()] == 1 && dest.get_row() == 2){
            if(actualmove){
                cout << "En passant !" << endl;
                cout << "Piece captured: " << board[dest.get_row()+1][dest.get_col()]->get_symbole() << endl;
                nocapture = 0;
                board[dest.get_row()+1][dest.get_col()] = nullptr;
                cout << "piece caputred en passant" << endl;
            }
        }
    }

    //make sure that pawn transforms if it reaches the other side 
    int i;
    string s;
    turn == White ? s= "\u2659" : s="\u265F";
    turn== White ? i=7 : i=0;
    if(p_orig->get_symbole()== s && dest.get_row()==i){
        cout <<"Pawn has reached the other side" << endl;
        char p = askwhichpiecewanted();
        switch (p){
            case 'Q':
                p_orig->set_pos(dest);
                board[orig.get_row()][orig.get_col()]=nullptr;
                board[i][dest.get_col()] = new Queen(turn, turn==White? "\u2655" :"\u265B" ,37 ,dest);
                p_orig=nullptr;
                break;
            case 'R':
                p_orig->set_pos(dest);
                board[orig.get_row()][orig.get_col()]=nullptr;
                board[i][dest.get_col()] = new Rook(turn, turn==White? "\u2656": "\u265C",38,dest);
                p_orig=nullptr;
                break;
            case 'B':
                p_orig->set_pos(dest); 
                board[orig.get_row()][orig.get_col()]=nullptr;   
                board[i][dest.get_col()] = new Bishop(turn, turn==White?  "\u2657": "\u265D",39,dest);
                p_orig=nullptr;
                break;
            case 'N':
                p_orig->set_pos(dest);
                board[orig.get_row()][orig.get_col()]=nullptr;
                board[i][dest.get_col()] = new Knight(turn,  turn==White? "\u2658": "\u265E",40,dest);
                p_orig=nullptr;
                break;
        
        }
        return true;
    }


    //check the path is clear 

    if( !pathisclear(orig,dest)){
        if(actualmove) cout << "The path is not clear" << endl;
        return false;
    }
    if (actualmove) cout << "the path is clear" << endl;
   

    // Check if the move will put the player in check (i added the chektest parameter to avoid recursion when testing check state)
    if (!checktest && willputincheck(orig, dest, turn)){
        if(actualmove) cout << "This move would put you in check" << endl;
        return false;
    }



    //place p_orig at dest  
    if(actualmove){
        p_orig->set_pos(dest);
        //if the moved piece is a pawn, a rook, or the king, set firstmove to false
        if ((p_orig->get_symbole() == "\u2659" || p_orig->get_symbole() == "\u265F" || p_orig->get_symbole() == "\u265C" || p_orig->get_symbole() == "\u2656" || p_orig->get_symbole() == "\u265A" ||  p_orig->get_symbole() == "\u2654")){
            p_orig->setFirstMove(false);
            cout << "first move is set to false" << endl;
        }
        if( p_dest != nullptr){
            //gerer le fait de manger la piece 
            p_dest = nullptr;
            nocapture=0;
        }
        else{
            nocapture ++;
        }
        
        board[dest.get_row()][dest.get_col()]= p_orig;
        cout << "etape 4"<< endl;
        board[orig.get_row()][orig.get_col()]=nullptr;
        cout << "etape5" << endl;
        cout << "Piece moved from " << orig.to_string() << " to " << dest.to_string() << endl;
    }
    // enpassant arrays update
    if(actualmove){
        for (int k = 0; k< 8; k++){
            enpassantw[k] = 0;
            enpassantb[k] = 0;
        }
    }

    // put 1 in the corresponding enpassant array if the pawn moved 2 squares forward
    if (p_orig->get_symbole() == "\u2659" && abs(orig.get_row() - dest.get_row()) == 2 && actualmove){
        enpassantw[orig.get_col()] = 1;
    }
    if (p_orig->get_symbole() == "\u265F" && abs(orig.get_row() - dest.get_row()) == 2 && actualmove){
        enpassantb[orig.get_col()] = 1;
    }
    
    return true;
    
}


//--------------------------------------------------------------
//--------------------------------------------------------------

bool Board::pathisclear(Spot orig, Spot dest){
    
    
    if (board[orig.get_row()][orig.get_col()]->get_symbole() != "\u265E" && board[orig.get_row()][orig.get_col()]->get_symbole() != "\u2658"){
        int x = orig.get_row();
        int y = orig.get_col();
        while (x != dest.get_row() || y != dest.get_col()){
            if (x < dest.get_row()){
                x++;
            }
            if (x > dest.get_row()){
                x--;
            }
            if (y < dest.get_col()){
                y++;
            }
            if (y > dest.get_col()){
                y--;
            }
            if ((x != dest.get_row() || y != dest.get_col()) && board[x][y] != nullptr){
                return false;
            }
        }
    }
    return true;

}

//--------------------------------------------------------------
//--------------------------------------------------------------







bool Board::incheck(Couleur turn){
    bool kingsposfound=false;
    Spot king_pos(0,0);
    //this iteration finds the position of the king 
    for(int row=0;row<8;row++){
        for(int col=0;col<8;col++){
            if(board[row][col] != nullptr && board[row][col]->get_symbole() == (turn == White ? "\u2654" : "\u265A")){
                king_pos.set_row(row);
                king_pos.set_col(col);
                kingsposfound=true;
            }    
        }
    }

    if (kingsposfound==false){
        cout << "king not found" << endl;
        return false;
    }  
    //Piece* King_p=board[king_pos.get_row()][king_pos.get_col()];
    cout << "king position is"<< king_pos.get_row() << king_pos.get_col() << endl;
    for(int row=0;row<8;row++){
        for(int col=0;col<8;col++){
            Piece* orig_p=board[row][col];
            Spot orig= Spot(row,col);
            if(orig_p != nullptr && orig_p->get_color()!= turn && orig_p->possible_move(orig,king_pos) && pathisclear(orig,king_pos)) {
                cout << turn << "king in check by " << orig.get_row() << orig.get_col() << endl;
                return true;
            }
        
        }
    }
    cout << "not in check" << endl;
    return false;
}


//--------------------------------------------------------------
//--------------------------------------------------------------

bool Board::willputincheck(Spot orig, Spot dest,Couleur turn){
    Piece* p_orig= get_piece(orig.get_row(), orig.get_col());
    Piece* p_dest=get_piece(dest.get_row(), dest.get_col());

    int old_row= orig.get_row();
    int old_col=orig.get_col();

    p_orig->set_pos(dest);
    board[dest.get_row()][dest.get_col()]=p_orig;
    board[orig.get_row()][orig.get_col()]=nullptr;

    cout << "starting the willputincheck "<< endl;
    bool check=incheck(turn);
    
    //undo the move
    p_orig->set_pos(Spot(old_row,old_col));
    board[old_row][old_col] = p_orig;
    board[dest.get_row()][dest.get_col()] = p_dest;

    cout << "nearly finished willputincheck" << endl;
    return check;
}


//--------------------------------------------------------------
//--------------------------------------------------------------

void Board::canonicallyprintboard(string score){
    string boardstring = "";
    // Canonical names for the pieces
    string canonicalnameswhites[6] = {"wR", "wN", "wB", "wQ", "wK", "wP"};
    string canonicalnamesblacks[6] = {"bR", "bN", "bB", "bQ", "bK", "bP"};
    // Unicode names for the pieces
    string whitenames[6] = {"\u2656", "\u2658", "\u2657", "\u2655", "\u2654", "\u2659"};
    string blacknames[6] = {"\u265C", "\u265E", "\u265D", "\u265B", "\u265A", "\u265F"};
    // Iterate over the board and add the pieces to the string
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            if (board[i][j] == nullptr){
                boardstring += ",";
            }
            else{
                for (int k = 0; k < 6; k++){
                    if (board[i][j]->get_symbole() == whitenames[k]){
                        boardstring += canonicalnameswhites[k];
                    }
                    if (board[i][j]->get_symbole() == blacknames[k]){
                        boardstring += canonicalnamesblacks[k];
                    }
                }
                boardstring += ",";
            }
        }
    }
    boardstring += " ";
    // Add the score to the string
    boardstring += score;
    cout << boardstring << endl;

}



//--------------------------------------------------------------
//--------------------------------------------------------------

bool Board::little_castle(Couleur turn){
    int i;
    turn == White ? i = 0 : i = 7;
    string sk;
    string sr;
    turn==White ? sk="\u2654" : sk="\u265A";
    turn==White ? sr="\u2656" : sr="\u265C";


    if( board[i][4]== nullptr || board[i][7]== nullptr || board[i][4]->get_symbole()!=sk || board[i][7]->get_symbole()!=sr || board[i][4]->get_firstmove()==false || board[i][7]->get_firstmove()==false){
        cout << "impossible little castle" << endl;
        return false;
    }
    if(board[i][5]!=nullptr || board[i][6]!=nullptr ) {
        cout << "path is not clear for little castle" << endl;
        return false;
    }
    if(incheck(turn)){
        cout << "little castle in check" << endl;
        return false;
    }

    Piece* p_king=board[i][4];
    Piece* p_right_rook=board[i][7];
     //Perform the move
    board[i][6] = board[i][4];
    board[i][4] = nullptr;
    board[i][5] = board[i][7];
    board[i][7] = nullptr;
 
     // Check if the player is in check in that new position
    if(incheck(turn)){
        // Player is in check, undo the move
        board[i][4] = p_king;
        board[i][7] = p_right_rook;
        board[i][6] = nullptr;
        board[i][5] = nullptr;
        return false;
    }
 
    cout << " little Castle !" << endl;
    return true;
}


//--------------------------------------------------------------
//--------------------------------------------------------------

bool Board::big_castle(Couleur turn){
    int i;
    turn == White ? i = 0 : i = 7;
    string sk;
    string sr;
    turn==White ? sk="\u2654" : sk="\u265A";
    turn==White ? sr="\u2656" : sr="\u265C";


    if( board[i][4]== nullptr || board[i][7]== nullptr || board[i][4]->get_symbole()!=sk || board[i][7]->get_symbole()!=sr || board[i][4]->get_firstmove()==false || board[i][7]->get_firstmove()==false){
        cout << "impossible big castle" << endl;
        return false;
    }
    if(board[i][1]!=nullptr || board[i][2]!=nullptr || board[i][3]!=nullptr ){
        cout << "path is not clear for big castle" << endl;
        return false;
    }
    if(incheck(turn)){
        cout << "big castle in check" << endl;
        return false;
    }

    Piece* p_king=board[i][4];
    Piece* p_left_rook=board[i][0];
    //Perform the move
    board[i][2] = board[i][4];
    board[i][4] = nullptr;
    board[i][3] = board[i][0];
    board[i][0] = nullptr;

    //Check if the player is in check
    if(incheck(turn)){
        //Player is in check, undo the move
        board[i][4] = p_king;
        board[i][0] = p_left_rook;
        board[i][2] = nullptr;
        board[i][3] = nullptr;
        return false;
    }

    cout << "Big Castle !" << endl;

    return true;
}

//--------------------------------------------------------------
//--------------------------------------------------------------

