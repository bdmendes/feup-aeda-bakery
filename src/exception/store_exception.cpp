//
// Created by up201906166 on 23/10/2020.
//

#include "store_exception.h"

StoreDoesNotExist::StoreDoesNotExist(const std::string& name) :
    std::invalid_argument(name + " Store does not exist!\n"){
}

StoreAlreadyExists::StoreAlreadyExists(const std::string &name) :
    std::logic_error(name + " Store already exists!\n") {
}

StoreHasNoWorkers::StoreHasNoWorkers() :
    std::logic_error("This store has no workers!\n"){
}