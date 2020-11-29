#include <iostream>
#include <sstream>
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
    printDeck();
}