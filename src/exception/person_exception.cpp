
#include "person_exception.h"

PersonDoesNotExist::PersonDoesNotExist(const std::string& name, int tributaryNumber) :
    std::logic_error(name + ", with number " + std::to_string(tributaryNumber) + ", does not exist!"){
}

PersonDoesNotExist::PersonDoesNotExist(unsigned long taxID) :
    std::logic_error("Person with number " + std::to_string(taxID) + " does not exist!"){
}

InvalidPersonPosition::InvalidPersonPosition(unsigned long position, unsigned long size) :
    std::invalid_argument(std::to_string(position + 1) + " is an invalid position; should be between 1 and " + std::to_string(size) + "!"){
}

InvalidCredential::InvalidCredential() :
    invalid_argument("You cannot use reserved UI keywords in your credential.") {
}
