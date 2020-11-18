//
// Created by laimi on 25/10/2020.
//

#ifndef FEUP_AEDA_PROJECT_PRODUCTEXCEPTIONS_H
#define FEUP_AEDA_PROJECT_PRODUCTEXCEPTIONS_H

#include <string>
#include <iostream>

class ProductDoesNotExist : public std::invalid_argument{
public:
    ProductDoesNotExist(const std::string& name, float price);
    explicit ProductDoesNotExist(const std::string& name);
    explicit ProductDoesNotExist(float price);
};

class InvalidProductPosition : public std::invalid_argument{
public:
    InvalidProductPosition(unsigned position, unsigned long size);
};


#endif //FEUP_AEDA_PROJECT_PRODUCTEXCEPTIONS_H
