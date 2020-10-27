//
// Created by up201906166 on 23/10/2020.
//

#ifndef FEUP_AEDA_PROJECT_PERSON_EXCEPTIONS_H
#define FEUP_AEDA_PROJECT_PERSON_EXCEPTIONS_H

#include <utility>
#include <stdexcept>

#include "../model/person.h"

class PersonDoesNotExist: public std::logic_error{
public:
    PersonDoesNotExist(const std::string& name, int tributaryNumber);
    explicit PersonDoesNotExist(const std::string& name);
    explicit PersonDoesNotExist(int tributaryNumber);
private:
    std::string _message;
};

class PersonAlreadyExists : public std::logic_error{
public:
    PersonAlreadyExists(const std::string& name, int tributaryNumber);
    explicit PersonAlreadyExists(const std::string& name);
    explicit PersonAlreadyExists(int tributaryNumber);
private:
    std::string _message;
};

#endif //FEUP_AEDA_PROJECT_PERSON_EXCEPTIONS_H
