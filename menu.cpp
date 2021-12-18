#include <iostream>
#include <vector>
using namespace std;
//contains a list of menus, allowing for us to navigate menus and keep track of where we are via linked list
class menu{
    private:
    //we will keep track of which menus this one can access via a vector and a parent pointer
    vector<menu*> options;
    string name="";
    menu* parent;
    public:
    string getName(){
        return name;
    }
    void insert(menu* obj){
        options.push_back(obj);
    }
    //print all the menus this one connects to, i.e. the menus the user can access from here
    void print(){
        int size=options.size();
        cout<<". return to "<<parent->getName();
        for(int i=0; i<size; i++){
            cout<<i+2<<". "<<options[i]->getName()<<endl;
        }
    }
    menu* nextMenu(int input){
        try{
            return(options[input]);
        }
        catch(...){
            return this;
        }
    }
    menu(string str, menu *parentIn){
        parent=parentIn;
        name=str;
    }
};