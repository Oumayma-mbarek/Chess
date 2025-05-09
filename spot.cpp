#include <iostream> 
#include <vector>
#include <string>

#include "spot.hpp"
#include "couleur.hpp"

using namespace std;

Spot::Spot( int row,int col): x(row), y(col) {}


bool Spot::operator==(const Spot& other) const{
    return x==other.x && y==other.y ;
 }

  
int Spot::get_col() const {return y;}
int Spot::get_row() const {return x;}

void Spot::set_col(int col){
    y=col; 
    return ;
}
void Spot::set_row(int row){
    x=row;
    return;
}

string Spot::to_string()  {
    return string(1, y + '1') + string(1, x + 'a') ;
}

bool Spot::validspot() const {
    return x >= 0 && x <= 7 && y >= 0 && y <= 7;
}
