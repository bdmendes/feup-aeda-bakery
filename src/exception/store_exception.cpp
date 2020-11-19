//
// Created by up201906166 on 23/10/2020.
//

#include "store_exception.h"

StoreHasNoWorkers::StoreHasNoWorkers() :
    std::logic_error("This store has no workers!"){
}

LocationDoesNotExist::LocationDoesNotExist(const std::string &location):
    invalid_argument(location + " does not exist.") {
}

InvalidLocationPosition::InvalidLocationPosition(unsigned long position):
    invalid_argument(std::to_string(++position) + " is not a valid index.") {
}
