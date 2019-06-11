//
// Created by petra on 11.5.17.
//

#ifndef SEMESTRALKA_LOCATION_H
#define SEMESTRALKA_LOCATION_H

#include <string>
#include <list>
#include <set>
#include <map>
#include <vector>
#include "GameComponent.h"

#include "Item.h"
#include "Character.h"

using namespace std;

/**
 * class representing a location in a game
 */
class Location : public GameComponent{
private:
    map<Item*, int> ItemsAmount;    /**<map of items and their amount*/
    map<int,string> exits;          /**<map of exits and text which should be showed*/
    vector<Character*> charsInLoc;  /**<vector of characters in a location*/

public:
    /**
     * constructor
     */
    Location() = default;

    /**
     * constructor
     * @param line string with information about location
     * @param items vector of items in the game
     * @param locations vector of locations in the game
     * @param characters vector of characters in the game
     */
    Location(string& line, vector<Item*>& items, vector<Location*>& locations, vector<Character*>& characters);

    /**
     * virtual destructor
     */
    ~Location();

    /**
     * method inserting items into location
     * @param str string with ids of items
     * @param items vector of items in the game
     */
    void insertItems(string & str, vector<Item*> &items);

    /**
     * method inserting exits into location
     * @param str string with ids of next locations
     */
    void insertExits(string & str);

    /**
     * method inserting characters into location
     * @param str string with ids of characters
     * @param characters vector of characters in the game
     */
    void insertCharacters(string& str, vector<Character*>& characters);

    /**
     * const method printing location
     * @param os ostream
     */
    void print(std::ostream& os) const;

    /**
     * overloaded operator <<
     * @param os ostream
     * @param location Location
     * @return ostream
     */
    friend ostream& operator << (ostream& os, const Location& location);

    /**
     * overloaded operator <
     * @param location Location
     * @return bool
     */
    bool operator < (const Location& location) const;

    /**
     * getter returning exits
     * @return map with number and string
     */
    map<int,string> getExits() const {return exits;}

    /**
     * getter returning items in location
     * @return map of items and their amount
     */
    map<Item*,int>  getItems() const;

    /**
     * method removing item from the location
     * @param item item which should be removed
     */
    void            removeItem(Item* item);

    /**
     * getter returning characters in loc
     * @return vector of characters in loc
     */
    vector<Character*>  getCharsInLoc() const {return this->charsInLoc;}

    /**
     * const method preparing location to saving
     * @return string with information about location
     */
    string save() const;
};

#endif //SEMESTRALKA_LOCATION_H
