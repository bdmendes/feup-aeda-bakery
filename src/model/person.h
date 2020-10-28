//
// Created by laimi on 15/10/2020.
//

#ifndef SRC_PERSON_H
#define SRC_PERSON_H

#include "store.h"
#include "product.h"

#include <string>
#include <vector>
#include <map>

class Store;

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

class Client : public Person {
public:
    Client(std::string name, bool premium = false, int tributaryNumber = 999999999,
           Credential credential = {"client", "client"});
    bool isPremium() const;
    unsigned getPoints() const;
    void addPoints(unsigned points);
    void removePoints(unsigned points);
    void resetPoints();
    float getMeanEvaluation() const;
    void addEvaluation(float evaluation);
    void setPremium(bool premium);
private:
    bool _premium;
    unsigned _points;
    std::vector<float> _evaluations;
};

class Worker : public Person{
public:
    Worker(std::string name, float salary, int tributaryNumber = 999999999,
           Credential credential = {"worker", "worker"});
    unsigned getOrders() const;
    void addOrder();
    void removeOrder();
    void setSalary(float salary);
    float getSalary() const;
private:
    float _salary;
    unsigned _orders;
};

#endif //SRC_PERSON_H
