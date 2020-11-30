#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sstream>
#include "player.h"
// #include "deck.h"

void printIntro();
std::map<std::string, double> parseConfig(const std::string);
void initialDraw(Player&, Player&, std::vector<Deck::card>&);
std::string askToHitOrStay();
bool checkWhoWon(Player&, Player&);

int main(){
    std::cout << "Welcome to Tsing's BlackJack Table!" << std::endl;
    bool gameRunning = true;
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

    bool roundOver = false;
    while(gameRunning){
        std::cout << "------NEW ROUND------\n";
        std::string playerStatus = "PLAYING"; // LOST, WON, DRAW, PLAYING
        if (!roundOver) initialDraw(newPlayer, Dealer, *shuffledDeck);
        roundOver = newPlayer.checkPlayerHandValue();
        int playerValue = newPlayer.getHandValue();
        if (playerValue >= 21){
            std::cout << "Dealer Shows: \n";
            Dealer.showHand();
            int dealerValue = Dealer.getHandValue();
            if(playerValue > 21 || (playerValue < dealerValue && dealerValue <= 21) || (playerValue > 21 && dealerValue > 21)) playerStatus = "LOST";
            else if(playerValue > dealerValue || (playerValue <= 21 && dealerValue > 21)) playerStatus = "WON";
            else if(playerValue == dealerValue) playerStatus = "DRAW";
            Dealer.printHandValue();
            std::cout << "Player Status: " << playerStatus << "\n";
            break;        
        }

        newPlayer.clearHand();
        Dealer.clearHand();
        std::cout << "---------------------\n\n";
    }
    return 0;
}

void initialDraw(Player &newPlayer,Player &Dealer, std::vector<Deck::card> &shuffledDeck){
    std::cout << newPlayer.getName() << "'s Money: " << newPlayer.getMoney() << "\n";
    newPlayer.drawPair(shuffledDeck); 
    newPlayer.showHand();
    Dealer.drawPair(shuffledDeck);
    Dealer.showDealerHand();
    newPlayer.printHandValue(); 
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
