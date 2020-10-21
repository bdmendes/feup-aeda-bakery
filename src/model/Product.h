//
// Created by laimi on 15/10/2020.
//

#ifndef SRC_PRODUCT_H
#define SRC_PRODUCT_H

#include <string>
#include <map>
#include <set>

class Product {
public:
    Product(std::string name, float price);
    std::string getName() const;
    float getPrice() const;
private:
    std::string _name;
    float _price;
};

class Bread : public Product{
public:
    Bread(std::string name, float price, bool small);
    bool isSmall() const;
private:
    bool _small;
};

class Cake : public Product{
public:
    Cake(std::string name, float price, std::string category);
    std::string getCategory() const;
    static void addCategory(const std::string &newCategory);
    static void removeCategory(const std::string &category);
    static std::set<std::string> availableCategories;
    bool operator == (const Cake &cake);
private:
    std::string _category;
};


#endif //SRC_PRODUCT_H
