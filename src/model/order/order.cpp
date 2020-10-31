//
// Created by laimi on 15/10/2020.
//

#include "order.h"

#include <utility>

Order::Order(Client &client, Worker &worker, Date date) :
        _client{client}, _worker(worker), _clientEvaluation(0), _delivered(false),
        _totalPrice(0.0f), _date(std::move(date)), _products(std::map<Product*, unsigned int>()){
    updateTotalPrice();
    _client.addPoints(10* static_cast<int>(_totalPrice)); //For each euro adds 10 points
}

bool Order::hasDiscount() const {
    return _client.getPoints() >= 100*_client.isPremium() + 200*!_client.isPremium();
}

bool Order::hasProduct(Product* product){
    return _products.find(product) != _products.end() && _products[product] > 0;
}

bool Order::wasDelivered() const {
    return _delivered;
}

const Worker& Order::getWorker() const {
    return _worker;
}

const Client& Order::getClient() const{
    return _client;
}

std::map<Product*, unsigned int> Order::getProducts() const {
    return _products;
}

float Order::getClientEvaluation() const {
    if (!_delivered) throw OrderWasNotDeliveredYet(_client,_worker,_date);
    return _clientEvaluation;
}

float Order::getFinalPrice() const {
    return hasDiscount() ? (_client.isPremium() ? 0.95f*_totalPrice : 0.98f*_totalPrice) : _totalPrice;
}

float Order::getTotal() const {
    return _totalPrice;
}

Date Order::getDate() const {
    return _date;
}

void Order::updateTotalPrice() {
    _totalPrice = 0;
    for(const auto &product : _products){
        _totalPrice += (product.first->getPrice() * product.second);
    }
}

Product * Order::addProduct(Product* product, unsigned quantity) {
    if (_delivered) throw OrderWasAlreadyDelivered(_client,_worker,_date);
    if (hasProduct(product)) _products[product] += quantity;
    else _products[product] = quantity;
    updateTotalPrice();
    return product;
}

Product * Order::removeProduct(Product* product, unsigned quantity) {
    if (_delivered) throw OrderWasAlreadyDelivered(_client,_worker,_date);
    if (hasProduct(product)){
        if (_products[product] < quantity) quantity = _products[product];
        _products[product] -= quantity;
        if (_products[product] == 0) _products.erase(product);
        updateTotalPrice();
    }
    else throw ProductDoesNotExist(product->getName(),product->getPrice());
    return product;
}

Product * Order::removeProduct(Product *product) {
    if (_delivered) throw OrderWasAlreadyDelivered(_client,_worker,_date);
    if (hasProduct(product)){
        _products.erase(product);
        updateTotalPrice();
    }
    else throw ProductDoesNotExist(product->getName(),product->getPrice());
    return product;
}

Product * Order::removeProduct(unsigned int position, unsigned int quantity) {
    auto it = _products.begin();
    if (position < _products.size()){
        if (_delivered) throw OrderWasAlreadyDelivered(_client,_worker,_date);
        while (position--) it++;
        if (it->second < quantity) quantity = it->second;
        it->second -= quantity;
        if (it->second == 0) _products.erase(it);

        updateTotalPrice();
        _products.erase(it);
        updateTotalPrice();
    }
    else throw InvalidProductPosition(position, _products.size());
    return it->first;
}

Product * Order::removeProduct(unsigned int position) {
    auto it = _products.begin();
    if (position < _products.size()){
        if (_delivered) throw OrderWasAlreadyDelivered(_client,_worker,_date);
        while (position--) it++;
        _products.erase(it);

        updateTotalPrice();
        _products.erase(it);
        updateTotalPrice();
    }
    else throw InvalidProductPosition(position, _products.size());
    return it->first;
}

void Order::deliver(float clientEvaluation) {
    if (_delivered) throw OrderWasAlreadyDelivered(_client,_worker,_date);
    if (clientEvaluation < 0 || clientEvaluation > 5) throw InvalidOrderEvaluation(clientEvaluation,_client);

    _clientEvaluation = clientEvaluation;
    _delivered = true;
    _client.addEvaluation(clientEvaluation);

    if (hasDiscount()) _client.resetPoints();
    _client.addPoints(10* static_cast<int>(_totalPrice)); //For each euro adds 10 points
}

bool Order::operator==(const Order &rhs) const {
    return _client == rhs.getClient() && _worker == rhs.getWorker()
    && _delivered && rhs.wasDelivered() && _products == rhs.getProducts();
}

bool Order::operator<(const Order &o2) const {
    return _date < o2.getDate();
}
