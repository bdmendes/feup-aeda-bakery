//
// Created by laimi on 15/10/2020.
//

#include "store.h"

#include <numeric>
#include <utility>

Store::Store(std::string name) :
        _name(std::move(name)),
        productManager(),clientManager(),workerManager(),
        orderManager(productManager,clientManager,workerManager),
        boss("Boss", 999999999, {"boss","boss"}){
}

std::string Store::getName() const {
    return _name;
}

float Store::getEvaluation() const {
    std::vector<float> evaluations;
    for(const auto& order : orderManager.getAll())
        if(order->wasDelivered()) evaluations.push_back(order->getClientEvaluation());
    return std::accumulate(evaluations.begin(),evaluations.end(),0.0f) / evaluations.size();
}

void Store::setName(std::string name) {
    _name = std::move(name);
}
