//
// Created by bdmendes on 29/10/20.
//

#ifndef FEUP_AEDA_PROJECT_WORKER_MANAGER_H
#define FEUP_AEDA_PROJECT_WORKER_MANAGER_H

#include "worker.h"

#include <exception/store_exception.h>

#include <algorithm>
#include <vector>
#include <fstream>

class WorkerManager {
public:
    WorkerManager();

    bool has(Worker* worker) const;

    Worker* get(unsigned position);
    Worker* getAvailable();
    std::set<Worker*, SmallerClient> getAll();

    Worker * changeSalary(unsigned position, float salary);

    Worker* add(std::string name, float salary, int tributaryNumber = 999999999,
             Credential credential = {"worker", "worker"});
    void remove(Worker* worker);
    void remove(unsigned position);

    void read(std::ifstream& file);
    void write(std::ofstream& file);
private:
    std::set<Worker*, SmallerClient> _workers;
};


#endif //FEUP_AEDA_PROJECT_WORKER_MANAGER_H
