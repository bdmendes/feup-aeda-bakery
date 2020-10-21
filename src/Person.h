//
// Created by laimi on 15/10/2020.
//

#ifndef SRC_PERSON_H
#define SRC_PERSON_H

#include <string>
#include <vector>
#include <map>

class Person {
public:
    Person(std::string name, int tributaryNumber,
           std::string username = "person", std::string password = "person");
    std::string getName() const;
    int getTributaryNumber() const;
    std::string getUsername() const;
    std::string getPassword() const;
    void changeUsername(const std::string& username);
    void changePassword(const std::string& password);
    void changeName(const std::string& name);

private:
    std::string _name;
    int _tributaryNumber;
    Credential _credential;
};

class Client : public Person {
public:
    Client(std::string name, int tributaryNumber, bool premium,
           std::string username = "client", std::string password = "client");
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
           std::string username = "worker", std::string password = "worker");
    unsigned getOrders() const;
    void addOrder();
    void removeOrder();
    void setSalary(float salary);
private:
    float _salary;
    unsigned _orders;
};

class Boss : public Worker {
public:
    Boss(std::string name, int tributaryNumber, float salary,
         std::string username = "boss", std::string password = "boss");
};

#endif //SRC_PERSON_H
