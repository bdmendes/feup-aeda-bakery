#include <iostream>

#include "model/person/person/person.h"
#include "model/person/worker/worker.h"
#include "model/store/store.h"
#include <stdexcept>
#include <algorithm>
#include <vector>


int main() {
    /*
    Store s;
    s.workerManager.add("João Malheiro",400);
    s.workerManager.add("Álvaro",600);
    s.workerManager.add("Sofia Teixeira",50000);
    s.workerManager.add("Adelaide Santos",50000);
    s.workerManager.add("Nuno Costa",20000);
    s.workerManager.add("Jorge Silva",1000000);
    s.workerManager.add("José Eduardo",10000);
    s.workerManager.add("João Canas",1000);
    s.workerManager.write(std::cout);
    */

    Store s;
    Product* p1 = s.productManager.addBread("Huge bread",0.2,false);
    Product* p2 = s.productManager.addBread("Very small indeed",0.1);
    Product* p3 = s.productManager.addCake("Tarte de morango",0.5,CakeCategory::PIE);
    Product* p4 = s.productManager.addCake("Aquele pão de ló",0.7,CakeCategory::PUFF_PASTRY);
    s.workerManager.add("Bandida",2000);
    Client* broccoli = s.clientManager.add("Brócolo");
    Order* order = s.orderManager.add(broccoli);
    order->addProduct(p1,4);
    order->addProduct(p2);
    order->addProduct(p3,2);
    order->addProduct(p4);
    s.orderManager.write(std::cout);
}
