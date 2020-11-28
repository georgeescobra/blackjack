#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <sstream>
#include "player.h"


void printIntro();

using namespace std;
int main(){
    cout << "Welcome to Tsing's BlackJack Table!" << endl;
    printIntro();
    std::map<std::string, double> config;
    std::ifstream configFile;
    configFile.open("config.txt", ios::out);
    if(configFile.is_open()){
        string line;
        string key;
        double value;
        while(getline(configFile, line)){
            std::istringstream parse(line);
            parse >> key >> value;
            config[key] = value;
        }
    }
    configFile.close();
    // for (auto const& table : config) cout << table.first << ": " << table.second << endl;

    string Name;
    do{
        cout << "Please enter your name: ";
        cin >> Name;
    } 
    while (Name.empty());
    Player newPlayer(Name, config["startingMoney"]);
    // cout << "Name: " << newPlayer.getName() << " " << "Money: " << newPlayer.getMoney() << endl;
    
    return 0;
}


void printIntro(){
    ifstream introFile;
    string line;
    introFile.open("intro.txt", ios::out);
    if(introFile.is_open()){
        while (getline(introFile, line)) cout << line << '\n';
        introFile.close();
    }else cout << "Failed to open Intro" << endl; 
        
}