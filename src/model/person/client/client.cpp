//
// Created by bdmendes on 29/10/20.
//

#include "client.h"

#include <utility>
#include <util/util.h>

Client::Client(std::string name, bool premium, int taxID, Credential credential):
        Person(std::move(name), taxID, std::move(credential)), _points{0}, _premium(premium),
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

std::vector<float> Client::getEvaluations() const {
    return _evaluations;
}

void Client::setPremium(bool premium) {
    _premium = premium;
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

void Client::addEvaluation(float evaluation) {
    _evaluations.push_back(evaluation);
}

void Client::print(std::ostream &os, bool showData) {
    os << util::column(getName(), true)
    << util::column(getTaxId() == Person::DEFAULT_TAX_ID ? "Not provided" : std::to_string(getTaxId()));
    if (showData){
        os << util::column(isPremium() ? "Premium" : "Basic")
                << util::column(std::to_string(getPoints()) + " points");
    }
}
