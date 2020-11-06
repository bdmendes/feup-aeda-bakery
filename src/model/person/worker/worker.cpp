//
// Created by bdmendes on 29/10/20.
//

#include <util/util.h>
#include "worker.h"

Worker::Worker(std::string name, float salary, int tributaryNumber, Credential credential):
        Person(std::move(name), tributaryNumber, std::move(credential)), _salary{salary}, _orders(0){
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

void Worker::write(std::ostream &os) {
    os << util::column(getName(), true)
    << util::column(getTaxId() == DEFAULT_TAXID ? "Not provided" : std::to_string(getTaxId()))
    << util::column(util::to_string(getSalary()) + " euros")
    << util::column(std::to_string(getOrders()) + " orders");
}
