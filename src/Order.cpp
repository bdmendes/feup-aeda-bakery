//
// Created by laimi on 15/10/2020.
//

#include "Order.h"

Order::Order(const std::map<Product, unsigned int> &products, Client &client, Worker &worker) :
        _products{std::map<Product, unsigned int>()},
        _client{client}, _worker(worker), _clientEvaluation(0){
    //Verifies if client has discount in this order
    if((_client.isPremium() && _client.getPoints() >= 100) || (!_client.isPremium() && _client.getPoints() >=200)) {
        _discount == true;
        _client.addPoints(_client.getPoints()*(-1)); //Reset client's points
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

float Order::getClientEvaluation() const {
    return _clientEvaluation;
}

float Order::getTotalPrice() const {
    return _totalPrice;
}

float Order::calculateFinalPrice() {
    for(const auto &product : _products){
        _totalPrice += (product.first.getPrice()*product.second);
    }
    _client.addPoints(10*_totalPrice); //For each euro adds 10 points
    if(_client.isPremium() && hasDiscount())
        return (_totalPrice*0.95);           //Premium clients have a 5% discount when reached 100 points
    else if(!_client.isPremium() && hasDiscount())
        return (_totalPrice*0.98);           //Normal clients have a 2% discount when reached 200 points
    return _totalPrice;
}

void Order::obtainClientEvaluation(float evaluation) {
    _clientEvaluation = evaluation;
}


