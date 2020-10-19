//
// Created by laimi on 15/10/2020.
//

#include "Person.h"

#include <utility>
#include <algorithm>

Person::Person(std::string name, int tributaryNumber, Credential credential) :
    _name{std::move(name)}, _tributaryNumber{tributaryNumber}, _credential{ credential } {

}

std::string Person::getName() const {
    return _name;
}

int Person::getTributaryNumber() const {
    return _tributaryNumber;
}

Credential Person::getCredential() const {
    return _credential;
}

void Person::changeCredential(const Credential& credential) {
    _credential = credential;
}

void Person::changeName(const std::string& name){
    _name = name;
}

Client::Client(std::string name, int tributaryNumber, bool premium, Credential credential):
    Person(std::move(name), tributaryNumber, std::move(credential)){

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

Worker::Worker(std::string name, int tributaryNumber, float salary, Credential credential):
    Person(std::move(name),tributaryNumber, std::move(credential)), _salary{salary}{

}

Boss::Boss(std::string name, int tributaryNumber, float salary, Credential credential) :
        Worker(std::move(name), tributaryNumber, salary, std::move(credential)) {

}
