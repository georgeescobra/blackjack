#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sstream>
#include <cctype>
#include "player.h"
#include "deck.h"


void printIntro();
std::map<std::string, double> parseConfig(const std::string);
double initialDraw(Player&, Player&, std::vector<Deck::card>&);
std::string askToHitOrStay();
bool checkWhoWon(Player&, Player&);

int main(){
    std::cout << "Welcome to Tsing's BlackJack Table!" << std::endl;
    printIntro();
    std::map<std::string, double> config = parseConfig("config.txt");
    Deck gameDeck(config.at("numOfDecks")); // initializes the deck
    gameDeck.shuffleDeck();
    std::vector<Deck::card> *shuffledDeck = gameDeck.getDeck(); //hold the address of the actual deck, also don't need to free because this pointer is on the stack
    bool gameRunning = true;
    // std::cout << shuffledDeck << std::endl; // only use delete if 'new' keyword is usued

    std::string Name;
    do{
        std::cout << "Please enter your name: ";
        std::getline(std::cin, Name);
    } 
    while (Name.empty() || Name.compare(" ") == 0);
    Player newPlayer(Name, config["startingMoney"]); // initializes player
    Player Dealer("Dealer"); // Initializes Dealer
    // cout << "Name: " << newPlayer.getName() << " " << "Money: " << newPPlayer.getMoney() << endl; // debug for player

    bool roundOver = false;
    while(gameRunning && (*shuffledDeck).size() > 4){
        std::cout << "------NEW ROUND------\n";
        std::string playerStatus = "PLAYING"; // LOST, WON, DRAW, PLAYING
        if (!roundOver) initialDraw(newPlayer, Dealer, *shuffledDeck);
        roundOver = newPlayer.checkPlayerHandValue();
        int playerValue = newPlayer.getHandValue();
        // check after initial draw
        if (playerValue >= 21){
            std::cout << "***Dealer Shows*** \n";
            Dealer.showHand();
            int dealerValue = Dealer.getHandValue();
            if(playerValue > 21 || (playerValue < dealerValue && dealerValue <= 21) || (playerValue > 21 && dealerValue > 21)) playerStatus = "LOST";
            else if((playerValue == 21 && dealerValue < playerValue) || (playerValue == 21 && dealerValue > 21)) playerStatus = "WON";
            else if(playerValue == dealerValue) playerStatus = "DRAW";
            Dealer.printHandValue();
        }

        newPlayer.clearHand();
        Dealer.clearHand();
        std::cout << "---------------------\n\n";
    }
    return 0;
}

double initialDraw(Player &newPlayer,Player &Dealer, std::vector<Deck::card> &shuffledDeck){
    std::string stringToCheck = "";
    double moneyToBet = 0;
    do{
        std::cout << "You have $" << newPlayer.getMoney() << " \nHow much would you like to bet? ";
        std::getline(std::cin, stringToCheck);
        bool valid = true;
        // std::cout << stringToCheck << "sdfsdf";
        if(stringToCheck.empty()) continue;
        for(char const &c : stringToCheck){ 
            if(!valid) break;
            valid = (!std::isdigit(c) || std::isspace(c)) ? false : true;
        }
        if(valid) moneyToBet = std::stod(stringToCheck);
        if(moneyToBet <= 0 || moneyToBet > newPlayer.getMoney()) std::cout << "Enter Valid Amount.\n";
    }while(moneyToBet <= 0 || moneyToBet > newPlayer.getMoney());
    newPlayer.drawPair(shuffledDeck); 
    newPlayer.showHand();
    Dealer.drawPair(shuffledDeck);
    Dealer.showDealerHand();
    newPlayer.printHandValue(); 

    return moneyToBet;
}

bool checkWhoWon(Player &newPlayer, Player &Dealer){
}

std::string askToHitOrStay(){
    std::string temp;
    std::cout << "Would you like to Hit(H) or Stay(S): ";
    std::cin >> temp;
    return temp;
}

void printIntro(){
    std::ifstream introFile;
    std::string line;
    introFile.open("intro.txt", std::ios::out);
    if(introFile.is_open()){
        while (getline(introFile, line)) std::cout << line << '\n';
        introFile.close();
    }else std::cout << "Failed to open Intro" << std::endl; 
        
}

std::map<std::string, double> parseConfig(const std::string configName){
    std::map<std::string, double>config;
    std::ifstream configFile;
    configFile.open(configName, std::ios::out);
    if(configFile.is_open()){
        std::string line;
        std::string key;
        double value;
        while(getline(configFile, line)){
            std::istringstream parse(line);
            parse >> key >> value;
            config[key] = value;
        }
    }
    configFile.close();
    // for (auto const& table : config) std::cout << table.first << ": " << table.second << std::endl;
    return config;
}
