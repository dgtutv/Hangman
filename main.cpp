#include <iostream>
#include "SkipList.h"
#include "menu.cpp"
#include <string>
using namespace std;
int main(int argc, char** argv) {
    SkipList *letterBank=new SkipList;
    vector<string> wordbank();
    //fill the letter bank with all lower case letters
    for(char currLetter=97; currLetter<123; currLetter++){
        Key currKey=to_string((int)currLetter);
        Value currVal=to_string(currLetter);
        letterBank->insert(currKey, currVal);
    }
    menu *MainMenu=new menu("Main Menu", nullptr);
    menu *NumOfPlayers=new menu("Number of Players", MainMenu);
    menu *PlayerSelect=new menu("Player Select", NumOfPlayers);
    menu *Game=new menu("Game", NumOfPlayers);
    menu *WordBankMenu=new menu("Word Bank Modification", MainMenu);
    MainMenu->insert(NumOfPlayers);
    NumOfPlayers->insert(PlayerSelect);
    PlayerSelect->insert(Game);
    MainMenu->insert(WordBankMenu);
    menu *thisMenu= MainMenu;
    int input;
    while(true){
        thisMenu->print();
        cin>>input;
        thisMenu=thisMenu->nextMenu(input);
    }
}