
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






string Board::canonical_position() const {
    string output;
    for (size_t row(1); row<=8; row++){
            for (char col('a');col<='h';col++) {

                    Spot square(col,row);
                    Piece *p= board[col][row];
                    if (p != nullptr )
                            // get pieces with theit PGN names, 
                            // true -> with P for pawns, true -> w/b for colors.
                            output += pgn_piece_name( p->get_symbole(),true,true);
                    output += ",";
            }
    }
    return output;
}

//--------------------------------------------------------------
//--------------------------------------------------------------


string Board::pgn_piece_name(string const name, bool view_pawn, bool view_color) const {

    string psymb;
    if      (name=="\u2656") psymb="R";  // Rook W
    else if (name=="\u2658") psymb="N";  // Knight W
    else if (name=="\u2657") psymb="B";  // Bishop W
    else if (name=="\u2655") psymb="Q";  // Queen W
    else if (name=="\u2654") psymb="K";  // King W
    else if (name.rfind("\u2659",0)==0 && view_pawn) psymb= "P"; // Pawn W
    if (psymb.size()>0) { // one of the white piece has been found
            if (view_color)
                  return "w"+psymb;
            else
                  return psymb;
    } 
    if      (name=="\u265C") psymb= "R";  // Rook B
    else if (name=="\u265E") psymb= "N";  // Knight B
    else if (name=="\u265D") psymb= "B";  // Bishop B
    else if (name=="\u265B") psymb= "Q";  // Queen B
    else if (name=="\u265A") psymb= "K";  // King B
    else if (name.rfind("\u265F",0)==0 && view_pawn) psymb= "P"; // Pawn B
    if (psymb.size()>0) { // one of the black piece has been found
            if (view_color)
                  return "b"+psymb;
            else
                  return psymb;
    } 
    else return "";
  }



//--------------------------------------------------------------
//--------------------------------------------------------------



// constructeur
Board::Board () 
{
   //alloc_mem_echiquier();
   // allocation des pieces                  
   // Constructeur (Couleur, nom_affiché, id, case)
   //pieces[White] et pieces[Black] sont deux vectuers (piece[2]) 
    for (int col =0; col<8;col++){
        for(int row=0;row<8;row++){
            board[col][row]= nullptr; 
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
   for (size_t i=0;i<8;i++) {
       pieces[White].push_back(new Pawn(White, "\u2659" + string(i,1), 16+i, Spot(i,1)));
       pieces[Black].push_back(new Pawn(Black,   "\u265F" + string(i,1), 24+i, Spot(i,6)));
   }
   // Pose des pieces en position initiale sur l'echiquier
   for (auto p : pieces[White])
       pose_piece(p, p->get_pos());
   for (auto p : pieces[Black])
       pose_piece(p, p->get_pos());
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
                      board[i][j]-> display();
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
    if (board[s.get_col()][s.get_row()]== nullptr){
        return true;
    }
    return false;
}

//--------------------------------------------------------------
//--------------------------------------------------------------

Piece* Board::get_piece(int col,int row){
    return board[col][row];
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





bool Board::deplace(Spot orig, Spot dest,Couleur turn){

    if(!orig.validspot() || !dest.validspot()){
        cout <<" please insert a valid spot" << endl;
        return false;
    }

    Piece* p_orig= get_piece(orig.get_col(), orig.get_row());
    Piece* p_dest=get_piece(dest.get_col(), dest.get_row());

    //make sure start square has a piece inside it
    if (p_orig==nullptr){
        cout << "no piece in origin square" << endl;
        return false;
    }

    //make sure dest is not origin
    if(dest==orig){
        cout << "you must move the piece" << endl;
        return false;
    }

    //make sure that the player is moving his own piece 

    if(p_orig->get_color()!= turn){
        cout << "choose a piece of your own" << endl;
        return false;
    }
    //make sure that the move is possible 
    if(! (*p_orig).possible_move(orig,dest)){
        cout << "Invalid move" << endl;
        return false;
    }

    //make sure that dest is either empty or has a piece of another color
    if( p_dest != nullptr && (*p_orig).get_color() == (*p_dest).get_color()){
        cout << "destination square has a piece of your own" << endl;
        return false;
    }

    //check the path is clear 
    //only concerns Rook, Queen and Bishop 
    else{
        if (p_dest->get_symbole()=="Rook"){
            if(isRookMoveBlocked(orig,dest)) {
                cout << "The path is not clear" << endl;
                return false;
            }
        }

        if(p_dest->get_symbole()=="Bishop"){
            if(isBishopMoveBlocked(orig,dest)){
                cout << "The path is not clear" << endl;
                return false;
            }
        }
        if(p_dest->get_symbole()=="Queen"){
            if(isQueenMoveBlocked(orig,dest)){
                cout << "The path is not clear" << endl;
                return false;
            } 
        }



        //place p_orig at dest
        (*p_orig).set_pos(dest);
        if( p_dest != nullptr){
            //gerer le fait de manger la piece 
            p_dest = nullptr;
        }
    }
    return true;
    
}


//--------------------------------------------------------------
//--------------------------------------------------------------

bool Board::incheck(Couleur turn){
    return true;
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
    int dirX = dest.get_col() > orig.get_col() ? 1 : -1;
    int dirY = dest.get_row() > orig.get_row() ? 1 : -1;
    for (int i=1; i < abs(dest.get_col() - orig.get_col()) - 1; ++i) {
        if (board[orig.get_col() + i*dirX][ orig.get_row() + i*dirY] !=nullptr)
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