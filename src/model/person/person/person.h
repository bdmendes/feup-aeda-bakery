//
// Created by bdmendes on 29/10/20.
//

#ifndef FEUP_AEDA_PROJECT_PERSON_H
#define FEUP_AEDA_PROJECT_PERSON_H

#include <string>
#include <stdexcept>

struct Credential {
    std::string username;
    std::string password;
    bool operator==(const Credential& c2) const{
        return username == c2.username && password == c2.password;
    }
};

class Person {
public:
    std::string getName() const;
    int getTributaryNumber() const;
    Credential getCredential() const;
    void changeCredential(const Credential& credential);
    void changeName(const std::string& name);

    bool operator==(const Person& p2) const{
        return _name == p2.getName() && _tributaryNumber == p2.getTributaryNumber();
    }
protected:
    Person(std::string name, int tributaryNumber, Credential credential);
private:
    std::string _name;
    int _tributaryNumber;
    Credential _credential;
};

#endif //FEUP_AEDA_PROJECT_PERSON_H
