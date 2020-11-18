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
    std::set<Worker*, PersonSmaller> getAll();
    Worker* getLessBusyWorker();

    Worker * setSalary(unsigned position, float salary);

    Worker* add(std::string name, int taxID = Person::DEFAULT_TAX_ID, float salary = Worker::DEFAULT_SALARY,
             Credential credential = {Worker::DEFAULT_USERNAME,Worker::DEFAULT_PASSWORD});
    void remove(Worker* worker);
    void remove(unsigned position);

    void read(const std::string& path);
    void write(const std::string& path);
    bool print(std::ostream& os, bool showData = true);

    Worker* getWorker(int taxID) const;

private:
    std::set<Worker*, PersonSmaller> _workers;
};


#endif //FEUP_AEDA_PROJECT_WORKER_MANAGER_H
