//
// Created by bdmendes on 29/10/20.
//

#include "worker_manager.h"
#include <algorithm>
#include <fstream>
#include <sstream>
#include <exception/person_exception.h>
#include <exception/store_exception.h>

WorkerManager::WorkerManager() : _workers(){
}

bool WorkerManager::has(Worker *worker) const {
    auto isEqual = [worker](const Worker* w2){
        return *worker == *w2;
    };
    return std::find_if(_workers.begin(),_workers.end(), isEqual) != _workers.end();
}

Worker *WorkerManager::get(unsigned int position) {
    if (position >= _workers.size()) throw std::invalid_argument("Out of bounds worker position");
    return _workers.at(position);
}

std::vector<Worker *> WorkerManager::getAll() {
    return _workers;
}

void WorkerManager::remove(Worker *worker) {
    if (_workers.empty()) throw StoreHasNoWorkers("Bakery Store"); // to change! no access to store name anymore
    auto position = std::find(_workers.begin(), _workers.end(),worker);
    if(position == _workers.end())
        throw PersonDoesNotExist(worker->getName(), worker->getTributaryNumber());
    _workers.erase(position);
}

Worker *WorkerManager::getAvailable() {
    if (_workers.empty()) throw StoreHasNoWorkers("Bakery Store"); // to change! no access to store name anymore

    auto orderComp = [](const Worker *worker1, const Worker *worker2) {
        return ((worker1->getOrders()) < (worker2->getOrders()));
    };
    return *std::min_element(_workers.begin(), _workers.end(), orderComp);
}

void WorkerManager::remove(unsigned int position) {
    if(position >= _workers.size()) throw std::invalid_argument("Out of bounds worker position");
    _workers.erase(_workers.begin() + position);
}

void WorkerManager::changeSalary(unsigned position, float salary) {
    if(position >= _workers.size()) throw std::invalid_argument("Out of bounds worker position");
    _workers.at(position)->setSalary(salary);
}

void WorkerManager::add(std::string name, float salary, int tributaryNumber, Credential credential) {
    auto* worker = new Worker(std::move(name),salary,tributaryNumber,std::move(credential));
    if (has(worker)) throw PersonAlreadyExists(worker->getName(),worker->getTributaryNumber());
    else _workers.push_back(worker);
}

void WorkerManager::read(std::ifstream &file) {

    if(!file){
        //TODO throw FileNotFound
    }
    else{
        std::string line;
        std::string name;
        float salary ;
        int tributaryNumber;
        Credential credential;

        while(getline(file, line)){
            std::stringstream worker(line);
            worker>>name>>salary>>tributaryNumber>>credential.username>>credential.password;

            std::replace(name.begin(), name.end(), '-', ' ');
            add(name, salary, tributaryNumber, credential);
        }
        file.close();
    }
}

void WorkerManager::write(std::ofstream &file) {
    if(!file){
        //TODO throw FileNotFound
    }
    else{

        std::string nameToSave;

        for(const auto & worker: _workers){
            nameToSave = worker->getName();
            std::replace(nameToSave.begin(), nameToSave.end(), ' ', '-');
            file<<nameToSave<<'\t'<<worker->getSalary()<<'\t'<<worker->getTributaryNumber()<<worker->getCredential().username<<worker->getCredential().password<<'\n';
        }
        file.close();
    }
}
