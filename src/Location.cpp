//
// Created by petra on 11.5.17.
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include "Location.h"
#include "game.h"

using namespace std;

Location::Location(string &line, vector<Item*> &vItem, vector<Location*>& , vector<Character*>& vChar){

    stringstream ss, ss2;
    ss.str(line);
    string part;
    string exit;

    for(int i = 1; i<=6; ++i){
        getline(ss,part,'|');

        switch (i) {
            case 1: this->id = stoi(part, nullptr); break;
            case 2: this->name = part; break;
            case 3: this->description = part; break;
            case 4:
                ss2.str(part);
                while (getline(ss2,exit,',')) {
                    insertExits(exit);
                }
                break;
            case 5: insertItems(part, vItem ); break;
            case 6: insertCharacters(part, vChar); break;
        }
    }
}

ostream& operator << (ostream& os, const Location & location){
    location.print(os);
    return os;
}

void Location::print(ostream &os) const{

    os << description << endl << endl;

    for(map< Item*, int >::const_iterator it = ItemsAmount.begin(); it != ItemsAmount.end(); it++) {
        if(it->second > 0) {
            os << *(it->first) << " (" << it->second << ")" << endl;
        }
    }

    int numOfWays =(int)exits.size();
    if(numOfWays == 1){
        os << endl << "There is 1 way:" << endl;
    }
    else if(numOfWays > 1){
        os << endl << "There are " << numOfWays << " ways:" << endl;
    }

    for(map<int,string>::const_iterator it = exits.begin(); it != exits.end(); it++) {
        os << "--> " << it->second << endl;
    }

    int numOfChars = (int)charsInLoc.size();
    if(numOfChars > 1) {
        os << endl << "There are some characters:" << endl;
    }
    else if (numOfChars == 1) {
        os << endl << "There is one character:" << endl;
    }

    for(vector<Character*>::const_iterator it = charsInLoc.begin(); it != charsInLoc.end(); it++) {
        os << (*it)->getName() << endl;
    }

}

void Location::insertItems(string & line, vector<Item*> &vItem){

    stringstream ss;
    ss.str(line);
    string part;
    string item;
    string amount;
    int itemNum;
    int amountNum;

    int i = 0;
    while (getline(ss,part,',')){
        i++;
        stringstream ssAmount;
        ssAmount.str(part);
        getline(ssAmount, item, 'x');
        itemNum = stoi(item, nullptr);
        if(getline(ssAmount, amount, 'x')){
            amountNum = stoi(amount, nullptr);
            ItemsAmount[vItem[itemNum - 1]] = amountNum;
        }
        else {
            ItemsAmount[vItem[itemNum - 1]] = 1;
        }
    }
}


void Location::insertExits(string &line){
    stringstream ss;
    string num, desc;
    pair<int,string> where;

    ss.str(line);
    num = desc = "";
    getline(ss,num,'-');
    getline(ss,desc,'-');
    where = {stoi(num, nullptr), desc};
    this->exits.insert(where);
}

bool Location::operator<(const Location &location) const {
    return (this->id < location.id);
}

map<Item*, int> Location::getItems() const {
    return ItemsAmount;
}

void Location::insertCharacters(string &line, vector<Character*> &vChar) {
    stringstream ss;
    string part;

    ss.str(line);
    while(getline(ss,part,',')){
        Character *newChar = new Character(*vChar[stoi(part, nullptr)-1]);
        charsInLoc.push_back(newChar);

    }
}

void Location::removeItem(Item * item) {
    for(map< Item*, int >::iterator it = ItemsAmount.begin(); it != ItemsAmount.end(); it++) {
        if(it->first == item) {
            if(it->second <= 1){
                ItemsAmount.erase(it);
            }
            else {
                it->second -= 1;
            }
            break;
        }
    }
}

string Location::save() const {
    string str = to_string(id) + "|" + name + "|" + description + "|";
    int mSize;
    int i = 0;


    mSize = (int)exits.size();

    for (map<int,string>::const_iterator it = exits.begin();
         it != exits.end(); ++it){
        str += to_string(it->first) + "-" + it->second;
        if(i+1 < mSize){
            str += ",";
            i++;
        }
    }

    str += "|";

    i = 0;
    mSize = (int)ItemsAmount.size();

    for (map<Item*,int>::const_iterator it = ItemsAmount.begin();
            it != ItemsAmount.end(); ++it){
        str += to_string(it->first->getId());
        if(i+1 < mSize){
            str += ",";
            i++;
        }
    }
    str += "|";
    return str;
}

Location::~Location() {
    for(auto it = charsInLoc.begin(); it != charsInLoc.end(); ++it){
        delete *it;
    }
}
