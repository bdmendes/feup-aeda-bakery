//
// Created by up201906166 on 23/10/2020.
//

#ifndef FEUP_AEDA_PROJECT_PERSON_EXCEPTIONS_H
#define FEUP_AEDA_PROJECT_PERSON_EXCEPTIONS_H

#include <utility>
#include <stdexcept>

#include "../model/person.h"

class PersonDoesNotExist: std::logic_error{
public:
    PersonDoesNotExist(const std::string& name, int tributaryNumber);
    explicit PersonDoesNotExist(const std::string& name);
    explicit PersonDoesNotExist(int tributaryNumber);
};

class PersonAlreadyExists : std::logic_error{
    PersonAlreadyExists(const std::string& name, int tributaryNumber);
    explicit PersonAlreadyExists(const std::string& name);
    PersonAlreadyExists(int tributaryNumber);
};

#endif //FEUP_AEDA_PROJECT_PERSON_EXCEPTIONS_H
