//
// Created by up201906166 on 23/10/2020.
//

#ifndef FEUP_AEDA_PROJECT_PERSON_EXCEPTIONS_H
#define FEUP_AEDA_PROJECT_PERSON_EXCEPTIONS_H

#include <utility>
#include <stdexcept>

#include "model/person/person.h"

class PersonDoesNotExist: public std::logic_error{
public:
    PersonDoesNotExist(const std::string& name, int tributaryNumber);
    explicit PersonDoesNotExist(const std::string& name);
    explicit PersonDoesNotExist(int taxID);
};

class InvalidPersonPosition : public std::invalid_argument{
public:
    InvalidPersonPosition(unsigned position, unsigned long size);
};

class InvalidCredential : public std::invalid_argument {
public:
    InvalidCredential(const std::string &offending);
};


#endif //FEUP_AEDA_PROJECT_PERSON_EXCEPTIONS_H
