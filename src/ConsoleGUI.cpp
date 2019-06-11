//
// Created by petra on 14.5.17.
//

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "ConsoleGUI.h"

using namespace std;

void ConsoleGUI::initializeScreen() {

}

void ConsoleGUI::printWelcome() const {
    ifstream f("./examples/intro.txt");
    ifstream fPic("./examples/asciiWelcome.txt");

    string line;
    if (f.is_open()){
        while(getline(f,line)){
            //cout << line << endl;
            printBold(line);
            cout << endl;
        }
        f.close();
    }
    //else cout << "Soubor nemohl byt nacten..." << endl;

    if (fPic.is_open()){
        while(getline(fPic,line)){
            //cout << line << endl;
            printYellow(line);
            cout << endl;
        }
        cout << endl;
        fPic.close();
    }
}

void ConsoleGUI::clearWin() {
    system("clear");
}

void ConsoleGUI::printMenu() const {
    ifstream f;
    f.open("./examples/menu.txt");

    string line;
    int i = 1;

    while(getline(f,line)){
        cout << "[" << i << "] " << line << endl;
        i++;
    }
    f.close();
}

void ConsoleGUI::printInfo() const {
    ifstream rFile;
    int i = 1;

    rFile.open("./examples/info.txt");
    string line;
    if (rFile.is_open()){
        while(getline(rFile,line)){
            cout << line << endl;
            i++;
        }
        rFile.close();
    }
    else cout << "Soubor nemohl byt nacten." << endl;
}

void ConsoleGUI::print(std::stringstream &ss) const{
    string str = ss.str();
    print(str);
}

void ConsoleGUI::print(std::string str) const {
    cout << str;
}

void ConsoleGUI::print(Response& res) const{
    stringstream ss;
    ss << res.sentence << endl << endl;
    int vSize = (int)res.choices.size();
    for(int i = 0; i<vSize; ++i){
        ss << "[" << /*res.choices[i].first*/ i+1 << "] " << res.choices[i].second << endl;
    }
    print(ss);
}


void ConsoleGUI::printBold(std::string str) const{
    cout << "\033[1m" << str << "\033[0m";
}

void ConsoleGUI::printBold(std::stringstream & ss) const{
    string str = ss.str();
    printBold(str);
}

void ConsoleGUI::printGreen(std::string str) const{
    cout <<  "\033[32m" << str << "\033[0m";
}

void ConsoleGUI::printGreen(std::stringstream & ss) const{
    string str = ss.str();
    printGreen(str);
}

void ConsoleGUI::printRed(std::string str) const{
    cout <<  "\033[31m" << str << "\033[0m";
}

void ConsoleGUI::printRed(std::stringstream & ss) const{
    string str = ss.str();
    printRed(str);
}

void ConsoleGUI::printBlue(std::string str) const{
    cout <<  "\033[36m" << str << "\033[0m";
}

void ConsoleGUI::printBlue(std::stringstream & ss) const{
    string str = ss.str();
    printBlue(str);
}

void ConsoleGUI::printYellow(std::string str) const{
    cout <<  "\033[33m" << str << "\033[0m";
}

void ConsoleGUI::printYellow(std::stringstream & ss) const{
    string str = ss.str();
    printYellow(str);
}

void ConsoleGUI::print(Location &location, bool withName) const{
    stringstream ss;

    if(withName){
        ss << "\n||-------------------------------------" << endl;
        ss << "||  " << location.getName() << endl;
        ss << "||-------------------------------------\n" << endl;
        printBold(ss);
        ss.str(string());
    }

    string str;

    ifstream fin("./examples/ascii"+to_string(location.getId())+".txt");
    while(getline(fin,str)) {
        //ss << str << endl;
        printYellow(str);
        cout << endl;
    }
    ss << location << endl;

    print(ss);
}

std::string ConsoleGUI::readInput(){
    print(">");
    string commandLine;
    getline(cin, commandLine);
    toLowerString(commandLine);
    return commandLine;
}

std::string ConsoleGUI::toLowerString(std::string str){
    int strSize = str.size();
    for(int i =0; i<strSize; ++i){
        str[i] = tolower(str[i]);
    }
    //cout << "toLower: " << str << endl;
    return str;
}