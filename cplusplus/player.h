#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <map>
#include "deck.h"
class Player{
    private: 
        std::string Name;
        double money;
        std::vector<Deck::card> hand {};
     public:
        Player(const std::string, const double);
        Player(const std::string);
        void showHand() const; // const at the end cant change any of the data members
        void showDealerHand() const;
        void drawPair(std::vector<Deck::card>&); 
        void drawCard(std::vector<Deck::card>&);
        double getMoney() const;
        std::string getName() const;
        int getHandValue() const;
        Player& operator+=(const double);
        void operator+(const double);
       
};


#endif /* PLAYER_H */