
#include "product_manager.h"

#include <fstream>
#include <algorithm>

#include "util/util.h"
#include "exception/file_exception.h"

ProductManager::ProductManager(): _products(){
}

bool ProductManager::has(Product *product) const {
    return std::find(_products.begin(), _products.end(), product) != _products.end();
}

Product* ProductManager::get(unsigned long position) {
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
    auto position = _products.find(product);
    if (position == _products.end()) throw ProductDoesNotExist(product->getName(),product->getPrice());
    _products.erase(position);
}

void ProductManager::remove(unsigned long position) {
    if (position >= _products.size()) throw std::invalid_argument("Product does not exist");
    auto it = _products.begin();
    advance(it,position);
    _products.erase(it);
}


void ProductManager::print(std::ostream &os) const {
    if (!_products.empty()) {
        os << std::string((_products.size()+1) / 10 + 3, util::SPACE)
           << util::column("NAME", true)
           << util::column("CATEGORY")
           << util::column("UNIT PRICE") << "\n";

        int count = 1;
        for (const auto &p: _products) {
            os << std::to_string(count++) + ". ";
            p->print(os);
            os << "\n";
        }
    }
    else os << "Nothing in the stock yet.\n";
}

Product *ProductManager::get(const std::string &name, float price) {
    for(const auto& p : _products){
        if(p->getName()==name && p->getPrice()==price)
            return p;
    }
    throw ProductDoesNotExist(name, price);
}

void ProductManager::read(const std::string &path) {
    std::ifstream file(path);
    if(!file) throw FileNotFound(path);

    bool readingCakes = true;
    std::vector<std::string> cakeCategories = Cake::getCategories();

    for (std::string line; getline(file, line); ){
        util::stripCarriageReturn(line);
        if (line.empty() || line.at(0) == '-') continue;

        if(line=="CAKES") readingCakes = true;
        else if(line=="BREADS") readingCakes = false;
        else if(readingCakes) {
            std::stringstream ss(line);
            std::string name, cakeCategory;
            float price = 1;

            ss >> name >> price >> cakeCategory;
            CakeCategory categoryToSave = CakeCategory::GENERAL;
            for (unsigned long i = 0; i < cakeCategories.size(); ++i){
                std::string styledCat = cakeCategories.at(i);
                std::replace(styledCat.begin(),styledCat.end(),' ','-');
                if (styledCat == cakeCategory) {
                    categoryToSave = static_cast<CakeCategory>(i);
                }
            }
            std::replace(name.begin(), name.end(), '-', ' ');
            addCake(name, price, categoryToSave);
        }
        else{
            std::stringstream ss(line);
            std::string name, small;
            float price = 1;

            ss>>name>>price>>small;
            std::replace(name.begin(), name.end(), '-', ' ');
            addBread(name, price, small=="small");
        }
    }
}

std::set<Cake *, ProductSmaller> ProductManager::getCakes() const {
    std::set<Cake *, ProductSmaller> s;
    for (const auto& p: _products){
        auto cake = dynamic_cast<Cake*>(p);
        if (cake) s.insert(cake);
    }
    return s;
}

std::set<Bread *, ProductSmaller> ProductManager::getBreads() const {
    std::set<Bread *, ProductSmaller> s;
    for (const auto& p: _products){
        auto bread = dynamic_cast<Bread*>(p);
        if (bread) s.insert(bread);
    }
    return s;
}

void ProductManager::write(const std::string &path) const{
    std::ofstream file(path);
    if(!file) throw FileNotFound(path);

    std::vector<std::string> cakeCategories=Cake::getCategories();
    std::set<Cake*,ProductSmaller> cakes = getCakes();
    std::set<Bread*,ProductSmaller> breads = getBreads();

    file << "CAKES\n";
    for (const auto& c: cakes){
        std::string nameToSave = c->getName();
        std::replace(nameToSave.begin(),nameToSave.end(),' ','-');

        std::string styledCat = cakeCategories.at(static_cast<unsigned long>(c->getCategory()));
        std::replace(styledCat.begin(),styledCat.end(),' ','-');

        file << nameToSave << " " << c->getPrice() << " " << styledCat << "\n";
    }

    file << util::SEPARATOR << "BREADS\n";
    for (const auto& b: breads){
        std::string nameToSave = b->getName();
        std::replace(nameToSave.begin(),nameToSave.end(),' ','-');
        file << nameToSave << " " << b->getPrice() << " " << ( (b->isSmall())? "small" : "big") << "\n";
    }
}

ProductManager::~ProductManager() {
    for (auto& p : _products) delete p;
}
