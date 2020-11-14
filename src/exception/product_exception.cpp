//
// Created by laimi on 25/10/2020.
//

#include "product_exception.h"


ProductDoesNotExist::ProductDoesNotExist(const std::string& name, float price):
    std::invalid_argument(name + ", costing " + std::to_string(price) + " euros, does not exist!\n"){
}

ProductDoesNotExist::ProductDoesNotExist(const std::string &name) :
    std::invalid_argument(name + " does not exist!\n"){
}

ProductDoesNotExist::ProductDoesNotExist(float price) :
    std::invalid_argument("There is no product costing " + std::to_string(price) + " euros!\n"){
}

ProductAlreadyExists::ProductAlreadyExists(const std::string &name, float price) :
    std::invalid_argument(name+", with price "+std::to_string(price)+" already exists!\n"){
}

ProductAlreadyExists::ProductAlreadyExists(const std::string &name) :
    std::invalid_argument(name+" already exists!\n") {
}

InvalidProductPosition::InvalidProductPosition(unsigned int position, unsigned int size) :
    std::invalid_argument(std::to_string(position) + " is an invalid position; should be between 0 and " + std::to_string(size-1) + "!\n"){
}
