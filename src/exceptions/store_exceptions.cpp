//
// Created by up201906166 on 23/10/2020.
//

#include "store_exceptions.h"

StoreDoesNotExist::StoreDoesNotExist(const std::string& name) :
    std::invalid_argument(name + " store does not exist!"){
}

StoreAlreadyExists::StoreAlreadyExists(const std::string &name) :
    logic_error(name + " store already exists!") {
}
