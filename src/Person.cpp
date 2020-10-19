//
// Created by laimi on 15/10/2020.
//

#include "Person.h"

#include <utility>
#include <algorithm>

Person::Person(std::string name, int tributaryNumber) :
    _name{std::move(name)}, _tributaryNumber{tributaryNumber},{

}

std::string Person::getName() const {
    return _name;
}

int Person::getTributaryNumber() const {
    return _tributaryNumber;
}


Client::Client(const std::string name, int tributaryNumber, bool premium):
    Person(name,tributaryNumber), _premium{premium}, _points{0}{

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

Worker::Worker(std::string name, int tributaryNumber, float salary):
    Person(name,tributaryNumber), _salary{salary}{

}
