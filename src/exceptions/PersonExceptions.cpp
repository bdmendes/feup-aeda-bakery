//
// Created by Filipa on 10/25/2020.
//

#include "PersonExceptions.h"

PersonExceptions::PersonExceptions(std::string name, int tributaryNumber)
    : _name(name), _tributaryNumber(tributaryNumber){}


ClientDoesNotExist::ClientDoesNotExist(std::string name, int tributaryNumber) :
    PersonExceptions(std::move(name), tributaryNumber){}

std::ostream & ClientDoesNotExist::operator<<(std::ostream &out) {
    out << "Client (" << _name << ", " << _tributaryNumber << ") does not exist." << std::endl;
    return out;
}


WorkerDoesNotExist::WorkerDoesNotExist(std::string name, int tributaryNumber) :
    PersonExceptions(std::move(name), tributaryNumber){}

std::ostream & WorkerDoesNotExist::operator<<(std::ostream &out) {
    out << "Worker (" << _name << ", " << _tributaryNumber << " does not exist." << std::endl;
    return out;
}