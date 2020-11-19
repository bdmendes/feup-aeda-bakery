
#include "product_exception.h"


ProductDoesNotExist::ProductDoesNotExist(const std::string& name, float price):
    std::invalid_argument(name + ", costing " + std::to_string(price) + " euros, does not exist!"){
}

InvalidProductPosition::InvalidProductPosition(unsigned long position, unsigned long size) :
    std::invalid_argument(std::to_string(position + 1) + " is an invalid position; should be between 1 and " + std::to_string(size) + "!"){
}
