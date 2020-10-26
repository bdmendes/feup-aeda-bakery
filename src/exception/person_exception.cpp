//
// Created by up201906166 on 23/10/2020.
//

#include "person_exception.h"

PersonDoesNotExist::PersonDoesNotExist(const std::string& name, int tributaryNumber) :
    std::logic_error(name + ", with number " + std::to_string(tributaryNumber) + ", does not exist!\n"){
}

PersonDoesNotExist::PersonDoesNotExist(const std::string& name):
    std::logic_error(name + " does not exist!\n"){
}

PersonDoesNotExist::PersonDoesNotExist(int tributaryNumber) :
    std::logic_error("Person with number " + std::to_string(tributaryNumber) + ", does not exist!\n"){
}

PersonAlreadyExists::PersonAlreadyExists(const std::string& name, int tributaryNumber) :
    std::logic_error(name + ", with number " + std::to_string(tributaryNumber) + ", does not exist!\n"){
}

PersonAlreadyExists::PersonAlreadyExists(const std::string& name):
        std::logic_error(name + " already exists!\n"){
}

PersonAlreadyExists::PersonAlreadyExists(int tributaryNumber):
    std::logic_error("Person with number " + std::to_string(tributaryNumber) + " already exists!\n"){
}
