//
// Created by bdmendes on 14/11/20.
//

#include "boss.h"

#include <utility>

Boss::Boss(std::string name, int taxID, Credential credential) :
    Person(std::move(name), taxID, std::move(credential)) {
}
