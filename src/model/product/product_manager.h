//
// Created by bdmendes on 29/10/20.
//

#ifndef FEUP_AEDA_PROJECT_PRODUCT_MANAGER_H
#define FEUP_AEDA_PROJECT_PRODUCT_MANAGER_H

#include "product.h"
#include <set>

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
    std::set<Product*, ProductSmaller> getAll();

    Bread* addBread(std::string name, float price, bool small = true);
    Cake* addCake(std::string name, float price, CakeCategory category = CakeCategory::GENERAL);
    void remove(Product* product);

    void readCakes(std::ifstream& file);
    void readBreads(std::ifstream& file);
    void writeCakes(std::ofstream& file) const;


    void read(std::ifstream& file);
    void print(std::ostream& os) const;

private:
    std::set<Product*, ProductSmaller> _products;
};


#endif //FEUP_AEDA_PROJECT_PRODUCT_MANAGER_H
