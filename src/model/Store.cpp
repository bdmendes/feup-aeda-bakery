//
// Created by laimi on 15/10/2020.
//

#include "Store.h"

Store::Store(const std::string& name, const Boss& boss) :
        _name(name), _boss(boss), _orders(std::vector<const Order*>()), _clientEvaluations(std::vector<float>()){
}

std::string Store::getName() const {
    return _name;
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
    if(std::find(_workers.begin(),_workers.end(), order->getWorker()) == _workers.end())
        throw WorkerDoesNotExist((order->getWorker())->getName(), (order->getWorker())->getTributaryNumber());
    else if(std::find(_clients.begin(),_clients.end(),order->getClient()) == _clients.end())
        throw ClientDoesNotExist((order->getClient())->getName(), (order->getClient())->getTributaryNumber());
    else{
        _orders.push_back(order);
        (order->getWorker())->addOrder();
        _workers.push_back(order->getWorker());
        _clients.push_back(order->getClient());
    }

}

const Worker& Store::assignWorker() {
   /* std::sort(_workers.begin(), _workers.end(), [](Worker* worker1,Worker* worker2){
        return ((worker1->getOrders()) < (worker2->getOrders()));
    });
    return *(_workers[0]);*/
   std::vector<Worker*>::iterator it = std::min_element(_workers.begin(),_workers.end(),  [](Worker* worker1,Worker* worker2){
        return ((worker1->getOrders()) < (worker2->getOrders()));
    });
   return *(_workers[std::distance(_workers.begin(),it)]);


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
