//
// Created by petra on 13.5.17.
//


#ifndef SEMESTRALKA_DIALOGUE_H
#define SEMESTRALKA_DIALOGUE_H

#include <vector>
#include <map>
//#include <cstdlib>
#include <string>

/**
 * struct representing a sentence of a character and next choices
 */
struct Response{
    std::string sentence;                               /**<sentence*/
    std::vector<std::pair<int,std::string>> choices;    /**<choices*/
    bool end;                           /**<true if sentence is last*/
};

/**
 * class representing a dialog
 */
class Dialogue {
private:
    int id;                                 /**<id*/
    int currentSentence;                    /**<current sentence in dialog*/
    std::map<int,std::string> npc;          /**<sentences of npc*/
    std::map<int,std::string> player;       /**<sentences of player*/
    std::vector<std::map<int,int>> arr;     /**<graph of dialog*/


public:
    /**
     * constructor
     */
    Dialogue() : id(0),currentSentence(1){ }

    /**
     *
     */
  /*  Dialogue(int id) {
        this->id = id;
    }*/


    /**
     * copy constructor
     * @param d dialogue
     */
    Dialogue(const Dialogue & d);

    /**
     * getter
     * @return id
     */
    int getID();

    /**
     * setter
     * @param id id
     */
    void setID(int id);

    /**
     * method inserting sentence into map of npc's sentences
     * @param num id
     * @param sentence string with sentence
     */
    void addSentenceToNpc(int num, std::string sentence);

    /**
     * method inserting sentence into map of player's sentences
     * @param num id
     * @param sentence string with sentence
     */
    void addSentenceToPlayer(int num, std::string sentence);

    /**
     * method finding needed response
     * @param choice number of player's choice
     * @return struct Response
     */
    Response getResponse(int choice);

    /**
     * method adding edge into graph of character's sentences
     * @param from sentence
     * @param via player's choice
     * @param to npc's response
     */
    void addEdge(const int from, const int via, const int to);

    /**
     * overloading method, operator <<
     * @param os ostream
     * @param dialogue dialogue
     * @return ostream
     */
    friend std::ostream& operator << (std::ostream& os, const Dialogue& dialogue);

    /**
     * const method printing dialogue
     * @param os ostream
     */
    void print(std::ostream & os) const;


};

#endif //SEMESTRALKA_DIALOGUE_H
