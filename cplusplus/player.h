#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <map>
class Player{
   public:
        Player(const std::string, const double);
        double getMoney();
        std::string getName();
        int getHandValue();
        Player& operator+=(const double);
        void operator+(const double);
    private: 
        std::string Name;
        double money;
        std::map<int ,int> hand;
        
};


#endif /* PLAYER_H */