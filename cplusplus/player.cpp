#include "player.h"
#include <string>

Player::Player(const std::string newName){
    Name = newName;
    money = 500.0;
}

std::string Player::getName(){
    return this->Name;
}

double Player::getPoints(){
    return this->money;
}

Player& Player::operator+=(const double n){
    this->money += n;
    return *this;
}

void Player::operator+(const double n){
    this->money += n;
}

