//
// Created by bdmendes on 29/10/20.
//

#include "worker_manager.h"

WorkerManager::WorkerManager() : _workers(std::set<Worker*, PersonSmaller>()){
}

bool WorkerManager::has(Worker *worker) const {
    return _workers.find(worker) != _workers.end();
}

Worker* WorkerManager::get(unsigned int position) {
    if (position >= _workers.size()) throw InvalidPersonPosition(position, _workers.size());
    auto it = _workers.begin(); std::advance(it, position);
    return *it;
}

std::set<Worker *, PersonSmaller> WorkerManager::getAll() {
    return _workers;
}

Worker* WorkerManager::setSalary(unsigned position, float salary) {
    if(position >= _workers.size()) throw InvalidPersonPosition(position, _workers.size());
    auto it = _workers.begin(); std::advance(it, position);
    (*it)->setSalary(salary);
    return *it;
}

Worker* WorkerManager::add(std::string name, int taxID, float salary, Credential credential) {
    auto* worker = new Worker(std::move(name), taxID, salary, std::move(credential));
    if (has(worker)) throw PersonAlreadyExists(worker->getName(), worker->getTaxId());
    else _workers.insert(worker);
    return worker;
}

void WorkerManager::remove(Worker *worker) {
    auto position = _workers.find(worker);
    if(position == _workers.end()) throw PersonDoesNotExist(worker->getName(), worker->getTaxId());
    _workers.erase(position);
}

void WorkerManager::remove(unsigned position) {
    if(position >= _workers.size()) throw InvalidPersonPosition(position, _workers.size());
    auto it = _workers.begin();
    std::advance(it, position);
    _workers.erase(it);
}

bool WorkerManager::print(std::ostream &os, bool showData) {
    if (_workers.empty()){
        os << "No workers yet.\n";
        return false;
    }

    os << std::string(static_cast<int>(_workers.size()) / 10 + 3, util::SPACE)
    << util::column("NAME", true)
    << util::column("TAX ID");
    if (showData){
        os << util::column("SALARY")
        << util::column("TO DELIVER")
        << util::column("RATING");
    }
    else {
        os << util::column("LOGGED IN");
    }
    os << "\n";

    int count = 1;
    for (const auto& w: _workers){
        os << std::to_string(count++) + ". ";
        w->print(os, showData);
        os << "\n";
    }
    return true;
}

Worker* WorkerManager::getLessBusyWorker() {
    if (_workers.empty()) throw StoreHasNoWorkers();

    auto orderComp = [](const Worker *worker1, const Worker *worker2) {
        return worker1->getUndeliveredOrders() < worker2->getUndeliveredOrders();
    };
    return *std::min_element(_workers.begin(), _workers.end(), orderComp);
}




