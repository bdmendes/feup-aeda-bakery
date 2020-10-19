//
// Created by laimi on 15/10/2020.
//

#include "Product.h"

#include <utility>

std::set<std::string> Cake::availableCategories = {"Pie", "Sponge Cake", "Puff Pastry Cake", "Crunchy"};

//CONSTRUCTORS

Product::Product(std::string name, float price) : _name(std::move(name)), _price(price) {}

Bread::Bread(std::string name, float price, bool small) : Product(name, price), _small(small) {}

Cake::Cake(std::string name, float price, std::string category) : Product(name, price), _category(std::move(category)){}


//GET METHODS

std::string Product::getName() const { return _name;}

float Product::getPrice() const { return _price;}

bool Bread::isSmall() const { return _small;}

std::string Cake::getCategory() const { return _category;}


//ADD AND REMOVE CATEGORIES

void Cake::addCategory(const std::string &newCategory) {availableCategories.insert(newCategory);}

void Cake::removeCategory(const std::string &category) { availableCategories.erase(category);}


//OPERATORS OVERLOADING
bool Cake::operator==(const Cake &cake) {
    return (_category==cake.getCategory());
}
//adicionar possíveis operadores depois de acordo com as necessidades

