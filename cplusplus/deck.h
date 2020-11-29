#ifndef DECK_u
#define DECK_H

#include <vector>
#include <map>
#include <string>

class Deck{
    private:
        struct card{
            std::string name;
            std::string kind;
            std::string suit;
            int value;
        };
        std::vector<card> deck{};
        std::string type[4] {"Hearts", "Spades", "Diamonds", "Clubs"};
        std::vector<std::pair<std::string, int>> face {
            {"Two", 2},
            {"Three", 3},
            {"Four", 4},
            {"Five", 5},
            {"Six", 6},
            {"Seven", 7},
            {"Eight", 8},
            {"Nine", 9},
            {"Ten", 10},
            {"Jack", 11},
            {"Queen", 11},
            {"King", 11},
            {"Ace", 11}
        };
        void printDeck();
    public:
            Deck(const double);
            int drawCard();
            int drawPair();
        
};
 
#endif /* DECK_H */ 