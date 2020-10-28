//
// Created by laimi on 15/10/2020.
//

#include "store.h"

#include <algorithm>
#include <numeric>

Store::Store(std::string name) :
        _name(std::move(name)), _orders(std::vector<Order>()), _clientEvaluations(std::vector<float>()){
}

std::string Store::getName() const {
    return _name;
}

float Store::getMeanEvaluation() const {
    std::vector<float> evaluations;
    for(const auto& order : _orders)
        if(order.wasDelivered()) evaluations.push_back(order.getClientEvaluation());
    return std::accumulate(evaluations.begin(),evaluations.end(),0.0f) / evaluations.size();
}

std::vector<Order> Store::getOrders() const {
    return _orders;
}

std::vector<Order*> Store::getClientOrders(const Client& client){
    std::vector<Order*> clientOrders;
    for(auto& order : _orders)
        if (order.getClient() == client) clientOrders.push_back(&order);
    return clientOrders;
}

std::vector<Order*> Store::getWorkerOrders(const Worker& worker){
    std::vector<Order*> workerOrders;
    for(auto& order : _orders)
        if (order.getWorker() == worker) workerOrders.push_back(&order);
    return workerOrders;
}

bool Store::hasWorker(const std::string& name) const{
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

bool Store::hasWorker(const Worker *worker) const{
    return std::find(_workers.begin(),_workers.end(),worker) != _workers.end();
}

bool Store::hasProduct(const Product *product) const {
    return std::find(_allProducts.begin(),_allProducts.end(),product) != _allProducts.end();
}

void Store::hireWorker(Worker *worker) {
    if(std::find(_workers.begin(),_workers.end(),worker) == _workers.end())
        _workers.push_back(worker);
    else throw PersonAlreadyExists(worker->getName(), worker->getTributaryNumber());
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
    if(!hasWorker(worker)) throw PersonDoesNotExist(worker->getName(), worker->getTributaryNumber());
    worker->setSalary(salary);
}

void Store::addOrder(const std::map<Product*, unsigned int>& products, Client& client) {
    if(!hasClient(&client)) throw PersonDoesNotExist(client.getName(),client.getTributaryNumber());
    _orders.emplace_back(client,*getAvailableWorker(),products);
}

bool Store::operator==(const std::string &name) const {
    return name == getName();
}

bool Store::hasClient(const std::string& name) const {
    auto comp = [name](const Client* client){
        return name == client->getName();
    };
    return std::find_if(_clients.begin(),_clients.end(),comp) != _clients.end();
}

bool Store::hasClient(int tributaryNumber) const {
    auto comp = [tributaryNumber](const Client* client){
        return tributaryNumber == client->getTributaryNumber();
    };
    return std::find_if(_clients.begin(),_clients.end(),comp) != _clients.end();
}

bool Store::hasClient(const Client *client) const {
    return std::find(_clients.begin(),_clients.end(),client) != _clients.end();
}

void Store::addProduct(const Product *product) {
    if(std::find(_allProducts.begin(),_allProducts.end(),product) != _allProducts.end())
        throw ProductAlreadyExists(product->getName(), product->getPrice());
    _allProducts.push_back(product);
}

void Store::removeProduct(const Product *product) {
    auto position=std::find(_allProducts.begin(), _allProducts.end(),product);
    if(position == _allProducts.end())
        throw ProductDoesNotExist(product->getName(), product->getPrice());
    _allProducts.erase(position);
}

void Store::addClient(const Client *client) {
    if(std::find(_clients.begin(),_clients.end(),client) != _clients.end())
        throw PersonAlreadyExists(client->getName(), client->getTributaryNumber());
    _clients.push_back(client);
}

void Store::removeClient(const Client *client) {
    auto position=std::find(_clients.begin(), _clients.end(),client);
    if(position == _clients.end())
        throw ProductDoesNotExist(client->getName(), client->getTributaryNumber());
    _clients.erase(position);
}
