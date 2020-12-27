
#include "worker_manager.h"
#include <utility>
#include "exception/file_exception.h"

WorkerManager::WorkerManager(LocationManager* lm) : _workers(), _locationManager(lm) {
}

bool WorkerManager::has(Worker *worker) const {
    return _workers.find(worker) != _workers.end();
}

Worker* WorkerManager::get(unsigned long position) {
    if (position >= _workers.size()) throw InvalidPersonPosition(position, _workers.size());
    auto it = _workers.begin(); std::advance(it, position);
    return *it;
}

tabHWorker WorkerManager::getAll() {
    return _workers;
}

Worker* WorkerManager::setSalary(unsigned position, float salary) {
    if(position >= _workers.size()) throw InvalidPersonPosition(position, _workers.size());
    auto it = _workers.begin(); std::advance(it, position);
    (*it)->setSalary(salary);
    return *it;
}

Worker* WorkerManager::add(std::string location, std::string name, unsigned long taxID, float salary, Credential credential) {
    if (!_locationManager->has(location)) throw LocationDoesNotExist(location);
    auto* worker = new Worker(std::move(location), std::move(name), taxID, salary, std::move(credential));
    _workers.insert(worker);
    return worker;
}

void WorkerManager::remove(Worker *worker) {
    auto position = _workers.find(worker);
    if(position == _workers.end()) throw PersonDoesNotExist(worker->getName(), worker->getTaxId());
    _workers.erase(position);
}

void WorkerManager::remove(unsigned long position) {
    if(position >= _workers.size()) throw InvalidPersonPosition(position, _workers.size());
    auto it = _workers.begin();
    std::advance(it, position);
    _workers.erase(it);
}

bool WorkerManager::print(std::ostream &os, bool showData, const std::string& location) {
    if (_workers.empty()){
        os << "No workers yet.\n";
        return false;
    }

    os << std::string(_workers.size() / 10 + 3, util::SPACE)
    << util::column("NAME", true)
    << util::column("TAX ID");
    if (showData){
        os << util::column("SALARY")
        << util::column("TO DELIVER")
        << util::column("RATING")
        << util::column("LOCATION");
    }
    else {
        os << util::column("LOGGED IN");
    }
    os << "\n";

    int count = 1;
    for (const auto& w: _workers){
        os << std::setw((int)_workers.size() / 10 + 3) << std::to_string(count++) + ". ";
        w->print(os, showData);
        if (!location.empty() && w->getLocation() == location) os << " <--";
        os << "\n";
    }
    return true;
}

Worker* WorkerManager::getLessBusyWorker(const std::string& location) {
    if (_workers.empty()) throw StoreHasNoWorkers();

    auto orderComp = [location](const Worker *worker1, const Worker *worker2) {
        if (worker1->getLocation() == location && worker2->getLocation() != location){
            return true;
        }
        if (worker1->getLocation() != location && worker2->getLocation() == location){
            return false;
        }
        return worker1->getUndeliveredOrders() < worker2->getUndeliveredOrders();
    };
    Worker* lessBusyWorker = *std::min_element(_workers.begin(), _workers.end(), orderComp);
    if (lessBusyWorker->getUndeliveredOrders() == Worker::MAX_ORDERS_AT_A_TIME) throw AllWorkersAreBusy();
    return lessBusyWorker;
}

void WorkerManager::read(const std::string& path) {
    std::ifstream file(path);
    if(!file) throw FileNotFound(path);

    std::string name, location;
    float salary = Worker::DEFAULT_SALARY;
    unsigned long taxID = Person::DEFAULT_TAX_ID;
    Credential credential;

    for(std::string line; getline(file, line); ){
        util::stripCarriageReturn(line);
        if (line.empty()) continue;

        std::stringstream ss(line);
        ss >> name >> taxID >> salary >> credential.username >> credential.password >> location;
        std::replace(name.begin(), name.end(), '-', ' ');
        std::replace(location.begin(),location.end(),'-',' ');
        add(location, name, taxID, salary, credential);
    }
}

void WorkerManager::write(const std::string &path) {
    std::ofstream file(path);
    if(!file) throw FileNotFound(path);

    for(const auto & worker: _workers){
        std::string nameToSave = worker->getName();
        std::string locationToSave = worker->getLocation();
        std::replace(nameToSave.begin(), nameToSave.end(), ' ', '-');
        std::replace(locationToSave.begin(), locationToSave.end(), ' ', '-');

        file << nameToSave << " " << worker->getTaxId() << " " << worker->getSalary()
        << " " << worker->getCredential().username << " " << worker->getCredential().password
        << " " << locationToSave << '\n';
    }
}

Worker* WorkerManager::getWorker(unsigned long taxID) const {
    for(const auto& _worker : _workers){
        if (_worker->getTaxId() == taxID) return _worker;
    }
    throw PersonDoesNotExist(taxID);
}

WorkerManager::~WorkerManager() {
    for (auto& w: _workers) delete w;
}

void WorkerManager::raiseSalary(float percentage) {
    for(const auto &worker : _workers){
        worker->setSalary(worker->getSalary()+(worker->getSalary()*percentage/100));
    }
}

void WorkerManager::decreaseSalary(float percentage) {
    for(const auto &worker : _workers){
        worker->setSalary(worker->getSalary()-(worker->getSalary()*percentage/100));
        if(worker->getSalary()<Worker::MINIMUM_SALARY) worker->setSalary(Worker::MINIMUM_SALARY);
    }
}

tabHWorker WorkerManager::getByLocation(const std::string &location) {
    tabHWorker res;
    for (const auto& w : _workers) if (w->getLocation() == location) res.insert(w);
    return res;
}
