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

#include "util/util.h"

class WorkerManager {
public:
    WorkerManager();

    bool has(Worker* worker) const;

    Worker* get(unsigned position);
    Worker* getAvailable();
    std::set<Worker*, PersonSmaller> getAll();

    Worker * setSalary(unsigned position, float salary);

    Worker* add(std::string name, float salary, int taxID = Person::DEFAULT_TAX_ID,
             Credential credential = {"worker", "worker"});
    void remove(Worker* worker);
    void remove(unsigned position);

    void read(std::ifstream& file);
    void print(std::ostream& os);
private:
    std::set<Worker*, PersonSmaller> _workers;
};


#endif //FEUP_AEDA_PROJECT_WORKER_MANAGER_H
