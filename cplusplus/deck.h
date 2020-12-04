#ifndef DECK_u
#define DECK_H

#include <vector>
#include <map>
#include <string>

class Deck{
    public:
        struct card{
            std::string name;
            std::string kind;
            std::string suit;
            int value;
        }; 
        Deck(const double);
        std::string getCardName();
        int getCardValue() const;
        void shuffleDeck();
        std::vector<card>* getDeck();
   private:
        std::vector<card> deck;
        const std::string type[4] {"Hearts", "Spades", "Diamonds", "Clubs"};
        const std::vector<std::pair<std::string, int>> face {
            {"Two", 2},
            {"Three", 3},
            {"Four", 4},
            {"Five", 5},
            {"Six", 6},
            {"Seven", 7},
            {"Eight", 8},
            {"Nine", 9},
            {"Ten", 10},
            {"Jack", 10},
            {"Queen", 10},
            {"King", 10},
            {"Ace", 11}
        };
        void printDeck();
 
};
 
#endif /* DECK_H */ 
