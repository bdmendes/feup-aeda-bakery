//
// Created by bdmendes on 29/10/20.
//

#include "person.h"

#include <utility>

Person::Person(std::string name, int tributaryNumber, Credential credential) :
        _name{std::move(name)}, _tributaryNumber{tributaryNumber}, _credential{ std::move(credential) } {
}

std::string Person::getName() const {
    return _name;
}

int Person::getTributaryNumber() const {
    return _tributaryNumber;
}

void Person::changeName(const std::string& name){
    _name = name;
}

Credential Person::getCredential() const {
    return _credential;
}

void Person::changeCredential(const Credential &credential) {
    if (_credential == credential) throw PersonSameCredentials();
    _credential = credential;
}