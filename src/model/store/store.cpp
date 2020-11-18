//
// Created by laimi on 15/10/2020.
//

#include "store.h"

#include <numeric>
#include <utility>

Store::Store(std::string name) :
        _name(std::move(name)),
        productManager(),clientManager(),workerManager(),
        orderManager(&productManager,&clientManager,&workerManager),
        boss("Boss", Person::DEFAULT_TAX_ID, {Boss::DEFAULT_USERNAME,Boss::DEFAULT_PASSWORD}){
}

std::string Store::getName() const {
    return _name;
}

int Store::getEvaluation() const {
    std::vector<int> evaluations;
    int count = 0;
    for(const auto& order : orderManager.getAll()) {
        if (order->wasDelivered()) evaluations.push_back(order->getClientEvaluation());
        count++;
    }
    return count ? std::accumulate(evaluations.begin(),evaluations.end(),0) / count : 0;
}

void Store::setName(const std::string& name) {
    _name = name;
}

float Store::getProfit() const {
    float profit = 0.0f;
    for (const auto& o: orderManager.getAll()){
        if (o->wasDelivered()) profit += o->getFinalPrice();
    }
    return profit;
}

std::string Store::read(const std::string &dataFolderPath, bool doReset) {
    try {
        if (doReset) reset();
        boss.read(dataFolderPath + "/boss.txt");
        productManager.read(dataFolderPath + "/products.txt");
        clientManager.read(dataFolderPath + "/clients.txt");
        workerManager.read(dataFolderPath + "/workers.txt");
        orderManager.read(dataFolderPath + "/orders.txt");
    }
    catch (std::exception& e){
        return "Import failed!\n" + std::string(e.what());
    }
    return "Import succeeded.";
}

void Store::reset() {
    boss = Boss();
    productManager = {};
    clientManager = {};
    workerManager = {};
    orderManager = OrderManager(&productManager,&clientManager,&workerManager);
}

std::string Store::write(const std::string& dataFolderPath) {
    try {
        boss.write(dataFolderPath + "/boss.txt");
        productManager.write(dataFolderPath + "/products.txt");
        clientManager.write(dataFolderPath + "/clients.txt");
        workerManager.write(dataFolderPath + "/workers.txt");
        orderManager.write(dataFolderPath + "/orders.txt");
    }
    catch (std::exception& e){
        return "Export failed!\n" + std::string(e.what());
    }
    return "Export succeeded.";
}

