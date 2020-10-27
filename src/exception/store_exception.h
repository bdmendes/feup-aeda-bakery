//
// Created by up201906166 on 23/10/2020.
//

#ifndef FEUP_AEDA_PROJECT_STORE_EXCEPTIONS_H
#define FEUP_AEDA_PROJECT_STORE_EXCEPTIONS_H

#include <stdexcept>
#include <iostream>

class StoreDoesNotExist : public std::invalid_argument {
public:
    explicit StoreDoesNotExist(const std::string& name);
};

class StoreAlreadyExists : public std::logic_error {
public:
    explicit StoreAlreadyExists(const std::string& name);
};

class StoreHasNoWorkers : public std::logic_error{
public:
    explicit StoreHasNoWorkers(const std::string& name);
};

#endif //FEUP_AEDA_PROJECT_STORE_EXCEPTIONS_H
