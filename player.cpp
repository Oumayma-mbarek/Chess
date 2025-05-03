#include <vector>
#include <iostream>
#include <string>

#include "couleur.hpp"
#include "player.hpp"

using namespace std; 

Player::Player (string n, Couleur c): nom(n), couleur(c) {}
Player::~Player() {}
Couleur Player::get_couleur() const {return couleur;}
string Player::get_nom() const {return nom;}