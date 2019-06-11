//
// Created by petra on 6.6.17.
//

#include <iostream>
#include "Dialogue.h"


using namespace std;

Dialogue::Dialogue(const Dialogue &d) {
    this->id = d.id;
    this->npc = d.npc;
    this->player = d.player;
    this->arr = d.arr;
    this->currentSentence = 1;
}

void Dialogue::addEdge(const int from, const int via, const int to) {

    std::pair<int,int> pairTmp = {via,to};

    if(from >= (int)arr.size()){
        arr.resize((uint)from+1);
    }

    arr[from].insert(pairTmp);

}

int Dialogue::getID() {
    return this->id;
}

void Dialogue::setID(int id) {
    this->id = id;
}

void Dialogue::print(ostream &os) const {
    os << "dialogue: " << this->id << endl;
    for(map<int,string>::const_iterator it = npc.begin();
        it != npc.end(); ++it){
        os << "..." <<it->first << ":" << it->second <<"..." << endl;
    }
}

Response Dialogue::getResponse(int choice) {

    //find Choice

    Response res;
    int num;
    string sentence;
    res.choices.resize(0);
    res.sentence = "...";
    res.end = false;

    map<int, int>::iterator it0;
    if(choice != 0) {
        it0 = arr[currentSentence].find(choice);
        this->currentSentence = it0->second;
    }
    else{
        currentSentence = 1;
    }

    map<int,string>::iterator it = npc.find(currentSentence);

    res.sentence = it->second;

    if(currentSentence >= (int)arr.size()){
        res.end = true;
        return res;
    }

    map<int,int> currentMap = arr[currentSentence];

    for(map<int,int>::const_iterator it2 = currentMap.begin();
        it2 != currentMap.end(); ++it2){
        num = it2->first;

        map<int,string>::iterator it3 = player.find(num);
        sentence = it3->second;
        res.choices.push_back({num,sentence});
    }

    return res;

}

ostream &operator<<(std::ostream &os, const Dialogue &dialogue)  {
    dialogue.print(os);
    return os;
}

void Dialogue::addSentenceToNpc(int num, string sentence) {
    npc.insert({num,sentence});
}
void Dialogue::addSentenceToPlayer(int num, string sentence){
    player.insert({num,sentence});
}
