#include <string>
#include <cmath>
#include <iostream>
#include "player.h"

Player::Player(const std::string newName, const double startingMoney){
    Name = newName;
    money = startingMoney;
}
Player::Player(const std::string name){
    Name = name;
    money = (name == "Dealer") ? HUGE_VAL : 500.0;
}

void Player::drawPair(std::vector<Deck::card>& deck){
    hand.push_back(deck.front());
    deck.erase(deck.begin());
    hand.push_back(deck.front());
    deck.erase(deck.begin());
}

void Player::drawCard(std::vector<Deck::card>& deck){
    hand.push_back(deck.front());
    deck.erase(deck.begin());
}

void Player::showHand() const{
    for (auto &p : this->hand) 
        std::cout << "\t" << p.name << std::endl;
}

void Player::showDealerHand() const{
    std::cout << "Dealer's Cards: " << std::endl;
    for(int i = 0; i < hand.size(); i++){
        (i != 0) ? (std::cout << "\t" << hand[i].name << std::endl) : (std::cout << "\t[hidden]" << std::endl);
    }

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

