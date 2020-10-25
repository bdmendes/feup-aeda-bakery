//
// Created by up201906166 on 23/10/2020.
//

#include "person_exceptions.h"

PersonDoesNotExist::PersonDoesNotExist(std::string name, int tributaryNumber) :
    _message(name + " does not exist!\n"){
}

std::ostream &PersonDoesNotExist::operator<<(std::ostream &out) {
    out << _message;
    return out;
}

PersonDoesNotExist::PersonDoesNotExist(std::string name) {

}

