//
// Created by laimi on 15/10/2020.
//

#include <iostream>
#include "Store.h"

Store::Store(const std::string &location) :
    _location(location), _clients(std::vector<const Client*>()),
    _evaluation(0), _workers(std::vector<const Worker*>()){

}

std::string Store::getLocation() const {
    return _location;
}

std::vector<const Client*> Store::getClients() const {
    return _clients;
}

float Store::getEvaluation() const {
    return _evaluation;
}

std::vector<const Worker*> Store::getWorkers() const{
    return _workers;
}

