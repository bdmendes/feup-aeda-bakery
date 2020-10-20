//
// Created by laimi on 15/10/2020.
//

#include "Store.h"

/*Store::Store(const std::string &location) :
    _location(location), _clients(std::vector<const Client*>()), _workers(std::vector<const Worker*>()){

}*/

Store::Store(const std::string &location, const Boss& boss) :
        _location(location), _boss(boss), _orders(std::vector<const Order*>()), _clientEvaluations(std::vector<float>()){

}

float Store::getMeanEvaluation() const {
    float sum = 0;
    for(const auto& order : _orders)
        sum += order->getClientEvaluation();
    return sum/_clients.size();
}

void Store::hireWorker(Worker *worker) {
    _workers.push_back(worker);
}

void Store::fireWorker(const Worker *worker) {
    for(unsigned i=0; i<_workers.size();i++){
        if(_workers[i] == worker) _workers.erase(_workers.begin()+i);
    }
}

void Store::newOrder(const Order* order) {
    _orders.push_back(order);
    (order->getWorker())->addOrder();
    _workers.push_back(order->getWorker());
    _clients.push_back(order->getClient());
}

const Worker& Store::assignWorker() {
    const Worker* worker = nullptr;
    for(auto const& worker1 : _workers){
        for(auto const& worker2 : _workers){
            if(worker1->getOrders() < worker2->getOrders())
                worker = worker1;
            else
                worker = worker2;
        }
    }
    return *worker;
}

void Store::deliveredOrder(const Order *order) {
    for(unsigned i=0; i < _orders.size();i++){
        if(_orders[i] == order) _orders.erase(_orders.begin()+i);
    }
    (order->getWorker())->removeOrder();
}

void Store::changeWorkerSalary(Worker *worker, float salary) {
    worker->setSalary(salary);
}
