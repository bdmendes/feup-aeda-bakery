//
// Created by bdmendes on 29/10/20.
//

#include "order_manager.h"

OrderManager::OrderManager(ProductManager &pm, ClientManager &cm, WorkerManager &wm) :
        _productManager(pm), _clientManager(cm), _workerManager(wm), _orders{}{
}

bool OrderManager::has(Order *order) const {
    return std::find(_orders.begin(),_orders.end(),order) != _orders.end();
}

Order* OrderManager::get(unsigned int position, Client* client, Worker* worker) {
    std::vector<Order*> filtered;
    if (client != nullptr && worker != nullptr) throw std::invalid_argument("Can't choose both worker and client");
    else if (client != nullptr) filtered = get(client);
    else if (worker != nullptr) filtered = get(worker);
    else filtered = getAll();

    if (position >= filtered.size()) throw InvalidOrderPosition(position, filtered.size());
    return filtered.at(position);
}

std::vector<Order *> OrderManager::getAll() const {
    return _orders;
}

std::vector<Order *> OrderManager::get(Client *client) const {
    if (!_clientManager.has(client)) throw PersonDoesNotExist(client->getName(), client->getTaxId());
    std::vector<Order*> filtered;
    for (const auto& order: _orders){
        if (order->getClient() == client) filtered.push_back(order);
    }
    return filtered;
}

std::vector<Order *> OrderManager::get(Worker *worker) const {
    if (!_workerManager.has(worker)) throw PersonDoesNotExist(worker->getName(), worker->getTaxId());
    std::vector<Order*> filtered;
    for (const auto& order: _orders){
        if (order->getWorker() == worker) filtered.push_back(order);
    }
    return filtered;
}

void OrderManager::sort() {
    std::sort(_orders.begin(), _orders.end());
}

Order* OrderManager::add(Client *client, Date date) {
    if (!_clientManager.has(client)) throw PersonDoesNotExist(client->getName(), client->getTaxId());
    Order* order = new Order(*client,*_workerManager.getLessBusyWorker(),date);
    _orders.push_back(order);
    return order;
}

void OrderManager::remove(Order *order) {
    auto position = std::find(_orders.begin(),_orders.end(),order);
    if (position == _orders.end()) throw OrderDoesNotExist();
    if (order->wasDelivered()) throw std::invalid_argument("It's not possible to delete a delivered order");
    order->getWorker()->removeOrderToDeliver();
    _orders.erase(position);
}

void OrderManager::remove(unsigned position) {
    if (position >= _orders.size()) throw OrderDoesNotExist();
    if (_orders.at(position)->wasDelivered()) throw std::invalid_argument("It's not possible to delete a delivered order");
    _orders.at(position)->getWorker()->removeOrderToDeliver();
    _orders.erase(_orders.begin() + position);
}

bool OrderManager::print(std::ostream &os, Client* client, Worker* worker) const {
    std::vector<Order*> toPrint;
    if (client != nullptr) toPrint = get(client);
    else if (worker != nullptr) toPrint = get(worker);
    else toPrint = getAll();

    if (toPrint.empty()) {
        os << "No orders here yet.\nHow about you go back and add some?\n";
        return false;
    }

    os << std::string(toPrint.size() / 10 + 3,util::SPACE);
    if (client == nullptr) os << util::column("CLIENT",true);
    if (worker == nullptr) os << util::column("WORKER",true);
    os << util::column("REQUESTED",true)
    << util::column("DELIVERED",true) << "\n";

    int count = 1;
    for (const auto& o: toPrint){
        os << std::to_string(count++) + ". ";
        if (client == nullptr) os << util::column(o->getClient()->getName(),true);
        if (worker == nullptr) os << util::column(o->getWorker()->getName(),true);
        os << util::column(o->getRequestDate().getCompleteDate(), true)
        << util::column(o->wasDelivered() ? o->getDeliverDate().getClockTime() + " (" +
        std::to_string(o->getClientEvaluation()) + " points)" : "Not Yet",true) << "\n";
    }
    return true;
}

