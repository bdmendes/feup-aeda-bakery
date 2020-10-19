//
// Created by laimi on 15/10/2020.
//

#ifndef SRC_PERSON_H
#define SRC_PERSON_H

#include <string>
#include <vector>
#include <map>

struct Credential {
    std::string userName;
    std::string password;
};

class Person {
public:
    Person(std::string name, int tributaryNumber,
           Credential credential = {"person", "person"} );
    std::string getName() const;
    int getTributaryNumber() const;
    Credential getCredential() const;
    void changeCredential (const Credential& credential);
    void changeName(const std::string& name);

private:
    std::string _name;
    int _tributaryNumber;
    Credential _credential;

};

class Client : public Person {
public:
    Client(std::string name, int tributaryNumber, bool premium,
           Credential credential = {"client", "client"});
    bool isPremium() const;
    unsigned getPoints() const;
    void addPoints(unsigned points);
    float getMeanEvaluation() const;
    std::vector<float> getEvaluations() const;
private:
    bool _premium;
    unsigned _points;
    std::vector<float> _evaluations;
};

class Worker : public Person{
public:
    Worker(std::string name, int tributaryNumber, float salary,
           Credential credential = {"worker", "worker"});
private:
    float _salary;
};

class Boss : public Worker {
public:
    Boss(std::string name, int tributaryNumber, float salary,
         Credential credential = {"boss", "boss"});
};

#endif //SRC_PERSON_H
