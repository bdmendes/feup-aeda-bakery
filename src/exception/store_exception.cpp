//
// Created by up201906166 on 23/10/2020.
//

#include "store_exception.h"

StoreDoesNotExist::StoreDoesNotExist(const std::string& name) :
    std::invalid_argument(name + " Store does not exist!"){
}

StoreAlreadyExists::StoreAlreadyExists(const std::string &name) :
    logic_error(name + " Store already exists!") {
}

StoreExceptions::StoreExceptions(std::string name) : _name(name){}

StoreHasNoWorkers::StoreHasNoWorkers(std::string name) : StoreExceptions(name){}

std::ostream & StoreHasNoWorkers::operator<<(std::ostream &out) {
    out << "Store "<< _name << " has no workers." << std::endl;
    return out;
}