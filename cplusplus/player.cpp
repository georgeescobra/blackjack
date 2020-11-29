#include "player.h"
#include "deck.h"
#include <string>
#include <cmath>

Player::Player(const std::string newName, const double startingMoney){
    Name = newName;
    money = startingMoney;
}

Player::Player(const std::string name){
    Name = name;
    money = (name == "Dealer") ? HUGE_VAL : 500.0;
}
std::string Player::getName() const{
    return this->Name;
}

double Player::getMoney() const{
    return this->money;
}

Player& Player::operator+=(const double n){
    this->money += n;
    return *this;
}

void Player::operator+(const double n){
    this->money += n;
}

