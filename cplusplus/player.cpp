#include "player.h"
#include <string>

Player::Player(std::string newName){
    Name = newName;
    points = 0;
}

std::string Player::getName(){
    return this->Name;
}