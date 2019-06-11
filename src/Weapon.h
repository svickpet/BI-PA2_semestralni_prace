//
// Created by petra on 23.5.17.
//

#ifndef SEMESTRALKA_WEAPON_H
#define SEMESTRALKA_WEAPON_H

#include <string>
#include "Item.h"
using namespace std;

/**
 * class representing a weapon
 */
class Weapon : public Item{
private:
    int strength;   /**<strength which will be added if equipped*/
public:
    /**
     * constructor
     */
    Weapon() = default;

    /**
     * constructor
     * @param line string with information about a weapon
     */
    Weapon(string& line);

    /**
     * virtual destructor
     */
    ~Weapon()= default;

    /**
     * overloaded operator <
     * @param w Weapon
     * @return bool
     */
    bool operator < (const Weapon& w) const;

    /**
     * const virtual getter returning strength
     * @return strength
     */
    int getStrength() const;

    /**
     * virtual method handling with the command eat
     * @return string with message for player
     */
    std::string eat();
};

#endif //SEMESTRALKA_WEAPON_H
