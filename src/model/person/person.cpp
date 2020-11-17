//
// Created by bdmendes on 29/10/20.
//

#include "person.h"

#include <utility>

const int Person::DEFAULT_TAX_ID = 999999999;

Person::Person(std::string name, int taxID, Credential credential) :
        _name(std::move(name)), _taxID{taxID}, _credential{std::move(credential) }, _logged(false) {
    if (credential.isReserved()) throw InvalidCredential(_credential.username);
}

std::string Person::getName() const {
    return _name;
}

int Person::getTaxId() const {
    return _taxID;
}

Credential Person::getCredential() const {
    return _credential;
}

void Person::setName(const std::string& name){
    if(_name == name) throw InvalidPersonNameChange();
    _name = name;
}

void Person::setCredential(const Credential &credential) {
    if (_credential == credential) throw InvalidPersonCredentialChange();
    if (_credential.isReserved()) throw InvalidCredential(_credential.username);
    _credential = credential;
}

bool Person::operator<(const Person &p2) const {
    return _name < p2.getName();
}

bool Person::operator==(const Person &p2) const {
    if (p2.getTaxId() != DEFAULT_TAX_ID) return _taxID == p2.getTaxId();
    else return _taxID == p2.getTaxId() && _name == p2.getName();
}

bool Person::isLogged() const {
    return _logged;
}

void Person::setLogged(bool logged) {
    if (logged && _logged) throw std::invalid_argument("Person is already logged in!");
    if (!logged && !_logged) throw std::invalid_argument("Person is already logged out!");
    _logged = logged;
}

void Person::setTaxID(int taxID) {
    _taxID = taxID;
}
