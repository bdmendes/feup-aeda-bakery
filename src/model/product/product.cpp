//
// Created by laimi on 15/10/2020.
//

#include "product.h"

#include <utility>
#include <util/util.h>

Product::Product(std::string name, float price) : _name(std::move(name)), _price(price) {}

Bread::Bread(std::string name, float price, bool small) : Product(std::move(name), price), _small(small) {}

Cake::Cake(std::string name, float price, enum CakeCategory category):
        Product(std::move(name), price), _category(category){
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
    return _name == cake.getName() && _price == cake.getPrice() && _category == cake.getCategory();
}

void Cake::print(std::ostream& os) const {
    const std::array<std::string,5> cakeCategories = {
            "General", "Pie", "Sponge", "Puff Pastry", "Crunchy Cake"
    };
    const std::string category = cakeCategories.at(static_cast<unsigned long>(_category));

    os << util::column(_name,true)
    << util::column(category)
    << util::column(util::to_string(_price) + " euros");
}

bool Bread::operator==(const Bread &bread) const{
    return _name == bread.getName() && _price == bread.getPrice() && _small == bread.isSmall();
}

void Bread::print(std::ostream& os) const {
    os << util::column(_name,true)
       << util::column(_small ? "Small bread" : "Big bread")
       << util::column(util::to_string(_price) + " euros");
}


