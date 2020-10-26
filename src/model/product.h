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
    bool operator== (const Product& p) const;
protected:
    std::string _name;
    float _price;
};

class Bread : public Product{
public:
    Bread(std::string name, float price, bool small);
    bool isSmall() const;
    bool operator== (const Bread& bread) const;
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
    bool operator== (const Cake& cake) const;
    //bool isPresent(const std::string &category) const; //for test purposes
private:
    std::string _category;
};


#endif //SRC_PRODUCT_H
