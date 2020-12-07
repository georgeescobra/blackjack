#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sstream>
#include <cctype>
#include <regex>
#include <unistd.h>
#include "player.h"


void printIntro();
std::map<std::string, double> parseConfig(const std::string);
double initialDraw(Player&, Player&, std::vector<Deck::card>&);
int askToHitOrStay();
void checkWhoWon(Player&, Player&, int, double, double);
void bothDraw(Player&, Player&, std::vector<Deck::card>&);
int toContinue();

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

    double multiplier = config.at("multiplier");
    double moneyToBet = 0.0;
    enum PLAYERSTATUS {DRAW, WON , LOST, PLAYING, NOTPLAYING}; // 0, 1, 2
    while(gameRunning && (*shuffledDeck).size() > 4 && newPlayer.getMoney() > 0){
        /*      1. Do an initial draw
         *          1a. Check if Dealer or if Player has a 21
         *          1b. If either of this: round ends
         *          1c. SKIP TO PAY OUT
         *      2. Player can either hit or stand up until either he busts or stands
         *          2a. If he busts SKIP TO PAY OUT
         *      3. If player stands, dealer here is guaranteed to be under 21 DEALER TURN
         *          3a. DEALER SHOWS 
         *          3b. if dealerV > playerV: STAND DEALER WINS
         *          3c. If dealer < 17 && dealerV < playerV: HIT until dealer either busts or value is greater than players
         *      4. PAYOUT
         *      5. CHECK IF PLAYER STILL HAS MONEY IF NOT GAME ENDS
         *      6. IF PLAYER STILL HAS MONEY ASK IF HE WANTS TO CONTINUE AND RESET
         */
        std::cout << "------NEW ROUND------\n";
        PLAYERSTATUS playerStatus = PLAYERSTATUS::PLAYING; // LOST, WON, DRAW, PLAYING
        moneyToBet = initialDraw(newPlayer, Dealer, *shuffledDeck);
        newPlayer.checkForAces();
        Dealer.checkForAces();
        int playerValue = newPlayer.getHandValue();
        int dealerValue = Dealer.getHandValue();
        if (playerValue == 21 || dealerValue == 21){ // check after initial draw if player draws a 21, cannot auto bust ;) natural 21 always win
            std::cout << "***Dealer Shows*** \n";
            Dealer.showHand();
            int dealerValue = Dealer.getHandValue();
            if (playerValue == dealerValue) playerStatus = PLAYERSTATUS::DRAW;
            else if (playerValue < dealerValue) playerStatus = PLAYERSTATUS::LOST;
            else if (playerValue > dealerValue) playerStatus = PLAYERSTATUS::WON;
            Dealer.printHandValue();
        }
        int playerChoice;
        while(playerStatus == PLAYERSTATUS::PLAYING){ // after initial check, player gets to hit or stay
            playerChoice =  askToHitOrStay(); // 0 h 1 s
            if (playerChoice == 1) playerStatus = PLAYERSTATUS::NOTPLAYING;
            else{
                // need to check for Ace's, if hand goes over 21 with an Ace, Ace value goes to 1
                newPlayer.drawCard(*shuffledDeck);
                newPlayer.checkForAces();
                newPlayer.showHand();
                newPlayer.printHandValue();
                if (newPlayer.getHandValue() == 21) playerStatus =  PLAYERSTATUS::NOTPLAYING;
                if (newPlayer.getHandValue() > 21) playerStatus = PLAYERSTATUS::LOST;
            }
        }
        while(Dealer.getHandValue() < 21 && (playerStatus != PLAYERSTATUS::PLAYING && playerStatus != PLAYERSTATUS::LOST)){ // dealer turns 
            /*      dealer should hit if hand < players
             *      dealer should stop if hand > players or busts
             *   need to check for Ace's, if hand goes over 21 with an Ace, Ace value goes to 1
             */
            if (Dealer.getHandValue() > newPlayer.getHandValue()) {
                playerStatus = PLAYERSTATUS::LOST; // premptive check before draw
                continue;
            }
            Dealer.drawCard(*shuffledDeck);
            Dealer.checkForAces();
            Dealer.showHand();
            Dealer.printHandValue();
            if (Dealer.getHandValue() > 21) playerStatus = PLAYERSTATUS::WON;
            if (Dealer.getHandValue() == newPlayer.getHandValue()){
                playerStatus = PLAYERSTATUS::DRAW;
                break;
            }
            if (Dealer.getHandValue() <= 21 && Dealer.getHandValue() > newPlayer.getHandValue() ) playerStatus = PLAYERSTATUS::LOST;
            sleep(1);
        }
        
        checkWhoWon(newPlayer, Dealer, playerStatus, multiplier, moneyToBet);
        newPlayer.clearHand();
        Dealer.clearHand();
        if(newPlayer.getMoney() < 0) std::cout << "YOU HAVE RAN OUT OF MONEY\n";
        std::cout << "---------------------\n\n";
    }
    return 0;
}

