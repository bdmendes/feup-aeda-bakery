
#include "client.h"

#include <utility>
#include <util/util.h>
#include <numeric>

const char* Client::DEFAULT_USERNAME = "client";
const char* Client::DEFAULT_PASSWORD = "client";

Client::Client(std::string name, int taxID, bool premium, Credential credential):
        Person(std::move(name), taxID, std::move(credential)), _points{0}, _premium(premium), _evaluations(){
}

bool Client::isPremium() const {
    return _premium;
}

unsigned Client::getPoints() const {
    return _points;
}

void Client::setPremium(bool premium) {
    if (_premium && premium) throw std::invalid_argument("Already a premium client!");
    else if (!_premium && !premium) throw std::invalid_argument("Already a regular client!");
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

void Client::print(std::ostream &os, bool showData) {
    os << util::column(getName(), true)
    << util::column(getTaxId() == Person::DEFAULT_TAX_ID ? "Not provided" : std::to_string(getTaxId()));
    if (showData){
        os << util::column(isPremium() ? "Premium" : "Basic")
        << util::column(std::to_string(getPoints()) + " points")
        << util::column(getMeanEvaluation() != 0 ? util::to_string(getMeanEvaluation()) + " points": "None yet");
    }
    else os << util::column(isLogged() ? "Yes" : "No");
}

Credential Client::getDefaultCredential() {
    return {DEFAULT_USERNAME, DEFAULT_PASSWORD};
}

void Client::setPoints(unsigned int points) {
    _points = points;
}

void Client::addEvaluation(int evaluation) {
    _evaluations.push_back(evaluation);
}

float Client::getMeanEvaluation() const {
    return _evaluations.empty()? 0 :
    std::accumulate(_evaluations.begin(),_evaluations.end(),0.0f) / _evaluations.size();
}


