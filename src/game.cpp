//
// Created by petra on 11.5.17.
//
#include <fstream>
#include <iostream>
#include <sstream>
#include <ncurses.h>
#include <unistd.h>
#include "game.h"
#include "Consumable.h"
#include "Weapon.h"


using namespace std;

Game::Game() {
}

bool Game::insertLocationsFromFile(string fLocation) {
    ifstream f;
    f.open(fLocation);
    string line;

    if (f.is_open()){
        vLocations.resize(0);
        while(getline(f, line)) {
            if (line[0] == '#') {continue;}
            Location* loc = new Location(line, vItems, vLocations,vCharacters);
            vLocations.push_back(loc);

            map<int,string> exits = loc->getExits();
            for(map<int,string>::const_iterator it = exits.begin(); it != exits.end(); it++) {
            }
        }
        f.close();

    }
    else {
        cout << "Soubor" + fLocation +  "nemohl byt nacten." << endl;
        return false;
    }
    return true;
}

bool Game::insertItemsFromFile(string fItems) {
    ifstream f;
    f.open(fItems);
    string line, part;

    stringstream ss;
    if (f.is_open()){
        vItems.resize(0);
        while(getline(f, line)) {
            if (line[0] == '#' || line == "") {continue;}
            ss.str(line);
            getline(ss, part, '|');
            getline(ss, part, '|');
            if(part == "consumable"){
                vItems.push_back(new Consumable(line));
            }
            if(part == "weapon"){
                vItems.push_back(new Weapon(line));
            }
        }
        f.close();
    }
    else {
        cout << "Soubor " << fItems << " nemohl byt nacten." << endl;
        return false;
    }
    return true;
}

void Game::play() {
    string commandLine;
    string str, command, attribute;
    vector<string> parsedCommand;

    //gui.deleteWin();
    //gui.newWinFce();
    gui.clearWin();

    gui.print(*vLocations[currentLocation-1],true);

    commandLine = gui.readInput();

    parsedCommand = parseCommand(commandLine);

    while (1) {

        command = parsedCommand[0];
        attribute = parsedCommand[1];

        if (command == "go"){
            Location * loc = findLocation(attribute);
            if(loc){
                gui.clearWin();
                gui.print(*loc,true);
            }
            else {
                gui.print("You cannot go there.\n");
            }
        }
        else if(command == "fight"){
            Character* tmp = findCharacter(attribute);
            if(tmp == nullptr){
                gui.print("You cannot fight with " + attribute + "\n");
            }
            else {fight(tmp);}

        }
        else if(command == "eat"){
            Item * item = findItem(attribute);
            if(item != nullptr){
                str = player.eat(item);
                gui.print(str);
            }
            else{
                str = "You cannot eat " + attribute + "\n";
                gui.print(str);
            }
        }
        else if(command == "show"){
            showInventory();
        }
        else if(command == "pick-up" || command == "pu"){
            pickUp(attribute);
        }
        else if(command == "look-around" || command == "la"){
            lookAround();
        }
        else if(command == "hi"){
            Character* tmp = findCharacter(attribute);
            if(tmp == nullptr){
                gui.print("You cannot talk with " + attribute + "\n");
            }
            else {hi(attribute);}
        }
        else if(command == "examine"){
            GameComponent * tmp = findItem(attribute);
            if(tmp == nullptr){
                tmp = findCharacter(attribute);
            }
            if(tmp == nullptr){
                gui.print("You cannot examine " + attribute + "\n");
            }
            else {
                str = tmp->examine();
                gui.print(str);
            }
        }
        else if(command == "exit") {
            exit();
            return;
        }
        else {
            str = "Try it again, " + player.getName() + ".\n";
            gui.print(str);
        }

        if(player.isDead()){
            return;
        }

        commandLine = gui.readInput();

        parsedCommand = parseCommand(commandLine);
    }
}

vector<string> Game::parseCommand(string & str) {
    vector<string> command;

    stringstream ss;
    str = gui.toLowerString(str);
    ss.str(str);
    //ss << str;
    string part;
    //gui.print(ss);

    if(getline(ss, part, ' ')) {

        //gui.print(part);
        command.push_back(part);
    }
    else{
        //gui.print(part);
        command.push_back("nothing");
        return command;
    }

    if(getline(ss, part)) {
        //gui.print(part);
        command.push_back(part);
    }
    else{
        command.push_back("second");
    }

    ss.clear();
    return command;
    //gui.print(part);


}

void Game::createCharacter() {
    string str, name;
    //char * input = new char();
    str = "What's your name, stranger?\n";
    gui.print(str);
    name = gui.readInput();
    //string name = input;

    str = "Let's play a game, " + name + ".\n";
    gui.print(str);

    player = Character(name,100,0,0);

}

