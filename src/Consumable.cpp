//
// Created by petra on 23.5.17.
//

#include <iostream>
#include <sstream>
#include "Consumable.h"

using namespace std;

Consumable::Consumable(std::string &line) {
    stringstream ss,ss2;
    ss.str(line);
    string part, num;
    for(int i = 1; i<=5; ++i){
        getline(ss,part,'|');
        switch (i) {
            case 1: this->id = stoi(part, nullptr); break;
            case 3: this->name = part;
                break;
            case 4: this->description = part; break;
            case 5:
                ss2.str(part);
                getline(ss2,num,',');
                this->health = stoi(num, nullptr);
                break;
        }
    }
}

bool Consumable::operator<(const Consumable &c) const {
    return this->id < c.id;
}

std::string Consumable::eat() {
    int num = health;

    std::string str;
    if(num < 0){str = "You've lost ";}
    else if(num > 0){str = "You've received ";}
    if(num < 0) {num *= -1;}
    str += std::to_string(num) + " points of life.\n";

    return str;
}
