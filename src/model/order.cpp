//
// Created by laimi on 15/10/2020.
//

#include "order.h"

Order::Order(const std::map<Product*, unsigned int> &products, Client &client, Worker &worker) :
        _products{std::map<Product*, unsigned int>()},
        _client{client}, _worker(worker), _clientEvaluation(0), _delivered(false){
    calculateDiscount();
    calculateFinalPrice();
}

void Order::calculateDiscount(){
    if((_client.isPremium() && _client.getPoints() >= 100) || (!_client.isPremium() && _client.getPoints() >= 200)) {
        _discount = true;
        _client.resetPoints();
    }
}

bool Order::hasDiscount() const {
    return _discount;
}

Worker* Order::getWorker() const {
    return &_worker;
}

const Client* Order::getClient() const{
    return &_client;
}

double Order::getClientEvaluation() const {
    return _clientEvaluation;
}

double Order::getTotalPrice() const {
    return _totalPrice;
}

void Order::calculateFinalPrice() {
    _totalPrice = 0;
    for(const auto &product : _products){
        _totalPrice += (product.first->getPrice() * product.second);
    }

    _client.addPoints(10*_totalPrice); //For each euro adds 10 points

    if(_client.isPremium() && hasDiscount())
        _totalPrice *= 0.95;           //Premium clients have a 5% discount when reached 100 points
    else if(!_client.isPremium() && hasDiscount())
        _totalPrice *= 0.98;           //Normal clients have a 2% discount when reached 200 points
}

void Order::deliver(float clientEvaluation) {
    _clientEvaluation = clientEvaluation;
    _delivered = true;
}

