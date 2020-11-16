//
// Created by bdmendes on 29/10/20.
//

#ifndef FEUP_AEDA_PROJECT_CLIENT_H
#define FEUP_AEDA_PROJECT_CLIENT_H

#include "../person/person.h"

#include <vector>
#include <string>

class Client : public Person {
public:
    explicit Client(std::string name, int tributaryNumber = 999999999, bool premium = false,
           Credential credential = {"client", "client"});

    bool isPremium() const;
    float getMeanEvaluation() const;
    unsigned getPoints() const;
    void setPoints(unsigned  points);
    std::vector<float> getEvaluations() const;
    void setPremium(bool premium);
    void addPoints(unsigned points);
    void removePoints(unsigned points);
    void resetPoints();
    void addEvaluation(float evaluation);
  
    void print(std::ostream& os);

    //bool operator==(const Client& c2) const;
private:
    bool _premium;
    unsigned _points;
    std::vector<float> _evaluations;
};


#endif //FEUP_AEDA_PROJECT_CLIENT_H
