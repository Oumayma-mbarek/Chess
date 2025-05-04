
#include <iostream> 
#include <vector>
#include <string>

#include "piece.hpp"
#include "spot.hpp"
#include "couleur.hpp"


using namespace std;

Piece::Piece(Couleur c, string sym, int i ,Spot s,bool fm): couleur(c),symbole(sym),id(i),pos(s), firstmove(fm) {}

void Piece::set_pos(Spot s){
    pos.set_col(s.get_col());
    pos.set_row(s.get_row());
}
        
Spot Piece::get_pos(){
    return Spot(pos.get_col(),pos.get_row());
}
       

void Piece::display(){
    cout<< symbole;
    return;
}

string Piece::get_symbole()const{return symbole;}

Couleur Piece::get_color()const{return couleur;}

bool Piece::get_firstmove()const {return firstmove;}

void Piece::setFirstMove(bool t){ 
    firstmove=t;
    return;
}






King::King(Couleur c,string sym,int i,Spot s):Piece(c,sym,i,s){}
bool King::possible_move(Spot orig, Spot dest ) {

    if(!dest.validspot()) return false;
    if(dest==orig) return false;

    // Move one square in any direction
    if (abs(orig.get_col() - dest.get_col()) <= 1 && abs(orig.get_row() - dest.get_row()) <= 1){
        return true;
    }
    return false;
} 

Queen::Queen(Couleur c,string sym,int i,Spot s):Piece(c,sym,i,s){}
bool Queen::possible_move(Spot orig, Spot dest ){

    if(!dest.validspot()) return false;
    if(dest==orig) return false;

    //Horizontal move
    if (orig.get_col() != dest.get_col() && orig.get_row() == dest.get_row()){
        return true;
    }
    //Verical move
    if (orig.get_col() == dest.get_col() && orig.get_row() != dest.get_row()){
        return true;
    }
    // Diagonal move
    if (abs(orig.get_col() - dest.get_col()) == abs(orig.get_row() - dest.get_row())){
        return true;
    }
    return false;
} 

Pawn::Pawn(Couleur c,string sym,int i,Spot s):Piece(c,sym,i,s){}
bool Pawn::possible_move(Spot orig, Spot dest ){

    if(!dest.validspot()) return false;
    if(dest==orig) return false;
    
    //White Pawns
    if(get_color()==White){
        
        //mouvement normal, anvance d'une case
        if(dest.get_col()== orig.get_col()  &&  dest.get_row()==orig.get_row()+1){
            return true;
        }
        //avance de deux cases si premier move
        else if(firstmove==true && dest.get_col()== orig.get_col()  &&  dest.get_row()==orig.get_row()+2){
            return true;
        }
        //mouvement diagonal vers la droite
        else if (dest.get_col()== orig.get_col()+1  &&  dest.get_row()==orig.get_row()+1 ){
            return true;
        }
        //mouvement diagonal vers la gauche 
        else if(dest.get_col()== orig.get_col()-1  &&  dest.get_row()==orig.get_row()+1){
            return true;
        }
        else return false;
    }


    //Black Pawns
    if(get_color()==Black){
        
        //mouvement normal, anvance d'une case
        if(dest.get_col()== orig.get_col()  &&  dest.get_row()==orig.get_row()-1){
            return true;
        }
        //avance de deux cases si premier move
        else if(firstmove==true && dest.get_col()== orig.get_col()  &&  dest.get_row()==orig.get_row()-2){
            return true;
        }
        //mouvement diagonal vers la droite
        else if (dest.get_col()== orig.get_col()-1  &&  dest.get_row()==orig.get_row()-1 ){
            return true;
        }
        //mouvement diagonal vers la gauche 
        else if(dest.get_col()== orig.get_col()+1  &&  dest.get_row()==orig.get_row()-1){
            return true;
        }
        else return false;
    }

    return false;
} 

Knight::Knight(Couleur c,string sym,int i,Spot s):Piece(c,sym,i,s){}
bool Knight::possible_move(Spot orig, Spot dest ){
    if(!dest.validspot()) return false;
    if(dest==orig) return false;
    

    // L-shaped move up-right
    if (dest.get_col() == orig.get_col() + 1 && dest.get_row() == orig.get_row() + 2){
        return true;
    }
    // L-shaped move up-left
    if (dest.get_col() == orig.get_col() - 1 && dest.get_row() == orig.get_row() + 2){
        return true;
    }
    // L-shaped move down-right
    if (dest.get_col() == orig.get_col() + 1 && dest.get_row() == orig.get_row() - 2){
        return true;
    }
    // L-shaped move down-left
    if (dest.get_col() == orig.get_col() - 1 && dest.get_row() == orig.get_row() - 2){
        return true;
    }
    // L-shaped move right-up
    if (dest.get_col() == orig.get_col() + 2 && dest.get_row() == orig.get_row() + 1){
        return true;
    }
    // L-shaped move right-down
    if (dest.get_col() == orig.get_col() + 2 && dest.get_row() == orig.get_row() - 1){
        return true;
    }
    // L-shaped move left-up
    if (dest.get_col() == orig.get_col() - 2 && dest.get_row() == orig.get_row() + 1){
        return true;
    }
    // L-shaped move left-down
    if (dest.get_col() == orig.get_row() - 2 && dest.get_row() == orig.get_row() - 1){
        return true;
    }
    else return false;

} 

Bishop::Bishop(Couleur c,string sym,int i,Spot s):Piece(c,sym,i,s){}
bool Bishop::possible_move(Spot orig, Spot dest ){
    if(!dest.validspot()) return false;
    if(dest==orig) return false;

    // Diagonal move
    if (abs(orig.get_col() - dest.get_col()) == abs(orig.get_row() - dest.get_row())){
        return true;
    }
    return false;
} 

Rook::Rook(Couleur c,string sym,int i,Spot s):Piece(c,sym,i,s){}
bool Rook::possible_move(Spot orig, Spot dest ){
    if(!dest.validspot()) return false;
    if(dest==orig) return false;
    //Horizontal move
    if (orig.get_col() != dest.get_col() && orig.get_row() == dest.get_row()){
        return true;
    }
    //Verical move
    if (orig.get_col() == dest.get_col() && orig.get_row() != dest.get_row()){
        return true;
    }
    return false;
} 