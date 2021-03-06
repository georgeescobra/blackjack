#include <iostream>
#include <sstream>
#include <algorithm>
#include <time.h>
#include "deck.h"


void Deck::printDeck(){
    for (auto const& p: deck) 
        std::cout << "Name Of Card: " << p.name << "\n" <<  "\tRank: " << p.kind << " " << "Value: " << p.value << std::endl;
}

Deck::Deck(const double numOfDeck){
    for(int i=0;i < numOfDeck; i++) {
        for(int s=0; s<4; s++){
            for(int v=0; v<13; v++){
                std::stringstream newName;
                newName << face[v].first << std::string(" of ") << type[s];
                deck.push_back({newName.str(), face[v].first, type[s] ,face[v].second});
            }
        }
    }
    // printDeck();
}

void Deck::shuffleDeck(){
    int len = deck.size();
    srand(time(0));
    for(int i = 0; i < len-1; i++){
        int randIndex = i + rand() % (len - i);
        std::swap(deck[randIndex], deck[i]);
    }
    // printDeck();
}

std::vector<Deck::card>* Deck::getDeck(){
    // std::cout << &deck << std::endl; // making sure that the deck's address holds
    return &deck;
}