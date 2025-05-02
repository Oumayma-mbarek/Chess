#include <iostream> 
#include <vector>
#include <string>

#include "couleur.hpp"
#include "piece.hpp"
#include "spot.hpp"
#include "board.hpp"

using namespace std;

Spot::Spot( int x,int y): x(x), y(y) {}
Spot::~Spot() {}




bool Spot::operator==(const Spot& other) const{
    return x==other.x && y==other.y ;
 }

  
int Spot::get_col() const {return x;}
int Spot::get_row() const {return y;}

void Spot::set_col(int col){
    x=col; 
    return ;
}
void Spot::set_row(int row){
    y=row;
    return;
}


string Spot::to_string()  {
    char colonne = 'a' + x;         // x = 0 → 'a'
    int ligne = y + 1;              // y = 0 → 1
    return string(1, colonne) + std::to_string(ligne);
}



bool Spot::validspot() const {
    return x >= 0 && x <= 7 && y >= 0 && y <= 7;
}
