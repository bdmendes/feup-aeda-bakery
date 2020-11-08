//
// Created by laimi on 15/10/2020.
//

#ifndef SRC_PRODUCT_H
#define SRC_PRODUCT_H

#include <string>
#include <map>
#include <set>

#include "exception/product_exception.h"

enum class CakeCategory {
    GENERAL, PIE, SPONGE, PUFF_PASTRY, CRUNCHY
};

class Product {
public:
    std::string getName() const;
    float getPrice() const;
    virtual bool operator== (const Product& p) const;
    bool operator<(const Product& p) const;

    virtual void print(std::ostream& os) const = 0;
protected:
    Product(std::string name, float price);
    std::string _name;
    float _price;
};

class Bread : public Product{
public:
    Bread(std::string name, float price, bool small = true);
    bool isSmall() const;
    virtual bool operator==(const Bread& bread) const;
    void print(std::ostream& os) const override;
private:
    bool _small;
};

class Cake : public Product{
public:
    Cake(std::string name, float price, CakeCategory category = CakeCategory::GENERAL);
    CakeCategory getCategory() const;
    virtual bool operator==(const Cake& cake) const;
    void print(std::ostream& os) const override;
private:
    CakeCategory _category;
};

#endif //SRC_PRODUCT_H
