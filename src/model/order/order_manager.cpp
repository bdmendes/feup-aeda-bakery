//
// Created by bdmendes on 29/10/20.
//

#include "order_manager.h"

OrderManager::OrderManager(ProductManager &pm, ClientManager &cm, WorkerManager &wm) :
        _productManager(pm), _clientManager(cm), _workerManager(wm), _orders(std::set<Order*, OrderSmaller>()){
}

bool OrderManager::has(Order *order) const {
    return std::find(_orders.begin(),_orders.end(),order) != _orders.begin();
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

/*Order *OrderManager::add(Client *client, Worker *worker, Date &date) {

}*/

void OrderManager::remove(Order *order) {
    auto position = std::find(_orders.begin(),_orders.end(),order);
    if (position == _orders.end())
        throw OrderDoesNotExist();
    _orders.erase(position);
}

void OrderManager::read(std::ifstream& file) {
    if(!file){
        throw FileNotFound();
    }
    else{
        std::string line, date, time;
        int clientTaxID, workerTaxID, day, month, year, hour, minute;
        bool orderEnd=false;

        while(getline(file, line)){

            Order *newOrder;

            if(!orderEnd) {
                std::stringstream order(line);
                order >> clientTaxID >> workerTaxID >> date >> hour;

                if (!_clientManager.has(_clientManager.get(clientTaxID)))
                    throw PersonDoesNotExist (clientTaxID);

                if (!_workerManager.has(_workerManager.get(workerTaxID)))
                    throw PersonDoesNotExist (workerTaxID);

                std::replace(date.begin(), date.end(), '/', ' ');
                std::stringstream tempDate(date);
                tempDate >> day >> month >> year;
                std::replace(date.begin(), date.end(), ':', ' ');
                std::stringstream tempHour(time);
                tempHour << hour << ':' << minute;
                Date date(day, month, year, hour, minute);

                newOrder = add(_clientManager.get(clientTaxID), _workerManager.get(workerTaxID), date);

                orderEnd = true;
            }
            else{

            }
        }
    }
}

void OrderManager::print(std::ostream &os) const {
    int numSpaces = static_cast<int>(std::to_string(_orders.size()).size() + 2);
    os << std::string(numSpaces,util::SPACE) << util::column("CLIENT",true)
    << util::column("WORKER",true)
    << util::column("REQUESTED",true)
    << util::column("DELIVERED",true) << "\n";

    int count = 1;
    for (const auto& o: _orders){
        os << std::setw(numSpaces) << std::left << std::to_string(count) + ". "
        << util::column(o->getClient().getName(),true)
        << util::column(o->getWorker().getName(),true)
        << util::column(o->getRequestDate().getCompleteDate(), true)
        << util::column(o->wasDelivered() ? o->getDeliverDate().getClockTime() + " (" +
        util::to_string(o->getClientEvaluation()) + " points)" : "Not Yet",true) << "\n";
        count++;
    }
}

