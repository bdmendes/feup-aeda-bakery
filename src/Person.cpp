//
// Created by laimi on 15/10/2020.
//

#include "Person.h"

#include <utility>
#include <algorithm>

Person::Person(std::string name, int tributaryNumber) :
    _name{std::move(name)}, _tributaryNumber{tributaryNumber},
    _orders{std::vector<const Shipping*>()}{

}

std::string Person::getName() const {
    return _name;
}

int Person::getTributaryNumber() const {
    return _tributaryNumber;
}

void Person::addOrder(const Shipping *order) {
    _orders.push_back(order);
}

bool Person::removeOrder(const Shipping *order) {
    for (auto it = _orders.begin(); it != _orders.end(); ++it){
        if (*it == order){
            _orders.erase(it);
            return true;
        }
    }
    return false;
}

std::vector<const Shipping *> Person::getOrders() {
    return _orders;
}

Client::Client(const std::string name, int tributaryNumber, bool premium):
    Person(name,tributaryNumber), _premium{premium}, _points{0}{

}

bool Client::isPremium() const {
    return _premium;
}

unsigned Client::getPoints() const {
    return _points;
}

void Client::addOrder(const Shipping* order) {
    _orders.push_back(order);
    //_points += order.getTotalPrice();
    if (_premium && _points >= 100){
        //...
    }
    else if (!_premium && _points >= 200){
        //...
    }
}

float Client::getMeanEvaluation() const {
    float sum = 0;
    for (float ev: _evaluations) sum += ev;
    return sum / _evaluations.size();
}

std::vector<float> Client::getEvaluations() const {
    return _evaluations;
}

Worker::Worker(std::string name, int tributaryNumber, float salary):
    Person(name,tributaryNumber), _salary{salary}{

}
