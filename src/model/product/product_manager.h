//
// Created by bdmendes on 29/10/20.
//

#ifndef FEUP_AEDA_PROJECT_PRODUCT_MANAGER_H
#define FEUP_AEDA_PROJECT_PRODUCT_MANAGER_H

#include "product.h"
#include <set>
#include <algorithm>
#include <utility>
#include <sstream>
#include <fstream>

#include <exception/file_exception.h>

struct ProductSmaller{
    bool operator()(const Product* p1, const Product* p2) {
        return *p1 < *p2;
    }
};

class ProductManager {
public:
    ProductManager();
    ProductManager(std::set<Product*, ProductSmaller> stock);

    bool has(Product* product) const;

    Product* get(unsigned position);
    Product* getProduct(std::string &name, float &price);
    std::set<Product*, ProductSmaller> getAll();

    Bread* addBread(std::string name, float price, bool small = true);
    Cake* addCake(std::string name, float price, CakeCategory category = CakeCategory::GENERAL);
    void remove(Product* product);
    void read(std::ifstream& file);
    void write(std::ofstream& file) const;
    void print(std::ostream& os) const;

private:
    std::set<Product*, ProductSmaller> _products;
};


#endif //FEUP_AEDA_PROJECT_PRODUCT_MANAGER_H
