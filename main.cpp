#include <iostream>
#include "SkipList.h"
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

}