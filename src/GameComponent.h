//
// Created by petra on 12.5.17.
//

#include <string>
#include <sstream>
#include <iostream>

#ifndef SEMESTRALKA_GAMECOMPONENT_H
#define SEMESTRALKA_GAMECOMPONENT_H

/**
 * Class representing a component of a game (location, character etc.)
 */

class GameComponent{
protected:
    int id;                     /**<component id*/
    std::string name;           /**<name of the component*/
    std::string description;    /**<component description*/

public:

    /**
     * Constructor
     */
    GameComponent():id(0),name(""),description(""){}

    /**
     * Virtual destructor
     */
    virtual ~GameComponent() = default;

    /**
     * getter returning id of the component
     * @return id int
     */
    int getId();

    /**
     * getter returning name of the component
     * @return name string
     */
    std::string getName() const;

    /**
     * overloaded operator <<, calls method print()
     * @param os ostream&
     * @param gc GameComponent
     * @return ostream
     */
    friend std::ostream& operator << (std::ostream &os , const GameComponent gc);

    /**
     * method printing information about component, sending it into ostream
     * @param ostream&
     */
    virtual void print(std::ostream&) const;

    /**
     * method handling with the command examine
     * @return string with information about the component,
     * default information is name and description
     */
    virtual std::string examine();

    /**
     * method handling with the command eat
     * @return string with default message for the player
     */
    virtual std::string eat();

};

#endif //SEMESTRALKA_GAMECOMPONENT_H
