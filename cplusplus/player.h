#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <map>
class Player{
    private: 
        std::string Name;
        double money;
        std::map<int ,int> hand;
     public:
        Player(const std::string, const double);
        double getMoney() const;
        std::string getName() const;
        int getHandValue() const;
        Player& operator+=(const double);
        void operator+(const double);
       
};


#endif /* PLAYER_H */