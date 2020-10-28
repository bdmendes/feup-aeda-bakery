//
// Created by laimi on 25/10/2020.
//

#include "product_exception.h"


ProductDoesNotExist::ProductDoesNotExist(const std::string& name, float price):
    std::invalid_argument(name + ", costing " + std::to_string(price) + " euros, does not exist!"){
}
ProductDoesNotExist::ProductDoesNotExist(const std::string &name) :
        std::invalid_argument(name + " does not exist!"){}

ProductDoesNotExist::ProductDoesNotExist(float price) :
        std::invalid_argument("There is no product costing " + std::to_string(price) + " euros!"){}

ProductAlreadyExists::ProductAlreadyExists(const std::string &name, float price) :
        std::invalid_argument(name+", with price "+std::to_string(price)+" already exists!"){}

ProductAlreadyExists::ProductAlreadyExists(const std::string &name) :
        std::invalid_argument(name+" already exists!") {}
