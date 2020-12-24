
#include "product_manager.h"

#include <fstream>
#include <algorithm>

#include "util/util.h"
#include "exception/file_exception.h"

ProductManager::ProductManager(): _products(ProductEntry()){
}

bool ProductManager::has(Product *product) const {
    return _products.find(ProductEntry(product)).getProduct() != nullptr;
}

Product* ProductManager::get(unsigned long position) {
    unsigned count = 0;
    for (BSTItrIn<ProductEntry> it(_products); !it.isAtEnd(); it.advance()){
        if (count == position) return it.retrieve().getProduct();
        count++;
    }
    throw InvalidProductPosition(position, count);
}

std::vector<Product*> ProductManager::getAll() const {
    std::vector<Product*> res;
    for (BSTItrIn<ProductEntry> it(_products); !it.isAtEnd(); it.advance()){
        res.push_back(it.retrieve().getProduct());
    }
    return res;
}

Bread* ProductManager::addBread(std::string name, float price, bool small) {
    auto it = new Bread(std::move(name),price,small);
    bool hi = _products.insert(ProductEntry(it));
    return it;
}

Cake* ProductManager::addCake(std::string name, float price, CakeCategory category) {
    auto it = new Cake(std::move(name),price,category);
    _products.insert(ProductEntry(it));
    return it;
}

void ProductManager::remove(Product *product) {
    auto p = _products.find(ProductEntry(product));
    if (p.getProduct() == nullptr) throw ProductDoesNotExist(product->getName(),product->getPrice());
    _products.remove(p);
}

void ProductManager::remove(unsigned long position) {
    unsigned count = 0;
    for (BSTItrIn<ProductEntry> it(_products); !it.isAtEnd(); it.advance()){
        if (count == position) {
            _products.remove(it.retrieve());
            return;
        }
        count++;
    }
    throw std::invalid_argument("Product does not exist");
}


void ProductManager::print(std::ostream &os, bool showInclusions) const {
    std::vector<Product*> vec = getAll();
    if (!vec.empty()) {
        os << std::string(vec.size() / 10 + 3, util::SPACE)
           << util::column("NAME", true)
           << util::column("CATEGORY")
           << util::column("UNIT PRICE");
        if (showInclusions) os << util::column("INCLUSIONS");
        os << "\n";

        unsigned count = 1;
        for (const auto &p: vec) {
            os << std::setw((int)vec.size() / 10 + 3) << std::to_string(count++) + ". ";
            p->print(os, showInclusions);
            os << "\n";
        }
    }
    else os << "Nothing in the stock yet.\n";
}

Product *ProductManager::get(const std::string &name, float price) {
    for (BSTItrIn<ProductEntry> it(_products); !it.isAtEnd(); it.advance()){
        Product* p = it.retrieve().getProduct();
        if (p->getName() == name && p->getPrice() == price) return p;
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

std::vector<Cake*> ProductManager::getCakes() const {
    std::vector<Cake*> res;
    for (BSTItrIn<ProductEntry> it(_products); !it.isAtEnd(); it.advance()){
        auto cake = dynamic_cast<Cake*>(it.retrieve().getProduct());
        if (cake) res.push_back(cake);
    }
    return res;
}

std::vector<Bread*> ProductManager::getBreads() const {
    std::vector<Bread*> res;
    for (BSTItrIn<ProductEntry> it(_products); !it.isAtEnd(); it.advance()){
        auto bread = dynamic_cast<Bread*>(it.retrieve().getProduct());
        if (bread) res.push_back(bread);
    }
    return res;
}

void ProductManager::write(const std::string &path) const{
    std::ofstream file(path);
    if(!file) throw FileNotFound(path);

    std::vector<std::string> cakeCategories=Cake::getCategories();
    auto cakes = getCakes();
    auto breads = getBreads();

    file << "CAKES\n";
    for (const auto& c: cakes){
        std::string nameToSave = c->getName();
        std::replace(nameToSave.begin(),nameToSave.end(),' ','-');

        std::string styledCat = c->getCategory();
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
    for (BSTItrIn<ProductEntry> it(_products); !it.isAtEnd(); it.advance()){
        delete it.retrieve().getProduct();
    }
}

Product *ProductManager::add(Product *product) {
    _products.insert(ProductEntry(product));
    return product;
}

std::vector<Product *> ProductManager::getUsed() const {
    std::vector<Product*> res;
    for (BSTItrIn<ProductEntry> it(_products); !it.isAtEnd(); it.advance()){
        if (it.retrieve().getProduct()->getTimesIncluded()) res.push_back(it.retrieve().getProduct());
    }
    return res;
}

std::vector<Product *> ProductManager::getUnused() const {
    std::vector<Product*> res;
    for (BSTItrIn<ProductEntry> it(_products); !it.isAtEnd(); it.advance()){
        if (!it.retrieve().getProduct()->getTimesIncluded()) res.push_back(it.retrieve().getProduct());
    }
    return res;
}
