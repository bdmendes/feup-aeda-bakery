#include <iostream>

#include "model/person.h"
#include <stdexcept>
#include <algorithm>

int main() {
    //Date d1(29,02,2019,23,53);
    /*try {
        Date d1(29,02,2019,23,53);
    }
    catch(const std::runtime_error& e){
        std::cout << "chovem tchouriças, também";
    }*/

    Worker worker("João Manuel", 780, 254678390);
    Worker worker1("João Manuel", 780, 254678390);
    Store store("ola");
    //store.hireWorker(worker);
    std::vector<Worker> _workers;
    _workers.push_back(worker1);
    auto it = std::find(_workers.begin(), _workers.end(), worker);
    if(it == _workers.end())
        std::cout << "Not found" << std::endl;
    else
        std::cout << "Found" << std::endl;
    std::cout << worker1.operator==(worker) << std::endl;

    return 0;
}
