//
// Created by Filipa on 10/25/2020.
//

#include "StoreExceptions.h"

StoreExceptions::StoreExceptions(std::string name) : _name(name){}


StoreHasNoWorkers::StoreHasNoWorkers(std::string name) : StoreExceptions(name){}

std::ostream & StoreHasNoWorkers::operator<<(std::ostream &out) {
    out << "Store "<< _name << " has no workers." << std::endl;
    return out;
}