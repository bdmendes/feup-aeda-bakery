//
// Created by up201906166 on 23/10/2020.
//

#ifndef FEUP_AEDA_PROJECT_STORE_EXCEPTIONS_H
#define FEUP_AEDA_PROJECT_STORE_EXCEPTIONS_H

#include <stdexcept>
#include <iostream>

class StoreDoesNotExist : std::invalid_argument {
public:
    explicit StoreDoesNotExist(const std::string& name);
private:
    std::string _message;
};

class StoreAlreadyExists : std::logic_error {
public:
    explicit StoreAlreadyExists(const std::string& name);
private:
    std::string _message;
};

class StoreHasNoWorkers : std::logic_error{
public:
    explicit StoreHasNoWorkers(const std::string& name);
    virtual const char * what() const noexcept;
private:
    std::string _message;
};

#endif //FEUP_AEDA_PROJECT_STORE_EXCEPTIONS_H
