#include "player.h"
#include <string>

Player::Player(const std::string newName, const double startingMoney){
    Name = newName;
    money = startingMoney;
}

std::string Player::getName(){
    return this->Name;
}

double Player::getMoney(){
    return this->money;
}

Player& Player::operator+=(const double n){
    this->money += n;
    return *this;
}

void Player::operator+(const double n){
    this->money += n;
}

