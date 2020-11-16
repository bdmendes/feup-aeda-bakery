//
// Created by bdmendes on 29/10/20.
//

#ifndef FEUP_AEDA_PROJECT_CLIENT_H
#define FEUP_AEDA_PROJECT_CLIENT_H

#include "model/person/person.h"

#include <vector>
#include <string>

class Client : public Person {
public:
    explicit Client(std::string name, bool premium = false, int taxID = Person::DEFAULT_TAX_ID,
           Credential credential = {"client", "client"});

    bool isPremium() const;
    float getMeanEvaluation() const;
    unsigned getPoints() const;
    std::vector<float> getEvaluations() const;
    void setPremium(bool premium);
    void addPoints(unsigned points);
    void removePoints(unsigned points);
    void resetPoints();
    void addEvaluation(float evaluation);

    void print(std::ostream& os, bool showData = true);
private:
    bool _premium;
    unsigned _points;
    std::vector<float> _evaluations;
};


#endif //FEUP_AEDA_PROJECT_CLIENT_H
