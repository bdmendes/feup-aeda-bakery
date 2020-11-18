//
// Created by laimi on 15/10/2020.
//

#include "product.h"

#include <utility>
#include <util/util.h>

const char* Cake::categoryStr[5] = {
        "General", "Pie", "Sponge", "Puff Pastry", "Crunchy Cake"
};

Product::Product(std::string name, float price) : _name(std::move(name)), _price(price) {}

Bread::Bread(std::string name, float price, bool small) : Product(std::move(name), price), _small(small) {}

Cake::Cake(std::string name, float price, enum CakeCategory category):
        Product(std::move(name), price), _category(category), _categoryStr(categoryStr[static_cast<int>(_category)]){
}

std::string Product::getName() const { return _name;}

float Product::getPrice() const { return _price;}

bool Bread::isSmall() const { return _small;}

CakeCategory Cake::getCategory() const { return _category;}

bool Product::operator==(const Product &p) const{
    return _name == p.getName() && _price == p.getPrice();
}

bool Product::operator<(const Product &p) const {
    return _name < p.getName();
}

bool Cake::operator==(const Cake &cake) const{
    return getName() == cake.getName() && getCategory() == cake.getCategory()
    && getPrice() == cake.getPrice();
}

void Cake::print(std::ostream& os) const {
    os << util::column(_name,true)
    << util::column(_categoryStr)
    << util::column(util::to_string(_price) + " euros");
}

std::vector<std::string> Cake::getCategories() {
    return std::vector<std::string>(categoryStr,categoryStr + 5);
}

bool Bread::operator==(const Bread &bread) const{
    return _name == bread.getName() && _price == bread.getPrice() && _small == bread.isSmall();
}

void Bread::print(std::ostream& os) const {
    os << util::column(_name,true)
       << util::column(_small ? "Small bread" : "Big bread")
       << util::column(util::to_string(_price) + " euros");
}


