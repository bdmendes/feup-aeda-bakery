
#include "person_exception.h"

PersonDoesNotExist::PersonDoesNotExist(const std::string& name, unsigned long taxID) :
    std::logic_error(name + ", with number " + std::to_string(taxID) + ", does not exist!"){
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

AllWorkersAreBusy::AllWorkersAreBusy() :
    std::logic_error("All workers are at their maximum capacity: " + std::to_string(Worker::MAX_ORDERS_AT_A_TIME) + " orders at a time! Come back later."){
}
