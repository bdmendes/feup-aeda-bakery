//
// Created by bdmendes on 14/11/20.
//

#include "worker_dashboard.h"

WorkerDashboard::WorkerDashboard(Store &store, Worker *worker) : UI(store), _worker(worker){

}

void WorkerDashboard::show() {
    printLogo();
    printLogo();
    std::cout << "Worker dashboard is work in progress. press enter to exit.";
    std::string input;
    std::getline(std::cin,input);
}
