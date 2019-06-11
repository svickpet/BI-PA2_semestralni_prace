#include <iostream>
#include <fstream>
#include <string>
//#include <ncurses.h>

#include "game.h"


using namespace std;

//TODO clean
//TODO createCharacter - better

//TODO class Player?
//TODO command help?


int main() {

    ConsoleGUI gui;
    int ch;
    string input;
    Game game;
    gui.initializeScreen();
    gui.clearWin();

    gui.printWelcome();
    gui.printMenu();

    while(1) {
        getline(cin,input);
        ch = stoi(input);
        switch (ch) {
            case 1:
                game.newGame();
               // gui.deleteWin();
                //gui.newWin();
                game.play();
                //game.end();
                return 0;
            case 2:
                game.loadGame();
                game.play();
                //game.end();
                return 0;
            case 3:
                gui.clearWin();
                gui.printInfo();
                getline(cin,input);
                while(input != ""){
                    getline(cin,input);
                }
                gui.printMenu();
                break;
            default:
                cout << "Please, try it again." << endl;
                break;
        }
    }
    return 0;
}