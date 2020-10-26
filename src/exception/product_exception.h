//
// Created by laimi on 25/10/2020.
//

#ifndef FEUP_AEDA_PROJECT_PRODUCTEXCEPTIONS_H
#define FEUP_AEDA_PROJECT_PRODUCTEXCEPTIONS_H

#include <string>
#include <iostream>

class ProductDoesNotExist{
public:
    ProductDoesNotExist(std::string name, float price);
    virtual std::ostream & operator<<(std::ostream &out);
    std::string getName() const;
    float getPrice() const;
private:
    std::string _name;
    float _price;
};

class CakeDoesNotExist: public ProductDoesNotExist{
public:
    CakeDoesNotExist(std::string name, float price, std::string category);
    std::ostream & operator<<(std::ostream &out);
private:
    std::string _category;
};

class BreadDoesNotExist: public ProductDoesNotExist{
public:
    BreadDoesNotExist(std::string name, float price);
    std::ostream & operator<<(std::ostream &out);
};

#endif //FEUP_AEDA_PROJECT_PRODUCTEXCEPTIONS_H
