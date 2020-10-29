//
// Created by bdmendes on 29/10/20.
//

#include "client.h"

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
