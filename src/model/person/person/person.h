//
// Created by bdmendes on 29/10/20.
//

#ifndef FEUP_AEDA_PROJECT_PERSON_H
#define FEUP_AEDA_PROJECT_PERSON_H

#include <exception/person_exception.h>

#include <string>
#include <stdexcept>
#include <set>

const int DEFAULT_TAXID = 999999999;

struct Credential {
    std::string username;
    std::string password;
    bool operator==(const Credential& c2) const{
        return username == c2.username && password == c2.password;
    }
};

class Person {
public:
    Person(std::string name, int tributaryNumber, Credential credential);
    std::string getName() const;
    int getTaxId() const;
    Credential getCredential() const;

    void changeName(const std::string& name);
    void changeCredential(const Credential& credential);

    bool operator<(const Person& p2) const;
    bool operator==(const Person& p2) const;
private:
    std::string _name;
    int _taxId;
    Credential _credential;
};

struct PersonSmaller{
    bool operator()(const Person* p1, const Person* p2) const{
        return *p1 < *p2;
    }
};

#endif //FEUP_AEDA_PROJECT_PERSON_H
