//
// Created by up201906166 on 23/10/2020.
//

#include "person_exceptions.h"

PersonDoesNotExist::PersonDoesNotExist(std::string name, int tributaryNumber) :
    _name(std::move(name)), _tributaryNumber(tributaryNumber){
}

std::ostream &PersonDoesNotExist::operator<<(std::ostream &out) {
    out << "Client does not exist: " << _name << ", " << _tributaryNumber << std::endl;
    return out;
}

