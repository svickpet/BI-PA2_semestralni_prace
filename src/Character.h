//
// Created by petra on 11.5.17.
//

#ifndef SEMESTRALKA_CHARACTER_H
#define SEMESTRALKA_CHARACTER_H

#include "GameComponent.h"
#include "Item.h"
#include "Dialogue.h"

/**
 * class representing character
 */
class Character: public GameComponent{
private:
    int health;                         /**<health of a character*/
    int strength;                       /**<strength of a character*/
    int defence;                        /**<defence of a character*/
    std::map<Item*, int> inventory;     /**<inventory with item and amount*/
    Dialogue dialogue;                  /**<character's dialog*/

public:
    /**
     * construktor
     */
    Character();

    /**
     * copy constructor
     * @param ch class Character
     */
    Character(const Character& ch);

    /**
     * virtual destructor
     */
    virtual ~Character(){
    }

    /**
     * method creating new player
     * @param name string with name of a character
     * @param h health
     * @param s strength
     * @param d defence
     */
    Character(std::string & name,int h, int s, int d);

    /**
     * method creating Character
     * @param line line with information about character
     * @param v vector of items
     * @param d vector of dialogues
     */
    Character(std::string& line, std::vector<Item*> & v, std::vector<Dialogue> &d);

    /**
     * method decreasing health
     * @param num value which should be decreased
     */
    void    decreaseHealth(int num);

    /**
     * getter
     * @return health
     */
    int     getHealth(){return this->health;}

    /**
     * getter
     * @return strength
     */
    int     getStrength(){return strength;}

    /**
     * getter
     * @return defence
     */
    int     getDefence(){return defence;}

    /**
     * getter
     * @return dialogue
     */
    Dialogue&    getDialogue(){return dialogue;}

    /**
     * method changing character's health
     */
    void    changeHealth(int i){this->health += i; }

    /**
     * method changing character's strength
     * @return strength
     */
    void    changeStrength(int i){this->strength += i; }

    /**
     * getter
     * @return inventory
     */
    std::map<Item*,int>  getInventory(){return this->inventory;}

    /**
     * method putting item into player's inventory
     * @param i item
     * @param num amount of items should be put
     */
    void    putIntoInventory(Item * i, int num);

    /**
     * method removing item from inventory
     * @param item item should be removed
     */
    void    removeFromInventory(Item * item);

    /**
     * method inserting items into characters inventory
     * @param str line with ids of items
     * @param v vector of items in game
     */
    void insertItemsIntoInventory(std::string& str, std::vector<Item*>& v);

    /**
     * method definitely killing a character, RIP
     */
    void setDead();

    /**
     * method returning if character is dead
     * @return bool
     */
    bool isDead();

    /**
     * overloading method, operator <<
     * @param os ostream
     * @param ch character
     * @return ostream
     */
    friend std::ostream& operator << (std::ostream& os, const Character& ch);

    /**
     * const method printing
     * @param os ostream
     */
    void print(std::ostream & os) const;

    /**
     * method preparing information about character to save
     * @return string of information
     */
    std::string save();

    /**
     * method handling with command eat
     * @param i item which should be eaten
     * @return message for player
     */
    std::string eat(Item* i);
};

#endif //SEMESTRALKA_CHARACTER_H
