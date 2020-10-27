//
// Created by laimi on 15/10/2020.
//

#include "store.h"

#include <algorithm>

Store::Store(std::string name) :
        _name(std::move(name)), _orders(std::vector<Order>()), _clientEvaluations(std::vector<float>()){
}

std::string Store::getName() const {
    return _name;
}

float Store::getMeanEvaluation() const {
    double sum = 0;
    for(const auto& order : _orders)
        sum += order.getClientEvaluation();
    return sum/_clients.size();
}

std::vector<Order*> Store::getClientOrders(const Client* client) {
    std::vector<Order*> clientOrders;
    for(auto& order : _orders)
        if (order.getClient() == client) clientOrders.push_back(&order);
    return clientOrders;
}

std::vector<Order*> Store::getWorkerOrders(const Worker *worker) {
    std::vector<Order*> workerOrders;
    for(auto& order : _orders)
        if (order.getWorker() == worker) workerOrders.push_back(&order);
    return workerOrders;
}

bool Store::hasWorker(std::string name) const{
    auto comp = [name](const Worker* worker){
        return name == worker->getName();
    };
    return std::find_if(_workers.begin(),_workers.end(),comp) != _workers.end();
}

bool Store::hasWorker(int tributaryNumber) const {
    auto comp = [tributaryNumber](const Worker* worker){
        return tributaryNumber == worker->getTributaryNumber();
    };
    return std::find_if(_workers.begin(),_workers.end(),comp) != _workers.end();
}

bool Store::hasWorker(const Worker* worker) const{
    return std::find(_workers.begin(),_workers.end(),worker) != _workers.end();
}

void Store::hireWorker(Worker *worker) {
    _workers.push_back(worker);
}

void Store::fireWorker(const Worker *worker) {
    if(_workers.empty())
        throw StoreHasNoWorkers(_name);
    if(!hasWorker(worker))
        throw PersonDoesNotExist(worker->getName(), worker->getTributaryNumber());
    _workers.erase(std::find(_workers.begin(),_workers.end(),worker));
}

Worker* Store::getAvailableWorker() {
    if (_workers.empty()){
        throw StoreHasNoWorkers(_name);
    }

    auto orderComp = [](const Worker *worker1, const Worker *worker2) {
        return ((worker1->getOrders()) < (worker2->getOrders()));
    };
    return *std::min_element(_workers.begin(), _workers.end(), orderComp);
}

void Store::changeWorkerSalary(Worker *worker, float salary) const {
    if(!hasWorker(worker))
        throw PersonDoesNotExist(worker->getName(), worker->getTributaryNumber());
    worker->setSalary(salary);
}

void Store::addOrder(const std::map<Product*, unsigned int>& products, Client& client) {
    _orders.emplace_back(products,client,*getAvailableWorker());
}
