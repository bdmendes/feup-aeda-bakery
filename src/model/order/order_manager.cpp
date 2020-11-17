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

std::vector<Order *> OrderManager::getAll() const {
    return _orders;
}

std::vector<Order *> OrderManager::get(Client *client) {
    if (!_clientManager.has(client)) throw PersonDoesNotExist(client->getName(), client->getTaxId());
    std::vector<Order*> filtered;
    for (const auto& order: _orders){
        if (order->getClient() == *client) filtered.push_back(order);
    }
    return filtered;
}

std::vector<Order *> OrderManager::get(Worker *worker) {
    if (!_workerManager.has(worker)) throw PersonDoesNotExist(worker->getName(), worker->getTaxId());
    std::vector<Order*> filtered;
    for (const auto& order: _orders){
        if (order->getWorker() == *worker) filtered.push_back(order);
    }
    return filtered;
}

Order* OrderManager::add(Client *client) {
    if (!_clientManager.has(client)) throw PersonDoesNotExist(client->getName(), client->getTaxId());
    _orders.push_back(new Order(*client,*_workerManager.getAvailable()));
    return *_orders.rbegin();
}

Order* OrderManager::add(Client *client, Worker *worker, Date &date) {

    if(!_clientManager.has(client)) throw PersonDoesNotExist(client->getTaxId());
    if(!_workerManager.has(worker)) throw PersonDoesNotExist(worker->getTaxId());
    if(!date.isValid()) throw InvalidDate(date.getCompleteDate());

    _orders.push_back(new Order(*client,*worker, date));
    return *_orders.rbegin();
}

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
        std::string line, date, time, productName;
        int clientTaxID, workerTaxID, day, month, year, hour, minute, quantity;
        float price, clientEvaluation;
        bool orderEnd=false;

        while(getline(file, line)){

            Order *newOrder;

            if(!orderEnd) {
                std::stringstream order(line);
                order >> clientTaxID >> workerTaxID >> date >> hour >> clientEvaluation;

                if (!_clientManager.has(_clientManager.getClient(clientTaxID)))
                    throw PersonDoesNotExist (clientTaxID);

                if (!_workerManager.has(_workerManager.getWorker(workerTaxID)))
                    throw PersonDoesNotExist (workerTaxID);

                std::replace(date.begin(), date.end(), '/', ' ');
                std::stringstream tempDate(date);
                tempDate >> day >> month >> year;
                std::replace(date.begin(), date.end(), ':', ' ');
                std::stringstream tempHour(time);
                tempHour >> hour >> minute;
                Date newDate(day, month, year, hour, minute);

                newOrder = add(_clientManager.getClient(clientTaxID), _workerManager.getWorker(workerTaxID), newDate);
                newOrder->deliver(clientEvaluation);
                orderEnd = true;
            }
            else{
                //reading products of the order
                if(line==""){
                    orderEnd=false;
                    continue;
                }
                std::stringstream product(line);
                product>>productName>>price>>quantity;
                if(!_productManager.has(_productManager.getProduct(productName, price))){
                    throw ProductDoesNotExist(productName, price);
                }
                else
                    newOrder->addProduct(_productManager.getProduct(productName, price), quantity);
            }
        }
    }
}

void OrderManager::write(std::ofstream &file) const {
    if(!file){
        throw FileNotFound();
    }
    else{

        std::string nameToSave;
        std::map<Product*, unsigned int, ProductSmaller> products;

        for(const auto &order: _orders){
            file<<order->getClient().getTaxId()<<'\t'<<order->getWorker().getTaxId()<<'\t'
                <<order->getRequestDate().getCompleteDate()<<order->getClientEvaluation()<<'\n';
            //std::map<Product *, unsigned int>::iterator it=order->getProducts().begin();
            products=order->getProducts();
            for(const auto product : products){

            }
            /*for(auto it=order->getProducts().begin(); it!=order->getProducts().end(); ++it){
                nameToSave=(*it).first->getName();
                std::replace(nameToSave.begin(), nameToSave.end(), ' ', '-');
                file<<it->first->getName()<<it->second;
            }*/
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


