#include "SkipList.h"
#include <iostream>

using namespace std;

// makes a new list on the top level of existing list.
// call only when top list is NULL or just the two sentinels. 
void SkipList::makeNewLevelList() {
    SkipList::Entry* minusInfinity = new Entry("!!", "");	// "!!" < any other string.
    SkipList::Entry* plusInfinity = new Entry("}}", "");	// "}}" > any other key.

    Quad* first = new Quad(minusInfinity);
    Quad* last = new Quad(plusInfinity);

    int numLists = listHeads.size();
    Quad* oldFirst = numLists == 0 ? NULL : listHeads[numLists - 1];
    Quad* oldLast  = numLists == 0 ? NULL : oldFirst->next;

    first->prev = NULL;
    first->next = last;
    first->above = NULL;
    first->below = oldFirst;

    last->prev = first;
    last->next = NULL;
    last->above = NULL;
    last->below = oldLast;

    if(oldFirst != NULL) {
        oldFirst->above = first;
        oldLast->above = last;
    }
    listHeads.push_back(first);
}

void SkipList::printOneList(int listNum) {
	Quad* bottomCurrent = listHeads[0];
	Quad* current = listHeads[listNum];

	while(bottomCurrent->next != NULL) {
		std::string toPrint;
		if(current->entry->getKey() == bottomCurrent->entry->getKey()) {
			toPrint = current->entry->getKey();
			current = current->next;
		}
		else {
			toPrint = "--";
		}
		cout << "--" << toPrint;
		bottomCurrent = bottomCurrent->next;
	}
	cout << "--" << bottomCurrent->entry->getKey() << "--" << endl;
}

void SkipList::print() {
	int numLists = listHeads.size();
	for(int i = numLists - 1; i >= 0; i--) {
		printOneList(i);
	}
} 

SkipList::Entry* SkipList::find(Key k) {
    int numLists = listHeads.size();
    Quad* current = listHeads[numLists - 1];

    while (current->below != NULL) {
        current = current->below;			// drop down
        while(k >= current->next->entry->getKey()) {	// scan forward
            current = current->next;
        }
    } 

    if(current->entry->key == k) {
        return current->entry;
    }
    else {
        return NULL;
    }
}

// the "trail" is a vector of the last node visited on each list
// the last element of trail is on the lowest list; the first is on the highest.
std::vector<SkipList::Quad*>* SkipList::findWithTrail(Key k) {
    std::vector<SkipList::Quad*>* trail = new std::vector<Quad*>();

    int numLists = listHeads.size();
    Quad* current = listHeads[numLists - 1];

    while (current != NULL) {
        while(k >= current->next->entry->getKey()) {	// scan forward
            current = current->next;
        }
	trail->push_back(current);
        current = current->below;			// drop down
    } 
    return trail;
}

