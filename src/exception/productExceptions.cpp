//
// Created by laimi on 25/10/2020.
//

#include "productExceptions.h"


ProductDoesNotExist::ProductDoesNotExist(std::string name, float price): _name(std::move(name)), _price(price) {}

std::ostream &ProductDoesNotExist::operator<<(std::ostream &out) {
    out << "Product " << _name <<" with the price "<< _price <<"does not exists.\n";
    return out;
}

std::string ProductDoesNotExist::getName() const {
    return _name;
}

float ProductDoesNotExist::getPrice() const {
    return _price;
}

CakeDoesNotExist::CakeDoesNotExist(std::string name, float price, std::string category) : ProductDoesNotExist(name, price), _category(category){}

std::ostream &CakeDoesNotExist::operator<<(std::ostream &out) {
    out << getName() <<" with the price "<< getPrice() <<" and from the category "<<_category<<" does not exists.\n";
    return out;
}


BreadDoesNotExist::BreadDoesNotExist(std::string name, float price) : ProductDoesNotExist(name, price){}

std::ostream &BreadDoesNotExist::operator<<(std::ostream &out) {
    out << getName() <<" with the price "<< getPrice() <<"does not exists.\n";
}


