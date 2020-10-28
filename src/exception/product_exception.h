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

private:
    std::string _message;
};

class ProductAlreadyExists : public std::invalid_argument{
public:
    ProductAlreadyExists(const std::string& name, float price);
    explicit ProductAlreadyExists(const std::string& name);
private:
    std::string _message;
};


#endif //FEUP_AEDA_PROJECT_PRODUCTEXCEPTIONS_H