void Game::fight( Character* ch2) {
    //
    string str;
    int attack = 0;

    str = "Fight has started!\n";
    gui.print(str);

    /* initialize random seed: */
    srand ((uint)time(NULL));

    while( 1) {
       /* str = "------------------------\n" + to_string(player.getHealth()) +
              "  " + to_string(ch2->getHealth()) +
              "\n------------------------\n";
        gui.print(str);*/

        //  player attacking
        attack = rand() % 30 + 1;
        attack += player.getStrength() - ch2->getDefence();
        if (attack <= 0) {gui.print("You've missed.\n");}
        else {
            if (attack > 20) { gui.print("Critical hit! "); }
            ch2->decreaseHealth(attack);
            str = "Enemy has lost " + to_string(attack) + " points of life.\n";
            gui.print(str);
        }
        if (ch2->getHealth() <= 0) {
            str = "Enemy is defeated.\n" + to_string(player.getHealth()) + " points of life has left.\n";

            gui.print(str);
            ch2->setDead();
           // cout << ch2->getName() << endl;
            break;
        }

        //  enemy attacking
        attack = rand() % 30 + 1;
        attack += ch2->getStrength() - player.getDefence();
        if (attack <= 0) {gui.print("Enemy's missed.");}
        else {
            if (attack > 20) { gui.print("Critical hit! "); }
            player.decreaseHealth(attack);
            str = "You have lost " + to_string(attack) + " points of life.\n";
            gui.print(str);
        }

        if (player.getHealth() <= 0) {
            str = "You are defeated.\nGAME OVER\n";
            player.setDead();
            gui.print(str);
            break;
        }

        usleep( 2 * 1000000 );

    }
}

bool Game::insertCharactersFromFile(string fCharacter) {
    ifstream f;
    //f.open("../examples/fCharacters.txt");
    f.open(fCharacter);
    string line;

    stringstream ss;

    if (f.is_open()) {
        vCharacters.resize(0);
        while (getline(f, line)) {
            if (line[0] == '#' || line == "") { continue; }
            //cout << "line CHAR je: " << line << endl;
            vCharacters.push_back(new Character(line,vItems,vDialogues));
        }
        f.close();
    }
    else{return false;}

 /*   for (int i = 0; i < (int)vCharacters.size(); i++){
        cout << "cout " << vCharacters[i] << endl;
    }*/

    return true;
}

void Game::showInventory() {

    stringstream ss;

    map<Item*,int> playerInventory = player.getInventory();

    for(map<Item*,int>::const_iterator it = playerInventory.begin();
            it != playerInventory.end(); ++it){
        ss << it->first->getName() << " (" << it->second << ")" << endl;
    }
    gui.print(ss);
}

void Game::pickUp(string &attribute) {

    string itemInLoc;

    map<Item*,int>::const_iterator it2;
    map<Item*,int> tmp = vLocations[currentLocation-1]->getItems();
    for (it2 = tmp.begin(); it2 != tmp.end();  ++it2){
        itemInLoc = it2->first->getName();
        itemInLoc = gui.toLowerString(itemInLoc);

        if(itemInLoc == attribute){
            player.putIntoInventory(it2->first,1);
            gui.print("You've picked up: " + it2->first->getName() + "\n");
            vLocations[currentLocation-1]->removeItem(it2->first);
            return;
        }
    }

    gui.print("You cannot pick up this item.\n");
}

Character* Game::findCharacter(string &attribute) {

    vector<Character*>::const_iterator it;

    string tmp;
    vector<Character*> v = getCurrentLocation()->getCharsInLoc();
    for( it = v.begin(); it != v.end(); ++it ){
        tmp = (*it)->getName();
        tmp = gui.toLowerString(tmp);
        if(attribute == tmp) {
            return *it;
        }
    }

    return nullptr;
}

Location* Game::getCurrentLocation() {
    return vLocations[currentLocation-1];
}

void Game::lookAround() {
    gui.print(*vLocations[currentLocation-1],false);
}

void Game::exit() {
    string str =  "Do you wish to save your current progress"
            " to continue the game later? (y/n)\n";
    gui.print(str);

    string choice;
    choice = gui.readInput();

    while(1) {

        if (choice == "y" || choice == "Y") {
            saveGame();
            gui.print("Game saved.\n");
            return;
        }
        else if (choice == "n" || choice == "N") {
            return;
        }
        else {
            gui.print("Please, choose \"y\" if you want to save your current progress"
                              "or \"n\" if you don't want.");
            choice = gui.readInput();
        }
    }
}

