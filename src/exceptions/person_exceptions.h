//
// Created by up201906166 on 23/10/2020.
//

#ifndef FEUP_AEDA_PROJECT_PERSON_EXCEPTIONS_H
#define FEUP_AEDA_PROJECT_PERSON_EXCEPTIONS_H

#include <utility>
#include <stdexcept>

#include "../model/Person.h"

class PersonDoesNotExist{
public:
    PersonDoesNotExist(std::string name, int tributaryNumber);
    std::ostream & operator<<(std::ostream &out);
private:
    std::string _name;
    int _tributaryNumber;
};

#endif //FEUP_AEDA_PROJECT_PERSON_EXCEPTIONS_H