#include <iostream>
#include <vector>
using namespace std;
//contains a list of menus, allowing for us to navigate menus and keep track of where we are via linked list
class menu{
    private:
        //we will keep track of which menus this one can access via a vector and a parent pointer
        vector<menu*> *options= new vector<menu*>;
        string name="";
        menu* parent;
    public:
        int size=options->size();
        string getName(){
            return name;
        }
        void insert(menu* obj){
            options->push_back(obj);
            size++;
        }
        //print all the menus this one connects to, i.e. the menus the user can access from here
        void print(){
            int i=1;
            if(parent!=nullptr){
                cout<<i<<". "<<parent->getName()<<endl;
                for(i; i<size+1; i++){
                    cout<<i+1<<". "<<options->at(i-1)->getName()<<endl;
                }
            }
            else{
                for(i; i<size+1; i++){
                    cout<<i<<". "<<options->at(i-1)->getName()<<endl;
                }
            }
        }
            
    menu* nextMenu(int input){
        if(input==1&&parent!=nullptr){
            return parent;
        }
        else{
            return(options->at(input-1));
        }
    }
    menu(string str, menu *parentIn){
        parent=parentIn;
        name=str;
    }
};