//
// Created by laimi on 15/10/2020.
//

#include "Person.h"
#include "../exceptions/store_exceptions.h"

#include <utility>
#include <algorithm>

Person::Person(std::string name, int tributaryNumber, Credential credential) :
    _name{std::move(name)}, _tributaryNumber{tributaryNumber}, _credential{ std::move(credential) } {
}

std::string Person::getName() const {
    return _name;
}

int Person::getTributaryNumber() const {
    return _tributaryNumber;
}

void Person::changeName(const std::string& name){
    _name = name;
}

Credential Person::getCredential() const {
    return _credential;
}

void Person::changeCredential(const Credential &credential) {
    // if no change, throw
    _credential = credential;
}

Client::Client(std::string name, int tributaryNumber, bool premium, Credential credential):
    Person(std::move(name), tributaryNumber, std::move(credential)), _points{0}, _premium(premium){
}

bool Client::isPremium() const {
    return _premium;
}

unsigned Client::getPoints() const {
    return _points;
}

float Client::getMeanEvaluation() const {
    float sum = 0;
    for (float ev: _evaluations) sum += ev;
    return sum / _evaluations.size();
}

std::vector<float> Client::getEvaluations() const {
    return _evaluations;
}

void Client::addPoints(unsigned int points) {
    _points += points;
}

void Client::resetPoints() {
    _points = 0;
}

unsigned Worker::getOrders() const {
    return _orders;
}

void Worker::addOrder() {
    _orders++;
}

void Worker::removeOrder(){
    _orders--;
}

void Worker::setSalary(float salary) {
    _salary = salary;
}

Worker::Worker(std::string name, int tributaryNumber, float salary, Credential credential):
    Person(std::move(name),tributaryNumber, std::move(credential)), _salary{salary}, _orders(0){
}

Boss::Boss(std::string name, int tributaryNumber, float salary, Credential credential) :
        Worker(std::move(name), tributaryNumber, salary, std::move(credential)),
        _stores (std::set<Store*, StoreComp>()){
}

Store *Boss::getStore(const std::string& name) {
    Store toFind = Store(name);
    auto it = _stores.find(&toFind);
    if (it == _stores.end()){
        throw StoreDoesNotExist(name);
    }
    return *it;
}
