#include <string>
#ifndef PLAYER_H
#define PLAYER_H
class Player{
   public:
        Player(const std::string, const double);
        double getMoney();
        std::string getName();
        Player& operator+=(const double);
        void operator+(const double);
    private: 
        std::string Name;
        double money;
};


#endif /* PLAYER_H */