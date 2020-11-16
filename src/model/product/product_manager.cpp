//
// Created by bdmendes on 29/10/20.
//

#include "product_manager.h"

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

void ProductManager::read(std::ifstream &file) {
    if(!file){
        throw FileNotFound();
    }
    else{
        std::vector<std::string> cakeCategories={"GENERAL", "PIE", "SPONGE", "PUFF_PASTRY", "CRUNCHY"};
        bool readingCakes=true;
        float price;
        std::string line, name, cakeCategory, breadCategory;

        while(getline(file, line)){
            if(line=="CAKES")
                readingCakes=true;
            else if(line=="BREADS"){
                readingCakes=false;
            }
            else if(readingCakes) {
                std::stringstream cake(line);
                cake >> name >> price >> cakeCategory;
                auto itr=std::find(cakeCategories.begin(), cakeCategories.end(), cakeCategory);
                int index=std::distance(cakeCategories.begin(), itr);
                enum CakeCategory categoryToSave= static_cast<CakeCategory>(index);
                std::replace(name.begin(), name.end(), '-', ' ');
                addCake(name, price, categoryToSave);
            }
            else{
                std::stringstream bread(line);
                bread>>name>>price>>breadCategory;
                std::replace(name.begin(), name.end(), '-', ' ');
                addBread(name, price, cakeCategory=="small");
            }
        }
    }
}

void ProductManager::write(std::ofstream &file) const {
    if(!file){
        throw FileNotFound();
    }
    else{
        std::vector<std::string> cakeCategories={"GENERAL", "PIE", "SPONGE", "PUFF_PASTRY", "CRUNCHY"};
        std::string nameToSave;
        std::string categoryToSave;

        for(const auto & product: _products){
            nameToSave = product->getName();
            std::replace(nameToSave.begin(), nameToSave.end(), ' ', '-');
            if (dynamic_cast<Cake *>(product) != nullptr){

                file<<nameToSave<<product->getPrice()<<cakeCategories.at(product->getCategory());
            }
            else if (dynamic_cast<Bread *>(product) != nullptr) {
                categoryToSave=(product->isSmall())? "small" : "big";
                file<<nameToSave<<product->getPrice()<<categoryToSave;
            }
        }
    }
}
