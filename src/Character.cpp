//
// Created by petra on 22.5.17.
//

#include "Character.h"

using namespace std;

Character::Character(){
}
Character::Character(std::string &name, int h, int s, int d) {
    this->id = 0;
    this->name = name;
    this->health = h;
    this->strength = s;
    this->defence = d;
}

Character::Character(std::string & line, std::vector<Item*> &vItems, std::vector<Dialogue> &vDialogues){
    stringstream ss, ss2;
    ss.str(line);
    string part;
    string num;
    for(int i = 1; i<=6; ++i){
        getline(ss,part,'|');
        switch (i) {
            case 1: this->id = stoi(part, nullptr); break;
            case 2: this->name = part; break;
            case 3: this->description = part; break;
            case 4:
                ss2.str(part);
                getline(ss2,num,',');
                this->health = stoi(num, nullptr);
                getline(ss2,num,',');
                this->strength = stoi(num, nullptr);
                getline(ss2,num,',');
                this->defence = stoi(num, nullptr);

                break;
            case 5:
                insertItemsIntoInventory(part,vItems);


                for(map<Item*,int>::iterator it = inventory.begin();
                    it != inventory.end(); ++it) {
                    //cout << it->first->getName() << endl;
                }
                break;
            case 6:
                if(part == "") break;
                int vSize = (int)vDialogues.size();
                for(int j = 0 ; j < vSize; ++j){
                    if (vDialogues[j].getID() == stoi(part)){
                        dialogue = (vDialogues[j]);
                        break;
                    }
                }
                break;
        }
    }

}

void Character::decreaseHealth(int hit) {
    this->health -= hit;
}

ostream& operator << (std::ostream& os, const Character& ch){
    ch.print(os);
    return os;
}

void Character::print(std::ostream &os) const{
    os << description << endl << endl;
}

void Character::setDead() {

    this->name = "Dead " + this->name;
}

Character::Character(const Character &ch) {
    this->id = ch.id;
    this->name = ch.name;
    this->description = ch.description;
    this->health = ch.health;
    this->strength = ch.strength;
    this->defence = ch.defence;
    this->inventory = ch.inventory;
}

string Character::save() {
    string str = to_string(id) + "|" + name + "|" + description + "|"
                 + to_string(health) + "," + to_string(strength) + ","
                 + to_string(defence) + "|";
    // save inventory
    int mSize = (int)inventory.size();
    int i = 0;
    for(map<Item*,int>::const_iterator it = inventory.begin();
            it != inventory.end(); ++it){
        str += to_string(it->first->getId()) + "x" + to_string(it->second);
        if(i+1 < mSize){
            str += ",";
            i++;
        }
    }
    return str;
}

void Character::insertItemsIntoInventory(std::string & line, std::vector<Item*> &vItems) {
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
            for(vector< Item* >::iterator it = vItems.begin(); it != vItems.end(); it++) {
                if((*it)->getId() == itemNum) {
                    putIntoInventory(*it,amountNum);
                }
            }
        }
    }
}

std::string Character::eat(Item *item) {

    int num = item->getHealth();

    string str;

    str = item->eat();

    if(str[0] == 'N' && str[1] == 'o'){
        return str;
    }
    changeHealth(num);
    removeFromInventory(item);

    if (health <= 0) {
        str = "GAME OVER";
        setDead();
    }
    else {
        str += "Your health: " + to_string(health) + "\n";
    }

    return str;

}

void Character::putIntoInventory(Item *i, int num){

    map<Item*,int>::iterator it = inventory.find(i);
    if(it == inventory.end()){
        pair<Item*,int> pairItem = {i,num};
        this->inventory.insert(pairItem);
    }
    else {
        it->second++;
    }

    strength += i->getStrength();
    defence += i->getDefence();
}

void Character::removeFromInventory(Item *item){
    map<Item*,int>::iterator it;
    for(it = inventory.begin(); it != inventory.end(); ++it){
        if(it->first == item){
            if(it->second == 1) {
                inventory.erase(it);
            }
            else {
                it->second--;
            }
            break;
        }
    }
}

bool Character::isDead() {
    stringstream ss;
    string str;
    ss.str(this->name);
    getline(ss,str,' ');
    //cout << "..." << str << "..." << endl;
    if(str == "Dead") {return true;}
    else {return false;}
}
