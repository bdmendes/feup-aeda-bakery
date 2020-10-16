//
// Created by laimi on 15/10/2020.
//

#ifndef SRC_PRODUCT_H
#define SRC_PRODUCT_H

#include <string>
#include <set>

//if we want to add or remove flavours we cant use enum
std::set<std::string> FLAVOURS = {"Crunchy","Meat Sauce", "Sponge","Chocolate","Vanilla","Red Velvet","Puff","Caramel","Orange",
                                  "Apple", "Carrot","Coconut"};

class Product {
public:
    Product(const std::string &name, float price);
    std::string getName() const;
    float getPrice() const;
private:
    std::string _name;
    float _price;
};

class Bread : public Product{
public:
    Bread(const std::string &name, float price, bool small);
    bool isSmall() const;
private:
    float _small;
};

class Cake : public Product{
public:
    Cake(const std::string &name, float price, std::string firstFlavour, std::string secondFlavour);
    std::string getFirstFlavour() const;
    std::string getSecondFlavour() const;
    void addFlavour(const std::string flavourName);
    void removeFlavour(const std::string flavourName);
private:
    std::string _firstFlavour;
    std::string _secondFlavour;
};
#endif //SRC_PRODUCT_H
