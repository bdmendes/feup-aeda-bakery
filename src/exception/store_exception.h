//
// Created by up201906166 on 23/10/2020.
//

#ifndef FEUP_AEDA_PROJECT_STORE_EXCEPTIONS_H
#define FEUP_AEDA_PROJECT_STORE_EXCEPTIONS_H

#include <stdexcept>
#include <iostream>

class StoreHasNoWorkers : public std::logic_error{
public:
    explicit StoreHasNoWorkers();
};

#endif //FEUP_AEDA_PROJECT_STORE_EXCEPTIONS_H
