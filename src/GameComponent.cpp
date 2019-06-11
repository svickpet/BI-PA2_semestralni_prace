//
// Created by petra on 6.6.17.
//
#include <string>

#include "GameComponent.h"


std::string GameComponent::examine() {
    std::stringstream ss;
    ss << name << std::endl << description << std::endl;
    return ss.str();
}

std::ostream &operator<<(std::ostream &os, const GameComponent gc) {
    gc.print(os);
    return os;
}

std::string GameComponent::eat() {
    return "You should not eat something like this.\n";
}

int GameComponent::getId() {
    return this->id;
}

std::string GameComponent::getName() const {
    return this->name;
}

void GameComponent::print(std::ostream &ostream) const {

}
