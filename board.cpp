
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
    if((p_orig->get_symbole()== "\u2659" || p_orig->get_symbole()=="\u265F" )    && p_dest == nullptr){
        if(p_orig->get_color()==White){
            //mouvement diagonal vers la droite
            if (dest.get_col()== orig.get_col()+1  &&  dest.get_row()==orig.get_row()+1 ){
                return false;
            }
            //mouvement diagonal vers la gauche 
            else if(dest.get_col()== orig.get_col()-1  &&  dest.get_row()==orig.get_row()+1){
                return false;
            }
        }
        if(p_orig->get_color()==Black){
            //mouvement diagonal vers la droite
            if (dest.get_col()== orig.get_col()-1  &&  dest.get_row()==orig.get_row()-1 ){
                return false;
            }
            //mouvement diagonal vers la gauche 
            if(dest.get_col()== orig.get_col()+1  &&  dest.get_row()==orig.get_row()-1){
                return false;
            }
        }
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
        if( p_dest != nullptr){
            //gerer le fait de manger la piece 
            p_dest = nullptr;
        }
        
        board[dest.get_row()][dest.get_col()]= p_orig;
        cout << "etape 4"<< endl;
        board[orig.get_row()][orig.get_col()]=nullptr;
        cout << "etape5" << endl;
        cout << "Piece moved from " << orig.to_string() << " to " << dest.to_string() << endl;
          
        //if the moved piece is a pawn, a rook, or the king, set firstmove to false
        if ((p_orig->get_symbole() == "\u2659" || p_orig->get_symbole() == "\u265F" || p_orig->get_symbole() == "\u265C" || p_orig->get_symbole() == "\u2656" || p_orig->get_symbole() == "\u265A" ||  p_orig->get_symbole() == "\u2654")){
            p_orig->setFirstMove(false);
            cout << "first move is set to false" << endl;
        }
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


bool Board::isBishopMoveBlocked(Spot orig,Spot dest) {
    // assume we have already done the tests above
    int dirX = dest.get_row() > orig.get_row() ? 1 : -1;
    int dirY = dest.get_col() > orig.get_col() ? 1 : -1;
    for (int i=1; i < abs(dest.get_row() - orig.get_row()) - 1; ++i) {
        if (board[orig.get_row() + i*dirX][ orig.get_col() + i*dirY] !=nullptr)
        {
            return false;
        }
    }
    return true;
}


//--------------------------------------------------------------
//--------------------------------------------------------------


bool Board::isRookMoveBlocked(Spot orig, Spot dest){
    //if horizontal move
    if(dest.get_row()==dest.get_row()){
        int signe= dest.get_col()-orig.get_col()/abs( dest.get_col()-orig.get_col());
        int i=orig.get_col();
        while (board[i][dest.get_row()]==nullptr || i==dest.get_col()){
            i=i+ signe*1;                           
        }
        if (i!=dest.get_col()+1 && i!=dest.get_col()-1) return true;
        
    }

    //if vertical move
    if(dest.get_col()==dest.get_col()){
        int signe= dest.get_row()-orig.get_row()/abs( dest.get_row()-orig.get_row());
        int i=orig.get_row();
        while (board[dest.get_col()][i]==nullptr || i==dest.get_row()){
            i=i+ signe*1;                           
        }
        if (i!=dest.get_row()+1 && i!=dest.get_row()-1) return true;
        
    }

    return false;

}

bool Board::isQueenMoveBlocked(Spot orig, Spot dest){
    if(isRookMoveBlocked(orig,dest) || isBishopMoveBlocked(orig,dest)) return true;
    return false;
}