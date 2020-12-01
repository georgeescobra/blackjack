#include "player.h"
#include <cmath>
#include <iostream>


Player::Player(const std::string newName, const double startingMoney){
    Name = newName;
    money = startingMoney;
}
Player::Player(const std::string name){
    Name = name;
    money = (name == "Dealer") ? HUGE_VAL : 500.0;
}

void Player::drawPair(std::vector<Deck::card> &deck){

    hand.push_back(deck.front());
    deck.erase(deck.begin());
    hand.push_back(deck.front());
    deck.erase(deck.begin());
}

void Player::drawCard(std::vector<Deck::card> &deck){
    hand.push_back(deck.front());
    deck.erase(deck.begin());
}

void Player::showHand() const{
    std::cout << Name << "'s Cards: \n";
    for (auto &p : this->hand) 
        std::cout << "\t" << p.name << std::endl;
}

void Player::showDealerHand() const{
    std::cout << "Dealer's Cards: " << std::endl;
    for(int i = 0; i < hand.size(); i++){
        (i != 0) ? (std::cout << "\t" << hand[i].name << std::endl) : (std::cout << "\t[hidden]" << std::endl);
    }
}

bool Player::checkPlayerHandValue() const{
    return (this->getHandValue() >= 21) ? true : false;
}

void Player::clearHand() {
    this->hand.clear();
}

std::string Player::getName() const{
    return this->Name;
}

double Player::getMoney() const{
    return this->money;
}

int Player::getHandValue() const{
    int sum = 0;
    for(auto &p: hand) sum += p.value;
    return sum;
}

void Player::printHandValue() const{
    std::cout << this->Name << "'s Hand Value: " << getHandValue() << "\n";
}

Player& Player::operator+=(const double n){
    this->money += n;
    return *this;
}

void Player::operator+(const double n){
    this->money += n;
}

