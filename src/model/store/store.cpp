
#include "store.h"

#include <numeric>

Store::Store(std::string name) :
        _name(std::move(name)),
        locationManager(),
        productManager(),
        clientManager(),
        workerManager(&locationManager),
        orderManager(&productManager,&clientManager,&workerManager,&locationManager),
        boss("Boss", Person::DEFAULT_TAX_ID, {Boss::DEFAULT_USERNAME,Boss::DEFAULT_PASSWORD})
        {}

std::string Store::getName() const {
    return _name;
}

int Store::getEvaluation() const {
    std::vector<int> evaluations;
    int count = 0;
    std::priority_queue<OrderEntry> orders = orderManager.getAll();
    while(!orders.empty()){
        const auto& order = orders.top().getOrder();
        orders.pop();
        if(order->wasDelivered()){
            evaluations.push_back(order->getClientEvaluation());
            count++;
        }
    }
    return count ? std::accumulate(evaluations.begin(),evaluations.end(),0) / count : 0;
}

void Store::setName(const std::string& name) {
    _name = name;
}

float Store::getProfit() const {
    float profit = 0.0f;
    std::priority_queue<OrderEntry> orders = orderManager.getAll();
    while(!orders.empty()){
        const auto& order = orders.top().getOrder();
        orders.pop();
        if(order->wasDelivered()) profit += order->getFinalPrice();
    }
    return profit;
}

std::string Store::read(const std::string &dataFolderPath) {
    try {
        boss.read(dataFolderPath + "/boss.txt");
        locationManager.read(dataFolderPath + "/locations.txt");
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

std::string Store::write(const std::string& dataFolderPath) {
    try {
        boss.write(dataFolderPath + "/boss.txt");
        locationManager.write(dataFolderPath + "/locations.txt");
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
