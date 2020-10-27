//
// Created by laimi on 25/10/2020.
//

#include "product_exception.h"


ProductDoesNotExist::ProductDoesNotExist(const std::string& name, float price):
    std::invalid_argument(name + ", costing " + std::to_string(price) + " euros, does not exist!"){
}
