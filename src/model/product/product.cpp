//
// Created by laimi on 15/10/2020.
//

#include "product.h"

#include <utility>
#include <algorithm>

//CONSTRUCTORS

Product::Product(std::string name, float price) : _name(std::move(name)), _price(price) {}

Bread::Bread(std::string name, float price, bool small) : Product(std::move(name), price), _small(small) {}

Cake::Cake(std::string name, float price, enum CakeCategory category):
        Product(std::move(name), price), _category(category){
}


//GET METHODS

std::string Product::getName() const { return _name;}

float Product::getPrice() const { return _price;}

bool Bread::isSmall() const { return _small;}

CakeCategory Cake::getCategory() const { return _category;}


//OPERATORS OVERLOADING

bool Product::operator==(const Product &p) const{
    return getName() == p.getName();
}

bool Product::operator<(const Product &p) const {
    return getName() < p.getName();
}

bool Cake::operator==(const Cake &cake) const{
    return getName() == cake.getName() && getCategory() ==cake.getCategory();
}

bool Bread::operator==(const Bread &bread) const{
    return getName() == bread.getName() && isSmall() == bread.isSmall();
}


