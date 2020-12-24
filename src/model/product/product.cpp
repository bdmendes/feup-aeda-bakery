
#include "product.h"

#include "util/util.h"

const char* Cake::categoryStr[5] = {
        "General", "Pie", "Sponge", "Puff Pastry", "Crunchy Cake"
};

Product::Product(std::string name, float price) :
    _name(std::move(name)), _price(price), _timesIncluded(0) {}

Bread::Bread(std::string name, float price, bool small) :
    Product(std::move(name), price), _small(small) {}

Cake::Cake(std::string name, float price, enum CakeCategory category):
        Product(std::move(name), price), _category(category), _categoryStr(categoryStr[static_cast<int>(_category)]){
}

std::string Product::getName() const {
    return _name;
}

float Product::getPrice() const {
    return _price;
}

void Product::print(std::ostream& os, bool showInclusions) const {
    os << util::column(_name,true)
       << util::column(getCategory())
       << util::column(util::to_string(_price) + " euros");
    if (showInclusions) os << util::column(std::to_string(getTimesIncluded()) + " orders");
}

std::string Bread::getCategory() const {
    return _small ? "Small Bread" : "Big Bread";
}

bool Bread::isSmall() const {
    return _small;
}

std::vector<std::string> Cake::getCategories() {
    return std::vector<std::string>(categoryStr,categoryStr + 5);
}

std::string Cake::getCategory() const {
    return _categoryStr;
}

void Product::addInclusion() {
    _timesIncluded++;
}

void Product::removeInclusion() {
    if (!_timesIncluded) return;
    _timesIncluded--;
}

unsigned Product::getTimesIncluded() const {
    return _timesIncluded;
}

bool Product::operator==(const Product &rhs) const {
    return getName() == rhs.getName() && getCategory() == rhs.getCategory();
}

bool Product::operator<(const Product &rhs) const {
    if (getTimesIncluded() != rhs.getTimesIncluded()){
        return getTimesIncluded() < rhs.getTimesIncluded();
    }
    if (getCategory() != rhs.getCategory()){
        return getCategory() < rhs.getCategory();
    }
    return getName() < rhs.getName();
}
