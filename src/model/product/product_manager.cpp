//
// Created by bdmendes on 29/10/20.
//

#include "product_manager.h"

#include <algorithm>
#include <utility>
#include <sstream>
#include <fstream>

ProductManager::ProductManager(): _products(){
}

bool ProductManager::has(Product *product) const {
    return std::find(_products.begin(), _products.end(), product) != _products.end();
}

void ProductManager::remove(Product *product) {
    auto position = std::find(_products.begin(), _products.end(), product);
    if (position == _products.end())
        throw ProductDoesNotExist(product->getName(),product->getPrice());
    _products.erase(position);
}

Product *ProductManager::get(unsigned int position) {
    if (position >= _products.size()) throw std::invalid_argument("Out of bounds product position");
    return _products.at(position);
}

std::vector<Product *> ProductManager::getAll() {
    return _products;
}

ProductManager::ProductManager(std::vector<Product *> stock) : _products(std::move(stock)){
}

void ProductManager::addBread(std::string name, float price, bool small) {
    _products.push_back(new Bread(std::move(name),price,small));
}

void ProductManager::addCake(std::string name, float price, CakeCategory category) {
    _products.push_back(new Cake(std::move(name),price,category));
}

void ProductManager::readCakes(std::ifstream &file) {
    //file.open("../feup-aeda-project/data/clients.txt");
    if(!file.is_open()){
        //TODO throw FileNotFound
    }
    else{
        std::string line;
        std::string name;
        float price;
        int cakeCategory;

        while(getline(file, line)){
            std::stringstream cake(line);
            cake>>name>>price>>cakeCategory;
            switch(cakeCategory){
                case
            }
            std::replace(name.begin(), name.end(), '-', ' ');
            addCake(name, price, cakeCategory);
        }
        file.close();
    }
}

void ProductManager::readBreads(std::ifstream &file) {

}

void ProductManager::writeBreads(std::ofstream &file) const {

}

void ProductManager::write(std::ofstream &file) const {

}
