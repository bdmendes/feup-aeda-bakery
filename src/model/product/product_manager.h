//
// Created by bdmendes on 29/10/20.
//

#ifndef FEUP_AEDA_PROJECT_PRODUCT_MANAGER_H
#define FEUP_AEDA_PROJECT_PRODUCT_MANAGER_H

#include "product.h"
#include <vector>

class ProductManager {
public:
    ProductManager();
    ProductManager(std::vector<Product*> stock);
    bool has(Product* product) const;
    Product* get(unsigned position);
    std::vector<Product*> getAll();
    void addBread(std::string name, float price, bool small = true);
    void addCake(std::string name, float price, CakeCategory category = CakeCategory::GENERAL);
    void remove(Product* product);
    void readCakes(std::ifstream& file);
    void readBreads(std::ifstream& file);
    void writeCakes(std::ofstream& file) const;
    void writeBreads(std::ofstream& file) const;
private:
    std::vector<Product*> _products;
};

#endif //FEUP_AEDA_PROJECT_PRODUCT_MANAGER_H
