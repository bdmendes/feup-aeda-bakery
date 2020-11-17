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

int Store::getEvaluation() const {
    std::vector<int> evaluations;
    int count = 0;
    for(const auto& order : orderManager.getAll()) {
        if (order->wasDelivered()) evaluations.push_back(order->getClientEvaluation());
        count++;
    }
    return std::accumulate(evaluations.begin(),evaluations.end(),0) / count;
}

void Store::setName(const std::string& name) {
    _name = name;
}

float Store::getProfit() const {
    float profit = 0.0f;
    for (const auto& o: orderManager.getAll()){
        if (o->wasDelivered()) profit += o->getFinalPrice();
    }
    return profit;
}

