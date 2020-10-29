//
// Created by bdmendes on 29/10/20.
//

#include "worker.h"

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

unsigned Worker::getOrders() const {
    return _orders;
}