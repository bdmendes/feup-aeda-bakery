//
// Created by laimi on 15/10/2020.
//

#include "store.h"

#include <algorithm>
#include <numeric>
#include <utility>

ClientManager::ClientManager() : _clients() {
}

bool ClientManager::has(Client *client) const {
    return std::find(_clients.begin(),_clients.end(), client) != _clients.end();
}

Client *ClientManager::get(unsigned int position) {
    if (position >= _clients.size()) throw std::invalid_argument("Out of bounds client position");
    return _clients.at(position);
}

std::vector<Client *> ClientManager::getAll() {
    return _clients;
}

void ClientManager::add(Client *client) {
    if(std::find(_clients.begin(),_clients.end(),client) != _clients.end())
        throw PersonAlreadyExists(client->getName(), client->getTributaryNumber());
    _clients.push_back(client);
}

void ClientManager::remove(Client *client) {
    auto position = std::find(_clients.begin(), _clients.end(),client);
    if(position == _clients.end())
        throw PersonDoesNotExist(client->getName(), client->getTributaryNumber());
    _clients.erase(position);
}

void ClientManager::remove(unsigned int position) {
    if(position >= _clients.size()) throw std::invalid_argument("Out of bounds client position");
    _clients.erase(_clients.begin() + position);
}

WorkerManager::WorkerManager() : _workers(){
}

bool WorkerManager::has(Worker *client) const {
    return std::find(_workers.begin(),_workers.end(), client) != _workers.end();
}

Worker *WorkerManager::get(unsigned int position) {
    if (position >= _workers.size()) throw std::invalid_argument("Out of bounds worker position");
    return _workers.at(position);
}

std::vector<Worker *> WorkerManager::getAll() {
    return _workers;
}

void WorkerManager::add(Worker *worker) {
    if(std::find(_workers.begin(),_workers.end(),worker) != _workers.end())
        throw PersonAlreadyExists(worker->getName(), worker->getTributaryNumber());
    _workers.push_back(worker);
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

ProductManager::ProductManager(): _stock(){
}

bool ProductManager::has(Product *product) const {
    return std::find(_stock.begin(), _stock.end(), product) != _stock.end();
}

void ProductManager::add(Product *product) {
    if(std::find(_stock.begin(),_stock.end(),product) != _stock.end()) _stock.push_back(product);
    else throw ProductAlreadyExists(product->getName(),product->getPrice());
}

void ProductManager::remove(Product *product) {
    auto position = std::find(_stock.begin(),_stock.end(),product);
    if (position == _stock.end())
        throw ProductDoesNotExist(product->getName(),product->getPrice());
    _stock.erase(position);
}

Product *ProductManager::get(unsigned int position) {
    if (position >= _stock.size()) throw std::invalid_argument("Out of bounds product position");
    return _stock.at(position);
}

std::vector<Product *> ProductManager::getAll() {
    return _stock;
}

ProductManager::ProductManager(std::vector<Product *> stock) : _stock(std::move(stock)){
}

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
    _orders.push_back(new Order(*client,*_workerManager.getAvailable(),&_productManager));
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

Store::Store(std::string name) :
        _name(std::move(name)),
        productManager(),clientManager(),workerManager(),
        orderManager(productManager,clientManager,workerManager){
}

std::string Store::getName() const {
    return _name;
}

float Store::getEvaluation() const {
    std::vector<float> evaluations;
    for(const auto& order : orderManager.getAll())
        if(order->wasDelivered()) evaluations.push_back(order->getClientEvaluation());
    return std::accumulate(evaluations.begin(),evaluations.end(),0.0f) / evaluations.size();
}

void Store::setName(std::string name) {
    _name = std::move(name);
}
