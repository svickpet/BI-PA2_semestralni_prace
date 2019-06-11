//
// Created by petra on 23.5.17.
//

#include <iostream>
#include <ncurses.h>
#include <sstream>
#include "Weapon.h"


Weapon::Weapon(string &line) {
    stringstream ss,ss2;
    ss.str(line);
    string part, num;
    // int i = 0;
    for(int i = 1; i<=5; ++i){
        getline(ss,part,'|');
        switch (i) {
            case 1: this->id = stoi(part, nullptr); break;
            case 3: this->name = part; break;
            case 4: this->description = part; break;
            case 5:
                ss2.str(part);
                getline(ss2,num,',');
                getline(ss2,num,',');
                this->strength = stoi(num, nullptr);
               /* getline(ss2,num,',');
                this->strength = stoi(num, nullptr);
                getline(ss2,num,',');
                this->defence = stoi(num, nullptr);*/
                break;
        }
    }
}

bool Weapon::operator<(const Weapon &c) const {
    return this->id < c.id;
}

int Weapon::getStrength() const  {
    return this->strength;
}

std::string Weapon::eat() {
    return "No, you really should not eat something you should fight with.\n";
}
