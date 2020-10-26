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
    std::string message;
};

class StoreAlreadyExists : std::logic_error {
public:
    explicit StoreAlreadyExists(const std::string& name);
private:
    std::string message;
};

class StoreExceptions {
public:
    StoreExceptions(std::string name);

protected:
    std::string _name;
};

class StoreHasNoWorkers : StoreExceptions{
public:
    StoreHasNoWorkers(std::string name);
    std::ostream & operator<<(std::ostream& out);
};

#endif //FEUP_AEDA_PROJECT_STORE_EXCEPTIONS_H
