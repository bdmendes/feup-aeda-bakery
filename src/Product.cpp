//
// Created by laimi on 15/10/2020.
//

#include "Product.h"

//CONSTRUCTORS

Product::Product(const std::string &name, float price) : _name(name), _price(price) {}

Bread::Bread(const std::string &name, float price, bool small) : Product(name, price), _small(small) {}

Cake::Cake(const std::string &name, float price, std::string firstFlavour, std::string secondFlavour) : Product(name, price),
        _firstFlavour(firstFlavour), _secondFlavour(secondFlavour) {

}

//GET METHODS

std::string Product::getName() const { return _name;}

float Product::getPrice() const { return _price;}

bool Bread::isSmall() const { return _small;}

std::string Cake::getFirstFlavour() const { return _firstFlavour;}

std::string Cake::getSecondFlavour() const { return _secondFlavour;}

//ADD AND REMOVE FLAVOURS

void Cake::addFlavour(const std::string flavourName) { FLAVOURS.insert(flavourName);}

void Cake::removeFlavour(const std::string flavourName) { FLAVOURS.erase(flavourName);}


