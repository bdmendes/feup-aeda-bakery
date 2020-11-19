
#include "product_exception.h"


ProductDoesNotExist::ProductDoesNotExist(const std::string& name, float price):
    std::invalid_argument(name + ", costing " + std::to_string(price) + " euros, does not exist!"){
}

ProductDoesNotExist::ProductDoesNotExist(const std::string &name) :
    std::invalid_argument(name + " does not exist!\n"){
}

ProductDoesNotExist::ProductDoesNotExist(float price) :
    std::invalid_argument("There is no product costing " + std::to_string(price) + " euros!"){
}

InvalidProductPosition::InvalidProductPosition(unsigned int position, unsigned long size) :
    std::invalid_argument(std::to_string(++position) + " is an invalid position; should be between 1 and " + std::to_string(size) + "!"){
}
