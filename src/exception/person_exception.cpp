//
// Created by up201906166 on 23/10/2020.
//

#include "person_exception.h"

PersonDoesNotExist::PersonDoesNotExist(const std::string& name, int tributaryNumber) :
    std::logic_error(name + ", with number " + std::to_string(tributaryNumber) + ", does not exist!"){
}

PersonDoesNotExist::PersonDoesNotExist(const std::string& name):
    std::logic_error(name + " does not exist!\n"){
}

PersonDoesNotExist::PersonDoesNotExist(int tributaryNumber) :
    std::logic_error("Person with number " + std::to_string(tributaryNumber) + ", does not exist!"){
}

PersonAlreadyExists::PersonAlreadyExists(const std::string& name, int tributaryNumber) :
    std::logic_error(name + ", with number " + std::to_string(tributaryNumber) + ", already exists!"){
}

PersonAlreadyExists::PersonAlreadyExists(const std::string& name):
    std::logic_error(name + " already exists!\n"){
}

PersonAlreadyExists::PersonAlreadyExists(int tributaryNumber):
    std::logic_error("Person with number " + std::to_string(tributaryNumber) + " already exists!"){
}

InvalidPersonPosition::InvalidPersonPosition(unsigned int position, unsigned int size) :
    std::invalid_argument(std::to_string(++position) + " is an invalid position; should be between 1 and " + std::to_string(size) + "!"){
}

InvalidPersonCredentialChange::InvalidPersonCredentialChange() :
    std::invalid_argument("New credentials must be different from the previous ones!\n"){
}

InvalidPersonNameChange::InvalidPersonNameChange() :
    std::invalid_argument("New name must be different from the previous one!\n"){
}

InvalidCredential::InvalidCredential(const std::string &arg) :
    invalid_argument("You cannot use '" + arg + "' in your credential since it's a reserved word!") {
}
