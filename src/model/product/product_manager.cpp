//
// Created by bdmendes on 29/10/20.
//

#include "product_manager.h"

#include <algorithm>
#include <utility>

ProductManager::ProductManager(): _products(std::set<Product*, ProductSmaller>()){
}

ProductManager::ProductManager(std::set<Product*, ProductSmaller> stock) : _products(std::move(stock)){
}

bool ProductManager::has(Product *product) const {
    return std::find(_products.begin(), _products.end(), product) != _products.end();
}

Product* ProductManager::get(unsigned int position) {
    if (position >= _products.size()) throw std::invalid_argument("Out of bounds product position");
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

Product* ProductManager::remove(Product *product) {
    auto position = std::find(_products.begin(), _products.end(), product);
    if (position == _products.end())
        throw ProductDoesNotExist(product->getName(),product->getPrice());
    _products.erase(position);
    return product;
}