double initialDraw(Player &newPlayer,Player &Dealer, std::vector<Deck::card> &shuffledDeck){
    std::string stringToCheck = "";
    double moneyToBet = 0;
    do{
        std::cout << "You have $" << newPlayer.getMoney() << " \nHow much would you like to bet? $";
        std::getline(std::cin, stringToCheck);
        bool valid = true;
        if(stringToCheck.empty()) continue;
        for(char const &c : stringToCheck){ 
            if(!valid) break;
            valid = (!std::isdigit(c) || std::isspace(c)) ? false : true;
        }
        if(valid) moneyToBet = std::stod(stringToCheck);
        if(moneyToBet <= 0 || moneyToBet > newPlayer.getMoney()) std::cout << "Enter Valid Amount.\n";
    }while(moneyToBet <= 0 || moneyToBet > newPlayer.getMoney());
    bothDraw(newPlayer, Dealer, shuffledDeck);
    return moneyToBet;
}

void bothDraw(Player &newPlayer, Player &Dealer, std::vector<Deck::card> &shuffledDeck){
    newPlayer.drawPair(shuffledDeck); 
    newPlayer.showHand();
    Dealer.drawPair(shuffledDeck);
    Dealer.showDealerHand();
    newPlayer.printHandValue(); 
}


void checkWhoWon(Player &newPlayer, Player &Dealer, int playerStatus, double multi, double bet){
    // enum PLAYERSTATUS {DRAW, WON , LOST, PLAYING, NOTPLAYING}; // 0, 1, 2
    std::cout << "\t********RESULTS********\n";
    newPlayer.showHand();
    newPlayer.printHandValue();
    Dealer.showHand();
    Dealer.printHandValue();
    switch(playerStatus){
        case (0):
            std::cout << "\t********" << newPlayer.getName() << " " << "DRAW!!********\n";
            break;
        case (1):
            std::cout << "\t********" << newPlayer.getName() << " " << "WON!!********\n";
            newPlayer += ((multi)*(bet));
            break;
        case (2):
            std::cout << "\t********" <<newPlayer.getName() << " " << "LOST!!********\n";
            newPlayer += ((-1)*(multi)*(bet));
            break;
        default:
            std::cout << newPlayer.getName() << " " << "STATUS DIDNT CHANGE!!\n";
    }
}

int askToHitOrStay(){ // 0 -> hit, 1 -> stay
    std::string playerChoice;
    bool h;
    bool s;
    do{
        std::cout << "Would you like to Hit(H) or Stay(S): "; 
        std::getline(std::cin, playerChoice);
        h = std::regex_search(playerChoice, std::regex{R"(^[hH]\w*)"});
        s = std::regex_search(playerChoice, std::regex{R"(^[sS]\w*)"});
    }while(playerChoice.empty() || (!h && !s));
    return (h) ? 0 : 1;
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

std::map<std::string, double> parseConfig(const std::string configName){ // prases the necessary configs for the game
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
