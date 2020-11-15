//
// Created by bdmendes on 29/10/20.
//

#include "worker_manager.h"

WorkerManager::WorkerManager() : _workers(std::set<Worker*, PersonSmaller>()){
}

bool WorkerManager::has(Worker *worker) const {
    return std::find(_workers.begin(),_workers.end(), worker) != _workers.end();
}

Worker* WorkerManager::get(unsigned int position) {
    if (position >= _workers.size()) throw InvalidPersonPosition(position, _workers.size());
    auto it = _workers.begin(); std::advance(it, position);
    return *it;
}

Worker* WorkerManager::getAvailable() {
    if (_workers.empty()) throw StoreHasNoWorkers(); // to change! no access to store name anymore

    auto orderComp = [](const Worker *worker1, const Worker *worker2) {
        return ((worker1->getOrders()) < (worker2->getOrders()));
    };
    return *std::min_element(_workers.begin(), _workers.end(), orderComp);
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

Worker* WorkerManager::add(std::string name, float salary, int taxID, Credential credential) {
    auto* worker = new Worker(std::move(name), salary, taxID, std::move(credential));
    if (has(worker)) throw PersonAlreadyExists(worker->getName(), worker->getTaxId());
    else _workers.insert(worker);
    return worker;
}

void WorkerManager::remove(Worker *worker) {
    if (_workers.empty()) throw StoreHasNoWorkers(); // to change! no access to store name anymore
    auto position = std::find(_workers.begin(), _workers.end(),worker);
    if(position == _workers.end())
        throw PersonDoesNotExist(worker->getName(), worker->getTaxId());
    _workers.erase(position);
}

void WorkerManager::remove(unsigned position) {
    if(position >= _workers.size()) throw InvalidPersonPosition(position, _workers.size());
    auto it = _workers.begin();
    std::advance(it, position);
    _workers.erase(it);
}

void WorkerManager::print(std::ostream &os) {
    int numSpaces = static_cast<int>(std::to_string(_workers.size()).size() + 2);
    os << std::string(numSpaces,util::SPACE)
    << util::column("NAME", true)
    << util::column("TAX ID")
    << util::column("SALARY")
    << util::column("DELIVERED") << "\n";

    int count = 1;
    for (const auto& w: _workers){
        os << std::setw(numSpaces) << std::left << std::to_string(count++) + ". ";
        w->write(os);
        os << "\n";
    }
}




