#include <iostream>
#include <fstream>
#include <string>
#include "player.h"

void printIntro();

using namespace std;
int main(){
    cout << "Welcome to Tsing's BlackJack Table!" << endl;
    printIntro();

    string Name;
    do{
        cout << "Please enter your name: ";
        cin >> Name;
    } 
    while (Name.empty());
    
    Player newPlayer(Name);
    
    // cout << newPlayer.getPoints() << endl;
    // newPlayer +=  1*20;
    // cout << newPlayer.getPoints() << endl;
    



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