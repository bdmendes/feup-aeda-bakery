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
    explicit Client(std::string name, int taxID = Person::DEFAULT_TAX_ID, bool premium = false,
           Credential credential = {DEFAULT_USERNAME, DEFAULT_PASSWORD});

    bool isPremium() const;
    unsigned getPoints() const;
    void setPremium(bool premium);
    void addPoints(unsigned points);
    void removePoints(unsigned points);
    void resetPoints();
    void setPoints(unsigned points);

    void print(std::ostream& os, bool showData = true);

    Credential getDefaultCredential() override;
    static const char* DEFAULT_USERNAME;
    static const char* DEFAULT_PASSWORD;
private:
    bool _premium;
    unsigned _points;
};


#endif //FEUP_AEDA_PROJECT_CLIENT_H
