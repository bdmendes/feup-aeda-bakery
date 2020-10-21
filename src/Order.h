//
// Created by laimi on 15/10/2020.
//

#ifndef SRC_ORDER_H
#define SRC_ORDER_H

#include <utility>
#include <vector>
#include <ctime>
#include <iostream>
#include <map>

#include "Person.h"
#include "Product.h"

class Order {
public:
    class Date;
    Order(const std::map<Product, unsigned int> &products, Client& client, Worker& worker);
    bool hasDiscount() const;
    Worker* getWorker() const;
    const Client* getClient() const;
    float getClientEvaluation() const ;
    float getTotalPrice() const;
    float calculateFinalPrice();
    void obtainClientEvaluation(float evaluation);
private:
    std::map<Product, unsigned int> _products;
    float _totalPrice;
    Client& _client;
    Worker& _worker;
    float _clientEvaluation;
    bool _discount;
};

class Date{
public:
    Date(){
        std::time_t t = std::time(0);
        std::tm*currentTime = std::localtime(&t);
        _minute = currentTime->tm_min;
        _hour = currentTime->tm_hour;
        _day = currentTime->tm_mday;
        _month = currentTime->tm_mon;
        _year = currentTime->tm_year+1900;
    }
    std::ostream & operator<<(std::ostream & out){
        out << _hour << ":" << _minute << " " << _day << "/" << _month << "/" << _year << std::endl;
        return out;
    }
private:
    unsigned _minute, _hour, _day, _month, _year;
};






#endif //SRC_ORDER_H
