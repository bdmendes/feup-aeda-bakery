//
// Created by bdmendes on 14/11/20.
//

#include "boss.h"

#include <utility>

const char* Boss::DEFAULT_USERNAME = "boss";
const char* Boss::DEFAULT_PASSWORD = "boss";

Boss::Boss(std::string name, int taxID, Credential credential) :
    Person(std::move(name), taxID, std::move(credential)) {
}

Credential Boss::getDefaultCredential() {
    return {DEFAULT_USERNAME, DEFAULT_PASSWORD};
}
