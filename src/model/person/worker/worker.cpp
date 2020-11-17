//
// Created by bdmendes on 29/10/20.
//

#include <util/util.h>
#include "worker.h"

const char* Worker::DEFAULT_USERNAME = "worker";
const char* Worker::DEFAULT_PASSWORD = "worker";

Worker::Worker(std::string name, float salary, int taxID, Credential credential):
        Person(std::move(name), taxID, std::move(credential)), _salary{salary}, _undeliveredOrders(0){
}

float Worker::getSalary() const{
    return _salary;
}

unsigned Worker::getUndeliveredOrders() const {
    return _undeliveredOrders;
}

void Worker::addOrderToDeliver() {
    _undeliveredOrders++;
}

void Worker::removeOrderToDeliver(){
    _undeliveredOrders--;
}

void Worker::setSalary(float salary) {
    _salary = salary;
}

void Worker::print(std::ostream &os, bool showData) {
    os << util::column(getName(), true)
    << util::column(getTaxId() == Person::DEFAULT_TAX_ID ? "Not provided" : std::to_string(getTaxId()));
    if (showData){
        os << util::column(util::to_string(getSalary()) + " euros")
        << util::column(std::to_string(getUndeliveredOrders()) + " orders");
    }
    else os << util::column(isLogged() ? "Yes" : "No");
}

Credential Worker::getDefaultCredential() {
    return {DEFAULT_USERNAME, DEFAULT_PASSWORD};
}
