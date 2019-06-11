#ifndef SEMESTRALKA_GAME_H
#define SEMESTRALKA_GAME_H

#include <vector>
#include <string>

#include "Location.h"
#include "Dialogue.h"
#include "ConsoleGUI.h"

/**
 * Class representing one game
 */
class Game{
private:

    vector<Location*> vLocations;   /**< vector of all locations in a game*/
    vector<Item*> vItems;           /**< vector of all types of items in a game*/
    vector<Character*> vCharacters; /**< vector of all characters in a game*/
    vector<Dialogue> vDialogues;    /**< vector of dialogues*/

    ConsoleGUI gui;                       /**<instance of GUI */
   // Command command;
    Character player;               /**<the only instance of player*/

    int currentLocation;            /**< number of current location*/

    /**
     * method inserting locations from a specified file
     * @param fileName a name of the file with locations
     * @return false if file doesn't exists, else true
     */
    bool insertLocationsFromFile(string fileName);

    /**
     * method inserting items from a specified file
     * @param fileName a name of the file with items
     * @return false if file doesn't exists, else true
     */
    bool insertItemsFromFile(string fileName);

    /**
     * method inserting characters from a specified file
     * @param fileName a name of the file with characters
     * @return false if file doesn't exists, else true
     */
    bool insertCharactersFromFile(string fileName);

    /**
     * method inserting dialogues from a specified file
     * @param fileName a name of the file with dialogues
     * @return false if file doesn't exists, else true
     */
    bool insertDialoguesFromFile(string fileName);

    /**
     * method finding Character in the vector of characters
     * @param attribute name od the character
     * @return pointer to founded character or null, if there is not one
     */
    Character*  findCharacter(string& attribute);

    /**
     * method finding Item in the vector of items
     * @param attribute name od the item
     * @return pointer to founded item or null, if there is not one
     */
    Item*       findItem(string & attribute);

    /**
     * method finding Location in the vector of locations
     * @param attribute name od the location
     * @return pointer to founded location or null, if there is not one
     */
    Location*   findLocation(string& attribute);

    /**
     * method founding out which Location is current
     * @return pointer of current Location
     */
    Location*   getCurrentLocation();

    /**
     * method handling with command fight
     * @param ch enemy
     */
    void fight(/*Character& ch1, */Character* ch); //TODO into Player class

    /**
     * method handling with the command show inventory,
     * showing items from player's inventory
     */
    void showInventory();

    /**
     * method handling with the command pickUp, inserting item
     * into player's inventory
     */
    void pickUp(string&);

    /**
     * method handling with the command lookAround, printing
     * information about location
     */
    void lookAround();

    /**
     * method handling with the command exit
     */
    void exit();

    /**
     * method handling with the command hi, letting player talk with character
     */
    void hi(string&);
    //void hi(Dialogue*);

    /**
     * method saving game into files
     */
    void saveGame();

    /**
     * method creating a player - name, statistics etc.
     */
    void createCharacter();

    /**
     * method parsing input into command and attribute
     * @param input player's input
     */
    vector<string> parseCommand(string& input);

public:
    /**
     * constructor
     */
    Game();

    /**
     * destructor
     */
    ~Game(){
        for (auto it = vItems.begin();
                it != vItems.end(); ++it){
            delete *it;
        }
        for (auto it = vLocations.begin();
             it != vLocations.end(); ++it){
            delete *it;
        }
        for (auto it = vCharacters.begin();
             it != vCharacters.end(); ++it){
            delete *it;
        }

    }

    /**
     * method loading saved game from files
     */
    void loadGame();

    /**
     * method creating new game with dialogs, items,
     * characters and locations from files.
     */
    void newGame();

    /**
     * method starting the game
     */
    void play();

    /**
     * winning method
     */
    void win();
};


#endif //SEMESTRALKA_GAME_H
