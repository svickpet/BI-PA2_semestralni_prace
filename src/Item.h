//
// Created by petra on 12.5.17.
//

#ifndef SEMESTRALKA_ITEM_H
#define SEMESTRALKA_ITEM_H

#include "GameComponent.h"

//using namespace std;

/**
 * class representing an item in a game
 */
class Item : public GameComponent{
public:
    /**
     * constructor
     */
    Item() = default;
    //Item(string&);

   /*
    virtual ~Item(){}
*/

    /**
     *const method printing information about an item
     *@param os ostream
     */
    void print(std::ostream& os) const;

    /**
     * overloaded operator <<
     * @param os ostream
     * @param item Item
     */
    friend std::ostream& operator << (std::ostream& os, const Item& item);

    /**
     * overloaded operator <
     * @param item Item
     * @return bool
     */
    bool operator < (const Item& item) const;

    /**
     * virtual getter returning how much item will affect player's health
     * @return health 0 - default behavior
     */
    virtual int getHealth() const {return 0;}

    /**
     * virtual getter returning how much item will affect player's strength
     * @return strength 0 - default behavior
     */
    virtual int getStrength() const {return 0;}

    /**
     * virtual getter returning how much item will affect player's defence
     * @return defence 0 - default behavior
     */
    virtual int getDefence() const {return 0;}
};

#endif //SEMESTRALKA_ITEM_H
