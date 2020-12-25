
#include "person.h"
#include "exception/person_exception.h"

const unsigned long Person::DEFAULT_TAX_ID = 999999999;

Person::Person(std::string name, unsigned long taxID, Credential credential, PersonRole role) :
        _name(std::move(name)), _taxID{taxID}, _credential{std::move(credential) }, _logged(false),
        _role(role) {
    if (_credential.isReserved()) throw InvalidCredential();
}

std::string Person::getName() const {
    return _name;
}

unsigned long Person::getTaxId() const {
    return _taxID;
}

Credential Person::getCredential() const {
    return _credential;
}

void Person::setName(const std::string& name){
    _name = name;
}

void Person::setCredential(const Credential &credential) {
    if (credential.isReserved()) throw InvalidCredential();
    _credential = credential;
}

bool Person::operator<(const Person &p2) const {
    if ((p2.getTaxId() != DEFAULT_TAX_ID || _taxID != DEFAULT_TAX_ID) && _taxID != p2.getTaxId()){
        return _taxID < p2.getTaxId();
    }
    else return _name < p2.getName();
}

bool Person::operator==(const Person &p2) const {
    if (p2.getTaxId() != DEFAULT_TAX_ID || _taxID != DEFAULT_TAX_ID) return _taxID == p2.getTaxId();
    else return _name == p2.getName();
}

bool Person::isLogged() const {
    return _logged;
}

void Person::setLogged(bool logged) {
    _logged = logged;
}

void Person::setTaxID(unsigned long taxID) {
    _taxID = taxID;
}

PersonRole Person::getRole() {
    return _role;
}
