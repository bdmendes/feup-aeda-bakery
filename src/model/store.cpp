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

std::vector<Order> Store::getClientHistory(const Client* client) {
    std::vector<Order> clientOrders;
    for(const auto& order : _orders){
        const Client* clientTemp = order.getClient();
        if(clientTemp->getTributaryNumber() == client->getTributaryNumber())
            clientOrders.push_back(order);
    }
    return clientOrders;
}

std::vector<Order> Store::getWorkerHistory(const Worker *worker) {
    std::vector<Order> workerOrders;
    for(const auto& order : _orders){
        Worker* workerTemp = order.getWorker();
        if(workerTemp->getTributaryNumber() == worker->getTributaryNumber())
            workerOrders.push_back(order);
    }
    return workerOrders;
}

int Store::searchWorkerByName(std::string name) {
    for(unsigned int i = 0; i < _workers.size(); i++)
        if (_workers[i]->getName() == name) return i;
    return -1;
}

int Store::searchWorkerByTributaryNumber(int tributaryNumber) {
    for(unsigned int i = 0; i < _workers.size(); i++)
        if (_workers[i]->getTributaryNumber() == tributaryNumber) return i;
    return -1;
}



int Store::findWorker(const Worker *worker) {
    int index1 = searchWorkerByName(worker->getName());
    int index2 = searchWorkerByTributaryNumber(worker->getTributaryNumber());
    if((index1 != -1) && (index2 != -1) && (index1 == index2)) return index1;
    return -1;
}

void Store::hireWorker(Worker *worker) {
    _workers.push_back(worker);
}

void Store::fireWorker(const Worker *worker) {
    if(_workers.empty())
        throw StoreHasNoWorkers(_name);
    if(findWorker(worker) == -1)
        throw PersonDoesNotExist(worker->getName(), worker->getTributaryNumber());
    for(unsigned i=0; i<_workers.size();i++){
        if(_workers[i] == worker) _workers.erase(_workers.begin()+i);
    }
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

void Store::changeWorkerSalary(Worker *worker, float salary) {
    if(findWorker(worker) == -1)
        throw PersonDoesNotExist(worker->getName(), worker->getTributaryNumber());
    worker->setSalary(salary);
}

void Store::addOrder(const std::map<Product, unsigned int>& products, Client& client) {
    _orders.emplace_back(products,client,*getAvailableWorker());
}
