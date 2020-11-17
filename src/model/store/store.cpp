//
// Created by laimi on 15/10/2020.
//

#include "store.h"

#include <numeric>
#include <utility>

Store::Store(std::string name) :
        _name(std::move(name)),
        productManager(),clientManager(),workerManager(),
        orderManager(productManager,clientManager,workerManager){
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

void Store::read() {
    try{
        workerManager.read("../feup-aeda-project/data/products.txt");
        productManager.read("../feup-aeda-project/data/products.txt");
        productManager.write("../feup-aeda-project/data/products.txt");
        std::ifstream clients("../feup-aeda-project/data/clients.txt");
        clientManager.read(clients);

    }

}
