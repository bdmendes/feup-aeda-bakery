//
// Created by bdmendes on 29/10/20.
//

#include <util/util.h>
#include "worker.h"

Worker::Worker(std::string name, float salary, int taxID, Credential credential):
        Person(std::move(name), taxID, std::move(credential)), _salary{salary}, _orders(0){
}

float Worker::getSalary() const{
    return _salary;
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

void Worker::write(std::ostream &os, bool showData) {
    os << util::column(getName(), true)
    << util::column(getTaxId() == Person::DEFAULT_TAX_ID ? "Not provided" : std::to_string(getTaxId()));
    if (showData){
        os << util::column(util::to_string(getSalary()) + " euros")
        << util::column(std::to_string(getOrders()) + " orders");
    }
}
