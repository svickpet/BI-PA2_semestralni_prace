//
// Created by petra on 23.5.17.
//



//using namespace std;

#ifndef SEMESTRALKA_CONSUMABLE_H
#define SEMESTRALKA_CONSUMABLE_H

#include <string>
#include "Item.h"

/**
 * class representing consumable item in a game
 */
class Consumable : public Item{
private:
    int health;     /**<amount how much item increase player's health*/
public:
    /**
     * constructor
     */
    Consumable(){}

    /**
     * constructor
     * @param str string with information about item
     */
    Consumable(std::string& str);

    /**
     * virtual destructor
     */
    ~Consumable()= default;

    /**
     * overloaded operator <
     * @param consumable Consumable
     */
    bool operator < (const Consumable& consumable) const;

    /**
     * virtual getter returning how much item will affect player's health
     * @return number
     */
    int getHealth() const {return this->health;}

    /**
     * virtual method handling with a command eat
     * @return string with message for the player
     */
    std::string eat();
};

#endif //SEMESTRALKA_CONSUMABLE_H