void Game::saveGame() {
    ofstream fout("./examples/player.save", ios::binary);
    ofstream foutLoc("./examples/fLocations.save");
    fout << currentLocation << "\n";
    fout << player.save() << endl;

    vector<Location*>::const_iterator it;
    for(it = vLocations.begin(); it != vLocations.end(); ++it){
        foutLoc << (*it)->save() << endl;
    }

    fout.close();
    foutLoc.close();
}

void Game::loadGame() {
    ifstream fin("./examples/player.save", ios::binary);
    string str;
    string currentLoc;

    getline(fin,currentLoc);
    currentLocation = stoi(currentLoc);

    fin >> str;
    fin.close();

    insertItemsFromFile("./examples/fItems.txt");
    insertCharactersFromFile("./examples/fCharacters.txt");
    insertLocationsFromFile("./examples/fLocations.save");

    player = Character(str,vItems,vDialogues);

}

void Game::newGame() {

    insertItemsFromFile("./examples/fItems.txt");
    insertDialoguesFromFile("./examples/fDialogues.txt");
    insertCharactersFromFile("./examples/fCharacters.txt");
    insertLocationsFromFile("./examples/fLocations.txt");

    currentLocation = 1;

    createCharacter();

}

bool Game::insertDialoguesFromFile(string fDialogues) {
    ifstream f;
    f.open(fDialogues);
    string line;
    string part, part2;
    string sentence;
    int id;
    int from, via, to;

    if(!f.is_open()){
        return false;
    }

    vDialogues.resize(0);

    while(getline(f,line) && line != ""){

        Dialogue dialogue;

        istringstream ss(line);
        vector<string> idParts;
        for (string each; getline(ss, each, '|');
             idParts.push_back(each));
        if(idParts[0] == "ID" && idParts[1] != ""){

            dialogue.setID(stoi(idParts[1]));

        }

        while(getline(f,line) && line != ""){
            istringstream split(line);
            vector<string> parts;
            for (string each; getline(split, each, '|');
                 parts.push_back(each));

            id = stoi(parts[0]);
            sentence = parts[1];
            dialogue.addSentenceToNpc(id,sentence);
        }
        while(getline(f,line) && line != ""){
            istringstream split(line);
            vector<string> parts;
            for (string each; getline(split, each, '|');
                 parts.push_back(each));

            id = stoi(parts[0]);
            sentence = parts[1];
            dialogue.addSentenceToPlayer(id,sentence);
        }
        while(getline(f,line) && line != ""){

            istringstream split(line);
            vector<string> parts;
            for (string each; getline(split, each, '|');
                 parts.push_back(each));

            from = stoi(parts[0]);
            via = stoi(parts[1]);
            to = stoi(parts[2]);
            dialogue.addEdge(from, via, to);

        }

        vDialogues.push_back(dialogue);

    }
    f.close();

    return true;
}

void Game::hi(string & name) {

    vector<Character*>::const_iterator it;
    string charName;
    bool charFound = false;;
    for(it = vCharacters.begin();
        it != vCharacters.end(); ++it){

        charName = (*it)->getName();
        if(gui.toLowerString(charName) == name){

            charFound = true;
            break;
        }
    }

    if(!charFound){return;}

    Dialogue * diag = &((*it)->getDialogue());

    if(diag->getID() == 0){
        gui.print("...\n");
        return;
    }

    int num = 0;


    while(1){
        Response res = diag->getResponse(num);
        gui.print(res);
        if(res.end){
            break;
        }

        string str;
        str = gui.readInput();

        num = res.choices[stoi(str,nullptr)-1].first;
    }
}


Item *Game::findItem(string &attribute) {
    bool itemFound = false;
    string tmp;

    map<Item*,int> inv = player.getInventory();
    map<Item*,int>::const_iterator it;
    for( it = inv.begin(); it != inv.end(); ++it ) {
        tmp = it->first->getName();
        tmp = gui.toLowerString(tmp);
        if (attribute == tmp) {
            itemFound = true;
            break;
        }
    }

    if(!itemFound){
        return nullptr;
    }

    return it->first;
}

Location *Game::findLocation(string &attribute) {
    map<int,string> mapOfLoc = vLocations[currentLocation-1]->getExits();
    map<int,string>::const_iterator it;
    for (it = mapOfLoc.begin(); it != mapOfLoc.end(); ++it) {
        if(gui.toLowerString(it->second) == attribute){
            currentLocation = it->first;
            return vLocations[it->first-1];
        }
    }
    return nullptr;
}

void Game::win() {
    gui.print("Congratulations. You won.\n");
}
