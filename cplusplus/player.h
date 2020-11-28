#include <string>
#ifndef PLAYER_H
#define PLAYER_H
class Player{
   public:
        Player(std::string);
        int getPoints();
        std::string getName();
    private: 
        std::string Name;
        int points;
        int setPoints();
};


#endif /* PLAYER_H */