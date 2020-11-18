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
    ~ProductManager();

    bool has(Product* product) const;

    Product* get(unsigned position);
    Product* get(const std::string &name, float price);
    std::set<Cake*, ProductSmaller> getCakes() const;
    std::set<Bread*, ProductSmaller> getBreads() const;
    std::set<Product*, ProductSmaller> getAll();


    Bread* addBread(std::string name, float price, bool small = true);
    Cake* addCake(std::string name, float price, CakeCategory category = CakeCategory::GENERAL);
    void remove(Product* product);
    void remove(unsigned position);

    void read(const std::string& path);
    void write(const std::string& path) const;
    void print(std::ostream& os) const;
private:
    std::set<Product*, ProductSmaller> _products;
};


#endif //FEUP_AEDA_PROJECT_PRODUCT_MANAGER_H
