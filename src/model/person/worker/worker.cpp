
#include <util/util.h>
#include <numeric>
#include <utility>
#include "worker.h"

const char* Worker::DEFAULT_USERNAME = "worker";
const char* Worker::DEFAULT_PASSWORD = "worker";
const float Worker::DEFAULT_SALARY = 1000;

Worker::Worker(std::string location, std::string name, unsigned long taxID, float salary, Credential credential):
        Person(std::move(name), taxID, std::move(credential), PersonRole::WORKER),
        _salary{salary}, _undeliveredOrders(0), _evaluations(), _location(std::move(location)){
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
        << util::column(std::to_string(getUndeliveredOrders()) + " orders")
        << util::column(getMeanEvaluation() != 0 ? util::to_string(getMeanEvaluation()) + " points" : "None yet")
        << util::column(getLocation());
    }
    else os << util::column(isLogged() ? "Yes" : "No");
}

Credential Worker::getDefaultCredential() {
    return {DEFAULT_USERNAME, DEFAULT_PASSWORD};
}

void Worker::addEvaluation(unsigned int evaluation) {
    _evaluations.push_back(evaluation);
}

float Worker::getMeanEvaluation() const {
    return _evaluations.empty()? 0 :
           std::accumulate(_evaluations.begin(),_evaluations.end(),0.0f) / _evaluations.size();
}

std::string Worker::getLocation() const {
    return _location;
}
