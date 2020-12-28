
#ifndef FEUP_AEDA_PROJECT_WORKER_MANAGER_H
#define FEUP_AEDA_PROJECT_WORKER_MANAGER_H

#include "worker.h"
#include "../../store/location_manager.h"

#include <exception/store_exception.h>

#include <algorithm>
#include <vector>
#include <fstream>
#include <unordered_set>

#include "util/util.h"
/**
 * Hash Table where the key is determined by the worker´s name
 */
struct WorkerHash
{
    int operator() (const Worker* worker) const
    {
        int hashValue = 0;
        for (const auto & item: worker->getName()){
            hashValue = hashValue * 37 + item;
        }
        return hashValue;
    }

    bool operator() (const Worker* worker1, const Worker* worker2) const
    {
        return *worker1 == *worker2;
    }
};

typedef std::unordered_set<Worker*, WorkerHash, WorkerHash> tabHWorker;

/**
 * Class that manages the store workers.
 */
class WorkerManager {
public:
    /**
     * Creates a new WorkerManager object.
     */
    explicit WorkerManager(LocationManager* lm);

    /**
     * Destructs the WorkerManager object.
     */
    ~WorkerManager();

    /**
     * Checks if the worker is on the workers list.
     *
     * @param worker the worker to check if is on the list
     * @return true, if the worker is on workers list; false, otherwise
     */
    bool has(Worker* worker) const;

    /**
     * Gets the worker on the workers list at a certain position.
     *
     * @param position the position
     * @return the worker at that position
     */
    Worker* get(unsigned long position);

    /**
     * Gets the workers list.
     *
     * @return the workers list
     */
    tabHWorker getAll();

    tabHWorker getByLocation(const std::string& location);

    /**
     * Gets a worker from the workers list by its taxpayer identification number.
     *
     * @param taxID the taxpayer identification number
     * @return the worker on the workers list with that taxpayer identification number
     */
    Worker* getWorker(unsigned long taxID) const;

    /**
     * Gets the less busy worker which is the worker with less number of undelivered orders,
     * who works at the selected delivery location. If no one works at that location, the less
     * busy worker from other location will be chosen.
     * If all workers are at the maximum delivery capacity, throws an exception.
     *
     * @return the less busy worker
     */
    Worker* getLessBusyWorker(const std::string& location);

    /**
     * Sets the salary of the worker at a certain position.
     *
     * @param position the position
     * @param salary the new salary
     * @return the worker whose salary has been set
     */
    Worker * setSalary(unsigned position, float salary);

    /**
     * Adds a worker to the workers list.
     *
     * @param name the name
     * @param taxID the taxpayer identification number
     * @param salary the salary
     * @param credential the login credentials
     * @return the worker added to de workers list of the worker manager
     */
    Worker* add(std::string location, std::string name, unsigned long taxID = Person::DEFAULT_TAX_ID, float salary = Worker::DEFAULT_SALARY,
                Credential credential = {Worker::DEFAULT_USERNAME, Worker::DEFAULT_PASSWORD});

    /**
     * Removes a worker from the workers list.
     *
     * @param worker the worker to remove
     */
    void remove(Worker* worker);

    /**
     * Removes a worker from the workers list at a certain position.
     *
     * @param position the position on the workers list where the worker to be removed is
     */
    void remove(unsigned long position);

    /**
     * Reads all the workers data (name, taxpayer identification number, salary and login credentials) from a file and
     * creates news ones with that data.
     *
     * @param path the file path
     */
    void read(const std::string& path);

    /**
     * Writes all the workers data that are on the workers list (name, taxpayer identification number, salary and login
     * credentials) to a file.
     *
     * @param path the file path
     */
    void write(const std::string& path);

    /**
     * Prints all the workers data.
     *
     * @param os the output stream
     * @param showData if true, prints all data: name, taxpayer identification number, salary, number of undelivered
     * orders and mean evaluation of the delivered orders; otherwise, just prints the name, the taxpayer
     * identification number and the log status.
     * @return true, if there are no workers on the list yet; false, otherwise
     */
    bool print(std::ostream& os, bool showData = true, const std::string& location = {});

    /**
     * Raise all active workers salary in a certain percentage
     *
     * @param percentage - increased salary percentage
     */
    void raiseSalary(float percentage);

    /**
     * Decrease all active workers salary in a certain percentage
     *
     * @param percentage - decreased salary percentage
     */
    void decreaseSalary(float percentage);

private:
    /**
     * The hash table with all the active workers.
     */
    tabHWorker _workers;
    /**
     * The store location manager.
     */
    LocationManager* _locationManager;
};


#endif //FEUP_AEDA_PROJECT_WORKER_MANAGER_H
