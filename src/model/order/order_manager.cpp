//
// Created by bdmendes on 29/10/20.
//

#include "order_manager.h"
#include <algorithm>
#include <exception/person_exception.h>

bool OrderManager::has(Order *order) const {
    auto comp = [order](const Order* o2){
        return *order == *o2;
    };
    return std::find_if(_orders.begin(),_orders.end(),comp) != _orders.begin();
}

OrderManager::OrderManager(ProductManager &pm, ClientManager &cm, WorkerManager &wm) :
        _productManager(pm), _clientManager(cm), _workerManager(wm), _orders(){
}

Order* OrderManager::add(Client *client) {
    if (!_clientManager.has(client)) throw PersonDoesNotExist(client->getName(),client->getTributaryNumber());
    _orders.push_back(new Order(*client,*_workerManager.getAvailable()));
    return _orders.back();
}

Order* OrderManager::get(unsigned int position) {
    if (position >= _orders.size()) throw std::invalid_argument("Out of bounds order position");
    return _orders.at(position);
}

std::vector<Order *> OrderManager::getAll() const {
    return _orders;
}

std::vector<Order*> OrderManager::get(Client *client) {
    if (!_clientManager.has(client)) throw PersonDoesNotExist(client->getName(),client->getTributaryNumber());
    std::vector<Order*> filtered;
    for (const auto& o: _orders){
        if (o->getClient() == *client) filtered.push_back(o);
    }
    return filtered;
}

std::vector<Order *> OrderManager::get(Worker *worker) {
    if (!_workerManager.has(worker)) throw PersonDoesNotExist(worker->getName(),worker->getTributaryNumber());
    std::vector<Order*> filtered;
    for (const auto& o: _orders){
        if (o->getWorker() == *worker) filtered.push_back(o);
    }
    return filtered;
}

void OrderManager::remove(Order *order) {
    auto position = std::find(_orders.begin(),_orders.end(),order);
    if (position == _orders.end())
        throw std::invalid_argument("Order does not exist");
    _orders.erase(position);
}

void OrderManager::read() {

}
