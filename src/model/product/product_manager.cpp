//
// Created by bdmendes on 29/10/20.
//

#include "product_manager.h"

#include <algorithm>
#include <utility>
#include <util/util.h>

ProductManager::ProductManager(): _products(std::set<Product*, ProductSmaller>()){
}

ProductManager::ProductManager(std::set<Product*, ProductSmaller> stock) : _products(std::move(stock)){
}

bool ProductManager::has(Product *product) const {
    return std::find(_products.begin(), _products.end(), product) != _products.end();
}

Product* ProductManager::get(unsigned int position) {
    if (position >= _products.size()) throw InvalidProductPosition(position, _products.size());
    auto it = _products.begin(); std::advance(it, position);
    return *it;
}

std::set<Product*, ProductSmaller> ProductManager::getAll() {
    return _products;
}

Bread* ProductManager::addBread(std::string name, float price, bool small) {
    auto it = new Bread(std::move(name),price,small);
    _products.insert(it);
    return it;
}

Cake* ProductManager::addCake(std::string name, float price, CakeCategory category) {
    auto it = new Cake(std::move(name),price,category);
    _products.insert(it);
    return it;
}

void ProductManager::remove(Product *product) {
    auto position = std::find(_products.begin(), _products.end(), product);
    if (position == _products.end())
        throw ProductDoesNotExist(product->getName(),product->getPrice());
    _products.erase(position);
}

void ProductManager::print(std::ostream &os) const {
    int numSpaces = static_cast<int>(std::to_string(_products.size()).size() + 2);
    os << std::string(numSpaces,util::SPACE)
    << util::column("NAME", true)
    << util::column("CATEGORY")
    << util::column("UNIT PRICE") << "\n";

    int count = 1;
    for (const auto& p: _products){
        os << std::setw(numSpaces) << std::left << std::to_string(count++) + ". ";
        p->print(os);
        os << "\n";
    }
}




