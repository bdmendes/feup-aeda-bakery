//
// Created by laimi on 15/10/2020.
//

#include "product.h"

#include <utility>

std::set<std::string> Cake::availableCategories{"Pie", "Sponge Cake", "Puff Pastry Cake", "Crunchy"};

//CONSTRUCTORS

Product::Product(std::string name, float price) : _name(std::move(name)), _price(price) {}

Bread::Bread(std::string name, float price, bool small) : Product(std::move(name), price), _small(small) {}

Cake::Cake(std::string name, float price, std::string category) : Product(std::move(name), price), _category(std::move(category)){}


//GET METHODS

std::string Product::getName() const { return _name;}

float Product::getPrice() const { return _price;}

bool Product::operator==(const Product &p) const{
    return getName() == p.getName();
}

bool Bread::isSmall() const { return _small;}

bool Bread::operator==(const Bread &bread) const{
    return getName() == bread.getName() && isSmall() == bread.isSmall();
}

std::string Cake::getCategory() const { return _category;}


//ADD AND REMOVE CATEGORIES

void Cake::addCategory(const std::string &newCategory) {availableCategories.insert(newCategory);}

void Cake::removeCategory(const std::string &category) { availableCategories.erase(category);}


//OPERATORS OVERLOADING
bool Cake::operator==(const Cake &cake) const{
    return getName() == cake.getName() && getCategory() ==cake.getCategory();
}

