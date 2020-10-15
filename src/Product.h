//
// Created by laimi on 15/10/2020.
//

#ifndef SRC_PRODUCT_H
#define SRC_PRODUCT_H
#include <string>

enum TOPPING {
    CRUNCHY,
    MEAT_SAUCE,
    SPONGE,
    CHOCOLATE,
    VANILLA,
    STRAWBERRY,
    PUFF
};

class Product {
public:
    Product(const std::string &name, float price);
private:
    std::string _name;
    float _price;
};

class Bread : public Product{
public:
    Bread(const std::string &name, float price, bool small);
private:
    float _small;
};

class Cake : public Product{
public:
    Cake(const std::string &name, float price, enum TOPPING firstTopping, enum TOPPING secondTopping);
private:
    enum TOPPING _firstTopping;
    enum TOPPING _secondTopping;
};
#endif //SRC_PRODUCT_H
