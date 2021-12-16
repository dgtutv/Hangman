#include <iostream>
#include <vector>
using namespace std;
class menu{
    private:
    struct menuObject{
        menuObject(string name, bool isMenu):name(name), isMenu(isMenu){}
        string name;
        bool isMenu;
        string getName(){
            return name;
        }
        bool isMenuCheck(){
            return isMenu;
        }
    };
    vector<menuObject> options;
    string name;
    public:
    void insert(menuObject obj){
        options.push_back(obj);
    }
    menu(string str):name(str){}
};