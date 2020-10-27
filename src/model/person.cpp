//
// Created by laimi on 15/10/2020.
//

#include "person.h"

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

Client::Client(std::string name, bool premium, int tributaryNumber, Credential credential):
        Person(std::move(name), tributaryNumber, std::move(credential)), _points{0}, _premium(premium),
        _evaluations(std::vector<float>()){
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

void Client::resetPoints() {
    _points = 0;
}

void Client::addPoints(unsigned points) {
    _points += points;
}

void Client::removePoints(unsigned int points) {
    _points -= points;
}

void Client::setPremium(bool premium) {
    _premium = premium;
}

void Client::addEvaluation(float evaluation) {
    _evaluations.push_back(evaluation);
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

Worker::Worker(std::string name, float salary, int tributaryNumber, Credential credential):
        Person(std::move(name), tributaryNumber, std::move(credential)), _salary{salary}, _orders(0){
}

float Worker::getSalary() const{
    return _salary;
}

Boss::Boss(std::string name, float salary, int tributaryNumber, Credential credential) :
        Worker(std::move(name), salary, tributaryNumber, std::move(credential)),
        _stores(std::vector<Store*>()){
}

Store* Boss::getStore(const std::string& name) {
    auto comp = [name](const Store* store){
        return store->getName() == name;
    };
    auto it = std::find_if(_stores.begin(),_stores.end(),comp);
    if (it == _stores.end()) throw StoreDoesNotExist(name);
    return *it;
}

