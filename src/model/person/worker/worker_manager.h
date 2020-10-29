//
// Created by bdmendes on 29/10/20.
//

#ifndef FEUP_AEDA_PROJECT_WORKER_MANAGER_H
#define FEUP_AEDA_PROJECT_WORKER_MANAGER_H

#include "worker.h"

#include <vector>
#include <fstream>

class WorkerManager {
public:
    WorkerManager();
    bool has(Worker* worker) const;
    Worker* get(unsigned position);
    Worker* getAvailable();
    std::vector<Worker*> getAll();
    void changeSalary(unsigned position, float salary);
    void add(std::string name, float salary, int tributaryNumber = 999999999,
             Credential credential = {"worker", "worker"});
    void remove(Worker* worker);
    void remove(unsigned position);
    void read(std::ifstream& file);
    void write(std::ofstream& file);
private:
    std::vector<Worker*> _workers;
};


#endif //FEUP_AEDA_PROJECT_WORKER_MANAGER_H
