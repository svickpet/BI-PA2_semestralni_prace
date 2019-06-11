//
// Created by petra on 12.5.17.
//
#include <iostream>
#include "Item.h"


using namespace std;

ostream& operator << (ostream& os, const Item& item){
    item.print(os);
    return os;
}

void Item::print(ostream &os) const {
    os << "You see " << this->name;
}

bool Item::operator<(const Item &item) const {
    return (this->id < item.id);
}

