#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sstream>
#include "player.h"
// #include "deck.h"

void printIntro();
std::map<std::string, double> parseConfig(const std::string);

int main(){
    std::cout << "Welcome to Tsing's BlackJack Table!" << std::endl;
    printIntro();
    std::map<std::string, double> config = parseConfig("config.txt");
    Deck gameDeck(config.at("numOfDecks")); // initializes the deck
    gameDeck.shuffleDeck();
    std::vector<Deck::card> *shuffledDeck = gameDeck.getDeck(); //hold the address of the actual deck, also don't need to free because this pointer is on the stack
    // std::cout << shuffledDeck << std::endl; // only use delete if 'new' keyword is usued

    std::string Name;
    do{
        std::cout << "Please enter your name: ";
        std::cin >> Name;
    } 
    while (Name.empty());
    Player newPlayer(Name, config["startingMoney"]); // initializes player
    Player Dealer("Dealer"); // Initializes Dealer
    // cout << "Name: " << newPlayer.getName() << " " << "Money: " << newPPlayer.getMoney() << endl; // debug for player

    newPlayer.drawPair(*shuffledDeck); 
    newPlayer.showHand();
    Dealer.drawPair(*shuffledDeck);
    Dealer.showDealerHand();
    // std::cout << (*shuffledDeck).size() << std::endl; // dereferences pointer and checks the size of deck
    
    return 0;
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
