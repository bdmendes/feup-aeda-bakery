//
// Created by bdmendes on 29/10/20.
//

#include "order_manager.h"

OrderManager::OrderManager(ProductManager &pm, ClientManager &cm, WorkerManager &wm) :
        _productManager(pm), _clientManager(cm), _workerManager(wm), _orders(std::set<Order*, OrderSmaller>()){
}

bool OrderManager::has(Order *order) const {
    auto comp = [order](const Order* o2){
        return *order == *o2;
    };
    return std::find_if(_orders.begin(),_orders.end(),comp) != _orders.begin();
}

Order* OrderManager::get(unsigned int position) {
    if (position >= _orders.size()) throw InvalidOrderPosition(position, _orders.size());
    auto it = _orders.begin(); std::advance(it, position);
    return *it;
}

std::set<Order *, OrderSmaller> OrderManager::getAll() const {
    return _orders;
}

std::set<Order *, OrderSmaller> OrderManager::get(Client *client) {
    if (!_clientManager.has(client)) throw PersonDoesNotExist(client->getName(), client->getTaxId());
    std::set<Order*, OrderSmaller> filtered;
    for (const auto& order: _orders){
        if (order->getClient() == *client) filtered.insert(order);
    }
    return filtered;
}

std::set<Order *, OrderSmaller> OrderManager::get(Worker *worker) {
    if (!_workerManager.has(worker)) throw PersonDoesNotExist(worker->getName(), worker->getTaxId());
    std::set<Order*, OrderSmaller> filtered;
    for (const auto& order: _orders){
        if (order->getWorker() == *worker) filtered.insert(order);
    }
    return filtered;
}

Order* OrderManager::add(Client *client) {
    if (!_clientManager.has(client)) throw PersonDoesNotExist(client->getName(), client->getTaxId());
    _orders.insert(new Order(*client,*_workerManager.getAvailable()));
    return *_orders.rbegin();
}

void OrderManager::remove(Order *order) {
    auto position = std::find(_orders.begin(),_orders.end(),order);
    if (position == _orders.end())
        throw OrderDoesNotExist();
    _orders.erase(position);
}

void OrderManager::write(std::ostream &os) const {
    os << util::column("CLIENT",true)
    << util::column("WORKER",true)
    << util::column("REQUEST DATE",true)
    << util::column("DELIVERED",true) << "\n";

    for (const auto& o: _orders){
        os << util::column(o->getClient().getName(),true)
        << util::column(o->getWorker().getName(),true)
        << util::column(o->getDate().getCompleteDate(),true)
        << util::column(o->wasDelivered() ? "Yes" : "No") << "\n";
    }
}
