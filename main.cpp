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
    menu *MainMenu=new menu(string("Main Menu"), nullptr);
    menu *NumOfPlayers=new menu(string("Number of Players"), MainMenu);
    menu *PlayerSelect=new menu(string("Player Select"), NumOfPlayers);
    menu *Game=new menu(string("Game"), NumOfPlayers);
    menu *WordBankMenu=new menu(string("Word Bank Modification"), MainMenu);
    MainMenu->insert(NumOfPlayers);
    PlayerSelect->insert(Game);
    NumOfPlayers->insert(PlayerSelect);
    Game->insert(nullptr);
    MainMenu->insert(WordBankMenu);
    menu *thisMenu= MainMenu;
    int input;
    while(thisMenu!=nullptr){
        thisMenu->print();
        cout<<"input: ";
        cin>>input;
        if(input<0){
            return(0);
        }
        cout<<endl;
        cout<<endl;
        thisMenu=thisMenu->nextMenu(input);
        cout<<thisMenu->getName()<<endl;
    }
}