//
// Created by petra on 14.5.17.
//

#ifndef SEMESTRALKA_CONSOLEGUI_H
#define SEMESTRALKA_CONSOLEGUI_H

#include <iostream>
#include "Location.h"

/**
 * method representing console GUI
 */
class ConsoleGUI{
public:
    /**
     * method preparing the screen for the game
     */
    void initializeScreen();

    /**
     * const method printing welcoming message
     */
    void printWelcome() const;

    /**
     * const method printing menu
     */
    void printMenu() const;

    /**
     * const method printing info about the game
     */
    void printInfo() const;

    /**
     * method which clears console window
     */
    void clearWin();

    /**
     * method changing string into lowercase string
     * @return lowercase string
     */
    string toLowerString(string);

    /**
     * method reading user's input
     * @return user's input
     */
    string readInput();

    /**
     * const method printing stringstream
     * @param ss stringstream with a message to print
     */
    void print(std::stringstream& ss) const;

    /**
     * const method printing string
     * @param str string
     */
    void print(std::string str) const;

    /**
     * const method printing information of the location
     * @param loc Location
     * @param withName true if name of the location should be printed
     */
    void print(Location& loc, bool withName) const;

    /**
     * const method printing struct Response (sentence and next choices)
     * @param res Response should be printed
     */
    void print(Response& res) const;

    /**
     * const method printing text in bold
     * @param ss text
     */
    void printBold(std::stringstream& ss )const;

    /**
     * const method printing text in bold
     * @param str text
     */
    void printBold(std::string str )const;

    /**
     * const method printing text in bold
     * @param ss text
     */
    void printGreen(std::stringstream& ss )const;

    /**
     * const method printing text in bold
     * @param str text
     */
    void printGreen(std::string str )const;

    /**
     * const method printing text in bold
     * @param ss text
     */
    void printRed(std::stringstream& ss )const;

    /**
     * const method printing text in bold
     * @param str text
     */
    void printRed(std::string str )const;

    /**
     * const method printing text in bold
     * @param ss text
     */
    void printBlue(std::stringstream& ss )const;

    /**
     * const method printing text in bold
     * @param str text
     */
    void printBlue(std::string str )const;

    /**
     * const method printing text in bold
     * @param ss text
     */
    void printYellow(std::stringstream& ss )const;

    /**
     * const method printing text in bold
     * @param str text
     */
    void printYellow(std::string str )const;


};

#endif //SEMESTRALKA_CONSOLEGUI_H