// fill in the assigned functions here.
int SkipList::coinFlip(){
    return(std::rand()%2);
}
void SkipList::insert(Key k, Value v){
    //let 0 represent heads, and let 1 represent tails
    int headCounter=0;
    int numLists = listHeads.size();
    int flip;
    Entry* newEntry;
    //flip our coin until we get a tails (0) then record the amount of heads before that (1) 
    while(true){
        flip = coinFlip();
        if(flip==1){
            headCounter++;
        }
        if(flip==0){
            break;
        }
    }
    //increase number of lists by the difference between heads and current lists
    for(int i=0; i<headCounter-numLists+2; i++){
        makeNewLevelList();
    } 
    //lets create a current reference
    Quad* current=nullptr;
    //lets also create a reference to our recently added node
    Quad* recentAdded=nullptr;
    numLists = listHeads.size();
    //set our insertLevel to our headCounter
    int insertLevel=headCounter;
    //set our index to one below the max (so index == level) (start at one below top level)
    for(int index=insertLevel; index>-1; index--){
        //take our list header for this level
        current=listHeads.at(index);
        //skip forward until we are at the right level
        while(true){
            //check if this is the right spot
            if((current->next->entry->getKey()=="}}")||(current->next->entry->getKey()>k)){
                //make a new entry
                newEntry = new Entry(k, v);
                // //set the values of the new entry
                //make a new node with the entry
                Quad* newNode = new Quad(newEntry);
                //set the new nodes next to current next
                newNode->next=current->next;
                newNode->prev=current;
                current->next->prev=newNode;
                //set current next to our new node
                current->next=newNode;
                //check if a previously added node exists
                if(recentAdded!=nullptr){
                    //if so, set appropiate pointers
                    recentAdded->below=newNode;
                    newNode->above=recentAdded;
                }
                recentAdded=newNode;
                break;
            }
            else{
                current=current->next;
            }
        }
    }
}
void SkipList::remove(Key k){
    Quad* current=nullptr;
    Quad* before=nullptr;
    Quad* after=nullptr;
    vector<Quad*>* found=findWithTrail(k);
    vector<Quad*> toRemove;
    //append all that are not our key to a new vector
    for(int i=0; i<found->size(); i++){
        current = found->at(i);
        if(current->entry->key==k){ 
            toRemove.push_back(current);   
        }
    }
   
    //now we should have all entries with key from top to bottom, remove them
    for(int i=0; i<toRemove.size(); i++){
        current = toRemove[i];
        before=current->prev;
        after=current->next;
        before->next=after;
        after->prev=before;
        delete current->entry;
        delete current;
    }
    //delete all empty levels
    for(int i=listHeads.size()-1; i>-1; i--){
        current=listHeads[i];
        if(current->next->entry->getKey()=="}}"){
            delete current->next->entry;
            delete current->next;
            delete current->entry;
            delete current;
            listHeads.pop_back();
        }
    }
    //tack on a new empty level on top
    //(preserving the original level is complex and error prone)
    makeNewLevelList();
    delete found;
}
SkipList::Entry* SkipList::ceilingEntry(Key k){
    //if the exact key is not present we will search for it
    if(find(k)==NULL){
        //Search algorithm above, modified
        int numLists = listHeads.size();
        Quad* current = listHeads[numLists - 1];

        while (current->below != NULL) {
            current = current->below;			// drop down
            while(k >= current->next->entry->getKey()) {	// scan forward
                current = current->next;
            }
        }
        //end search algorithm at largest key < k
        //return the next key, as if it not the cieling of k, it is the end
        return(current->next->entry);     
    }
    //if the exact key is present, return searches result for it.
    else{
        return(find(k));
    }
}
SkipList::Entry* SkipList::floorEntry(Key k){
    //if the exact key is not present we will search for it
    if(find(k)==NULL){
        ///Search algorithm above, modified
        int numLists = listHeads.size();
        Quad* current = listHeads[numLists - 1];

        while (current->below != NULL) {
            current = current->below;			// drop down
            while(k >= current->next->entry->getKey()) {	// scan forward
                current = current->next;
            }
        }
        //end search algorithm at largest key < k
        //if the floor entry is the start
        if(current->entry->getKey()=="!!"){
            //iterate throught the row until the end 
            while(current->next!=nullptr){
                current=current->next;
            }
            //return the end
            return(current->entry);
        }
        //otherwise, return the current key, as it is the floor of k
        else{
            return(current->entry);   
        }
    }
    //if the exact key is present, return searches result for it.
    else{
        return(find(k));
    }
}
SkipList::Entry* SkipList::greaterEntry(Key k){
    int numLists = listHeads.size();
    Quad* current = listHeads[numLists - 1];
    //if the exact key is not present we will return end
    if(find(k)==NULL){
        //iterate throught the row until the end 
            while(current->next!=nullptr){
                current=current->next;
            }
            //return the end
            return(current->entry);   
    }
    //if the exact key is present, return the next key
    else{
        //Search algorithm above, modified
        while (current->below != NULL) {
            current = current->below;			// drop down
            while(k >= current->next->entry->getKey()) {	// scan forward
                current = current->next;
            }
        }
        //end search algorithm at k
        //return the next next key, as it is the key greater than k
        return(current->next->entry);   
    }
}
SkipList::Entry* SkipList::lesserEntry(Key k){
    int numLists = listHeads.size();
    Quad* current = listHeads[numLists - 1];
    //if the exact key is not present we will return end
    if(find(k)==NULL){
        //iterate throught the row until the end 
        while(current->next!=nullptr){
            current=current->next;
        }
        //return the end
        return(current->entry);   
    }
    //if the exact key is present, return the previous key
    else{
        //Search algorithm above, modified
        while (current->below != NULL) {
            current = current->below;			// drop down
            while(k >= current->next->next->entry->getKey()) {	// scan forward
                current = current->next;
            }
        }
        //end search algorithm at value before k
        //If k is the first value
        if(current->entry->getKey()=="!!"){
            //iterate throught the row until the end 
            while(current->next!=nullptr){
                current=current->next;
            }
            //return the end
            return(current->entry); 
        }
        //otherwise, return the entry before k
        return(current->entry);
    }
}
SkipList::SkipList() : listHeads() {
    //just make 2 new levels
    makeNewLevelList();
    makeNewLevelList();
}

SkipList::~SkipList(){
    Quad* current;
    //iterate through and delete all the next's as long as they exist
    for(int i=listHeads.size()-1; i>-1; i--){
        current=listHeads[i];
        while(current->next!=nullptr){
            current=current->next;
            delete current->prev->entry;
            delete current->prev;
        }
        //delete our final pointer
        delete current->entry;
        delete current;
        //update the list
        listHeads.pop_back();
    }
}